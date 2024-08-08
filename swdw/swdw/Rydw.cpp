#include "Rydw.h"
#include <nlohmann/json.hpp>
#include <fstream>

CollectMonitor::~CollectMonitor()
{
}

time_t StrToTime(std::string & str)
{
	char* ptr = (char*)str.c_str();
	tm tmTemp;
	int year = 0, month = 0, day = 0, hour = 0, minute = 0, second = 0;
	sscanf(ptr, "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);
	tmTemp.tm_year = year - 1900;                 // 年，由于tm结构体存储的是从1900年开始的时间，所以tm_year为int临时变量减去1900。
	tmTemp.tm_mon = month - 1;                    // 月，由于tm结构体的月份存储范围为0-11，所以tm_mon为int临时变量减去1。
	tmTemp.tm_mday = day;                         // 日。
	tmTemp.tm_hour = hour;                        // 时。
	tmTemp.tm_min = minute;                       // 分。
	tmTemp.tm_sec = second;                       // 秒。
	tmTemp.tm_isdst = 0;
	time_t tTemp = mktime(&tmTemp);
	return tTemp;
}

void  FileTimeToTime_t(FILETIME  ft, time_t* t)
{
	LONGLONG  ll;
	ULARGE_INTEGER ui;
	ui.LowPart = ft.dwLowDateTime;
	ui.HighPart = ft.dwHighDateTime;
	//ll = ft.dwHighDateTime << 32 + ft.dwLowDateTime;  //这一步是不是多余的
	*t = ((LONGLONG)(ui.QuadPart - 116444736000000000) / 10000000);
	//将ui.QuadPart的数据类型ULONGLONG强制转换为time_t的LONGLONG数据类型
}

void SplitStr(const std::string& str, std::vector<std::string>& tokens, const std::string delim = "_")
{
	tokens.clear();

	auto start = str.find_first_not_of(delim, 0);       // 分割到的字符串的第一个字符
	auto position = str.find_first_of(delim, start);    // 分隔符的位置
	while (position != std::string::npos || start != std::string::npos) {
		// [start, position) 为分割下来的字符串
		tokens.emplace_back(std::move(str.substr(start, position - start)));
		start = str.find_first_not_of(delim, position);
		position = str.find_first_of(delim, start);
	}
}

int CollectMonitor::Init()
{
	ReadCfg();
	WORD versionReq = MAKEWORD(2, 2);
	WSAData wsa;
	if (WSAStartup(versionReq, &wsa) != 0)
	{
		//SPDLOG_LOGGER_CALL(log_, level_enum::err, " WSAStartup socket error code ={}", GetLastError());
	}
	int af = AF_INET;
	int type = SOCK_DGRAM;
	int protocol = IPPROTO_UDP;

	serSock_ = socket(af, type, protocol);
	if (serSock_ == INVALID_SOCKET)
	{
		int er = WSAGetLastError();
		return -1;
	}

	sockaddr_in servAddr;
	memset(&servAddr, 0, sizeof(servAddr));  //每个字节都用0填充
	servAddr.sin_family = PF_INET;  //使用IPv4地址
	servAddr.sin_addr.s_addr = inet_addr(listenIp_.c_str()); //自动获取IP地址
	servAddr.sin_port = htons(listenPort_);  //端口
	bind(serSock_, (SOCKADDR*)&servAddr, sizeof(SOCKADDR));

	BOOL bReuseaddr = TRUE;
	setsockopt(serSock_, SOL_SOCKET, SO_REUSEADDR, (const char*)&bReuseaddr, sizeof(BOOL));
	BOOL bDontLinger = FALSE;
	setsockopt(serSock_, SOL_SOCKET, SO_DONTLINGER, (const char*)&bDontLinger, sizeof(BOOL));
	int nNetTimeout = 3000; //1秒
	//发送时限
	setsockopt(serSock_, SOL_SOCKET, SO_SNDTIMEO, (char *)&nNetTimeout, sizeof(int));
	//接收时限
	setsockopt(serSock_, SOL_SOCKET, SO_RCVTIMEO, (char *)&nNetTimeout, sizeof(int));

	int nRecvBuf = 1024 * 1024 * 10; //设置为10M
	setsockopt(serSock_, SOL_SOCKET, SO_RCVBUF, (const char*)&nRecvBuf, sizeof(int));
	dstAddr_.sin_family = AF_INET;
	dstAddr_.sin_port = htons(listenPort_);
	dstAddr_.sin_addr.S_un.S_addr = inet_addr(listenIp_.c_str());
	if (m_dbApi.Connect(m_dbInfo) < 0)
	{
		std::cout << "Rtdb connect fail!" << std::endl;
		return -1;
	}
	else
	{
		std::cout << "Rtdb connect success!" << std::endl;
	}
	std::thread thrUdp(&CollectMonitor::UdpThr, this);
	std::thread thrHttp(&CollectMonitor::HttpThr, this);
	thrUdp.detach();
	thrHttp.detach();
	return 0;
}

int CollectMonitor::Run()
{
	const int m_keepAliveInterval = 20;
	const std::string SERVER_ADDRESS = m_mqttAddr + ":1883";
	const std::string CLIENT_ID = "collect";
	const auto TIMEOUT = std::chrono::seconds(1);
	mqtt::connect_options connOpts;
	connOpts.set_keep_alive_interval(m_keepAliveInterval);
	connOpts.set_clean_session(true);
	mqtt::async_client cli(SERVER_ADDRESS, CLIENT_ID);

	while (true)
	{
		try
		{
			if (!cli.is_connected())
			{
				std::cout << ("mqtt disconnect!") << std::endl;
				cli.connect(connOpts)->wait();
			}
			if (m_dataQueue.empty())
			{
				std::this_thread::sleep_for(std::chrono::seconds(m_interval));
				continue;
			}
			std::vector<Place> placeList;
			{
				std::lock_guard<std::mutex> guard(m_mutex);
				while (!m_dataQueue.empty())
				{
					placeList.push_back(m_dataQueue.front());
					m_dataQueue.pop();
				}
			}
			nlohmann::json jDatas;
			for (auto place : placeList)
			{
				nlohmann::json jData;
				jData["objectID"] = place.ID;
				jData["timestamp"] = place.timeStamp;
				jData["objectType"] = "P";
				jData["underRail"] = "";
				jData["powerQuantiry"] = "";
				jData["xAxis"] = (place.y * 10 - m_paraC) / 1000;
				jData["yAxis"] = (m_paraD - place.x * 10) / 1000;
				float height = 0.0;
				switch (place.floor)
				{
				case 1:
					height = 1.5;
					break;
				case 3:
					height = 6.7;
					break;
				case 4:
					height = 9.5;
					break;
				case 5:
					height = 14.0;
					break;
				default:
					break;
				}
				jData["zAxis"] = height;
				jData["labelInfo"] = "";
				jData["labelStatus"] = 1;
				jDatas["data"].emplace_back(jData);
			}
			std::string dataStr = jDatas.dump();
			mqtt::delivery_token_ptr pubtok;
			pubtok = cli.publish(m_topic, dataStr.c_str(), strlen(dataStr.c_str()), 2, false);
			pubtok->wait_for(TIMEOUT);
			std::this_thread::sleep_for(std::chrono::seconds(m_interval));
		}
		catch (const mqtt::exception& exc)
		{
			std::cout << "mqtt exception = " << exc.what();
		}
	}
	return 0;
}

int CollectMonitor::UdpThr()
{
	SOCKADDR clntAddr;  //客户端地址信息
	int nSize = sizeof(SOCKADDR);
	int ret = 0;
	while (true)
	{
		char buff[1024] = { 0 };
		ret = recvfrom(serSock_, buff, sizeof(buff), 0, (SOCKADDR*)&clntAddr, &nSize);
		if (ret <= 0)
		{
			std::cout << "recv error , ret = " << ret << std::endl;
			//LOGINFO("recv error , ret = {}", ret);
			continue;
		}
		if (ret != 46)
		{
			std::cout << "len error , ret = " << ret << std::endl;
			//LOGINFO("len error , ret = {}", ret);
			continue;
		}
		DataType recvData;
		memcpy_s(&recvData, sizeof(recvData), buff, sizeof(recvData));
		char buf[18] = { 0 };
		sprintf(buf, "%X", recvData.ID);
		std::string tmpID(buf);
		std::cout << "recv success , ID = " << tmpID << std::endl;
		Place p;
		p.ID = tmpID;
		p.floor = recvData.floor;
		p.timeStamp = time(NULL);
		p.x = recvData.x;
		p.y = recvData.y;
		p.z = recvData.z;
		{
			std::lock_guard<std::mutex> guard(m_mutex);
			m_dataQueue.push(p);
		}
		std::vector<std::wstring> tagList;
		std::vector<int32_t> resultList;
		std::vector<TagData> tagDataList;
		TagData tmpTag;
		tmpTag.status = 1;
		FILETIME ft;
		time_t t = time(NULL);
		Time_tToFileTime(t, &ft);
		tmpTag.timestamp = ft;
		std::string tagName;
		tagName = "db101." + tmpID + "_ID";
		tagList.push_back(StringToWstring(tagName));
		tmpTag.value = std::atoi(tmpID.c_str());
		tagDataList.push_back(tmpTag);
		tagName = "db101." + tmpID + "_floor";
		tagList.push_back(StringToWstring(tagName));
		tmpTag.value = recvData.floor;
		tagDataList.push_back(tmpTag);
		tagName = "db101." + tmpID + "_x";
		tagList.push_back(StringToWstring(tagName));
		tmpTag.value = recvData.x;
		tagDataList.push_back(tmpTag);
		tagName = "db101." + tmpID + "_y";
		tagList.push_back(StringToWstring(tagName));
		tmpTag.value = recvData.y;
		tagDataList.push_back(tmpTag);
		tagName = "db101." + tmpID + "_z";
		tagList.push_back(StringToWstring(tagName));
		tmpTag.value = recvData.z;
		tagDataList.push_back(tmpTag);
		ret = m_dbApi.SetValueByTagName(tagList, tagDataList, resultList);
		if (ret < 0)
		{
			std::cout << "set value fail , ID = " << recvData.ID << std::endl;
		}
	}
	return 0;
}

int CollectMonitor::HttpThr()
{
	crow::SimpleApp app;

	CROW_ROUTE(app, "/Liems/historicalRoute")
		.methods("POST"_method)
		([this](const crow::request& req, crow::response &res) {
		try
		{
			res.add_header("Content-Type", "application/json;charset=UTF-8");
			nlohmann::json jRecv;
			jRecv = nlohmann::json::parse(req.body);
			auto startDate = jRecv["startDate"].get<std::string>();
			auto endDate = jRecv["endDate"].get<std::string>();
			auto granularity = jRecv["granularity"].get<int>();
			auto staffID = jRecv["staffID"].get<std::string>();
			std::cout << "/Liems/historicalRoute req body = {}" << req.body << std::endl;
			nlohmann::json jData;
			std::vector<float> sendDatas;
			if (!m_dbApi.Connected())
			{
				if (m_dbApi.Connect(m_dbInfo) < 0)
				{
					std::cout << "reconnect fail" << std::endl;
					jData["state"] = -1;
					jData["records"] = sendDatas;
					res.write(jData.dump());
					res.end();
				}
				return;
			}
			auto startTime = StrToTime(startDate);
			auto endTime = StrToTime(endDate);
			FILETIME startFt;
			FILETIME endFt;
			Time_tToFileTime(startTime, &startFt);
			Time_tToFileTime(endTime, &endFt);
			std::vector<std::wstring> tagNames;
			std::vector<TAGID> tagIDList;
			std::vector<TagData> tagDatasX;
			std::vector<TagData> tagDatasY;
			std::vector<TagData> tagDatasZ;
			tagNames.emplace_back(StringToWstring("db101." + staffID + "_x"));
			tagNames.emplace_back(StringToWstring("db101." + staffID + "_y"));
			tagNames.emplace_back(StringToWstring("db101." + staffID + "_floor"));
			auto ret = m_dbApi.GetTagIDByTagName(tagNames, tagIDList);
			if (ret < 0 || tagIDList.size() != 3)
			{
				std::cout << "get tagID fail" << std::endl;
				jData["state"] = -1;
				jData["records"] = sendDatas;
				res.write(jData.dump());
				res.end();
				return;
			}
			std::ofstream ofs("C:\\data.txt");
			ret = m_dbApi.GetValueByTagID(tagIDList[0], startFt, endFt, tagDatasX);
			ret = m_dbApi.GetValueByTagID(tagIDList[1], startFt, endFt, tagDatasY);
			ret = m_dbApi.GetValueByTagID(tagIDList[2], startFt, endFt, tagDatasZ);
			//ret = m_dbApi.GetValueByPeriod(tagIDList[0], startFt, endFt, granularity, tagDatasX);
			//ret = m_dbApi.GetValueByPeriod(tagIDList[1], startFt, endFt, granularity, tagDatasY);
			//ret = m_dbApi.GetValueByPeriod(tagIDList[2], startFt, endFt, granularity, tagDatasZ);
			//ofs << "ret = " << ret << " tagDatasX.size = " << tagDatasX.size() << std::endl;
			if (ret <= 0 || tagDatasX.empty()|| tagDatasY.empty() || tagDatasZ.empty())
			{
				std::cout << "get tagValue fail" << std::endl;
				jData["state"] = -1;
				jData["records"] = sendDatas;
				res.write(jData.dump());
				res.end();
				return;
			}
			std::vector<float> outDatasX;
			std::vector<float> outDatasY;
			std::vector<float> outDatasZ;
			time_t tTemp;
			FileTimeToTime_t(tagDatasX.front().timestamp, &tTemp);
			startTime = tTemp;
			FileTimeToTime_t(tagDatasY.front().timestamp, &tTemp);
			startTime = startTime < tTemp ? startTime : tTemp;
			FileTimeToTime_t(tagDatasZ.front().timestamp, &tTemp);
			startTime = startTime < tTemp ? startTime : tTemp;

			FileTimeToTime_t(tagDatasX.back().timestamp, &tTemp);
			endTime = tTemp;
			FileTimeToTime_t(tagDatasY.back().timestamp, &tTemp);
			endTime = endTime > tTemp ? endTime : tTemp;
			FileTimeToTime_t(tagDatasZ.back().timestamp, &tTemp);
			endTime = endTime > tTemp ? endTime : tTemp;
			CalcTagDatasX(startTime, endTime, granularity, tagDatasX, outDatasX);
			CalcTagDatasY(startTime, endTime, granularity, tagDatasY, outDatasY);
			CalcTagDatasZ(startTime, endTime, granularity, tagDatasZ, outDatasZ);
			For(outDatasX.size())
			{
				sendDatas.push_back(outDatasY[index]);
				sendDatas.push_back(outDatasX[index]);
				sendDatas.push_back(outDatasZ[index]);
			}
			//float lastX = (tagDatasY[0].value * 10 - m_paraC) / 1000.0;
			//float lastY = (m_paraD - tagDatasX[0].value * 10) / 1000.0;
			//for (int index = 0; index + granularity - 1 < tagDatasX.size(); index += granularity)
			//{
			//	float x = (tagDatasY[index].value * 10 - m_paraC) / 1000.0;
			//	float y = (m_paraD - tagDatasX[index].value * 10) / 1000;
			//	ofs << "index = " << index << "last= " << lastX << "\t" << lastY << " value = " << x << "\t" << y << std::endl;
			//	if (abs(lastX - x) > granularity * 10 || abs(lastY - y) > granularity * 10)
			//	{
			//		continue;
			//	}
			//	lastX = x;
			//	lastY = y;
			//	float height = 0.0;
			//	int floor = tagDatasZ[index].value;
			//	switch (floor)
			//	{
			//	case 1:
			//		height = 1.5;
			//		break;
			//	case 3:
			//		height = 6.7;
			//		break;
			//	case 4:
			//		height = 9.5;
			//		break;
			//	case 5:
			//		height = 14.0;
			//		break;
			//	default:
			//		break;
			//	}
			//	sendDatas.emplace_back(x);
			//	sendDatas.emplace_back(y);
			//	sendDatas.emplace_back(height);
			//}
			jData["state"] = 0;
			jData["records"] = sendDatas;
			res.write(jData.dump());
			res.end();
		}
		catch (const std::exception&e)
		{
			std::cout << "catch exception {}" << e.what() << std::endl;
			res.write(e.what());
			res.end();
		}
	});
	app.port(m_httpPort)
		//.multithreaded()
		.run();
	return 0;
}

int CollectMonitor::ReadCfg()
{
	std::ifstream file("./config.ini");
	if (!file)
	{
		WritePrivateProfileString("Config", "MqttAdd", "127.0.0.1", "./config.ini");
		WritePrivateProfileString("Config", "RtdbAddr", "127.0.0.1", "./config.ini");
		WritePrivateProfileString("Config", "listenIp", "0.0.0.0", "./config.ini");
		WritePrivateProfileString("Config", "listenPort", "1234", "./config.ini");
		WritePrivateProfileString("Config", "topic", "topic", "./config.ini");
		WritePrivateProfileString("Config", "Url", "/lk/rest/fm/enigne/addWarn", "./config.ini");
		WritePrivateProfileString("Config", "httpPort", "9001", "./config.ini");
		WritePrivateProfileString("Config", "interval", "1000", "./config.ini");
		WritePrivateProfileString("Config", "paraC", "1000", "./config.ini");
		WritePrivateProfileString("Config", "paraD", "1000", "./config.ini");
	}
	char* lpPath = new char[MAX_PATH];
	char* MqttAdd = new char[100];
	char* RtdbAddr = new char[100];
	char* listenIp = new char[100];
	char* listenPort = new char[100];
	char* topic = new char[100];
	char* Url = new char[100];
	char* httpPort = new char[100];
	char* interval = new char[100];
	char* paraC = new char[100];
	char* paraD = new char[100];
	strcpy_s(lpPath, MAX_PATH, "./config.ini");
	GetPrivateProfileString("Config", "MqttAdd", "", MqttAdd, 100, lpPath);
	GetPrivateProfileString("Config", "RtdbAddr", "", RtdbAddr, 100, lpPath);
	GetPrivateProfileString("Config", "listenIp", "", listenIp, 100, lpPath);
	GetPrivateProfileString("Config", "listenPort", "", listenPort, 100, lpPath);
	GetPrivateProfileString("Config", "topic", "", topic, 100, lpPath);
	GetPrivateProfileString("Config", "Url", "", Url, 100, lpPath);
	GetPrivateProfileString("Config", "httpPort", "", httpPort, 100, lpPath);
	GetPrivateProfileString("Config", "interval", "", interval, 100, lpPath);
	GetPrivateProfileString("Config", "paraC", "", paraC, 100, lpPath);
	GetPrivateProfileString("Config", "paraD", "", paraD, 100, lpPath);
	delete[] lpPath;
	m_mqttAddr = MqttAdd;
	m_dbInfo.port = 7000;
	m_dbInfo.addr = StringToWstring(RtdbAddr);
	listenIp_ = listenIp;
	listenPort_ = std::atoi(listenPort);
	m_topic = topic;
	m_httpPort = std::atoi(httpPort);
	m_url = Url;
	m_interval = std::atoi(interval);
	m_paraC = std::atof(paraC);
	m_paraD = std::atof(paraD);
	delete[] MqttAdd;
	delete[] RtdbAddr;
	delete[] listenIp;
	delete[] listenPort;
	delete[] httpPort;
	delete[] Url;
	delete[] topic;
	delete[] interval;
	delete[] paraC;
	delete[] paraD;
	return 0;
}

void CollectMonitor::CalcTagDatasY(time_t startTime, time_t endTime, int period ,std::vector<TagData>& originDatas, std::vector<float>& outDatas)
{
	outDatas.clear();
	std::map<time_t, float>dataMap;
	for (auto &origin : originDatas)
	{
		time_t tTemp;
		FileTimeToTime_t(origin.timestamp, &tTemp);
		dataMap[tTemp] = (origin.value * 10 - m_paraC) / 1000.0;
		origin.value = (origin.value * 10 - m_paraC) / 1000.0;
	}
	int index = 0;
	while (period * index <= endTime - startTime)
	{
		time_t timeTemp = period * index;
		auto tempIndex = timeTemp + startTime;
		auto ptr = dataMap.upper_bound(tempIndex);
		if (ptr == dataMap.end())
		{
			outDatas.push_back(originDatas.back().value);
		}
		else
		{
			outDatas.push_back(ptr->second);
		}
		index++;
	}
}

void CollectMonitor::CalcTagDatasX(time_t startTime, time_t endTime, int period, std::vector<TagData>& originDatas, std::vector<float>& outDatas)
{
	outDatas.clear();
	std::map<time_t, float>dataMap;
	for (auto &origin : originDatas)
	{
		time_t tTemp;
		FileTimeToTime_t(origin.timestamp, &tTemp);
		dataMap[tTemp] = (m_paraD - origin.value * 10) / 1000.0;
		origin.value = (m_paraD - origin.value * 10) / 1000.0;
	}
	int index = 0;
	while (period * index <= endTime - startTime)
	{
		time_t timeTemp = period * index;
		auto tempIndex = timeTemp + startTime;
		auto ptr = dataMap.upper_bound(tempIndex);
		if (ptr == dataMap.end())
		{
			outDatas.push_back(originDatas.back().value);
		}
		else
		{
			outDatas.push_back(ptr->second);
		}
		index++;
	}
}

void CollectMonitor::CalcTagDatasZ(time_t startTime, time_t endTime, int period, std::vector<TagData>& originDatas, std::vector<float>& outDatas)
{
	outDatas.clear();
	std::map<time_t, float>dataMap;
	for (auto &origin : originDatas)
	{
		int floor = origin.value;
		switch (floor)
		{
		case 1:
			origin.value = 1.5;
			break;
		case 3:
			origin.value = 6.7;
			break;
		case 4:
			origin.value = 9.5;
			break;
		case 5:
			origin.value = 14.0;
			break;
		default:
			break;
		}
		time_t tTemp;
		FileTimeToTime_t(origin.timestamp, &tTemp);
		dataMap[tTemp] = origin.value;
	}
	int index = 0;
	while (period * index <= endTime - startTime)
	{
		time_t timeTemp = period * index;
		auto tempIndex = timeTemp + startTime;
		auto ptr = dataMap.upper_bound(tempIndex);
		if (ptr == dataMap.end())
		{
			outDatas.push_back(originDatas.back().value);
		}
		else
		{
			outDatas.push_back(ptr->second);
		}
		index++;
	}
}

std::wstring inline CollectMonitor::StringToWstring(const std::string str)
{
	unsigned len = str.size() * 2;// 预留字节数
	setlocale(LC_CTYPE, "");     //必须调用此函数
	wchar_t *p = new wchar_t[len];// 申请一段内存存放转换后的字符串
	mbstowcs(p, str.c_str(), len);// 转换
	std::wstring str1(p);
	delete[] p;// 释放申请的内存
	return str1;
}

inline void CollectMonitor::Time_tToFileTime(time_t t, FILETIME *ft)
{
	LONGLONG ll = Int32x32To64(t, 10000000) + 116444736000000000;
	ft->dwLowDateTime = (DWORD)ll;
	ft->dwHighDateTime = (DWORD)(ll >> 32);
}

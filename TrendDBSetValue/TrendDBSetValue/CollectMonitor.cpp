
#include "CollectMonitor.h"
#include "simple_web_server/client_http.hpp"
#include <nlohmann/json.hpp>
#include <fstream>
#include "minidump.h"
//auto httpClientPtr = std::make_shared<SimpleWeb::Client<SimpleWeb::HTTP>>("10.154.220.21:7004");
std::shared_ptr<SimpleWeb::Client<SimpleWeb::HTTP>> httpClientPtr;

CollectMonitor::~CollectMonitor()
{
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
	m_dbInfoGt.addr = L"127.0.0.1";
	m_dbInfoGt.port = 7000;
	Minidump::startMonitering("");
	auto path = "./log.txt";
	spdlog::set_pattern("[%H:%M:%S %z] [source %s] [line %#] [thread %t] %v");
	m_logger = spdlog::daily_logger_mt(" ", path, 0, 0);
	m_logger->set_level(static_cast<spdlog::level::level_enum>(m_logLevel));
	spdlog::flush_every(std::chrono::seconds(1));
	ReadTag();
	if (m_dbApiGt.Connect(m_dbInfoGt) < 0)
	{
		LOGINFO("connect gt rtdb error");
		std::cout << "connect rtdb error" << std::endl;
		return -1;
	}
	return 0;
}

int CollectMonitor::Run()
{
	std::vector<int32_t> resultList;
	while (true)
	{
		if (!m_dbApiGt.Connected())
		{
			LOGINFO("gt Rtdb Disconnect!");
			std::cout << "Rtdb Disconnect!" << std::endl;
			if (m_dbApiGt.Connect(m_dbInfoGt) < 0)
			{
				LOGINFO("gt Rtdb reconnect fail!");
				std::cout << "Rtdb reconnect fail!" << std::endl;
				continue;
			}
		}
		int ret = m_dbApiGt.SetValueByTagName(m_tagNameList, m_tagDataList, resultList);
		if (ret < 0)
		{
			LOGINFO("set value fail , ret = {} ", ret);
			std::cout << "set value fail , ret = " + ret << std::endl;
		}
		Sleep(1000);
	}

	return 0;
}

void CollectMonitor::CheckTimeThr()
{
	while (1)
	{
		time_t timeNow = time(NULL);
		m_rtdbMutex.lock();
		for (auto &timeOut : m_rtdbTimeOut)
		{
			if ((timeNow - timeOut.second) > timeOut_)
			{
				//LOGINFO("time out ,tag name = {}", timeOut.first);
				m_dataMutex.lock();
				m_tagData[timeOut.first] = 0;
				m_dataMutex.unlock();
			}
		}
		m_rtdbMutex.unlock();
		std::string sqlStr0 = "UPDATE tdmacquista set acqui_sta = 0 where acqui_id = ";
		std::string sqlStr1 = "UPDATE tdmacquista set acqui_sta = 1 where acqui_id = ";
		m_pgMutex.lock();
		for (auto &timeMap : m_pgTimeOut)
		{
			if ((timeNow - timeMap.second) > timeOut_)
			{
				std::string sqlString = sqlStr0 + "'" + timeMap.first + "'";
				PGresult * result = PQexec(m_conn, sqlString.c_str());
				//LOGINFO("time out ,sql = {}", sqlString);
				if (PQresultStatus(result) != PGRES_COMMAND_OK)
				{
					LOGINFO(" exec sql fail , sql = {} ,ret = {}", sqlString.c_str(), PQresultStatus(result));
					break;
				}
				//m_bufferMutex.lock();
				//m_bufferMap[timeMap.first].statusType = 0;
				//m_bufferMutex.unlock();
			}
			else
			{
				std::string sqlString = sqlStr1 + "'" + timeMap.first + "'";
				PGresult * result = PQexec(m_conn, sqlString.c_str());
				if (PQresultStatus(result) != PGRES_COMMAND_OK)
				{
					LOGINFO(" exec sql fail , sql = {} ,ret = {}", sqlString.c_str(), PQresultStatus(result));
				}
			}
		}
		m_pgMutex.unlock();
		std::this_thread::sleep_for(std::chrono::seconds(m_interval));
	}
}

int CollectMonitor::UnpackBuffer(std::string &buffer)
{
	using namespace nlohmann;
	try
	{
		auto jBuffer = json::parse(buffer);
		if (jBuffer.find("taskType") == jBuffer.end())
		{
			LOGINFO("zi duan 'taskType' do not exit !");
			std::cout << "zi duan 'taskType' do not exit !" << std::endl;
			return -1;
		}
		if (jBuffer.find("taskName") == jBuffer.end())
		{
			LOGINFO("zi duan 'taskName' do not exit !");
			std::cout << "zi duan 'taskName' do not exit !" << std::endl;
			return -1;
		}
		if (jBuffer.find("statusType") == jBuffer.end())
		{
			LOGINFO("zi duan 'statusType' do not exit !");
			std::cout << "zi duan 'statusType' do not exit !" << std::endl;
			return -1;
		}
		if (jBuffer.find("timestamp") == jBuffer.end())
		{
			LOGINFO("zi duan 'timestamp' do not exit !");
			std::cout << "zi duan 'timestamp' do not exit !" << std::endl;
			return -1;
		}
		jsonData data;
		data.taskType = jBuffer["taskType"];
		std::string taskName = jBuffer["taskName"];
		data.statusType = jBuffer["statusType"];
		data.timestamp = jBuffer["timestamp"];
		if (m_bufferMap.find(taskName) == m_bufferMap.end())
		{
			return 0;
		}
		//LOGINFO("ready to push map");
		{
			std::lock_guard<std::mutex>guard(m_bufferMutex);
			m_bufferMap[taskName] = data;
		}

	}
	catch (const std::exception&e)
	{
		LOGINFO("exception = {} !", e.what());
		std::cout << "exception = " << e.what() << std::endl;
		return -1;
	}
	return 0;
}

int CollectMonitor::SendThr()
{
	std::this_thread::sleep_for(std::chrono::seconds(3));
	while (true)
	{
		try
		{
			std::map<std::string, jsonData> bufferMap;
			{
				std::lock_guard<std::mutex>guard(m_bufferMutex);
				bufferMap = m_bufferMap;
				for (auto &map : m_bufferMap)
				{
					if (map.second.statusType == 0 || map.second.statusType == 2)
					{
						LOGDEBUG("task {} status = {}", map.first, map.second.statusType);
					}
					//map.second.statusType = 0;
				}
			}
			//if (bufferMap.empty())
			//{
			//	Sleep(30000);
			//	continue;
			//}
			//std::string sqlStr0 = "INSERT INTO tdmacquista ( acqui_id, acqui_sta ) VALUES ";
			//std::string sqlStr1 = "INSERT INTO tdmacquista ( acqui_id, acqui_sta ) VALUES ";
			//std::string sqlStr2 = "INSERT INTO tdmacquista ( acqui_id, acqui_sta ) VALUES ";
			//int number0 = 0;
			//int number1 = 0;
			//int number2 = 0;
			std::vector<std::wstring> tagList;
			std::vector<int32_t> resultList;
			std::vector<TagData> tagDataList;
			for (auto &data : bufferMap)
			{
				//if (data.second.statusType == 0)
				//{
				//	sqlStr0 += "('" + data.first + "',0),";
				//	number0++;
				//}
				//if (data.second.statusType == 1)
				//{
				//	sqlStr1 += "('" + data.first + "',1),";
				//	number1++;
				//}
				//if (data.second.statusType == 2)
				//{
				//	sqlStr2 += "('" + data.first + "',2),";
				//	number2++;
				//}

				std::string prefix;
				switch (data.second.taskType)
				{
				case 0:
					prefix = "CollectTask";
					break;
				case 1:
					prefix = "CalcTask";
					break;
				case 2:
					prefix = "TransmitTask";
					break;
				case 3:
					prefix = "VibrationTask";
					break;
				case 4:
					prefix = "PowerCollectTask";
					break;
				case 5:
					prefix = "PowerTrans";
					break;
				default:
					break;
				}
				m_dataMutex.lock();
				m_tagData[m_prefix + prefix + ":" + data.first] = data.second.statusType;
				m_dataMutex.unlock();
				m_rtdbMutex.lock();
				m_rtdbTimeOut[m_prefix + prefix + ":" + data.first] = time(NULL);
				m_rtdbMutex.unlock();
				m_pgMutex.lock();
				if (data.second.statusType == 1)
				{
					m_pgTimeOut[data.first] = data.second.timestamp;
				}
				m_pgMutex.unlock();
				std::vector<std::wstring> tagNames;
				std::vector<TagData> tagDataList;
				nlohmann::json jobj;
				jobj["warnSta"] = data.second.statusType == 1 ? 1 : 0;
				jobj["warnTyp"] = data.second.statusType == 0 ? 2 : 1;
				jobj["acquiId"] = data.first;
				if (m_queryTags.find(data.first) != m_queryTags.end())
				{
					tagNames.emplace_back(m_queryTags[data.first]);
					int ret = m_dbApiGt.GetValueByTagName(tagNames, tagDataList);
					if (ret < 0)
					{
						LOGINFO("get value fail , ret = {} ", ret);
					}
					else
					{
						if (tagDataList.front().value == 1)
						{
							jobj["warnSta"] = 1;
							jobj["warnTyp"] = 1;
						}
						else
						{
							jobj["warnSta"] = 0;
							jobj["warnTyp"] = 2;
						}
					}
				}

				//SimpleWeb::CaseInsensitiveMultimap headerMultiMap;
				//headerMultiMap.insert(std::unordered_multimap<std::string, std::string, SimpleWeb::CaseInsensitiveHash, SimpleWeb::CaseInsensitiveEqual>::value_type("Content-Type", "application/json;charset=UTF-8"));
				//headerMultiMap.insert(std::unordered_multimap<std::string, std::string, SimpleWeb::CaseInsensitiveHash, SimpleWeb::CaseInsensitiveEqual>::value_type("Content-Length", std::to_string(jobj.dump().size())));
				////LOGDEBUG("ready to send url!");
				//if (data.second.statusType != 1)
				//{
				//	if (m_alarmCounts[data.first] == 100)
				//	{
				//		auto res = httpClientPtr->request("POST", m_url.c_str(), jobj.dump(), headerMultiMap);

				//		if (res->status_code != "200 ")
				//		{
				//			LOGINFO("post url fail! ,res = {}", res->status_code);
				//			std::cout << "post url fail!" << std::endl;
				//		}
				//		m_alarmCounts[data.first] = 0;
				//	}
				//	else
				//	{
				//		m_alarmCounts[data.first]++;
				//	}
				//}
				//else
				//{
				//	auto res = httpClientPtr->request("POST", m_url.c_str(), jobj.dump(), headerMultiMap);

				//	if (res->status_code != "200 ")
				//	{
				//		LOGINFO("post url fail! ,res = {}", res->status_code);
				//		std::cout << "post url fail!" << std::endl;
				//	}
				//	m_alarmCounts[data.first] = 0;
				//}
			}
			//auto iter0 = sqlStr0.end() - 1;
			//sqlStr0.erase(iter0);
			//auto iter1 = sqlStr1.end() - 1;
			//sqlStr1.erase(iter1);
			//auto iter2 = sqlStr2.end() - 1;
			//sqlStr2.erase(iter2);
			//sqlStr0 += "ON conflict ( acqui_id ) DO \
			//	UPDATE \
			//	SET acqui_sta = 0";
			//sqlStr1 += "ON conflict ( acqui_id ) DO \
			//	UPDATE \
			//	SET acqui_sta = 1";
			//sqlStr2 += "ON conflict ( acqui_id ) DO \
			//	UPDATE \
			//	SET acqui_sta = 2";

			//LOGINFO("ready to write pg!");

			//if (number0 > 0)
			//{
			//	PGresult * result = PQexec(m_conn, sqlStr0.c_str());
			//	if (PQresultStatus(result) != PGRES_COMMAND_OK)
			//	{
			//		LOGINFO(" exec sql fail , sql = {} ,ret = {}", sqlStr0.c_str(), PQresultStatus(result));
			//		std::cout << "exec sql fail" << std::endl;
			//		continue;
			//	}
			//}
			//if (number1 > 0)
			//{
			//	PGresult *result = PQexec(m_conn, sqlStr1.c_str());
			//	if (PQresultStatus(result) != PGRES_COMMAND_OK)
			//	{
			//		LOGINFO(" exec sql fail , sql = {} ,ret = {}", sqlStr1.c_str(), PQresultStatus(result));
			//		std::cout << "exec sql fail" << std::endl;
			//		continue;
			//	}
			//}
			//if (number2 > 0)
			//{
			//	PGresult *result = PQexec(m_conn, sqlStr2.c_str());
			//	if (PQresultStatus(result) != PGRES_COMMAND_OK)
			//	{
			//		LOGINFO(" exec sql fail , sql = {} ,ret = {}", sqlStr2.c_str(), PQresultStatus(result));
			//		std::cout << "exec sql fail" << std::endl;
			//		continue;
			//	}
			//}
			TagData tmpTag;
			tmpTag.status = 1;
			FILETIME ft;
			time_t t = time(NULL);
			Time_tToFileTime(t, &ft);
			tmpTag.timestamp = ft;
			m_dataMutex.lock();
			for (auto &tag : m_tagData)
			{
				tagList.emplace_back(StringToWstring(tag.first));
				tmpTag.value = tag.second;
				tagDataList.emplace_back(tmpTag);
			}
			m_dataMutex.unlock();
			if (m_gtEnable)
			{
				int ret = m_dbApiGt.SetValueByTagName(tagList, tagDataList, resultList);
				if (ret < 0)
				{
					LOGINFO("set value fail , ret = {} ", ret);
					std::cout << "set value fail , ret = " + ret << std::endl;
				}
			}
			int ret = m_dbApiJt.SetValueByTagName(tagList, tagDataList, resultList);
			if (ret < 0)
			{
				LOGINFO("set value fail , ret = {} ", ret);
				std::cout << "set value fail , ret = " + ret << std::endl;
			}
		}
		catch (const std::exception&e)
		{
			LOGINFO("send exception = {}", e.what());
			std::this_thread::sleep_for(std::chrono::seconds(m_interval));
			continue;
		}
		std::this_thread::sleep_for(std::chrono::seconds(m_interval));
		continue;
	}
	return 0;
}

int CollectMonitor::ReadCfg()
{
	std::ifstream file("./config.ini");
	if (!file)
	{
		WritePrivateProfileString("Config", "MqttAdd", "127.0.0.1", "./config.ini");
		WritePrivateProfileString("Config", "PgAddr", "10.154.220.25", "./config.ini");
		WritePrivateProfileString("Config", "PgDbName", "sushine_business", "./config.ini");
		WritePrivateProfileString("Config", "PgUser", "postgres", "./config.ini");
		WritePrivateProfileString("Config", "PgPwd", "luculent", "./config.ini");
		WritePrivateProfileString("Config", "PgPort", "5432", "./config.ini");
		WritePrivateProfileString("Config", "RtdbAddrGt", "10.154.220.22", "./config.ini");
		WritePrivateProfileString("Config", "RtdbAddrJt", "172.16.0.117", "./config.ini");
		WritePrivateProfileString("Config", "Url", "/lk/rest/fm/enigne/addWarn", "./config.ini");
		WritePrivateProfileString("Config", "UrlAddr", "10.154.220.21:7004", "./config.ini");
		WritePrivateProfileString("Config", "prefix", "db101.GT:", "./config.ini");
		WritePrivateProfileString("Config", "logLevel", "1", "./config.ini");
		WritePrivateProfileString("Config", "interval", "600", "./config.ini");
	}
	char* lpPath = new char[MAX_PATH];
	char* MqttAdd = new char[100];
	char* PgAddr = new char[100];
	char* PgDbName = new char[100];
	char* PgUser = new char[100];
	char* PgPwd = new char[100];
	char* PgPort = new char[100];
	char* RtdbAddrGt = new char[100];
	char* RtdbAddrJt = new char[100];
	char* Url = new char[100];
	char* UrlAddr = new char[100];
	char* prefix = new char[100];
	char* logLevel = new char[100];
	char* interval = new char[100];
	strcpy_s(lpPath, MAX_PATH, "./config.ini");

	GetPrivateProfileString("Config", "MqttAdd", "", MqttAdd, 100, lpPath);
	GetPrivateProfileString("Config", "PgAddr", "", PgAddr, 100, lpPath);
	GetPrivateProfileString("Config", "PgDbName", "", PgDbName, 100, lpPath);
	GetPrivateProfileString("Config", "PgUser", "", PgUser, 100, lpPath);
	GetPrivateProfileString("Config", "PgPwd", "", PgPwd, 100, lpPath);
	GetPrivateProfileString("Config", "PgPort", "", PgPort, 100, lpPath);
	GetPrivateProfileString("Config", "RtdbAddrGt", "", RtdbAddrGt, 100, lpPath);
	GetPrivateProfileString("Config", "RtdbAddrJt", "", RtdbAddrJt, 100, lpPath);
	GetPrivateProfileString("Config", "Url", "", Url, 100, lpPath);
	GetPrivateProfileString("Config", "UrlAddr", "", UrlAddr, 100, lpPath);
	GetPrivateProfileString("Config", "prefix", "", prefix, 100, lpPath);
	GetPrivateProfileString("Config", "logLevel", "", logLevel, 100, lpPath);
	GetPrivateProfileString("Config", "interval", "", interval, 100, lpPath);
	delete[] lpPath;
	m_mqttAddr = MqttAdd;
	m_pgIp = PgAddr;
	m_pgDbName = PgDbName;
	m_pgUser = PgUser;
	m_pgPwd = PgPwd;
	m_pgPort = PgPort;
	m_dbInfoGt.addr = StringToWstring(RtdbAddrGt);
	m_dbInfoGt.port = 7000;
	m_dbInfoJt.addr = StringToWstring(RtdbAddrJt);
	m_dbInfoJt.port = 7000;
	m_url = Url;
	m_urlAddr = UrlAddr;
	m_prefix = prefix;
	m_logLevel = std::atoi(logLevel);
	m_interval = std::atoi(interval);
	std::string s = RtdbAddrGt;
	if (s.empty())
	{
		m_gtEnable = false;
	}
	delete[] MqttAdd;
	delete[] PgAddr;
	delete[] PgDbName;
	delete[] PgUser;
	delete[] PgPwd;
	delete[] PgPort;
	delete[] RtdbAddrGt;
	delete[] RtdbAddrJt;
	delete[] Url;
	delete[] UrlAddr;
	delete[] prefix;
	delete[] logLevel;
	delete[] interval;
	return 0;
}

int CollectMonitor::ReadTag()
{
	std::ifstream ifs("./tag.txt");
	if (!ifs)
	{
		LOGINFO("can not find tag.txt");
		return -1;
	}
	std::string lineStr;
	jsonData data;
	data.statusType = 1;
	data.timestamp = 0;
	TagData tag;
	tag.status = 1;
	while (std::getline(ifs, lineStr))
	{
		std::vector<std::string> tmpList;
		SplitStr(lineStr, tmpList, ",");
		tag.value = std::atof(tmpList[1].c_str());
		m_tagNameList.push_back(StringToWstring(tmpList[0]));
		m_tagDataList.push_back(tag);
	}
	LOGINFO("m_queryTags.size = {}", m_queryTags.size());
	return 0;
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

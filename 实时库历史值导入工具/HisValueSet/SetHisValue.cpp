#include <regex>
#include "SetHisValue.h"

SetHisValue::SetHisValue(SetValueInfo info_)
{
	m_info = info_;
	my_logger_ = m_info.my_logger_;
	m_dbName = StringToWstring(info_.dbName_);
	m_groupName = StringToWstring(info_.groupName_);
}

SetHisValue::~SetHisValue()
{
	this->m_dbApi.Disconnect();
	this->m_dbApi.UnSetDefaultInstance();
}
//
//************************************
// Method:    Run
// FullName:  SetHisValue::Run
// Access:    public 
// Returns:   int
// Qualifier:
//************************************

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
//void SetHisValue::GetDirects(std::string &path)
//{
//	m_fileLists.clear();
//	boost::filesystem::path myPath(path);
//	boost::filesystem::directory_iterator endIter;
//	for (boost::filesystem::directory_iterator iter(myPath); iter != endIter; iter++) {
//		if (boost::filesystem::is_directory(*iter)) {
//			std::vector<std::string>fileList;
//			GetFiles(iter->path().string(), fileList);
//			m_fileLists[iter->path().stem().string()] = fileList;
//		}
//		else {}
//	}
//}

const std::vector<std::string>& SetHisValue::scanFilesUseRecursive(const std::string& rootPath, std::vector<std::string>& container) {
	namespace fs = boost::filesystem;
	std::regex pattern("^.*\.csv");
	fs::path fullpath(rootPath, fs::native);
	std::vector<std::string> &ret = container;

	if (!fs::exists(fullpath)) { return ret; }
	fs::recursive_directory_iterator end_iter;
	for (fs::recursive_directory_iterator iter(fullpath); iter != end_iter; iter++) {
		try {
			if (fs::is_directory(*iter)) {
				std::cout << *iter << "is dir" << std::endl;
				//ret.push_back(iter->path().string());
				//ScanAllFiles::scanFiles(iter->path().string(),ret);
			}
			else {
				if (regex_match(iter->path().string(), pattern))
					ret.push_back(iter->path().string());
				std::cout << *iter << " is a file" << std::endl;
			}
		}
		catch (const std::exception & ex) {
			std::cerr << ex.what() << std::endl;
			continue;
		}
	}
	return ret;
}

//void SetHisValue::GetFiles(std::string path, std::vector<std::string> &fileList)
//{
//	boost::filesystem::path myPath(path);
//	boost::filesystem::directory_iterator endIter;
//	for (boost::filesystem::directory_iterator iter(myPath); iter != endIter; iter++) {
//		if (boost::filesystem::is_directory(*iter)) {
//		}
//		else {
//			fileList.emplace_back(iter->path().string());
//		}
//	}
//}

int SetHisValue::Run()
{
	int ret = 0;
	if (m_info.mode == MODE::MAKE_FILE)
	{
		ret = GetTagNames(m_tagNames);
		if (ret < 0)
		{
			LOGINFO("Get TagName fail,ret = {}", ret)
				return ret;
		}
		LOGDEBUG("get tag number = {}", m_tagNames.size());
		std::vector<TagInfo>tagInfo;
		std::vector<int32_t>resultList;
		GroupInfo g_info(m_groupName);
		std::vector<GroupInfo>groupList({ g_info });
		m_dbApi.AddGroup(m_dbName, groupList, resultList);
		for (auto tagName : m_tagNames)
		{
			std::wstring wTagName = StringToWstring(m_info.prefix_ + tagName);
			TagInfo tag(wTagName, L"7", m_groupName, m_dbName, 1, 0.3);
			tag.timePrecision = 0;
			tagInfo.push_back(tag);
		}
		ret = m_dbApi.AddTag(m_dbName, tagInfo, resultList);
		if (ret != tagInfo.size())
		{
			LOGINFO("Add Tag fail ,ret = {}", ret);
		}
		finishFlg = true;
	}
	else
	{
		char timeStr[50];
		time_t now = time(NULL);
		strftime(timeStr, 50, "%Y%m%d%H%M%S", localtime(&now));
		m_failDirec = std::string("./failFiles_") + timeStr + "/";
		LOGDEBUG("m_failDirec is {}", m_failDirec);
		//m_setThr = std::thread(&SetHisValue::Set, this);
		m_getThr = std::thread(&SetHisValue::GetData, this);
		//m_setThr.detach();
		m_getThr.detach();
	}
	return 0;
}
//
//************************************
// Method:    Init
// FullName:  SetHisValue::Init
// Access:    public 
// Returns:   int
// Qualifier:
//************************************
int SetHisValue::Init()
{
	m_fileLists = scanFilesUseRecursive(m_info.filePath_);
	if (m_fileLists.empty())
	{
		LOGINFO(" fileLists empty , m_fileLists.size() = {}", m_fileLists.size());
		return FILEEMPTY;
	}
	m_dbInfo.addr = StringToWstring(m_info.addr_);
	m_dbInfo.port = m_info.port_;
	if (m_dbApi.Connect(m_dbInfo) < 0)
	{
		LOGINFO("connect rtdb error");
		return CONNECTERROR;
	}
	return 0;
}
//
//************************************
// Method:    GetProGress
// FullName:  SetHisValue::GetProGress
// Access:    public 
// Returns:   double
// Qualifier:
//************************************
double SetHisValue::GetProGress()
{
	if (m_totalProgress > 0)
		return m_progress / (m_totalProgress *1.0);
	else return 0.0;
}
//
//************************************
// Method:    SetValue
// FullName:  SetHisValue::SetValue
// Access:    private 
// Returns:   int
// Qualifier:
//************************************
int SetHisValue::Set()
{
	int totalProgress = 0;
	std::unordered_map<std::string, std::vector<TagData>> dataMap;
	std::unique_lock<std::mutex> lck(m_mutex);
	m_msgQueue.wait(lck);
	totalProgress += m_Datas.size();
	while (!m_Datas.empty())
	{
		dataMap[m_Datas.front().first].emplace_back(m_Datas.front().second);
		m_Datas.pop();
	}
	lck.unlock();
	SetValue(dataMap);
	dataMap.clear();
	while (true)
	{
		if (m_readOverFlg)
			break;
		Sleep(1000);
	}
	clock_t t = clock();
	m_totalProgress += m_Datas.size() + totalProgress;
	while (!m_Datas.empty())
	{
		dataMap[m_Datas.front().first].emplace_back(m_Datas.front().second);
		m_Datas.pop();
	}
	LOGINFO("copy data using {}", clock() - t);
	SetValue(dataMap);
	finishFlg = true;
	return 0;
}

int SetHisValue::SetValue(std::unordered_map<std::string, std::vector<TagData>>& dataMap)
{
	std::ofstream ofsGlobal("./failLog.txt");
	std::string failDirec = m_failDirec;
	std::vector <TAGID> tagIDList;
	m_progress = 0;
	for (auto &datas : dataMap)
	{
		LOGINFO("datas.size = {}", datas.second.size());

		if (m_dbApi.GetTagIDByTagName({ StringToWstring(m_info.dbName_ + "." + datas.first) }, tagIDList) < 0)
		{
			LOGINFO("get tagID error tagName = {}", datas.first);
			continue;
			//disConnectFlg = true;
			//Sleep(5000);
			//disConnectFlg = false;
			//while (true)
			//{
			//	if (m_dbApi.GetTagIDByTagName({ StringToWstring(m_info.dbName_ + "." + datas.first) }, tagIDList) < 0)
			//	{
			//		tagIDList.clear();
			//		LOGINFO("get tagID error tagName = {}", datas.first);
			//		Sleep(10000);
			//		continue;
			//	}
			//	break;
			//}
		}
		tagName_ = datas.first;
		LOGDEBUG("tagName = {}", tagName_);
		long scanIdx = 1;
		while (!cancelFlg)
		{
			if (pauseStatus)
			{
				continue;
			}
			if (!m_dbApi.Connected())
			{
				disConnectFlg = true;
				LOGINFO("RTDB disconnect");
				Sleep(5000);
				disConnectFlg = false;
				m_dbApi.Disconnect();
				while (1)
				{
					if (m_dbApi.Connect(m_dbInfo) >= 0)
					{
						LOGINFO("RTDB reconnect success");
						break;
					}
					Sleep(10000);
				}
			}
			if ((scanIdx*m_info.interval) > datas.second.size())
			{
				std::vector<TagData>data_(datas.second.begin() + (m_info.interval*(scanIdx - 1)), datas.second.end());
				int ret = m_dbApi.SetHistoryValues(tagIDList.back(), data_);
				if (ret >= 0)
				{
					LOGDEBUG("set value success tagID = {}", std::to_string(tagIDList.back().tagID));
				}
				else
				{
					if (!boost::filesystem::exists(m_failDirec))
					{
						CreateDirectory(m_failDirec.c_str(), NULL);
					}
					LOGDEBUG("set value fail tagID = {} , ret = {}", std::to_string(tagIDList.back().tagID), ret);
					std::string filePath = failDirec + std::to_string(tagIDList.back().tagID) + ".csv";
					std::ifstream ifs(filePath);
					if (!ifs)
					{
						ifs.close();
						std::ofstream ofs;

						ofs.open(filePath, std::ios::app);
						ofs << "time," << tagName_ << std::endl;
						time_t t = 0;
						for (auto &dat : data_)
						{
							Tools::FileTimeToTime_t(dat.timestamp, &t);
							std::string timeStr = Tools::Time_tToString(t);
							if (timeStr == "0")
							{
								ofsGlobal << "tag " << tagName_ << " set value error value = " << dat.value << std::endl;
							}
							else
							{
								ofs << timeStr << "," << dat.value << std::endl;
							}
						}
						ofs.close();
					}
					else
					{
						ifs.close();
						std::ofstream ofs;
						ofs.open(filePath, std::ios::app);
						time_t t = 0;
						for (auto &dat : data_)
						{
							Tools::FileTimeToTime_t(dat.timestamp, &t);
							std::string timeStr = Tools::Time_tToString(t);
							if (timeStr == "0")
							{
								ofsGlobal << "tag " << tagName_ << " set value error value = " << dat.value << std::endl;
							}
							else
							{
								ofs << timeStr << "," << dat.value << std::endl;
							}
						}
						ofs.close();
					}
				}
				m_progress += (scanIdx*m_info.interval) - datas.second.size();
				break;
			}
			std::vector<TagData> data_(datas.second.begin() + (m_info.interval*(scanIdx - 1)), datas.second.begin() + (m_info.interval)*scanIdx);
			int ret = m_dbApi.SetHistoryValues(tagIDList.back(), data_);
			if (ret >= 0)
			{
				LOGDEBUG("set value success tagID = {} ,scanIdx = {}", std::to_string(tagIDList.back().tagID), scanIdx);
			}
			else
			{
				if (!boost::filesystem::exists(m_failDirec))
				{
					CreateDirectory(m_failDirec.c_str(), NULL);
				}
				time_t t = time(NULL);
				FileTimeToTime_t(data_.front().timestamp, &t);
				LOGDEBUG("set value fail tagID = {} , time = {} , ret = {} ", std::to_string(tagIDList.back().tagID),t, ret);
				std::string filePath = failDirec + std::to_string(tagIDList.back().tagID) + ".csv";
				std::ifstream ifs(filePath);
				if (!ifs)
				{
					ifs.close();
					std::ofstream ofs;
					ofs.open(filePath, std::ios::app);
					ofs << "time," << tagName_ << std::endl;
					time_t t = 0;
					for (auto &dat : data_)
					{
						Tools::FileTimeToTime_t(dat.timestamp, &t);
						std::string timeStr = Tools::Time_tToString(t);
						if (timeStr == "0")
						{
							ofsGlobal << "tag " << tagName_ << " set value error value = " << dat.value << std::endl;
						}
						else
						{
							ofs << timeStr << "," << dat.value << std::endl;
						}
					}
					ofs.close();
				}
				else
				{
					ifs.close();
					std::ofstream ofs;
					ofs.open(filePath, std::ios::app);
					time_t t = 0;
					for (auto &dat : data_)
					{
						Tools::FileTimeToTime_t(dat.timestamp, &t);
						std::string timeStr = Tools::Time_tToString(t);
						if (timeStr == "0")
						{
							ofsGlobal << "tag " << tagName_ << " set value error value = " << dat.value << std::endl;
						}
						else
						{
							ofs << timeStr << "," << dat.value << std::endl;
						}
					}
					ofs.close();
				}
			}
			m_progress += m_info.interval;
			scanIdx++;
		}
		scanIdx = 1;
		tagIDList.clear();
	}
	return 0;
}

int SetHisValue::GetData()
{
	int fileIndex = 0;
	int lineIndex = 0;
	int pointIndex = 0;
	TagData tag;
	tag.status = 1;
	std::string data_;
	FILETIME ft;
	std::vector <std::string> linedata;
	std::vector<std::string>tagNames;
	for (auto &fileList : m_fileLists)
	{
		int regexType = -1;
		std::string filepath = fileList;
		std::ifstream istrm(filepath);
		if (!istrm)
		{
			return OPENERROR;
		}
		while (getline(istrm, data_))
		{
			pointIndex = 0;
			if (lineIndex == 0)
			{
				Tools::SplitString(data_, tagNames, ",");
				tagNames.erase(tagNames.begin());
				for (auto &tag : tagNames)
				{
					tag = m_info.prefix_ + tag;
				}
				lineIndex++;
				continue;
			}
			Tools::SplitString(data_, linedata, ",");

			Tools::Time_tToFileTime(TimeConvert1(linedata.front()), &ft);
			tag.timestamp = ft;
			for (auto it = (++linedata.begin()); it != linedata.end(); ++it)
			{
				if (it->size() < 1)
				{
					pointIndex++;
					continue;
				}
				tag.value = (atof(it->c_str()));
				//std::unique_lock<std::mutex> lck(m_mutex);
				m_Datas.push(std::pair<std::string, TagData>(tagNames[pointIndex], tag));
				//lck.unlock();
				//if (m_Datas.size() > m_info.readMax)
				//{
				//	m_msgQueue.notify_all();
				//}
				pointIndex++;
			}
			linedata.clear();
			lineIndex++;
		}
		tagNames.clear();
		LOGDEBUG("read over ,fileName = {}", fileList);
		istrm.close();
		/*remove(filepath.c_str());*/
		int progress = 0;
		std::unordered_map<std::string, std::vector<TagData>> dataMap;
		while (!m_Datas.empty())
		{
			dataMap[m_Datas.front().first].emplace_back(m_Datas.front().second);
			m_Datas.pop();
			progress++;
		}
		m_totalProgress = progress;
		SetValue(dataMap);
		lineIndex = 0;
		fileIndex++;
	}
	m_readOverFlg = true;
	finishFlg = true;
	//m_msgQueue.notify_all();
	return 0;
}

int SetHisValue::GetTagNames(std::set<std::string>& tagNames)
{
	std::string data_;
	std::vector<std::string>tagName;
	int fileIndex = 0;
	int directIndex = m_fileLists.size();

	for (auto &fileList : m_fileLists)
	{

		int index = 0;
		std::string filepath(fileList);
		std::ifstream istrm(filepath);
		if (!istrm)
		{
			return OPENERROR;
		}
		getline(istrm, data_);
		Tools::SplitString(data_, tagName, ",");
		tagName.erase(tagName.begin());
		tagNames.insert(tagName.begin(), tagName.end());
		tagName.clear();
		fileIndex++;
		data_.clear();
	}
	if (tagNames.empty())
	{
		LOGINFO("tagNames empty!");
		return -1;
	}
	return 0;
}
//
//************************************
// Method:    StringToWstring
// FullName:  SetHisValue::StringToWstring
// Access:    private 
// Returns:   std::wstring
// Qualifier:
// Parameter: const std::string str
//************************************
std::wstring SetHisValue::StringToWstring(const std::string str)
{
	unsigned len = str.size() * 2;// 预留字节数
	setlocale(LC_CTYPE, "");     //必须调用此函数
	wchar_t *p = new wchar_t[len];// 申请一段内存存放转换后的字符串
	mbstowcs(p, str.c_str(), len);// 转换
	std::wstring str1(p);
	delete[] p;// 释放申请的内存
	return str1;
}

void SetHisValue::SplitTagName(const std::string & s, std::vector<std::string>& v, const std::string & c)
{
	std::string::size_type pos1, pos2;
	pos2 = s.find(c);
	pos1 = 0;
	while (std::string::npos != pos2)
	{
		v.push_back(m_info.prefix_ + s.substr(pos1, pos2 - pos1));

		pos1 = pos2 + c.size();
		pos2 = s.find(c, pos1);
	}
	if (pos1 != s.length())
		v.push_back(m_info.prefix_ + s.substr(pos1));
}

time_t SetHisValue::TimeConvert1(std::string timeStr)
{
	std::string pattern1 = "^(20[0-9][0-9])/([1-9]|[0-2][0-9]|3[0-1])/(0[1-9]|[1-9]|1[0-2]) +([0-1][0-9]|2[0-3]):([0-5][0-9]):([0-5][0-9])";// 
	std::regex express(pattern1, std::regex::icase);
	auto els_begin = std::sregex_iterator(timeStr.cbegin(), timeStr.cend(), express);

	auto els_end = std::sregex_iterator();
	if (els_begin == els_end)
	{
		return -1;
	}

	int year = std::atoi((*els_begin)[1].str().c_str());
	int month = std::atoi((*els_begin)[2].str().c_str());
	int day = std::atoi((*els_begin)[3].str().c_str());
	int hour = std::atoi((*els_begin)[4].str().c_str());
	int min = std::atoi((*els_begin)[5].str().c_str());
	int second = std::atoi((*els_begin)[6].str().c_str());
	tm tmTemp;
	tmTemp.tm_year = year - 1900;
	tmTemp.tm_mon = month - 1;
	tmTemp.tm_mday = day;
	tmTemp.tm_hour = hour;
	tmTemp.tm_min = min;
	tmTemp.tm_sec = second;
	tmTemp.tm_isdst = 0;
	time_t tTemp = mktime(&tmTemp);
	return tTemp;
}




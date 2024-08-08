
#include "PlayBack.h"
#include <fstream>

CollectMonitor::~CollectMonitor()
{
}

int SplitTime(time_t &startAll, time_t &endAll, std::vector<std::pair<time_t, time_t>> &startList, uint16_t &interval) {
	startList.clear();
	int index = 0;
	while (startAll + interval * index++ < endAll) {
		startList.emplace_back(std::make_pair(startAll + interval * (index - 1), startAll + interval * index < endAll ? startAll + interval * index : endAll));
	}
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
	auto path = "./log.txt";
	spdlog::set_pattern("[%H:%M:%S %z] [source %s] [line %#] [thread %t] %v");
	m_logger = spdlog::daily_logger_mt(" ", path, 0, 0);
	m_logger->set_level(static_cast<spdlog::level::level_enum>(m_logLevel));
	spdlog::flush_every(std::chrono::seconds(1));
	if (ReadTag() < 0)
	{
		return -1;
	}
	int index = 0;
	while (m_start + TimeInterval_ * index++ < m_end) {
		m_timeList.emplace_back(std::make_pair(m_start + TimeInterval_ * (index - 1), m_start + TimeInterval_ * index < m_end ? m_start + TimeInterval_ * index : m_end));
	}
	LOGDEBUG("m_timeList.size() = {}", m_timeList.size());
	try
	{
		if (m_dbApiGt.Connect(m_dbInfoGt) < 0)
		{
			LOGINFO("connect gt rtdb error");
			std::cout << "connect rtdb error" << std::endl;
			return -1;
		}
		int ret = m_dbApiGt.GetTagIDByTagName(m_wtagList, m_tagID);
		LOGINFO("get tagid ret = {}", ret);
		if (ret < 0)
		{
			return -1;
		}
		std::thread thrSend(&CollectMonitor::GetValue, this);
		thrSend.detach();
	}
	catch (const std::exception&e)
	{
		LOGINFO("exception = {}", e.what());
		std::cout << "exception = " << e.what() << std::endl;
		return -1;
	}
	return 0;
}

int CollectMonitor::Run()
{
	int ret = 0;
	std::vector<TAGID> tagIDList;
	std::vector<TagData> tagDataList;
	std::vector<int32_t> resultList;
	int playIndex = 0;
	while (true)
	{
		if (playIndex >= m_timeList.size())
		{
			playIndex = 0;
		}
		if (m_tagDatas.size() <= playIndex)
		{
			LOGDEBUG("wait getValue!");
			std::this_thread::sleep_for(std::chrono::seconds(10));
			continue;
		}
		if (!m_dbApiGt.Connected())
		{
			LOGINFO("jt Rtdb Disconnect!");
			if (m_dbApiGt.Connect(m_dbInfoGt) < 0)
			{
				LOGINFO("jt Rtdb reconnect fail!");
				std::this_thread::sleep_for(std::chrono::seconds(30));
				continue;
			}
		}
		time_t t = time(NULL);
		FILETIME timeNow;
		Time_tToFileTime(t, &timeNow);
		TagData tagData;
		tagData.status = 1;
		tagData.timestamp = timeNow;
		LOGDEBUG("wait getValue!");
		For(TimeInterval_)
		{
			tagDataList.clear();
			auto tagNum = m_tagIDs[playIndex].size();
			for(int i = 0; i < tagNum ; i++)
			{
				tagDataList.push_back((*m_tagDatas[playIndex])[i][index]);
			}
			m_mutex.lock();
			ret = m_dbApiGt.SetValueByTagIDNoTime(m_tagIDs[playIndex], tagDataList, resultList);
			m_mutex.unlock();
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
		playIndex++;
	}

	return 0;
}

int CollectMonitor::GetValue()
{
	int ret = 0;

	for (auto &timePiece : m_timeList)
	{
		FILETIME fStart;
		FILETIME fEnd;
		Time_tToFileTime(timePiece.first, &fStart);
		Time_tToFileTime(timePiece.second, &fEnd);
		clock_t clo = clock();
		std::vector<std::vector<TagData>>* pieceData = new std::vector<std::vector<TagData>>();
		std::vector<TAGID> tagIDList;
		for (auto tag : m_tagID)
		{
			std::vector<TagData> tagData;
			clock_t c = clock();
			m_mutex.lock();
			ret = m_dbApiGt.GetValueByPeriod(tag, fStart, fEnd, 1000, tagData);
			m_mutex.unlock();
			if (!tagData.empty())
			{
				pieceData->emplace_back(std::move(tagData));
				tagIDList.emplace_back(tag);
			}
			LOGDEBUG("tagid = {} , ret = {} , size = {} , use = {}", tag.tagID, ret, tagData.size(), clock() - c);
		}
		m_tagDatas.push_back(pieceData);
		m_tagIDs.push_back(tagIDList);
	}
	return 0;
}

int CollectMonitor::ReadCfg()
{
	std::ifstream file("./config.ini");
	if (!file)
	{
		WritePrivateProfileString("Config", "RtdbAddr", "168.168.10.91", "./config.ini");
		WritePrivateProfileString("Config", "start", "1640830232", "./config.ini");
		WritePrivateProfileString("Config", "end", "1640830233", "./config.ini");
		WritePrivateProfileString("Config", "level", "1", "./config.ini");
	}
	char* lpPath = new char[MAX_PATH];
	char* RtdbAddr = new char[100];
	char* start = new char[100];
	char* end = new char[100];
	char* level = new char[100];
	strcpy_s(lpPath, MAX_PATH, "./config.ini");
	GetPrivateProfileString("Config", "RtdbAddr", "", RtdbAddr, 100, lpPath);
	GetPrivateProfileString("Config", "start", "", start, 100, lpPath);
	GetPrivateProfileString("Config", "end", "", end, 100, lpPath);
	GetPrivateProfileString("Config", "level", "", level, 100, lpPath);
	delete[] lpPath;
	m_dbInfoGt.addr = StringToWstring(RtdbAddr);
	m_dbInfoGt.port = 7000;
	m_start = std::atoi(start);
	m_end = std::atoi(end);
	m_logLevel = std::atoi(level);
	delete[] RtdbAddr;
	delete[] start;
	delete[] end;
	delete[] level;
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
	while (std::getline(ifs, lineStr))
	{
		m_wtagList.emplace_back(StringToWstring("db101." + lineStr));
	}
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

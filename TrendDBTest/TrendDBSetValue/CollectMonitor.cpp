
#include "CollectMonitor.h"
#include <fstream>
#include "minidump.h"

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

std::string DatetimeToString(time_t time)
{
	tm *tm_ = localtime(&time);                // 将time_t格式转换为tm结构体
	if (tm_ == nullptr)
	{
		return "0/0/0 0:0:0";
	}
	int year, month, day, hour, minute, second;// 定义时间的各个int临时变量。
	year = tm_->tm_year + 1900;                // 临时变量，年，由于tm结构体存储的是从1900年开始的时间，所以临时变量int为tm_year加上1900。
	month = tm_->tm_mon + 1;                   // 临时变量，月，由于tm结构体的月份存储范围为0-11，所以临时变量int为tm_mon加上1。
	day = tm_->tm_mday;                        // 临时变量，日。
	hour = tm_->tm_hour;                       // 临时变量，时。
	minute = tm_->tm_min;                      // 临时变量，分。
	second = tm_->tm_sec;                      // 临时变量，秒。
	char yearStr[5], monthStr[3], dayStr[3], hourStr[3], minuteStr[3], secondStr[3];// 定义时间的各个char*变量。
	sprintf(yearStr, "%d", year);              // 年。
	sprintf(monthStr, "%d", month);            // 月。
	sprintf(dayStr, "%d", day);                // 日。
	sprintf(hourStr, "%d", hour);              // 时。
	sprintf(minuteStr, "%d", minute);          // 分。
	if (minuteStr[1] == '\0')                  // 如果分为一位，如5，则需要转换字符串为两位，如05。
	{
		minuteStr[2] = '\0';
		minuteStr[1] = minuteStr[0];
		minuteStr[0] = '0';
	}
	sprintf(secondStr, "%d", second);          // 秒。
	if (secondStr[1] == '\0')                  // 如果秒为一位，如5，则需要转换字符串为两位，如05。
	{
		secondStr[2] = '\0';
		secondStr[1] = secondStr[0];
		secondStr[0] = '0';
	}
	if (monthStr[1] == '\0')                  // 如果秒为一位，如5，则需要转换字符串为两位，如05。
	{
		monthStr[2] = '\0';
		monthStr[1] = monthStr[0];
		monthStr[0] = '0';
	}
	if (dayStr[1] == '\0')                  // 如果秒为一位，如5，则需要转换字符串为两位，如05。
	{
		dayStr[2] = '\0';
		dayStr[1] = dayStr[0];
		dayStr[0] = '0';
	}
	if (hourStr[1] == '\0')                  // 如果秒为一位，如5，则需要转换字符串为两位，如05。
	{
		hourStr[2] = '\0';
		hourStr[1] = hourStr[0];
		hourStr[0] = '0';
	}
	char s[20];                                // 定义总日期时间char*变量。
	sprintf(s, "%s-%s-%s %s:%s:%s", yearStr, monthStr, dayStr, hourStr, minuteStr, secondStr);// 将年月日时分秒合并。
	std::string str(s);                             // 定义string变量，并将总日期时间char*变量作为构造函数的参数传入。
	return str + ".000";                                // 返回转换日期时间后的string变量。
}

int CollectMonitor::Init()
{
	Minidump::startMonitering("");
	auto path = "./log.txt";
	spdlog::set_pattern("[%H:%M:%S %z] [source %s] [line %#] [thread %t] %v");
	m_logger = spdlog::daily_logger_mt(" ", path, 0, 0);
	m_logger->set_level(static_cast<spdlog::level::level_enum>(1));
	spdlog::flush_every(std::chrono::seconds(1));
	ReadTag();
	tagID_.dbID = 103;
	tagID_.tagID = 8;
	startTime_ = time(NULL) - 3600*29;
	endTime_ = time(NULL) + 3600*15;
	m_dbInfoGt.addr = L"192.168.1.227";
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
	FILETIME fStart;
	FILETIME fEnd;
	Time_tToFileTime(startTime_, &fStart);
	Time_tToFileTime(endTime_, &fEnd);
	std::ofstream ofs("./data.txt", std::ios::trunc);
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
		std::vector<TagData> tagDataList;
		int ret = m_dbApiGt.GetValueByPeriod(tagID_, fStart, fEnd, 3600*1000,tagDataList);
		for (auto data : tagDataList)
		{
			time_t tTemp;
			FileTimeToTime_t(data.timestamp, &tTemp);
			ofs << DatetimeToString(tTemp) << "\t" << data.value << std::endl;
		}
		Sleep(1000);
	}

	return 0;
}

int CollectMonitor::ReadCfg()
{
	std::ifstream file("./config.ini");
	if (!file)
	{
		WritePrivateProfileString("Config", "RtdbAddrGt", "127.0.0.1", "./config.ini");
	}
	char* lpPath = new char[MAX_PATH];
	char* RtdbAddr = new char[100];
	strcpy_s(lpPath, MAX_PATH, "./config.ini");
	GetPrivateProfileString("Config", "RtdbAddr", "", RtdbAddr, 100, lpPath);
	delete[] lpPath;
	m_dbInfoGt.addr = StringToWstring(RtdbAddr);
	m_dbInfoGt.port = 7000;
	delete[] RtdbAddr;
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
	TAGID tag;
	tag.dbID = 101;
	while (std::getline(ifs, lineStr))
	{
		//tagID_ = 
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

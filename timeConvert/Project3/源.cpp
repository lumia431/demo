#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include <regex>
#include<Windows.h>
#include<time.h>
#include<string>
using namespace std;

inline void Time_tToFileTime(time_t t, FILETIME *ft)
{
	LONGLONG ll = Int32x32To64(t, 10000000) + 116444736000000000;
	ft->dwLowDateTime = (DWORD)ll;
	ft->dwHighDateTime = (DWORD)(ll >> 32);
}


time_t TimeConvert1(std::string timeStr)
{
	std::string pattern1 = "^([1-9]|[0-2][0-9]|3[0-1])/(0[1-9]|[1-9]|1[0-2])/(20[0-9][0-9]) +([0-1][0-9]|2[0-3]):([0-5][0-9]):([0-5][0-9])";// 
	std::regex express(pattern1, std::regex::icase);
	auto els_begin = std::sregex_iterator(timeStr.cbegin(), timeStr.cend(), express);

	auto els_end = std::sregex_iterator();
	if (els_begin == els_end)
	{
		return -1;
	}

	int day = std::atoi((*els_begin)[1].str().c_str());
	int month = std::atoi((*els_begin)[2].str().c_str());
	int year = std::atoi((*els_begin)[3].str().c_str());
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

time_t StrToTime(const std::string& str) 
{
	char* ptr = (char*)str.c_str();
	tm tmTemp;
	int year, month, day, hour, minute, second = 0;
	auto ret = sscanf_s(ptr, "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);
	tmTemp.tm_year = year - 1900;
	tmTemp.tm_mon = month - 1;
	tmTemp.tm_mday = day;
	tmTemp.tm_hour = hour;
	tmTemp.tm_min = minute;
	tmTemp.tm_sec = second;
	tmTemp.tm_isdst = 0;
	time_t tTemp = mktime(&tmTemp);
	return tTemp;
}
int StrToTime(const std::string& str, FILETIME& time) {
	auto timestamp = StrToTime(str);
	std::cout << timestamp << std::endl;
	timestamp -= 8 * 3600;
	tm temtm;
	localtime_s(&temtm, &timestamp);
	SYSTEMTIME timeSys = { 1900 + temtm.tm_year,temtm.tm_mon + 1,temtm.tm_mday,temtm.tm_hour,temtm.tm_min,temtm.tm_sec,0 };
	SystemTimeToFileTime(&timeSys, &time);
	return 0;
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
string DatetimeToString(time_t time)
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

void FormatTime(time_t time1, char* szTime)
{
	struct tm tm1;

#ifdef WIN32
	tm1 = *localtime(&time1);
#else
	localtime_r(&time1, &tm1);
#endif
	sprintf(szTime, "%4.4d/%2.2d/%2.2d/ %2.2d:%2.2d:%2.2d",
		tm1.tm_year + 1900, tm1.tm_mon + 1, tm1.tm_mday,
		tm1.tm_hour, tm1.tm_min, tm1.tm_sec);
}

int main() {
	//std::string start = "2020-16-28 12:00:00";
	//std::string end = "2020-16-28 15:00:00";
	//std::int64_t period = 1000;
	//FILETIME startTime;
	//FILETIME endTime;
	//StrToTime(start, startTime);
	//StrToTime(end, endTime);
	////string strDateStr;
	//time_t now = 1593401129;
	//FileTimeToTime_t(startTime, &now);
	//FILETIME ft;
	//ft.dwHighDateTime = 30887314;
	//ft.dwLowDateTime = 933215465;
	//FileTimeToTime_t(ft, &now);auto s
	//auto str = DatetimeToString(now);
	//string a = "01/14/2020 00:04:11";
	//auto b = TimeConvert1(a);
	//FILETIME f;
	//Time_tToFileTime(b, &f);
	time_t c = time(NULL);
	char tmp[22];
	FormatTime(c, tmp);
	//FileTimeToTime_t(f, &c);
	//auto d = DatetimeToString(c);
	return 0;
}
#ifndef _TOOLS_H_
#define _TOOLS_H_
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif 

//#ifdef TOOLS_EXPORTS
//#define TOOLS_EXPORTS __declspec(dllexport)
//#else 
//#define  TOOLS_EXPORTS __declspec(dllimport)
//#endif // LED_EXPORTS

#include <fstream>
#include <vector>
#include <string>
#include <time.h>
#include <windows.h>
namespace Tools
{
	inline time_t StrToTime(const std::string& str)
	{
		char* ptr = (char*)str.c_str();
		tm tmTemp;
		int year, month, day, hour, minute, second = 0;
		auto ret = sscanf_s(ptr, "%d/%d/%d %d:%d:%d", &month, &day, &year, &hour, &minute, &second);
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

	inline void Time_tToFileTime(time_t t, FILETIME *ft)
	{
		LONGLONG ll = Int32x32To64(t, 10000000) + 116444736000000000;
		ft->dwLowDateTime = (DWORD)ll;
		ft->dwHighDateTime = (DWORD)(ll >> 32);
	}

	inline void  FileTimeToTime_t(FILETIME  ft, time_t* t)
	{
		LONGLONG  ll;
		ULARGE_INTEGER ui;
		ui.LowPart = ft.dwLowDateTime;
		ui.HighPart = ft.dwHighDateTime;
		//ll = ft.dwHighDateTime << 32 + ft.dwLowDateTime;  //这一步是不是多余的
		*t = ((LONGLONG)(ui.QuadPart - 116444736000000000) / 10000000);
		//将ui.QuadPart的数据类型ULONGLONG强制转换为time_t的LONGLONG数据类型
	}

	inline std::string Time_tToString(time_t time)
	{
		tm *tm_ = localtime(&time);                // 将time_t格式转换为tm结构体
		if (tm_ == nullptr)
		{
			return "0";
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
		sprintf(s, "%s/%s/%s %s:%s:%s", dayStr, monthStr, yearStr, hourStr, minuteStr, secondStr);// 将年月日时分秒合并。
		std::string str(s);                             // 定义string变量，并将总日期时间char*变量作为构造函数的参数传入。
		return str;                                // 返回转换日期时间后的string变量。
	}

	inline void SplitString(const std::string& s, std::vector<std::string> &v, const std::string& c)
	{
		std::string::size_type pos1, pos2;
		pos2 = s.find(c);
		pos1 = 0;

		while (std::string::npos != pos2)
		{
			auto it = v.end();
			v.push_back(s.substr(pos1, pos2 - pos1));

			pos1 = pos2 + c.size();
			pos2 = s.find(c, pos1);
		}
		if (pos1 != s.length())
			v.push_back(s.substr(pos1));
	}
	template<typename T>
	inline void GetFiles(const std::string&filePath, T &fileNames)
	{

		std::string pointstr = "dir " + filePath + " /B > ./fname.txt";
		//const char *a =("dir %s /B > D:\\fname.txt", pointstr.c_str());
		system(pointstr.c_str());
		std::ifstream fReadFName("./fname.txt");
		std::string tName;
		while (getline(fReadFName, tName))
		{
			auto it = fileNames.end();
			fileNames.insert(it, tName);
		}
	}
	//LOADOMETER_API double GetWeight(int &id, int &orgNo);
};
#endif
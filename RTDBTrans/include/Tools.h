#ifndef _TOOLS_H_
#define _TOOLS_H_
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif 
#pragma warning( disable : 4566 4819 )
//#ifdef TOOLS_EXPORTS
//#define TOOLS_EXPORTS __declspec(dllexport)
//#else 
//#define  TOOLS_EXPORTS __declspec(dllimport)
//#endif // LED_EXPORTS

#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
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
	inline void FileTimeToTime_t(FILETIME  ft, time_t* t)
	{
		ULARGE_INTEGER ui;
		ui.LowPart = ft.dwLowDateTime;
		ui.HighPart = ft.dwHighDateTime;
		//ll = ft.dwHighDateTime << 32 + ft.dwLowDateTime;  //这一步是不是多余的
		*t = ((LONGLONG)(ui.QuadPart - 116444736000000000) / 10000000);
		//将ui.QuadPart的数据类型ULONGLONG强制转换为time_t的LONGLONG数据类型
	}
	void inline CheckOut(const char * sourceBuff, const int & sourceLen, const std::string & headBuff)
	{
		std::ofstream ofile;
		ofile.open(headBuff, std::ios::app);

		ofile << "Recv : ";

		int a = 0;

		for (int i = 0; i < sourceLen; ++i)
		{
			a = sourceBuff[i];
			a = a & 0XFF;

			ofile << std::setfill('0') << std::setw(2) << std::hex << a << " ";
		}

		ofile << std::endl;

		ofile.close();
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
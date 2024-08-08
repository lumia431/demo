#include "Tools.h"
template<typename T>
time_t Tools<T>::StrToTime(const std::string& str)
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
template<typename T>
void Tools<T>::Time_tToFileTime(time_t t, FILETIME *ft)
{
	LONGLONG ll = Int32x32To64(t, 10000000) + 116444736000000000;
	ft->dwLowDateTime = (DWORD)ll;
	ft->dwHighDateTime = (DWORD)(ll >> 32);
}

template<typename T>
void Tools<T>::SplitString(const std::string& s, T &v, const std::string& c)
{
	std::string::size_type pos1, pos2;
	pos2 = s.find(c);
	pos1 = 0;

	while (std::string::npos != pos2)
	{
		auto it = v.end();
		v.insert(it, s.substr(pos1, pos2 - pos1));

		pos1 = pos2 + c.size();
		pos2 = s.find(c, pos1);
	}
	if (pos1 != s.length())
		v.insert(v.end(), s.substr(pos1));
}

template<typename T>
void Tools<T>::GetFiles(const std::string&filePath, T &fileNames)
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



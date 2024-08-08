#include<boost/filesystem.hpp>
#include <boost/filesystem/operations.hpp>
#include <fstream>
#include <sstream>
#include "SdkHGY.h"
#include <regex>
int SdkHGY::Init(SetValueInfo info_)
{
	m_info = info_;
	m_logger = info_.my_logger_;
	auto path = boost::filesystem::current_path().string();
	LOGDEBUG("read over ,fileName = {}", path);
	Tools::GetFiles(m_info.filePath_, m_fileLists);
	if (m_fileLists.empty())
	{
		return FILEEMPTY;
	}
	return 0;
}

int SdkHGY::GetData(std::map<std::string, std::vector<TagData>>& Datas)
{
	int fileIndex = 0;
	int lineIndex = 0;
	int pointIndex = 0;
	funcList.push_back(&SdkHGY::TimeConvert1);
	funcList.push_back(&SdkHGY::TimeConvert2);
	funcList.push_back(&SdkHGY::TimeConvert3);
	funcList.push_back(&SdkHGY::TimeConvert4);
	TagData tag;
	tag.status = 1;
	std::string data_;
	FILETIME ft;
	std::vector <std::string> linedata;
	std::vector<std::string>tagNames;
	for (auto &fileList : m_fileLists)
	{
		int regexType = -1;
		std::string filepath = m_info.filePath_ + "\\" + fileList;
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
			if (regexType < 0)
			{
				for (int i = 0; i < 4; ++i)
				{
					if ((this->*funcList[i])(linedata.front()) > 0)
					{
						regexType = i;
						break;
					}
				}
			}
			if (regexType < 0)
			{
				LOGINFO("time pattern error!,fileName = {}", fileList);
				linedata.clear();
				break;
			}
			Tools::Time_tToFileTime((this->*funcList[regexType])(linedata.front()), &ft);
			tag.timestamp = ft;
			for (auto it = (++linedata.begin()); it != linedata.end(); ++it)
			{
				if (it->size() < 1)
				{
					pointIndex++;
					continue;
				}
				tag.value = (atof(it->c_str()));
				Datas[tagNames[pointIndex]].push_back(tag);
				pointIndex++;
			}
			linedata.clear();
			lineIndex++;
		}
		tagNames.clear();
		LOGDEBUG("read over ,fileName = {}", fileList);
		istrm.close();
		/*remove(filepath.c_str());*/
		lineIndex = 0;
		fileIndex++;
	}
	if (!Datas.empty())
	{
		return Datas.size();
	}
	return UNPACKERROR;
}

int SdkHGY::GetTagNames(std::set<std::string>&tagNames)
{

	std::string data_;
	std::vector<std::string>tagName;
	int fileIndex = 0;
	for (auto &fileList : m_fileLists)
	{
		int index = 0;
		std::string filepath(m_info.filePath_ + "\\" + fileList);
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
	return 0;
}

void SdkHGY::SplitTagName(const std::string & s, std::vector<std::string>& v, const std::string & c)
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
time_t inline SdkHGY::TimeConvert1(std::string timeStr)
{
	std::string pattern0 = "^(20[0-9][0-9])/(0[1-9]|[1-9]|1[0-2])/([0-9]|[0-2][0-9]|3[0-1]) +([0-1][0-9]|2[0-3]):([0-5][0-9]):([0-5][0-9])";
	std::regex express(pattern0, std::regex::icase);
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
time_t inline SdkHGY::TimeConvert2(std::string timeStr)
{
	std::string pattern1 = "^(0[1-9]|[1-9]|1[0-2])/([1-9]|[0-2][0-9]|3[0-1])/(20[0-9][0-9]) +([0-1][0-9]|2[0-3]):([0-5][0-9]):([0-5][0-9])";// 
	std::regex express(pattern1, std::regex::icase);
	auto els_begin = std::sregex_iterator(timeStr.cbegin(), timeStr.cend(), express);

	auto els_end = std::sregex_iterator();
	if (els_begin == els_end)
	{
		return -1;
	}

	int month = std::atoi((*els_begin)[1].str().c_str());
	int day = std::atoi((*els_begin)[2].str().c_str());
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
time_t inline SdkHGY::TimeConvert3(std::string timeStr)
{
	std::string pattern2 = "^(0[1-9]|[1-9]|1[0-2])-([1-9]|[0-2][0-9]|3[0-1])-(20[0-9][0-9]) +([0-1][0-9]|2[0-3]):([0-5][0-9]):([0-5][0-9])";
	std::regex express(pattern2, std::regex::icase);
	auto els_begin = std::sregex_iterator(timeStr.cbegin(), timeStr.cend(), express);

	auto els_end = std::sregex_iterator();
	if (els_begin == els_end)
	{
		return -1;
	}

	int month = std::atoi((*els_begin)[1].str().c_str());
	int day = std::atoi((*els_begin)[2].str().c_str());
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
time_t inline SdkHGY::TimeConvert4(std::string timeStr)
{
	std::string pattern3 = "^(20[0-9][0-9])-(0[1-9]|[1-9]|1[0-2])-([1-9]|[0-2][0-9]|3[0-1]) +([0-1][0-9]|2[0-3]):([0-5][0-9]):([0-5][0-9])";

	std::regex express(pattern3, std::regex::icase);
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

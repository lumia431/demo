
#include <fstream>
#include <sstream>
#include "SdkLMY.h"

int SdkLMY::Init(SetValueInfo info_)
{
	m_info = info_;
	m_logger = info_.my_logger_;
	Tools::GetFiles(m_info.filePath_, m_fileLists);
	if (m_fileLists.empty())
	{
		return FILEEMPTY;
	}
	return 0;
}

int SdkLMY::GetData(std::map<std::string, std::vector<TagData>>& Datas)
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
			Tools::Time_tToFileTime(Tools::StrToTime(linedata.front()), &ft);
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
		LOGDEBUG("unpack tag numbers = {}", Datas.size());
		return Datas.size();
	}
	return UNPACKERROR;
}

int SdkLMY::GetTagNames(std::set<std::string>&tagNames)
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

void SdkLMY::SplitTagName(const std::string & s, std::vector<std::string>& v, const std::string & c)
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


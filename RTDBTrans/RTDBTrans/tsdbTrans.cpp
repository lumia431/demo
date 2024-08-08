#include "pch.h"
#include "tsdbTrans.h"

trans::TsdbTrans::TsdbTrans(TransInfo & info, std::vector<TagBasicInfo>&tagInfoList)
	:m_info(info), m_logger(info.logger),m_tagInfoList(tagInfoList)
{
}

int trans::TsdbTrans::Connect()
{
	return 0;
}

int trans::TsdbTrans::Send(const std::vector<std::string>& tagNames, const std::vector<TagData>& tagDatalist)
{
	httplib::Client m_cli((m_info.rtdbAddr + ":"+std::to_string(m_info.rtdbPort)).c_str());
	using nlohmann::json;
	try
	{
		int packSize = 50;
		int sendCount = std::ceil((float)tagNames.size() / packSize);

		for (int i = 0; i < sendCount; ++i)
		{

			auto beginValueItr = tagDatalist.begin() + i * packSize;
			auto endValueItr = (i * packSize + packSize) > tagDatalist.size() ? tagDatalist.end() : (tagDatalist.begin() + (i + 1) * packSize);
			auto beginNoItr = tagNames.begin() + i * packSize;
			auto endNoItr = (i * packSize + packSize) > tagNames.size() ? tagNames.end() : (tagNames.begin() + (i + 1) * packSize);
			auto beginNameItr = m_tagInfoList.begin() + i * packSize;
			auto endNameItr = (i * packSize + packSize) > m_tagInfoList.size() ? m_tagInfoList.end() : (m_tagInfoList.begin() + (i + 1) * packSize);
			std::vector<TagData> tempTagValue(beginValueItr, endValueItr);
			std::vector<std::string> tempTagNo(beginNoItr, endNoItr);
			std::vector<TagBasicInfo> tempTagInfo(beginNameItr, endNameItr);
			json j_object = { {} };
			time_t timestamp = time(NULL);
			for (int i = 0; i < tempTagNo.size(); ++i)
			{
				json j_objecttemp = { {"metric", tempTagInfo[i].group},{"timestamp",timestamp },{"value",tempTagValue[i].value } ,{"tags",{{"tagname", tempTagNo[i]}}} };
				j_object.insert(j_object.cend(), j_objecttemp);
			}
			j_object.erase(j_object.begin());
			auto ret = m_cli.Post("/api/put", j_object.dump(), "application/json");
			if (!ret)
			{
				LOGINFO("tsdb send fail");
			}
		}
	}
	catch (std::exception &e)
	{
		LOGINFO("tsdb send fail {}", e.what());
		return -1;
	}
	return 0;
}

int trans::TsdbTrans::Reconnect()
{
	return 0;
}



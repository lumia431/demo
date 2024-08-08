#pragma once
#include "TransSdk.h"
#include "nlohmann/json.hpp"
#include "httplib.h"
namespace trans
{
	class TsdbTrans :virtual public TransSdk
	{
	public:
		TsdbTrans(TransInfo &info, std::vector<TagBasicInfo>&tagInfoList);
		int Connect() override;
		int Send(const std::vector<std::string> &tagNames, const std::vector<TagData>&tagDatalist) override;
		int Reconnect() override;

	private:
		std::vector <TagBasicInfo> m_tagInfoList;
		std::vector<std::string> m_tagNames;
		std::shared_ptr<spdlog::logger> m_logger;
		TransInfo m_info;
	};

}


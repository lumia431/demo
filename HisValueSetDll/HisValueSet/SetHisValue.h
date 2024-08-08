#pragma once
#include "RTDBApi.h"
#include "SdkUnpack.h"
#include <fstream>
class SetHisValue
{
public:
	SetHisValue(SetValueInfo info_);
	~SetHisValue();
	int Run();
	int Init();
	double GetProGress();
	std::atomic_bool pauseStatus = false;
	std::atomic_int tagID_;
	bool finishFlg = false;
	bool cancelFlg = false;
	
private:
	SetValueInfo m_info;
	std::wstring m_dbName;
	std::wstring m_groupName;
	std::shared_ptr<SdkUnpack>m_unpack;
	int SetValue();
	boost::dll::shared_library dllPtr_;
	std::wstring StringToWstring(const std::string str);
	std::map<std::string, std::vector<TagData>>m_Datas;
	std::set<std::string>m_tagNames;
	RTDB::ApiCpp::GlobalDBApi m_dbApi;
	ConnectInfo m_dbInfo;	
	std::atomic_int progress_ = 0;
	std::thread thr_;
	std::shared_ptr<spdlog::logger>m_logger;
	auto GetMylog()
	{
		return m_logger;
	}
};






#pragma once
#include "RTDBApi.h"
#include "HisDateUnpack.h"
#include <queue>
#include <unordered_map>
#include <fstream>
#include<boost/filesystem.hpp>
#include <boost/filesystem/operations.hpp>
class SetHisValue
{
public:
	SetHisValue(SetValueInfo info_);
	~SetHisValue();
	int Run();
	int Init();
	auto GetMylog()
	{
		return my_logger_;
	}
	double GetProGress();
	std::atomic_bool pauseStatus = false;
	std::string tagName_ = "luculent";
	bool finishFlg = false;
	bool cancelFlg = false;
	std::atomic_bool disConnectFlg = false;
private:
	SetValueInfo m_info;
	std::wstring m_dbName;
	std::wstring m_groupName;
	std::atomic_bool m_readOverFlg = false;
	int Set();
	int SetValue(std::unordered_map<std::string, std::vector<TagData>> &dataMap);
	int GetData();
	int GetTagNames(std::set<std::string>&tagNames);
	void SplitTagName(const std::string & s, std::vector<std::string>& v, const std::string & c);
	void GetDirects(std::string &path);
	const std::vector<std::string>& scanFilesUseRecursive(const std::string& rootPath, std::vector<std::string>& container = *(new std::vector<std::string>()));
	time_t TimeConvert1(std::string timeStr);
	std::wstring StringToWstring(const std::string str);
	void GetFiles(std::string path, std::vector<std::string> &fileList);
	std::queue<std::pair<std::string, TagData>> m_Datas;
	std::set<std::string>m_tagNames;
	RTDB::ApiCpp::GlobalDBApi m_dbApi;
	ConnectInfo m_dbInfo;	
	std::atomic_int m_progress = 0;
	std::atomic_int m_totalProgress = 0;
	std::thread m_getThr;
	std::thread m_setThr;
	std::shared_ptr<spdlog::logger> my_logger_;
	std::vector<std::string>m_fileLists;
	std::mutex m_mutex;
	std::condition_variable m_msgQueue;
	std::string m_failDirec;
};






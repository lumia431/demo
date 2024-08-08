#pragma once
#define LOGDEBUG(...) SPDLOG_LOGGER_CALL(this->m_logger,spdlog::level::level_enum::debug,__VA_ARGS__);
#define LOGINFO(...) SPDLOG_LOGGER_CALL(this->m_logger,spdlog::level::level_enum::info,__VA_ARGS__);
#define LOGWARN(...) SPDLOG_LOGGER_CALL(this->m_logger,spdlog::level::level_enum::warn(),__VA_ARGS__);
#define LOGERR(...) SPDLOG_LOGGER_CALL(this->m_logger,spdlog::level::level_enum::err,__VA_ARGS__);
#define _CRT_SECURE_NO_WARNINGS
#define _SILENCE_CXX17_ALLOCATOR_VOID_DEPRECATION_WARNING
#include "mqtt/async_client.h"
#include "RTDBApi.h"
#include "libpq-fe.h"
#include "spdlog/spdlog.h"
#include "spdlog/logger.h"
#include <spdlog/sinks/daily_file_sink.h>
struct jsonData
{
	int taskType;
	int statusType;
	time_t timestamp;
};
class CollectMonitor
{
public:
	CollectMonitor() = default;
	~CollectMonitor();
	int Init();
	int Run();
private:
	void CheckTimeThr();
	int UnpackBuffer(std::string &buffer);
	int SendThr();
	std::wstring StringToWstring(const std::string str);
	void Time_tToFileTime(time_t t, FILETIME *ft);
	int ReadCfg();
	int ReadTag();
	std::shared_ptr<spdlog::logger> m_logger;
	std::string m_mqttAddr;
	PGconn *m_conn;
	std::string m_pgIp;
	std::string m_pgDbName;
	std::string m_pgUser;
	std::string m_pgPwd;
	std::string m_pgPort;
	RTDB::ApiCpp::GlobalDBApi m_dbApiGt;
	RTDB::ApiCpp::GlobalDBApi m_dbApiJt;
	ConnectInfo m_dbInfoGt;
	ConnectInfo m_dbInfoJt;
	std::string m_url;
	std::string m_urlAddr;
	std::string m_topic;
	std::map <std::string, time_t> m_pgTimeOut;
	std::map <std::string, time_t> m_rtdbTimeOut;
	int timeOut_ = 1800;
	std::map<std::string,jsonData> m_bufferMap;
	std::map<std::string,int> m_alarmCounts;
	std::mutex m_dataMutex;
	std::mutex m_pgMutex;
	std::mutex m_rtdbMutex;
	std::mutex m_bufferMutex;
	std::vector<std::string> m_taskList;
	std::map<std::string, std::wstring> m_queryTags;
	std::vector<std::wstring> m_tagNameList;
	std::vector<TagData> m_tagDataList;
	std::map<std::string, float> m_tagData;
	bool m_gtEnable = true;
	std::string m_prefix;
	int m_logLevel;
	int m_interval;
};


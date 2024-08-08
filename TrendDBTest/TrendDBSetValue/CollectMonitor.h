#pragma once
#define LOGDEBUG(...) SPDLOG_LOGGER_CALL(this->m_logger,spdlog::level::level_enum::debug,__VA_ARGS__);
#define LOGINFO(...) SPDLOG_LOGGER_CALL(this->m_logger,spdlog::level::level_enum::info,__VA_ARGS__);
#define LOGWARN(...) SPDLOG_LOGGER_CALL(this->m_logger,spdlog::level::level_enum::warn(),__VA_ARGS__);
#define LOGERR(...) SPDLOG_LOGGER_CALL(this->m_logger,spdlog::level::level_enum::err,__VA_ARGS__);
#define _CRT_SECURE_NO_WARNINGS
#include "TrendDB/RTDBApi.h"
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
	std::wstring StringToWstring(const std::string str);
	void Time_tToFileTime(time_t t, FILETIME *ft);
	int ReadCfg();
	int ReadTag();
	std::shared_ptr<spdlog::logger> m_logger;
	RTDB::ApiCpp::GlobalDBApi m_dbApiGt;
	ConnectInfo m_dbInfoGt;
	TAGID tagID_;
	time_t startTime_;
	time_t endTime_;
};


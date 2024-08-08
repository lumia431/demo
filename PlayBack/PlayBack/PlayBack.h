#pragma once
#define LOGDEBUG(...) SPDLOG_LOGGER_CALL(this->m_logger,spdlog::level::level_enum::debug,__VA_ARGS__);
#define LOGINFO(...) SPDLOG_LOGGER_CALL(this->m_logger,spdlog::level::level_enum::info,__VA_ARGS__);
#define LOGWARN(...) SPDLOG_LOGGER_CALL(this->m_logger,spdlog::level::level_enum::warn(),__VA_ARGS__);
#define LOGERR(...) SPDLOG_LOGGER_CALL(this->m_logger,spdlog::level::level_enum::err,__VA_ARGS__);
#define For(n) for(int index = 0;index < n;++index)
#define _CRT_SECURE_NO_WARNINGS
#include "RTDBApi.h"
#include "spdlog/spdlog.h"
#include "spdlog/logger.h"
#include <spdlog/sinks/daily_file_sink.h>
#include <thread>
#include <mutex>
#include <map>
class CollectMonitor
{
public:
	CollectMonitor() = default;
	~CollectMonitor();
	int Init();
	int Run();
private:
	int GetValue();
	std::wstring StringToWstring(const std::string str);
	void Time_tToFileTime(time_t t, FILETIME *ft);
	int ReadCfg();
	int ReadTag();
	std::shared_ptr<spdlog::logger> m_logger;
	RTDB::ApiCpp::GlobalDBApi m_dbApiGt;
	ConnectInfo m_dbInfoGt;
	std::vector<std::wstring> m_wtagList;
	std::vector<TAGID> m_tagID;
	std::vector<std::vector<std::vector<TagData>>*> m_tagDatas;
	std::vector<std::vector<TAGID>> m_tagIDs;
	std::vector<std::pair<time_t, time_t>> m_timeList;
	std::mutex m_mutex;
	int m_logLevel;
	int m_pieceNums;
	time_t m_start;
	time_t m_end;
	const uint16_t TimeInterval_ = 10800;
};


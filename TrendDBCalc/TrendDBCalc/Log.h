#pragma once
#define LOGDEBUG(...) SPDLOG_LOGGER_CALL(this->m_logger,spdlog::level::level_enum::debug,__VA_ARGS__);
#define LOGINFO(...) SPDLOG_LOGGER_CALL(this->m_logger,spdlog::level::level_enum::info,__VA_ARGS__);
#define LOGWARN(...) SPDLOG_LOGGER_CALL(this->m_logger,spdlog::level::level_enum::warn(),__VA_ARGS__);
#define LOGERR(...) SPDLOG_LOGGER_CALL(this->m_logger,spdlog::level::level_enum::err,__VA_ARGS__);
#pragma warning( disable : 4099)
#define For(n) for(int index=0;index<n;++index)
#include "spdlog/spdlog.h"
#include "spdlog/logger.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/async.h"

enum 
{
	CONNECTERROR = -1,
	PACKERROR = -2,
	INITERROR =-3
};

enum class Status
{
	EMPTY,
	DBCHOOSE,
	GROUPCHOOSE
};

struct MyInfo
{
	std::wstring addr = L"127.0.0.1";
	uint16_t port = 7000;
	std::shared_ptr<spdlog::logger>logger;
};

struct TabInfo
{
	Status status = Status::EMPTY;
	QString dbName;
	QString groupName;
	TabInfo(Status &s,QString &db,QString group = QString("")):
		status(s),dbName(db),groupName(group)
	{}
};
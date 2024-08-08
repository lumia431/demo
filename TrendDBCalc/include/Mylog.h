#pragma once
#define LOGDEBUG(...) SPDLOG_LOGGER_CALL(my_logger,spdlog::level::level_enum::debug,__VA_ARGS__);
#define LOGINFO(...) SPDLOG_LOGGER_CALL(my_logger,spdlog::level::level_enum::info,__VA_ARGS__);
#define LOGWARN(...) SPDLOG_LOGGER_CALL(my_logger,spdlog::level::level_enum::warn(),__VA_ARGS__);
#define LOGERR(...) SPDLOG_LOGGER_CALL(my_logger,spdlog::level::level_enum::err,__VA_ARGS__);
#include<string>
#include<vector>
#include <map>
#include "spdlog/spdlog.h"
#include "spdlog/logger.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/async.h"
static std::shared_ptr<spdlog::logger>my_logger;
static void SetLevel(std::string logName, int logLevel)
{
	using namespace spdlog::level;
	spdlog::set_pattern("%Y-%m-%d %H:%M:%S - [thread %t][%^%l%$][%s][%#]|,%v");
	my_logger = spdlog::basic_logger_mt(logName, "./log.txt");
	my_logger->set_level(static_cast<spdlog::level::level_enum>(logLevel));
	spdlog::flush_every(std::chrono::seconds(3));
}





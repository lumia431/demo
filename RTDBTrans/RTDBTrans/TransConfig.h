#pragma once
#define LOGDEBUG(...) SPDLOG_LOGGER_CALL(this->m_logger,spdlog::level::level_enum::debug,__VA_ARGS__);
#define LOGINFO(...) SPDLOG_LOGGER_CALL(this->m_logger,spdlog::level::level_enum::info,__VA_ARGS__);
#define LOGWARN(...) SPDLOG_LOGGER_CALL(this->m_logger,spdlog::level::level_enum::warn(),__VA_ARGS__);
#define LOGERR(...) SPDLOG_LOGGER_CALL(this->m_logger,spdlog::level::level_enum::err,__VA_ARGS__);
#include <string>
#include <map>
#include "spdlog/spdlog.h"
#include "spdlog/logger.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/async.h"
namespace trans
{
	enum
	{
		RTDBCONNECTERROR = -1,
		GETVALUEERROR = -2,
		POINTEMPTY = -3,
		TRANSEMPTY = -4,
		GETINFOERROR = -5,
		INTERVALERROR
	};
	enum SdkType 
	{
		UA =0,
		TSDB,
		MQTT,
		KAFKA
	};
	struct TransInfo
	{
		std::string rtdbAddr;
		uint16_t rtdbPort;
		std::string tsdbAddr;
		std::string mqttAddr;
		std::string kafkaAddr;
		uint16_t tsdbPort;
		uint16_t mqttPort;
		uint16_t kafkaPort;
		uint16_t uaPort;
		uint16_t interval;
		std::string mqttTopic;
		std::string kafkaTopic;
		std::string pointPath;
		time_t nowTime;
		std::shared_ptr<spdlog::logger> logger;
		std::map<std::string, uint16_t> sdkEnable;
	};
}
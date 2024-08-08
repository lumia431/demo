#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/logger.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/async.h"

inline std::map<std::string, std::string>sdkMap_{ {"HGY","SdkHGY"},{"LMY","SdkLMY"} };

enum 
{
	FILEEMPTY = -1,
	OPENERROR = -2,
	UNPACKERROR = -3,
	CONNECTERROR = -4
};

enum SdkIndex
{
	HGY,
	LMY
};

enum MODE
{
	WRITE_VALUE,
	MAKE_FILE
};
struct SetValueInfo
{
	int logLevel_;
	std::string filePath_;
	std::string prefix_;
	std::string dbName_;
	std::string addr_;
	std::string groupName_;
	std::string sdk;
	int port_;
	int interval;
	int totalProgress_ = 1;
	MODE mode;
	std::shared_ptr<spdlog::logger>my_logger_;
};

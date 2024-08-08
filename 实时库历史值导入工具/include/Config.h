#pragma once
#include "spdlog/spdlog.h"
#include "spdlog/logger.h"
#include "spdlog/async.h"
#include "spdlog/sinks//basic_file_sink.h"

enum 
{
	FILEEMPTY = -1,
	OPENERROR = -2,
	UNPACKERROR = -3,
	CONNECTERROR = -4
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
	int port_;
	int interval;
	int readMax;
	MODE mode;
	std::shared_ptr<spdlog::logger> my_logger_;
};

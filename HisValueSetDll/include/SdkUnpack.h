#pragma once
#define LOGDEBUG(...) SPDLOG_LOGGER_CALL(this->GetMylog(),spdlog::level::level_enum::debug,__VA_ARGS__);
#define LOGINFO(...) SPDLOG_LOGGER_CALL(this->GetMylog(),spdlog::level::level_enum::info,__VA_ARGS__);
#define LOGWARN(...) SPDLOG_LOGGER_CALL(this->GetMylog(),spdlog::level::level_enum::warn(),__VA_ARGS__);
#define LOGERR(...) SPDLOG_LOGGER_CALL(this->GetMylog(),spdlog::level::level_enum::err,__VA_ARGS__);
#include "boost/dll.hpp"
#include "boost/dll/shared_library.hpp"
#include "boost/filesystem.hpp"
#include "Tools.h"
#include <set>
#include <vector>
#include <map>
#include "commtypes.h"
#include "Config.h"
class SdkUnpack
{
public:
	virtual ~SdkUnpack()
	{

	}

	virtual int GetData(std::map<std::string, std::vector<TagData>>&Datas) = 0;

	virtual int Init(SetValueInfo info_) = 0;

	virtual int GetTagNames(std::set<std::string>&tagNames) = 0;


};


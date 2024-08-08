#pragma once
#define LOGDEBUG(...) SPDLOG_LOGGER_CALL(this->GetMylog(),spdlog::level::level_enum::debug,__VA_ARGS__);
#define LOGINFO(...) SPDLOG_LOGGER_CALL(this->GetMylog(),spdlog::level::level_enum::info,__VA_ARGS__);
#include "Tools.h"
#include <set>
#include <vector>
#include <map>
#include "commtypes.h"
#include "Config.h"


#pragma once
#include "TransConfig.h"
#include "RTDBApi.h"
namespace trans
{
	class TransSdk
	{
	public:
		TransSdk() = default;
		virtual ~TransSdk();
		virtual int Connect() = 0;
		virtual int Send(const std::vector<std::string> &tagNames, const std::vector<TagData>&tagDatalist) = 0;
		virtual int Reconnect() = 0;
	};
}

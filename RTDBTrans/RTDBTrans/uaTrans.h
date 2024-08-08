#pragma once
#include "TransSdk.h"
#include "opcua_server.h"

namespace trans
{
	class UaTrans:virtual public TransSdk
	{
	public:
		UaTrans(TransInfo &info, std::vector<std::string>&names);
		int Connect() override;
		int Send(const std::vector<std::string> &tagNames, const std::vector<TagData>&tagDatalist) override;
		int Reconnect() override;
		void OPCUArun();

	private:
		std::vector<POINT_VALUE> point;
		OpcuaApi *p = GetOpcua();
		std::shared_ptr<spdlog::logger> m_logger;
		TransInfo m_info;
	};

}


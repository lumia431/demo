#pragma once

#include "mqtt/async_client.h"
#include "TransSdk.h"
namespace trans
{
	class MqttTrans :virtual public TransSdk
	{
	public:
		MqttTrans(TransInfo &info);
		~MqttTrans();
		int Connect() override;
		int Send(const std::vector<std::string> &tagNames, const std::vector<TagData>&tagDatalist) override;
		int Reconnect() override;

	private:
		mqtt::async_client m_cli;
		const std::chrono::seconds TIMEOUT = std::chrono::seconds(10);
		std::shared_ptr<spdlog::logger> m_logger;
		TransInfo m_info;
	};

}


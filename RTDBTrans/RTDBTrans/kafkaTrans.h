#pragma once
#include "TransSdk.h"
#include "kafka/rdkafkacpp.h"
namespace trans
{
	class KafkaTrans :virtual public TransSdk
	{
	public:
		KafkaTrans(TransInfo &info);
		int Connect() override;
		int Send(const std::vector<std::string> &tagNames, const std::vector<TagData>&tagDatalist) override;
		int Reconnect() override;

	private:
		RdKafka::Producer *producer_;
		RdKafka::Topic *topic_;
		int32_t partition_;
		std::shared_ptr<spdlog::logger> m_logger;
		TransInfo m_info;
	};

}


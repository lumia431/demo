#include "pch.h"
#include "nlohmann/json.hpp"
#include "kafkaTrans.h"
#include "Tools.h"
trans::KafkaTrans::KafkaTrans(TransInfo &info):m_info(info),m_logger(info.logger)
{
}

int trans::KafkaTrans::Connect()
{
	std::string errStr = "";
	RdKafka::Conf *conf = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL);
	RdKafka::Conf *tconf = RdKafka::Conf::create(RdKafka::Conf::CONF_TOPIC);
	if (conf->set("bootstrap.servers", m_info.kafkaAddr, errStr) != RdKafka::Conf::CONF_OK)
	{
		LOGINFO("RdKafka conf set brokerlist failed :{}" , errStr.c_str());
		return -1;
	}
	if (conf->set("acks", "1", errStr) != RdKafka::Conf::CONF_OK)
	{
		LOGINFO("RdKafka conf set brokerlist failed :{}", errStr.c_str());
		return -1;
	}
	if (conf->set("retries", "3", errStr) != RdKafka::Conf::CONF_OK)
	{
		LOGINFO("RdKafka conf set brokerlist failed :{}", errStr.c_str());
		return -1;
	}
	if (conf->set("client.id", "gateway", errStr) != RdKafka::Conf::CONF_OK)
	{
		LOGINFO("RdKafka conf set brokerlist failed :{}", errStr.c_str());
		return -1;
	}
	producer_ = RdKafka::Producer::create(conf, errStr);
	if (!producer_)
	{
		LOGINFO("RdKafka conf set brokerlist failed :{}", errStr.c_str());
		return -1;
	}
	topic_ = RdKafka::Topic::create(producer_, m_info.kafkaTopic, tconf, errStr);
	if (!topic_)
	{
		LOGINFO("RdKafka conf set brokerlist failed :{}", errStr.c_str());
		return false;
	}

	return 0;
}

int trans::KafkaTrans::Send(const std::vector<std::string>& tagNames, const std::vector<TagData>& tagDatalist)
{

	nlohmann::json valueList;
	nlohmann::json value;

	time_t timeStamp = time(NULL);
	time_t *timePtr = &timeStamp;
	for (int i = 0; i < tagNames.size(); ++i)
	{

		nlohmann::json temp;
		double b = 0;
		Tools::FileTimeToTime_t(tagDatalist[i].timestamp, timePtr);

		//原始平台兼容json
		temp["N"] = tagNames[i];
		temp["S"] = "1";
		temp["T"] = std::to_string(timeStamp);
		temp["V"] = tagDatalist[i].value;
		value.push_back(temp);
	}
	//原始平台兼容json
	valueList["data"] = value;
	std::string data = valueList.dump();
	RdKafka::ErrorCode resp = producer_->produce(topic_, RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY,
		const_cast<char *>(data.c_str()), data.size(), NULL, NULL);
	if (resp != RdKafka::ERR_NO_ERROR)
	{
		LOGINFO("Produce failed: {}" , RdKafka::err2str(resp));
		return -1;
	}
	//producer_->flush(1000);
	//producer_->poll(0);
	//while (producer_->outq_len() > 0)
	//{
	//	producer_->poll(1000);
	//}
	return 0;
}

int trans::KafkaTrans::Reconnect()
{
	return 0;
}



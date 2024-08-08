#include "pch.h"
#include "mqttTrans.h"
#include "nlohmann/json.hpp"
#include "Tools.h"
trans::MqttTrans::MqttTrans(TransInfo &info):
	m_cli(info.mqttAddr + ":" + std::to_string(info.mqttPort), std::to_string(info.nowTime)),
	m_info(info),
	m_logger(info.logger)
{
}

trans::MqttTrans::~MqttTrans()
{
	mqtt::token_ptr conntok = m_cli.disconnect();
	conntok->wait_for(TIMEOUT);
}

int trans::MqttTrans::Connect()
{
	mqtt::connect_options connOpts;
	connOpts.set_keep_alive_interval(20);
	connOpts.set_clean_session(true);

	try
	{
		mqtt::token_ptr conntok = m_cli.connect(connOpts);
		conntok->wait_for(TIMEOUT);
		LOGDEBUG("Connect MQTT OK!");
	}
	catch (const mqtt::exception& exc)
	{
		/*que.put(mqtt::delivery_token_ptr{});*/
		LOGINFO("mqtt connect fail {}", exc.what());
		return -1;
	}
	return 0;
}

int trans::MqttTrans::Send(const std::vector<std::string>& tagNames, const std::vector<TagData>& tagDatalist)
{
	nlohmann::json valueList;
	nlohmann::json value;

	time_t timeStamp = time(NULL);
	time_t *timePtr = &timeStamp;
	for (int i = 0; i < tagNames.size(); ++i)
	{

		nlohmann::json temp;
		double b = 0;
		/*	Tools::FileTimeToTime_t(tagDatalist[i].timestamp, timePtr);*/

		temp["N"] = tagNames[i];
		temp["S"] = "1";
		temp["T"] = std::to_string(timeStamp);
		temp["V"] = tagDatalist[i].value;
		value.push_back(temp);
	}
	//原始平台兼容json
	valueList["data"] = value;
	std::string data = valueList.dump();
	try
	{
		mqtt::delivery_token_ptr pubtok;
		pubtok = m_cli.publish(m_info.mqttTopic, data.c_str(), strlen(data.c_str()), 2, false);
		pubtok->wait_for(TIMEOUT);
	}
	catch (const mqtt::exception& exc)
	{
		/*que.put(mqtt::delivery_token_ptr{});*/
		LOGINFO("mqtt send fail {}", exc.what());
		return -1;
	}
	return 0;
}

int trans::MqttTrans::Reconnect()
{
	mqtt::connect_options connOpts;
	connOpts.set_keep_alive_interval(20);
	connOpts.set_clean_session(true);
	try
	{
		mqtt::token_ptr conntok = m_cli.connect(connOpts);
		conntok->wait_for(TIMEOUT);
		LOGDEBUG("Connect MQTT OK!");
	}
	catch (const mqtt::exception& exc)
	{
		/*que.put(mqtt::delivery_token_ptr{});*/
		LOGINFO("mqtt connect fail {}", exc.what());
		return -1;
	}
	return 0;
}




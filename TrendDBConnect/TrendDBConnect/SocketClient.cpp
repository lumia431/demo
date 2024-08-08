#include "SocketClient.h"

SocketClient::SocketClient(SOCKET sock)
{
	sock_ = sock;
}

SocketClient::~SocketClient()
{
	while (!sendBuff_.empty())
	{
		sendBuff_.pop();
	}
}

bool SocketClient::hasSendData()
{
	return sendFlg_;
}

std::string SocketClient::getSendData()
{
	if (sendBuff_.empty())
	{
		return "";
	}
	std::string sendData = sendBuff_.front();
	sendBuff_.pop();
	if (sendBuff_.empty())
	{
		sendFlg_ = false;
	}
	return sendData;
}

time_t SocketClient::getOffLineTime()
{
	return time_t();
}

SOCKET SocketClient::GetSock()
{
	return sock_;
}

int SocketClient::PushSendData(std::string & sendData)
{
	sendBuff_.push(sendData);
	sendFlg_ = true;
	return 0;
}

#pragma once
#define SEND_BUFF_MAXSIZE 1024*8
#include "xspsc_queue.h"
#include <WinSock2.h>
#include <string>
#include <atomic>
//客户端封装类
class SocketClient
{
	using ringQueue = x_spsc_queue_t< std::string, 10 >;
public:
	SocketClient(SOCKET sock);
	~SocketClient();
	//检验缓冲队列是否有值
	bool hasSendData();
	//获取最新一条待发送的数据
	std::string getSendData();
	//获取离线时间
	time_t getOffLineTime();
	SOCKET GetSock();
	int PushSendData(std::string &sendData);
private:
	//socket套接字，每个SocketClient对应一个socket
	SOCKET sock_;
	//发送缓冲区
	ringQueue sendBuff_;
	//上次发送消息数据的时间，用于计时踢下线
	time_t dtSend_;
	bool sendFlg_ = false;
};
#pragma once
#define FD_SETSIZE      1024
#include "SocketClient.h"
#include "xspsc_queue.h"
#include <iostream>
#include <string>
#include <map>
#include <thread>
#include <queue>
#include <mutex>
#include <functional>
#include <condition_variable>
//线程任务类，每个任务接管一定数量的客户端
//使用select模型与客户端进行IO操作

struct RecvBufferData
{
	SOCKET sock;
	std::string buf;
	RecvBufferData() {};
	RecvBufferData(SOCKET sockArg, std::string bufArg) :sock(sockArg), buf(bufArg) {}
};
using ringQueue = x_spsc_queue_t< RecvBufferData, 100 >;

struct RecvLock
{
	ringQueue* recvBuffer;
	std::mutex *mutex;
	std::condition_variable *cv;
};

class ThreadTask
{
public:
	ThreadTask(RecvLock recvLock);
	ThreadTask(RecvLock recvLock, std::function<void (SOCKET)> cbDelete);
	~ThreadTask();
	//获取在线客户端数量
	uint16_t getClientNum();
	//增加一个客户端
	void addClient(SOCKET sock);
	//删除一个客户端
	void deleteClient(SOCKET sock);
	//开启线程
	void Start();
	//结束线程,超时自动退出
	bool PushSendData(RecvBufferData &sendData);
private:
	void Work();
	std::function<void (SOCKET)> cbDelete_;
	//在线客户端的集合
	std::map<SOCKET, SocketClient*> onlineClients_;
	//保护增删客户端线程安全
	std::mutex clientsMutex_;
	//控制线程启停
	time_t emptyContinueTime_;
	const uint16_t EMPTYOVERTIME = 3600;
	ringQueue* recvQueue_;
	std::condition_variable *cv_;
	std::condition_variable clientCv_;
	std::mutex* recvMutex_;
	std::atomic_bool startFlg_;
};
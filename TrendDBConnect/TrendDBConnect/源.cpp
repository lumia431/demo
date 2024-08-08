#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define For(n) for(int index = 0;index < n;index++)
#include <iostream>
#include <WinSock2.h>
#include <stdio.h>
#include <stdlib.h>
#include "ThreadTask.h"
#include <mutex>

#pragma comment(lib, "ws2_32.lib")
const UINT COMM_MAXLEN = 6 * 1024;
std::vector<ThreadTask*> v;
std::map<SOCKET, std::vector<std::string>> recvData_;
ringQueue ringQueue_;
std::condition_variable cv_;
std::mutex mutex_;
std::map<SOCKET, int> clientAllocation_;
void AllocateClient(SOCKET sock)
{
	std::map<int, int>m;
	for (int i = 0; i < v.size();i++)
	{
		m[v[i]->getClientNum()] = i;
	}
	v[m.begin()->second]->addClient(sock);
	clientAllocation_[sock] = m.begin()->second;
}

void CallBack(SOCKET sock)
{
	std::cout << "sock" << sock << "is iffline" << std::endl;
	clientAllocation_.erase(sock);
}

void test()
{
	RecvBufferData recvBuf;
	while (true)
	{
		std::unique_lock<std::mutex> locker(mutex_);
		while (ringQueue_.empty())
		{
			cv_.wait(locker);
		}
		recvBuf = ringQueue_.front();
		ringQueue_.pop();
		locker.unlock();
		recvBuf.buf.erase(recvBuf.buf.end() - 1);
		v[clientAllocation_[recvBuf.sock]]->PushSendData(recvBuf);
	}
}

int main()
{
	RecvLock recvLock;
	recvLock.cv = &cv_;
	recvLock.mutex = &mutex_;
	recvLock.recvBuffer = &ringQueue_;
	For(1)
	{
		ThreadTask *task = new ThreadTask(recvLock, &CallBack);
		v.emplace_back(task);
		v[index]->Start();
	}
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		printf("Failed to load Winsock");
		return 0;
	}    //创建用于监听的套接字
	SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(5099);
	server.sin_addr.S_un.S_addr = inet_addr("0.0.0.0");//这里填写IP
	int bindMeg = bind(sockSrv, (const sockaddr*)&server, sizeof(server));
	if (SOCKET_ERROR == bindMeg) /// 绑定出错
	{
		int a = WSAGetLastError();
		std::cout << "绑定出错了" << std::endl;
		closesocket(sockSrv);
		WSACleanup();
	}
	///监听ServerSocket,服务器socket + 最大挂起数
	int listenMeg = listen(sockSrv, SOMAXCONN);
	if (SOCKET_ERROR == listenMeg)
	{
		int a = WSAGetLastError();
		std::cout << "监听函数出错了" << std::endl;
		closesocket(sockSrv);
		WSACleanup();
	}
	sockaddr_in addrClient;
	int len = sizeof(addrClient);
	SOCKET socketClient;
	int index = 0;
	std::thread thr(test);
	thr.detach();
	while (++index)
	{
		socketClient = accept(sockSrv, (sockaddr*)&addrClient, &len);
		if (INVALID_SOCKET != socketClient)
		{
			std::cout << "success socketClient = " << socketClient << std::endl;
			AllocateClient(socketClient);
		}
		else
		{
			std::cout << "fail index = " << socketClient << std::endl;
		}
	}
	return 0;
}
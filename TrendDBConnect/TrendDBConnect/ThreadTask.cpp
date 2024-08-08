#include "ThreadTask.h"

ThreadTask::ThreadTask(RecvLock recvLock)
{
	recvQueue_ = recvLock.recvBuffer;
	recvMutex_ = recvLock.mutex;
	cv_ = recvLock.cv;
	startFlg_ = false;
}

ThreadTask::ThreadTask(RecvLock recvLock, std::function<void(SOCKET)> cbDelete)
{
	recvQueue_ = recvLock.recvBuffer;
	recvMutex_ = recvLock.mutex;
	cv_ = recvLock.cv;
	cbDelete_ = cbDelete;
}

ThreadTask::~ThreadTask()
{

}

uint16_t ThreadTask::getClientNum()
{
	return onlineClients_.size();
}

void ThreadTask::addClient(SOCKET sock)
{
	SocketClient *socketClient = new SocketClient(sock);
	{
		std::lock_guard<std::mutex>locker(clientsMutex_);
		onlineClients_[sock] = socketClient;
	}
	if (!startFlg_)
	{
		clientCv_.notify_one();
	}
}

void ThreadTask::deleteClient(SOCKET sock)
{
	closesocket(sock);
	clientsMutex_.lock();
	delete onlineClients_[sock];
	onlineClients_.erase(sock);
	clientsMutex_.unlock();
	cbDelete_(sock);
}

void ThreadTask::Start()
{
	std::thread thr = std::thread(&ThreadTask::Work, this);
	thr.detach();
}

bool ThreadTask::PushSendData(RecvBufferData & sendData)
{
	auto ptr = onlineClients_.find(sendData.sock);
	if (ptr == onlineClients_.end())
	{
		return false;
	}
	ptr->second->PushSendData(sendData.buf);
	return true;
}

void ThreadTask::Work()
{
	timeval serverTime;
	///select阻塞1秒
	serverTime.tv_sec = 0;
	serverTime.tv_usec = 100;
	FD_SET readSocketSet;
	FD_SET writeSocketSet;
	int recvMeg = 0;
	int sendMeg = 0;
	char buf[100] = {};
	std::map<SOCKET, std::shared_ptr<std::string>> sendTempMap;
	while (true)
	{
		FD_ZERO(&readSocketSet);
		FD_ZERO(&writeSocketSet);
		{
			std::unique_lock<std::mutex> clientLock(clientsMutex_);
			while (onlineClients_.empty())
			{
				startFlg_ = false;
				clientCv_.wait(clientLock);
			}
			startFlg_ = true;
			//根据并发量设置阻塞时间
			for (auto &sock : onlineClients_)
			{
				FD_SET(sock.first, &readSocketSet);
				if (sock.second->hasSendData())
				{
					FD_SET(sock.first, &writeSocketSet);
				}
			}
		}
		int selectMeg = select(0, &readSocketSet, &writeSocketSet, 0, &serverTime);
		if (selectMeg > 0)
		{
			int recvSuccessNum = 0;
			for (uint16_t i = 0; i < readSocketSet.fd_count; i++)
			{
				auto clientIter = onlineClients_.find(readSocketSet.fd_array[i]);
				if (clientIter == onlineClients_.end())
				{
					continue;
				}
				recvMeg = recv(readSocketSet.fd_array[i], buf, 100, 0);
				if (recvMeg > 0)
				{
					std::unique_lock<std::mutex> locker(*recvMutex_);
					recvQueue_->push(RecvBufferData(readSocketSet.fd_array[i], std::string(buf, recvMeg)));
					recvSuccessNum++;
				}
				else
				{
					std::cout << readSocketSet.fd_array[i] << "下线" << std::endl;
					deleteClient(readSocketSet.fd_array[i]);
				}
			}
			if (recvSuccessNum > 0)
			{
				std::unique_lock<std::mutex> locker(*recvMutex_);
				cv_->notify_one();
			}
			for (uint16_t i = 0; i < writeSocketSet.fd_count; i++)
			{
				auto clientIter = onlineClients_.find(writeSocketSet.fd_array[i]);
				if (clientIter == onlineClients_.end())
				{
					continue;
				}
				auto sendBuf = clientIter->second->getSendData();
				if (sendBuf.empty())
				{
					continue;
				}
				sendMeg = send(writeSocketSet.fd_array[i], sendBuf.c_str(), sendBuf.size(), 0);
			}
		}
		else if (selectMeg == 0)
		{
			continue;
		}
		else if (errno == EINTR)
		{
			std::cout << ("EasySelectServer select EINTR") << std::endl;
			continue;
		}
		else
		{
			std::cout << ("EasySelectServer select error") << std::endl;
			break;
		}
	}
	return;
}


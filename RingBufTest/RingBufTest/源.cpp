#define _CRT_SECURE_NO_WARNINGS
#define For(n) for(int index = 0;index < n;++index)
//#include "vld.h"
//#include "output_Container.h"
#include <iostream>
#include "xspsc_queue.h"
#include <string>
#include <vector>
#include <thread>
#include <queue>
#include <map>
#include <time.h>
#include <mutex>
using namespace std;
void test()
{
	mutex mutex_;
	int clientNum = 10000;
	bool b_push_finished = false;
	std::map<int, std::queue<int>> data_;
	For(clientNum)
	{
		data_[index];
	}
	std::thread xthread_in([&]()
	{
		for (int i = 1; i < 10000; ++i)
		{
			For(clientNum)
			{
				mutex_.lock();
				data_[index].push(i);
				mutex_.unlock();
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(50));//生产的快，消费慢就会出问题，front取值为空异常
		}
		b_push_finished = true;
	});

	std::thread xthread_out([&]()
	{
		while (true)
		{
			clock_t clo = clock();
			For(clientNum)
			{
				if (!data_[index].empty())
				{
					mutex_.lock();
					//1w个客户端加锁耗时500ms，不加锁耗时200ms
					auto a = data_[index].front();
					data_[index].pop();
					mutex_.unlock();
				}
				else if (b_push_finished)
				{
					break;
				}
			}
			std::cout << "time use " << clock() - clo << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
		}
	});

	if (xthread_in.joinable())
	{
		xthread_in.join();
	}

	if (xthread_out.joinable())
	{
		xthread_out.join();
	}

}
int main(int argc, char * argv[])
{
	//test();
	int clientNum = 10000;
	std::map<int, x_spsc_queue_t< int, 8 >> data_;
	std::vector<int> recvData_;

	//For(clientNum)
	//{
	//	data_[index];
	//}
	using x_int_queue_t = x_spsc_queue_t< int, 8 >;
	x_int_queue_t x;
	//x_int_queue_t spsc;

	//std::cout << "sizeof(x_int_queue_t) : " << sizeof(x_int_queue_t) << std::endl;

	bool b_push_finished = false;
	std::thread xthread_in([&](void) -> void
	{
		for (int i = 1; i < 10000; ++i)
		{
			x.push(i);
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
		}
		b_push_finished = true;
	});

	std::thread xthread_out([&](void) -> void
	{
		std::this_thread::sleep_for(std::chrono::seconds(5));
		while (true)
		{
			if (!x.empty())
			{
				//mutex_.lock();
				//1w个客户端加锁耗时500ms，不加锁耗时200ms
				auto a = x.front();
				x.pop();
				//mutex_.unlock();
				recvData_.emplace_back(a);
			}
			else if (b_push_finished)
			{
				break;
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
			//else if (b_push_finished)
			//{
			//	break;
			//}
		}
	});

	if (xthread_in.joinable())
	{
		xthread_in.join();
	}

	if (xthread_out.joinable())
	{
		xthread_out.join();
	}

	return 0;
}
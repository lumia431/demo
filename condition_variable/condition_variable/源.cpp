#include <thread>
#include <mutex>
#include <condition_variable>
#include <list>
#include <string>
#include <iostream>
#include <atomic>
using namespace std;
atomic<int> g_count;
bool g_flg = false;
class Task
{
public:
	Task(int taskID)
	{
		this->taskID = taskID;
	}
	void doTask()
	{
		std::cout << "handle a task, taskID: " << taskID << ", threadID: " << std::this_thread::get_id() << std::endl;
	}
private:
	int taskID;
};
std::mutex mymutex;
std::list<Task*> tasks;
std::condition_variable mycv;
void* consumer_thread()
{
	Task* pTask = NULL;
	while (true)
	{
		std::unique_lock<std::mutex> guard(mymutex);
		while (tasks.empty())
		{
			//如果获得了互斥锁，但是条件不合适的话，pthread_cond_wait 会释放锁，不往下执行
			//当发生变化后，条件合适， pthread_cond_wait 将直接获得锁

			mycv.wait(guard);
		}
		pTask = tasks.front();
		tasks.pop_front();
		if (pTask == NULL)
			continue;
		pTask->doTask();
		delete pTask;
		pTask = NULL;
	}
	return NULL;
}
void* producer_thread()
{
	int taskID = 0;
	Task* pTask = NULL;
	while (true)
	{
		pTask = new Task(taskID);
		{
			std::lock_guard<std::mutex> guard(mymutex);//使用括号减小 guard 锁的作用范围
			tasks.push_back(pTask);
			std::cout << "produce a task, taskID: " << taskID << ", threadID: " << std::this_thread::get_id() << std::endl;
		}
		//释放信号量，通知消费者线程
		mycv.notify_one();
		taskID++;
		//休眠 1 秒
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	return NULL;
}
std::shared_ptr<std::string> test()
{
	auto str = std::make_shared<std::string>("123");
	return str;
}
void test1()
{
	std::cout << 1 << std::endl;
	std::unique_lock<std::mutex> lock(mymutex);
	mycv.wait(lock, [] { return g_count.load() == 3; });
	std::cout << 5 << std::endl;
}

void test2()
{
	std::cout << 2 << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));
	g_count.fetch_add(1);
	mycv.notify_one();
}

void test3()
{
	std::cout << 3 << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));
	g_count.fetch_add(1);
	mycv.notify_one();
}

void test4()
{
	std::cout << 4 << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));
	g_count.fetch_add(1);
	mycv.notify_one();
}
int main()
{
	int bufLen = 2401;
	int a = 1242 / 7 / 3;
	int lineNum_perThr = (1242 / 7) / 3;	//每个线程处理的行数
	int max_send_perThr = lineNum_perThr * 7;	//每个线程能发送的最大字节
	int max_send = max_send_perThr * 3;	//总体能发送的最大字节
	int remain = bufLen - max_send;
	auto c = "12323";
	string str;
	str = "abc";
	str.append(c);
	str.append(c);
	str.append(c);
	//创建 5 个消费者线程
	//auto str = test();
	//if (str)
	//{
	//	std::cout << 1 << std::endl;
	//}
	//std::thread consumer1(consumer_thread);
	//std::thread consumer2(consumer_thread);
	//std::thread consumer3(consumer_thread);
	//std::thread consumer4(consumer_thread);
	//std::thread consumer5(consumer_thread);
	////创建一个生产者线程
	//std::thread producer(producer_thread);
	//producer.join();
	//consumer1.join();
	//consumer2.join();
	//consumer3.join();
	//consumer4.join();
	std::thread consumer1(test1);
	std::thread consumer2(test2);
	std::thread consumer3(test3);
	std::thread consumer4(test4);
	std::this_thread::sleep_for(std::chrono::seconds(10));
	consumer1.join();
	consumer2.join();
	consumer3.join();
	consumer4.join();
	return 0;
}
#include<iostream>
#include<thread>
#include<string>
#include<vector>
#include<list>
#include<mutex>
using namespace std;
vector<int>g_v = { 1,2,3 };
void myprint(int inum) {
	//cout << "myprint开始执行了" << endl;
	cout << "线程id为：" << this_thread::get_id() << "打印g_v值：" << g_v[0] << g_v[1] << g_v[2] << endl;
	return;
	//cout << "myprint执行完毕了" << endl;
}
class A {
public:
	void inMsgRecvQueue() {
		for (int i = 0; i < 10000; i++) {
			cout << "inMsgRecvQueue()insert:" << i << endl;
			{
				/*     lock_guard<mutex>sbguard(my_mutex1);*/
					   //my_mutex1.lock();//实际中不一定挨着，他们需要保护不同的共享数据
					   //my_mutex2.lock();
				lock(my_mutex1, my_mutex2);
				msgRecvQueue.push_back(i);
				my_mutex2.unlock();
				my_mutex1.unlock();
			}//加大括号提前解锁
		}
	}
	bool outMsgLULproc(int& command) {
		/* lock_guard<mutex>sbguard(my_mutex1);*/
		 //my_mutex.lock();
		my_mutex2.lock();
		my_mutex1.lock();//反着来才可能出现死锁
		if (!msgRecvQueue.empty()) {
			int command = msgRecvQueue.front();
			msgRecvQueue.pop_front();
			/*   my_mutex.unlock();*///每个分支，只要往外退，都必须有unlock
			my_mutex2.unlock();
			my_mutex1.unlock();
			return true;
		}
		/* my_mutex.unlock();*/
		my_mutex2.unlock();
		my_mutex1.unlock();
		return false;
	}
	void outMsgRecvQueue() {
		int command = 0;
		for (int i = 0; i < 10000; i++) {
			bool result = outMsgLULproc(command);
			if (result == true) {
				cout << "outMsgRecvQueue()" << command << endl;
			}
			else {
				cout << "outMsgRecvQueue()" << i << endl;
			}
		}
		cout << "end" << endl;
	}
private:
	list<int>msgRecvQueue;//把共享数据锁住，其他想操作共享数据的必须等待解锁，锁住》操作》解锁
	mutex my_mutex1;
	mutex my_mutex2;
};
int main() {
	//    vector<thread>mythreads;
	//    for (int i = 0; i < 10; i++) {
	//        mythreads.push_back(thread(myprint,i));
	//    }
	//    for (vector<thread>::iterator iter = mythreads.begin(); iter != mythreads.end(); iter++) {
	//        iter->join();
	//    }
	//读的时候不写，写的时候不读,不同时读写
	//    互斥量mutex，是个类对象，理解成一把锁，多个线程尝试用lock成员函数加锁，只有一个线程能锁定成功，成功标志是lock()返回
		//没成功卡在lock（）；与unlock成对使用   
		//互斥量少了达不到保护效果，多了影响效率
		//lock_guard类模板，自动unlock，使用后不能使用lock,unlock了，构造调用lock,析构unlock
		//死锁问题至少有两个锁头，即两个互斥量产生
		//死锁解决方案：上锁顺序一致
		//std::lock()函数模板同时锁两个以上，不存在死锁。要么两个互斥量都锁柱，要么都不锁。一个锁一个没锁上，会把锁住的解锁
	//    cout << "i love china" << endl;
	A myobja;
	thread myOut(&A::outMsgRecvQueue, &myobja);//第二个参数是引用保证两个线程用的同一个对象
	thread myIn(&A::inMsgRecvQueue, &myobja);
	myOut.join();
	myIn.join();
	system("pause");
	return 0;
}

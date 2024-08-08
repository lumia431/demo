#include<iostream>
using namespace std;
#include<string>
#include<future>
#include <deque>
#include "ThreadPool.h"
#include <windows.h>
//class A {
//public:
//    int mythread(int mypar) {
//        cout << mypar << endl;
//        cout << "mythread start thread id:" << this_thread::get_id() << endl;
//        chrono::milliseconds dura(5000);
//        this_thread::sleep_for(dura);
//        cout << "mythread start thread id:" << this_thread::get_id() << endl;
//        return 5;
//    }
//};
//int mythread() 
//{
//            //cout << mypar << endl;
//            cout << "mythread start thread id:" << this_thread::get_id() << endl;
//            chrono::milliseconds dura(5000);
//            this_thread::sleep_for(dura);
//            cout << "mythread start thread id:" << this_thread::get_id() << endl;
//            return 5;
//}
//void mythread(promise<int>&tmpp,int calc)
//{
//	calc *= 10;
//	chrono::milliseconds dura(1000);
//    this_thread::sleep_for(dura);
//	tmpp.set_value(calc);
//
//}
atomic<int> g_mycout = 0;
int mythread()
{
	static int a = 0;
	++a;
	for (int i = 0; i < 100; i++)
	{
		g_mycout++;
		Sleep(100);
		//g_mycout = g_mycout + 1;//++ -- += &= 原子操作是支持的
	}
	return g_mycout;
}

bool test1(int a) {
	return true;
}

bool test2(float a) {
	return false;
}

bool test3(string a) {
	return false;
}


int main() {
	//std::atomic<int> count = { 0 };
	//std::thread t1([&]() {
	//	count.fetch_add(1);
	//	});
	//std::thread t2([&]() {
	//	count++;        // 等价于 fetch_add
	//	count += 1;     // 等价于 fetch_add
	//	});
	////t1.join();
	//t2.join();
	//std::cout << count << std::endl;
	TestQueue pool;

	pool.exexute(test1, 2);
	pool.exexute(test2, 2.1);
	pool.exexute(test3, "2");
	//pool.printResult();
	//for (auto&& result : results)
	//	std::cout << result.get() << ' ';
	std::cout << std::endl;

	return 0;
}
//int main() {
//    //async,futrue
//    //async:函数模板，启动一个异步任务，返回一个futrue对象，futrue是个类模板，调用futrue对象的get函数获取线程返回值
//    //futrue的结果不能马上得到，在线程执行完毕时能拿到
//    //launch::deferred:不会进入子线程，表示入口函数延迟到future的wait或get调用时才执行，在主线程中执行。如果没有wait,get,线程都不会创建
//    //launch::async,在调用async函数的时候就开始创建线程,不加参数时默认用async；
//    //packaged_task,把各种可调用对象包装起来
//    //promise:在某个线程中给它赋值，在其他线程中取出来用
//   // A a;
// //   int tmppar = 12;
//	//promise <int>myProm;
// //   cout<<"main thread id:"<< this_thread::get_id() << endl;
//	//thread thr(mythread, ref(myProm), tmppar);//async创建自动执行线程，result是个将来值
//	//以future作为参数传入其他线程，get方法阻塞等待
//	//thr.join();
//   // cout << "continue....!" << endl;
//   // cout << "continue....!" << endl;
//   // cout << "continue....!" << endl;
//   // cout << "continue....!" << endl;
//   // cout << "continue....!" << endl;
//   // cout << "continue....!" << endl;
//   // int def = 0;
//   // cout << result.get() << endl;//卡在这里等待mythread执行完
//   /* cout << result << endl;*///get只能调用一次,因为它相当于移动，原来的值移完就没了
//   /* result.wait();*///等待线程返回，并不返回结果
//	thread mytobj1(mythread);
//	thread mytobj2(mythread);
//	mytobj1.join();
//	mytobj2.join();
//	g_mycout += 1;
//	cout << "g_mycout最终结果为:" << g_mycout << endl;
//    cout << "i love china!" << endl;
//	//资源紧张时thread可能创建失败，async()创建一个异步任务不是创建线程
//	//原子操作:多线程中不会被打断的代码片段，不可分割的操作，不拆成汇编，效率高
//	//原子操作相当于无锁的多线程并发技术，原子操作适用于一个变量而不是代码段
//	//原子操作一般用于累计统计
//    //cout << "main thread id:" << this_thread::get_id() << endl;
//    //packaged_task<int(int)>mypt(mythread);//把函数mythread通过package
//    //thread t1(ref(mypt), 1);
//    //t1.join();
//    //future<int>result = mypt.get_future();
//    //cout << result.get() << endl;
//    //cout << "i love china" << endl;
//    return 0;
//}
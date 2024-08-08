#include<iostream>
#include<thread>
#include<string>
#include<vector>
#include<list>
#include<mutex>
#include<Windows.h>
using namespace std;
#define __WINDOWSJQ_
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
            cout << "inMsgRecvQueue()执行，插入一个元素:" << i << endl;
            unique_lock<mutex>sbguard1(my_mutex1);
            //类 unique_lock 是通用互斥包装器，允许延迟锁定、锁定的有时限尝试、递归锁定、所有权转移和与条件变量一同使用。
            //unique_lock比lock_guard使用更加灵活，功能更加强大。使用unique_lock需要付出更多的时间、性能成本。
            msgRecvQueue.push_back(i);
            my_cond.notify_one();//唤醒wait
        }
        return;
    }
    //bool outMsgLULproc(int& command) {
    //    /* lock_guard<mutex>sbguard(my_mutex1);*/
    //     //my_mutex.lock();
    //    if (!msgRecvQueue.empty()) {
    //        unique_lock<mutex>sbguard1(my_mutex1);
    //        if (!msgRecvQueue.empty()) {
    //            int command = msgRecvQueue.front();
    //            msgRecvQueue.pop_front();
    //            /*   my_mutex.unlock();*///每个分支，只要往外退，都必须有unlock
    //            return true;
    //        }
    //    }
    //    return false;
    //}
    void outMsgRecvQueue() {
        int command = 0;
        while (true) {
            unique_lock<mutex>sbguard1(my_mutex1);
            my_cond.wait(sbguard1, [this] {//一个lambda就是可调用对象
                if (!msgRecvQueue.empty())
                    return true;
                return false;
                }); //如果第二个参数lambda返回值是true,wait直接返回
            //如果第二个参数lambda返回值是false,wait将解锁互斥量并堵塞到本行，直到其他某个线程调用nitify_one为止
            //如果wait没有第二个参数，那么效果类似于lambda返回false
            //被唤醒后不断尝试重新获取互斥量锁，如果获取不到，流程卡在wait等着获取
            //流程能走下来，互斥锁一定被锁着的
            //也就是等待消息队列是否为空的通知，取代原来的判断，开销小
            int command = msgRecvQueue.front();
            msgRecvQueue.pop_front();
            sbguard1.unlock();//unique_lock随时解锁方便
            cout << "outMsgRecvQueue()执行,取出一个元素" << command << endl;
        }


        //for (int i = 0; i < 10000; i++) {
        //    bool result = outMsgLULproc(command);
        //    if (result == true) {
        //        cout << "outMsgRecvQueue()执行,取出一个元素" << command << endl;
        //    }
        //    else {
        //        cout << "outMsgRecvQueue()执行,但目前消息队列为空" << i << endl;
        //    }
        //}
        //cout << "end" << endl;
    }
    A() {
#ifdef  __WINDOWSJQ_
        InitializeCriticalSection(&my_winsec);//用临界区前先初始化
#endif
    }
private:
    list<int>msgRecvQueue;//把共享数据锁住，其他想操作共享数据的必须等待解锁，锁住》操作》解锁
    mutex my_mutex1;
    condition_variable my_cond;//生成条件变量对象
#ifdef  __WINDOWSJQ_
    CRITICAL_SECTION my_winsec;//windows中的临界区，非常类似于c++中的mutex
#endif

};
int main() {
	g_v.erase()
    //condition_variable:实际上是一个类，等待条件达成，与互斥量配合使用，要生存类的对象
    A myobja;
    thread myOut(&A::outMsgRecvQueue, &myobja);//第二个参数是引用保证两个线程用的同一个对象
    thread myIn(&A::inMsgRecvQueue, &myobja);
    myOut.join();
    myIn.join();
    system("pause");
    return 0;
}

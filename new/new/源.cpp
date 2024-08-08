#define For(n) for(int index = 0;index < n;++index)
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<vector>
#include"PObject.h"
using namespace std;

class testClass
{
public:
    testClass(int data) :data(data) {}
    int getData() { return this->data; }
    void setData(int data) { this->data = data; }
    void* operator new(size_t size)
    {
        return malloc(size);
    }
    void* operator new(size_t size,void *ptr)
    {
        printf("global new/n");
        return malloc(size);
    }
private:
    int data;
};


int main()
{
    testClass* t = new testClass(1);
    //申请一个testClass类大小的动态内存
    char* buff = new char[sizeof(testClass)];
    memset(buff, 0, sizeof(buff));

    //placement new一个对象
    testClass* myClass = new (buff)testClass(10);
    std::cout << myClass->getData() << std::endl;

    //使用完之后调用析构函数销毁对象并置空（但是buff动态内存仍存在）
    myClass->~testClass();
    myClass = nullptr;

    //在这块内存上再次分配一个对象
    testClass* myClass2 = new (buff)testClass(12);
    std::cout << myClass2->getData() << std::endl;

    //释放对象
    myClass2->~testClass();
    myClass2 = nullptr;

    //释放动态内存
    delete[]buff;

    return 0;
}


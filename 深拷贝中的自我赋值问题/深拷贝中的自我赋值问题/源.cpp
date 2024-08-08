#define _CRT_SECURE_NO_WARNINGS
#define For(n) for(int index = 0;index < n;++index)
//#include "vld.h"
//#include "output_Container.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Bitmap { 
	int data_;
};
class Widget {
public:

private:
	Bitmap * pb;  //指针，指向一个从heap分配而得的对象
};

//可能第一眼看没什么问题，但如果传入的参数rhs是它本身呢？这就会导致delete语句把*this自己的资源释放掉，
//同时也释放掉了rhs的资源。最后，返回的*this包含了一个损坏的数据，你不能访问不能修改，
//甚至不能通过delete来为其释放资源，等于说这段内存空间就凭空消失了。所以，这段代码不是自赋值安全的
Widget& Widget::operator=(const Widget& rhs) //一份不安全的operator=实现版本
{
	//如果含有指针成员，需要使用深拷贝
	delete pb;   //停止使用当前的bitmap
	pb = new Bitmap(*rhs.pb); //使用rhs's bitmap的副本
	return *this;
}

//自我赋值检测：方式一
//这个方法考虑到了自我赋值的安全性问题，但仍然不是异常安全的。如果执行完delete语句后，
//再执行下面的new语句时抛出了异常(例如内存不足、拷贝构造函数抛出异常)。最后，也会导致*this储存了一个损坏的数据
Widget& Widget::operator=(const Widget& rhs)
{
	if (this == &rhs) return *this; //证同测试；如果是自我赋值则不做任何事

	delete pb;   //停止使用当前的bitmap
	pb = new Bitmap(*rhs.pb); //使用rhs's bitmap的副本
	return *this;
}

//自我赋值检测：方式二
//现在，如果“new Bitmap”抛出异常，pb保持原状，不会被delete。
Widget& Widget::operator=(const Widget& rhs)
{
	Bitmap* pOrig = pb;   //记住原先的pb
	pb = new Bitmap(*rhs.pb); //令pb指向一个*pb的一个副本
	delete pOrig;      //删除原先的pb
	return *this;
}


int main() 
{

	system("pause");
	return 0;
}
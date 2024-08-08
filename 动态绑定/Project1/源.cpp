#pragma message( "Compiling " __FILE__ )         //显示被编译的文件
#pragma message( "Last modified on " __TIMESTAMP__ )     //文件最后一次修改的日期和时间 
#pragma warning( push, 4 )
#define For(n) for(int index=0;index<n;++index)
//#include "vld.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;
//int f()
//{
//
//}
//float f(int a )//无法重载仅按返回值区分的函数,一定要参数也不一样
//{
//
//}
#pragma pack(1)
struct DataType
{
	uint8_t head1;
	uint8_t head2;
	unsigned weizhuangjia : 1;
	unsigned qipao : 1;
	unsigned duse : 1;
	unsigned genghuandianchi : 1;
	unsigned jixieguzhang : 1;
	unsigned jixianliang : 1;
	unsigned jiangjieshu : 1;
	unsigned shuyejieshu : 1;
	DataType() :
		head1(0x02),
		head2(0x02),
		weizhuangjia(1),
		qipao(0),
		duse(0),
		genghuandianchi(0),
		jixieguzhang(0),
		jixianliang(1),
		jiangjieshu(0),
		shuyejieshu(0) {}

};

struct DataHead
{
	uint8_t type;
	unsigned short time;
	uint8_t stream;
	//DataHead():
	//	head1(0),
	//	head2(0),
	//	head3(0),
	//	head4(0),
	//	reserve(0),
	//	curveEnd(0),
	//	partStart(0),
	//	partEnd(0){}
};
#pragma pack()
class A
{
public:
	void FuncA()
	{
		printf("FuncA called\n");
	}
	virtual void FuncB()
	{
		printf("FuncB called\n");
	}
};
class B : public A
{
public:
	void FuncA()
	{
		A::FuncA();
		printf("FuncAB called\n");
	}
	virtual void FuncB()
	{
		printf("FuncBB called\n");
	}
};
int main(void)
{
	char dataIndex1[] = { 0x61,  0x53 , 0x11,  0x00 };
	char dataIndex2[] = { 0x61,  0x53 , 0x11,  0x01 };

	//int b = sizeof(DataType);
	//DataHead head1;
	//DataHead head2;
	//head1 = *(DataHead*)dataIndex1;
	//head2 = *(DataHead*)dataIndex2;
	//int v = (head1.type & 0xf0)>>4;
	//int s = head1.stream;
	//bool d = head1.type & 0x04;
	B  b;
	A  *pa;
	pa = &b;
	A *pa2 = new A;
	pa->FuncA(); //pa=&b动态绑定但是FuncA不是虚函数，所以FuncA called,虚函数才会调用B
	pa->FuncB(); //FuncB是虚函数所以调用B中FuncB，FuncBB called  
	pa2->FuncA(); //pa2是A类指针，不涉及虚函数，调用的都是A中函数，所以FuncA called FuncB called
	pa2->FuncB();
	delete pa2;
	return 0;
}

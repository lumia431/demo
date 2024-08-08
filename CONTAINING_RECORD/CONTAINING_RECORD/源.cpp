#include <windows.h>
#include <stdio.h>
typedef struct {		//相对地址	
	int m_1;			//0x0
	int m_2;			//0x4
	int m_3;			//0x8
}DATA, *PDATA;
// 利用地址的偏移和对0用结构体指针型强制类型转换来实现对结构体基地址的寻址。
//三参数：某一成员、对象中该成员的地址以及这一结构体名或类名
#define CONTAINING_RECORD(address,type,field) ((type*)((PCHAR)(address)-(ULONG_PTR)(&((type*)0)->field)))
int main()
{

	DATA Data = { 33,22,11 };
	//int* v3 = (int*)(&((PDATA)0)->m_1);
	int* v1 = &Data.m_2;
	PDATA v2 = CONTAINING_RECORD(v1, DATA, m_2);
	printf("%d %d %d\n", v2->m_1, v2->m_2, v2->m_3);
	//printf("%p\r\n", v3);
	return 0;
}
//最终v2就是对象Data的地址，我们可以不使用Data就直接访问该对象的成员

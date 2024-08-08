#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <string>
#include <future>
#include <functional>
#include <queue>
using namespace std;

void f1() {}
void f2(int a){}
int main()
{
	//queue<function<void()>>q;
	//q.push(f1);
	//q.emplace(f2);
	int b;
	if (int a = 1)
	{
		a = 2;
	}
	scanf("%d", &b);

	char buf1[10];
	size_t i = snprintf(buf1, 10, "%5d", 6666666);
	//将可变参数 “…” 按照format的格式格式化为字符串，然后再将其拷贝至str中
	char a[20] = { 0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9,

					  0xa, 0xb, 0xc, 0xd, 0xe, 0xf, 0x10, 0x11, 0x12, 0x13 };

	char buf[20 * 2 + 1] = { 0 };

	for (int i = 0; i < 20; ++i) {

		snprintf(&buf[i * 2], 3, "%02x", a[i]);//注意是3不是2，snprintf 比sprintf要预留一个位置

	}
	cout << "热点撒" << endl;
	printf("buf:%s\n", buf);
	const char *ptr = "2020-06-28 12:00:00";
	int year, month, day, hour, minute, second = 0;
	auto ret = sscanf_s(ptr, "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);
	return 0;
}
#include<iostream>
#include<vector>
using namespace std;
template <class T>
//c++有很多初始化方式，默认初始化、值初始化、复制初始化、列表初始化、聚合初始化（指数组，结构体等初始化）
struct MyStruct
{
	//MyStruct(){}//用户如果自定义了构造函数则该类不能算聚合类，无法使用聚合初始化
	//此时可以用花括号初始化器列表列表初始化一个对象，
	// 其中对应构造函数接受一个 std::initializer_list 参数
	//MyStruct() = default;
	MyStruct(std::initializer_list<T> l) {
		std::cout << "constructed with a " << l.size() << "-element list\n";
	}
	int a;
	double b;
	char* c;
};

class M
{
	void test(){}
};

int main() {
	MyStruct m = { 1,2 };
	//下面是指派初始化器（c++20），须按照成员声明顺序,不能作为initializer_list传入
	//MyStruct m2 = { .a = 1 ,.c = (char*)"haha"};
	auto a = { 1,2,3 };
	M m3 = {};
	system("pause");
}
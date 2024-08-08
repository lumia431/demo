#include<iostream>
#include<string>
#include<functional>

void* (*g_read)(void*);

struct X {
	static void* f(void *p) 
	{ 
		char* c = (char*)p;
		std::cout << c << std::endl;
		return nullptr;
	}
};

void f2() {
	std::cout << "7";
}

struct Test_bind {
	void t(int n) {
		for (; n; n--)
			std::cout << "t\n";
	}
	void t() {
		std::cout << "重载的t\n";
	}
};

std::string& f()
{
	std::string s = "Example";
	return s; // 退出 s 的作用域:
	// 调用其析构函数并解分配其存储
}

void *ff(void* (*read)(void*))
{
	g_read = read;
	return nullptr;
}

int main() {
	//void(X:: * p)() = &X::f;
	//X x;
	//(x.*p)();//6
	//void(*p2)() = f2;
	//(*p2)();//等价于p2()
	//std::string& r = f(); // 悬垂引用
	////std::cout << r;       // 未定义行为：从悬垂引用读取
	//std::string s = f();  // 未定义行为：从悬垂引用复制初始化
	//std::string str("123");
	//std::string& s1 = str;
	//str.~basic_string();
	//std::cout << str << std::endl;
	//std::cout << s1 << std::endl;
	std::function<void()> f;

	Test_bind t_b;
	f = std::bind(static_cast<void(Test_bind::*)(int)>(&Test_bind::t), &t_b, 3);
	f();
	//n();
	ff(&X::f);
	g_read((void *)"123");
}
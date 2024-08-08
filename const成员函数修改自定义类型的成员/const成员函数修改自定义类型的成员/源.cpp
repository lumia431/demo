#define For(n) for(int index = 0;index < n;++index)
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<vector>
using namespace std;
class Data
{
public:
	void setVal(int a) { data_ = a; };
private:
	int data_;
};
class Test
{
public:
	void setVal(int a)const {
		//d_.setVal(a);//对象含有不兼容的类型限定符,即要求Data的setVal也必须是const
		d2_->setVal(a);
	}
	void f() {
		int a = 3;
		d3_ = &a;
		d4_ = &a;
	}
private:
	Data d_;
	Data* d2_;
	Data* const d3_;
	Data const * d4_;
};
int main() {

	system("pause");
	return 0;
}
#include<iostream>
using namespace std;
class Base
{
public:
	virtual void f() { cout << 1 << endl; }
};

class De :Base
{
public:
	void f() { cout << 2 << endl; }
	void fun() { cout << 3 << endl; }
private:
	int data_;
};

int main() {
	De* b = nullptr;
	b->fun();
}
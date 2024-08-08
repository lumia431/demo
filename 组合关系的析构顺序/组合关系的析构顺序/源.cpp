#include<iostream>
#include<string.h>
using namespace std;

class A
{
public:
	A() { 
		c = new char[10];
		strcpy(c, "123");
		cout << "A Constructor." << endl; 
	}
	~A() { 
		delete c; 
		cout << "A Destructor." << endl; 
	}
private:
	char* c;
};

class B
{
public:
	B() { 
		c = new char[10];
		strcpy(c, "123");
		cout << "B Constructor." << endl; 
	}
	~B() { 
		delete c;
		cout << "B Destructor." << endl; 
	}
private:
	char* c;
};

class C
{
public:
	C() { 
		c = new char[10];
		strcpy(c, "123");
	}
	~C() { 
		delete c;
		cout << "C Destructor." << endl; 
	}

private:
	char* c;
};

class D
{
public:
	D(){ 
		c = new char[10];
		strcpy(c, "123");
	}
	~D() { 
		delete c;
		cout << "D Destructor." << endl; 
	}
private:
	char* c;
	A m_a_;
	B m_b_;
};

class E
{
public:

private:
	int m_j;
	D m_c_;
};

int main()
{
	{
		E e;
	}
}
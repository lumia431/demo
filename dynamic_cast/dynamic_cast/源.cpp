#include <iostream>
using namespace std;

class A {
public:
	virtual void func() const { cout << "Class A" << endl; }
private:
	int m_a;
};

class B : public A {
public:
	virtual void func() const { cout << "Class B" << endl; }
private:
	int m_b = 1;
};

class B2 : public A {
public:
	virtual void func() const { cout << "Class B" << endl; }
private:
	int m_b1 = 1;
	int m_b2 = 2;
};

class C : public B {
public:
	virtual void func() const { cout << "Class C" << endl; }
	void funcC(){}
private:
	int m_c;
};

class D : public C {
public:
	virtual void func() const { cout << "Class D" << endl; }
private:
	int m_d;
};

int main() {
	A *pa = new A();
	B *pb;
	C *pc;

	A* b1 = new B();
	B2* c1 = (B2 *)b1;

	//情况①
	pb = dynamic_cast<B*>(pa);  //向下转型失败
	if (pb == NULL) {
		cout << "Downcasting failed: A* to B*" << endl;
	}
	else {
		cout << "Downcasting successfully: A* to B*" << endl;
		pb->func();
	}
	pc = dynamic_cast<C*>(pa);  //向下转型失败
	if (pc == NULL) {
		cout << "Downcasting failed: A* to C*" << endl;
	}
	else {
		cout << "Downcasting successfully: A* to C*" << endl;
		pc->func();
	}

	cout << "-------------------------" << endl;

	//情况②
	pa = new D();  //向上转型都是允许的
	pb = dynamic_cast<B*>(pa);  //向下转型成功
	if (pb == NULL) {
		cout << "Downcasting failed: A* to B*" << endl;
	}
	else {
		cout << "Downcasting successfully: A* to B*" << endl;
		pb->func();
	}
	pa = dynamic_cast<C*>(pa);  //向下转型成功
	if (pa == NULL) {
		cout << "Downcasting failed: A* to C*" << endl;
	}
	else {
		cout << "Downcasting successfully: A* to C*" << endl;
		pa->func();
	}

	return 0;
}
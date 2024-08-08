#include <iostream>  
using namespace std;
class Base
{
public:
	Base() { int_pro = 1; };
	Base(int da) { int_pro = da; };
	virtual ~Base() {};
protected:
	int int_pro;
    void print() {
        cout << "print " << int_pri << endl;
    }
private:
	int int_pri;
};
class Derived : public Base
{
public:
    Derived() {};
    Derived(int da):Base(da) { /*this->int_pro = 4;*/ }
	void Print(Derived&obj) { 
        obj.data = 24; 

    }
	//void Print(Base &obj) { obj.int_pro = 24; }
	void PrintPro() { 
        print();
        cout << "The proteted data is " << data << endl; 
    }
private:
	int data = 5;
};
int main()
{
    //这是第一种情况
    Base* base = new Derived;
    cout << sizeof(*base) << endl;
    if (Derived* der = dynamic_cast<Derived*>(base))
    {
        der->PrintPro();
        cout << "第一种情况转换成功" << endl;
        cout << endl;
    }
    //这是第二种情况
    Base* base1 = new Base;
    if (Derived* der1 = dynamic_cast<Derived*>(base1))
    {
        cout << "第二种情况转换成功" << endl;
    }
    else
    {
        cout << "第二种情况转换失败" << endl;
    }

    delete(base);
    delete(base1);
	cout << sizeof(Derived) << '\t' << sizeof(Base) << endl;
	//注释1  
	//aObj.int_pro = 8;  
}
#define _CRT_SECURE_NO_WARNINGS
#define For(n) for(int index = 0;index < n;++index)
//#include "vld.h"
//#include "output_Container.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Phone {
	virtual void show();
};
class Phone1 :public Phone{
	void show() override;
};
class Phone2 :public Phone {
	void show() override;
};
class PC {
	virtual void show();
};
class PC1 :public PC {
	void show() override;
};
class PC2 :public PC {
	void show() override;
};

class Mouse {
	virtual void show();
};
class Mouse1 :public Mouse {
	void show() override;
};
class Mouse2 :public Mouse {
	void show() override;
};
class Factory {
	virtual Phone* productPhone() = 0;
	virtual PC* productPC() = 0;
	virtual Mouse* productMouse() = 0;
};
class Factory1 :public Factory {
	virtual Phone* productPhone();
	void productPC(PC* pc) override;
};

int main() 
{
	Factory* f = new Factory1();
	Phone* p = new Phone1();
	f->productPhone()->show();
	system("pause");
	return 0;
}

Phone* Factory1::productPhone()
{
	Phone* phone = new Phone1();
	return phone;
}

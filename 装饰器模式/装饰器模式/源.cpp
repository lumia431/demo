#include <iostream>
#include <list>
#include <algorithm>
#include <memory>
using namespace std;
//抽象构件类 Transform (变形⾦刚)
class Transform {
public:
	virtual void move() = 0;
};
//具体构件类Car
class Car : public Transform {
public:
	Car() {
		std::cout << "变形⾦刚是⼀辆⻋！" << endl;
	}
	void move() {
		std::cout << "在陆地上移动。" << endl;
	}
};
//抽象装饰类
class Changer : public Transform {
public:
	Changer(shared_ptr<Transform> transform) {
		this->transform = transform;
	}
	void move() {
		transform->move();
	}
private:
	shared_ptr<Transform> transform;
};
//具体装饰类Robot
class Robot : public Changer {
public:
	Robot(shared_ptr<Transform> transform) : Changer(transform) {
		std::cout << "变成机器⼈!" << std::endl;
	}
	void say() {
		std::cout << "说话!" << std::endl;
	}
};
//具体装饰类AirPlane
class Airplane : public Changer {
public:
	Airplane(shared_ptr<Transform> transform) : Changer(transform) {
		std::cout << "变成⻜机!" << std::endl;
	}
	void say() {
		std::cout << "在天空⻜翔!" << std::endl;
	}
};
int main(void) {
	//算法可以用原生指针做参数
	int arr[3] = { 3,6,1 };
	auto ptr = std::find(arr, arr + 2,2);
	shared_ptr<Transform> camaro = make_shared<Car>();
	camaro->move();
	std::cout << "--------------" << endl;
	shared_ptr<Robot> bumblebee = make_shared<Robot>(camaro);
	bumblebee->move();
	bumblebee->say();
	return 0;
}
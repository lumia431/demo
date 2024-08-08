#include<iostream>
using namespace std;

template<class T>
struct X{};

template<class T,template<class T> typename C>
struct Y {
	C<T>c;
};

template<class T>
struct X2
{
	T t;
};
// 泛型的模板类
template <typename T>
class MyClass {
public:
    MyClass(T data) {
        // 实现代码
    }
};

// 对于指针类型的特化实现
template <typename T>
class MyClass<T*> {
public:
    MyClass(T* data) {
        // 特化的实现代码
    }
};

int f() {
    return 3;
}


int main() {
    int &&a = f();
    int b = 4;
    a = b;
    b = 5;
}
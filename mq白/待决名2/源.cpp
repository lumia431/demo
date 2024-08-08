#include <iostream>
#include <string>

void g(double) { std::cout << "g(double)\n"; }

template<class T>
struct S
{
    void f() const
    {
        g(1); // "g" 是非待决名，现在绑定
    }
};

void g(int) { std::cout << "g(int)\n"; }

int main()
{
    g(1);  // 调用 g(int)

    S<int> s;
    s.f(); // 调用 g(double)
}
#include <iostream>
#include <string>
#include <vector>
using namespace std;
template<typename T, template<typename U> typename Container>
class XCls
{
public:
	XCls(T a);
	Container<T> c;
};
template<typename T ,template<typename U> typename Container>
XCls<T, Container>::XCls(T a):c(Container<T>(a))
{
	
}

template<typename T>
class test
{
public:
	test(T a);
	T t;
};
template<typename T>
test<T>::test(T a)
{
	//if constexpr (is_integral<T>::value)
	//{
	//	return t;
	//}
	t = a;
}
template<typename T>
using V = std::vector<T, std::allocator<T>>;
int main(void)
{
	string str = "lmy";
	//XCls<std::string, test> mylst1(str);
	//cout<<mylst1.c.t;

	XCls<string, V>x(str);
	cout << x.c.size();
	return 0;
}


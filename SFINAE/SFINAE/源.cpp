#include <iostream>
#include <list>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <iterator>
template <typename>
using void_t = void;

template <typename T, typename V = void>
struct has_push_back :std::false_type {};//继承std::false_type

//std::declval<T>()返回T类型的右值引用
//decltype获取类型不调用函数
template <typename T>
//用上面的基本模板生成一个特化
struct has_push_back<T, void_t<decltype(std::declval<T>().push_back(std::declval<typename T::value_type>()))>> :std::true_type {};

int main() {
	//test<int,std::string>();
	//std::vector<const int> v{ 1,2,3 };
	//std::vector<const int>::iterator cIter = v.begin();
	//*cIter = 2;//指针指向的对象无法被修改,相当于value_type是一个const对象
	std::cout << has_push_back<std::list<int>>::value << std::endl;
	std::cout << has_push_back<std::map<int, int>>::value << std::endl;
	std::cout << has_push_back<std::set<int>>::value << std::endl;
	std::cout << has_push_back<std::string>::value << std::endl;
	std::cout << has_push_back<std::vector<int>>::value << std::endl;
	return 0;
}
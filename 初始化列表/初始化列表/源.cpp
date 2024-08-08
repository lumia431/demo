#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;
class AA
{
public:
	AA()
	{
		std::cout << "AA默认构造函数" << std::endl;
	}
	AA(const AA&)
	{
		std::cout << "AA拷贝构造函数" << std::endl;
	}
	AA& operator=(const AA&)
	{
		std::cout << "AA赋值函数" << std::endl;
		return *this;
	}
	~AA()
	{
		std::cout << "AA析构函数" << std::endl;
	}
private:
	char a;
	vector<int> v;
	
};
class BB
{
public:
	BB()
	{
		std::cout << "BB默认构造函数" << std::endl;
	}
	//BB(const AA& a)
	//{
	//	a_ = a;
	//	std::cout << "BB构造函数" << std::endl;
	//}
	BB(const AA& a) :a_(a)
	{
		std::cout << "BB构造函数" << std::endl;
	}
	~BB()
	{
		std::cout << "BB析构函数" << std::endl;
	}
private:
	AA a_;
};
void main() {
	AA a;
	cout << "===========" << endl;
	BB b(a);
	unordered_set<int> uSet{ 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17};
	system("pause");
}
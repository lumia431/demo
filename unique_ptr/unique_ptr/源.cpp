#include "vld.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <memory.h>
#include <shared_mutex>
#include <time.h>

using namespace std;
struct ThreadSafe
{
	mutable std::shared_timed_mutex mutex_;
	int value_;
	ThreadSafe()
	{
		cout << "ye" << endl;
		value_ = 0;
	}
	int get() const
	{
		std::shared_lock<std::shared_timed_mutex> loc(mutex_);
		return value_;
	}
	//************************************
	// Method:    increase
	// FullName:  ThreadSafe::increase
	// Access:    public 
	// Returns:   void
	// Qualifier:
	//************************************
	void increase() 
	{
		std::unique_lock<std::shared_timed_mutex> lock(mutex_);
		value_ += 1;
	}
};
class A
{
public:
	A()
	{
		cout << 1 << endl;
	}
private:
	int a;
};
//************************************
// Method:    main
// FullName:  main
// Access:    public 
// Returns:   int
// Qualifier:
//************************************
class Investment { // 投资
public:
	virtual ~Investment() {}
};
class Stock : public Investment {}; // 股票
class Bond : public Investment {}; // 债券
class RealEstate : public Investment {}; // 不动产

void makeLogEntry(Investment*) {}

auto delInvmt1 = [](Investment* pInvestment) { // custom deleter(a lambda expression), 使用无状态lambda表达式作为自定义析构器
	makeLogEntry(pInvestment);
	delete pInvestment;
};

void delInvmt2(Investment* pInvestment) // 使用函数作为自定义析构器
{
	makeLogEntry(pInvestment);
	delete pInvestment;
}

template<typename... Ts>
//std::unique_ptr<Investment> makeInvestment(Ts&&... params) // return std::unique_ptr to an object created from the given args
std::unique_ptr<Investment, decltype(delInvmt1)> makeInvestment(Ts&&... params) // 改进的返回类型,返回值尺寸与Investment*相同
//std::unique_ptr<Investment, void(*)(Investment*)> makeInvestment(Ts&&... params) // 返回值尺寸等于Investment*的尺寸+至少函数指针的尺寸
{
	//std::unique_ptr<Investment> pInv(nullptr);
	std::unique_ptr<Investment, decltype(delInvmt1)> pInv(nullptr, delInvmt1); // ptr to be returned

	if (nullptr/* a Stoc object should be created*/) {
		pInv.reset(new Stock(std::forward<Ts>(params)...));
	}
	else if (nullptr/*a Bond object should be created*/) {
		pInv.reset(new Bond(std::forward<Ts>(params)...));
	}
	else if (nullptr/*a RealEstate object should be created*/) {
		pInv.reset(new RealEstate(std::forward<Ts>(params)...));
	}

	return pInv;
}

//int test_item_18()
//{
//	auto pInvestment = makeInvestment(1); // pInvestment is of type std::unique_ptr<Investment>
//	std::shared_ptr<Investment> sp = makeInvestment(1); // converts std::unique_ptr to std::shared_ptr
//
//	return 0;
//} // destroy *pInvestment
int main()
{
	//vector<int>v{1,2,3,4};
	//vector<int>v2{5,6,7,8,9};
	///*v.swap(v2);*/
	//exchange(v, v2);
	//string str = "lvelvelve";
	//cout<<quoted(str);
	//int a = 0b0001'0011'1010;
	//double b = 3.14'1234'1234'1234;
	A t;
	auto ptr = make_unique<A>();
	ptr.reset(new A());
	auto p = ptr.get();
	//test_item_18();
	return 0;
}
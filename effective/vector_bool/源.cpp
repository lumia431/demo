#include<iostream>
#include<vector>
using namespace std;
class Widget6 {};
std::vector<bool> features(const Widget6& w)
{
	return std::vector<bool>{true, true, false, false, true, false};
}


class Widget7 {
public:
	Widget7(int i, bool b) {} // constructor not declaring std::initializer_list params
	Widget7(int i, double d) {}
	//Widget7(std::initializer_list<long double> il) { fprintf(stdout, "std::initializer_list params\n"); }
	Widget7() = default;
	Widget7(int) {}

	operator float() const { return 1.0f; } // 强制转换成float型别, 注意：此函数的作用,下面的w13和w15

private:
	int x{ 0 }; // fine, x's default value is 0
	int y = 0; // also fine
	//int z(0); // error
};

void processWidget6(const Widget6& w, bool highPriority) {}

double calcEpsilon() { return 1.0; }
//vector<bool>是一个伪容器，并不保存真正的bool，而是打包bool以节省空间。在一个典型的实现中，
//每个保存在“vector”中的“bool”占用一个单独的比特，而一个8比特的字节将容纳8个“bool”。在内部，
//vector<bool>使用了与位域（bitfield）等价的思想来表示它假装容纳的bool。
//引用单个比特也是禁止的，这为vector<bool>接口的设计摆出了难题。因为vector<T>::operator[]的返回值应该是T& 。
//如果vector<bool>真正容纳bool，这不成问题，但因为它没有，vector<bool>::operator[]需要返回指向一个比特的引用，
//而并不存在这样的东西。为了解决这个难题，vector<boo>::operator[]返回一个对象，其行为类似于比特的引用，也称为代理对象。
int test_item_6()
{
	Widget6 w;
	bool highPriority = features(w)[5]; // 正确,显式声明highPriority的型别
	processWidget6(w, highPriority);

	// 把highPriority从显示型别改成auto
	auto highPriority2 = features(w)[5]; // highPriority2的型别由推导而得,std::vector<bool>的operator[]的返回值并
										//不是容器中一个元素的引用(单单bool是个例外),返回的是个
										//std::vector<bool>::reference型别的对象,返回一个std::vector<bool>型别的临时对象
	processWidget6(w, highPriority2); // undefined behavior, highPriority2 contains dangling pointer(空悬指针)

	auto highPriority3 = static_cast<bool>(features(w)[5]); // 正确
	processWidget6(w, highPriority3);

	float ep = calcEpsilon(); // 隐式转换 double-->float,这种写法难以表明"我故意降低了函数的返回值精度"
	auto ep2 = static_cast<float>(calcEpsilon()); // 推荐

	return 0;
}

int main() {
	Widget7 w10{ 10, true };
	int a = 1;
	const int& b = a;
	test_item_6();
	return 0;
}
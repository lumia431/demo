#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <complex>
#include "container.h"
using namespace std;
void test() noexcept(true)
{
	try
	{
		vector<vector<int>> vv{
		{1, 1},
		{2, 4},
		{3, 9} };
		cout << vv.at(3) << endl;
	}
	catch (const std::exception&)
	{
		cout << "1" << endl;
	}

}
void may_throw() {
	throw true;
}
auto non_block_throw = [] {
	may_throw();
};
void no_throw() noexcept {
	return;
}

auto block_throw = []() noexcept {
	no_throw();
};
int main()
{
	//map<string, complex<double>>m;
	//m.emplace(piecewise_construct, make_tuple("hello"), make_tuple(1, 2));
	//cout << m << endl;
	//map<int, int> mp{
	//	{1, 1},
	//	{2, 4},
	//	{3, 9} };
	//cout << mp << endl;
	//vector <int> a{ 1,2,3 };
	try
	{
		test();
	}
	catch (const std::exception&)
	{

	}
	//cout << a.at(2) << endl;
	//std::cout << std::boolalpha
	//	<< "may_throw() noexcept? " << noexcept(may_throw()) << std::endl
	//	<< "no_throw() noexcept? " << noexcept(no_throw()) << std::endl
	//	<< "lmay_throw() noexcept? " << noexcept(non_block_throw()) << std::endl
	//	<< "lno_throw() noexcept? " << noexcept(block_throw()) << std::endl;

	//try {
	//	may_throw();
	//}
	//catch (...) {
	//	std::cout << "exception captured from my_throw()" << std::endl;
	//}

	//try {
	//	non_block_throw();
	//}
	//catch (...) {
	//	std::cout << "exception captured from non_block_throw()" << std::endl;
	//}

	//try {
	//	block_throw();
	//}
	//catch (...) {
	//	std::cout << "exception captured from block_throw()" << std::endl;
	//}
	return 0;
}
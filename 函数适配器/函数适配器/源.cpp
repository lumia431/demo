#define _CRT_SECURE_NO_WARNINGS
#define For(n) for(int index = 0;index < n;++index)
//#include "vld.h"
//#include "output_Container.h"
#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <algorithm>
#include <functional>
using namespace std;
struct CTest /*:public binary_function<int, int, void>*/
{
	void operator()(int i, int val) const
	{
		cout << i << " + " << val << " = " << i + val << endl;
	}
};
void obj3()
{
	vector<int> v = { 9,8,7,6,5,1,2,3,4 };
	//bind2nd和bind1nd过程一样
	for_each(v.begin(), v.end(), bind2nd(CTest(), 10));
	//for_each(v.begin(), v.end(), bind1st(CTest(),10)); 
}

int main() 
{
	obj3();
	system("pause");
	return 0;
}
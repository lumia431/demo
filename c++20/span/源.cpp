#include <span>
#include <iostream>
using namespace std;

void test(short* s) {
	cout << sizeof(s) << endl;
}

void test_span(span<short> sp) {
	cout << sp.size() << endl;
}

int main()
{
	short arr[] = {1,2,3,4,5};

	const std::span sp{ arr };

	for (auto x : sp) {
		std::cout << x << std::endl;
	}
	test((short*)arr);
	test_span(sp);

	//for (auto n{ sp.size() }; n != 2; --n) {
	//    std::cout << sp.last(n).data();
	//}
	system("pause");
}

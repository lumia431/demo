#include <iostream>

struct Storage {
	char      a;
	int       b;
	double    c;
	long long d;
};
//设置该类型的对齐方式，但不能比原来默认的8小
//若alignas小于自然对齐的最小单位，则被忽略
struct alignas(1) AlignasStorage {
	char      a;
	int       b;
	double    c;
	long long d;
};

int main() {
	//返回该类型的字节对齐方式
	std::cout << alignof(Storage) << std::endl;//8
	std::cout << sizeof(Storage) << std::endl;
	std::cout << alignof(AlignasStorage) << std::endl;//16
	std::cout << sizeof(AlignasStorage) << std::endl;

	return 0;
}
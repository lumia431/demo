//#pragma GCC optimize(2)
#include <iostream>
#include <time.h>
using namespace std;

//memset主要对数组进行赋值，且对int型数组，只能赋值为0和 - 1
//fill函数可以对数组或其他容器，进行赋值，值可以任意
//fill和memset都作用于int型数组上时，fill方法速度较慢
#define max 100000000+5
int a[max];
int main()
{
	time_t beg, end;

	cout << "---------------------------for\n";
	beg = clock();
	for (int i = 0; i < max; ++i) a[i] = 0;
	end = clock();
	cout << "test 1 cost: " << end - beg << "MS" << endl;
	beg = clock();
	for (int i = 0; i < max; ++i) a[i] = 0;
	end = clock();
	cout << "test 2 cost: " << end - beg << "MS" << endl;
	beg = clock();
	for (int i = 0; i < max; ++i) a[i] = 0;
	end = clock();
	cout << "test 3 cost: " << end - beg << "MS" << endl;
	beg = clock();
	for (int i = 0; i < max; ++i) a[i] = 0;
	end = clock();
	cout << "test 4 cost: " << end - beg << "MS" << endl;
	beg = clock();
	for (int i = 0; i < max; ++i) a[i] = 0;
	end = clock();
	cout << "test 5 cost: " << end - beg << "MS" << endl;
	beg = clock();
	for (int i = 0; i < max; ++i) a[i] = 0;
	end = clock();
	cout << "test 6 cost: " << end - beg << "MS" << endl;

	cout << "----------------register---for\n";
	beg = clock();
	for (register int i = 0; i < max; ++i) a[i] = 0;
	end = clock();
	cout << "test 1 cost: " << end - beg << "MS" << endl;
	beg = clock();
	for (register int i = 0; i < max; ++i) a[i] = 0;
	end = clock();
	cout << "test 2 cost: " << end - beg << "MS" << endl;
	beg = clock();
	for (register int i = 0; i < max; ++i) a[i] = 0;
	end = clock();
	cout << "test 3 cost: " << end - beg << "MS" << endl;
	beg = clock();
	for (register int i = 0; i < max; ++i) a[i] = 0;
	end = clock();
	cout << "test 4 cost: " << end - beg << "MS" << endl;
	beg = clock();
	for (register int i = 0; i < max; ++i) a[i] = 0;
	end = clock();
	cout << "test 5 cost: " << end - beg << "MS" << endl;
	beg = clock();
	for (register int i = 0; i < max; ++i) a[i] = 0;
	end = clock();
	cout << "test 6 cost: " << end - beg << "MS" << endl;

	cout << "---------------------------fill\n";
	beg = clock();
	fill(a, a + max, 0);
	end = clock();
	cout << "test 1 cost: " << end - beg << "MS" << endl;
	beg = clock();
	fill(a, a + max, 0);
	end = clock();
	cout << "test 2 cost: " << end - beg << "MS" << endl;
	beg = clock();
	fill(a, a + max, 0);
	end = clock();
	cout << "test 3 cost: " << end - beg << "MS" << endl;
	beg = clock();
	fill(a, a + max, 0);
	end = clock();
	cout << "test 4 cost: " << end - beg << "MS" << endl;
	beg = clock();
	fill(a, a + max, 0);
	end = clock();
	cout << "test 5 cost: " << end - beg << "MS" << endl;
	beg = clock();
	fill(a, a + max, 0);
	end = clock();
	cout << "test 6 cost: " << end - beg << "MS" << endl;

	cout << "---------------------------memset\n";
	beg = clock();
	memset(a, 0, sizeof(a));
	end = clock();
	cout << "test 1 cost: " << end - beg << "MS" << endl;
	beg = clock();
	memset(a, 0, sizeof(a));
	end = clock();
	cout << "test 2 cost: " << end - beg << "MS" << endl;
	beg = clock();
	memset(a, 0, sizeof(a));
	end = clock();
	cout << "test 3 cost: " << end - beg << "MS" << endl;
	beg = clock();
	memset(a, 0, sizeof(a));
	end = clock();
	cout << "test 4 cost: " << end - beg << "MS" << endl;
	beg = clock();
	memset(a, 0, sizeof(a));
	end = clock();
	cout << "test 5 cost: " << end - beg << "MS" << endl;
	beg = clock();
	memset(a, 0, sizeof(a));
	end = clock();
	cout << "test 6 cost: " << end - beg << "MS" << endl;
	return 0;
}
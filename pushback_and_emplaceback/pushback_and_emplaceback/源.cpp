#define _CRT_SECURE_NO_WARNINGS
#define For(n) for(int index = 0;index < n;++index)
//#include "vld.h"
//#include "output_Container.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <set>
#include <algorithm>
using namespace std;
class Person {

public:
	Person(int age) : _age(age) {
		cout << "Construct a person." << _age << endl;
	}

	Person(const Person &p) : _age(p._age) {
		cout << "Copy-Construct" << _age << endl;
	}

	Person(const Person &&p) noexcept : _age(p._age) {
		cout << "Move-Construct" << _age << endl;
	}
	int _age;
};
int main() {
	vector<Person> person;
	list<int>l{1,2,3,4,5};
	set<int>s{1, 2, 3, 4, 5, 6};
	std::reverse(l.begin(), l.end());
	auto p = l.begin();
	//auto p = Person(1); // >: Construct a person.1
	////person.push_back(Person(1));
	//auto a = move(p);
	//auto b = p._age;
	//person.emplace_back(move(p)); // >: Move-Construct1
	//person.emplace_back(2);
	/**
	 * >: Copy-Construct1 因为容器扩容，需要把前面的元素重新添加进来，因此需要拷贝
	 */
	system("pause");
}
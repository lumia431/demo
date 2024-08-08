#include <iostream>
#include <vector>
#include <array>
#include <forward_list>
#include <unordered_map>
#include <complex>
#include <ctime>
#include <list>
#include <deque>
using namespace std;
class Mystring
{
public:
	static size_t DCtor;
	static size_t Ctor;
	static size_t CCtor;
	static size_t CAsign;
	static size_t MCtor;
	static size_t MAsign;
	static size_t Dtor;
	Mystring() = default;
	Mystring(const char *p) :len_(strlen(p))
	{
		++Ctor;
		init_data(p);
	}
	Mystring(const Mystring &str) :
		len_(str.len_)
	{
		++CCtor;
		init_data(str.data_);
	}
	Mystring& operator = (Mystring&& str) noexcept
	{
		++MAsign;
		if (this != &str)
		{
			if (data_) delete data_;
			len_ = str.len_;
			data_ = str.data_;
			str.len_ = 0;
			str.data_ = NULL;
		}
		return *this;
	}
	Mystring& operator = (const Mystring& str) noexcept
	{
		++CAsign;
		if (this != &str)
		{
			if (data_) delete data_;//如果不是自己赋值自己，先把自己杀掉
			len_ = str.len_;
			init_data(str.data_);//然后做一次深拷贝
		}
		return *this;
	}
	Mystring(Mystring &&str) noexcept:
		len_(str.len_),data_(str.data_)
	{
		++MCtor;
		str.data_ = NULL;//切断与内存的联系，不清空的话后面该临时变量执行析构的时候会释放指向的内存
	}
	~Mystring()
	{
		++DCtor;
		if (data_)
		{
			delete data_;
		}
	}
private:
	char * data_;
	size_t len_;
	void init_data(const char *s)
	{
		data_ = new char[len_ + 1];//创建一个新的空间，深拷贝
		memcpy(data_, s, len_);
		data_[len_] = '\0';
	}
};
size_t Mystring::DCtor = 0;
size_t Mystring::Ctor = 0;
size_t Mystring::CCtor = 0;
size_t Mystring::CAsign = 0;
size_t Mystring::MCtor = 0;
size_t Mystring::MAsign = 0;
size_t Mystring::Dtor = 0;

int main()
{
	//deque <Mystring> v;
	//array<Mystring, 10>arr;//没有ctor,没有dtor
	//unordered_map<int, Mystring>m;
	//char buf[10];
	//clock_t timeNow = clock();
	//for (long i = 0; i < 3000000; i++)
	//{
	//	snprintf(buf, 10, "%d", rand());
	//	auto ite = v.end();
	//	v.insert(ite, Mystring(buf));//关系容器insert不需要指定位置，指定了也只是起到指示作用
	//}
	//cout << " time consuming =" << clock() - timeNow << "million-seconds" << endl;
	//cout << "Ctor" << Mystring::Ctor<<endl;
	//cout << "CCtor" << Mystring::CCtor<<endl;
	//cout << "MCtor" << Mystring::MCtor<<endl;
	//cout << "DCtor" << Mystring::DCtor<<endl;
	//hash<const char *>hashchar;
	//cout << hashchar("ads") << endl;
	//cout << v.size() << endl;
	//cout << hash<string>()("1") << endl;
	//tuple<string, int, int, complex<double>>tu;//64,使用了内存对齐
	//cout << sizeof(string) << endl;//string里面只有一个指针，大小为28
	//cout << sizeof(complex<double>) << endl;//16
	//cout << sizeof(tu) << endl;
	//cout <<  Mystring::Ctor<<endl;
	//cout << sizeof(v) << endl;
	//system("pause");
	vector< Mystring>v1;
	vector< Mystring>v2(100);
	vector< Mystring>v3(100);
	v1 = v2;
	cout << "CCtor is :" << Mystring::CCtor << endl;
	cout << "CAsign is :" << Mystring::CAsign<< endl;
	v1 = v3;
	cout << "CCtor is :" << Mystring::CCtor << endl;
	cout << "CAsign is :" << Mystring::CAsign << endl;
	return 0;
}
#include <boost/algorithm/string.hpp> 
#include <iostream> 
#include <string>
#include <vector>
#include <array>
using namespace std;
using namespace boost;
int main()
{
	string str1(" \[ hello ;]	world! ");
	trim(str1);//去除字符串首位的空白字符
	string str2 = trim_copy_if(std::string(",,,hell.o wor:ld"), is_any_of(" ,"));
	string str3 = trim_copy_if(std::string(",,,hell.o wor:ld"), is_any_of(":"));
	//也可以去首位的其他，只能是首位
	cout << (ends_with("hello world", "world") ? "true" : "false") << endl;
	cout << (contains("hello world", "world") ? "true" : "false") << endl;
	auto result = find_first("hello world", "world");
	if (result.empty())
		cout << "can't find result" << endl;
	else
		cout << result << endl;
	string str4("abc-*-ABC-*-aBc");
	string s("hello world");
	cout << s.substr(find_first(s, "wo").begin() - s.begin()) << endl;//substr只有一个数字表示直到结尾
	cout << s.substr(find_nth(s, "wo",2).begin() - s.begin()) << endl;
	cout << replace_all_copy(string("hello world"), "l", "-") << endl;
	cout << erase_all_copy(string("hello world"), "l") << endl;
	string str5("hello abc-*-ABC-*-aBc goodbye");
	vector<string> SplitVec;
	split(SplitVec, str5, is_any_of("-*"), token_compress_on);
	//token_compress_on参数，它可以吧连续多个分隔符当一个，默认没有打开
	std::array<string, 3> k = { "hello", "world", "123" };
	cout << join(k, "-");
}
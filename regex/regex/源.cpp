//
// 6.1.regex.cpp
// chapter 06 regular expression
// modern c++ tutorial
//
// created by changkun at changkun.de
// https://github.com/changkun/modern-cpp-tutorial
//
#include <iostream>
#include <regex>
#include <string.h>
using namespace std;
int packScript(std::string& script, std::vector<std::string>& queryRealList, std::vector<std::string>& queryHisList)
{
	smatch result;
	regex patternReal("GetValue\\(\"(.*?)\"\\)");	//匹配四个数字

	//迭代器声明
	string::const_iterator iterStart = script.begin();
	string::const_iterator iterEnd = script.end();
	string temp;
	while (regex_search(iterStart, iterEnd, result, patternReal))
	{
		temp = regex_replace(result[0].str(), patternReal, "$1");
		queryRealList.emplace_back(temp);
		iterStart = result[0].second;	//更新搜索起始位置,搜索剩下的字符串
	}
	return 0;
}

void f(void* s)
{
	auto p = (char**)s;
	cout << strlen(p[0]) << endl;
}
//int main()
//{
//	std::string timeA = "2020/10/21 11:39:52";
//	std::string timePatterA = "(20[0-9][0-9])/(0[0-9]|[0-9]|1[0-2])/([0-9]|[0-2][0-9]|3[0-1]) +([0-1][0-9]|2[0-3]):([0-5][0-9]):([0-5][0-9])";
//	std::regex expressA(timePatterA, std::regex::icase);
//	auto els_beginA = std::sregex_iterator(timeA.cbegin(), timeA.cend(), expressA);
//
//
//	std::string timeB = "11/0/2018 06:52:00.000";
//	std::string timePatterB = "^([0-9]|1[0-2])/([0-9]|[0-2][0-9]|3[0-1])/(20[0-9][0-9]) +([0-1][0-9]|2[0-3]):([0-5][0-9]):([0-5][0-9])";
//	std::regex expressB(timePatterB, std::regex::icase);
//	auto els_beginB = std::sregex_iterator(timeB.cbegin(), timeB.cend(), expressB);
//
//	std::string timeC = "7-0-2018 06:52:00.000";
//	std::string timePatterC = "(0[0-9]|[1-9]|1[0-2])-|/([0-9]|[0-2][0-9]|3[0-1])-(20[0-9][0-9]) +([0-1][0-9]|2[0-3]):([0-5][0-9]):([0-5][0-9])";
//	std::regex expressC(timePatterC, std::regex::icase);
//	auto els_beginC = std::sregex_iterator(timeC.cbegin(), timeC.cend(), expressC);
//
//	std::string timeD = "2020-10-21 11:39:52.000";
//	std::string timePatterD = "(20[0-9][0-9])-(0[0-9]|[1-9]|1[0-2])-([0-9]|[0-2][0-9]|3[0-1]) +([0-1][0-9]|2[0-3]):([0-5][0-9]):([0-5][0-9])";
//	std::regex expressD(timePatterD, std::regex::icase);
//	auto els_beginD = std::sregex_iterator(timeD.cbegin(), timeD.cend(), expressD);
//
//	auto els_end = std::sregex_iterator();
//	if (els_beginA == els_end)
//	{
//		std::cout << "error " << std::endl;
//	}
//
//	int year = std::atoi((*els_beginA)[1].str().c_str());
//	int month = std::atoi((*els_beginA)[2].str().c_str());
//	int day = std::atoi((*els_beginA)[3].str().c_str());
//	int hour = std::atoi((*els_beginA)[4].str().c_str());
//	int min = std::atoi((*els_beginA)[5].str().c_str());
//	int s = std::atoi((*els_beginA)[6].str().c_str());
//	std::cout << "OK" << std::endl;
//	system("pause");
//}
int main() {

	//std::regex pattern("^\\s*[s|S][e|E][l|L][e|E][c|C][t|T].*");
	//auto ccc = std::regex_match("seLect",pattern);
	//auto a = new char[6]{ 'a', 'a', 'a','\0' };
	//auto t = strstr(a, "\0");
	//auto b = new char[3] {'a', 'a', 'a'};
	//auto c = new char[3] {'a', 'a', 'a'};
	//char** abc = new char* [3];
	//abc[0] = a;
	//abc[1] = b;
	//abc[2] = c;
	//f(abc);
	//auto s1 = new char(*a);
	//delete a;
	//cout << s1 << endl;
	//cout << a << b << c << endl;
	//std::string fnames[] = { "foo.txt", "bar.txt", "test", "a0.txt", "AAA.txt" };
	//// In C++, `\` will be used as an escape character in the string. 
	//// In order for `\.` to be passed as a regular expression, 
	//// it is necessary to perform second escaping of `\`, thus we have `\\.`
	//std::regex txt_regex("[a-z]+\\.txt");
	//for (const auto &fname : fnames)
	//	std::cout << fname << ": " << std::regex_match(fname, txt_regex) << std::endl;

	//std::regex base_regex("([a-z]+)\\.txt");
	//std::smatch base_match;
	//for (const auto &fname : fnames) {
	//	if (std::regex_match(fname, base_match, base_regex)) {
	//		// the first element of std::smatch matches the entire string
	//		// the second element of std::smatch matches the first expression with brackets
	//		if (base_match.size() == 2) {
	//			std::string base = base_match[1].str();
	//			std::cout << "sub-match[0]: " << base_match[0].str() << std::endl;
	//			std::cout << fname << " sub-match[1]: " << base << std::endl;
	//		}
	//	}
	//}
	string str = "sadas d:       1 qwe: eqe::'ww";//6 16 23 26 34 6 8 5 1 6												//	0 14 19 20 																//  
	smatch result;
	regex pattern(":\\s*[a-zA-Z0-9]");	//匹配四个数字

	//迭代器声明
	string::const_iterator iterStart = str.begin();
	string::const_iterator iterEnd = str.end();
	string temp;
	while (regex_search(iterStart, iterEnd, result, pattern))
	{
		temp = result[0];
		cout << temp << " ";
		iterStart = result[0].second;	//更新搜索起始位置,搜索剩下的字符串
	}


	////迭代器声明
	//string::const_iterator iterStart = str.begin();
	//string::const_iterator iterEnd = str.end();
	//string temp;
	//std::vector<int> headIndex;
	//int pos = 0;
	//while (std::regex_search(iterStart, iterEnd, result, pattern))
	//{
	//	pos += result.position();
	//	headIndex.push_back(pos);
	//	iterStart = result[0].second;
	//	pos += 1;
	//}
	//if (headIndex.empty())
	//{
	//	return -1;
	//}
	//for (int i = 0; i < headIndex.size() - 1; i += 2)
	//{
	//	std::string s(str, headIndex[i] + 1, headIndex[i + 1] - headIndex[i]-1);
	//}
	//std::string timeD = "{\"time\":3680154727,\"id\":\"1025\",\"wave\":{-0.63,-543.2,9.2},}";
	//std::string timePatterD = "^\\{\"time\":([0-9]+),\"id\":(\"[0-9]+\"),\"wave\":\\{(.*)\\},\\}";
	//std::regex expressD(timePatterD, std::regex::icase);
	//auto els_beginD = std::sregex_iterator(timeD.cbegin(), timeD.cend(), expressD);

	//auto els_end = std::sregex_iterator();
	//if (els_beginD == els_end)
	//{
	//	std::cout << "error " << std::endl;
	//}

	//string s = (*els_beginD)[3].str();
	//string result;
	//int i = s.find_first_of(",");
	//if ( i!= string::npos)
	//{
	//	result = s.substr(0, 0);
	//}
	//else
	//{
	//	result = s;
	//}
	//cout << result;
 //	auto a = atof((*els_beginD)[1].str().c_str());
	//cout << a;
	//string s("function Main() return GetValue(\"wKgB4w_1_AAABc4 - eQqc.point0001\") + GetValue(\"wKgB4w_1_AAABc4 - eQqc.point0002\") end");
	//vector<string>v1;
	//vector<string>v2;
	//packScript(s,v1,v2);
	//string str("GetValue(\"asdasd\")");
	//regex pattern("GetValue\\(\".*\"\\)");
	//auto a = regex_match(str, pattern);
	//std::string str = "DB:5:2:16位无符号";
	//std::string patternElse = "(DB):([\\d]*):([\\d]*):(.*):([\\d]*)";
	//std::regex expressElse(patternElse, std::regex::icase);
	//auto els_begin = std::sregex_iterator(str.cbegin(), str.cend(), expressElse);
	//auto els_end = std::sregex_iterator();
	//if (els_begin != els_end)
	//{
	//	auto s1 = (*els_begin)[0].str();
	//	auto s2 = (*els_begin)[1].str();
	//	auto s3 = (*els_begin)[2].str();
	//	auto s4 = (*els_begin)[3].str();
	//	auto s5 = (*els_begin)[4].str();
	//	auto s6 = (*els_begin)[5].str();
	//}
	return 0;
}

#define For(n) for(int index = 0;index < n;++index)
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;
#define Jan 1
#define Feb 2
#define Mar 3
#define Apr 4
#define May 5
#define Jun 6
#define Jul 7
#define Aug 8
#define Sep 9
#define Oct 10
#define Nov 11
#define Dec 12
void SplitStr(const std::string& str, std::vector<std::string>& tokens, const std::string delim = "_")
{
	tokens.clear();

	auto start = str.find_first_not_of(delim, 0);       // 分割到的字符串的第一个字符
	auto position = str.find_first_of(delim, start);    // 分隔符的位置
	while (position != std::string::npos || start != std::string::npos) {
		// [start, position) 为分割下来的字符串
		tokens.emplace_back(std::move(str.substr(start, position - start)));
		start = str.find_first_not_of(delim, position);
		position = str.find_first_of(delim, start);
	}
}
vector<string> process(vector<string>dates)
{
	map<string, int> m;
	m.insert({ "Jan", 1 });
	m.insert({ "Feb", 2 });
	m.insert({ "Mar", 3 });
	m.insert({ "Apr", 4 });
	m.insert({ "May", 5 });
	m.insert({ "Jun", 6 });
	m.insert({ "Jul", 7 });
	m.insert({ "Aug", 8 });
	m.insert({ "Sep", 9 });
	m.insert({ "Oct", 10 });
	m.insert({ "Nov", 11 });
	m.insert({ "Dec", 12 });
	vector<string> res;
	for (auto& date : dates)
	{
		int day = 0;
		int mon = 0;
		int year = 0;
		vector<string> v;
		SplitStr(date, v, " ");
		sscanf_s(v[0].c_str(), "%dth",&day);
		mon = m[v[1]];
		sscanf_s(v[2].c_str(), "%d", &year);
		char temp[128];
		sprintf(temp, "%4d-%2d-%2d",year,mon,day);
		res.push_back(temp);
	}
}

vector<int> MyGet(vector<int>arr, long k)
{
	map<int, int> v2;
	vector<int> v;
	int len = arr.size();
	k -= 1;
	sort(arr.begin(), arr.end());
	int num = 1;
	int last = -1;
	for (int i = 0; i < len; ++i)
	{
		if (i == 0)
		{
			last = arr[i];
			continue;
		}
		if (arr[i] == last)
		{
			++num;
		}
		else
		{
			v2.insert({ last, num });
			last = arr[i];
			num = 1;
		}
	}
	v2.insert({ last ,num });
	int div = k / len;
	int remain = k % len / v2[arr[div]];
	v.push_back(arr[div]);
	v.push_back(arr[remain]);
	return v;
}
int main() {
	vector<int> v{ 2,2,1 };
	auto v2 = MyGet(v, 5);
	system("pause");
	return 0;
}
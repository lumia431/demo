#define _CRT_SECURE_NO_WARNINGS
#define For(n) for(int index = 0;index < n;++index)
//#include "vld.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "nlohmann/json.hpp"
using namespace std;
using namespace nlohmann;
struct MyJson
{
	string t;
	string k;
	string d;
};
int main()
{
	ifstream ifs("./wolong.json");
	string str;
	string lineStr;
	while (getline(ifs, lineStr))
	{
		str += lineStr;
	}
	try
	{
		nlohmann::json jsonData = nlohmann::json::parse(str);
		for (auto iter = jsonData.begin(); iter != jsonData.end(); ++iter)
		{
			if (iter.key() == "meter")
			{
				auto jValues = jsonData["meter"].front()["values"];

				//for (auto iter = jValues.begin(); iter != jValues.end(); ++iter)
				//{
				//	cout << iter.key() << "\t" << iter.value() << endl;
				//}
			}
		}
	}
	catch (const std::exception&e)
	{
		cout << e.what() << endl;
	}

	system("pause");
	return 0;
}
#include <unordered_set>
#include <iostream>
#include <string>
using namespace std;
struct str_hash {
	size_t operator()(const string& str) const
	{
		unsigned long __h = 0;
		for (size_t i = 0; i < str.size(); i++)
			__h = 5 * __h + str[i];
		return size_t(__h);
	}
};
int main()
{
	unordered_set<string, str_hash>s{"as1","sd2","w3","q4","f5"};
	int bucket = s.load_factor();
	str_hash a;
	size_t b = a("sad");
	return 0;
}
#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>
#include <thread>
#include <iostream>
#include <assert.hpp>
#include <map>
using namespace std;
int test(int i)
{
	return i;
}

int main(int, char*[]) {
	std::cout << "=== passing arguments to scripts ===" << std::endl;

	sol::state lua;
	lua.open_libraries();
	lua.set_function("GetValue",
		[&](const std::string& name)
		{

			int ret = 1;
			if (ret < 0)
			{
				throw ret;
			}
			return obj.getvalue();
		});
	try
	{
		lua.script("function Main() \
		
		a = \"abc\"..3 \
		b = a..\"def\" \
		print(a) \
		return b \
		end");
		lua.script("function Main() 
		return math.pi 
		end");
		lua.script("function Main() \
		a , b = 0,1  \
		while( a ~= 10 ) \
			do \
				b = b+b \
				a = a+1 \
			end \
		return b \
		end ");
		//lua.script("function f(x) 
		//	return x * 2 
		//	end 
		//	function Main() 
		//	b = 1 
		//	for i = 0, 9  do b=f(b) end 
		//	return b 
		//	end");
		//lua.script("function Main() \
		//	b,result = 100,0 \
		//	b += 1 \
		//	if(b > 100) \
		//	then \
		//		result = b-100 \
		//	elseif(b < 100) \
		//	then \
		//		result = 100 - b \
		//	else \
		//		result = b \
		//	end \
		//	return result \
		//end");
		//string s("function Main() 
		//	a = true 
		//	b = false 
		//	if (a and b) 
		//		then 
		//		return 1 
		//		end 
		//	if (a or b) 
		//		then 
		//		return 0 
		//		end 
		//	end");
		sol::function mainFun = lua["Main"];
		string b = mainFun();
		std::cout << b << std::endl;
	}
	catch (const std::exception&e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}

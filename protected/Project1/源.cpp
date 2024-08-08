#include <iostream>  
#include "execp.h"
using namespace std;


int main()
{
	SQLException s;
	s.setErrorCtx((void*)"danger");
	try
	{
		throw s;
	}
	catch (SQLException e)
	{
		cout << e.what() << endl;
	}
	auto a = 0;
}
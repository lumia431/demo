#define _CRT_SECURE_NO_WARNINGS
#define For(n) for(int index = 0;index < n;++index)
#include <iostream>
#include <string>
#include <vector>
#include "CollectMonitor.h"
using namespace std;
int main()
{
	srand(time(NULL));
	CollectMonitor monitor;
	if (monitor.Init() < 0)
	{
		cout << "init error" << endl;
		system("pause");
		return 0;
	}
	monitor.Run();
	system("pause");
	return 0;
}
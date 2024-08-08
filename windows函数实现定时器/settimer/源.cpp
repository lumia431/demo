#include<iostream>
#include<Windows.h>

using namespace std;

void Resp_fun()
{
	cout << "定时一次!\n";
}

int main()
{
	DWORD dwTimerId;
	dwTimerId = SetTimer(NULL, 1, 10000, NULL);
	MSG msg;
	unsigned int i = 0;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (i > 9)
		{
			KillTimer(NULL, dwTimerId);
			dwTimerId = SetTimer(NULL, 1, 1000, NULL);
			break;
		}
		else if (msg.message == WM_TIMER)
		{
			Resp_fun();
		}
		++i;
	}
	return 0;
}
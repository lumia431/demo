#include "TrendDBCalc.h"
#include "stdafx.h"
#include <QtWidgets/QApplication>
#include <tchar.h> 
//#include "vld.h"

BOOL Reg_Judge()
{
	HKEY key;
	LPBYTE path_Get = new BYTE[254];
	DWORD type = REG_SZ;
	DWORD dwBytes = 254;
	if (RegOpenKeyEx(HKEY_CURRENT_USER, _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"), 0, KEY_READ, &key) == ERROR_SUCCESS)
	{
		if (RegQueryValueEx(key, _T("TrendDBCalc"), 0, &type, path_Get, &dwBytes) == ERROR_SUCCESS)

		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return true;
}

BOOL Reg_CurrentUser(char *lpszFileName, char *lpszValueName)
{
	WCHAR wFileName[256];
	WCHAR wValueName[256];
	memset(wFileName, 0, sizeof(wFileName));
	memset(wValueName, 0, sizeof(wValueName));
	MultiByteToWideChar(CP_ACP, 0, lpszFileName, strlen(lpszFileName) + 1, wFileName,
		sizeof(wFileName) / sizeof(wFileName[0]));
	MultiByteToWideChar(CP_ACP, 0, lpszValueName, strlen(lpszValueName) + 1, wValueName,
		sizeof(wValueName) / sizeof(wValueName[0]));
	LPCTSTR lpSubKey = _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run");
	HKEY hKey;

	if (ERROR_SUCCESS != ::RegOpenKeyEx(HKEY_CURRENT_USER, lpSubKey, 0, KEY_WRITE, &hKey))
	{
		return FALSE;
	}

	if (ERROR_SUCCESS != ::RegSetValueEx(hKey, wValueName, 0, REG_SZ, (BYTE *)wFileName, (MAX_PATH)))
	{
		return FALSE;
	}

	::RegCloseKey(hKey);

	return TRUE;
}
int main(int argc, char *argv[])
{
	if (!Reg_Judge())
	{
		char path[MAX_PATH];
		getcwd(path, MAX_PATH);
		char pathSuff[20] = "\\TrendDBCalc.exe";
		strcat(path, pathSuff);
		char name[20] = "TrendDBCalc";
		if (FALSE == Reg_CurrentUser(path, name))
		{
			printf("Reg_CurrentUser Error!\n");
		}
	}
    QApplication a(argc, argv);
    TrendDBCalc calc;
	calc.show();
    return a.exec();
}

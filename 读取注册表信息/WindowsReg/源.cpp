#include <stdio.h>
#include <Windows.h>

void Enum_Regedit(const char *Reg_Path)
{
	HKEY hKey = NULL;
	DWORD dwType = 0;
	char szValueName[MAXBYTE], szValueKey[MAXBYTE] = { 0 };
	DWORD dwBufferSize = MAXBYTE, dwKeySize = MAXBYTE;

	// 打开注册表项
	LONG lRet = RegOpenKeyEx(HKEY_CURRENT_USER, Reg_Path, 0, KEY_ALL_ACCESS, &hKey);

	int index = 0;
	while (1)
	{
		// 枚举注册表键项
		lRet = RegEnumValue(hKey, index, szValueName, &dwBufferSize, NULL,
			&dwType, (unsigned char *)szValueKey, &dwKeySize);

		if (lRet == ERROR_NO_MORE_ITEMS)
			break;

		printf("ID: %3d --> 名称: %30s --> 键: %-50s --> 值: %d \n", index, szValueName, szValueKey, dwKeySize);

		ZeroMemory(szValueKey, MAXBYTE);
		ZeroMemory(szValueKey, MAXBYTE);
		dwBufferSize = MAXBYTE;
		dwKeySize = MAXBYTE;
		index++;
	}
	RegCloseKey(hKey);
}

int main(int argc, char *argv[])
{
	Enum_Regedit("Software\\Microsoft\\Windows\\CurrentVersion\\Run\\");

	system("pause");
	return 0;
}
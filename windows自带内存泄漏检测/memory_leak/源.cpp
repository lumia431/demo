#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#ifdef _DEBUG
#define DEBUG_CLIENTBLOCK   new( _CLIENT_BLOCK, __FILE__, __LINE__)
#else
#define DEBUG_CLIENTBLOCK   new( _CLIENT_BLOCK, __FILE__, __LINE__)
#endif
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#ifdef _DEBUG
#define new DEBUG_CLIENTBLOCK
#endif
#define new DEBUG_CLIENTBLOCK
using namespace std;
void Exit()
{
	int i = _CrtDumpMemoryLeaks();
}
int main()
{
	//ifstream fin("input.txt"); // 已有输入文件
	//ofstream fout("output.txt"); //输出文件
	//streambuf *cinbackup;
	//streambuf *coutbackup;
	//coutbackup = cout.rdbuf(fout.rdbuf()); //用 rdbuf() 重新定向
	//cinbackup = cin.rdbuf(fin.rdbuf()); //用 rdbuf() 重新定向
	atexit(Exit);
	int* p = new int();
	return 0;
}
#include <iostream>
#include <windows.h>
#include <psapi.h>
#pragma comment(lib,"psapi.lib")
using namespace std;
void showMemoryInfo(void)
    {
    HANDLE handle=GetCurrentProcess();
    PROCESS_MEMORY_COUNTERS pmc;
    GetProcessMemoryInfo(handle,&pmc,sizeof(pmc));
    cout<<"内存使用:"<<pmc.WorkingSetSize/1000 <<"K/"<<pmc.PeakWorkingSetSize/1000<<"K + "<<pmc.PagefileUsage/1000 <<"K/"<<pmc.PeakPagefileUsage/1000 <<"K"<<endl;
    }
int main(int argc,char* argv)
    {
    showMemoryInfo();
    cout<<"回收所有可回收的内存"<<endl;
    EmptyWorkingSet(GetCurrentProcess());
    showMemoryInfo();
    cout<<"开始动态分配内存"<<endl;
    char* buf[5];
    for(int i=0;i<sizeof(buf)/sizeof(char*);i++)
        {
        buf[i]=new char[102400];
        showMemoryInfo();
        }
    cout<<"开始释放内存"<<endl;
    for(int i=0;i<sizeof(buf)/sizeof(char*);i++)
        {
        delete buf[i];
        buf[i]=NULL;
        showMemoryInfo();
        }
    cout<<"回收所有可回收的内存"<<endl;
    EmptyWorkingSet(GetCurrentProcess());
    showMemoryInfo();
    return 0;
    }
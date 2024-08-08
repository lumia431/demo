#define _AFXDLL
#define _CRT_SECURE_NO_WARNINGS
#define For(n) for(int index = 0;index < n;++index)
#include <afxwin.h>
#include <stdio.h>
#include "MyService.h"
#include <direct.h>
#include <DbgHelp.h>
#include <iostream>
#include <thread>
#include <time.h>
#include <afxinet.h>
#include <Sensapi.h>
#include <math.h>
#include "afxcmn.h"
#include <string>
#include <vector>
#include <fstream>
#include <atlstr.h>
#include <algorithm>
#include "pugixml.hpp"
#include "simple_web_server/client_http.hpp"
#pragma comment(lib, "Sensapi.lib")
#pragma comment( lib, "Dbghelp.lib" )
using namespace std;

void ServiceRun(DWORD argc, CHAR *argv[]);
void ServiceStop(void);
DWORD m_mainThreadID = 0;
HANDLE g_hInstance = NULL;
std::string g_instanceName = "MyTest";

struct StockStruct
{
	double fOpen;
	double fClose;
	double fCurrent;
	double fTop;
	double fBottom;

	double fDealSum;
	double fMoney;

	double fBAmount1;
	double fBuy1;
	double fBAmount2;
	double fBuy2;
	double fBAmount3;
	double fBuy3;
	double fBAmount4;
	double fBuy4;
	double fBAmount5;
	double fBuy5;

	double fSAmount1;
	double fSell1;
	double fSAmount2;
	double fSell2;
	double fSAmount3;
	double fSell3;
	double fSAmount4;
	double fSell4;
	double fSAmount5;
	double fSell5;

	long dTime;
	double rate;
	string abbrName;
	CString strName;
	CString strCode;
	CString strDate;
	CString strTime;

	StockStruct(void)
	{
		Reset();
	}

	void Reset(void)
	{
		fOpen = 0.0;
		fClose = 0.0;
		fCurrent = 0.0;
		fTop = 0.0;
		fBottom = 0.0;

		fDealSum = 0.0;
		fMoney = 0.0;

		fBAmount1 = 0.0;
		fBuy1 = 0.0;
		fSAmount1 = 0.0;
		fSell1 = 0.0;
		fBAmount2 = 0.0;
		fBuy2 = 0.0;
		fSAmount2 = 0.0;
		fSell2 = 0.0;
		fBAmount3 = 0.0;
		fBuy3 = 0.0;
		fSAmount3 = 0.0;
		fSell3 = 0.0;
		fBAmount4 = 0.0;
		fBuy4 = 0.0;
		fSAmount4 = 0.0;
		fSell4 = 0.0;
		fBAmount5 = 0.0;
		fBuy5 = 0.0;
		fSAmount5 = 0.0;
		fSell5 = 0.0;

		strName.Empty();
		strCode.Empty();
		strDate.Empty();
		strTime.Empty();
	}
};
vector<StockStruct> g_ssInfo;
vector<string> g_vecStockList;
vector<string> g_abbrList;

void SplitStr(const std::string& str, std::vector<std::string>& tokens, const std::string delim = "_")
{
	tokens.clear();

	auto start = str.find_first_not_of(delim, 0);       // 分割到的字符串的第一个字符
	auto position = str.find_first_of(delim, start);    // 分隔符的位置
	while (position != std::string::npos || start != std::string::npos) {
		// [start, position) 为分割下来的字符串
		tokens.emplace_back(std::move(str.substr(start, position - start)));
		start = str.find_first_not_of(delim, position);
		position = str.find_first_of(delim, start);
	}
}

int ReadCfg()
{
	ifstream ifs("D:\\config.ini");
	string str;
	if (!ifs)
	{
		return -1;
	}
	while (getline(ifs, str))
	{
		vector<string>v;
		SplitStr(str, v, ",");
		g_vecStockList.emplace_back(v[0]);
		g_abbrList.emplace_back(v[1]);
	}
}

long TimeFronStr(const CString &str)
{
	long p1 = str.Find(_T(':'));
	if (p1 == -1)
	{
		return 0;
	}

	long p2 = str.Find(_T(':'), p1 + 1);
	if (p2 == -1)
	{
		return 0;
	}

	CString h = str.Mid(0, p1);
	CString m = str.Mid(p1 + 1, p2 - p1 - 1);
	CString s = str.Mid(p2 + 1, str.GetLength() - p2 - 1);

	long dtime = atoi(h) * 10000 + atoi(m) * 100 + atoi(s);

	return dtime;
}

void ParseRealtimeInfo(const CString &strInfo, vector<StockStruct> &ssInfo)
{
	ssInfo.clear();

	long pos = 0, pos2 = 0;
	long iCounter = 0;
	StockStruct ssOne;
	for (long i = 0; i < strInfo.GetLength(); i++)
	{
		if (strInfo[i] == _T('='))
		{
			ssOne.strCode = strInfo.Mid(i - 8, 8);
		}

		if (strInfo[i] == _T('"'))
		{
			pos2 = i;
		}

		if (strInfo[i] == _T(','))
		{
			switch (iCounter++)
			{
			case 0:
			{
				ssOne.strName = strInfo.Mid(pos2 + 1, i - pos2 - 1);
				break;
			}
			case 1:
			{
				ssOne.fOpen = atof(strInfo.Mid(pos + 1, i - pos - 1));
				break;
			}
			case 2:
			{
				ssOne.fClose = atof(strInfo.Mid(pos + 1, i - pos - 1));
				break;
			}
			case 3:
			{
				ssOne.fCurrent = atof(strInfo.Mid(pos + 1, i - pos - 1));
				break;
			}
			case 4:
			{
				ssOne.fTop = atof(strInfo.Mid(pos + 1, i - pos - 1));
				break;
			}
			case 5:
			{
				ssOne.fBottom = atof(strInfo.Mid(pos + 1, i - pos - 1));
				break;
			}
			case 6:
			{
				ssOne.fBuy1 = atof(strInfo.Mid(pos + 1, i - pos - 1));
				break;
			}
			case 7:
			{
				ssOne.fSell1 = atof(strInfo.Mid(pos + 1, i - pos - 1));
				break;
			}
			case 8:
			{
				ssOne.fDealSum = atof(strInfo.Mid(pos + 1, i - pos - 1));
				break;
			}
			case 9:
			{
				ssOne.fMoney = atof(strInfo.Mid(pos + 1, i - pos - 1));
				break;
			}
			case 10:
			{
				ssOne.fBAmount1 = atof(strInfo.Mid(pos + 1, i - pos - 1));
				break;
			}
			case 11:
			{
				ssOne.fBuy1 = atof(strInfo.Mid(pos + 1, i - pos - 1));
				break;
			}
			case 12:
			{
				ssOne.fBAmount2 = atof(strInfo.Mid(pos + 1, i - pos - 1));
				break;
			}
			case 13:
			{
				ssOne.fBuy2 = atof(strInfo.Mid(pos + 1, i - pos - 1));
				break;
			}
			case 14:
			{
				ssOne.fBAmount3 = atof(strInfo.Mid(pos + 1, i - pos - 1));
				break;
			}
			case 15:
			{
				ssOne.fBuy3 = atof(strInfo.Mid(pos + 1, i - pos - 1));
				break;
			}
			case 16:
			{
				ssOne.fBAmount4 = atof(strInfo.Mid(pos + 1, i - pos - 1));
				break;
			}
			case 17:
			{
				ssOne.fBuy4 = atof(strInfo.Mid(pos + 1, i - pos - 1));
				break;
			}
			case 18:
			{
				ssOne.fBAmount5 = atof(strInfo.Mid(pos + 1, i - pos - 1));
				break;
			}
			case 19:
			{
				ssOne.fBuy5 = atof(strInfo.Mid(pos + 1, i - pos - 1));
				break;
			}
			case 20:
			{
				ssOne.fSAmount1 = atof(strInfo.Mid(pos + 1, i - pos - 1));
				break;
			}
			case 21:
			{
				ssOne.fSell1 = atof(strInfo.Mid(pos + 1, i - pos - 1));
				break;
			}
			case 22:
			{
				ssOne.fSAmount2 = atof(strInfo.Mid(pos + 1, i - pos - 1));
				break;
			}
			case 23:
			{
				ssOne.fSell2 = atof(strInfo.Mid(pos + 1, i - pos - 1));
				break;
			}
			case 24:
			{
				ssOne.fSAmount3 = atof(strInfo.Mid(pos + 1, i - pos - 1));
				break;
			}
			case 25:
			{
				ssOne.fSell3 = atof(strInfo.Mid(pos + 1, i - pos - 1));
				break;
			}
			case 26:
			{
				ssOne.fSAmount4 = atof(strInfo.Mid(pos + 1, i - pos - 1));
				break;
			}
			case 27:
			{
				ssOne.fSell4 = atof(strInfo.Mid(pos + 1, i - pos - 1));
				break;
			}
			case 28:
			{
				ssOne.fSAmount5 = atof(strInfo.Mid(pos + 1, i - pos - 1));
				break;
			}
			case 29:
			{
				ssOne.fSell5 = atof(strInfo.Mid(pos + 1, i - pos - 1));
				break;
			}
			case 30:
			{
				ssOne.strDate = strInfo.Mid(pos + 1, i - pos - 1);
				break;
			}
			case 31:
			{
				ssOne.strTime = strInfo.Mid(pos + 1, i - pos - 1);
				break;
			}
			default:
				break;
			}

			pos = i;
		}

		if (strInfo[i] == _T(';'))
		{
			ssOne.dTime = TimeFronStr(ssOne.strTime);
			ssInfo.push_back(ssOne);
			ssOne.Reset();
			iCounter = 0;
		}
	}
}

BOOL GetRealtimeInfo(const CString &url, vector<StockStruct> &ssInfo)
{
	CInternetSession session;
	CHttpFile* fileGet;
	try
	{
		session.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, 3000);      // 3秒的连接超时
		session.SetOption(INTERNET_OPTION_SEND_TIMEOUT, 2000);           // 2秒的发送超时
		session.SetOption(INTERNET_OPTION_RECEIVE_TIMEOUT, 7000);        // 7秒的接收超时
		session.SetOption(INTERNET_OPTION_CONNECT_RETRIES, 1);          // 1次重试
		fileGet = (CHttpFile*)session.OpenURL(url);
	}
	catch (CInternetException *e)
	{
		//清理资源
		session.Close();
		fileGet = 0;

		//停止，并恢复更新按钮
		//显示错误
		TCHAR szError[200];
		e->GetErrorMessage(szError, 200);
		e->Delete();
		return FALSE;
		//g_bNetIsOk = 0;
		//throw;
	}

	if (fileGet)
	{
		//g_bNetIsOk = 1;
		DWORD dwStatus;
		DWORD dwBuffLen = sizeof(dwStatus);
		BOOL bSuccess = fileGet->QueryInfo(HTTP_QUERY_STATUS_CODE | HTTP_QUERY_FLAG_NUMBER, &dwStatus, &dwBuffLen);

		//连接成功
		if (bSuccess && dwStatus >= 200 && dwStatus < 300)
		{
			//查询文件长度
			CString info;
			fileGet->QueryInfo(HTTP_QUERY_CONTENT_LENGTH, info);
			long fileLen = (long)atoi(info);

			const long blen = 1024 * 5;
			char buf[blen] = { 0 };
			CString downloadInfo;

			long readLen = 0, alreadyRead = 0;
			CString strStockInfo;
			while ((readLen = fileGet->Read(buf, blen - 1)))
			{
				alreadyRead += readLen;

				TCHAR wbuf[blen] = { 0 };
				//MultiByteToWideChar(CP_ACP, 0, buf, readLen, (LPWSTR)wbuf, readLen);
				strStockInfo += buf;
				//超过文件长度或者用户停止则退出
				if (alreadyRead >= fileLen)
				{
					break;
				}
			}

			ParseRealtimeInfo(strStockInfo, ssInfo);
		}
		else
		{
			fileGet->Close();
			delete fileGet;
			session.Close();
		}
	}
	session.Close();
	return TRUE;
}

void CreateDumpFile(LPCSTR lpstrDumpFilePathName, EXCEPTION_POINTERS *pException)
{
	// 创建Dump文件  
	//  
	HANDLE hDumpFile = CreateFile(lpstrDumpFilePathName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	// Dump信息  
	//  
	MINIDUMP_EXCEPTION_INFORMATION dumpInfo;
	dumpInfo.ExceptionPointers = pException;
	dumpInfo.ThreadId = GetCurrentThreadId();
	dumpInfo.ClientPointers = TRUE;

	// 写入Dump文件内容  
	//  
	MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hDumpFile, MiniDumpNormal, &dumpInfo, NULL, NULL);

	CloseHandle(hDumpFile);
}
LONG ApplicationCrashHandler(EXCEPTION_POINTERS *pException)
{
	TCHAR file[MAX_PATH + 1] = { 0 };
	GetModuleFileName(NULL, file, MAX_PATH);
	std::string path = file;
	UINT pos = path.rfind('.', path.length());
	path.erase(pos);
	path += _T(".dmp");

	CreateDumpFile(path.c_str(), pException);
	// 这里弹出一个错误对话框并退出程序  
	//  
	//FatalAppExit(-1,  _T("*** Unhandled Exception! ***"));  

	return EXCEPTION_EXECUTE_HANDLER;
}
void ServiceRun(DWORD argc, CHAR *argv[])
{
	m_mainThreadID = GetCurrentThreadId();
	(void)MyService::ReportStatusToSCMgr(SERVICE_RUNNING, NO_ERROR, 0);

	// 设置处理Unhandled Exception的回调函数  
	SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)ApplicationCrashHandler);
	std::thread thr([]() {
		Sleep(8000);
		ReadCfg();
		while (1)
		{
			ofstream ofs("D:\\DA202106210001_6_55000_25000.txt", ios::trunc);
			char ch[10] = {};
			time_t tNow = time(NULL);
			strftime(ch, 10, "%a", localtime(&tNow));
			string str(ch);
			if (str == "Sat" || str == "Sun")
			{
				ofs << "week = " << str << endl;
				ofs.close();
				Sleep(1000);
				continue;
			}
			else
			{
				char ch[10] = {};
				time_t tNow = time(NULL);
				strftime(ch, 10, "%H", localtime(&tNow));
				string str(ch);
				int hour = atoi(str.c_str());
				if (hour < 9 || hour > 15 || hour == 12)
				{
					ofs << "hour = " << hour << endl;
					ofs.close();
					Sleep(1000);
					continue;
				}
				if (hour == 9)
				{
					char ch[10] = {};
					time_t tNow = time(NULL);
					strftime(ch, 10, "%M", localtime(&tNow));
					string str(ch);
					int minite = atoi(str.c_str());
					if (minite < 30)
					{
						ofs << "minute = " << minite << endl;
						ofs.close();
						Sleep(1000);
						continue;
					}
				}
				if (hour == 11)
				{
					char ch[10] = {};
					time_t tNow = time(NULL);
					strftime(ch, 10, "%M", localtime(&tNow));
					string str(ch);
					int minite = atoi(str.c_str());
					if (minite > 30)
					{
						ofs << "minute = " << minite << endl;
						ofs.close();
						Sleep(1000);
						continue;
					}
				}
				CString strUrl = _T("http://hq.sinajs.cn/list=");
				long size = (long)g_vecStockList.size();
				long iCounter = 0;
				for (long i = 0; i < size; i++)
				{

					CString s = iCounter > 0 ? _T(",") : _T("");
					strUrl += s + CString(g_vecStockList[i].c_str());
					iCounter++;
				}
				g_ssInfo.clear();
				GetRealtimeInfo(strUrl, g_ssInfo);
				int stokeSize = g_abbrList.size();
				For(2500)
				{
					ofs << 12.0 + (rand() % 1000 / 1000.0) << endl;
				}
				for (int i = 0; i < stokeSize; i++)
				{
					g_ssInfo[i].abbrName = g_abbrList[i];
					double diff = g_ssInfo[i].fCurrent - g_ssInfo[i].fClose;
					double rate = diff / g_ssInfo[i].fClose * 100.0 + 10;
					if (rate < 0)
					{
						rate = 0;
					}
					g_ssInfo[i].rate = rate;
					ofs << rate << endl;
				}
				std::sort(g_ssInfo.begin(), g_ssInfo.end(), [](const StockStruct&s1, const StockStruct&s2) {
					return s1.rate >= s2.rate;
				});

				pugi::xml_document doc;
				auto child = doc.append_child("Sushine_ZD_Tcp");
				child.append_attribute("tcp_port").set_value(8888);
				child.append_attribute("timeout").set_value(120);
				auto fileLogChild = child.append_child("FileLog");
				fileLogChild.append_attribute("log_level").set_value("Warning");
				auto transChild = child.append_child("KafkaConfig");
				transChild.append_attribute("enable").set_value(false);
				transChild.append_attribute("url").set_value("127.0.0.1:9092");
				transChild.append_attribute("topic").set_value("topic");
				auto trendDBChild = child.append_child("TrendDBConfig");
				trendDBChild.append_attribute("enable").set_value(false);
				trendDBChild.append_attribute("addr").set_value("127.0.0.1");
				trendDBChild.append_attribute("port").set_value(20010);
				auto mqttChild = child.append_child("MqttConfig");
				mqttChild.append_attribute("addr").set_value("127.0.0.1:1883");
				mqttChild.append_attribute("topic").set_value("sys/");
				mqttChild.append_attribute("enable").set_value(false);
				auto warnChild = child.append_child("SushineWarnUrl");
				warnChild.append_attribute("enable").set_value(false);
				warnChild.append_attribute("url").set_value("127.0.0.1:1234");
				auto pgChild = child.append_child("PgsqlConfig");
				pgChild.append_attribute("enable").set_value(false);
				pgChild.append_attribute("addr").set_value("127.0.0.1");
				pgChild.append_attribute("port").set_value("5432");
				pgChild.append_attribute("username").set_value("postgres");
				pgChild.append_attribute("password").set_value("postgres");
				pgChild.append_attribute("db_name").set_value("sushine_db");
				pgChild.append_attribute("charset").set_value("utf-8");
				auto jsonChild = child.append_child("JsonConfigPaths");
				srand(time(NULL));
				For(stokeSize)
				{
					string str = "DA202107100";
					float rate = g_ssInfo[index].rate;
					if (rate < 10)
					{
						str += "0";
					}
					string abbrName = g_ssInfo[index].abbrName;
					if(abbrName.empty())
						continue;
					char buf[10] = {};
					sprintf(buf, "%.1f", rate);
					str += buf;
					str.erase(str.end() - 2);
					string jsonPath = "./config/" + str;
					auto jsonTemp = jsonChild.append_child("JsonConfigPath");
					jsonTemp.append_attribute("json_path").set_value(jsonPath.c_str());
					jsonTemp.append_attribute("model_id").set_value(str.c_str());
					jsonTemp.append_attribute("model_desc").set_value(abbrName.c_str());
					jsonTemp.append_attribute("sampleRate").set_value(5120);
					jsonTemp.append_attribute("dataSize").set_value(8192);
					jsonTemp.append_attribute("log_flag").set_value(true);
				}
				auto saveResult = doc.save_file("D:\\DA202105200001.json");
				For(2500)
				{
					ofs << 12.0 + (rand() % 1000 / 1000.0) << endl;
				}
				ofs.close();
				//让该线程睡眠xx秒
				::Sleep(1000);
			}
		}
		});
	thr.detach();
	const int TIME_WAIT = 5000;
	MSG msg;
	PeekMessage(&msg, NULL, WM_USER, WM_USER, PM_NOREMOVE);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void ServiceStop(void)
{
	if (!PostThreadMessage(m_mainThreadID, WM_QUIT, NULL, NULL))
	{
		return;
	}
}
int main(int argc, char *argv[])
{
	MyService::ServiceInfo servInfo;
	MyService servCtrl;

	servInfo.servName = "idb";
	servInfo.dispName = "idb";
	servInfo.servDesc = "idb test";
	servInfo.funcStart = ServiceRun;
	servInfo.funcStop = ServiceStop;
	//Sleep(10000);
	if (servCtrl.SetServiceInfo(servInfo) == 0)
	{
		(void)servCtrl.SerivceEntry(argc, argv);
	}
	return 0;
	//int nRetCode = 0;

	//HMODULE hModule = GetModuleHandle(NULL);

	//// 唯一实例
	//std::string instanceName = g_instanceName;
	//HANDLE hEvent = CreateEvent(NULL, FALSE, FALSE, instanceName.c_str());

	//if (GetLastError() == ERROR_ALREADY_EXISTS)
	//{
	//	CloseHandle(hEvent);

	//	return NULL;
	//}
	//if (hEvent == NULL)
	//{
	//	return 0;
	//}

	//if (hModule != NULL)
	//{
	//	// 初始化 MFC 并在失败时显示错误
	//	if (!AfxWinInit(hModule, NULL, GetCommandLine(), 0))
	//	{
	//		// TODO: 更改错误代码以符合您的需要
	//		printf("错误: MFC 初始化失败\n");
	//		nRetCode = 1;
	//	}
	//	else
	//	{
	//		// TODO: 在此处为应用程序的行为编写代码。
	//		MyService::ServiceInfo servInfo;
	//		MyService servCtrl;

	//		servInfo.servName = "Service";
	//		servInfo.dispName = "Myservice";
	//		servInfo.servDesc = "Myservice test";
	//		servInfo.funcStart = ServiceRun;
	//		servInfo.funcStop = ServiceStop;

	//		if (servCtrl.SetServiceInfo(servInfo) == 0)
	//		{
	//			(void)servCtrl.SerivceEntry(argc, argv);
	//		}
	//	}
	//}
	//else
	//{
	//	printf("错误: GetModuleHandle 失败\n");
	//	nRetCode = 1;
	//}
}

////////////////////////////////////////////////////////////////////////////////
//
// 文件名称：dbservice.h
// 文件标识：
// 摘要：windows服务封装
//
// 版本：1.0
// 作者：乐蔚芸
// 日期：2009.10.26
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <Windows.h>
#include <string>
#include <vector>
typedef void SERVICE_START_FUNC(DWORD, CHAR**);
typedef void SERVICE_STOP_FUNC(void);

class MyService{
public:
	struct ServiceInfo
	{
	 std::string servName;
	 std::string dispName;
	 std::string servDesc;
	 std::string servPathName;
	 std::vector <std::string> servDependList;
	 DWORD startType;
	 DWORD serviceType;
	 SERVICE_START_FUNC *funcStart;
	 SERVICE_STOP_FUNC *funcStop;

	 ServiceInfo() : startType(SERVICE_AUTO_START), serviceType(SERVICE_WIN32_OWN_PROCESS), funcStart(NULL), funcStop(NULL) {}
	};

	MyService();
	~MyService();

	INT SetServiceInfo(ServiceInfo &serviceInfo);

	INT SerivceEntry(DWORD argc, CHAR **argv);

	static void ServiceStart(void);

	static void WINAPI ServiceMain(DWORD argc, CHAR **argv);
	static void WINAPI ServiceCtrl(DWORD ctrlCode);
	static DWORD WINAPI ServiceCtrlEx(DWORD ctrlCode, DWORD eventType, LPVOID eventData, LPVOID context);

	static INT CmdInstallService(void);
	static void CmdUninstallService(void);
	static void CmdDebugService(DWORD argc, CHAR **argv);

	static BOOL WINAPI ControlHandler(DWORD dwCtrlType);

	static void AddToMessageLog(DWORD errCode, LPCSTR msgAdd);
	static BOOL ReportStatusToSCMgr(
	 DWORD dwCurrentState,
	 DWORD dwWin32ExitCode,
	 DWORD dwWaitHint);

	HWND m_winHnd;

protected:
	static ServiceInfo m_servInfo;

	static SERVICE_STATUS m_sstatus;
	static SERVICE_STATUS_HANDLE m_ssHandle;

	INT m_status;
};


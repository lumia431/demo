#include "MyService.h"
#include <Lmcons.h>
#include <io.h>
#include <fcntl.h>
#include <Psapi.h>
#include <iostream>
#pragma comment(lib, "Psapi")

using std::string;

enum
{
	LDBOS_SERVICE_INIT = 0,
	LDBOS_SERVICE_OK
};

MyService::ServiceInfo MyService::m_servInfo;
SERVICE_STATUS MyService::m_sstatus;
SERVICE_STATUS_HANDLE MyService::m_ssHandle(NULL);

MyService::MyService() :
	m_winHnd(NULL),
	m_status(LDBOS_SERVICE_INIT)
{
}

MyService::~MyService()
{
}

INT MyService::SetServiceInfo(ServiceInfo &serviceInfo)
{
	if (serviceInfo.servName.empty()
		|| (serviceInfo.funcStart == NULL)
		|| (serviceInfo.funcStop == NULL))
	{
		return -1;
	}

	m_servInfo.servName = serviceInfo.servName.c_str();
	m_servInfo.dispName = serviceInfo.dispName.c_str();
	m_servInfo.servDesc = serviceInfo.servDesc.c_str();
	m_servInfo.servPathName = serviceInfo.servPathName.c_str();
	m_servInfo.servDependList = serviceInfo.servDependList;
	m_servInfo.startType = serviceInfo.startType;
	m_servInfo.serviceType = serviceInfo.serviceType;
	m_servInfo.funcStart = serviceInfo.funcStart;
	m_servInfo.funcStop = serviceInfo.funcStop;

	m_status = LDBOS_SERVICE_OK;
	return 0;
}

INT MyService::SerivceEntry(DWORD argc, CHAR **argv)
{
	if (m_status != LDBOS_SERVICE_OK)
	{
		return -1;
	}

	if ((argc > 1) &&
		((*argv[1] == '-') || (*argv[1] == '/')))
	{
		//BOOL consoleOK = TRUE;
		//FILE *fileOut = NULL;
		//if (!AttachConsole(ATTACH_PARENT_PROCESS))
		//{
		//    //if (!AllocConsole())
		//    //{
		//    //    consoleOK = FALSE;
		//    //}
		//    consoleOK = FALSE;
		//}

		//if (consoleOK)
		//{
		//     freopen_s(&fileOut, "conout$", "w+t", stdout);
		//     printf("\n");
		//}

		if (_stricmp("install", argv[1] + 1) == 0)
		{
			CmdInstallService();
		}
		else if ((_stricmp("uninstall", argv[1] + 1) == 0)
			|| (_stricmp("remove", argv[1] + 1) == 0))
		{
			CmdUninstallService();
		}
		else if ((_stricmp("debug", argv[1] + 1) == 0)
			|| (_stricmp("start", argv[1] + 1) == 0))
		{
			CmdDebugService(argc, argv);
		}

		//if (fileOut != NULL)
		//{
		//    fclose(fileOut);
		//}
		//if (consoleOK)
		//{
		//    FreeConsole();
		//}
	}
	else
	{
		ServiceStart();
	}

	return 0;
}

void MyService::ServiceStart(void)
{
	SERVICE_TABLE_ENTRY dispatchTable[] =
	{
		{(LPSTR)m_servInfo.servName.c_str(), ServiceMain},
		{NULL, NULL}
	};

	string fileName;
	CHAR pathName[MAX_PATH + 1] = { 0 };

	if (fileName.empty() || (_stricmp(fileName.c_str(), "services.exe") == 0))
	{
		if (!StartServiceCtrlDispatcher(dispatchTable))
		{
			AddToMessageLog(GetLastError(), "StartServiceCtrlDispatcher failed.");
		}
	}
	else
	{
		SC_HANDLE scMan = NULL;
		SC_HANDLE scSrv = NULL;

		do
		{
			if ((scMan = OpenSCManager(NULL, NULL, GENERIC_EXECUTE)) == NULL)
			{
				AddToMessageLog(GetLastError(), "OpenSCManager failed.");
				break;
			}

		redo:
			if ((scSrv = OpenService(scMan, m_servInfo.servName.c_str(),
				SERVICE_START | SERVICE_QUERY_CONFIG | SERVICE_QUERY_STATUS)) == NULL)
			{
				DWORD errCode = GetLastError();
				if (errCode == ERROR_SERVICE_DOES_NOT_EXIST)
				{
					if (CmdInstallService() != 0)
					{
						break;
					}
					else
					{
						goto redo;
					}
				}
				else
				{
					AddToMessageLog(GetLastError(), "OpenService failed.");
					break;
				}
				break;
			}

			SERVICE_STATUS status;
			if (!QueryServiceStatus(scSrv, &status))
			{
				AddToMessageLog(GetLastError(), "QueryServiceStatus failed.");
				break;
			}

			if (status.dwCurrentState == SERVICE_RUNNING)
			{
				break;
			}

			if (status.dwCurrentState == SERVICE_STOPPED)
			{
				StartService(scSrv, NULL, NULL);
			}
		} while (0);

		if (scSrv != NULL)
		{
			CloseServiceHandle(scSrv);
		}
		if (scMan != NULL)
		{
			CloseServiceHandle(scMan);
		}
	}
}

void WINAPI MyService::ServiceMain(DWORD argc, CHAR **argv)
{
	//m_ssHandle = RegisterServiceCtrlHandler(m_servInfo.servName.c_str(), ServiceCtrl);
	//if (m_ssHandle == NULL)
	//{
	//    AddToMessageLog(GetLastError(), "RegisterServiceCtrlHandler failed.");
	//    return;
	//}

	m_ssHandle = RegisterServiceCtrlHandlerEx(m_servInfo.servName.c_str(), ServiceCtrlEx, NULL);
	if (m_ssHandle == NULL)
	{
		AddToMessageLog(GetLastError(), "RegisterServiceCtrlHandlerEx failed.");
		return;
	}

	m_sstatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
	m_sstatus.dwServiceSpecificExitCode = 0;

	if (!ReportStatusToSCMgr(SERVICE_START_PENDING, NO_ERROR, 3000))
	{
		ReportStatusToSCMgr(SERVICE_STOPPED, NO_ERROR, 0);
		return;
	}

	if (m_servInfo.funcStart != NULL)
	{
		m_servInfo.funcStart(argc, argv);
	}

	ReportStatusToSCMgr(SERVICE_STOPPED, NO_ERROR, 0);
}

void WINAPI MyService::ServiceCtrl(DWORD ctrlCode)
{
	switch (ctrlCode)
	{
	case SERVICE_CONTROL_STOP:
	{
		ReportStatusToSCMgr(SERVICE_STOP_PENDING, NO_ERROR, 0);

		if (m_servInfo.funcStop != NULL)
		{
			m_servInfo.funcStop();
		}
		return;
	}
	default:
	{
		break;
	}
	}

	ReportStatusToSCMgr(m_sstatus.dwCurrentState, NO_ERROR, 0);
}

DWORD WINAPI MyService::ServiceCtrlEx(DWORD ctrlCode,
	DWORD eventType,
	LPVOID eventData,
	LPVOID context)
{
	switch (ctrlCode)
	{
	case SERVICE_CONTROL_STOP:
	case SERVICE_CONTROL_SHUTDOWN:
	{
		ReportStatusToSCMgr(SERVICE_STOP_PENDING, NO_ERROR, 0);

		if (m_servInfo.funcStop != NULL)
		{
			m_servInfo.funcStop();
		}
		return NO_ERROR;
	}
	default:
	{
		break;
	}
	}

	ReportStatusToSCMgr(m_sstatus.dwCurrentState, NO_ERROR, 0);
	return ERROR_CALL_NOT_IMPLEMENTED;
}

INT MyService::CmdInstallService(void)
{
	DWORD errCode;
	SC_HANDLE schSCManager;
	SC_HANDLE schService;

	if (m_servInfo.servPathName.empty())
	{
		CHAR pathName[MAX_PATH + 1] = { 0 };
		if (GetModuleFileName(NULL, pathName, MAX_PATH) == 0)
		{
			errCode = GetLastError();
			std::cout << "failed in GetModuleFileName: " << errCode << std::endl;
			return -1;
		}
		m_servInfo.servPathName = pathName;
	}

	schSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (schSCManager == NULL)
	{
		std::cout << "failed in OpenSCManager: " << GetLastError() << std::endl;
		return -1;
	}

	INT ret = 0;

	INT dependLen = 0;
	CHAR *depend = NULL;
	for (UINT i = 0; i < m_servInfo.servDependList.size(); ++i)
	{
		dependLen += m_servInfo.servDependList[i].length() + 1;
	}
	if (dependLen != 0)
	{
		++dependLen;
		depend = new(std::nothrow)CHAR[dependLen];
		memset(depend, 0, dependLen);
		for (UINT i = 0, pos = 0; i < m_servInfo.servDependList.size(); ++i)
		{
			memcpy(depend + pos, m_servInfo.servDependList[i].c_str(), m_servInfo.servDependList[i].length());
			pos += m_servInfo.servDependList[i].length() + 1;
		}
	}

	schService = CreateService(
		schSCManager,
		m_servInfo.servName.c_str(),
		m_servInfo.dispName.c_str(),
		SERVICE_ALL_ACCESS,
		m_servInfo.serviceType,
		m_servInfo.startType,
		SERVICE_ERROR_NORMAL,
		m_servInfo.servPathName.c_str(),
		NULL,
		NULL,
		depend,
		NULL,
		NULL);
	if (depend != NULL)
	{
		delete[] depend;
	}
	if (schService != NULL)
	{
		if (!m_servInfo.servDesc.empty())
		{
			SERVICE_DESCRIPTION servDesc;
			servDesc.lpDescription = (LPSTR)m_servInfo.servDesc.c_str();
			ChangeServiceConfig2(schService, SERVICE_CONFIG_DESCRIPTION, (LPVOID)&servDesc);
		}

		std::cout << m_servInfo.servName.c_str() << " installed." << std::endl;
		CloseServiceHandle(schService);
	}
	else
	{
		errCode = GetLastError();
		std::cout << "failed in CreateService: " << errCode << std::endl;
		ret = -1;
	}

	CloseServiceHandle(schSCManager);
	return ret;
}

void MyService::CmdUninstallService(void)
{
	SC_HANDLE schService;
	SC_HANDLE schSCManager;

	schSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (schSCManager != NULL)
	{
		schService = OpenService(schSCManager, m_servInfo.servName.c_str(), SERVICE_ALL_ACCESS);
		if (schService != NULL)
		{
			if (ControlService(schService, SERVICE_CONTROL_STOP, &m_sstatus))
			{
				printf("Stopping %s.", m_servInfo.servName.c_str());
				Sleep(1000);

				while (QueryServiceStatus(schService, &m_sstatus))
				{
					if (m_sstatus.dwCurrentState == SERVICE_STOP_PENDING)
					{
						printf(".");
						Sleep(1000);
					}
					else
					{
						break;
					}
				}

				if (m_sstatus.dwCurrentState == SERVICE_STOPPED)
				{
					printf("\n%s stopped.\n", m_servInfo.servName.c_str());
				}
				else
				{
					printf("\n%s failed to stop.\n", m_servInfo.servName.c_str());
				}
			}

			if (DeleteService(schService))
			{
				printf("%s removed.\n", m_servInfo.servName.c_str());
			}
			else
			{
				printf("failed in DeleteService: %u\n", GetLastError());
			}

			CloseServiceHandle(schService);
		}
		else
		{
			printf("failed in OpenService: %u\n", GetLastError());
		}

		CloseServiceHandle(schSCManager);
	}
	else
	{
		printf("failed int OpenSCManager: %u\n", GetLastError());
	}
}

void MyService::CmdDebugService(DWORD argc, CHAR **argv)
{
	//SetConsoleCtrlHandler(ControlHandler, TRUE);
	m_servInfo.funcStart(argc, argv);
	while (true)
	{

	}
}

BOOL WINAPI MyService::ControlHandler(DWORD dwCtrlType)
{
	switch (dwCtrlType)
	{
	case CTRL_BREAK_EVENT:  // use Ctrl+C or Ctrl+Break to simulate
	case CTRL_C_EVENT:      // SERVICE_CONTROL_STOP in debug mode
	{
		printf("Stopping %s.\n", m_servInfo.servName.c_str());
		if (m_servInfo.funcStop != NULL)
		{
			m_servInfo.funcStop();
		}
		return TRUE;
	}
	default:
	{
		break;
	}
	}
	return FALSE;
}

BOOL MyService::ReportStatusToSCMgr(DWORD status,
	DWORD errCode,
	DWORD waitHint)
{
	static DWORD checkPoint = 1;
	BOOL ret = TRUE;

	if (status == SERVICE_START_PENDING)
	{
		m_sstatus.dwControlsAccepted = 0;
	}
	else
	{
		m_sstatus.dwControlsAccepted = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN;
	}

	m_sstatus.dwCurrentState = status;
	m_sstatus.dwWin32ExitCode = errCode;
	m_sstatus.dwWaitHint = waitHint;

	if ((status == SERVICE_RUNNING) || (status == SERVICE_STOPPED))
	{
		m_sstatus.dwCheckPoint = 0;
	}
	else
	{
		m_sstatus.dwCheckPoint = checkPoint++;
	}

	ret = SetServiceStatus(m_ssHandle, &m_sstatus);
	if (!ret)
	{
		AddToMessageLog(GetLastError(), "SetServiceStatus");
	}

	return ret;
}

void MyService::AddToMessageLog(DWORD errCode, LPCSTR msgAdd)
{
	HANDLE eventSource;
	if ((eventSource = RegisterEventSource(NULL, m_servInfo.servName.c_str())) != NULL)
	{
		CHAR msg[256];
		sprintf_s(msg, "%s error: %u", m_servInfo.servName.c_str(), errCode);

		LPCSTR lpszStrings[2];
		lpszStrings[0] = msg;
		lpszStrings[1] = msgAdd;

		ReportEvent(
			eventSource,          // handle of event source
			EVENTLOG_ERROR_TYPE,  // event type
			0,                    // event category
			0,                    // event ID
			NULL,                 // current user's SID
			2,                    // strings in lpszStrings
			0,                    // no bytes of raw data
			(LPCSTR *)lpszStrings,// array of error strings
			NULL);                // no raw data

		DeregisterEventSource(eventSource);
	}
}

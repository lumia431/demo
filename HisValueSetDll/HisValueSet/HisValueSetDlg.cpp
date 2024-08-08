
// HisValueSetDlg.cpp: 实现文件
//
#include "pch.h"
#include "framework.h"
#include "HisValueSet.h"
#include <io.h>
#include "HisValueSetDlg.h"
#include "afxdialogex.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CHisValueSetDlg 对话框



CHisValueSetDlg::CHisValueSetDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_HISVALUESET_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
	m_percent = "0.000%";
	m_tagID = 10000;
	ReadCfg();
	Tools::SplitString(m_unpackStr, m_unpackList, ",");
	spdlog::set_pattern("%Y-%m-%d %H:%M:%S - [thread %t][%^%l%$][%s][%#]|,%v");
	spdlog::set_level(static_cast<spdlog::level::level_enum>(m_logLevel));
	//设置日志为异步日志，不带滚动，日志文件会一直写入
	//my_logger_ = spdlog::basic_logger_mt(logger_name, file_name);
	m_logger = spdlog::basic_logger_mt<spdlog::async_factory >("hisvalue", "./log.txt");
	//当遇到错误级别以上的立刻刷新到日志
	m_logger->flush_on(spdlog::level::err);
	//每三秒刷新一次
	spdlog::flush_every(std::chrono::seconds(3));
}

void CHisValueSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDITDBID, m_dbName);
	DDX_Text(pDX, IDC_EDITGROUP, m_groupName);
	DDX_Text(pDX, IDC_EDITPORT, m_port);
	DDX_Text(pDX, IDC_EDITPWD, m_pwd);
	DDX_Text(pDX, IDC_EDITUSR, m_usr);
	DDX_Text(pDX, IDC_EDITSUFFIX, m_prefix);
	DDX_Text(pDX, IDC_IPADDRESS1, m_addr);
	DDX_Control(pDX, IDC_COMBO1, m_sdk);
	DDX_Control(pDX, IDC_PROGRESS1, m_progress);
	DDX_Text(pDX, IDC_STATIC_PROGRESS, m_percent);
	DDX_Text(pDX, IDC_MFCEDITBROWSE_WRITE, m_filePath);
	DDX_Text(pDX, IDC_STATIC_TAGID, m_tagID);
	DDX_Radio(pDX, IDC_RADIO_WRITE, m_mode);
}

BEGIN_MESSAGE_MAP(CHisValueSetDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(ID_PAUSE, &CHisValueSetDlg::OnBnClickedPause)
	ON_BN_CLICKED(ID_START, &CHisValueSetDlg::OnBnClickedStart)
	ON_BN_CLICKED(ID_CONTINUE, &CHisValueSetDlg::OnBnClickedContinue)
	ON_BN_CLICKED(ID_CANCEL, &CHisValueSetDlg::OnBnClickedCancel)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CHisValueSetDlg 消息处理程序

BOOL CHisValueSetDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_progress.SetRange(0, 100);
	m_progress.SetPos(0);

	for (auto list_:m_unpackList)
	{
		m_sdk.AddString(list_.c_str());
	}

	m_sdk.SetCurSel(0);

	CRect rect;
	GetClientRect(&rect);     //取客户区大小  
	old.x = rect.right - rect.left;
	old.y = rect.bottom - rect.top;

	SetWindowLong(m_hWnd, GWL_STYLE, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX);

	GetDlgItem(ID_CANCEL)->EnableWindow(false);
	GetDlgItem(ID_CONTINUE)->EnableWindow(false);
	GetDlgItem(ID_PAUSE)->EnableWindow(false);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CHisValueSetDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CHisValueSetDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CHisValueSetDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CHisValueSetDlg::OnBnClickedPause()
{
	// TODO: 在此添加控件通知处理程序代码
	m_setHis->pauseStatus = true;
	GetDlgItem(ID_PAUSE)->EnableWindow(false);
	GetDlgItem(ID_CONTINUE)->EnableWindow(true);
}


void CHisValueSetDlg::OnBnClickedStart()
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(true);
	SetValueInfo info;
	CString unpackSdk;
	info.addr_ = m_addr;
	info.dbName_ = m_dbName;
	info.filePath_ = m_filePath;
	info.interval = m_interval;
	info.logLevel_ = m_logLevel;
	info.groupName_ = m_groupName;
	info.my_logger_ = m_logger;
	GetDlgItem(IDC_COMBO1)->GetWindowTextA(unpackSdk);
	info.sdk = unpackSdk;
	//int index = m_sdk.GetCurSel();
	//m_sdk.GetLBText(index,(CString)info.sdk.c_str());
	info.port_ = m_port;
	info.prefix_ = m_prefix;
	info.mode = m_mode == 0 ? MODE::WRITE_VALUE : MODE::MAKE_FILE;
	m_setHis = std::make_shared<SetHisValue>(info);
	m_percent = "0.000%";
	m_tagID = 10000;
	if ( _access(m_filePath, 0) == -1)
	{
		MessageBox("file path error!");
		return;
	}
	int ret = m_setHis->Init();
	if (ret == -4)
	{
		MessageBox("Connect RTDB fail!");
		return;
	}
	if (ret == -1)
	{
		MessageBox("file empty!");
		return;
	}
	SetTimer(1, 5000, nullptr);
	GetDlgItem(ID_START)->EnableWindow(false);
	GetDlgItem(ID_PAUSE)->EnableWindow(true);
	GetDlgItem(ID_CONTINUE)->EnableWindow(false);
	GetDlgItem(ID_CANCEL)->EnableWindow(true);
	if (m_setHis->Run() < 0)
	{
		MessageBox("set history value error!");
		return;
	}
}


void CHisValueSetDlg::OnBnClickedContinue()
{
	// TODO: 在此添加控件通知处理程序代码
	m_setHis->pauseStatus = false;
	GetDlgItem(ID_PAUSE)->EnableWindow(true);
	GetDlgItem(ID_CONTINUE)->EnableWindow(false);
}


void CHisValueSetDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	m_setHis->cancelFlg = true;
	m_percent = "0.000%";
	m_tagID = 10000;
	UpdateData(false);
	WriteCfg();
	GetDlgItem(ID_START)->EnableWindow(true);
	GetDlgItem(ID_CANCEL)->EnableWindow(false);
	GetDlgItem(ID_CONTINUE)->EnableWindow(false);
	GetDlgItem(ID_PAUSE)->EnableWindow(false);
	KillTimer(1);
	UpdateData(true);
}

void CHisValueSetDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (m_setHis->finishFlg)
	{
		KillTimer(1);
		MessageBox("task over!");
		WriteCfg();
		GetDlgItem(ID_START)->EnableWindow(true);
		GetDlgItem(ID_CANCEL)->EnableWindow(false);
		GetDlgItem(ID_CONTINUE)->EnableWindow(false);
		GetDlgItem(ID_PAUSE)->EnableWindow(false);
		UpdateData(true);
		return;
	}
	auto progs = m_setHis->GetProGress();
	if (progs < 0)
	{
		MessageBox("set value fail!");
		KillTimer(1);
	}

	char buf[20] = { 0 };
	sprintf_s(buf, "%.3f%%", progs * 100);
	m_percent = buf;
	m_tagID = m_setHis->tagID_;
	UpdateData(false);
	CDialogEx::OnTimer(nIDEvent);//把当前函数没有被处理的消息id，用默认的处理函数来处理
}

void CHisValueSetDlg::ReadCfg()
{
	std::ifstream file("./config.ini");
	if (!file)
	{
		WritePrivateProfileString("Config", "Add", "127.0.0.1", "./config.ini");
		WritePrivateProfileString("Config", "Port", "7000", "./config.ini");
		WritePrivateProfileString("Config", "User", "sa", "./config.ini");
		WritePrivateProfileString("Config", "Pwd", "sa1234", "./config.ini");
		WritePrivateProfileString("Config", "DBname", "db101", "./config.ini");
		WritePrivateProfileString("Config", "Group", "group", "./config.ini");
		WritePrivateProfileString("Config", "Prefix", "", "./config.ini");
		WritePrivateProfileString("Config", "Interval", "300", "./config.ini");
		WritePrivateProfileString("Config", "LogLevel", "1", "./config.ini");
		WritePrivateProfileString("Config", "UnpackDll", "HGY", "./config.ini");
	}
	char* lpPath = new char[MAX_PATH];
	char* addr = new char[20];
	char* path= new char[100];
	char* user = new char[100];
	char* pwd = new char[100];
	char* pref = new char[100];
	char* dbName = new char[100];
	char* group = new char[100];
	char* unpack = new char[100];
	strcpy_s(lpPath, MAX_PATH, "./config.ini");

	GetPrivateProfileString("Config", "Add", "", addr, 20, lpPath);
	GetPrivateProfileString("Config", "User", "", user, 20, lpPath);
	GetPrivateProfileString("Config", "Pwd", "", pwd, 20, lpPath);
	GetPrivateProfileString("Config", "Prefix", "", pref, 100, lpPath);
	GetPrivateProfileString("Config", "DBname", "", dbName, 100, lpPath);
	GetPrivateProfileString("Config", "Group", "", group, 100, lpPath);
	GetPrivateProfileString("Config", "UnpackDll", "", unpack, 100, lpPath);
	m_port = GetPrivateProfileInt("Config", "Port", 0, lpPath);
	m_interval = GetPrivateProfileInt("Config", "Interval", 0, lpPath);
	m_logLevel = GetPrivateProfileInt("Config", "LogLevel", 0, lpPath);
	delete[] lpPath;
	m_addr = (CString)addr;
	m_usr = (CString)user;
	m_pwd = (CString)pwd;
	m_prefix = (CString)pref;
	m_dbName = (CString)dbName;
	m_groupName = (CString)group;
	m_unpackStr = unpack;
	delete[]addr;
	delete[] user;
	delete[] pwd;
	delete[] pref;
	delete[] dbName;
	delete[] group;
	delete[] unpack;
}

void CHisValueSetDlg::WriteCfg()
{
	WritePrivateProfileString("Config", "Add",m_addr, "./config.ini");
	WritePrivateProfileString("Config", "Port", std::to_string(m_port).c_str(), "./config.ini");
	WritePrivateProfileString("Config", "User", m_usr, "./config.ini");
	WritePrivateProfileString("Config", "Pwd", m_pwd, "./config.ini");
	WritePrivateProfileString("Config", "DBname", m_dbName, "./config.ini");
	WritePrivateProfileString("Config", "Group", m_groupName, "./config.ini");
	WritePrivateProfileString("Config", "Prefix", m_prefix, "./config.ini");
}


void CHisValueSetDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	if (nType == SIZE_RESTORED || nType == SIZE_MAXIMIZED) {
		ReSize();
	}
}
void CHisValueSetDlg::ReSize()
{
	float fsp[2];
	POINT Newp; //获取现在对话框的大小
	CRect recta;
	GetClientRect(&recta);     //取客户区大小  
	Newp.x = recta.right - recta.left;
	Newp.y = recta.bottom - recta.top;
	fsp[0] = (float)Newp.x / old.x;
	fsp[1] = (float)Newp.y / old.y;
	CRect Rect;
	int woc;
	CPoint OldTLPoint, TLPoint; //左上角
	CPoint OldBRPoint, BRPoint; //右下角
	HWND  hwndChild = ::GetWindow(m_hWnd, GW_CHILD);  //列出所有控件  
	while (hwndChild)
	{
		woc = ::GetDlgCtrlID(hwndChild);//取得ID
		GetDlgItem(woc)->GetWindowRect(Rect);
		ScreenToClient(Rect);
		OldTLPoint = Rect.TopLeft();
		TLPoint.x = long(OldTLPoint.x*fsp[0]);
		TLPoint.y = long(OldTLPoint.y*fsp[1]);
		OldBRPoint = Rect.BottomRight();
		BRPoint.x = long(OldBRPoint.x *fsp[0]);
		BRPoint.y = long(OldBRPoint.y *fsp[1]);
		Rect.SetRect(TLPoint, BRPoint);
		GetDlgItem(woc)->MoveWindow(Rect, TRUE);
		hwndChild = ::GetWindow(hwndChild, GW_HWNDNEXT);
	}
	old = Newp;
}
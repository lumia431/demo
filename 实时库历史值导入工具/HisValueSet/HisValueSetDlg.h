
// HisValueSetDlg.h: 头文件
//

#pragma once
#include "SetHisValue.h"
// CHisValueSetDlg 对话框
class CHisValueSetDlg : public CDialogEx
{
// 构造
public:
	CHisValueSetDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HISVALUESET_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	std::shared_ptr<SetHisValue>m_setHis;
	afx_msg void OnBnClickedPause();
	afx_msg void OnBnClickedStart();
	afx_msg void OnBnClickedContinue();
	afx_msg void OnBnClickedCancel();
	CString m_filePath;
	CString m_addr;
	CString m_dbName;
	UINT m_port;
	UINT m_interval;
	CString m_tagName;
	UINT m_readMax;
	int m_mode;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CString m_usr;
	CString m_pwd;
	int m_logLevel;
	CString m_prefix;
	CString m_percent;
	CString m_groupName;
	std::shared_ptr<spdlog::logger> my_logger_;
	void ReadCfg();
	void WriteCfg();
	auto GetMylog()
	{
		return my_logger_;
	}
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void ReSize();
	POINT old;
};


// RTDBTransDlg.h: 头文件
//

#pragma once
#include "TransTask.h"

// CRTDBTransDlg 对话框
class CRTDBTransDlg : public CDialogEx
{
// 构造
public:
	CRTDBTransDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RTDBTRANS_DIALOG };
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

private:
	CString m_rtdbAddr;
	UINT m_rtdbPort;
	CString m_tsdbAddr;
	CString m_mqttAddr;
	CString m_kafkaAddr;
	UINT m_uaPort;
	UINT m_tsdbPort;
	UINT m_mqttPort;
	int m_kafkaPort;
	CString m_mqttTopic;
	CString m_kafkaTopic;
	CString m_pointPath;
	std::shared_ptr<spdlog::logger>m_logger;
	UINT m_logLevel;
	INT m_uaCheck;
	INT m_tsdbCheck;
	INT m_mqttCheck;
	INT m_kafkaCheck;
	std::shared_ptr<trans::TransTask> m_trans;
	void ReadCfg();
	void WriteCfg();
	UINT m_interval;
public:
	afx_msg void OnBnClickedCheckUa();
	afx_msg void OnBnClickedCheckOpentsdb();
	afx_msg void OnBnClickedCheckMqtt();
	afx_msg void OnBnClickedCheckKafka();
	afx_msg void OnBnClickedStart();
	afx_msg void OnBnClickedCancel();
	/*afx_msg void OnTimer(UINT_PTR nIDEvent);*/
};

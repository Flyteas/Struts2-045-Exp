
// Struts2-045-ExpDlg.h : 头文件
//

#pragma once
#include "CommandDlg.h"
#include "UploadFileDlg.h"
#include "GetshellDlg.h"

// CStruts2045ExpDlg 对话框
class CStruts2045ExpDlg : public CDialogEx
{
// 构造
public:
	CStruts2045ExpDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_STRUTS2045EXP_DIALOG };

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
	CTabCtrl funcTab;
	CommandDlg commandDlg; //命令执行对话框
	UploadFileDlg uploadFileDlg; //上传文件对话框
	GetshellDlg getshellDlg; //GETSHELL对话框
	int currTab; //当前TAB页
	CDialogEx* tabDlgs[3];//TAB所有对话框
public:
	afx_msg void OnTcnSelchangeTab2(NMHDR *pNMHDR, LRESULT *pResult);
};

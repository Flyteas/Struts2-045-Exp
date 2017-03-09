
#pragma once
#include "Exp.h"

// GetshellDlg 对话框
class GetshellDlg : public CDialogEx
{
// 构造
public:
	GetshellDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_GETSHELL_DIALOG};

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
	Exp exp;
	CString editTextURL;
	CString editTextShellName;
	CString editTextShellData;
	CString editTextResult;
	CString shellDefaultName; //SHELL默认名
	CString shellDefaultData; //SHELL默认内容
	CString shellDefaultPwd; //SHELL默认密码
	CString getJspRes(UINT resId); //获取JSP资源
public:
	afx_msg void OnBnClickedGetshell();
};

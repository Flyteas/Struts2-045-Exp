
// Struts2-045-ExpDlg.h : 头文件
//

#pragma once


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
	CString editTextURL;
	CString editTextCommand;
	CString editTextResult;
public:
	afx_msg void OnExecuteBtnClicked();
};

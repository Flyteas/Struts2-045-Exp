
// Struts2-045-ExpDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Struts2-045-Exp.h"
#include "Struts2-045-ExpDlg.h"
#include "afxdialogex.h"
#include "Exp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CStruts2045ExpDlg 对话框



CStruts2045ExpDlg::CStruts2045ExpDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CStruts2045ExpDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CStruts2045ExpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB2, funcTab);
}

BEGIN_MESSAGE_MAP(CStruts2045ExpDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB2, &CStruts2045ExpDlg::OnTcnSelchangeTab2)
END_MESSAGE_MAP()


// CStruts2045ExpDlg 消息处理程序

BOOL CStruts2045ExpDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//为Tab Control增加两个页面
	funcTab.InsertItem(0, "命令执行");
	funcTab.InsertItem(1, "文件上传");
	funcTab.InsertItem(2, "Getshell");
	commandDlg.Create(IDD_COMMAND_DIALOG, &funcTab); //创建命令执行对话框
	uploadFileDlg.Create(IDD_UPLOADFILE_DIALOG,&funcTab); //创建上传文件对话框
	getshellDlg.Create(IDD_GETSHELL_DIALOG,&funcTab); //创建GETSHELL对话框
	//设定在Tab内显示的范围
	CRect displayRange;
	commandDlg.GetClientRect(displayRange);
	displayRange.top += 20;
	displayRange.bottom -= 0;
	displayRange.left += 0;
	displayRange.right -= 0;
	commandDlg.MoveWindow(&displayRange);
	getshellDlg.MoveWindow(&displayRange);
	uploadFileDlg.MoveWindow(&displayRange);
 
	//把对话框对象指针保存起来
	tabDlgs[0] = &commandDlg;
	tabDlgs[1] = &uploadFileDlg;
	tabDlgs[2] = &getshellDlg;
	//显示初始页面
	tabDlgs[0]->ShowWindow(SW_SHOW);
	tabDlgs[1]->ShowWindow(SW_HIDE);
	tabDlgs[2]->ShowWindow(SW_HIDE);
	//保存当前选择
	currTab = 0;

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CStruts2045ExpDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CStruts2045ExpDlg::OnPaint()
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
HCURSOR CStruts2045ExpDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CStruts2045ExpDlg::OnTcnSelchangeTab2(NMHDR *pNMHDR, LRESULT *pResult) //TAB选择改变事件
{
    tabDlgs[currTab]->ShowWindow(SW_HIDE); //隐藏当前页面
    currTab = funcTab.GetCurSel();  //得到新的页面索引
    tabDlgs[currTab]->ShowWindow(SW_SHOW); //显示新页面
	*pResult = 0;
}

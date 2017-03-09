
// Struts2-045-ExpDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Struts2-045-Exp.h"
#include "CommandDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框


// CommandDlg 对话框



CommandDlg::CommandDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CommandDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CommandDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, editTextURL);
	DDX_Text(pDX, IDC_EDIT2, editTextCommand);
	DDX_Text(pDX, IDC_EDIT3, editTextResult);
}

BEGIN_MESSAGE_MAP(CommandDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CommandDlg::OnExecuteBtnClicked)
END_MESSAGE_MAP()


// CommandDlg 消息处理程序

BOOL CommandDlg::OnInitDialog()
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
	editTextCommand = "whoami"; //默认命令
	UpdateData(false);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CommandDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CommandDlg::OnPaint()
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
HCURSOR CommandDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CommandDlg::OnExecuteBtnClicked() //执行 按钮 点击事件
{
	UpdateData(true); //同步输入框变量值
	CString url = editTextURL;
	url.Replace("\r",""); //删除回车，否则无法正确访问
	url.Replace("\n",""); //删除换行，否则无法正确访问
	CString command = editTextCommand;
	command.Replace("\r",""); //删除回车，否则无法正确访问
	command.Replace("\n",""); //删除换行，否则无法正确访问
	if(url.IsEmpty()) //如果URL输入框为空
	{
		MessageBox("请输入URL","错误");
		return;
	}
	if(command.IsEmpty()) //如果命令输入框为空
	{
		MessageBox("请输入执行命令","错误");
		return;
	}
	
	editTextResult = exp.executeCommand(url,command);
	editTextResult.Replace("\n","\r\n"); //换行符 替换，否则CEDIT控件不能换行显示
	UpdateData(false); //同步输入框变量值
}

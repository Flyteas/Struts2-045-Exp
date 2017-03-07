#pragma once
class Exp
{
public:
	Exp(void);
	~Exp(void);
	CString executeCommand(CString URL,CString command); //执行命令，返回执行命令结果
};


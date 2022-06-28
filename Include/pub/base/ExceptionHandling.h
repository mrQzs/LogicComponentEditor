#ifndef _ITC_UTILS_EXP_HANDLING_H_
#define _ITC_UTILS_EXP_HANDLING_H_

#include "platform.h"
#include "windows.h"


#ifdef WIN32

#pragma comment(lib, "Dbghelp.lib")

class CExceptionHandling
{
public:
	~CExceptionHandling();
	
	int StartMonitor(const char* szFileName); 
	int DoMiniDump(void* pExceptionInfo);
	//谨慎调用改函数，在不确定程序中还存在使用其他异常处理的情况下，不可调用。
	int PreventOtherExceptionHandling(); 

	static CExceptionHandling& GetExceptionHandling();

private:
	CExceptionHandling();

	int CreateMiniDumpFile();
	void CloseMiniDumpFile();
	int WriteMiniDumpFile(void* pExceptionInfo);
	int DeleteExistDumpFile(const char* pcszDumpPath);

	void ReleaseAddrsSpace();
	void PrintError(const char* sDst);

private:
	static CExceptionHandling m_objExceptionHandling;
	HANDLE m_hFileMiniDump;
	const char *m_sFileName;
	void* m_pAddrsSpace; //地址空间。
};

#define GEH		CExceptionHandling::GetExceptionHandling()	
#define	R_A_S	200 * 1024 * 1024	//保留地址空间。

#endif

#endif

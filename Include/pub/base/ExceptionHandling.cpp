#include "pch.h"
#include "ExceptionHandling.h"
#include <vector>
using namespace std;


#ifdef WIN32
#include <dbghelp.h>
#include <excpt.h>

CExceptionHandling CExceptionHandling::m_objExceptionHandling;

LPTOP_LEVEL_EXCEPTION_FILTER
WINAPI
SetUnhandledExceptionFilter2( __in LPTOP_LEVEL_EXCEPTION_FILTER lpTopLevelExceptionFilter )
{
	//printf("enter SetUnhandledExceptionFilter2\n");
	return 0;
}

LONG WINAPI my_exception_handle(struct _EXCEPTION_POINTERS* ExceptionInfo)
{
	printf("enter my_exception_handle handle\n");
	if(ExceptionInfo)
		return GEH.DoMiniDump( (void*)ExceptionInfo );
	else
	{
		printf("struct _EXCEPTION_POINTERS* ExceptionInfo == NULL\n");
		return EXCEPTION_CONTINUE_SEARCH;
	}
}

void purecall_handler(void)
{
	printf("enter purecall_handler handle\n");
	GEH.DoMiniDump( NULL );
} 

void invalidparameter_handle(const wchar_t* expression, const wchar_t* function, const wchar_t* file, unsigned int line, uintptr_t pReserved)
{
	printf("enter invalidparameter_handle handle\n");
	GEH.DoMiniDump( (void*)expression );
}

CExceptionHandling::~CExceptionHandling()
{
	ReleaseAddrsSpace();
}

CExceptionHandling::CExceptionHandling()
{
	m_hFileMiniDump = INVALID_HANDLE_VALUE;
	m_pAddrsSpace = NULL;
}

int CExceptionHandling::StartMonitor(const char* szFileName)
{
	// <2> set exception filter
	::SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX | SEM_NOOPENFILEERRORBOX);
	::SetUnhandledExceptionFilter(my_exception_handle);
	::_set_purecall_handler(purecall_handler);
	::_set_invalid_parameter_handler(invalidparameter_handle);
	m_pAddrsSpace = VirtualAlloc(0, R_A_S, MEM_RESERVE, PAGE_EXECUTE_READWRITE);

	if(szFileName)
		m_sFileName = szFileName;
	else
		m_sFileName = " ";
	
	printf("Start Exception Handling...\n");
	return 0;
}

int CExceptionHandling::DoMiniDump( void* pExceptionInfo )
{
	//Begin 先删除目录下的所有.dmp文件 lvbing 2012-2-13
	char szCurDir[MAX_PATH]= {0};
	GetCurrentDirectory(MAX_PATH, szCurDir);
	DeleteExistDumpFile(szCurDir);
	//End 先删除目录下的所有.dmp文件 lvbing 2012-2-13
	if( CreateMiniDumpFile() )
		return EXCEPTION_EXECUTE_HANDLER;

	MINIDUMP_EXCEPTION_INFORMATION exception_param;
	exception_param.ExceptionPointers = (PEXCEPTION_POINTERS)pExceptionInfo;
	exception_param.ThreadId = GetCurrentThreadId();
	exception_param.ClientPointers = TRUE;

	ReleaseAddrsSpace();

	if(pExceptionInfo)
		WriteMiniDumpFile(&exception_param); //此处无需在申请地址空间，程序将会退出。
	else
	{
		WriteMiniDumpFile(NULL);
		m_pAddrsSpace = VirtualAlloc(0, R_A_S, MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	}

	CloseMiniDumpFile();
	printf("DoMiniDump OK...\n");

	// 需要使用G_OS::exit
	// G_OS::exit的Windows实现是ExitProcess
	// ExitProcess和exit的区别是它不会释放全局变量
	// 这样可以避免对象析构时造成的死锁、阻塞等不希望出现的情况
#ifndef _DEBUG
	G_OS::exit(0);
#endif
	
	return EXCEPTION_EXECUTE_HANDLER;
}

int CExceptionHandling::PreventOtherExceptionHandling()
{
	HMODULE hKernel32 = LoadLibrary("kernel32.dll");
	if (hKernel32 == NULL) 
		return 1;

	void *pOrgEntry = GetProcAddress(hKernel32, "SetUnhandledExceptionFilter");
	if(pOrgEntry == NULL) 
		return 1;

	DWORD dwOldProtect = 0;
	SIZE_T jmpSize = 5;

	BOOL bProt = VirtualProtect(pOrgEntry, jmpSize, PAGE_EXECUTE_READWRITE, &dwOldProtect);
	if (!bProt)
	{
		PrintError("PreventOtherExceptionHandling");
		return 1;
	}

	BYTE newJump[20];
	void *pNewFunc = &SetUnhandledExceptionFilter2;

	SIZE_T dwOrgEntryAddr = (SIZE_T) pOrgEntry;
	dwOrgEntryAddr += jmpSize; // add 5 for 5 op-codes for jmp rel32
	SIZE_T dwNewEntryAddr = (SIZE_T) pNewFunc;
	SIZE_T dwRelativeAddr = dwNewEntryAddr - dwOrgEntryAddr;
	// JMP rel32: Jump near, relative, displacement relative to next instruction.
	newJump[0] = 0xE9;  // JMP rel32
	memcpy(&newJump[1], &dwRelativeAddr, sizeof(pNewFunc));

	SIZE_T bytesWritten;
	BOOL bRet = WriteProcessMemory(GetCurrentProcess(), pOrgEntry, newJump, jmpSize, &bytesWritten);
	if (!bRet)
	{
		PrintError("PreventOtherExceptionHandling");
		return 1;
	}
	
	DWORD dwBuf;
	VirtualProtect(pOrgEntry, jmpSize, dwOldProtect, &dwBuf);
	return 0;
}

CExceptionHandling& CExceptionHandling::GetExceptionHandling()
{
	return CExceptionHandling::m_objExceptionHandling;
}

int CExceptionHandling::CreateMiniDumpFile()
{
	char file_name[MAX_PATH];
	SYSTEMTIME lpSystemTime;

	::GetLocalTime(&lpSystemTime);
	_snprintf_s(file_name, sizeof(file_name), sizeof(file_name), "%s-%04d%02d%02d-%02d%02d%02d-%ld.dmp", m_sFileName,
				lpSystemTime.wYear, lpSystemTime.wMonth, lpSystemTime.wDay, lpSystemTime.wHour, lpSystemTime.wMinute, 
				lpSystemTime.wSecond, GetCurrentProcessId() ); 

	m_hFileMiniDump = ::CreateFile(file_name, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (m_hFileMiniDump == INVALID_HANDLE_VALUE)
	{
		PrintError("CreateMiniDumpFile");
		return 1;
	}

	return 0;
}

void CExceptionHandling::CloseMiniDumpFile()
{
	if(m_hFileMiniDump != INVALID_HANDLE_VALUE)
		CloseHandle(m_hFileMiniDump);

	m_hFileMiniDump = INVALID_HANDLE_VALUE;
}

int CExceptionHandling::WriteMiniDumpFile( void* pExceptionInfo )
{
	if( !MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), m_hFileMiniDump, 
						   MiniDumpWithFullMemory/*MiniDumpNormal*/, (PMINIDUMP_EXCEPTION_INFORMATION)pExceptionInfo, NULL, NULL))
	{
		PrintError("WriteMiniDumpFile");
		return 1;
	}

	return 0;
}

void CExceptionHandling::PrintError( const char* sDst )
{
	LPVOID lpMsgBuf;

	FormatMessage( 
		FORMAT_MESSAGE_ALLOCATE_BUFFER | 
		FORMAT_MESSAGE_FROM_SYSTEM | 
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		GetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		(LPTSTR) &lpMsgBuf,
		0,
		NULL 
		);

	printf( "%s failed, error: %s\n", sDst, (LPTSTR)lpMsgBuf);
	LocalFree( lpMsgBuf );
}

void CExceptionHandling::ReleaseAddrsSpace()
{
	if(m_pAddrsSpace)
	{
		VirtualFree(m_pAddrsSpace, 0, MEM_RELEASE);
		m_pAddrsSpace = NULL;
	}
}

int CExceptionHandling::DeleteExistDumpFile(const char* pcszDumpPath)
{
	std::vector<string> vecfile;
	vecfile.clear();

	char szDumpDir[MAX_PATH] = {0};
	strncpy_s(szDumpDir, pcszDumpPath, sizeof(szDumpDir));
	int nLen = (int)strlen(szDumpDir);
	if( '\\' != szDumpDir[nLen -1])
	{
		strncat_s(szDumpDir, "\\", sizeof(szDumpDir));
	}
	strncat_s(szDumpDir, "*", sizeof(szDumpDir));

	WIN32_FIND_DATA finddata;
	BOOL findOK = TRUE;
	HANDLE hSearch = INVALID_HANDLE_VALUE;
	hSearch = FindFirstFile(szDumpDir, &finddata);
	if(INVALID_HANDLE_VALUE == hSearch)
	{
		return -1;
	}

	while(INVALID_HANDLE_VALUE != hSearch && findOK != FALSE)
	{
		if((finddata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != FILE_ATTRIBUTE_DIRECTORY &&
			(finddata.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM) != FILE_ATTRIBUTE_SYSTEM &&
			strcmp(finddata.cFileName, ".") != 0 &&
			strcmp(finddata.cFileName, "..") != 0)   
		{
			if(strstr(finddata.cFileName, ".dmp") != NULL)
			{
				vecfile.push_back(finddata.cFileName);	
			}	
		}
		findOK = FindNextFile(hSearch, &finddata);
	}
	FindClose(hSearch);

	std::vector<string>::iterator it = vecfile.begin();
	for(; it != vecfile.end(); it++)
	{
		//DWORD dwAttr = GetFileAttributes((*it).c_str());
		SetFileAttributes((*it).c_str(), FILE_ATTRIBUTE_ARCHIVE|FILE_ATTRIBUTE_NORMAL);
		remove((*it).c_str());
		printf("Delete exist dmp file %s\n", (*it).c_str());
	}

	return 0;
}

#endif


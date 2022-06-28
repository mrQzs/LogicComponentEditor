#pragma once

#include "platform.h"
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN             // 从 Windows 头文件中排除极少使用的内容
#include <Windows.h>
#endif
#include "SystemHelper.h"
#include "StringHelper.h"
#include <DbgHelp.h>
#pragma comment(lib, "Dbghelp.lib")

// Dump文件管理类
class CMiniDumpManager
{
public:
	constexpr std::string	m_strFileName{ "" };

public:
	// Dump文件生成
	static LONG WINAPI ExceptionFilter(EXCEPTION_POINTERS* pExceptionPointers) {
		std::string strFilePath = yd::CStringHelper::Format(
			"YDDaemon_%llu.dmp",
			yd::CTimestamp::GetCurrentMilliseconds());
		HANDLE hFile = CreateFile(
			strFilePath.c_str(),
			GENERIC_WRITE,
			0,
			NULL,
			CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			NULL);
		if (INVALID_HANDLE_VALUE == hFile) {
			return EXCEPTION_CONTINUE_EXECUTION;
		}

		MINIDUMP_EXCEPTION_INFORMATION einfo = { 0 };
		einfo.ThreadId = ::GetCurrentThreadId();
		einfo.ExceptionPointers = pExceptionPointers;
		einfo.ClientPointers = FALSE;
		MINIDUMP_TYPE mdt = (MINIDUMP_TYPE)(
			MiniDumpWithPrivateReadWriteMemory |
			MiniDumpWithDataSegs |
			MiniDumpWithHandleData |
			0x00000800 | 0x00001000 | MiniDumpWithUnloadedModules);
		MiniDumpWriteDump(
			GetCurrentProcess(),
			GetCurrentProcessId(),
			hFile,
			mdt,
			&einfo,
			NULL,
			NULL);
		CloseHandle(hFile);

		return EXCEPTION_EXECUTE_HANDLER;
	}

	// 注册Dump生成函数
	static bool Register(const std::string& strFileName) {
		// 指定ExceptionFilter替换原生的异常处理
		SetUnhandledExceptionFilter(CMiniDumpManager::ExceptionFilter);
	}
};
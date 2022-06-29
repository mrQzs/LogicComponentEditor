#pragma once

#include "platform.h"
#include <string>

//#define __ENABLE_SCRIPT_DATA_CACHE__

#ifdef _WIN32
#include <Windows.h>
#include <sddl.h>
#include <AccCtrl.h>
#include <AclAPI.h>
#include <lmerr.h>
#include <memoryapi.h>
class KernelUtility
{
public:
	// 创建信号量
	static int32 CreateUserSemaphore(HANDLE* pSemHandle, const char* lpszName, int32 iInitialCount, int32 iMaximumCount) {
		// 创建命名信号量
		*pSemHandle = CreateSemaphoreA(nullptr, iInitialCount, iMaximumCount, lpszName);
		if (nullptr == *pSemHandle || INVALID_HANDLE_VALUE == *pSemHandle) {
			return (int32)GetLastError();
		}
		return 0;
	}

	// 打开信号量
	static int32 OpenUserSemaphore(HANDLE* pSemHandle, const char* lpszName) {
		// 信号量已经打开
		if (nullptr != *pSemHandle && INVALID_HANDLE_VALUE != *pSemHandle) {
			return 0;
		}
		// 打开信号量
		*pSemHandle = OpenSemaphoreA(SEMAPHORE_ALL_ACCESS, FALSE, lpszName);
		if (nullptr == *pSemHandle || INVALID_HANDLE_VALUE == *pSemHandle) {
			return (int32)GetLastError();
		}
		return 0;
	}

	// 释放信号量
	static int32 FreeUserSemaphore(HANDLE* pSemHandle) {
		if (nullptr != *pSemHandle && INVALID_HANDLE_VALUE != *pSemHandle) {
			CloseHandle(*pSemHandle);
			*pSemHandle = INVALID_HANDLE_VALUE;
			return 0;
		}
		return ACCESS_RESULT_NOT_OPENED;
	}

	// 锁定信号量
	static int32 LockUserSemaphore(HANDLE* pSemHandle, uint32 uiMilliseconds) {
		if (nullptr == *pSemHandle || INVALID_HANDLE_VALUE == *pSemHandle) {
			return ACCESS_RESULT_NOT_OPENED;
		}
		// 等待信号量
		int32 iResult = WaitForSingleObject(*pSemHandle, uiMilliseconds);
		if (WAIT_OBJECT_0 != iResult) {
			return (int32)GetLastError();;
		}
		return 0;
	}

	// 解锁信号量
	static int32 UnlockUserSemaphore(HANDLE* pSemHandle, int32 iUlockCount) {
		if (nullptr == *pSemHandle || INVALID_HANDLE_VALUE == *pSemHandle) {
			return ACCESS_RESULT_NOT_OPENED;
		}
		// 释放信号量
		if (!ReleaseSemaphore(*pSemHandle, iUlockCount, nullptr)) {
			return (int32)GetLastError();
		}
		return 0;
	}

	// 创建共享内存
	static void* CreateUserMemory(HANDLE* pMemHandle, const char* lpszName, uint32 uiSize, int32* piError) {
		*piError = 0;
		// 创建共享文件句柄
		*pMemHandle = CreateFileMappingA(
			INVALID_HANDLE_VALUE,
			nullptr,
			PAGE_READWRITE,
			0,
			uiSize,
			lpszName);
		if (nullptr == *pMemHandle || INVALID_HANDLE_VALUE == *pMemHandle) {
			*piError = (int32)GetLastError();
			return nullptr;
		}
		// 映射缓存区视图
		LPVOID lpBuffer = MapViewOfFile(*pMemHandle, FILE_MAP_ALL_ACCESS, 0, 0, uiSize);
		if (nullptr == lpBuffer) {
			*piError = (int32)GetLastError();
			return nullptr;
		}
		return lpBuffer;
	}

	// 打开共享内存
	static void* OpenUserMemory(HANDLE* pMemHandle, const char* lpszName, uint32 uiSize, int32* piError) {
		*piError = 0;
		// 打开共享文件句柄
		*pMemHandle = OpenFileMappingA(FILE_MAP_ALL_ACCESS, FALSE, lpszName);
		if (nullptr == *pMemHandle || INVALID_HANDLE_VALUE == *pMemHandle) {
			*piError = (int32)GetLastError();
			return nullptr;
		}
		// 映射缓存区视图
		LPVOID lpBuffer = MapViewOfFile(*pMemHandle, FILE_MAP_ALL_ACCESS, 0, 0, uiSize);
		if (nullptr == lpBuffer) {
			*piError = (int32)GetLastError();
			return nullptr;
		}
		return lpBuffer;
	}

	// 释放共享内存
	static int32 FreeUserMemory(HANDLE* pMemHandle, void* lpData) {
		// 解除文件映射
		if (nullptr != lpData) {
			UnmapViewOfFile((LPCVOID)lpData);
			lpData = nullptr;
		}
		// 关闭共享文件句柄
		if (nullptr != *pMemHandle && INVALID_HANDLE_VALUE != *pMemHandle) {
			CloseHandle(*pMemHandle);
			*pMemHandle = INVALID_HANDLE_VALUE;
		}
		return 0;
	}

	// 获取进程优先级
	static uint32 GetUserProcessPriority(HANDLE hProcess) {
		return (uint32)GetPriorityClass(hProcess);
	}

	// 设置进程优先级
	static int32 SetUserProcessPriority(HANDLE hProcess, uint32 uiPriority) {
		if (!SetPriorityClass(hProcess, uiPriority)) {
			return (int32)GetLastError();
		}
		else {
			return 0;
		}
	}

	// 获取线程优先级
	static uint32 GetUserThreadPriority(HANDLE hThread) {
		return (uint32)GetThreadPriority(hThread);
	}

	// 设置线程优先级
	static int32 SetUserThreadPriority(HANDLE hThread, uint32 uiPriority) {
		if (!SetThreadPriority(hThread, uiPriority)) {
			return (int32)GetLastError();
		}
		else {
			return 0;
		}
	}

	// 格式化错误描述
	static std::string FormatErrorMessage(DWORD dwErrorCode) {
		std::string strMessage = "";
		HMODULE hModule = NULL;
		LPSTR lpszMessageBuffer = NULL;
		DWORD dwBufferLength = 0;
		DWORD dwFormatFlags =
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_IGNORE_INSERTS |
			FORMAT_MESSAGE_FROM_SYSTEM;
		if (dwErrorCode >= NERR_BASE && dwErrorCode <= MAX_NERR) {
			hModule = LoadLibraryExA("netmsg.dll", NULL, LOAD_LIBRARY_AS_DATAFILE);
			if (NULL != hModule) {
				dwFormatFlags |= FORMAT_MESSAGE_FROM_HMODULE;
			}
		}
		dwBufferLength = FormatMessageA(
			dwFormatFlags,
			hModule,
			dwErrorCode,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPSTR)&lpszMessageBuffer,
			0,
			NULL);
		if (dwBufferLength > 0) {
			strMessage = std::string(lpszMessageBuffer);
			LocalFree(lpszMessageBuffer);
			lpszMessageBuffer = NULL;
		}
		if (NULL != hModule) {
			FreeLibrary(hModule);
			hModule = NULL;
		}
		return strMessage;
	}
};
#else
#endif

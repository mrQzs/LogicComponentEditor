#pragma once

#include <filesystem>
#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <regex>
#include <chrono>
#include <thread>
#include <platform.h>
#include <direct.h>
#include <sys/stat.h>
#include "StringHelper.h"
#include "SystemHelper.h"
#ifdef _WIN32
#include <TlHelp32.h>
#endif

namespace yd {
	// 进程管理类
#ifdef _WIN32
	class CProcessHelper
	{
	public:
		// 获取进程id
		static bool GetPid(uint32& uiProcessId, const std::string& strProcessName) {
			uiProcessId = 0;
			PROCESSENTRY32 procEntry;
			procEntry.dwSize = sizeof(PROCESSENTRY32);
			HANDLE hSnapshot = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
			if (INVALID_HANDLE_VALUE == hSnapshot) {
				return false;
			}
			BOOL bMore = ::Process32First(hSnapshot, &procEntry);
			while (bMore) {
				std::string strExeName = procEntry.szExeFile;
				if (std::string::npos != strExeName.find(strProcessName)) {
					uiProcessId = (uint32)procEntry.th32ProcessID;
					break;
				}
				bMore = ::Process32Next(hSnapshot, &procEntry);
			}
			::CloseHandle(hSnapshot);
			return (uiProcessId > 0);
		}

		// 启动进程
		static bool Start(uint32& uiProcessId, const std::string& strProcessName) {
			std::string strApplicationName = strProcessName;
			if (std::string::npos == strProcessName.find(".exe")) {
				strApplicationName = strProcessName + std::string(".exe");
			}
			if (!yd::CFileHelper::FileExists(strApplicationName)) {
				return true;
			}
			STARTUPINFO startInfo; memset(&startInfo, 0x00, sizeof(STARTUPINFO));
			startInfo.cb = sizeof(STARTUPINFO);
			startInfo.dwFlags = STARTF_USESHOWWINDOW;
			PROCESS_INFORMATION procInfo; memset(&procInfo, 0x00, sizeof(procInfo));
			char szCommandLine[MAX_PATH] = { 0x00 };
			BOOL bInheritHandles = FALSE;
			DWORD dwCreationFlags = DETACHED_PROCESS;
			if (!::CreateProcess(
				strApplicationName.c_str(),
				szCommandLine,
				nullptr,
				nullptr,
				bInheritHandles,
				dwCreationFlags,
				nullptr,
				nullptr,
				&startInfo,
				&procInfo)) {
				return false;
			}
			uiProcessId = (uint32)procInfo.dwProcessId;
			::CloseHandle(procInfo.hProcess);
			::CloseHandle(procInfo.hThread);
			return (uiProcessId > 0);
		}

		// 停止进程
		static bool Stop(uint32& uiProcessId, const std::string& strProcessName, uint32 uiTimeout = 5000) {
			if (uiProcessId <= 0) {
				if (!CProcessHelper::GetPid(uiProcessId, strProcessName)) {
					return true;
				}
			}
			// 停止子进程
			HANDLE hProcess = ::OpenProcess(PROCESS_TERMINATE, FALSE, uiProcessId);
			if (INVALID_HANDLE_VALUE == hProcess || nullptr == hProcess) {
				return true;
			}
			int32 iResult = ::WaitForSingleObject(hProcess, uiTimeout);
			::TerminateProcess(hProcess, 0);
			::CloseHandle(hProcess);
			hProcess = nullptr;
			return true;
		}
	};
#else
#endif
}

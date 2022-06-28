#pragma once

#include "platform.h"

#ifdef __cplusplus
extern "C" {
#endif	
	// 进程状态
	constexpr uint8 PROCESS_STATE_STOPPED			= 0;
	constexpr uint8 PROCESS_STATE_RUNNING			= 1;
	constexpr uint8 PROCESS_STATE_PAUSED			= 2;

	// 进程命令
	constexpr uint8 PROCESS_COMMAND_INVALID			= 0;
	constexpr uint8 PROCESS_COMMAND_START			= 1;
	constexpr uint8 PROCESS_COMMAND_STOP			= 2;
	constexpr uint8 PROCESS_COMMAND_PAUSE			= 3;

	// 创建共享内存
	int32 libp_CreateMemory();

	// 打开共享内存
	int32 libp_OpenMemory();

	// 释放共享内存
	int32 libp_FreeMemory();

	// 共享内存释放创建
	uint8 libp_MemoryCreated();

	// 获取指定进程运行状态
	uint8 libp_GetProcessState(const char* lpszProcessName);

	// 更新指定进程运行状态
	int32 libp_SetProcessState(const char* lpszProcessName, uint8 ucState);

	// 获取指定进程命令
	uint8 libp_GetProcessCommand(const char* lpszProcessName);

	// 更新指定进程命令
	int32 libp_SetProcessCommand(const char* lpszProcessName, uint8 ucCommand);

	// 获取指定进程更新时间
	int64 libp_GetProcessLastUpdateTime(const char* lpszProcessName);

	// 更新指定进程更新时间
	int32 libp_SetProcessLastUpdateTime(const char* lpszProcessName, int64 llLastUpdateTime);
#ifdef __cplusplus
};
#endif
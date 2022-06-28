#pragma once

#include "yddef.h"

#ifdef __cplusplus
extern "C" {
#endif
	// 创建共享内存
	int32 libm_CreateMemory();

	// 打开共享内存
	int32 libm_OpenMemory();

	// 释放共享内存
	int32 libm_FreeMemory();

	// 共享内存释放创建
	uint8 libm_MemoryCreated();

	// 推送消息
	int32 libm_PushMessage(const yd::MESSAGE* pMessage);
	int32 libm_PushMessages(const yd::MESSAGES* pMessages);

	// 弹出消息
	int32 libm_PopMessage(yd::MESSAGE* pMessage);
	int32 libm_PopMessages(yd::MESSAGES* pMessages);

#ifdef __cplusplus
};
#endif
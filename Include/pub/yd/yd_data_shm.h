#pragma once

#include "yddef.h"

// 数据位掩码定义
constexpr uint32 UPDATE_BITMASK_DAEMON1 = 0x00000001;
constexpr uint32 UPDATE_BITMASK_DAEMON2 = 0x00000002;
constexpr uint32 UPDATE_BITMASK_DAEMON3 = 0x00000004;
constexpr uint32 UPDATE_BITMASK_DAEMON4 = 0x00000008;
constexpr uint32 UPDATE_BITMASK_DAEMON5 = 0x00000010;
constexpr uint32 UPDATE_BITMASK_DAEMON6 = 0x00000020;
constexpr uint32 UPDATE_BITMASK_DAEMON7 = 0x00000040;
constexpr uint32 UPDATE_BITMASK_DAEMON8 = 0x00000080;
constexpr uint32 UPDATE_BITMASK_LOGIC_CONTROLLER1 = 0x00000100;
constexpr uint32 UPDATE_BITMASK_LOGIC_CONTROLLER2 = 0x00000200;
constexpr uint32 UPDATE_BITMASK_LOGIC_CONTROLLER3 = 0x00000400;
constexpr uint32 UPDATE_BITMASK_LOGIC_CONTROLLER4 = 0x00000800;
constexpr uint32 UPDATE_BITMASK_LOGIC_CONTROLLER5 = 0x00001000;
constexpr uint32 UPDATE_BITMASK_LOGIC_CONTROLLER6 = 0x00002000;
constexpr uint32 UPDATE_BITMASK_LOGIC_CONTROLLER7 = 0x00004000;
constexpr uint32 UPDATE_BITMASK_LOGIC_CONTROLLER8 = 0x00008000;
constexpr uint32 UPDATE_BITMASK_COMMUNICATION1 = 0x00010000;
constexpr uint32 UPDATE_BITMASK_COMMUNICATION2 = 0x00020000;
constexpr uint32 UPDATE_BITMASK_COMMUNICATION3 = 0x00040000;
constexpr uint32 UPDATE_BITMASK_COMMUNICATION4 = 0x00080000;
constexpr uint32 UPDATE_BITMASK_COMMUNICATION5 = 0x00100000;
constexpr uint32 UPDATE_BITMASK_COMMUNICATION6 = 0x00200000;
constexpr uint32 UPDATE_BITMASK_COMMUNICATION7 = 0x00400000;
constexpr uint32 UPDATE_BITMASK_COMMUNICATION8 = 0x00800000;

#ifdef __cplusplus
extern "C" {
#endif
	// 创建共享内存
	int32 libd_CreateMemory();

	// 打开共享内存
	int32 libd_OpenMemory();

	// 释放共享内存
	int32 libd_FreeMemory();

	// 共享内存释放创建
	uint8 libd_MemoryCreated();

	// 设置系统状态
	int32 libd_SetSystemStatus(uint8 ucSystemStatus);

	// 获取系统状态
	uint8 libd_GetSystemStatus();

	// 设置控制器工作模式
	int32 libd_SetControllerMode(uint8 ucControllerMode);

	// 获取控制器工作模式
	uint8 libd_GetControllerMode();

	// 设置项目参数
	int32 libd_SetProjectParam(const yd::PROJECTPARAM* pProjectParam);

	// 获取项目参数
	int32 libd_GetProjectParam(yd::PROJECTPARAM* pProjectParam);

	// 设置数据接收器
	int32 libd_SetDataReceiver(const yd::DATARECEIVER* pDataReceiver);

	// 获取数据接收器
	int32 libd_GetDataReceivers(yd::DATARECEIVERS* pDataReceivers);

	// 添加变量：成功返回序号，失败返回0xFFFFFFFF
	uint32 libd_AddVariable(uint64 ullVariableId, const yd::VRVARIABLE* pVariable);

	// 设置单个变量
	int32 libd_SetVariableById(uint64 ullVariableId, const yd::VRVARIABLE* pVariable);
	int32 libd_SetVariableByIndex(uint32 uiVariableIndex, const yd::VRVARIABLE* pVariable);

	// 获取单个变量
	int32 libd_GetVariableById(uint64 ullVariableId, yd::VRVARIABLE* pVariable);
	int32 libd_GetVariableByIndex(uint32 uiVariableIndex, yd::VRVARIABLE* pVariable);
	int32 libd_GetVariableByName(const std::string& strVariableName, yd::VRVARIABLE* pVariable);

	// 设置多个变量
	int32 libd_SetVariables(const yd::VRVARIABLES* pVariables);

	// 获取多个变量
	int32 libd_GetVariables(yd::VRVARIABLES* pVariables);

	// 获取变化的多个变量
	int32 libd_GetChangedVariables(yd::VRVARIABLES* pVariables);

	// 获取指定序号的变量数值
	int32 libd_GetVariableValues(const uint32* parrVRIndexes, yd::VRVALUE* parrVRValues, uint32 uiNumber);

	// 设置多个变量数值
	int32 libd_SetVariableValues(const yd::VRVALUE* parrVRValues, uint32 uiNumber);

	// 获取变量的序号
	int32 libd_GetVariableIndexById(uint64 ullVariableId, uint32& uiVariableIndex);
	int32 libd_GetVariableIndexByName(const std::string& strVariableName, uint64& ullVariableId, uint32& uiVariableIndex);

	// 获取时间戳
	int32 libd_GetVariableTimestampById(uint64 ullVariableId, uint64& ullTimestamp);
	int32 libd_GetVariableTimestampByIndex(uint32 uiVariableIndex, uint64& ullTimestamp);

	// 获取变量名称
	int32 libd_GetVariableNameById(uint64 ullVariableId, std::string& strVariableName);
	int32 libd_GetVariableNameByIndex(uint32 uiVariableIndex, std::string& strVariableName);

	// 获取变量类型
	int32 libd_GetVariableTypeById(uint64 ullVariableId, uint8& ucVariableType);
	int32 libd_GetVariableTypeByIndex(uint32 uiVariableIndex, uint8& ucVariableType);

	// 获取变量数值类型
	int32 libd_GetValueTypeById(uint64 ullVariableId, uint8& ucValueType);
	int32 libd_GetValueTypeByIndex(uint32 uiVariableIndex, uint8& ucValueType);

	// 设置单个变量当前值
	int32 libd_SetVariableValueById(uint64 ullVariableId, const yd::VRVALUE* pValue);
	int32 libd_SetVariableValueByIndex(uint32 uiVariableIndex, const yd::VRVALUE* pValue);
	int32 libd_SetVariableBoolById(uint64 ullVariableId, const bool& bValue);
	int32 libd_SetVariableBoolByIndex(uint32 uiVariableIndex, const bool& bValue);
	int32 libd_SetVariableUint8ById(uint64 ullVariableId, const uint8& ucValue);
	int32 libd_SetVariableUint8ByIndex(uint32 uiVariableIndex, const uint8& ucValue);
	int32 libd_SetVariableInt8ById(uint64 ullVariableId, const int8& cValue);
	int32 libd_SetVariableInt8ByIndex(uint32 uiVariableIndex, const int8& cValue);
	int32 libd_SetVariableUint16ById(uint64 ullVariableId, const uint16& usValue);
	int32 libd_SetVariableUint16ByIndex(uint32 uiVariableIndex, const uint16& usValue);
	int32 libd_SetVariableInt16ById(uint64 ullVariableId, const int16& sValue);
	int32 libd_SetVariableInt16ByIndex(uint32 uiVariableIndex, const int16& sValue);
	int32 libd_SetVariableUint32ById(uint64 ullVariableId, const uint32& uiValue);
	int32 libd_SetVariableUint32ByIndex(uint32 uiVariableIndex, const uint32& uiValue);
	int32 libd_SetVariableInt32ById(uint64 ullVariableId, const int32& iValue);
	int32 libd_SetVariableInt32ByIndex(uint32 uiVariableIndex, const int32& iValue);
	int32 libd_SetVariableUint64ById(uint64 ullVariableId, const uint64& ullValue);
	int32 libd_SetVariableUint64ByIndex(uint32 uiVariableIndex, const uint64& ullValue);
	int32 libd_SetVariableInt64ById(uint64 ullVariableId, const int64& llValue);
	int32 libd_SetVariableInt64ByIndex(uint32 uiVariableIndex, const int64& llValue);
	int32 libd_SetVariableFloatById(uint64 ullVariableId, const float& fValue);
	int32 libd_SetVariableFloatByIndex(uint32 uiVariableIndex, const float& fValue);
	int32 libd_SetVariableDoubleById(uint64 ullVariableId, const double& dblValue);
	int32 libd_SetVariableDoubleByIndex(uint32 uiVariableIndex, const double& dblValue);
	int32 libd_SetVariableStringById(uint64 ullVariableId, const std::string& strValue);
	int32 libd_SetVariableStringByIndex(uint32 uiVariableIndex, const std::string& strValue);
	int32 libd_SetVariableCoordsById(uint64 ullVariableId, const yd::COORDS* pCoords);
	int32 libd_SetVariableCoordsByIndex(uint32 uiVariableIndex, const yd::COORDS* pCoords);

	// 获取单个变量当前值
	int32 libd_GetVariableValueById(uint64 ullVariableId, yd::VRVALUE* pValue);
	int32 libd_GetVariableValueByIndex(uint32 uiVariableIndex, yd::VRVALUE* pValue);
	int32 libd_GetVariableBoolById(uint64 ullVariableId, bool& bValue);
	int32 libd_GetVariableBoolByIndex(uint32 uiVariableIndex, bool& bValue);
	int32 libd_GetVariableUint8ById(uint64 ullVariableId, uint8& ucValue);
	int32 libd_GetVariableUint8ByIndex(uint32 uiVariableIndex, uint8& ucValue);
	int32 libd_GetVariableInt8ById(uint64 ullVariableId, int8& cValue);
	int32 libd_GetVariableInt8ByIndex(uint32 uiVariableIndex, int8& cValue);
	int32 libd_GetVariableUint16ById(uint64 ullVariableId, uint16& usValue);
	int32 libd_GetVariableUint16ByIndex(uint32 uiVariableIndex, uint16& usValue);
	int32 libd_GetVariableInt16ById(uint64 ullVariableId, int16& sValue);
	int32 libd_GetVariableInt16ByIndex(uint32 uiVariableIndex, int16& sValue);
	int32 libd_GetVariableUint32ById(uint64 ullVariableId, uint32& uiValue);
	int32 libd_GetVariableUint32ByIndex(uint32 uiVariableIndex, uint32& uiValue);
	int32 libd_GetVariableInt32ById(uint64 ullVariableId, int32& iValue);
	int32 libd_GetVariableInt32ByIndex(uint32 uiVariableIndex, int32& iValue);
	int32 libd_GetVariableUint64ById(uint64 ullVariableId, uint64& ullValue);
	int32 libd_GetVariableUint64ByIndex(uint32 uiVariableIndex, uint64& ullValue);
	int32 libd_GetVariableInt64ById(uint64 ullVariableId, int64& llValue);
	int32 libd_GetVariableInt64ByIndex(uint32 uiVariableIndex, int64& llValue);
	int32 libd_GetVariableFloatById(uint64 ullVariableId, float& fValue);
	int32 libd_GetVariableFloatByIndex(uint32 uiVariableIndex, float& fValue);
	int32 libd_GetVariableDoubleById(uint64 ullVariableId, double& dblValue);
	int32 libd_GetVariableDoubleByIndex(uint32 uiVariableIndex, double& dblValue);
	int32 libd_GetVariableStringById(uint64 ullVariableId, std::string& strValue);
	int32 libd_GetVariableStringByIndex(uint32 uiVariableIndex, std::string& strValue);
	int32 libd_GetVariableCoordsById(uint64 ullVariableId, yd::COORDS* pCoords);
	int32 libd_GetVariableCoordsByIndex(uint32 uiVariableIndex, yd::COORDS* pCoords);

	// 变量是否变更
	uint8 libd_VariableChanged(uint32 uiBitMask);

	// 指定变量值是否变更
	uint8 libd_VariableValueChangedById(uint64 ullVariableId, uint32 uiBitMask);
	uint8 libd_VariableValueChangedByIndex(uint32 uiVariableIndex, uint32 uiBitMask);

	// 通知控制器已经停止
	int32 libd_NotifiyControllerStopped();

	// 是否控制器已经停止
	uint8 libd_IsControllerStopped(uint32 uiBitMask);

	// 通知控制器已经启动
	int32 libd_NotifiyControllerStarted();

	// 是否控制器已经启动
	uint8 libd_IsControllerStarted(uint32 uiBitMask);

	// 通知控制器已经暂停
	int32 libd_NotifiyControllerSuspended();

	// 是否控制器已经暂停
	uint8 libd_IsControllerSuspended(uint32 uiBitMask);

	// 通知控制器已经恢复
	int32 libd_NotifiyControllerRestored();

	// 是否控制器已经恢复
	uint8 libd_IsControllerRestored(uint32 uiBitMask);

	// 通知控制器已经切换手动模式
	int32 libd_NotifiyControllerSwitchedToManualMode();

	// 是否控制器已经切换手动模式
	uint8 libd_IsControllerSwitchedToManualMode(uint32 uiBitMask);

	// 通知控制器已经切换自动模式
	int32 libd_NotifiyControllerSwitchedToAutomaticMode();

	// 是否控制器已经切换自动模式
	uint8 libd_IsControllerSwitchedToAutomaticMode(uint32 uiBitMask);

	// 控制命令入列
	uint32 libd_EnqueueControlCommand(const yd::CONTROLCOMMAND* pControlCommand);

	// 控制命令出列
	int32 libd_DequeueControlCommand(yd::CONTROLCOMMAND* pControlCommand);

	// 更新控制命令结果
	int32 libd_SetControlCommandResult(uint32 uiCommandId, const yd::COMMANDRESULT* pCommandResult);

	// 获取控制命令结果
	int32 libd_GetControlCommandResult(uint32 uiCommandId, yd::COMMANDRESULT* pCommandResult);

	// 交互命令入列
	uint32 libd_EnqueueInteractCommand(const yd::INTERACTCOMMAND* pInteractCommand);

	// 交互命令出列
	int32 libd_DequeueInteractCommand(yd::INTERACTCOMMAND* pInteractCommand);

	// 更新交互命令结果
	int32 libd_SetInteractCommandResult(uint32 uiCommandId, const yd::COMMANDRESULT* pCommandResult);

	// 获取交互命令结果
	int32 libd_GetInteractCommandResult(uint32 uiCommandId, yd::COMMANDRESULT* pCommandResult);

	// 更新逻辑状态
	int32 libd_SetLogicStates(const yd::LOGICTASKSTATES* pLogicStates);

	// 获取逻辑状态
	int32 libd_GetLogicStates(yd::LOGICTASKSTATES* pLogicStates);

	// 添加运动轴
	int32 libd_AddMotionAxis(const yd::MOTIONAXIS* pMotionAxis);
	int32 libd_AddMotionAxises(const yd::MOTIONAXIS* parrMotionAxises, uint32 uiNumber);

	// 获取运动轴
	int32 libd_GetMotionAxisById(uint16 usCard, uint16 usAxis, yd::MOTIONAXIS* pMotionAxis);
	int32 libd_GetMotionAxisByName(const std::string& strAxisName, yd::MOTIONAXIS* pMotionAxis);

	// 添加气油缸
	int32 libd_AddCylinder(const yd::CYLINDER* pCylinder);
	int32 libd_AddCylinders(const yd::CYLINDER* parrCylinders, uint32 uiNumber);

	// 获取气油缸
	int32 libd_GetCylinderById(uint32 uiCylinderId, yd::CYLINDER* pCylinder);
	int32 libd_GetCylinderByName(const std::string& strCylinderName, yd::CYLINDER* pCylinder);

	// 添加DI
	int32 libd_AddDIInfo(const yd::IOINFO* pIOInfo);
	int32 libd_AddDIInfos(const yd::IOINFO* parrIOInfos, uint32 uiNumber);

	// 获取DI
	int32 libd_GetDIInfoById(uint16 usCard, uint16 usType, uint16 usIndex, yd::IOINFO* pIOInfo);
	int32 libd_GetDIInfoByName(const std::string& strDIName, yd::IOINFO* pIOInfo);

	// 添加DO
	int32 libd_AddDOInfo(const yd::IOINFO* pIOInfo);
	int32 libd_AddDOInfos(const yd::IOINFO* parrIOInfos, uint32 uiNumber);

	// 获取DO
	int32 libd_GetDOInfoById(uint16 usCard, uint16 usType, uint16 usIndex, yd::IOINFO* pIOInfo);
	int32 libd_GetDOInfoByName(const std::string& strDOName, yd::IOINFO* pIOInfo);

	// 更新逻辑任务调试状态
	int32 libd_SetLogicTaskDebugState(uint32 uiTaskId, uint8 ucState);

	// 获取逻辑任务调试状态
	uint8 libd_GetLogicTaskDebugState(uint32 uiTaskId);

	// 更新回原点脚本执行状态
	int32 libd_SetHomeMoveScriptExecuteState(uint8 ucState);

	// 获取回原点脚本执行状态
	uint8 libd_GetHomeMoveScriptExecuteState();

#ifdef __cplusplus
};
#endif

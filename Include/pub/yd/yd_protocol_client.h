#pragma once

#include "yd_protocol.h"

namespace yd::proto {
	// 变量实时值
	typedef struct _VariableRTValue {
		std::string		strRealtimeValue;	// 实时值
		uint8			ucValueType;		// 数值类型
		uint64			ullTimestamp;		// 更新时间（Unix微秒）
	}VariableRTValue;
	using MapId2VariableRTValue = std::map<uint64, VariableRTValue>;

	// 协议客户端接口
	interface IProtocolClient : public ICountor
	{
		// 初始化
		virtual bool Initialize(
			IProtocol* pIProtocol,
			const std::string& strUser,
			const std::string& strPassword,
			const std::string& strServerIp,
			uint16 usServerPort,
			uint32 uiTimeout) = 0;

		// 反初始化
		virtual bool Unitialize() = 0;

		// 连接
		virtual bool Connect(uint8 ucMaxRetries) = 0;

		// 断开
		virtual bool Disconnect() = 0;

		// 是否连接
		virtual bool IsConnected() = 0;

		// 获取错误代码
		virtual int32 GetErrorCode() = 0;

		// 获取错误信息
		virtual const char* GetErrorMsg() = 0;

		// 获取执行时间：微秒
		virtual uint64 GetTimeConsumed() = 0;

		// 通知工作参数
		virtual int32 NotifyWorkParams(
			const std::string& strProjectName,
			const std::string& strRecipeName,
			const std::string& strReceiverAddress,
			uint16 usReceiverPort) = 0;

		// 启动逻辑控制器
		virtual int32 StartLogicController() = 0;

		// 停止逻辑控制器
		virtual int32 StopLogicController() = 0;

		// 暂停逻辑控制器
		virtual int32 SuspendLogicController() = 0;

		// 恢复逻辑控制器
		virtual int32 RestoreLogicController() = 0;

		// 逻辑控制器切换手动模式
		virtual int32 LogicControllerSwitchToManualMode() = 0;

		// 逻辑控制器切换自动模式
		virtual int32 LogicControllerSwitchToAutoMode() = 0;

		// 获取逻辑控制器状态
		virtual int32 GetLogicControllerStatus(uint8& ucStatus, uint8& ucMode) = 0;

		// 获取单个变量数据
		virtual int32 GetSingleVariableValue(
			uint64 ullVariableId,
			VariableRTValue* pVariableTRValue) = 0;

		// 更新单个变量数据
		virtual int32 SetSingleVariableValue(
			uint64 ullVariableId,
			const std::string& strVariableValue) = 0;

		// 获取多个变量数据
		virtual int32 GetMultiVariableValues(
			const std::vector<uint64>& listVariableIds,
			MapId2VariableRTValue& mapVariableId2RTValue) = 0;

		// 获取指定类型变量数据
		virtual int32 GetTypedVariableValues(
			uint8 ucVariableType,
			MapId2VariableRTValue& mapVariableId2RTValue) = 0;

		// 获取指定分组变量数据
		virtual int32 GetGroupedVariableValues(
			uint16 usGroupId,
			MapId2VariableRTValue& mapVariableId2RTValue) = 0;

		// 设置多个变量数据
		virtual int32 SetMultiVariableValues(
			const std::vector<uint64>& listVariableIds,
			const std::vector<std::string>& listVariableValues) = 0;

		// 获取运动控制设备数据
		virtual int32 GetMotionData(
			const std::vector<uint32>& listDeviceIds,
			Motions* pMotions) = 0;

		// 获取气油缸设备数据
		virtual int32 GetCylinderData(
			const std::vector<uint32>& listDeviceIds,
			Cylinders* pCylinders) = 0;

		// 获取IO设备数据
		virtual int32 GetIOData(
			const std::vector<uint32>& listDeviceIds,
			IODevices* pIODevices) = 0;

		// 获取业务逻辑状态
		virtual int32 GetLogicStates(
			const std::vector<uint32>& listTaskIds,
			LogicStates* pLogicStates) = 0;

		// 发送DO控制命令
		virtual int32 SendDOControl(
			uint32 uiDeviceId,
			uint16 usIndex,
			uint16 usType,
			bool bStatus) = 0;

		// 发送AO控制命令
		virtual int32 SendAOControl(
			uint32 uiDeviceId,
			uint16 usIndex,
			uint16 usType,
			bool bUseVariable,
			const std::string& strValue) = 0;

		// 停止轴运动
		virtual int32 StopAxisMove(
			uint32 uiDeviceId,
			uint16 usAxis,
			bool bUrgent) = 0;

		// 启动绝对运动
		virtual int32 StartAbsoluteMove(
			uint32 uiDeviceId,
			uint16 usAxis,
			bool bPositionUseVariable,
			const std::string& strPositionValue,
			bool bVelocityUseVariable,
			const std::string& strVelocityValue) = 0;

		// 启动相对运动
		virtual int32 StartRelativeMove(
			uint32 uiDeviceId,
			uint16 usAxis,
			bool bDistanceUseVariable,
			const std::string& strDistanceValue,
			bool bVelocityUseVariable,
			const std::string& strVelocityValue,
			uint8 ucDirection) = 0;

		// 启动Jog运动
		virtual int32 StartJogMove(
			uint32 uiDeviceId,
			uint16 usAxis,
			bool bVelocityUseVariable,
			const std::string& strVelocityValue,
			uint8 ucDirection) = 0;

		// 启动多轴运动
		virtual int32 StartMultiAxisesMove(
			bool bUseVariable,
			const std::string& strCoords) = 0;

		// 启动回零运动
		virtual int32 StartHomeMove(
			uint32 uiDeviceId,
			uint16 usAxis) = 0;

		// 启动原点急停
		virtual int32 StartHomeStop(
			uint32 uiDeviceId,
			uint16 usAxis) = 0;

		// 使能运动轴
		virtual int32 EnableAxis(
			uint32 uiDeviceId,
			uint16 usAxis,
			bool bEnable) = 0;

		// 清除运动轴状态
		virtual int32 ClearAxisStatus(
			uint32 uiDeviceId,
			uint16 usAxis) = 0;

		// 清零运动轴位置
		virtual int32 ZeroAxisPosition(
			uint32 uiDeviceId,
			uint16 usAxis) = 0;

		// 设置运动轴速度
		virtual int32 SetAxisVelocities(
			uint32 uiDeviceId,
			uint16 usAxis,
			yd::dev::MCAxisMoveSetup* pMCAxisMoveSetup) = 0;

		// 控制气油缸
		virtual int32 ControlCylinder(
			uint32 uiDeviceId,
			uint8 ucActionDirection) = 0;

		// 获取输入（DI）状态
		virtual int32 GetDIStates(
			uint32 uiDeviceId,
			std::map<uint64, bool>& mapId2Status) = 0;

		// 获取输出（DO）状态
		virtual int32 GetDOStates(
			uint32 uiDeviceId,
			std::map<uint64, bool>& mapId2Status) = 0;

		// 获取指定运动轴状态
		virtual int32 GetAxisState(
			uint32 uiDeviceId,
			uint16 usAxis,
			AxisState* pAxisState) = 0;

		// 获取指定气油缸状态
		virtual int32 GetCylinderState(
			uint32 uiDeviceId,
			DirectionState* pDirection1State,
			DirectionState* pDirection2State) = 0;

		// 启动任务调试
		virtual int32 StartLogicTaskDebug(
			uint32 uiTaskId,
			const std::string& strTaskConfig) = 0;

		// 停止任务调试
		virtual int32 StopLogicTaskDebug(
			uint32 uiTaskId) = 0;

		// 暂停任务调试
		virtual int32 SuspendLogicTaskDebug(
			uint32 uiTaskId) = 0;

		// 获取指定任务状态
		virtual int32 GetTaskState(
			uint32 uiTaskId,
			TaskState* pTaskState) = 0;

		// 启动回原点
		virtual int32 ExecuteHomeMove() = 0;

		// 启动主任务
		virtual int32 StartMainLogicTask() = 0;

		// 暂停主任务
		virtual int32 SuspendMainLogicTask() = 0;

		// 结束主任务
		virtual int32 StopMainLogicTask() = 0;

		// 下载项目配置
		virtual int32 DownloadProject(
			const std::string& strDirectory,
			const std::string& strProjectName) = 0;

		// 上传项目配置
		virtual int32 UploadProject(
			const std::string& strDirectory,
			std::string& strProjectName) = 0;

		// 获取后台日志信息
		virtual int32 GetLogMessages(
			uint64 ullBegin,
			uint64 ullEnd,
			std::vector<std::string>& listMessage) = 0;
	};
	typedef IProtocolClient* (*funcGetIProtocolClient)(uint32, const char*);
}

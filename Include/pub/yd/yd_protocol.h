#pragma once

#include "yd_project.h"

namespace yd {
	namespace proto {
		// 通讯协议数据类型定义
		constexpr uint16 PROTOCOL_USER_IDENTIFY = 1;
		constexpr uint16 PROTOCOL_WORK_PARARMS_NOTIFICATION = 2;
		constexpr uint16 PROTOCOL_READ_MOTION_DEVICE_DATA = 101;
		constexpr uint16 PROTOCOL_READ_CYLINDER_DATA = 102;
		constexpr uint16 PROTOCOL_READ_IO_DATA = 103;
		constexpr uint16 PROTOCOL_READ_VARIABLE_DATA = 104;
		constexpr uint16 PROTOCOL_READ_LOGIC_STATES = 105;
		constexpr uint16 PROTOCOL_READ_TYPED_VARIABLE_DATA = 106;
		constexpr uint16 PROTOCOL_READ_GROUPED_VARIABLE_DATA = 107;
		constexpr uint16 PROTOCOL_READ_NEWEST_LOGS = 181;
		constexpr uint16 PROTOCOL_SET_LOGIC_CONTROLLER = 201;
		constexpr uint16 PROTOCOL_UPDATE_VARIABLES = 202;
		constexpr uint16 PROTOCOL_OPEN_DEVICE = 301;
		constexpr uint16 PROTOCOL_CLOSE_DEVICE = 302;
		constexpr uint16 PROTOCOL_RESET_DEVICE = 303;
		constexpr uint16 PROTOCOL_STOP_DEVICE = 304;
		constexpr uint16 PROTOCOL_START_ABSOLUTE_MOVE = 401;
		constexpr uint16 PROTOCOL_START_RELATIVE_MOVE = 402;
		constexpr uint16 PROTOCOL_START_JOG_MOVE = 403;
		constexpr uint16 PROTOCOL_START_MULTI_AXISES_MOVE = 404;
		constexpr uint16 PROTOCOL_START_HOME_MOVE = 405;
		constexpr uint16 PROTOCOL_ENABLE_AXIS = 407;
		constexpr uint16 PROTOCOL_CLEAR_AXIS = 408;
		constexpr uint16 PROTOCOL_ZERO_AXIS = 409;
		constexpr uint16 PROTOCOL_SET_AXIS_VELOCITIES = 410;
		constexpr uint16 PROTOCOL_CONTROL_CYLINDER = 411;
		constexpr uint16 PROTOCOL_START_DEBUG_TASK = 412;
		constexpr uint16 PROTOCOL_STOP_DEBUG_TASK = 413;
		constexpr uint16 PROTOCOL_SUSPEND_DEBUG_TASK = 414;
		constexpr uint16 PROTOCOL_EXECUTE_HOME_MOVE = 415;
		constexpr uint16 PROTOCOL_GET_TASK_DEBUG_STATE = 416;
		constexpr uint16 PROTOCOL_GET_HOME_MOVE_EXECUTE_STATE = 417;
		constexpr uint16 PROTOCOL_SEND_DO_CONTROL = 501;
		constexpr uint16 PROTOCOL_SEND_AO_CONTROL = 502;
		constexpr uint16 PROTOCOL_GET_COMMAND_RESULT = 600;
		constexpr uint16 PROTOCOL_GET_MCDEVICE_PARAMETERS = 701;
		constexpr uint16 PROTOCOL_GET_CYLINDER_PARAMETERS = 702;
		constexpr uint16 PROTOCOL_GET_IO_PARAMETERS = 703;
		constexpr uint16 PROTOCOL_GET_VARIALBE_PARAMETERS = 704;
		constexpr uint16 PROTOCOL_GET_AXIS_VELOCITIES = 705;
		constexpr uint16 PROTOCOL_GET_LOGIC_PARAMETERS = 706;
		constexpr uint16 PROTOCOL_PUSH_UPDATED_MCDEVICE_DATA = 801;
		constexpr uint16 PROTOCOL_PUSH_UPDATED_CYLINDER_DATA = 802;
		constexpr uint16 PROTOCOL_PUSH_UPDATED_IO_DATA = 803;
		constexpr uint16 PROTOCOL_PUSH_UPDATED_LOGIC_STATES = 804;
		constexpr uint16 PROTOCOL_PUSH_UPDATED_LOGS = 805;
		constexpr uint16 PROTOCOL_PUSH_UPDATED_INTERACT_MSG = 806;
		constexpr uint16 PROTOCOL_PUSH_UPDATED_VARIABLE_DATA = 807;
		constexpr uint16 PROTOCOL_DOWNLOAD = 901;
		constexpr uint16 PROTOCOL_UPLOAD = 902;

		// 协议缓冲区大小
		constexpr uint32 MAX_PROTOCOL_BUFFER_SIZE = (2 * 1024 * 1024);

		// 协议结果数据
		typedef struct _CmdResult {
			uint32					id;
			int32					result;
			uint64					begin;
			uint64					end;
		}CmdResult;
		typedef struct _Result {
			uint64					id;
			uint32					type;
			int32					error_code;
			uint64					request_time;
			uint64					response_time;
			std::string				auth_code;
			CmdResult				command_result;
		}Result;

		// 通用数据结构
		typedef struct _IOState {
			uint16					index;
			bool					value;
		}IOState;
		typedef struct _IOGroup {
			uint16					type;
			std::vector<IOState>	values;
		}IOGroup;
		typedef struct _ReferData {
			bool					use_variable;
			std::string				refer_value;
		}ReferData;
		typedef struct _ReferDevice {
			uint32					device_id;
		}ReferDevice;
		typedef struct _ReferDevices {
			std::vector<uint32>		device_ids;
		}ReferDevices;
		typedef struct _ReferVariable {
			uint64					variable_id;
		}ReferVariable;
		typedef struct _ReferVariables {
			std::vector<uint64>		variable_ids;
		}ReferVariables;
		typedef struct _ReferVarType {
			uint8					variable_type;
		}ReferVarType;
		typedef struct _ReferCommand {
			uint32					command_id;
		}ReferCommand;
		typedef struct _ReferCommands {
			std::vector<uint32>		command_ids;
		}ReferCommands;
		typedef struct _ReferVarGrp {
			uint16					group_id;
		}ReferVarGrp;
		typedef struct _ReferVarGrps {
			std::vector<ReferVarGrp> groups;
		}ReferVarGrps;
		typedef struct _ReferLogicId {
			uint32					logic_id;
		}ReferLogicId;
		typedef struct _ReferLogicIds {
			std::vector<uint32>		logic_ids;
		}ReferLogicIds;

		// 工作参数
		typedef struct _WorkParams {
			std::string				project_name;
			std::string				recipe_name;
			std::string				receiver_address;
			uint16					receiver_port;
		}WorkParams;

		// 运动控制设备状态数据结构
		typedef struct _AxisState {
			uint16					index;				// 轴序号
			bool					driver_alarm;		// 驱动报警
			bool					follow_error;		// 跟随误差
			bool					positive_limit;		// 正向限位
			bool					negative_limit;		// 负向限位
			bool					smooth_stop;		// 平滑停止
			bool					urgent_stop;		// 紧急停止
			bool					servo_on;			// 伺服使能
			bool					profile_move;		// 运动状态
			bool					motor_arrive;		// 电机到位
			bool					home_signal;		// 原点信号
			bool					home_moved;			// 回零状态（是否执行回零运动）
			bool					driver_enable;		// 驱动使能
			uint8					home_status;		// 回零状态（0--未回零/1--回零中/2--已回零）
			uint32					profile_mode;		// 运动模式
			double					target_position;	// 目标位置
			double					target_velocity;	// 目标速度
			double					profile_position;	// 规划位置
			double					profile_velocity;	// 规划速度
			double					encoder_position;	// 编码器位置（反馈位置）
			double					encoder_velocity;	// 编码器速度（反馈速度）
			double					position_offset;	// 位置偏差
		}AxisState;
		typedef struct _Motion {
			uint32					id;
			std::vector<IOGroup>	dis;
			std::vector<IOGroup>	dos;
			std::vector<AxisState>	axises;
		}Motion;
		typedef struct _Motions {
			std::vector<Motion>		devices;
		}Motions;

		// 气油缸数据结构
		typedef struct _DirectionState {
			bool					refer_di;			// 关联DI状态（true--ON/false--OFF）
			bool					arrived;			// 是否运动到位
			bool					alarmed;			// 是否报警触发
			bool					moving;				// 是否运动中
		}DirectionState;
		typedef struct _Cylinder {
			uint32					id;
			DirectionState			direction1;
			DirectionState			direction2;
		}Cylinder;
		typedef struct _Cylinders {
			std::vector<Cylinder>	devices;
		}Cylinders;

		// IO数据结构
		typedef struct _IODevice {
			uint32					id;
			std::vector<IOGroup>	dis;
			std::vector<IOGroup>	dos;
		}IODevice;
		typedef struct _IODevices {
			std::vector<IODevice>	devices;
		}IODevices;

		// 变量数据结构
		typedef struct _VariableValue {
			uint64					id;
			uint8					type;
			std::string				value;
			uint64					timestamp;
		}VariableValue;
		typedef struct _VariableValues {
			std::vector<VariableValue>	values;
		}VariableValues;

		// 业务逻辑流程状态结构
		typedef struct _ProcState {
			uint32					id;
			uint8					state;
			uint64					begin;
			uint64					end;
		}ProcState;
		typedef struct _TaskState {
			uint32					id;
			uint8					state;
			std::vector<ProcState>	process_states;
		}TaskState;
		typedef struct _LogicStates {
			std::vector<TaskState>	task_states;
		}LogicStates;

		// 日志数据结构
		typedef struct _LogFilter {
			uint64					begin;
			uint64					end;
		}LogFilter;
		typedef struct _Log {
			uint64					time;
			uint32					process;
			uint32					thread;
			std::string				module;
			uint8					level;
			std::string				content;
		}Log;
		typedef struct _Logs {
			std::vector<Log>		logs;
		}Logs;

		// 变量参数
		typedef struct _VariableParam {
			uint64					variable_id;
			std::string				variable_name;
			uint8					variable_type;
			uint8					value_type;
			std::string				init_value;
			std::string				min_value;
			std::string				max_value;
		}VariableParam;
		typedef struct _SubVariableGroup {
			uint16					id;
			std::string				name;
			std::vector<VariableParam>	variables;
		}SubVariableGroup;
		typedef struct _MainVariableGroup {
			uint16					id;
			std::string				name;
			std::vector<SubVariableGroup>	sub_groups;
		}MainVariableGroup;
		typedef struct _MainVariableGroups {
			std::vector<MainVariableGroup>	main_groups;
		}MainVariableGroups;

		// 运动轴速度
		typedef struct _AxisVelocity {
			uint16					index;
			double					velocity;
			double					acceleration;
			double					deceleration;
			double					takeoff_velocity;
			double					manual_velocity;
			uint32					smooth_time;
			double					smooth_factor;
		}AxisVelocity;
		typedef struct _DeviceVelocity {
			uint32					id;
			std::vector<AxisVelocity>	axises;
		}DeviceVelocity;
		typedef struct _DeviceVelocities {
			std::vector<DeviceVelocity>	devices;
		}DeviceVelocities;

		// 业务逻辑流程配置
		typedef struct _LogicProcParam {
			uint32					id;
			uint32					previous_id;
			uint32					next_id;
			uint8					type;
			std::string				name;
		}LogicProcParam;
		typedef struct _LogicSubTaskParam {
			uint32						id;
			std::string					name;
			std::vector<LogicProcParam>	processes;
		}LogicSubTaskParam;
		typedef struct _LogicTaskParam {
			uint32							id;
			std::string						name;
			std::vector<LogicSubTaskParam>	subtasks;
			std::vector<LogicProcParam>		processes;
		}LogicTaskParam;
		typedef struct _LogicTaskParams {
			std::vector<LogicTaskParam>		tasks;
		}LogicTaskParams;

		// 变量更新数据结构
		typedef struct _CmdVariableValue {
			uint64					id;
			std::string				value;
		}CmdVariableValue;
		typedef struct _CmdVariableValues {
			std::vector<CmdVariableValue>	values;
		}CmdVariableValues;

		// 控制器命令数据结构
		typedef struct _CmdController {
			uint8					action_type;
		}CmdController;

		// 设备停止数据结构
		typedef struct _CmdDeviceStop {
			uint32					device_id;
			uint16					axis;
			bool					urgent;
		}CmdDeviceStop;

		// 绝对运动数据结构
		typedef struct _CmdAbosulteMove {
			uint32					device_id;
			uint16					axis;
			ReferData				position;
			ReferData				velocity;
			uint8					direction;
		}CmdAbosulteMove;

		// 相对运动数据结构
		typedef struct _CmdRelativeMove {
			uint32					device_id;
			uint16					axis;
			ReferData				distance;
			ReferData				velocity;
			uint8					direction;
		}CmdRelativeMove;

		// Jog运动数据结构
		typedef struct _CmdJogMove {
			uint32					device_id;
			uint16					axis;
			ReferData				velocity;
			uint8					direction;
		}CmdJogMove;

		// 多轴运动数据结构
		typedef struct _CmdMultiAxisesMove {
			ReferData				coords;
		}CmdMultiAxisesMove;

		// 回零运动数据结构
		typedef struct _CmdHomeMove {
			uint32					device_id;
			uint16					axis;
		}CmdHomeMove;

		// 原点急停数据结构
		typedef struct _CmdHomeStop {
			uint32					device_id;
			uint16					axis;
		}CmdHomeStop;

		// DO控制数据结构
		typedef struct _CmdDOControl {
			uint32					device_id;
			uint16					index;
			uint16					type;
			bool					status;
		}CmdDOControl;

		// AO控制数据结构
		typedef struct _CmdAOControl {
			uint32					device_id;
			uint16					index;
			uint16					type;
			ReferData				value;
		}CmdAOControl;

		// 控制指令结果数据结构
		typedef struct _CmdResults {
			std::vector<CmdResult>	results;
		}CmdResults;

		// 运动轴使能
		typedef struct _CmdAxisEnable {
			uint32					device_id;
			uint16					axis;
			bool					enable;
		}CmdAxisEnable;

		// 运动轴状态清除
		typedef struct _CmdAxisStatusClear {
			uint32					device_id;
			uint16					axis;
		}CmdAxisStatusClear;

		// 运动轴位置清零
		typedef struct _CmdAxisZeroPosition {
			uint32					device_id;
			uint16					axis;
		}CmdAxisZeroPosition;

		// 运动轴速度设定
		typedef struct _CmdAxisVelocitySetup {
			uint32					device_id;
			uint16					axis;
			double					velocity;
			double					acceleration;
			double					deceleration;
			double					takeoff_velocity;
			double					manual_velocity;
			uint32					smooth_time;
			double					smooth_factor;
		}CmdAxisVelocitySetup;

		// 控制气油缸
		typedef struct _CmdCylinderControl {
			uint32					device_id;
			uint8					action_direction;
		}CmdCylinderControl;

		// 调试任务
		typedef struct _CmdDebugTask {
			uint32					task_id;
			std::string				task_config;
		}CmdDebugTask;

		// 项目参数（上传/下载）
		typedef struct _CmdProjectItem {
			std::string					name;
			std::string					content;
		}CmdProjectItem;
		typedef struct _CmdProject {
			CmdProjectItem				project;
			std::vector<CmdProjectItem>	recipes;
		}CmdProject;
		typedef struct _CmdProjects {
			std::vector<CmdProject>		projects;
		}CmdProjects;

		// 协议接口
		interface IProtocol : public ICountor
		{
			// 错误代码
			virtual int32 SetErrorCode(int32 iErrorCode) = 0;
			virtual int32 GetErrorCode() const = 0;

			// 认证授权码
			virtual int32 SetAuthIdentityCode(const std::string& strAuthCode) = 0;
			virtual const std::string& GetAuthIdentityCode() = 0;

			// 获取请求/响应结果
			virtual int32 GetRequestResult(Result* pResult) = 0;
			virtual int32 GetResponseResult(Result* pResult) = 0;
			virtual Result* RequestResult() = 0;
			virtual Result* ResponseResult() = 0;

			// 解析协议公共数据
			virtual int32 DecodePublicData(const std::string& strInputData, Result* pOutputData) = 0;

			// 轴坐标数据与Json字符串互转
			virtual bool AxisCoords2Json(const yd::COORDS* pCoords, std::string& strJson) = 0;
			virtual bool Json2AxisCoords(const std::string& strJson, yd::COORDS* pCoords) = 0;

			// 协议认证
			virtual int32 EncodeRequestOfAuthIdentity(const std::string& strUser, const std::string& strPassword, std::string& strOutputData) = 0;
			virtual int32 DecodeRequestOfAuthIdentity(const std::string& strInputData, std::string& strUser, std::string& strPassword) = 0;
			virtual int32 EncodeResponseOfAuthIdentity(std::string& strOutputData) = 0;
			virtual int32 DecodeResponseOfAuthIdentity(const std::string& strInputData) = 0;

			// 工作参数通知
			virtual int32 EncodeRequestOfWorkParamsNotification(WorkParams* pInputData, std::string& strOutputData) = 0;
			virtual int32 DecodeRequestOfWorkParamsNotification(const std::string& strInputData, WorkParams* pOutputData) = 0;

			// 运动设备参数
			virtual int32 EncodeResponseOfMCDeviceParameters(std::vector<yd::dev::MCDevice*>& listDevices, std::string& strOutputData) = 0;

			// 气油缸参数
			virtual int32 EncodeResponseOfCylinderParameters(std::vector<yd::dev::Cylinder*>& listDevices, std::string& strOutputData) = 0;

			// 变量参数
			virtual int32 EncodeResponseOfVariableParameters(MainVariableGroups* pInputData, std::string& strOutputData) = 0;

			// 运动轴速度参数
			virtual int32 EncodeResponseOfAxisVelocityParameters(DeviceVelocities* pInputData, std::string& strOutputData) = 0;

			// 业务逻辑流程参数
			virtual int32 EncodeResponseOfLogicParameters(LogicTaskParams* pInputData, std::string& strOutputData) = 0;

			// 运动控制设备状态
			virtual int32 EncodeRequestOfMotionData(ReferDevices* pInputData, std::string& strOutputData) = 0;
			virtual int32 DecodeRequestOfMotionData(const std::string& strInputData, ReferDevices* pOutputData) = 0;
			virtual int32 EncodeResponseOfMotionData(Motions* pInputData, std::string& strOutputData) = 0;
			virtual int32 DecodeResponseOfMotionData(const std::string& strInputData, Motions* pOutputData) = 0;

			// 气油缸状态
			virtual int32 EncodeRequestOfCylinderData(ReferDevices* pInputData, std::string& strOutputData) = 0;
			virtual int32 DecodeRequestOfCylinderData(const std::string& strInputData, ReferDevices* pOutputData) = 0;
			virtual int32 EncodeResponseOfCylinderData(Cylinders* pInputData, std::string& strOutputData) = 0;
			virtual int32 DecodeResponseOfCylinderData(const std::string& strInputData, Cylinders* pOutputData) = 0;

			// IO状态
			virtual int32 EncodeRequestOfIOData(ReferDevices* pInputData, std::string& strOutputData) = 0;
			virtual int32 DecodeRequestOfIOData(const std::string& strInputData, ReferDevices* pOutputData) = 0;
			virtual int32 EncodeResponseOfIOData(IODevices* pInputData, std::string& strOutputData) = 0;
			virtual int32 DecodeResponseOfIOData(const std::string& strInputData, IODevices* pOutputData) = 0;

			// 变量数据
			virtual int32 EncodeRequestOfVariableData(ReferVariables* pInputData, std::string& strOutputData) = 0;
			virtual int32 DecodeRequestOfVariableData(const std::string& strInputData, ReferVariables* pOutputData) = 0;
			virtual int32 EncodeResponseOfVariableData(uint16 usExpectedProtocolType, VariableValues* pInputData, std::string& strOutputData) = 0;
			virtual int32 DecodeResponseOfVariableData(uint16 usExpectedProtocolType, const std::string& strInputData, VariableValues* pOutputData) = 0;

			// 类型变量数据
			virtual int32 EncodeRequestOfTypedVariableData(ReferVarType* pInputData, std::string& strOutputData) = 0;
			virtual int32 DecodeRequestOfTypedVariableData(const std::string& strInputData, ReferVarType* pOutputData) = 0;

			// 分组变量数据
			virtual int32 EncodeRequestOfGroupedVariableData(ReferVarGrp* pInputData, std::string& strOutputData) = 0;
			virtual int32 DecodeRequestOfGroupedVariableData(const std::string& strInputData, ReferVarGrp* pOutputData) = 0;

			// 业务逻辑流程状态
			virtual int32 EncodeRequestOfLogicStates(ReferLogicIds* pInputData, std::string& strOutputData) = 0;
			virtual int32 DecodeRequestOfLogicStates(const std::string& strInputData, ReferLogicIds* pOutputData) = 0;
			virtual int32 EncodeResponseOfLogicStates(LogicStates* pInputData, std::string& strOutputData) = 0;
			virtual int32 DecodeResponseOfLogicStates(const std::string& strInputData, LogicStates* pOutputData) = 0;

			// 最新日志消息
			virtual int32 EncodeRequestOfNewestLogs(LogFilter* pInputData, std::string& strOutputData) = 0;
			virtual int32 DecodeRequestOfNewestLogs(const std::string& strInputData, LogFilter* pOutputData) = 0;
			virtual int32 EncodeResponseOfNewestLogs(Logs* pInputData, std::string& strOutputData) = 0;
			virtual int32 DecodeResponseOfNewestLogs(const std::string& strInputData, Logs* pOutputData) = 0;

			// 控制指令结果
			virtual int32 EncodeResponseOfCommand(Result* pInputData, std::string& strOutputData) = 0;
			virtual int32 DecodeResponseOfCommand(const std::string& strInputData, Result* pOutputData) = 0;

			// 无参数请求
			virtual int32 EncodeRequestWithNone(const uint16& usRequestType, std::string& strOutputData) = 0;
			virtual int32 DecodeRequestWithNone(const std::string& strInputData, uint16& usRequestType) = 0;

			// 逻辑控制器命令
			virtual int32 EncodeRequestOfControllerCommand(CmdController* pInputData, std::string& strOutputData) = 0;
			virtual int32 DecodeRequestOfControllerCommand(const std::string& strInputData, CmdController* pOutputData) = 0;

			// 变量更新命令
			virtual int32 EncodeRequestOfVariablesUpdate(CmdVariableValues* pInputData, std::string& strOutputData) = 0;
			virtual int32 DecodeRequestOfVariablesUpdate(const std::string& strInputData, CmdVariableValues* pOutputData) = 0;

			// 打开设备命令
			virtual int32 EncodeRequestOfDeviceOpen(ReferDevice* pInputData, std::string& strOutputData) = 0;
			virtual int32 DecodeRequestOfDeviceOpen(const std::string& strInputData, ReferDevice* pOutputData) = 0;

			// 关闭设备命令
			virtual int32 EncodeRequestOfDeviceClose(ReferDevice* pInputData, std::string& strOutputData) = 0;
			virtual int32 DecodeRequestOfDeviceClose(const std::string& strInputData, ReferDevice* pOutputData) = 0;

			// 复位设备命令
			virtual int32 EncodeRequestOfDeviceReset(ReferDevice* pInputData, std::string& strOutputData) = 0;
			virtual int32 DecodeRequestOfDeviceReset(const std::string& strInputData, ReferDevice* pOutputData) = 0;

			// 停止设备命令
			virtual int32 EncodeRequestOfDeviceStop(CmdDeviceStop* pInputData, std::string& strOutputData) = 0;
			virtual int32 DecodeRequestOfDeviceStop(const std::string& strInputData, CmdDeviceStop* pOutputData) = 0;

			// 绝对运动命令
			virtual int32 EncodeRequestOfAbsoluteMove(CmdAbosulteMove* pInputData, std::string& strOutputData) = 0;
			virtual int32 DecodeRequestOfAbsoluteMove(const std::string& strInputData, CmdAbosulteMove* pOutputData) = 0;

			// 相对运动命令
			virtual int32 EncodeRequestOfRelativeMove(CmdRelativeMove* pInputData, std::string& strOutputData) = 0;
			virtual int32 DecodeRequestOfRelativeMove(const std::string& strInputData, CmdRelativeMove* pOutputData) = 0;

			// Jog运动命令
			virtual int32 EncodeRequestOfJogMove(CmdJogMove* pInputData, std::string& strOutputData) = 0;
			virtual int32 DecodeRequestOfJogMove(const std::string& strInputData, CmdJogMove* pOutputData) = 0;

			// 多轴运动命令
			virtual int32 EncodeRequestOfMultiAxisesMove(CmdMultiAxisesMove* pInputData, std::string& strOutputData) = 0;
			virtual int32 DecodeRequestOfMultiAxisesMove(const std::string& strInputData, CmdMultiAxisesMove* pOutputData) = 0;

			// 回零运动命令
			virtual int32 EncodeRequestOfHomeMove(CmdHomeMove* pInputData, std::string& strOutputData) = 0;
			virtual int32 DecodeRequestOfHomeMove(const std::string& strInputData, CmdHomeMove* pOutputData) = 0;

			// DO控制命令
			virtual int32 EncodeRequestOfDOControl(CmdDOControl* pInputData, std::string& strOutputData) = 0;
			virtual int32 DecodeRequestOfDOControl(const std::string& strInputData, CmdDOControl* pOutputData) = 0;

			// AO控制命令
			virtual int32 EncodeRequestOfAOControl(CmdAOControl* pInputData, std::string& strOutputData) = 0;
			virtual int32 DecodeRequestOfAOControl(const std::string& strInputData, CmdAOControl* pOutputData) = 0;

			// 运动轴使能
			virtual int32 EncodeRequestOfAxisEnable(CmdAxisEnable* pInputData, std::string& strOutputData) = 0;
			virtual int32 DecodeRequestOfAxisEnable(const std::string& strInputData, CmdAxisEnable* pOutputData) = 0;

			// 运动轴状态清除
			virtual int32 EncodeRequestOfAxisStatusClear(CmdAxisStatusClear* pInputData, std::string& strOutputData) = 0;
			virtual int32 DecodeRequestOfAxisStatusClear(const std::string& strInputData, CmdAxisStatusClear* pOutputData) = 0;

			// 运动轴位置清零
			virtual int32 EncodeRequestOfAxisZeroPosition(CmdAxisZeroPosition* pInputData, std::string& strOutputData) = 0;
			virtual int32 DecodeRequestOfAxisZeroPosition(const std::string& strInputData, CmdAxisZeroPosition* pOutputData) = 0;

			// 运动轴速度设定
			virtual int32 EncodeRequestOfAxisVelocitiesSetup(CmdAxisVelocitySetup* pInputData, std::string& strOutputData) = 0;
			virtual int32 DecodeRequestOfAxisVelocitiesSetup(const std::string& strInputData, CmdAxisVelocitySetup* pOutputData) = 0;

			// 控制气油缸
			virtual int32 EncodeRequestOfCylinderControl(CmdCylinderControl* pInputData, std::string& strOutputData) = 0;
			virtual int32 DecodeRequestOfCylinderControl(const std::string& strInputData, CmdCylinderControl* pOutputData) = 0;

			// 调试任务
			virtual int32 EncodeRequestOfTaskDebugStart(const uint16& usExpectedType, CmdDebugTask* pInputData, std::string& strOutputData) = 0;
			virtual int32 DecodeRequestOfTaskDebugStart(const uint16& usExpectedType, const std::string& strInputData, CmdDebugTask* pOutputData) = 0;
			virtual int32 EncodeRequestOfTaskDebugStop(const uint16& usExpectedType, const uint32& uiTaskId, std::string& strOutputData) = 0;
			virtual int32 DecodeRequestOfTaskDebugStop(const uint16& usExpectedType, const std::string& strInputData, uint32& uiTaskId) = 0;
			virtual int32 EncodeRequestOfTaskDebugSuspend(const uint16& usExpectedType, const uint32& uiTaskId, std::string& strOutputData) = 0;
			virtual int32 DecodeRequestOfTaskDebugSuspend(const uint16& usExpectedType, const std::string& strInputData, uint32& uiTaskId) = 0;

			// 任务调试状态
			virtual int32 EncodeRequestOfTaskDebugState(const uint32& uiTaskId, std::string& strOutputData) = 0;
			virtual int32 DecodeRequestOfTaskDebugState(const std::string& strInputData, uint32& uiTaskId) = 0;
			virtual int32 EncodeResponseOfTaskDebugState(const uint8& ucState, std::string& strOutputData) = 0;
			virtual int32 DecodeResponseOfTaskDebugState(const std::string& strInputData, uint8& ucState) = 0;

			// 回原点执行状态
			virtual int32 EncodeResponseOfHomeMoveScriptState(const uint8& ucState, std::string& strOutputData) = 0;
			virtual int32 DecodeResponseOfHomeMoveScriptState(const std::string& strInputData, uint8& ucState) = 0;

			// 控制指令结果
			virtual int32 EncodeRequestOfCommandResults(ReferCommands* pInputData, std::string& strOutputData) = 0;
			virtual int32 DecodeRequestOfCommandResults(const std::string& strInputData, ReferCommands* pOutputData) = 0;
			virtual int32 EncodeResponseOfCommandResults(CmdResults* pInputData, std::string& strOutputData) = 0;
			virtual int32 DecodeResponseOfCommandResults(const std::string& strInputData, CmdResults* pOutputData) = 0;

			// 交互消息
			virtual int32 EncodeRequestOfInteractMessage(const INTERACTMESSAGE* pInputData, std::string& strOutputData) = 0;
			virtual int32 DecodeRequestOfInteractMessage(const std::string& strInputData, INTERACTMESSAGE* pOutputData) = 0;
			virtual int32 EncodeResponseOfInteractMessage(const INTERACTRESULT* pInputData, std::string& strOutputData) = 0;
			virtual int32 DecodeResponseOfInteractMessage(const std::string& strInputData, INTERACTRESULT* pOutputData) = 0;

			// 项目下载
			virtual int32 EncodeRequestOfDownload(const CmdProject* pInputData, std::string& strOutputData) = 0;
			virtual int32 DecodeRequestOfDownload(const std::string& strInputData, CmdProject* pOutputData) = 0;
			virtual int32 EncodeResponseOfDownload(Result* pInputData, std::string& strOutputData) = 0;
			virtual int32 DecodeResponseOfDownload(const std::string& strInputData, Result* pOutputData) = 0;

			// 项目上传
			virtual int32 EncodeRequestOfUpload(std::string& strOutputData) = 0;
			virtual int32 DecodeRequestOfUpload(const std::string& strInputData) = 0;
			virtual int32 EncodeResponseOfUpload(const CmdProject* pInputData, std::string& strOutputData) = 0;
			virtual int32 DecodeResponseOfUpload(const std::string& strInputData, CmdProject* pOutputData) = 0;
		};
		typedef IProtocol* (*funcGetIProtocol)(uint32, const char*);
	}
}

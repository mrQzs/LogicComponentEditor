#pragma once


#include <platform.h>
#include <cstring>
#include <cstdlib>
#include <string>
#include <map>

namespace yd
{
	// 设备类型
	typedef struct _PreDIType {
		uint8			ucTypeId;
		char			szTypeName[VARIABLE_NAME_LENGTH + 1];
		uint8			ucNumber;
	}PREDITYPE;
	typedef struct _PreDOType {
		uint8			ucTypeId;
		char			szTypeName[VARIABLE_NAME_LENGTH + 1];
		uint8			ucNumber;
	}PREDOTYPE;
	typedef struct _PreAIType {
		uint8			ucTypeId;
		char			szTypeName[VARIABLE_NAME_LENGTH + 1];
		uint8			ucNumber;
	}PREAITYPE;
	typedef struct _PreAOType {
		uint8			ucTypeId;
		char			szTypeName[VARIABLE_NAME_LENGTH + 1];
		uint8			ucNumber;
	}PREAOTYPE;
	typedef struct _PreDeviceType {
		uint32			uiTypeId;
		char			szTypeName[VARIABLE_NAME_LENGTH + 1];
		char			szModel[VARIABLE_NAME_LENGTH + 1];
		char			szVendor[VARIABLE_NAME_LENGTH + 1];
		char			szLibrary[VARIABLE_NAME_LENGTH + 1];
		bool			bExtended;
		uint8			ucCardStart;
		uint8			ucCardEnd;
		uint8			ucAxisStart;
		uint8			ucAxisEnd;
		PREDITYPE		arrDITypes[MAX_IO_TYPE_NUMBER];
		uint8			ucDITypeNumber;
		PREDOTYPE		arrDOTypes[MAX_IO_TYPE_NUMBER];
		uint8			ucDOTypeNumber;
		PREAITYPE		arrAITypes[MAX_IO_TYPE_NUMBER];
		uint8			ucAITypeNumber;
		PREAOTYPE		arrAOTypes[MAX_IO_TYPE_NUMBER];
		uint8			ucAOTypeNumber;
	}PREDEVICETYPE;
	typedef struct _PreDeviceTypes {
		PREDEVICETYPE	arrPreDeviceTypes[MAX_DEVICE_TYPE_NUBMER];
		uint8			ucNumber;
	}PREDEVICETYPES;
	// 参考值
	typedef struct _ReferValue {
		bool			bUseVariable;
		char			szValue[VARIABLE_VALUE_LENGTH + 1];
	}REFERVALUE;
	// 数据点定义
	typedef struct _Coord {
		uint32			uiDeviceId;							// 所属设备id
		uint16			usCard;								// 运动卡
		uint16			usAxis;								// 运动轴
		uint8			ucType;								// 运动类型
		uint8			ucDirection;						// 运动方向
		REFERVALUE		refTarget;							// 运动目标
		REFERVALUE		refVelocity;						// 运动速度
	}COORD;
	typedef struct _Coords {
		COORD			arrCoords[MAX_AXIS_COORD_NUMBER];
		uint8			ucNumber;							// 坐标个数
		uint8			ucCtrlType;							// 控制类型
	}COORDS;
	typedef struct _VRValue {
		union _unValue {
			bool		bValue;
			int8		cValue;
			uint8		ucValue;
			int16		sValue;
			uint16		usValue;
			int32		iValue;
			uint32		uiValue;
			int64		llValue;
			uint64		ullValue;
			float		fValue;
			double		dblValue;
			char		szValue[VARIABLE_VALUE_LENGTH + 1];
			COORDS		coords;
		}unValue;											// 数据点数值
		uint32			uiIndex;							// 序号
		uint64			ullTimestamp;						// 最后更新时间：微秒
	}VRVALUE;
	// 变量定义
	typedef struct _VRVariable {
		uint64			ullVariableId;						// 变量id
		char			szVariableName[VARIABLE_NAME_LENGTH + 1];// 变量名称
		uint8			ucVariableType;						// 变量类型
		uint8			ucValueType;						// 数据类型
		double			dblMaxValue;						// 最大值
		double			dblMinValue;						// 最小值
		VRVALUE			curValue;							// 当前值
	}VRVARIABLE;
	typedef struct _VRVariables {
		VRVARIABLE		arrVariables[MAX_TOTAL_VARIABLE_NUMBER];
		uint32			uiNumber;
	}VRVARIABLES;
	// 业务逻辑流程状态
	typedef struct _LogicProcState {
		uint32			uiProcessId;
		uint8			ucProcessState;
		uint64			ullBegin;
		uint64			ullEnd;
	}LOGICPROCSTATE;
	typedef struct _LogicTaskState {
		uint32			uiTaskId;
		uint8			ucTaskState;
		LOGICPROCSTATE	arrProcesses[MAX_LOGIC_PROCESS_NUMBER_EACH_TASK];
		uint32			uiProcessNumber;
	}LOGICTASKSTATE;
	typedef struct _LogicTaskStates {
		LOGICTASKSTATE	arrTasks[MAX_LOGIC_TASK_NUMBER];
		uint32			uiTaskNumber;
	}LOGICTASKSTATES;
	// 命令结果
	typedef struct _CommandResult {
		uint32			uiCommandId;						// 命令id：系统唯一
		uint64			ullBeginTime;						// 开始时间：微秒
		uint64			ullEndTime;							// 结束时间：微秒
		int32			iResult;							// 执行结果
		uint64			ullData;							// 附加数据
	}COMMANDRESULT;
	// 控制命令
	typedef struct _CtrlCmdData {
		uint8			ucActionType;						// 动作类型：启动/停止/暂停/恢复/手动/自动
	}CTRLCMDDATA;
	typedef struct _VarCmdData {
		struct _Variable {
			uint64		ullId;								// 变量id
			char		szValue[8192 + 1];					// 变量值
		}arrVariables[MAX_COMMAND_VALUE_NUMBER];			// 变量数组
		uint32			uiNumber;							// 变量个数
	}VARCMDDATA;
	typedef struct _ProcMethodCmdData {
		uint32			uiProcessId;						// 流程id
		VARCMDDATA		varCmdData;							// 变量数据（可选）
	}PROCMETHODCMDDATA;
	typedef struct _DevOpenCmdData {
		uint32			uiDeviceId;							// 设备id
	}DEVOPENCMDDATA;
	typedef struct _DevCloseCmdData {
		uint32			uiDeviceId;							// 设备id
	}DEVCLOSECMDDATA;
	typedef struct _DevResetCmdData {
		uint32			uiDeviceId;							// 设备id
	}DEVRESETCMDDATA;
	typedef struct _DevStopCmdData {
		uint32			uiDeviceId;							// 设备id
		uint16			usAxis;								// 轴序号
		bool			bUrgent;							// 是否急停
	}DEVSTOPCMDDATA;
	typedef struct _DevReadCmdData {
		uint32			uiDeviceId;							// 设备id
	}DEVREADCMDDATA;
	typedef struct _DevZeroCmdData {
		uint32			uiDeviceId;							// 设备id
		uint16			usDataId;							// 数据id
	}DEVZEROCMDDATA;
	typedef struct _AbsoluteMoveCmdData {
		uint32			uiDeviceId;							// 设备id
		uint16			usAxis;								// 轴序号
		REFERVALUE		refPosition;						// 目标位置
		REFERVALUE		refVelocity;						// 目标速度
		uint8			ucDirection;						// 运动方向
	}ABSOLUTEMOVECMDDATA;
	typedef struct _RelativeMoveCmdData {
		uint32			uiDeviceId;							// 设备id
		uint16			usAxis;								// 轴序号
		REFERVALUE		refDistance;						// 运动距离
		REFERVALUE		refVelocity;						// 目标速度
		uint8			ucDirection;						// 运动方向
	}RELATIVEMOVECMDDATA;
	typedef struct _JogMoveCmdData {
		uint32			uiDeviceId;							// 设备id
		uint16			usAxis;								// 轴序号
		REFERVALUE		refVelocity;						// 目标速度
		uint8			ucDirection;						// 运动方向
	}JOGMOVECMDDATA;
	typedef struct _MultiAxisesMoveCmdData {
		bool			bUseVariable;
		union _unCoords {
			struct _ReferVariable {
				uint64	ullVariableId;
			}			ReferVariable;
			COORDS		ReferCoords;
		}unCoords;
	}MULTIAXISESMOVECMDDATA;
	typedef struct _HomeMoveCmdData {
		uint32			uiDeviceId;							// 设备id
		uint16			usAxis;								// 轴序号
	}HOMEMOVECMDDATA;
	typedef struct _DOCtrlCmdData {
		uint32			uiDeviceId;							// 设备id
		uint16			usIndex;							// 序号
		uint16			usType;								// 类型
		bool			bStatus;							// 状态
	}DOCTRLCMDDATA;
	typedef struct _AOCtrlCmdData {
		uint32			uiDeviceId;							// 设备id
		uint16			usIndex;							// 序号
		uint16			usType;								// 类型
		REFERVALUE		refValue;							// 数值
	}AOCTRLCMDDATA;
	typedef struct _DevSetupCmdData {
		uint32			uiDeviceId;							// 设备id
		uint16			usDataId;							// 数据id
		uint8			ucType;								// 类型
		char			szValue[TEXT_CONTENT + 1];			// 数值
	}DEVSETUPCMDDATA;
	typedef struct _AxisEnableCmdData {
		uint32			uiDeviceId;							// 设备id
		uint16			usAxis;								// 轴序号
		bool			bEnable;							// 使能
	}AXISENABLECMDDATA;
	typedef struct _AxisClearCmdData {
		uint32			uiDeviceId;							// 设备id
		uint16			usAxis;								// 轴序号
	}AXISCLEARCMDDATA;
	using AXISPOSZEROCMDDATA = AXISCLEARCMDDATA;
	typedef struct _AxisVelocityCmdData {
		uint32			uiDeviceId;							// 设备id
		uint16			usAxis;								// 轴序号
		double			dblVelocity;						// 运动速度
		double			dblAcceleration;					// 加速度
		double			dblDeceleration;					// 减速度
		double			dblTakeoffVelocity;					// 起跳速度
		double			dblManualVelocity;					// 手动运动速度
		uint32			uiSmoothTime;						// 平滑时间
		double			dblSmoothFactor;					// 平滑系数
	}AXISVELOCITYCMDDATA;
	typedef struct _CylinderCtrlCmdData {
		uint32			uiDeviceId;							// 设备id
		uint8			ucActionDirection;					// 动作方向
	}CYLINDERCTRLCMDDATA;
	typedef struct _TaskDebugCmdData {
		uint32			uiTaskId;
		char			szTaskCfgFile[200 + 1];
	}TASKDEBUGCMDDATA;
	typedef struct _ControlCommand {
		uint32						uiCommandId;			// 命令id：系统唯一
		uint8						ucCommandType;			// 命令类型
		union _unCommandData {
			CTRLCMDDATA				ctrlCmdData;			// 逻辑控制器命令数据
			VARCMDDATA				varCmdData;				// 变量更新命令数据
			PROCMETHODCMDDATA		procMethodCmdData;		// 逻辑流程方法命令数据（必须关联流程接口方法实例）
			DEVOPENCMDDATA			devOpenCmdData;			// 设备打开命令数据
			DEVCLOSECMDDATA			devCloseCmdData;		// 设备关闭命令数据
			DEVRESETCMDDATA			devResetCmdData;		// 设备复位命令数据
			DEVSTOPCMDDATA			devStopCmdData;			// 设备停止命令数据
			DEVREADCMDDATA			devReadCmdData;			// 设备采样命令数据
			DEVZEROCMDDATA			devZeroCmdData;			// 设备清零命令数据
			DEVSETUPCMDDATA			devSetupCmdData;		// 设备配置命令数据
			ABSOLUTEMOVECMDDATA		absoluteMoveCmdData;	// 绝对运动命令数据
			RELATIVEMOVECMDDATA		relativeMoveCmdData;	// 相对运动命令数据
			JOGMOVECMDDATA			jogMoveCmdData;			// Jog运动命令数据
			MULTIAXISESMOVECMDDATA	multiAxisesMoveCmdData;	// 多轴运动命令数据
			HOMEMOVECMDDATA			homeMoveCmdData;		// 回零运动命令数据
			DOCTRLCMDDATA			doCtrlCmdData;			// DO控制命令数据
			AOCTRLCMDDATA			aoCtrlCmdData;			// AO控制命令数据
			AXISENABLECMDDATA		axisEnableCmdData;		// 轴使能命令数据
			AXISCLEARCMDDATA		axisClearCmdData;		// 轴状态清除命令数据
			AXISPOSZEROCMDDATA		axisPosZeroCmdData;		// 轴位置清零命令数据
			AXISVELOCITYCMDDATA		axiVelocityCmdData;		// 轴速度命令数据
			CYLINDERCTRLCMDDATA		cylinderCtrlCmdData;	// 气油缸控制数据
			TASKDEBUGCMDDATA		taskDebugCmdData;		// 任务调试数据
		}unCommandData;
	}CONTROLCOMMAND;
	typedef struct _InteractAction {
		uint8			ucActionType;						// 动作类型
		char			szActionName[TEXT_MID + 1];			// 动作名称
		bool			bSelected;							// 是否勾选
	}INTERACTACTION;
	// 交互命令
	typedef struct _InteractCommand {
		uint32			uiCommandId;						// 命令id：系统唯一
		uint8			ucCommandType;						// 命令类型
		uint8			ucCommandLevel;						// 命令级别
		INTERACTACTION	arrActions[MAX_INTERACT_ACTION_NUMBER];// 允许的动作类型
		uint8			ucActionNumber;						// 允许动作类型个数
		char			szMessage[MESSAGE_CONTENT_LENGTH + 1];// 内容
	}INTERACTCOMMAND;
	// 交互结果
	typedef struct _InteractResult {
		uint32			uiCommandId;						// 命令id：系统唯一
		uint8			ucActionCommand;					// 动作指令
		uint32			uiActionValue;						// 动作值
	}INTERACTRESULT;
	// 交互消息
	typedef struct _InteractMessage {
		uint32			uiCommandId;						// 命令id：系统唯一
		uint8			ucLevel;
		char			szMessage[MESSAGE_CONTENT_LENGTH + 1];
		INTERACTACTION	arrActions[MAX_INTERACT_ACTION_NUMBER];// 允许的动作类型
		uint8			ucActionNumber;						// 允许动作类型个数
	}INTERACTMESSAGE;
	// 项目参数
	typedef struct _ProjectParam {
		uint32			uiVersion;							// 版本号
		char			szName[TEXT_BIG + 1];				// 项目名称
		char			szRecipe[TEXT_BIG + 1];				// 配方名称
	}PROJECTPARAM;
	// 接收服务器
	typedef struct _DataReceiver {
		char			szAddress[TEXT_MID + 1];			// 地址
		uint16			usPort;								// 端口
	}DATARECEIVER;
	typedef struct _DataReceivers {
		DATARECEIVER	arrReceivers[MAX_DATA_RECEIVER_NUMBER];// 接收服务器数组
		uint8			ucNumber;							// 接收服务器个数
	}DATARECEIVERS;
	// 消息
	typedef struct _Message {
		uint64			ullExtendData;
		uint64			ullTime;
		uint32			uiProcessId;
		uint32			uiThreadId;
		uint8			ucLevel;
		char			szModule[MESSAGE_NAME_LENGTH + 1];
		char			szMessage[MESSAGE_CONTENT_LENGTH + 1];
	}MESSAGE;
	typedef struct _Messages {
		MESSAGE			arrMessages[MAX_MESSAGE_NUMBER];
		uint32			uiNumber;
	}MESSAGES;
	typedef struct MessageFilter {
		char			szBeginTime[MESSAGE_TIME_LENGTH + 1];
		char			szEndTime[MESSAGE_TIME_LENGTH + 1];
		uint8			arrLevels[MESSAGE_FILTER_LENGTH];
		int32			iLevelNumber;
		char			arrModules[MESSAGE_FILTER_LENGTH][MESSAGE_NAME_LENGTH + 1];
		int32			iModuleNumber;
		char			arrKeywords[MESSAGE_FILTER_LENGTH][MESSAGE_NAME_LENGTH + 1];
		int32			iKeywordNumber;
		uint64			ullTotalRecords;
		uint64			ullTotalPages;
		uint64			ullPageRecords;
		uint64			ullPageIndex;
	}MESSAGEFILTER;
	//接口用户数据
	typedef struct _InterfaceUserData {
		uint32			uiMask;
	}INTERFACEUSERDATA;

	// 运动轴
	typedef struct _MotionAxis {
		uint32			uiDeviceId;
		uint16			usCard;
		uint16			usAxis;
		char			szName[MAX_NAME_LENGTH + 1];
		bool			bEnable;
		double			dblEquivalent;
	}MOTIONAXIS;
	// 气油缸
	typedef struct _CylinderInplace {
		uint8			ucType;
		uint32			uiReferId;
		uint16			usReferIndex;
		uint8			ucActionValue;
		uint32			uiDelayTime;
		uint32			uiAlarmTime;
	}CYLINDERINPLACE;
	typedef struct _CylinderOutput {
		uint32			uiReferId;
		uint16			usReferIndex;
		uint8			ucActionValue;
	}CYLINDEROUTPUT;
	typedef struct _Cylinder {
		uint32			uiCylinderId;
		char			szCylinderName[MAX_NAME_LENGTH + 1];
		bool			bEnable;
		char			szDirection1Name[MAX_NAME_LENGTH + 1];
		CYLINDERINPLACE	InplaceDirection1;
		CYLINDEROUTPUT	OutputDirection1;
		char			szDirection2Name[MAX_NAME_LENGTH + 1];
		CYLINDERINPLACE	InplaceDirection2;
		CYLINDEROUTPUT	OutputDirection2;
	}CYLINDER;
	// IO
	typedef struct _IOInfo {
		uint64			ullVariableId;
		uint32			uiDeviceId;
		uint16			usCard;
		uint16			usIndex;
		char			szName[MAX_NAME_LENGTH + 1];
		char			szLabel[MAX_NAME_LENGTH + 1];
		bool			bEnable;
		bool			bReverse;
	}IOINFO;

	//数据成员信息
	struct datamemberinfo
	{
		uint8 dt;//成员类别
		uint64 id;		//成员类型ID
		bool isarray;   //是否数组（vector）
		STR_SMALL name;	//成员名称		
		STR_BIG desc;	//成员描述
		// added by steven,20211111
		STR_BIG minValue;//最小值
		STR_BIG maxValue;//最大值
		// end of added,20211111
		// added by steven,20220107
		uint64 extend_type;	// 扩展类型
		// end of added,20220107
	};

	//方法信息
	struct methodinfo
	{
		STR_SMALL name;	//方法名称
		STR_MAX desc;//方法描述
		uint64 inparam_id; //输入参数ID
		STR_SMALL inparam_name;//输入参数描述
		uint64 outparam_id;//输出参数ID
		STR_SMALL outparam_name;//输出参数描述
	};

	// 数值范围
	struct ValueRange
	{
		uint8	dataType;	//数据类别
		bool	valid;		//是否有效
		STR_BIG minValue;	//最小值
		STR_BIG maxValue;	//最大值
	};

	//组件计数器接口，用于自动化的接口管理
	interface ICountor
	{
		virtual uint32 AddRef() = 0;
		virtual uint32 Release() = 0;
	};

	//自动结构信息
	interface IAutoDataInfo :public ICountor
	{
		//数据类型ID
		virtual uint64 TypeID() = 0;

		virtual const char* TypeName() = 0;

		//获取数据成员数量
		virtual uint32 GetMemberCount() = 0;

		//获取数据成员信息,可用于生成其它语言的结构代码
		virtual bool GetMemberInfo(uint32 index, datamemberinfo& outinfo) = 0;
		virtual bool GetMemberInfo(const std::string& name, datamemberinfo& outinfo) = 0;

		//获取数据成员id
		virtual uint64 GetMemberId(uint32 index) = 0;
		virtual uint64 GetMemberId(const std::string& name) = 0;
	};

	//自动数据对象接口
	interface IAutoData :IAutoDataInfo
	{
		//获取对象数据大小
		virtual uint32 GetSize() = 0;

		//获取对象数据
		virtual uint32 GetData(byte*& outdata, uint32 maxsize) = 0;

		//设置对象数据
		virtual uint32 SetData(const byte* pdata, uint32 dsize) = 0;

		//获取数据成员的索引
		virtual uint32 GetMemberIndex(const char* name) = 0;

		//added by steven,20211111
		//获取指定索引数据成员值范围
		virtual bool GetMemberValueRange(uint32 index, ValueRange* pValueRange) = 0;

		//指定数值是否超出数据成员值范围：true-越界/false-无越界
		template<typename _tyValue>
		bool IsValueOutsideMemberRange(uint32 index, _tyValue& value, ValueRange* pValueRange = nullptr) {
			ValueRange valueRange;
			if (!this->GetMemberValueRange(index, &valueRange)) {
				return false;
			}
			bool bOutside = false;
			switch (valueRange.dataType) {
			case DATA_TYPE_BOOL:			//布尔型
			{
				bool cur_val = static_cast<bool>(value);
				bool min_val = (0 == strcmp(valueRange.minValue, "true") ||
					0 == strcmp(valueRange.minValue, "True") ||
					0 == strcmp(valueRange.minValue, "TRUE") ||
					0 == strcmp(valueRange.minValue, "T") ||
					0 == strcmp(valueRange.minValue, "on") ||
					0 == strcmp(valueRange.minValue, "On") ||
					0 == strcmp(valueRange.minValue, "ON") ||
					0 != atoi(valueRange.minValue));
				bool max_val = (0 == strcmp(valueRange.maxValue, "true") ||
					0 == strcmp(valueRange.maxValue, "True") ||
					0 == strcmp(valueRange.maxValue, "TRUE") ||
					0 == strcmp(valueRange.maxValue, "T") ||
					0 == strcmp(valueRange.maxValue, "on") ||
					0 == strcmp(valueRange.maxValue, "On") ||
					0 == strcmp(valueRange.maxValue, "ON") ||
					0 != atoi(valueRange.maxValue));
				bOutside = (cur_val != min_val && cur_val != max_val);
			}
			break;
			case DATA_TYPE_INT8:			//有符号字符型（有符号8位整型）
			{
				int8 cur_val = static_cast<int8>(value);
				int8 min_val = (int8)atoi(valueRange.minValue);
				int8 max_val = (int8)atoi(valueRange.maxValue);
				bOutside = (cur_val < min_val || cur_val > max_val);
			}
			break;
			case DATA_TYPE_UINT8:		//无符号字符型（无符号8位整型）
			{
				uint8 cur_val = static_cast<uint8>(value);
				uint8 min_val = (uint8)atoi(valueRange.minValue);
				uint8 max_val = (uint8)atoi(valueRange.maxValue);
				bOutside = (cur_val < min_val || cur_val > max_val);
			}
			break;
			case DATA_TYPE_INT16:		//有符号短整型（有符号16位整型）
			{
				int16 cur_val = static_cast<int16>(value);
				int16 min_val = (int16)atoi(valueRange.minValue);
				int16 max_val = (int16)atoi(valueRange.maxValue);
				bOutside = (cur_val < min_val || cur_val > max_val);
			}
			break;
			case DATA_TYPE_UINT16:		//无符号短整型（无符号16位整型）
			{
				uint16 cur_val = static_cast<uint16>(value);
				uint16 min_val = (uint16)atoi(valueRange.minValue);
				uint16 max_val = (uint16)atoi(valueRange.maxValue);
				bOutside = (cur_val < min_val || cur_val > max_val);
			}
			break;
			case DATA_TYPE_INT32:		//有符号整型（有符号32位整型）
			{
				char* pEnd = nullptr;
				int32 cur_val = static_cast<int32>(value);
				int32 min_val = (int32)strtol(valueRange.minValue, &pEnd, 10);
				int32 max_val = (int32)strtol(valueRange.maxValue, &pEnd, 10);
				bOutside = (cur_val < min_val || cur_val > max_val);
			}
			break;
			case DATA_TYPE_UINT32:		//无符号整型（无符号32位整型）
			{
				char* pEnd = nullptr;
				uint32 cur_val = static_cast<uint32>(value);
				uint32 min_val = (uint32)strtoul(valueRange.minValue, &pEnd, 10);
				uint32 max_val = (uint32)strtoul(valueRange.maxValue, &pEnd, 10);
				bOutside = (cur_val < min_val || cur_val > max_val);
			}
			break;
			case DATA_TYPE_INT64:		//有符号长整型（有符号64位长整型）
			{
				char* pEnd = nullptr;
				int64 cur_val = static_cast<int64>(value);
				int64 min_val = (int64)strtoll(valueRange.minValue, &pEnd, 10);
				int64 max_val = (int64)strtoll(valueRange.maxValue, &pEnd, 10);
				bOutside = (cur_val < min_val || cur_val > max_val);
			}
			break;
			case DATA_TYPE_UINT64:		//无符号长整型（无符号64位长整型）
			{
				char* pEnd = nullptr;
				uint64 cur_val = static_cast<uint64>(value);
				uint64 min_val = (uint64)strtoull(valueRange.minValue, &pEnd, 10);
				uint64 max_val = (uint64)strtoull(valueRange.maxValue, &pEnd, 10);
				bOutside = (cur_val < min_val || cur_val > max_val);
			}
			break;
			case DATA_TYPE_FLOAT:		//单精度浮点型（32位）
			{
				char* pEnd = nullptr;
				float cur_val = static_cast<float>(value);
				float min_val = (float)strtof(valueRange.minValue, &pEnd);
				float max_val = (float)strtof(valueRange.maxValue, &pEnd);
				bOutside = (cur_val < min_val || cur_val > max_val);
			}
			break;
			case DATA_TYPE_DOUBLE:		//双精度浮点型（64位）
			{
				char* pEnd = nullptr;
				double cur_val = static_cast<double>(value);
				double min_val = (double)strtod(valueRange.minValue, &pEnd);
				double max_val = (double)strtod(valueRange.maxValue, &pEnd);
				bOutside = (cur_val < min_val || cur_val > max_val);
			}
			break;
			}
			if (nullptr != pValueRange) {
				memcpy(pValueRange, &valueRange, sizeof(ValueRange));
			}

			return bOutside;
		}
		//end of added,20211111

		//获取VEC容器大小
		virtual bool GetArraySize(uint32 index, uint32& outSize) = 0;
		//设置VEC容器大小
		virtual bool SetArraySize(uint32 index, uint32 newSize) = 0;

		//获取成员对象
		template<typename _tyCast>
		bool GetMember(size_t index, _tyCast& outVal)
		{
			return GetMember(index, &outVal, typeid(_tyCast).hash_code());
		}

		//获取VEC成员中的对象
		template<typename _tyCast>
		bool GetMemberItem(size_t index, uint32 itemindex, _tyCast& outVal)
		{
			return GetMemberItem(index, itemindex, &outVal, typeid(_tyCast).hash_code());
		}

		//设置成员对象
		template<typename _tyCast>
		bool SetMember(size_t index, _tyCast& newVal)
		{
			return SetMember(index, &newVal, typeid(_tyCast).hash_code());
		}

		//设置VEC成员中的对象
		template<typename _tyCast>
		bool SetMemberItem(size_t index, uint32 itemindex, _tyCast& newVal)
		{
			return SetMemberItem(index, itemindex, &newVal, typeid(_tyCast).hash_code());
		}
	protected:
		virtual bool GetMember(size_t index, void* outVal, size_t typecode) = 0;
		virtual bool GetMemberItem(size_t index, uint32 itemindex, void* outVal, size_t typecode) = 0;
		virtual bool SetMember(size_t index, void* inVal, size_t typecode) = 0;
		virtual bool SetMemberItem(size_t index, uint32 itemindex, void* inVal, size_t typecode) = 0;

	};

	//自动结构创建器
	interface IAutoDataCreator
	{
		//获取工厂支持的自动结构数量
		virtual uint32 GetAutoDataCount() = 0;

		//用索引获取自动结构信息
		virtual bool GetAutoDataInfo(uint32 uiIndex, IAutoDataInfo*& pOutInfo) = 0;

		//用ID获取自动结构信息
		virtual bool GetAutoDataInfo(IAutoDataInfo*& pOutInfo, uint64 ullId) = 0;

		//创建自动数据接口
		virtual bool CreateData(uint64 ullId, IAutoData** ppOutData, IAutoData* pFromData = nullptr) = 0;
	};

	//事件接口
	interface IEvent
	{
		//消息
		virtual void OnMessage(uint64 ullEventData, uint8 ucLevel, const char* lpszModule, const char* lpszMessage) = 0;

		//状态
		virtual void OnStatus(uint64 ullEventData, uint8 ucStatusType, uint64 ullStatusId, uint64 ullStatusData) = 0;

		//结果
		virtual void OnResult(uint64 ullEventData, uint64 ullUserData, IAutoData* pResultData) = 0;
	};

	//数据接口
	interface IDataManager
	{
		// 初始化
		virtual bool Initialize() = 0;

		//更新变量值
		virtual bool SetVariableValue(uint64 ullVariableId, const std::string& strValue, bool bRefresh = true) = 0;
		virtual bool SetVariableValue(uint64 ullVariableId, const bool& bValue, bool bRefresh = true) = 0;
		virtual bool SetVariableValue(uint64 ullVariableId, const int8& cValue, bool bRefresh = true) = 0;
		virtual bool SetVariableValue(uint64 ullVariableId, const uint8& ucValue, bool bRefresh = true) = 0;
		virtual bool SetVariableValue(uint64 ullVariableId, const int16& sValue, bool bRefresh = true) = 0;
		virtual bool SetVariableValue(uint64 ullVariableId, const uint16& usValue, bool bRefresh = true) = 0;
		virtual bool SetVariableValue(uint64 ullVariableId, const int32& iValue, bool bRefresh = true) = 0;
		virtual bool SetVariableValue(uint64 ullVariableId, const uint32& uiValue, bool bRefresh = true) = 0;
		virtual bool SetVariableValue(uint64 ullVariableId, const int64& llValue, bool bRefresh = true) = 0;
		virtual bool SetVariableValue(uint64 ullVariableId, const uint64& ullValue, bool bRefresh = true) = 0;
		virtual bool SetVariableValue(uint64 ullVariableId, const float& fValue, bool bRefresh = true) = 0;
		virtual bool SetVariableValue(uint64 ullVariableId, const double& dblValue, bool bRefresh = true) = 0;
		virtual bool SetVariableValue(uint64 ullVariableId, const uint8& ucType, const VRVALUE* pValue, bool bRefresh = true) = 0;
		virtual bool SetVariableValue(uint64 ullVariableId, const COORDS* pCoords, bool bRefresh = true) = 0;

		//获取变量值
		virtual bool GetVariableValue(uint64 ullVariableId, std::string& strValue, bool bRefresh = true) = 0;
		virtual bool GetVariableValue(uint64 ullVariableId, bool& bValue, bool bRefresh = true) = 0;
		virtual bool GetVariableValue(uint64 ullVariableId, int8& cValue, bool bRefresh = true) = 0;
		virtual bool GetVariableValue(uint64 ullVariableId, uint8& ucValue, bool bRefresh = true) = 0;
		virtual bool GetVariableValue(uint64 ullVariableId, int16& sValue, bool bRefresh = true) = 0;
		virtual bool GetVariableValue(uint64 ullVariableId, uint16& usValue, bool bRefresh = true) = 0;
		virtual bool GetVariableValue(uint64 ullVariableId, int32& iValue, bool bRefresh = true) = 0;
		virtual bool GetVariableValue(uint64 ullVariableId, uint32& uiValue, bool bRefresh = true) = 0;
		virtual bool GetVariableValue(uint64 ullVariableId, int64& llValue, bool bRefresh = true) = 0;
		virtual bool GetVariableValue(uint64 ullVariableId, uint64& ullValue, bool bRefresh = true) = 0;
		virtual bool GetVariableValue(uint64 ullVariableId, float& fValue, bool bRefresh = true) = 0;
		virtual bool GetVariableValue(uint64 ullVariableId, double& dblValue, bool bRefresh = true) = 0;
		virtual bool GetVariableValue(uint64 ullVariableId, uint8& ucType, VRVALUE* pValue, bool bRefresh = true) = 0;
		virtual bool GetVariableValue(uint64 ullVariableId, COORDS* pCoords, bool bRefresh = true) = 0;

		// 更新变量类型
		virtual bool SetVariableType(uint64 ullVariableId, uint8 ucType) = 0;

		// 获取变量类型
		virtual uint8 GetVariableType(uint64 ullVariableId) = 0;

		// 更新数值类型
		virtual bool SetValueType(uint64 ullVariableId, uint8 ucType) = 0;

		// 获取数值类型
		virtual uint8 GetValueType(uint64 ullVariableId) = 0;

		// 获取变量数组序号
		virtual uint32 GetVariableIndex(uint64 ullVariableId) = 0;

		// 获取格式化字符串变量值
		virtual bool GetVariableStringValue(uint64 ullVariableId, std::string& strValue, bool bRefresh = true) = 0;

		// 更新变量时间戳
		virtual bool SetVariableTimestamp(uint64 ullVariableId, uint64 ullTimestamp) = 0;

		// 获取变量时间戳
		virtual uint64 GetVariableTimestamp(uint64 ullVariableId) = 0;

		// 更新变量名称
		virtual bool SetVariableName(uint64 ullVariableId, std::string& strName) = 0;

		// 获取变量名称
		virtual const char* GetVariableName(uint64 ullVariableId) = 0;

		// 获取运动轴最后一次运动模式
		virtual uint32 GetMotionAxisLastProfileMode(uint32 uiDeviceId, uint16 usAxis) = 0;

		// 更新运动轴最后一次运动模式
		virtual bool SetMotionAxisLastProfileMode(uint32 uiDeviceId, uint16 usAxis, uint32 uiProfileMode) = 0;

		// 获取运动轴最后一次目标位置
		virtual double GetMotionAxisLastPosition(uint32 uiDeviceId, uint16 usAxis) = 0;

		// 更新运动轴最后一次目标位置
		virtual bool SetMotionAxisLastPosition(uint32 uiDeviceId, uint16 usAxis, double dblPosition) = 0;
	};

	//交互接口
	interface IInteractAction
	{
		// 推送消息
		virtual uint32 PushInteractMessage(INTERACTMESSAGE* pInteractMessage) = 0;

		// 获取交互结果
		virtual int32 GetInteractResult(INTERACTRESULT* pInteractResult) = 0;
	};

	//接口信息
	interface IInterfaceInfo :public ICountor
	{
		//接口对象类型ID
		virtual uint64 TypeID() = 0;

		//接口对象类型名称
		virtual const char* TypeName() = 0;

		//类型名，可有多级分类，使用“:”为类级分隔符
		virtual const char* TypeClass() = 0;

		//获取图标
		virtual const byte* Icon(uint32& icoSize) = 0;

		//接口对象版本
		virtual uint32 GetVer() = 0;

		//接口对象描述
		virtual const char* Desc() = 0;

		//是否线程安全
		virtual bool IsThreadSafe() = 0;

		//是否支持某接口 
		virtual bool IsSupportInterface(uint64 interfaceid) = 0;

		//获取属性绑定结构信息
		virtual uint64 GetPropertyID() = 0;

		//获取方法数量
		virtual uint32 GetMethodCount() = 0;

		//获取方法信息
		virtual bool GetMethodInfo(uint32 index, methodinfo& outinfo) = 0;

	};

	//接口
	interface IInterface :public IInterfaceInfo
	{
		//获取预定义设备类型
		virtual bool GetPreDeviceTypes(PREDEVICETYPES* pPreDeviceTypes) = 0;

		//获取接口名称
		virtual const char* GetName() = 0;

		//获取错误代码
		virtual int32 GetLastErrorCode() = 0;

		//获取错误描述
		virtual const char* GetLastErrorMsg() = 0;

		//接口状态
		virtual uint8 GetStatus() = 0;

		//获取接口
		virtual bool GetInterface(uint64 interfaceid, IInterface*& outInterface) = 0;

		//获取属性值
		template<typename _tyCast>
		bool GetProperty(size_t index, _tyCast& outVal)
		{
			return GetProperty(index, &outVal, typeid(_tyCast).hash_code());
		}

		//获取VEC成员中的值
		template<typename _tyCast>
		bool GetPropertyItem(size_t index, uint32 itemindex, _tyCast& outVal)
		{
			return GetPropertyItem(index, itemindex, &outVal, typeid(_tyCast).hash_code());
		}

		//设置属性值
		template<typename _tyCast>
		bool SetProperty(size_t index, _tyCast& newVal)
		{
			return SetProperty(index, &newVal, typeid(_tyCast).hash_code());
		}

		//设置VEC成员中的值
		template<typename _tyCast>
		bool SetPropertyItem(size_t index, uint32 itemindex, _tyCast& newVal)
		{
			return SetPropertyItem(index, itemindex, &newVal, typeid(_tyCast).hash_code());
		}

		//获取属性VEC容器大小
		virtual bool GetPropertySize(uint32 index, uint32& outSize) = 0;
		//设置属性VEC容器大小
		virtual bool SetPropertySize(uint32 index, uint32 newSize) = 0;

		//初始化组件对象
		virtual bool Init(IDataManager* pDataManager, IEvent* pEventHandler, uint64 ullEventData, IAutoData* pExtendData, uint64 ullTimeout, IInteractAction* pInteractAction, void* lpRefer) = 0;

		//指派操作函数
		virtual bool Invoke(const char* lpszMethodName, IAutoData* pInputData, uint64 ullUserData, IAutoData* pOutputData = nullptr) = 0;

		//反初始化组件对象
		virtual void Uninit() = 0;

	private:
		virtual bool GetProperty(size_t index, void* outVal, size_t typecode) = 0;
		virtual bool GetPropertyItem(size_t index, uint32 itemindex, void* outVal, size_t typecode) = 0;
		virtual bool SetProperty(size_t index, void* inVal, size_t typecode) = 0;
		virtual bool SetPropertyItem(size_t index, uint32 itemindex, void* inVal, size_t typecode) = 0;

	};

	interface IFactory :IAutoDataCreator
	{
		//获取对象工厂相关信息
		virtual uint32 GetVersion() = 0;
		virtual const char* GetName() = 0;
		virtual const char* GetDesc() = 0;


		//获取工厂支持的接口数量
		virtual uint32 GetInterfaceCount() = 0;

		//用索引获取接口信息
		virtual bool GetInterfaceInfo(uint32 index, IInterfaceInfo*& info) = 0;

		//用ID获取接口信息
		virtual bool GetInterfaceInfo(IInterfaceInfo*& info, uint64 id) = 0;

		//创建一个接口
		virtual bool CreateInterface(IAutoData* propertys, IEvent* pHandler, uint64 handledata, uint64 id, IInterface*& outObj, const char* nameit = nullptr) = 0;

	};

	typedef IFactory* (*funcGetFactory)(uint32);
}

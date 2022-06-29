#pragma once

#pragma warning(disable:4005)

#if !defined(Char)
typedef char				Char;
#endif

#if !defined(Boolean)
typedef unsigned int		Boolean;
#endif

#if !defined(Byte)
typedef unsigned char		Byte;
#endif

#if !defined(SByte)
typedef signed char			SByte;
#endif

#if !defined(Int16)
typedef signed short		Int16;
#endif

#if !defined(UInt16)
typedef unsigned short		UInt16;
#endif

#if !defined(Int32)
typedef signed int			Int32;
#endif

#if !defined(UInt32)
typedef unsigned int		UInt32;
#endif

#if !defined(UInt64)
#if defined(WIN32) && !defined(__MINGW32__)
typedef unsigned __int64	UInt64;
#else
typedef unsigned long long	UInt64;
#endif
#endif

#if !defined(Int64)
#if defined(WIN32) && ! defined(__MINGW32__)
typedef __int64				Int64;
#else
typedef signed long long 	Int64;
#endif
#endif

#if !defined(Single)
typedef float				Single;
#endif

#if !defined(Double)
typedef double				Double;
#endif

#if !defined(IntPtr)
typedef signed int* IntPtr;
#endif

#if !defined(UIntPtr)
typedef unsigned int* UIntPtr;
#endif

#ifdef _WIN32
#define YD_MOTION_API extern "C" __declspec(dllexport) Int32 __stdcall
#else
#define YD_MOTION_API extern "C" Int32
#endif

// 接口错误代码定义
constexpr Int32 YD_API_ERROR_SUCCESS = 0;				// 成功
constexpr Int32 YD_API_ERROR_FAILED = -1;				// 失败
constexpr Int32 YD_API_ERROR_NOT_INITIALIZED = -2;		// 未初始化
constexpr Int32 YD_API_ERROR_NOT_FOUND = -3;			// 不存在
constexpr Int32 YD_API_ERROR_INVALID_INPUT = -4;		// 输入参数无效
constexpr Int32 YD_API_ERROR_DISMATCHED = -5;			// 类型不匹配
constexpr Int32 YD_API_ERROR_UNAUTHORIZED = -6;			// 未授权
constexpr Int32 YD_API_ERROR_OPERATION_FORBIDDEN = -7;	// 操作被禁止
constexpr Int32 YD_API_ERROR_TIMEOUT = -8;				// 超时
constexpr Int32 YD_API_ERROR_OUTSIDE_RANGE = -9;		// 越界
constexpr Int32 YD_API_ERROR_MEMORY_OVERFLOW = -100;	// 内存溢出

// 数值类型定义
constexpr Byte YD_API_VALUE_TYPE_BOOL = 2;				// 布尔型
constexpr Byte YD_API_VALUE_TYPE_INT8 = 3;				// 有符号8位整型
constexpr Byte YD_API_VALUE_TYPE_UINT8 = 4;				// 无符号8位整型
constexpr Byte YD_API_VALUE_TYPE_INT16 = 5;				// 有符号16位整型
constexpr Byte YD_API_VALUE_TYPE_UINT16 = 6;			// 无符号16位整型
constexpr Byte YD_API_VALUE_TYPE_INT32 = 7;				// 有符号32位整型
constexpr Byte YD_API_VALUE_TYPE_UINT32 = 8;			// 无符号32位整型
constexpr Byte YD_API_VALUE_TYPE_INT64 = 9;				// 有符号64位整型
constexpr Byte YD_API_VALUE_TYPE_UINT64 = 10;			// 无符号64位整型
constexpr Byte YD_API_VALUE_TYPE_FLOAT = 11;			// 单精度浮点型
constexpr Byte YD_API_VALUE_TYPE_DOUBLE = 12;			// 双精度浮点型
constexpr Byte YD_API_VALUE_TYPE_STRING = 13;			// 字符串
constexpr Byte YD_API_VALUE_TYPE_MOTION_COORDS = 17;	// 运动坐标

// 运动类型定义
constexpr Byte YD_API_MOVE_TYPE_ABSOLUTE = 11;			// 绝对运动
constexpr Byte YD_API_MOVE_TYPE_RELATIVE = 12;			// 相对运动
constexpr Byte YD_API_MOVE_TYPE_JOG = 13;				// Jog运动

// 变量类型定义
constexpr Byte YD_API_VARIABLE_TYPE_DI = 1;				// DI变量，只读
constexpr Byte YD_API_VARIABLE_TYPE_DO = 2;				// DO变量，读/写
constexpr Byte YD_API_VARIABLE_TYPE_AI = 3;				// AI变量，只读
constexpr Byte YD_API_VARIABLE_TYPE_AO = 4;				// AO变量，读/写
constexpr Byte YD_API_VARIABLE_TYPE_SYSTEM = 5;			// 系统变量，只读
constexpr Byte YD_API_VARIABLE_TYPE_MOTION = 6;			// 运动变量，只读
constexpr Byte YD_API_VARIABLE_TYPE_CYLINDER = 7;		// 气油缸变量，只读
constexpr Byte YD_API_VARIABLE_TYPE_CONFIG = 8;			// 配置变量，读/写
constexpr Byte YD_API_VARIABLE_TYPE_VIRTUAL = 9;		// 虚拟变量，读/写
constexpr Byte YD_API_VARIABLE_TYPE_CONTROL = 10;		// 控制变量，读/写
constexpr Byte YD_API_VARIABLE_TYPE_LOGIC = 11;			// 逻辑变量，读/写
constexpr Byte YD_API_VARIABLE_TYPE_SAFE = 12;			// 安全变量，只读

// 运动方向定义
constexpr Byte YD_API_MOVE_DIRECTION_POSITIVE = 1;		// 正方向运动
constexpr Byte YD_API_MOVE_DIRECTION_NEGATIVE = 2;		// 负方向运动

// DI类型定义
constexpr Byte YD_API_DITYPE_GENERAL = 0;				// 通用输入
constexpr Byte YD_API_DITYPE_POSITIVE_LIMIT = 1;		// 正限位
constexpr Byte YD_API_DITYPE_NEGATIVE_LIMIT = 2;		// 负限位
constexpr Byte YD_API_DITYPE_DRIVER_ALARM = 3;			// 驱动报警
constexpr Byte YD_API_DITYPE_HOME_SIGNAL = 4;			// 原点信号
constexpr Byte YD_API_DITYPE_MOTOR_ARRIVE = 5;			// 电机到位

// DO类型定义
constexpr Byte YD_API_DOTYPE_GENERAL = 0;				// 通用输出
constexpr Byte YD_API_DOTYPE_DRIVER_ENABLE = 1;			// 驱动使能
constexpr Byte YD_API_DOTYPE_ALARM_CLEAR = 2;			// 报警清除

// 控制器模式
constexpr Byte YD_API_CONTROLLER_MODE_MANUAL = 0;		// 手动模式
constexpr Byte YD_API_CONTROLLER_MODE_AUTOMATIC = 1;	// 自动模式

// 轴回零状态
constexpr Byte YD_API_AXIS_HOME_MOVE_NOT_EXECUTED = 0;	// 未回零
constexpr Byte YD_API_AXIS_HOME_MOVE_IN_PROCESSING = 1;	// 回零中
constexpr Byte YD_API_AXIS_HOME_MOVE_EXECUTED = 2;		// 已回零

// 控制器状态
constexpr Byte YD_API_CONTROLLER_STATUS_STOPED = 0;		// 已停止
constexpr Byte YD_API_CONTROLLER_STATUS_RUNNING = 1;	// 运行中
constexpr Byte YD_API_CONTROLLER_STATUS_SUSPENDED = 2;	// 已暂停
constexpr Byte YD_API_CONTROLLER_STATUS_RESTORED = 3;	// 已恢复

// 气油缸运动方向
constexpr Byte YD_API_CYLINDER_MOVE_DIRECTION1 = 1;		// 方向一运动
constexpr Byte YD_API_CYLINDER_MOVE_DIRECTION2 = 2;		// 方向二运动

// 气油缸到位类型
constexpr Byte YD_API_CYLINDER_DELAYED_ARRIVE = 1;		// 延时等待
constexpr Byte YD_API_CYLINDER_DION_ARRIVE = 2;			// DI有效到位
constexpr Byte YD_API_CYLINDER_DION_DELAYED_ARRIVE = 3;	// DI有效+延时等待到位
constexpr Byte YD_API_CYLINDER_AXIS_ENCODER_ARRIVE = 4;	// 编码器到位

// 运动轴回原点模式
constexpr Byte YD_API_HOMEMODE_NONE = 0;											// 不用回原点
constexpr Byte YD_API_HOMEMODE_CHECKSIGNAL_BY_POSITIVEMOVE_IF_NEGATIVELIMIT_ON = 1; // 轴先运动到负限位，然后向正方向查找原点信号，当检测到原点信号时立即停止，当前位置为原点
constexpr Byte YD_API_HOMEMODE_CHECKSIGNAL_BY_NEGATIVEMOVE_IF_POSITIVELIMIT_ON = 2; // 轴先运动到正限位，然后向负方向查找原点信号，当检测到原点信号时立即停止，当前位置为原点
constexpr Byte YD_API_HOMEMODE_CHECKSIGNAL_BY_ANTICLOCKWISEMOVE = 3;				// 旋转轴向负方向（逆时针）查找原点信号，当检测到原点信号时 立即停止，当前位置为原点
constexpr Byte YD_API_HOMEMODE_CHECKSIGNAL_BY_CLOCKWISEMOVE = 4;					// 旋转轴向正方向（顺时针）查找原点信号，当检测到原点信号时 立即停止，当前位置为原点
constexpr Byte YD_API_HOMEMODE_IF_POSITIVELIMIT_ON = 5;								// 将该轴的负限位作为原点信号
constexpr Byte YD_API_HOMEMODE_IF_NEGATIVELIMIT_ON = 6;								// 将该轴的正限位作为原点信号

// 电平捕捉类型
constexpr Byte YD_API_ELECTRIC_CAPTURE_RISING_EDGE = 1; 							// 上升沿触发
constexpr Byte YD_API_ELECTRIC_CAPTURE_FALLING_EDGE = 2; 							// 下降沿触发

// 限位类型
constexpr Byte YD_API_LIMIT_TYPE_POSITIVE = 1; 										// 正限位
constexpr Byte YD_API_LIMIT_TYPE_NEGATIVE = 2; 										// 负限位

// 回原点查找方向
constexpr Byte YD_API_HOMECHECK_DIRECTION_POSITIVE = 1; 										// 正向
constexpr Byte YD_API_HOMECHECK_DIRECTION_NEGATIVE = 2; 										// 负向
constexpr Byte YD_API_HOMECHECK_DIRECTION_CLOCKWISE = YD_API_HOMECHECK_DIRECTION_POSITIVE; 		// 顺时针
constexpr Byte YD_API_HOMECHECK_DIRECTION_ANTICLOCKWISE = YD_API_HOMECHECK_DIRECTION_NEGATIVE; 	// 逆时针

// 跨语言函数结果
constexpr Int32 YD_API_CROSS_RESULT_SUCCESS = 0;		// 成功
constexpr Int32 YD_API_CROSS_RESULT_FAILED = -1;		// 失败
constexpr Int32 YD_API_CROSS_RESULT_RETRY = 1;			// 重试

// 最大数量定义
constexpr Byte YD_MAX_MOTION_COORD_NUMBER = 32;			// 运动坐标最大轴数
constexpr Byte YD_MAX_NAME_LENGTH = 64;					// 名称最大长度
constexpr Byte YD_MAX_VALUE_LENGTH = 64;				// 数值最大长度

// 日志级别
constexpr Byte YD_API_LOG_LEVEL_TRACE = 1;				// 跟踪
constexpr Byte YD_API_LOG_LEVEL_DEBUG = 2;				// 调试
constexpr Byte YD_API_LOG_LEVEL_INFO = 3;				// 信息
constexpr Byte YD_API_LOG_LEVEL_WARN = 4;				// 警告
constexpr Byte YD_API_LOG_LEVEL_ERROR = 5;				// 错误
constexpr Byte YD_API_LOG_LEVEL_CRITICAL = 6;			// 致命

// 项目信息
#pragma pack(push, 8)
typedef struct _YD_Project {
	UInt32			version;							// 版本号
	Char			name[YD_MAX_NAME_LENGTH + 1];		// 项目名称
	Char			recipe[YD_MAX_NAME_LENGTH + 1];		// 配方名称
}YD_Project;
#pragma pack(pop)

// 运动坐标
#pragma pack(push, 8)
typedef struct _YD_MotionCoords {
	UInt16			cards[YD_MAX_MOTION_COORD_NUMBER];	// 卡编号数组 [0, N]
	UInt16			axises[YD_MAX_MOTION_COORD_NUMBER];	// 轴序号数组 [1, M]
	Byte			types[YD_MAX_MOTION_COORD_NUMBER];	// 运动类型数组
	Byte			directions[YD_MAX_MOTION_COORD_NUMBER];// 运动方向数组
	Double			targets[YD_MAX_MOTION_COORD_NUMBER];	// 运动目标数组
	Double			velocities[YD_MAX_MOTION_COORD_NUMBER];// 运动速度数组
	Byte			number;								// 运动坐标个数
}YD_MotionCoords;
#pragma pack(pop)

// 变量信息
#pragma pack(push, 8)
typedef struct _YD_VariableInfo {
	UInt64			variable_id;						// 变量id
	Char			variable_name[YD_MAX_NAME_LENGTH];	// 变量名称
	Byte			variable_type;						// 变量类型
	Byte			value_type;							// 数值类型
	Double			max_value;							// 最大值：布尔型和数值类型有效
	Double			min_value;							// 最小值：布尔型和数值类型有效
}YD_VariableInfo;
#pragma pack(pop)

// IO信息
#pragma pack(push, 8)
typedef struct _YD_IOInfo {
	UInt16			card;								// 卡编号 [0, N]
	UInt16			type;								// 类型
	UInt16			index;								// 序号
	Char			name[YD_MAX_NAME_LENGTH];			// 名称
	Char			label[YD_MAX_NAME_LENGTH];			// 标识
	Byte			enable;								// 是否使能
	Byte			reverse;							// 是否反转
}YD_IOInfo;
#pragma pack(pop)

// 运动轴信息
#pragma pack(push, 8)
typedef struct _YD_AxisInfo {
	UInt16			card;								// 卡编号 [0, N]
	UInt16			axis;								// 轴序号 [1, M]
	Char			name[YD_MAX_NAME_LENGTH];			// 轴名称
	Byte			enable;								// 是否使能
	Double			equivalent;							// 脉冲当量
}YD_AxisInfo;
#pragma pack(pop)

// 运动轴回原点参数
#pragma pack(push, 8)
typedef struct _YD_AxisHomeConfig {
	Byte			priority;							// 回原点优先级
	Byte			mode;								// 回原点模式
	Double			search_distance;					// 搜索距离
	Double			move_velocity;						// 移动速度
	Double			search_high_velocity;				// 搜索速度（高速）
	Double			search_low_velocity;				// 搜索速度（低速）
	Double			origin_offset;						// 原点偏移量
	Boolean			capture_electric_level;				// 原点捕获电平选中
}YD_AxisHomeConfig;
#pragma pack(pop)

// 运动轴状态
#pragma pack(push, 8)
typedef struct _YD_AxisStates {
	Byte			driver_alarm;						// 驱动报警标志
	Byte			follow_error;						// 跟随误差标志
	Byte			positive_limit;						// 正向限位标志
	Byte			negative_limit;						// 负向限位标志
	Byte			smooth_stop;						// 平滑停止标志
	Byte			urgent_stop;						// 紧急停止标志
	Byte			servo_on;							// 伺服使能标志
	Byte			profile_move;						// 运动状态标志
	Byte			motor_arrive;						// 电机到位标志
	Byte			home_signal;						// 原点信号标志
	Byte			home_moved;							// 回零状态标志
	UInt32			profile_mode;						// 运动模式
	Double			target_position;					// 目标位置
	Double			target_velocity;					// 目标速度
	Double			profile_position;					// 规划位置
	Double			profile_velocity;					// 规划速度
	Double			encoder_position;					// 编码器位置（反馈位置）
	Double			encoder_velocity;					// 编码器速度（反馈速度）
}YD_AxisStates;
#pragma pack(pop)

// 气油缸信息
#pragma pack(push, 8)
typedef struct _YD_CylinderInplace {
	Byte				inplace_type;						// 到位类型
	UInt32				refer_di_device;					// 关联di所属设备id
	UInt16				refer_di_type;						// 关联di类型
	UInt16				refer_di_index;						// 关联di序号
	UInt32				delay_time;							// 延迟时间：毫秒
	UInt32				alarm_time;							// 报警时间：毫秒
}YD_CylinderInplace;
typedef struct _YD_CylinderCoil {
	UInt32				refer_do_device;					// 关联do所属设备id
	UInt16				refer_do_type;						// 关联do类型
	UInt16				refer_do_index;						// 关联do序号
	Byte				refer_do_value;						// 关联do动作值
}YD_CylinderCoil;
typedef struct _YD_CylinderInfo {
	UInt32				id;									// 气油缸id
	Char				name[YD_MAX_NAME_LENGTH];			// 气油缸名称
	Byte				enable;								// 是否使能
	Char				direction1_name[YD_MAX_NAME_LENGTH];// 方向一名称
	YD_CylinderInplace	direction1_inplace;					// 方向一到位参数
	YD_CylinderCoil		direction1_coil;					// 方向一电磁阀
	Char				direction2_name[YD_MAX_NAME_LENGTH];// 方向二名称
	YD_CylinderInplace	direction2_inplace;					// 方向二到位参数
	YD_CylinderCoil		direction2_coil;					// 方向二电磁阀
}YD_CylinderInfo;
#pragma pack(pop)

// 气油缸状态
#pragma pack(push, 8)
typedef struct _YD_DirectionState {
	Byte				refer_di_state;						// 关联DI状态
	Byte				inplace_state;						// 到位状态
	Byte				alarm_state;						// 报警状态
}YD_DirectionState;
typedef struct _YD_CylinderStates {
	YD_DirectionState	direction1_state;					// 方向一状态
	YD_DirectionState	direction2_state;					// 方向二状态
}YD_CylinderStates;
#pragma pack(pop)

/// <summary>
/// 获取项目信息
/// </summary>
/// <param name="project"></param>
/// <returns></returns>
YD_MOTION_API yd_get_project_info(YD_Project* project);

/// <summary>
/// 获取模块名称
/// </summary>
/// <param name="buffer"></param>
/// <param name="size"></param>
/// <returns></returns>
YD_MOTION_API yd_get_module_name(Char* buffer, Int32 size);

/// <summary>
/// 输出日志
/// </summary>
/// <param name="level"></param>
/// <param name="log"></param>
/// <returns></returns>
YD_MOTION_API yd_output_log(Byte level, const Char* log);

/// <summary>
/// 获取错误信息
/// </summary>
/// <param name="buffer"></param>
/// <param name="size"></param>
/// <returns></returns>
YD_MOTION_API yd_get_error_msg(Char* buffer, Int32 size);

/// <summary>
/// 获取逻辑控制器状态
/// </summary>
/// <param name="status"></param>
/// <returns></returns>
YD_MOTION_API yd_get_controller_status(Byte* status);

/// <summary>
/// 获取逻辑控制器模式
/// </summary>
/// <param name="mode"></param>
/// <returns></returns>
YD_MOTION_API yd_get_controller_mode(Byte* mode);

/// <summary>
/// 启动逻辑控制器
/// </summary>
/// <param name="timeout"></param>
/// <returns></returns>
YD_MOTION_API yd_start_controller(UInt32 timeout = 3000);

/// <summary>
/// 停止逻辑控制器
/// </summary>
/// <param name="timeout"></param>
/// <returns></returns>
YD_MOTION_API yd_stop_controller(UInt32 timeout = 3000);

/// <summary>
/// 暂停逻辑控制器
/// </summary>
/// <param name="timeout"></param>
/// <returns></returns>
YD_MOTION_API yd_pause_controller(UInt32 timeout = 3000);

/// <summary>
/// 恢复逻辑控制器
/// </summary>
/// <param name="timeout"></param>
/// <returns></returns>
YD_MOTION_API yd_restore_controller(UInt32 timeout = 3000);

/// <summary>
/// 切换逻辑控制器手动模式
/// </summary>
/// <param name="timeout"></param>
/// <returns></returns>
YD_MOTION_API yd_switch_controller_to_manual_mode(UInt32 timeout = 3000);

/// <summary>
/// 切换逻辑控制器自动模式
/// </summary>
/// <param name="timeout"></param>
/// <returns></returns>
YD_MOTION_API yd_switch_controller_to_automatic_mode(UInt32 timeout = 3000);

/// <summary>
/// 获取指定ID的变量
/// </summary>
/// <param name="id"></param>
/// <param name="pVariableInfo"></param>
/// <returns></returns>
YD_MOTION_API yd_get_variable_by_id(UInt64 id, YD_VariableInfo* pVariableInfo);

/// <summary>
/// 获取指定名称的变量
/// </summary>
/// <param name="name"></param>
/// <param name="pVariableInfo"></param>
/// <returns></returns>
YD_MOTION_API yd_get_variable_by_name(const Char* name, YD_VariableInfo* pVariableInfo);

/// <summary>
/// 获取指定变量布尔数值
/// </summary>
/// <param name="id"></param>
/// <param name="value"></param>
/// <param name="timestamp"></param>
/// <returns></returns>
YD_MOTION_API yd_get_variable_boolean(UInt64 id, Boolean* value, UInt64* timestamp = nullptr);

/// <summary>
/// 设置指定变量布尔数值
/// </summary>
/// <param name="id"></param>
/// <param name="value"></param>
/// <returns></returns>
YD_MOTION_API yd_set_variable_boolean(UInt64 id, Boolean value);

/// <summary>
/// 获取指定变量有符号8位整型数值
/// </summary>
/// <param name="id"></param>
/// <param name="value"></param>
/// <param name="timestamp"></param>
/// <returns></returns>
YD_MOTION_API yd_get_variable_int8(UInt64 id, SByte* value, UInt64* timestamp = nullptr);

/// <summary>
/// 设置指定变量有符号8位整型数值
/// </summary>
/// <param name="id"></param>
/// <param name="value"></param>
/// <returns></returns>
YD_MOTION_API yd_set_variable_int8(UInt64 id, SByte value);

/// <summary>
/// 获取指定变量无符号8位整型数值
/// </summary>
/// <param name="id"></param>
/// <param name="value"></param>
/// <param name="timestamp"></param>
/// <returns></returns>
YD_MOTION_API yd_get_variable_uint8(UInt64 id, Byte* value, UInt64* timestamp = nullptr);

/// <summary>
/// 设置指定变量无符号8位整型数值
/// </summary>
/// <param name="id"></param>
/// <param name="value"></param>
/// <returns></returns>
YD_MOTION_API yd_set_variable_uint8(UInt64 id, Byte value);

/// <summary>
/// 获取指定变量有符号16位整型数值
/// </summary>
/// <param name="id"></param>
/// <param name="value"></param>
/// <param name="timestamp"></param>
/// <returns></returns>
YD_MOTION_API yd_get_variable_int16(UInt64 id, Int16* value, UInt64* timestamp = nullptr);

/// <summary>
/// 设置指定变量有符号16位整型数值
/// </summary>
/// <param name="id"></param>
/// <param name="value"></param>
/// <returns></returns>
YD_MOTION_API yd_set_variable_int16(UInt64 id, Int16 value);

/// <summary>
/// 获取指定变量无符号16位整型数值
/// </summary>
/// <param name="id"></param>
/// <param name="value"></param>
/// <param name="timestamp"></param>
/// <returns></returns>
YD_MOTION_API yd_get_variable_uint16(UInt64 id, UInt16* value, UInt64* timestamp = nullptr);

/// <summary>
/// 设置指定变量无符号16位整型数值
/// </summary>
/// <param name="id"></param>
/// <param name="value"></param>
/// <returns></returns>
YD_MOTION_API yd_set_variable_uint16(UInt64 id, UInt16 value);

/// <summary>
/// 获取指定变量有符号32位整型数值
/// </summary>
/// <param name="id"></param>
/// <param name="value"></param>
/// <param name="timestamp"></param>
/// <returns></returns>
YD_MOTION_API yd_get_variable_int32(UInt64 id, Int32* value, UInt64* timestamp = nullptr);

/// <summary>
/// 设置指定变量有符号32位整型数值
/// </summary>
/// <param name="id"></param>
/// <param name="value"></param>
/// <returns></returns>
YD_MOTION_API yd_set_variable_int32(UInt64 id, Int32 value);

/// <summary>
/// 获取指定变量无符号32位整型数值
/// </summary>
/// <param name="id"></param>
/// <param name="value"></param>
/// <param name="timestamp"></param>
/// <returns></returns>
YD_MOTION_API yd_get_variable_uint32(UInt64 id, UInt32* value, UInt64* timestamp = nullptr);

/// <summary>
/// 设置指定变量无符号32位整型数值
/// </summary>
/// <param name="id"></param>
/// <param name="value"></param>
/// <returns></returns>
YD_MOTION_API yd_set_variable_uint32(UInt64 id, UInt32 value);

/// <summary>
/// 获取指定变量有符号64位整型数值
/// </summary>
/// <param name="id"></param>
/// <param name="value"></param>
/// <param name="timestamp"></param>
/// <returns></returns>
YD_MOTION_API yd_get_variable_int64(UInt64 id, Int64* value, UInt64* timestamp = nullptr);

/// <summary>
/// 设置指定变量有符号64位整型数值
/// </summary>
/// <param name="id"></param>
/// <param name="value"></param>
/// <returns></returns>
YD_MOTION_API yd_set_variable_int64(UInt64 id, Int64 value);

/// <summary>
/// 获取指定变量无符号64位整型数值
/// </summary>
/// <param name="id"></param>
/// <param name="value"></param>
/// <param name="timestamp"></param>
/// <returns></returns>
YD_MOTION_API yd_get_variable_uint64(UInt64 id, UInt64* value, UInt64* timestamp = nullptr);

/// <summary>
/// 设置指定变量无符号64位整型数值
/// </summary>
/// <param name="id"></param>
/// <param name="value"></param>
/// <returns></returns>
YD_MOTION_API yd_set_variable_uint64(UInt64 id, UInt64 value);

/// <summary>
/// 获取指定变量单精度浮点型数值
/// </summary>
/// <param name="id"></param>
/// <param name="value"></param>
/// <param name="timestamp"></param>
/// <returns></returns>
YD_MOTION_API yd_get_variable_float(UInt64 id, Single* value, UInt64* timestamp = nullptr);

/// <summary>
/// 设置指定变量单精度浮点型数值
/// </summary>
/// <param name="id"></param>
/// <param name="value"></param>
/// <returns></returns>
YD_MOTION_API yd_set_variable_float(UInt64 id, Single value);

/// <summary>
/// 获取指定变量双精度浮点型数值
/// </summary>
/// <param name="id"></param>
/// <param name="value"></param>
/// <param name="timestamp"></param>
/// <returns></returns>
YD_MOTION_API yd_get_variable_double(UInt64 id, Double* value, UInt64* timestamp = nullptr);

/// <summary>
/// 设置指定变量双精度浮点型数值
/// </summary>
/// <param name="id"></param>
/// <param name="value"></param>
/// <returns></returns>
YD_MOTION_API yd_set_variable_double(UInt64 id, Double value);

/// <summary>
/// 获取指定变量字符串数值
/// </summary>
/// <param name="id"></param>
/// <param name="value"></param>
/// <param name="size"></param>
/// <param name="timestamp"></param>
/// <returns></returns>
YD_MOTION_API yd_get_variable_string(UInt64 id, Char* value, Int32 size, UInt64* timestamp = nullptr);

/// <summary>
/// 设置指定变量字符串数值
/// </summary>
/// <param name="id"></param>
/// <param name="value"></param>
/// <returns></returns>
YD_MOTION_API yd_set_variable_string(UInt64 id, const Char* value);

/// <summary>
/// 获取指定变量运动坐标
/// </summary>
/// <param name="id"></param>
/// <param name="pMotionCoords"></param>
/// <param name="timestamp"></param>
/// <returns></returns>
YD_MOTION_API yd_get_variable_motion_coords(UInt64 id, YD_MotionCoords* pMotionCoords, UInt64* timestamp = nullptr);

/// <summary>
/// 设置指定变量运动坐标
/// </summary>
/// <param name="id"></param>
/// <param name="pMotionCoords"></param>
/// <returns></returns>
YD_MOTION_API yd_set_variable_motion_coords(UInt64 id, YD_MotionCoords* pMotionCoords);

/// <summary>
/// 获取指定id的DI输入
/// </summary>
/// <param name="card"></param>
/// <param name="type"></param>
/// <param name="index"></param>
/// <param name="pDIInfo"></param>
/// <returns></returns>
YD_MOTION_API yd_get_digital_input_by_id(UInt16 card, UInt16 type, UInt16 index, YD_IOInfo* pDIInfo);

/// <summary>
/// 获取指定名称的DI输入
/// </summary>
/// <param name="name"></param>
/// <param name="pDIInfo"></param>
/// <returns></returns>
YD_MOTION_API yd_get_digital_input_by_name(const Char* name, YD_IOInfo* pDIInfo);

/// <summary>
/// 获取DI输入状态
/// </summary>
/// <param name="card"></param>
/// <param name="type"></param>
/// <param name="index"></param>
/// <param name="value"></param>
/// <param name="timestamp"></param>
/// <returns></returns>
YD_MOTION_API yd_get_digital_input_status(UInt16 card, UInt16 type, UInt16 index, Boolean* value, UInt64* timestamp = nullptr);

/// <summary>
/// 获取指定id的DO输出
/// </summary>
/// <param name="card"></param>
/// <param name="type"></param>
/// <param name="index"></param>
/// <param name="pDOInfo"></param>
/// <returns></returns>
YD_MOTION_API yd_get_digital_output_by_id(UInt16 card, UInt16 type, UInt16 index, YD_IOInfo* pDOInfo);

/// <summary>
/// 获取指定名称的DO输出
/// </summary>
/// <param name="name"></param>
/// <param name="pDOInfo"></param>
/// <returns></returns>
YD_MOTION_API yd_get_digital_output_by_name(const Char* name, YD_IOInfo* pDOInfo);

/// <summary>
/// 获取DO输出状态
/// </summary>
/// <param name="card"></param>
/// <param name="type"></param>
/// <param name="index"></param>
/// <param name="value"></param>
/// <param name="timestamp"></param>
/// <returns></returns>
YD_MOTION_API yd_get_digital_output_status(UInt16 card, UInt16 type, UInt16 index, Boolean* value, UInt64* timestamp = nullptr);

/// <summary>
/// 控制DO输出
/// </summary>
/// <param name="card"></param>
/// <param name="type"></param>
/// <param name="index"></param>
/// <param name="value"></param>
/// <param name="timeout"></param>
/// <returns></returns>
YD_MOTION_API yd_set_digital_output_status(UInt16 card, UInt16 type, UInt16 index, Boolean value, UInt32 timeout = 3000);

/// <summary>
/// 获取指定id的运动轴
/// </summary>
/// <param name="card"></param>
/// <param name="axis"></param>
/// <param name="pAxisInfo"></param>
/// <returns></returns>
YD_MOTION_API yd_get_axis_by_id(UInt16 card, UInt16 axis, YD_AxisInfo* pAxisInfo);

/// <summary>
/// 获取指定名称的运动轴
/// </summary>
/// <param name="name"></param>
/// <param name="pAxisInfo"></param>
/// <returns></returns>
YD_MOTION_API yd_get_axis_by_name(const Char* name, YD_AxisInfo* pAxisInfo);

/// <summary>
/// 指定轴打开使能
/// </summary>
/// <param name="card"></param>
/// <param name="axis"></param>
/// <param name="timeout"></param>
/// <returns></returns>
YD_MOTION_API yd_enable_axis(UInt16 card, UInt16 axis, UInt32 timeout = 3000);

/// <summary>
/// 指定轴关闭使能
/// </summary>
/// <param name="card"></param>
/// <param name="axis"></param>
/// <param name="timeout"></param>
/// <returns></returns>
YD_MOTION_API yd_disable_axis(UInt16 card, UInt16 axis, UInt32 timeout = 3000);

/// <summary>
/// 指定轴报警清除
/// </summary>
/// <param name="card"></param>
/// <param name="axis"></param>
/// <param name="timeout"></param>
/// <returns></returns>
YD_MOTION_API yd_clear_axis_alarm(UInt16 card, UInt16 axis, UInt32 timeout = 3000);

/// <summary>
/// 指定轴位置清零
/// </summary>
/// <param name="card"></param>
/// <param name="axis"></param>
/// <param name="timeout"></param>
/// <returns></returns>
YD_MOTION_API yd_zero_axis_position(UInt16 card, UInt16 axis, UInt32 timeout = 3000);

/// <summary>
/// 获取指定轴状态
/// </summary>
/// <param name="card"></param>
/// <param name="axis"></param>
/// <param name="pAxisStates"></param>
/// <returns></returns>
YD_MOTION_API yd_get_axis_states(UInt16 card, UInt16 axis, YD_AxisStates* pAxisStates);

/// <summary>
/// 启动指定轴指定轴回零运动
/// </summary>
/// <param name="card"></param>
/// <param name="axis"></param>
/// <param name="timeout"></param>
/// <returns></returns>
YD_MOTION_API yd_start_axis_home_move(UInt16 card, UInt16 axis, UInt32 timeout = 3000);

/// <summary>
/// 启动指定轴绝对运动
/// </summary>
/// <param name="card"></param>
/// <param name="axis"></param>
/// <param name="position"></param>
/// <param name="velocity"></param>
/// <param name="timeout"></param>
/// <returns></returns>
YD_MOTION_API yd_start_axis_absolute_move(UInt16 card, UInt16 axis, Double position, Double velocity, UInt32 timeout = 3000);

/// <summary>
/// 启动指定轴相对运动
/// </summary>
/// <param name="card"></param>
/// <param name="axis"></param>
/// <param name="distance"></param>
/// <param name="velocity"></param>
/// <param name="direction"></param>
/// <param name="timeout"></param>
/// <returns></returns>
YD_MOTION_API yd_start_axis_relative_move(UInt16 card, UInt16 axis, Double distance, Double velocity, Byte direction, UInt32 timeout = 3000);

/// <summary>
/// 启动指定轴Jog运动
/// </summary>
/// <param name="card"></param>
/// <param name="axis"></param>
/// <param name="velocity"></param>
/// <param name="direction"></param>
/// <param name="timeout"></param>
/// <returns></returns>
YD_MOTION_API yd_start_axis_jog_move(UInt16 card, UInt16 axis, Double velocity, Byte direction, UInt32 timeout = 3000);

/// <summary>
/// 启动多轴运动
/// </summary>
/// <param name="pMotionCoords"></param>
/// <param name="timeout"></param>
/// <returns></returns>
YD_MOTION_API yd_start_multi_axis_moves(YD_MotionCoords* pMotionCoords, UInt32 timeout = 3000);

/// <summary>
/// 停止指定轴运动
/// </summary>
/// <param name="card"></param>
/// <param name="axis"></param>
/// <param name="urgent"></param>
/// <param name="timeout"></param>
/// <returns></returns>
YD_MOTION_API yd_stop_axis_move(UInt16 card, UInt16 axis, Boolean urgent, UInt32 timeout = 3000);

/// <summary>
/// 获取指定轴驱动报警标志
/// </summary>
/// <param name="card"></param>
/// <param name="axis"></param>
/// <param name="flag"></param>
/// <returns></returns>
YD_MOTION_API yd_get_axis_driver_alarm_flag(UInt16 card, UInt16 axis, Boolean* flag);

/// <summary>
/// 获取跟随误差标志
/// </summary>
/// <param name="card"></param>
/// <param name="axis"></param>
/// <param name="flag"></param>
/// <returns></returns>
YD_MOTION_API yd_get_axis_follow_error_flag(UInt16 card, UInt16 axis, Boolean* flag);

/// <summary>
/// 获取正向限位标志
/// </summary>
/// <param name="card"></param>
/// <param name="axis"></param>
/// <param name="flag"></param>
/// <returns></returns>
YD_MOTION_API yd_get_axis_positive_limit_flag(UInt16 card, UInt16 axis, Boolean* flag);

/// <summary>
/// 获取负向限位标志
/// </summary>
/// <param name="card"></param>
/// <param name="axis"></param>
/// <param name="flag"></param>
/// <returns></returns>
YD_MOTION_API yd_get_axis_negative_limit_flag(UInt16 card, UInt16 axis, Boolean* flag);

/// <summary>
/// 获取平滑停止标志
/// </summary>
/// <param name="card"></param>
/// <param name="axis"></param>
/// <param name="flag"></param>
/// <returns></returns>
YD_MOTION_API yd_get_axis_smooth_stop_flag(UInt16 card, UInt16 axis, Boolean* flag);

/// <summary>
/// 获取紧急停止标志
/// </summary>
/// <param name="card"></param>
/// <param name="axis"></param>
/// <param name="flag"></param>
/// <returns></returns>
YD_MOTION_API yd_get_axis_urgent_stop_flag(UInt16 card, UInt16 axis, Boolean* flag);

/// <summary>
/// 获取伺服使能标志
/// </summary>
/// <param name="card"></param>
/// <param name="axis"></param>
/// <param name="flag"></param>
/// <returns></returns>
YD_MOTION_API yd_get_axis_servo_on_flag(UInt16 card, UInt16 axis, Boolean* flag);

/// <summary>
/// 获取规划运动标志
/// </summary>
/// <param name="card"></param>
/// <param name="axis"></param>
/// <param name="flag"></param>
/// <returns></returns>
YD_MOTION_API yd_get_axis_profile_move_flag(UInt16 card, UInt16 axis, Boolean* flag);

/// <summary>
/// 获取电机到位标志
/// </summary>
/// <param name="card"></param>
/// <param name="axis"></param>
/// <param name="flag"></param>
/// <returns></returns>
YD_MOTION_API yd_get_axis_motor_arrive_flag(UInt16 card, UInt16 axis, Boolean* flag);

/// <summary>
/// 获取原点信号标志
/// </summary>
/// <param name="card"></param>
/// <param name="axis"></param>
/// <param name="flag"></param>
/// <returns></returns>
YD_MOTION_API yd_get_axis_home_signal_flag(UInt16 card, UInt16 axis, Boolean* flag);

/// <summary>
/// 获取回零状态标志
/// </summary>
/// <param name="card"></param>
/// <param name="axis"></param>
/// <param name="flag"></param>
/// <returns></returns>
YD_MOTION_API yd_get_axis_home_moved_flag(UInt16 card, UInt16 axis, Boolean* flag);

/// <summary>
/// 获取运动模式
/// </summary>
/// <param name="card"></param>
/// <param name="axis"></param>
/// <param name="mode"></param>
/// <returns></returns>
YD_MOTION_API yd_get_axis_profile_mode(UInt16 card, UInt16 axis, UInt32* mode);

/// <summary>
/// 获取目标位置
/// </summary>
/// <param name="card"></param>
/// <param name="axis"></param>
/// <param name="position"></param>
/// <returns></returns>
YD_MOTION_API yd_get_axis_target_position(UInt16 card, UInt16 axis, Double* position);

/// <summary>
/// 获取目标速度
/// </summary>
/// <param name="card"></param>
/// <param name="axis"></param>
/// <param name="velocity"></param>
/// <returns></returns>
YD_MOTION_API yd_get_axis_target_velocity(UInt16 card, UInt16 axis, Double* velocity);

/// <summary>
/// 获取规划位置
/// </summary>
/// <param name="card"></param>
/// <param name="axis"></param>
/// <param name="position"></param>
/// <returns></returns>
YD_MOTION_API yd_get_axis_profile_position(UInt16 card, UInt16 axis, Double* position);

/// <summary>
/// 获取规划速度
/// </summary>
/// <param name="card"></param>
/// <param name="axis"></param>
/// <param name="velocity"></param>
/// <returns></returns>
YD_MOTION_API yd_get_axis_profile_velocity(UInt16 card, UInt16 axis, Double* velocity);

/// <summary>
/// 获取编码器位置（反馈位置）
/// </summary>
/// <param name="card"></param>
/// <param name="axis"></param>
/// <param name="position"></param>
/// <returns></returns>
YD_MOTION_API yd_get_axis_encoder_position(UInt16 card, UInt16 axis, Double* position);

/// <summary>
/// 获取编码器速度（反馈速度）
/// </summary>
/// <param name="card"></param>
/// <param name="axis"></param>
/// <param name="velocity"></param>
/// <returns></returns>
YD_MOTION_API yd_get_axis_encoder_velocity(UInt16 card, UInt16 axis, Double* velocity);

/// <summary>
/// 获取回零状态
/// </summary>
/// <param name="card"></param>
/// <param name="axis"></param>
/// <param name="status"></param>
/// <returns></returns>
YD_MOTION_API yd_get_axis_home_move_status(UInt16 card, UInt16 axis, Byte* status);

/// <summary>
/// 更新回零状态
/// </summary>
/// <param name="card"></param>
/// <param name="axis"></param>
/// <param name="status"></param>
/// <returns></returns>
YD_MOTION_API yd_set_axis_home_move_status(UInt16 card, UInt16 axis, Byte status);

/// <summary>
/// 根据轴号获取运动轴回原点参数
/// </summary>
/// <param name="card"></param>
/// <param name="axis"></param>
/// <param name="pHomeConfig"></param>
/// <returns></returns>
YD_MOTION_API yd_get_axis_home_config_by_id(UInt16 card, UInt16 axis, YD_AxisHomeConfig* pHomeConfig);

/// <summary>
/// 根据轴名称获取运动轴回原点参数
/// </summary>
/// <param name="name"></param>
/// <param name="pHomeConfig"></param>
/// <returns></returns>
YD_MOTION_API yd_get_axis_home_config_by_name(const Char* name, YD_AxisHomeConfig* pHomeConfig);

/// <summary>
/// 根据id获取气油缸信息
/// </summary>
/// <param name="id"></param>
/// <param name="pCylinderInfo"></param>
/// <returns></returns>
YD_MOTION_API yd_get_cylinder_by_id(UInt32 id, YD_CylinderInfo* pCylinderInfo);

/// <summary>
/// 根据名称获取气油缸信息
/// </summary>
/// <param name="name"></param>
/// <param name="pCylinderInfo"></param>
/// <returns></returns>
YD_MOTION_API yd_get_cylinder_by_name(const Char* name, YD_CylinderInfo* pCylinderInfo);

/// <summary>
/// 获取气油缸状态
/// </summary>
/// <param name="id"></param>
/// <param name="pCylinderStates"></param>
/// <returns></returns>
YD_MOTION_API yd_get_cylinder_states(UInt32 id, YD_CylinderStates* pCylinderStates);

/// <summary>
/// 控制气油缸运动
/// </summary>
/// <param name="id"></param>
/// <param name="direction"></param>
/// <returns></returns>
YD_MOTION_API yd_control_cylinder_move(UInt32 id, Byte direction, UInt32 timeout = 3000);

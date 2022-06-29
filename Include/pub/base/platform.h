#ifndef __PLATFORM_H__
#define __PLATFORM_H__
//
// basic primitive data types:
//   byte, int8, uint8, int16, uint16, int32, uint32, float32, float64
//   char, string, boolean, time, octetString, binaryString, octet, displayString
//   octetString
//

#pragma warning(disable:4005)

#if !defined(byte)
typedef unsigned char byte;
#endif

#if !defined(int8)
typedef signed char int8;
#endif

#if !defined(uint8)
typedef unsigned char uint8;
#endif

#if !defined(int16)
typedef short int16;
#endif

#if !defined(uint16)
typedef unsigned short uint16;
#endif

#if !defined(int32)
typedef int int32;
#endif

#if !defined(uint32)
typedef unsigned int uint32;
#endif

#if !defined(float32)
typedef float float32;
#endif

#if !defined(float64)
typedef double float64;
#endif

#if !defined(octet)
typedef unsigned char octet;
#endif

#if !defined(sstring)
typedef char* sstring;
#endif

#if !defined(displayString)
typedef char* displayString;
#endif

#if !defined(octetString)
typedef unsigned char* octetString;
#endif

#if !defined(binaryString)
typedef unsigned char* binaryString;
#endif

#if !defined(uint64)
#if defined( WIN32 ) && ! defined( __MINGW32__ )
typedef unsigned __int64	uint64;
#else
typedef unsigned long long	uint64;
#endif
#endif

#if !defined(int64)
#if defined( WIN32 ) && ! defined( __MINGW32__ )
typedef __int64	int64;
#else
typedef long long	int64;
#endif
#endif

#if !defined(uint128)
typedef struct { unsigned char octet[16]; } uint128;
#endif

#if !defined(boolean)
typedef uint8 boolean;
#endif

#if !defined(ip_Address)
typedef unsigned char* ip_Address;
#endif

#if !defined(DateTime)
typedef unsigned long DateTime;
#endif

#if !defined(TRUE)
#define  TRUE ((boolean)1)
#endif

#if !defined(FALSE)
#define  FALSE ((boolean)0)
#endif

#if !defined(NULL)
#define  NULL ((int32)0)
#endif

#ifndef interface
#define interface struct
#endif

#if !defined(LPCSTR)
typedef  const char* LPCSTR;
#endif // !LPCSTR

#if !defined(LPSTR)
typedef  char* LPSTR;
#endif // !LPSTR


#if !defined(i8)
typedef int8 i8;
#endif

constexpr int32 TEXT_MINI = 16;
constexpr int32 TEXT_SMALL = 32;
constexpr int32 TEXT_MID = 64;
constexpr int32 TEXT_BIG = 128;
constexpr int32 TEXT_LONG = 256;
constexpr int32 TEXT_MAX = 512;
constexpr int32 TEXT_CONTENT = 1024;

typedef char STR_IP[TEXT_MINI];
typedef char STR_MINI[TEXT_MINI];
typedef char STR_ID[TEXT_SMALL];
typedef char STR_SMALL[TEXT_SMALL];
typedef char STR_MID[TEXT_MID];
typedef char STR_BIG[TEXT_BIG];
typedef char STR_LONG[TEXT_LONG];
typedef char STR_MAX[TEXT_MAX];
typedef char STR_CONTENT[TEXT_CONTENT];

// 配置存储格式
constexpr uint8 CONFIG_FORMA_XML = 1;
constexpr uint8 CONFIG_FORMA_SQLITE = 2;
constexpr uint8 CONFIG_FORMA_MYSQL = 3;

// 程序版本号
constexpr uint32 CURRENT_VERSION = 1100;
constexpr uint8 CURRENT_CONFIG_FORMAT = CONFIG_FORMA_XML;

// 跨语言接口返回值
constexpr int32 CROSS_INTERFACE_RESULT_SUCCESS = 0;
constexpr int32 CROSS_INTERFACE_RESULT_FAILED = -1;
constexpr int32 CROSS_INTERFACE_RESULT_RETRY = 1;

// 默认 .Net 命名
constexpr char DEFAULT_DOTNET_NAMESPACE[] = "YDApplication\0";
constexpr char DEFAULT_DOTNET_CLASS[] = "YDEntry\0";
constexpr char DEFAULT_DOTNET_FUNCTION[] = "Execute\0";

// 进程名称定义
constexpr char PROCESS_NAME_DAEMON[] = "YDDaemon\0";
constexpr char PROCESS_NAME_LOGIC_CONTROLLER[] = "YDLogicController\0";
constexpr char PROCESS_NAME_DATA_GATEWAY[] = "YDDataGateway\0";
constexpr char PROCESS_NAME_DATA_UPLOADER[] = "YDDataUploader\0";
constexpr char PROCESS_NAME_SCRIPT_EXECUTOR[] = "YDScriptExecutor\0";

// 配置名称定义
constexpr char CONFIG_PATH_NAME[] = "configs\0";
constexpr char DOWNLOAD_PATH_NAME[] = "downloads\0";
constexpr char UPLOAD_PATH_NAME[] = "uploads\0";
constexpr char COMPONENT_PATH_NAME[] = "components\0";
constexpr char DEPENDENCE_PATH_NAME[] = "dependences\0";
constexpr char LOG_PATH_NAME[] = "logs\0";
constexpr char PLUGIN_PATH_NAME[] = "plugins\0";
constexpr char TEMP_PATH_NAME[] = "temp\0";
constexpr char SCRIPT_PATH_NAME[] = "scripts\0";
constexpr char PROJECT_CFG_NAME[] = "Project.xml\0";
constexpr char RECIPE_CFG_NAME[] = "Recipe.xml\0";
constexpr char PROJECT_DATA_NAME[] = "ProjectData.xml\0";
constexpr char RECIPE_DATA_NAME[] = "RecipeData.xml\0";

// 设备类型名称定义
constexpr char MOTION_TYPE_NAME[] = "mod:dev:mc\0";
constexpr char CYLINDER_TYPE_NAME[] = "mod:dev:cy\0";
constexpr char IODEVICE_TYPE_NAME[] = "mod:dev:io\0";

// 回原点脚本名称定义
constexpr char HOME_MOVE_SCRIPT_NAME[] = "home_move\0";

// 数据类型定义
constexpr uint8 DATA_TYPE_NULL = 0;	// 表示空，无此数据，无此类型
constexpr uint8 DATA_TYPE_ENUM = 1;	// 枚举类型
constexpr uint8 DATA_TYPE_BOOL = 2;	// 布尔型
constexpr uint8 DATA_TYPE_INT8 = 3;	// 有符号字符型（有符号8位整型）
constexpr uint8 DATA_TYPE_UINT8 = 4;	// 无符号字符型（元符号8位整型）
constexpr uint8 DATA_TYPE_INT16 = 5;	// 有符号短整型（有符号16位整型）
constexpr uint8 DATA_TYPE_UINT16 = 6;	// 无符号短整型（无符号16位整型）
constexpr uint8 DATA_TYPE_INT32 = 7;	// 有符号整型（有符号32位整型）
constexpr uint8 DATA_TYPE_UINT32 = 8;	// 无符号整型（无符号32位整型）
constexpr uint8 DATA_TYPE_INT64 = 9;	// 有符号长整型（有符号64位长整型）
constexpr uint8 DATA_TYPE_UINT64 = 10;	// 无符号长整型（无符号64位长整型）
constexpr uint8 DATA_TYPE_FLOAT = 11;	// 单精度浮点型（32位）
constexpr uint8 DATA_TYPE_DOUBLE = 12;	// 双精度浮点型（64位）
constexpr uint8 DATA_TYPE_STRING = 13;	// 字符串形(std::string)
constexpr uint8 DATA_TYPE_AUTODATA = 14;	// 自动数据类型(IAutoData*)
constexpr uint8 DATA_TYPE_REALTYPE = 15;	// 其它用户自定义实类型(可以直接内存复制的类型)
constexpr uint8 DATA_TYPE_MEMORY_ADDR = 16;	// 内存地址
constexpr uint8 DATA_TYPE_AXIS_COORD = 17;	// 轴坐标

// 接口状态定义
constexpr uint8 INTERFACE_STATUS_SUCCESS = 0;	// 成功
constexpr uint8 INTERFACE_STATUS_FAILURE = 1;	// 失败	
constexpr uint8 INTERFACE_STATUS_READY = 2;	// 就绪
constexpr uint8 INTERFACE_STATUS_UNINIT = 3;	// 未初始化	
constexpr uint8 INTERFACE_STATUS_UNCONNECT = 4;	// 未连接
constexpr uint8 INTERFACE_STATUS_UNLOGIN = 5;	// 未登录
constexpr uint8 INTERFACE_STATUS_BUSY = 6;	// 设备忙

// 状态类型定义
constexpr uint8 STATUS_TYPE_TASK = 1;	// 任务
constexpr uint8 STATUS_TYPE_PROCESS = 2;	// 流程
constexpr uint8 STATUS_TYPE_LINK = 3;	// 连接
constexpr uint8 STATUS_TYPE_INTERFACE = 4;	// 接口

// 日志级别
constexpr uint8 LOG_LEVEL_TRACE = 1;	// 跟踪
constexpr uint8 LOG_LEVEL_DEBUG = 2;	// 调试
constexpr uint8 LOG_LEVEL_INFO = 3;	// 信息
constexpr uint8 LOG_LEVEL_WARN = 4;	// 警告
constexpr uint8 LOG_LEVEL_ERROR = 5;	// 错误
constexpr uint8 LOG_LEVEL_CRITICAL = 6;	// 致命
constexpr uint8 LOG_LEVEL_OFF = 7;	// 关闭

// 常量值定义
constexpr int64 NAN_VALUE = (int64)(-1E9);
constexpr double PI = 3.1415926535897932384626433832795;
constexpr double EPSINON_ZERO = 0.000000001;

// 数值方向定义
constexpr uint8 COMMU_VALUE_INPUT = 1;
constexpr uint8 COMMU_VALUE_OUTPUT = 2;
constexpr uint8 COMMU_VALUE_RETURN = 3;

// 执行结果定义
constexpr int32 COMMU_RESULT_TIME_OUT = -3;
constexpr int32 COMMU_RESULT_INVALID = -2;
constexpr int32 COMMU_RESULT_FAILURE = -1;
constexpr int32 COMMU_RESULT_WAITING = 0;
constexpr int32 COMMU_RESULT_SUCCESS = 1;
constexpr int32 COMMU_RESULT_IN_PROCESS = 2;

// 逻辑数据类型定义
constexpr uint8 LOGIC_DATA_TASK = 1;
constexpr uint8 LOGIC_DATA_PROCESS = 2;
constexpr uint8 LOGIC_DATA_INTERFACE = 3;

// 消息长度定义
constexpr uint32 MESSAGE_TIME_LENGTH = 24;
constexpr uint32 MESSAGE_NAME_LENGTH = 64;
constexpr uint32 MESSAGE_FILTER_LENGTH = 20;
constexpr uint32 MESSAGE_CONTENT_LENGTH = 1024;
constexpr uint32 MAX_MESSAGE_NUMBER = 200;

// 数据长度定义
constexpr uint32 MAX_NAME_LENGTH = 64;
constexpr uint32 MAX_VALUE_LENGTH = 64;
constexpr uint32 MAX_MOTION_AXIS_NUMBER = 64;
constexpr uint32 MAX_CYLINDER_NUMBER = 100;
constexpr uint32 MAX_IO_NUMBER = 512;
constexpr uint32 MAX_DI_VARIABLE_NUMBER = MAX_IO_NUMBER;
constexpr uint32 MAX_DO_VARIABLE_NUMBER = MAX_IO_NUMBER;
constexpr uint32 MAX_AI_VARIABLE_NUMBER = MAX_IO_NUMBER;
constexpr uint32 MAX_AO_VARIABLE_NUMBER = MAX_IO_NUMBER;
constexpr uint32 MAX_STATUS_VARIABLE_NUMBER = 4000;
constexpr uint32 MAX_CONFIG_VARIABLE_NUMBER = 1000;
constexpr uint32 MAX_VIRTUAL_VARIABLE_NUMBER = 1000;
constexpr uint32 MAX_CONTROL_VARIABLE_NUMBER = 100;
constexpr uint32 MAX_SAFEGUARD_VARIABLE_NUMBER = 200;
constexpr uint32 MAX_GLOBAL_VARIABLE_NUMBER = 200;
constexpr uint32 MAX_RECIPE_VARIABLE_NUMBER = 100;
constexpr uint32 MAX_LOCAL_VARIABLE_NUMBER = 120;
constexpr uint32 MAX_COMMAND_VALUE_NUMBER = 20;
constexpr uint32 VARIABLE_NAME_LENGTH = MAX_NAME_LENGTH;
constexpr uint32 VARIABLE_VALUE_LENGTH = MAX_VALUE_LENGTH;
constexpr uint8 MAX_AXIS_COORD_NUMBER = MAX_MOTION_AXIS_NUMBER;
constexpr uint32 MAX_LOGIC_NUMBER = 200;
constexpr uint32 MAX_TOTAL_VARIABLE_NUMBER = 6000;
constexpr uint32 MAX_LOGIC_TASK_NUMBER = 40;

// 变量类型定义
constexpr uint8 VARIABLE_TYPE_DI = 1;	// DI变量，只读
constexpr uint8 VARIABLE_TYPE_DO = 2;	// DO变量，读/写
constexpr uint8 VARIABLE_TYPE_AI = 3;	// AI变量，只读
constexpr uint8 VARIABLE_TYPE_AO = 4;	// AO变量，读/写
constexpr uint8 VARIABLE_TYPE_SYSTEM = 5;	// 系统变量，只读
constexpr uint8 VARIABLE_TYPE_AXIS = 6;	// 轴变量，只读
constexpr uint8 VARIABLE_TYPE_CYLINDER = 7;	// 气油缸变量，只读
constexpr uint8 VARIABLE_TYPE_CONFIG = 8;	// 配置变量，读/写
constexpr uint8 VARIABLE_TYPE_VIRTUAL = 9;	// 虚拟变量，读/写
constexpr uint8 VARIABLE_TYPE_CONTROL = 10;	// 控制变量，读/写
constexpr uint8 VARIABLE_TYPE_LOGIC = 11;	// 逻辑变量，读/写
constexpr uint8 VARIABLE_TYPE_SAFE = 12;	// 安全变量，只读
constexpr uint8 VARIABLE_TYPE_GLOBAL = 91;	// 全局变量，读/写
constexpr uint8 VARIABLE_TYPE_RECIPE = 92;	// 配方变量，读/写
constexpr uint8 VARIABLE_TYPE_LOCAL = 93;	// 临时变量，读/写

// 逻辑结果类型定义
constexpr uint8 LOGIC_RESULT_TASK = 1;
constexpr uint8 LOGIC_RESULT_SUB_TASK = 2;
constexpr uint8 LOGIC_RESULT_PROCESS = 3;
constexpr uint8 LOGIC_RESULT_SUB_PROCESS = 4;

// 系统变量ID定义
constexpr uint32 SYSTEM_VARIABLEID_SYSTEM_STATUS = 1;
constexpr uint32 SYSTEM_VARIABLEID_CONTROLLER_MODE = 2;
constexpr uint32 SYSTEM_VARIABLEID_VELOCITY_RATE = 3;

// 命令类型
constexpr uint16 COMMAND_TYPE_CONTROLLER_ACTION = 1;	// 控制器动作
constexpr uint16 COMMAND_TYPE_UPDATE_VARIABLES = 2;	// 更新变量
constexpr uint16 COMMAND_TYPE_INVOKE_PROCESS_METHOD = 3;	// 执行逻辑流程接口
constexpr uint16 COMMAND_TYPE_DOWNLOAD = 1001;
constexpr uint16 COMMAND_TYPE_UPLOAD = 1002;
constexpr uint16 COMMAND_TYPE_DEVICE_OPEN = 101;
constexpr uint16 COMMAND_TYPE_DEVICE_CLOSE = 102;
constexpr uint16 COMMAND_TYPE_DEVICE_RESET = 103;
constexpr uint16 COMMAND_TYPE_DEVICE_STOP = 104;
constexpr uint16 COMMAND_TYPE_DEVICE_READ = 105;
constexpr uint16 COMMAND_TYPE_DEVICE_ZERO = 106;
constexpr uint16 COMMAND_TYPE_DEVICE_SETUP = 107;
constexpr uint16 COMMAND_TYPE_ABSOLUTE_MOVE = 108;
constexpr uint16 COMMAND_TYPE_RELATIVE_MOVE = 109;
constexpr uint16 COMMAND_TYPE_JOG_MOVE = 110;
constexpr uint16 COMMAND_TYPE_MULTIAXISES_MOVE = 111;
constexpr uint16 COMMAND_TYPE_HOME_MOVE = 112;
constexpr uint16 COMMAND_TYPE_DO_CONTROL = 114;
constexpr uint16 COMMAND_TYPE_AO_CONTROL = 115;
constexpr uint16 COMMAND_TYPE_AXIS_ENABLE = 116;
constexpr uint16 COMMAND_TYPE_AXIS_CLEAR = 117;
constexpr uint16 COMMAND_TYPE_AXIS_ZERO = 118;
constexpr uint16 COMMAND_TYPE_AXIS_VELOCITY = 119;
constexpr uint16 COMMAND_TYPE_SET_AXIS_SOFT_LIMIT = 120;
constexpr uint16 COMMAND_TYPE_CYLINDER_CONTROL = 201;
constexpr uint16 COMMAND_TYPE_START_TASK_DEBUG = 301;
constexpr uint16 COMMAND_TYPE_STOP_TASK_DEBUG = 302;
constexpr uint16 COMMAND_TYPE_SUSPEND_TASK_DEBUG = 303;
constexpr uint16 COMMAND_TYPE_START_MAIN_TASK_DEBUG = 304;
constexpr uint16 COMMAND_TYPE_STOP_MAIN_TASK_DEBUG = 305;
constexpr uint16 COMMAND_TYPE_SUSPEND_MAIN_TASK_DEBUG = 306;
constexpr uint16 COMMAND_TYPE_EXECUTE_HOME_MOVE = 401;
constexpr uint16 COMMAND_TYPE_INTERACTION = 501;

// 轴规划运动模式
constexpr uint32 AXIS_PROFILE_MOVE_ABSOLUTE = COMMAND_TYPE_ABSOLUTE_MOVE;
constexpr uint32 AXIS_PROFILE_MOVE_RELATIVE = COMMAND_TYPE_RELATIVE_MOVE;
constexpr uint32 AXIS_PROFILE_MOVE_JOG = COMMAND_TYPE_JOG_MOVE;

// 多轴坐标运动定义
constexpr uint16 MULTI_AXIS_COORDS_TYPE_ABSOLUTE_MOVE = COMMAND_TYPE_ABSOLUTE_MOVE;
constexpr uint16 MULTI_AXIS_COORDS_TYPE_RELATIVE_MOVE = COMMAND_TYPE_RELATIVE_MOVE;
constexpr uint16 MULTI_AXIS_COORDS_TYPE_JOG_MOVE = COMMAND_TYPE_JOG_MOVE;
constexpr uint16 MULTI_AXIS_COORDS_TYPE_HOME_MOVE = COMMAND_TYPE_HOME_MOVE;

// 逻辑控制器动作类型
constexpr uint8 CONTROLLER_ACTION_START = 1;	// 启动控制器
constexpr uint8 CONTROLLER_ACTION_STOP = 2;	// 停止控制器
constexpr uint8 CONTROLLER_ACTION_SUSPEND = 3;	// 挂起控制器
constexpr uint8 CONTROLLER_ACTION_RESTORE = 4;	// 恢复控制器
constexpr uint8 CONTROLLER_ACTION_MANUAL_MODE = 5;	// 设置控制器手动模式
constexpr uint8 CONTROLLER_ACTION_AUTOMATIC_MODE = 6;	// 设置控制器自动模式

// 逻辑控制器工作模式
constexpr uint8 CONTROLLER_MODE_MANUAL = 0;
constexpr uint8 CONTROLLER_MODE_AUTOMATIC = 1;

// 系统状态
constexpr uint8 SYSTEM_STATUS_STOPED = 0;
constexpr uint8 SYSTEM_STATUS_RUNNING = 1;
constexpr uint8 SYSTEM_STATUS_SUSPENDED = 2;
constexpr uint8 SYSTEM_STATUS_RESTORED = 3;

// 成员扩展类型定义
constexpr uint64 FIELD_EXTEND_TYPE_NORMAL = 0;
constexpr uint64 FIELD_EXTEND_TYPE_ADDRESS = 1;

// DI类型定义
constexpr uint8 DITYPE_GENERAL = 0;
constexpr uint8 DITYPE_POSITIVE_LIMIT = 1;
constexpr uint8 DITYPE_NEGATIVE_LIMIT = 2;
constexpr uint8 DITYPE_DRIVER_ALARM = 3;
constexpr uint8 DITYPE_HOME_SIGNAL = 4;
constexpr uint8 DITYPE_MOTOR_ARRIVE = 5;

// DO类型定义
constexpr uint8 DOTYPE_GENERAL = 0;
constexpr uint8 DOTYPE_DRIVER_ENABLE = 1;
constexpr uint8 DOTYPE_ALARM_CLEAR = 2;

// AI类型定义
constexpr uint8 AITYPE_GENERAL = 0;

// AO类型定义
constexpr uint8 AOTYPE_GENERAL = 0;

// 系统设备定义
constexpr uint32 DEVICEID_SYSTEM = 10000;
constexpr uint32 DEVICEID_VIRTUAL = 10001;
constexpr uint32 DEVICEID_SAFE = 10002;

// 特殊逻辑id定义
constexpr uint32 TASKID_DEVICE_SPECIAL_FUNCTIONS = 1;

// 流程结果定义
constexpr int32 LOGIC_CODE_INVALID_PARAMETER = -4;	// 参数错误
constexpr int32 LOGIC_CODE_NOT_FOUND = -3;	// 未找到
constexpr int32 LOGIC_CODE_INTERRUPTED = -2;	// 已中断
constexpr int32 LOGIC_CODE_FAILURE = -1;	// 已失败
constexpr int32 LOGIC_CODE_WAITING = 0;	// 等待中
constexpr int32 LOGIC_CODE_SUCCESS = 1;	// 已成功
constexpr int32 LOGIC_CODE_IN_PROCESS = 2;	// 处理中

// 逻辑任务类型
constexpr uint8 LOGIC_TASK_TYPE_PRIMARY = 1;	// 主任务
constexpr uint8 LOGIC_TASK_TYPE_SECONDARY = 2;	// 子任务

// 逻辑执行方式
constexpr uint8 LOGIC_EXECUTE_METHOD_ONCE = 0;	// 执行一次
constexpr uint8 LOGIC_EXECUTE_METHOD_LOOP = 1;	// 循环执行

// 流程类型定义
constexpr uint8	LOGIC_PROCESS_INVALID = 0;	// 无效流程
constexpr uint8	LOGIC_PROCESS_INITIALIZE = 1;	// 初始化流程
constexpr uint8	LOGIC_PROCESS_UNINITIALIZE = 2;	// 反初始化流程
constexpr uint8	LOGIC_PROCESS_ABSOLUTE_MOVE = 3;	// 绝对运动流程
constexpr uint8	LOGIC_PROCESS_RELATIVE_MOVE = 4;	// 相对运动流程
constexpr uint8	LOGIC_PROCESS_JOG_MOVE = 5;	// Jog运动流程
constexpr uint8	LOGIC_PROCESS_MULTIAXISES_MOVE = 6;	// 多轴运动流程
constexpr uint8	LOGIC_PROCESS_HOME_MOVE = 7;	// 回零运动流程
constexpr uint8	LOGIC_PROCESS_STOP_MOVE = 9;	// 停止运动流程
constexpr uint8	LOGIC_PROCESS_DO_CONTROL = 10;	// 控制DO输出流程
constexpr uint8	LOGIC_PROCESS_AO_CONTROL = 11;	// 控制AO输出流程
constexpr uint8	LOGIC_PROCESS_IF_ELSE = 12;	// IF-ELSE判定条件流程
constexpr uint8	LOGIC_PROCESS_COUNTER_LOOP = 13;	// 计数循环流程
constexpr uint8	LOGIC_PROCESS_CONDITION_LOOP = 14;	// 条件循环流程
constexpr uint8	LOGIC_PROCESS_BREAK = 15;	// 跳出流程
constexpr uint8	LOGIC_PROCESS_DELAY = 16;	// 延时等待流程
constexpr uint8	LOGIC_PROCESS_MESSAGE = 17;	// 消息流程
constexpr uint8	LOGIC_PROCESS_TASK_CALLER = 18;	// 子例程调用流程
constexpr uint8	LOGIC_PROCESS_PROGRAMABLE = 19;	// 可编程模块流程
constexpr uint8	LOGIC_PROCESS_CYLINDER = 20;	// 气油缸模块流程
constexpr uint8	LOGIC_PROCESS_CONDITION = 21;	// 条件模块流程
constexpr uint8	LOGIC_PROCESS_INPLACE_WAIT = 22;	// 到位等待流程
constexpr uint8	LOGIC_PROCESS_TASK_STATE_WAIT = 23;	// 任务状态等待流程
constexpr uint8	LOGIC_PROCESS_JUMP_TO = 24;	// 跳转模块
constexpr uint8	LOGIC_PROCESS_IF = 25;	// IF条件流程

// 逻辑状态值
constexpr uint8 LOGIC_STATE_INVALID = 0;	// 不可用
constexpr uint8 LOGIC_STATE_READY = 1;	// 已就绪
constexpr uint8 LOGIC_STATE_IN_PROCESSING = 2;	// 运行中
constexpr uint8 LOGIC_STATE_COMPLETED = 3;	// 已完成
constexpr uint8 LOGIC_STATE_FAILED = 4;	// 已失败

// 逻辑任务状态值
constexpr uint8 LOGIC_TASK_STATE_INVALID = LOGIC_STATE_INVALID;
constexpr uint8 LOGIC_TASK_STATE_READY = LOGIC_STATE_READY;
constexpr uint8 LOGIC_TASK_STATE_IN_PROCESSING = LOGIC_STATE_IN_PROCESSING;
constexpr uint8 LOGIC_TASK_STATE_COMPLETED = LOGIC_STATE_COMPLETED;
constexpr uint8 LOGIC_TASK_STATE_FAILED = LOGIC_STATE_FAILED;

// 调试状态
constexpr uint8 DEBUG_STATE_STOPPED = 0;
constexpr uint8 DEBUG_STATE_IN_PROCESSING = 1;
constexpr uint8 DEBUG_STATE_SUSPENDED = 2;
constexpr uint8 DEBUG_STATE_FAILED = 3;

// 逻辑节点类型
constexpr uint8	LOGIC_NODE_TASK = 1;
constexpr uint8	LOGIC_NODE_SUBTASK = 2;
constexpr uint8	LOGIC_NODE_PROCESS = 3;

// 每个任务最大流程个数
constexpr uint32 MAX_LOGIC_PROCESS_NUMBER_EACH_TASK = 200;

// 模块类型
constexpr uint8 MODULE_TYPE_INVALID = 0;
constexpr uint8 MODULE_TYPE_DEVICE = 1;
constexpr uint8 MODULE_TYPE_GENERAL = 2;

// 逻辑运算类型定义
constexpr uint8 LOGIC_OPERATOR_AND = 1;
constexpr uint8 LOGIC_OPERATOR_OR = 2;

// 比较类型
constexpr uint8 COMPARE_TYPE_LESS_THAN = 1;
constexpr uint8 COMPARE_TYPE_LESS_EQUAL = 2;
constexpr uint8 COMPARE_TYPE_EQUAL_TO = 3;
constexpr uint8 COMPARE_TYPE_GREATER_THAN = 4;
constexpr uint8 COMPARE_TYPE_GREATER_EQUAL = 5;
constexpr uint8 COMPARE_TYPE_NOT_EQUAL_TO = 6;

// 访问类型
constexpr uint8 ACCESS_TYPE_RO = 1;
constexpr uint8 ACCESS_TYPE_WO = 2;
constexpr uint8 ACCESS_TYPE_RW = 3;

// 运行模式
constexpr uint8 RUNNING_MODE_NORMAL = 0;
constexpr uint8 RUNNING_MODE_DEBUG_MAIN_TIME = 1;
constexpr uint8 RUNNING_MODE_DEBUG_ALL_TIMES = 2;
constexpr uint8 RUNNING_MODE_DEBUG_FULL_INFO = 3;

// 索引数定义
constexpr uint8 MAX_USER_NUMBER = 30;
constexpr uint8 MAX_ROLE_NUMBER = 20;
constexpr uint8 MAX_PRIVILEGE_NUMBER = 40;

// 错误代码
constexpr int32 PROJECT_ERROR_NONE = 0;										// 无错误
constexpr int32 PROJECT_ERROR_BASE = -80000;								// 错误基址
constexpr int32 PROJECT_ERROR_GENERAL_FAILURE = PROJECT_ERROR_BASE - 1;		// 通用错误
constexpr int32 PROJECT_ERROR_INITIALIZE_FAILED = PROJECT_ERROR_BASE - 2;	// 初始化失败
constexpr int32 PROJECT_ERROR_LOAD_FAILED = PROJECT_ERROR_BASE - 3;			// 加载失败
constexpr int32 PROJECT_ERROR_SAVE_FAILED = PROJECT_ERROR_BASE - 4;			// 保存失败
constexpr int32 PROJECT_ERROR_CREATE_FAILED = PROJECT_ERROR_BASE - 5;		// 创建失败
constexpr int32 PROJECT_ERROR_UPDATE_FAILED = PROJECT_ERROR_BASE - 6;		// 更新失败
constexpr int32 PROJECT_ERROR_GET_FAILED = PROJECT_ERROR_BASE - 7;			// 获取失败
constexpr int32 PROJECT_ERROR_DELETE_FAILED = PROJECT_ERROR_BASE - 8;		// 删除失败
constexpr int32 PROJECT_ERROR_EXECUTE_FAILED = PROJECT_ERROR_BASE - 9;		// 执行失败
constexpr int32 PROJECT_ERROR_CONNECT_FAILED = PROJECT_ERROR_BASE - 10;		// 连接失败
constexpr int32 PROJECT_ERROR_COMMUNICATION_FAILED = PROJECT_ERROR_BASE - 11;// 通讯失败
constexpr int32 PROJECT_ERROR_LOCK_FAILED = PROJECT_ERROR_BASE - 12;		// 加锁失败
constexpr int32 PROJECT_ERROR_UNLOCK_FAILED = PROJECT_ERROR_BASE - 13;		// 解锁失败
constexpr int32 PROJECT_ERROR_LOGIN_FAILED = PROJECT_ERROR_BASE - 14;		// 登录失败
constexpr int32 PROJECT_ERROR_INVALID_INPUT = PROJECT_ERROR_BASE - 15;		// 无效输入
constexpr int32 PROJECT_ERROR_NOT_FOUND = PROJECT_ERROR_BASE - 16;			// 不存在
constexpr int32 PROJECT_ERROR_NOT_RESPONSE = PROJECT_ERROR_BASE - 17;		// 无响应
constexpr int32 PROJECT_ERROR_NOT_CONNECTED = PROJECT_ERROR_BASE - 18;		// 未连接
constexpr int32 PROJECT_ERROR_NOT_INITIALIZED = PROJECT_ERROR_BASE - 19;	// 未初始化
constexpr int32 PROJECT_ERROR_IN_PROCESS = PROJECT_ERROR_BASE - 20;			// 处理中
constexpr int32 PROJECT_ERROR_EXISTING = PROJECT_ERROR_BASE - 21;			// 已存在
constexpr int32 PROJECT_ERROR_REPEATED = PROJECT_ERROR_BASE - 22;			// 重复
constexpr int32 PROJECT_ERROR_PWD_INCORRECT = PROJECT_ERROR_BASE - 23;		// 密码错误
constexpr int32 PROJECT_ERROR_USER_INCORRECT = PROJECT_ERROR_BASE - 24;		// 用户错误
constexpr int32 PROJECT_ERROR_EXPIRED = PROJECT_ERROR_BASE - 25;			// 已过期
constexpr int32 PROJECT_ERROR_TIME_OUT = PROJECT_ERROR_BASE - 26;			// 已超时
constexpr int32 PROJECT_ERROR_NOT_LOGIN = PROJECT_ERROR_BASE - 27;			// 未登录
constexpr int32 PROJECT_ERROR_UNAUTHORIZED = PROJECT_ERROR_BASE - 28;		// 未授权
constexpr int32 PROJECT_ERROR_AUTHCODE_MISMATCHED = PROJECT_ERROR_BASE - 29;// 授权码不匹配
constexpr int32 PROJECT_ERROR_FULL = PROJECT_ERROR_BASE - 30;				// 已满
constexpr int32 PROJECT_ERROR_OVER_LIMIT = PROJECT_ERROR_BASE - 31;			// 超出限制
constexpr int32 PROJECT_ERROR_NOT_SUPPORTED = PROJECT_ERROR_BASE - 32;		// 不支持
constexpr int32 PROJECT_ERROR_IN_RUNNING = PROJECT_ERROR_BASE - 33;			// 运行中
constexpr int32 PROJECT_ERROR_INTERNAL = PROJECT_ERROR_BASE - 9000;			// 内部错误


// 访问结果定义
constexpr int32 ACCESS_RESULT_FULL = PROJECT_ERROR_FULL;
constexpr int32 ACCESS_RESULT_OVER_LIMIT = PROJECT_ERROR_OVER_LIMIT;
constexpr int32 ACCESS_RESULT_INVALID_PARAMETERS = PROJECT_ERROR_INVALID_INPUT;
constexpr int32 ACCESS_RESULT_FREE_FAILURE = PROJECT_ERROR_DELETE_FAILED;
constexpr int32 ACCESS_RESULT_LOCK_FAILURE = PROJECT_ERROR_LOCK_FAILED;
constexpr int32 ACCESS_RESULT_INITIALIZE_FAILURE = PROJECT_ERROR_INITIALIZE_FAILED;
constexpr int32 ACCESS_RESULT_OPEN_FAILURE = PROJECT_ERROR_LOAD_FAILED;
constexpr int32 ACCESS_RESULT_CREATE_FAILURE = PROJECT_ERROR_CREATE_FAILED;
constexpr int32 ACCESS_RESULT_NOT_AUTHORIZED = PROJECT_ERROR_UNAUTHORIZED;
constexpr int32 ACCESS_RESULT_NOT_FOUND = PROJECT_ERROR_NOT_FOUND;
constexpr int32 ACCESS_RESULT_NOT_INITIALIZED = PROJECT_ERROR_NOT_INITIALIZED;
constexpr int32 ACCESS_RESULT_NOT_OPENED = PROJECT_ERROR_NOT_CONNECTED;
constexpr int32 ACCESS_RESULT_FAILURE = PROJECT_ERROR_GENERAL_FAILURE;
constexpr int32 ACCESS_RESULT_SUCCESS = PROJECT_ERROR_NONE;
constexpr int32 ACCESS_RESULT_REPEATED = PROJECT_ERROR_REPEATED;

// 权限类型定义
constexpr uint8 PRIVILEGE_TYPE_INVALID = 0;	// 未授权
constexpr uint8 PRIVILEGE_TYPE_READ_ONLY = 1;	// 只读
constexpr uint8 PRIVILEGE_TYPE_WRITE_ONLY = 2;	// 只写
constexpr uint8 PRIVILEGE_TYPE_READ_WRITE = 3;	// 读/写

// 角色类型定义
constexpr uint8 ROLE_TYPE_INVALID = 0;	// 无效
constexpr uint8 ROLE_TYPE_SUPERADMIN = 1;	// 超级管理员
constexpr uint8 ROLE_TYPE_ADMIN = 2;	// 普通管理员
constexpr uint8 ROLE_TYPE_MAINTENANCE = 3;	// 设备维护员
constexpr uint8 ROLE_TYPE_OPERATOR = 4;	// 操作员
constexpr uint8 ROLE_TYPE_GUEST = 5;	// 访客

// 接口用户数据掩码定义
constexpr uint32 INTF_USERDATA_MASK_NONE = 0x00000001;
constexpr uint32 INTF_USERDATA_MASK_RESTORE = 0x00000002;

// 轴回零状态
constexpr uint8 AXIS_HOME_MOVE_NOT_EXECUTED = 0;
constexpr uint8 AXIS_HOME_MOVE_IN_PROCESSING = 1;
constexpr uint8 AXIS_HOME_MOVE_EXECUTED = 2;

// 轴坐标控制类型
constexpr uint8 AXIS_COORD_CTRL_RUN_ONE_AFTER_ONE = 0;	// 等待一个轴坐标命令执行完毕
constexpr uint8 AXIS_COORD_CTRL_START_ONE_BY_ONE = 1;	// 逐步轴坐标命令启动

// 轴命令类型
constexpr uint8 AXIS_COMMAND_MOVE_ABSOLUTE = 1;
constexpr uint8 AXIS_COMMAND_MOVE_RELATIVE = 2;
constexpr uint8 AXIS_COMMAND_MOVE_JOG = 3;

// 轴停止方式
constexpr uint8 AXIS_STOP_SMOOTHLY = 0;
constexpr uint8 AXIS_STOP_URGENTLY = 1;

// 消息流程定义
constexpr uint8 ALARM_MESSAGE_LEVEL_INFO = 0;
constexpr uint8 ALARM_MESSAGE_LEVEL_WARNING = 1;
constexpr uint8 ALARM_MESSAGE_LEVEL_ERROR = 2;

// 交互指令定义
constexpr uint8 INTERACT_COMMAND_CONFIRM = 1;
constexpr uint8 INTERACT_COMMAND_IGNORE = 2;
constexpr uint8 INTERACT_COMMAND_RETRY = 3;
constexpr uint8 INTERACT_COMMAND_TERMINATE = 4;
constexpr uint8 INTERACT_COMMAND_JUMPTO = 5;

// 交互动作个数
constexpr uint8 MAX_INTERACT_ACTION_NUMBER = 10;

// 交互命令执行结果
constexpr uint8 INTERACT_RESULT_TIME_OUT = COMMU_RESULT_TIME_OUT;
constexpr uint8 INTERACT_RESULT_INVALID = COMMU_RESULT_INVALID;
constexpr uint8 INTERACT_RESULT_FAILURE = COMMU_RESULT_FAILURE;
constexpr uint8 INTERACT_RESULT_WAITING = COMMU_RESULT_WAITING;
constexpr uint8 INTERACT_RESULT_SUCCESS = COMMU_RESULT_SUCCESS;
constexpr uint8 INTERACT_RESULT_IN_PROCESS = COMMU_RESULT_IN_PROCESS;

// 气油缸定义
constexpr uint8 CYLINDER_ARRIVE_IF_DELAYED = 1;
constexpr uint8 CYLINDER_ARRIVE_IF_DITRIGGRED = 2;
constexpr uint8 CYLINDER_ARRIVE_IF_DITRIGGRED_T_DELAYED = 3;
constexpr uint8 CYLINDER_ARRIVE_IF_AXIS_ENCODER_TO = 4;

// 接口方法定义
constexpr uint8 METHOD_TYPE_OPEN = 1;
constexpr uint8 METHOD_TYPE_CLOSE = 2;
constexpr uint8 METHOD_TYPE_STOP = 3;
constexpr uint8 METHOD_TYPE_RESET = 4;
constexpr uint8 METHOD_TYPE_READ = 5;
constexpr uint8 METHOD_TYPE_ZERO_AXIS = 6;
constexpr uint8 METHOD_TYPE_ENABLE_AXIS = 7;
constexpr uint8 METHOD_TYPE_CLEAR_AXIS = 8;
constexpr uint8 METHOD_TYPE_STOP_MOVE_SMOOTHLY = 9;
constexpr uint8 METHOD_TYPE_STOP_MOVE_URGENTLY = 10;
constexpr uint8 METHOD_TYPE_START_ABSOLUTE_MOVE = 11;
constexpr uint8 METHOD_TYPE_START_RELATIVE_MOVE = 12;
constexpr uint8 METHOD_TYPE_START_JOG_MOVE = 13;
constexpr uint8 METHOD_TYPE_START_MULTIAXISES_MOVE = 14;
constexpr uint8 METHOD_TYPE_WAIT_FOR_INPLACE = 15;
constexpr uint8 METHOD_TYPE_SEND_DO_CONTROL = 16;
constexpr uint8 METHOD_TYPE_SEND_AO_CONTROL = 17;
constexpr uint8 METHOD_TYPE_GET_DISTATUS = 18;
constexpr uint8 METHOD_TYPE_GET_DOSTATUS = 19;
constexpr uint8 METHOD_TYPE_GET_AIVALUE = 20;
constexpr uint8 METHOD_TYPE_GET_AOVALUE = 21;
constexpr uint8 METHOD_TYPE_SET_TARGET_POSITION = 22;
constexpr uint8 METHOD_TYPE_GET_TARGET_POSITION = 23;
constexpr uint8 METHOD_TYPE_SET_TARGET_VELOCITY = 24;
constexpr uint8 METHOD_TYPE_GET_TARGET_VELOCITY = 25;
constexpr uint8 METHOD_TYPE_SET_PROFILE_POSITION = 26;
constexpr uint8 METHOD_TYPE_GET_PROFILE_POSITION = 27;
constexpr uint8 METHOD_TYPE_SET_PROFILE_VELOCITY = 28;
constexpr uint8 METHOD_TYPE_GET_PROFILE_VELOCITY = 29;
constexpr uint8 METHOD_TYPE_SET_ENCODER_POSITION = 30;
constexpr uint8 METHOD_TYPE_GET_ENCODER_POSITION = 31;
constexpr uint8 METHOD_TYPE_SET_ENCODER_VELOCITY = 32;
constexpr uint8 METHOD_TYPE_GET_ENCODER_VELOCITY = 33;
constexpr uint8 METHOD_TYPE_SET_SOFTWARE_LIMIT = 34;
constexpr uint8 METHOD_TYPE_LOGIC_PROCESS = 101;

constexpr uint32 MAX_METHOD_INPUT_NUMBER = 20;

// 运动等待就位类型
constexpr uint8 INPLACE_WAIT_UNTILL_NONE = 0; // 不等待
constexpr uint8 INPLACE_WAIT_UNTILL_PROFILE_STOP = 1; // 等待规划位置停止
constexpr uint8 INPLACE_WAIT_UNTILL_DEFAULT_ERROR_SATIFIED = 2; // 等待默认误差带到位
constexpr uint8 INPLACE_WAIT_UNTILL_CUSTOMIZED_ERROR_SATIFIED = 3; // 等待自定义误差带到位

// 数据交互端口定义
constexpr uint16 DATAGATEWAY_SERVER_PORT = 40001;
constexpr uint16 INTERACT_SERVER_PORT = 40002;

// IO类型个数
constexpr uint8 MAX_IO_TYPE_NUMBER = 20;

// 设备类型个数
constexpr uint8 MAX_DEVICE_TYPE_NUBMER = 20;

// 系统用设备类型id定义
constexpr uint32 DEVICE_TYPE_ID_CYLINDER = 0xFFFFFFFF;

// 最大接收服务器个数
constexpr uint8 MAX_DATA_RECEIVER_NUMBER = 10;

// 运动方向定义
constexpr uint8 MOVE_DIRECTION_POSITIVE = 1; // 正方向运动
constexpr uint8 MOVE_DIRECTION_NEGATIVE = 2; // 负方向运动
constexpr uint8 CYLINDER_CTRL_MOVE_DIRECTION1 = MOVE_DIRECTION_POSITIVE;
constexpr uint8 CYLINDER_CTRL_MOVE_DIRECTION2 = MOVE_DIRECTION_NEGATIVE;

// 运动轴回原点模式
constexpr uint8 AXIS_HOMEMODE_NONE = 0; // 不用回原点
constexpr uint8 AXIS_HOMEMODE_CHECKSIGNAL_BY_POSITIVEMOVE_IF_NEGATIVELIMIT_ON = 1; // 轴先运动到负限位，然后向正方向查找原点信号， 当检测到原点信号时立即停止，当前位置为原点
constexpr uint8 AXIS_HOMEMODE_CHECKSIGNAL_BY_NEGATIVEMOVE_IF_POSITIVELIMIT_ON = 2; // 轴先运动到正限位，然后向负方向查找原点信号， 当检测到原点信号时立即停止，当前位置为原点
constexpr uint8 AXIS_HOMEMODE_CHECKSIGNAL_BY_ANTICLOCKWISEMOVE = 3; // 旋转轴向负方向（逆时针）查找原点信号，当检测到原点信号时 立即停止，当前位置为原点
constexpr uint8 AXIS_HOMEMODE_CHECKSIGNAL_BY_CLOCKWISEMOVE = 4; // 旋转轴向正方向（顺时针）查找原点信号，当检测到原点信号时 立即停止，当前位置为原点
constexpr uint8 AXIS_HOMEMODE_IF_POSITIVELIMIT_ON = 5; // 将该轴的正限位作为原点信号
constexpr uint8 AXIS_HOMEMODE_IF_NEGATIVELIMIT_ON = 6; // 将该轴的负限位作为原点信号

// 运动轴暂停处理模式
constexpr uint8 AXIS_PAUSEMODE_NONE = 0;					// 无暂停模式
constexpr uint8 AXIS_PAUSEMODE_WAITFOR_MOVES_COMPLETED = 1; // 等待该轴的运动指令执行完成后再停止；
constexpr uint8 AXIS_PAUSEMODE_SMOOTH_STOP_IMMEDIATELY = 2; // 该轴立即减速停止，重新启动后继续执行运动指令
constexpr uint8 AXIS_PAUSEMODE_URGENT_STOP_IMMEDIATELY = 3; // 该轴立即紧急停止，重新启动后继续执行运动指令

// 运动轴手动控制模式
constexpr uint8 AXIS_MANUALCTRL_HORIZONTAL_LEFTPOS_RIGHTNEG = 1; // 平移_左正右负
constexpr uint8 AXIS_MANUALCTRL_HORIZONTAL_LEFTNEG_RIGHTPOS = 2; // 平移_左负右正
constexpr uint8 AXIS_MANUALCTRL_VERTICAL_UPPOS_DOWNNEG = 3; // 平移_上正下负
constexpr uint8 AXIS_MANUALCTRL_VERTICAL_UPNEG_DOWNPOS = 4; // 平移_上负下正
constexpr uint8 AXIS_MANUALCTRL_ROTATE_CLOCKWISE_INCREASE = 5; // 旋转_顺时针加
constexpr uint8 AXIS_MANUALCTRL_ROTATE_CLOCKWISE_DECREASE = 6; // 旋转_顺时针减

// 电平捕捉类型
constexpr uint8 ELECTRIC_CAPTURE_RISING_EDGE = 1; // 上升沿触发
constexpr uint8 ELECTRIC_CAPTURE_FALLING_EDGE = 2; // 下降沿触发

// 限位类型
constexpr uint8 AXIS_LIMIT_TYPE_POSITIVE = 1; // 正限位
constexpr uint8 AXIS_LIMIT_TYPE_NEGATIVE = 2; // 负限位

// 回零查找方向
constexpr uint8 AXIS_HOME_CHECK_DIRECTION_POSITIVE = 1; // 正向
constexpr uint8 AXIS_HOME_CHECK_DIRECTION_NEGATIVE = 2; // 负向
constexpr uint8 AXIS_HOME_CHECK_DIRECTION_CLOCKWISE = AXIS_HOME_CHECK_DIRECTION_POSITIVE; // 顺时针
constexpr uint8 AXIS_HOME_CHECK_DIRECTION_ANTICLOCKWISE = AXIS_HOME_CHECK_DIRECTION_NEGATIVE; // 逆时针

// 脚本类型
constexpr uint8 SCRIPT_TYPE_VB_NET = 1;			// VB.NET
constexpr uint8 SCRIPT_TYPE_CSHARP_NET = 2;		// C#.NET
constexpr uint8 SCRIPT_TYPE_C_CPLUSPLUS = 3;	// C/C++

// 脚本执行方式
constexpr uint8 SCRIPT_EXECUTE_METHOD_ONCE = 0;	// 执行一次
constexpr uint8 SCRIPT_EXECUTE_METHOD_LOOP = 1;	// 循环执行
constexpr uint8 SCRIPT_EXECUTE_METHOD_TIMER = 2;// 定时执行

// 编译器类型
constexpr uint8 COMPILER_TYPE_VB_NET = SCRIPT_TYPE_VB_NET;			// VB.NET
constexpr uint8 COMPILER_TYPE_CSHARP_NET = SCRIPT_TYPE_CSHARP_NET;	// C#.NET
constexpr uint8 COMPILER_TYPE_C_CPLUSPLUS = SCRIPT_TYPE_C_CPLUSPLUS;// C/C++

// 目标CPU
constexpr uint8 TARGET_CPU_X86 = 1;				// X86
constexpr uint8 TARGET_CPU_X64 = 2;				// X64

#endif //__PLATFORM_H__

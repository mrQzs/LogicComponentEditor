using System;
using System.Text;
using System.Runtime.InteropServices;

namespace YudaoMotionApi
{
    // 接口包装类
    public class CMotionApi
    {
        // 字符常量
        public const String YD_MOTION_API_LIBRARY = "dependences/yd_motion_api.dll";   // API库名称

        // 接口错误代码定义
        public const Int32 YD_API_ERROR_SUCCESS = 0;                         // 成功
        public const Int32 YD_API_ERROR_FAILED = -1;                         // 失败
        public const Int32 YD_API_ERROR_NOT_INITIALIZED = -2;                // 未初始化
        public const Int32 YD_API_ERROR_NOT_FOUND = -3;                      // 不存在
        public const Int32 YD_API_ERROR_INVALID_INPUT = -4;                  // 输入参数无效
        public const Int32 YD_API_ERROR_DISMATCHED = -5;                     // 类型不匹配
        public const Int32 YD_API_ERROR_UNAUTHORIZED = -6;                   // 未授权
        public const Int32 YD_API_ERROR_OPERATION_FORBIDDEN = -7;            // 操作被禁止
        public const Int32 YD_API_ERROR_TIMEOUT = -8;                        // 超时
        public const Int32 YD_API_ERROR_OUTSIDE_RANGE = -9;                  // 越界
        public const Int32 YD_API_ERROR_MEMORY_OVERFLOW = -100;              // 内存溢出

        // 数值类型定义
        public const Byte YD_API_VALUE_TYPE_BOOL = 2;                       // 布尔型
        public const Byte YD_API_VALUE_TYPE_INT8 = 3;                       // 有符号8位整型
        public const Byte YD_API_VALUE_TYPE_UINT8 = 4;                      // 无符号8位整型
        public const Byte YD_API_VALUE_TYPE_INT16 = 5;                      // 有符号16位整型
        public const Byte YD_API_VALUE_TYPE_UINT16 = 6;                     // 无符号16位整型
        public const Byte YD_API_VALUE_TYPE_INT32 = 7;                      // 有符号32位整型
        public const Byte YD_API_VALUE_TYPE_UINT32 = 8;                     // 无符号32位整型
        public const Byte YD_API_VALUE_TYPE_INT64 = 9;                      // 有符号64位整型
        public const Byte YD_API_VALUE_TYPE_UINT64 = 10;                    // 无符号64位整型
        public const Byte YD_API_VALUE_TYPE_FLOAT = 11;                     // 单精度浮点型
        public const Byte YD_API_VALUE_TYPE_DOUBLE = 12;                    // 双精度浮点型
        public const Byte YD_API_VALUE_TYPE_STRING = 13;                    // 字符串
        public const Byte YD_API_VALUE_TYPE_MOTION_COORDS = 17;             // 运动坐标

        // 运动类型定义
        public const Byte YD_API_MOVE_TYPE_ABSOLUTE = 11;                   // 绝对运动
        public const Byte YD_API_MOVE_TYPE_RELATIVE = 12;                   // 相对运动
        public const Byte YD_API_MOVE_TYPE_JOG = 13;                        // Jog运动

        // 变量类型定义
        public const Byte YD_API_VARIABLE_TYPE_DI = 1;                      // DI变量，只读
        public const Byte YD_API_VARIABLE_TYPE_DO = 2;                      // DO变量，读/写
        public const Byte YD_API_VARIABLE_TYPE_AI = 3;                      // AI变量，只读
        public const Byte YD_API_VARIABLE_TYPE_AO = 4;                      // AO变量，读/写
        public const Byte YD_API_VARIABLE_TYPE_SYSTEM = 5;                  // 系统变量，只读
        public const Byte YD_API_VARIABLE_TYPE_MOTION = 6;                  // 运动变量，只读
        public const Byte YD_API_VARIABLE_TYPE_CYLINDER = 7;                // 气油缸变量，只读
        public const Byte YD_API_VARIABLE_TYPE_CONFIG = 8;                  // 配置变量，读/写
        public const Byte YD_API_VARIABLE_TYPE_VIRTUAL = 9;                 // 虚拟变量，读/写
        public const Byte YD_API_VARIABLE_TYPE_CONTROL = 10;                // 控制变量，读/写
        public const Byte YD_API_VARIABLE_TYPE_LOGIC = 11;                  // 逻辑变量，读/写
        public const Byte YD_API_VARIABLE_TYPE_SAFE = 12;                   // 安全变量，只读
		public const Byte YD_API_VARIABLE_TYPE_GLOBAL = 91;					// 全局变量，读/写
		public const Byte YD_API_VARIABLE_TYPE_RECIPE = 92;					// 配方变量，读/写
		public const Byte YD_API_VARIABLE_TYPE_LOCAL = 93;					// 临时变量，读/写

        // 运动方向定义
        public const Byte YD_API_MOVE_DIRECTION_POSITIVE = 1;               // 正方向运动
        public const Byte YD_API_MOVE_DIRECTION_NEGATIVE = 2;               // 负方向运动

        // DI类型定义
        public const Byte YD_API_DITYPE_GENERAL = 0;                        // 通用输入
        public const Byte YD_API_DITYPE_POSITIVE_LIMIT = 1;                 // 正限位
        public const Byte YD_API_DITYPE_NEGATIVE_LIMIT = 2;                 // 负限位
        public const Byte YD_API_DITYPE_DRIVER_ALARM = 3;                   // 驱动报警
        public const Byte YD_API_DITYPE_HOME_SIGNAL = 4;                    // 原点信号
        public const Byte YD_API_DITYPE_MOTOR_ARRIVE = 5;                   // 电机到位

        // DO类型定义
        public const Byte YD_API_DOTYPE_GENERAL = 0;                        // 通用输出
        public const Byte YD_API_DOTYPE_DRIVER_ENABLE = 1;                  // 驱动使能
        public const Byte YD_API_DOTYPE_ALARM_CLEAR = 2;                    // 报警清除

        // 控制器模式
        public const Byte YD_API_CONTROLLER_MODE_MANUAL = 0;                // 手动模式
        public const Byte YD_API_CONTROLLER_MODE_AUTOMATIC = 1;             // 自动模式

		// 轴回零状态
		public const Byte YD_API_AXIS_HOME_MOVE_NOT_EXECUTED = 0;			// 未回零
		public const Byte YD_API_AXIS_HOME_MOVE_IN_PROCESSING = 1;			// 回零中
		public const Byte YD_API_AXIS_HOME_MOVE_EXECUTED = 2;				// 已回零

        // 控制器状态
        public const Byte YD_API_CONTROLLER_STATUS_STOPED = 0;              // 已停止
        public const Byte YD_API_CONTROLLER_STATUS_RUNNING = 1;             // 运行中
        public const Byte YD_API_CONTROLLER_STATUS_SUSPENDED = 2;           // 已暂停
        public const Byte YD_API_CONTROLLER_STATUS_RESTORED = 3;            // 已恢复

        // 气油缸运动方向
        public const Byte YD_API_CYLINDER_MOVE_DIRECTION1 = 1;              // 方向一运动
        public const Byte YD_API_CYLINDER_MOVE_DIRECTION2 = 2;              // 方向二运动

        // 气油缸到位类型
        public const Byte YD_API_CYLINDER_DELAYED_ARRIVE = 1;               // 延时等待
        public const Byte YD_API_CYLINDER_DION_ARRIVE = 2;                  // DI有效到位
        public const Byte YD_API_CYLINDER_DION_DELAYED_ARRIVE = 3;          // DI有效+延时等待到位
        public const Byte YD_API_CYLINDER_AXIS_ENCODER_ARRIVE = 4;	        // 编码器到位
		
		// 运动轴回原点模式
		public const Byte YD_API_HOMEMODE_NONE = 0;												// 不用回原点
		public const Byte YD_API_HOMEMODE_CHECKSIGNAL_BY_POSITIVEMOVE_IF_NEGATIVELIMIT_ON = 1; 	// 轴先运动到负限位，然后向正方向查找原点信号，当检测到原点信号时立即停止，当前位置为原点
		public const Byte YD_API_HOMEMODE_CHECKSIGNAL_BY_NEGATIVEMOVE_IF_POSITIVELIMIT_ON = 2; 	// 轴先运动到正限位，然后向负方向查找原点信号，当检测到原点信号时立即停止，当前位置为原点
		public const Byte YD_API_HOMEMODE_CHECKSIGNAL_BY_ANTICLOCKWISEMOVE = 3;					// 旋转轴向负方向（逆时针）查找原点信号，当检测到原点信号时 立即停止，当前位置为原点
		public const Byte YD_API_HOMEMODE_CHECKSIGNAL_BY_CLOCKWISEMOVE = 4;						// 旋转轴向正方向（顺时针）查找原点信号，当检测到原点信号时 立即停止，当前位置为原点
		public const Byte YD_API_HOMEMODE_IF_POSITIVELIMIT_ON = 5;								// 将该轴的正限位作为原点信号
		public const Byte YD_API_HOMEMODE_IF_NEGATIVELIMIT_ON = 6;								// 将该轴的负限位作为原点信号
		
		// 电平捕捉类型
		public const Byte YD_API_ELECTRIC_CAPTURE_RISING_EDGE = 1; 								// 上升沿触发
		public const Byte YD_API_ELECTRIC_CAPTURE_FALLING_EDGE = 2; 							// 下降沿触发
		
		// 限位类型
		public const Byte YD_API_LIMIT_TYPE_POSITIVE = 1; 										// 正限位
		public const Byte YD_API_LIMIT_TYPE_NEGATIVE = 2; 										// 负限位
		
		// 回原点查找方向
		public const Byte YD_API_HOMECHECK_DIRECTION_POSITIVE = 1; 											// 正向
		public const Byte YD_API_HOMECHECK_DIRECTION_NEGATIVE = 2; 											// 负向
		public const Byte YD_API_HOMECHECK_DIRECTION_CLOCKWISE = YD_API_HOMECHECK_DIRECTION_POSITIVE; 		// 顺时针
		public const Byte YD_API_HOMECHECK_DIRECTION_ANTICLOCKWISE = YD_API_HOMECHECK_DIRECTION_NEGATIVE; 	// 逆时针
		
		// 跨语言函数结果
		public const Int32 YD_API_CROSS_RESULT_SUCCESS = 0;					// 成功
		public const Int32 YD_API_CROSS_RESULT_FAILED = -1;					// 失败
		public const Int32 YD_API_CROSS_RESULT_RETRY = 1;					// 重试

        // 最大数量定义
        public const Byte YD_MAX_MOTION_COORD_NUMBER = 32;                  // 运动坐标最大轴数
        public const Byte YD_MAX_NAME_LENGTH = 64;                          // 名称最大长度
        public const Byte YD_MAX_VALUE_LENGTH = 64;                         // 数值最大长度

        // 日志级别
        public const Byte YD_API_LOG_LEVEL_TRACE = 1;                       // 跟踪
        public const Byte YD_API_LOG_LEVEL_DEBUG = 2;                       // 调试
        public const Byte YD_API_LOG_LEVEL_INFO = 3;                        // 信息
        public const Byte YD_API_LOG_LEVEL_WARN = 4;                        // 警告
        public const Byte YD_API_LOG_LEVEL_ERROR = 5;                       // 错误
        public const Byte YD_API_LOG_LEVEL_CRITICAL = 6;			        // 致命

        // 项目信息
        [StructLayoutAttribute(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 8)]
        public struct YD_Project
        {
            public UInt32 version;                                          // 版本号
            [MarshalAsAttribute(UnmanagedType.ByValArray, SizeConst = YD_MAX_VALUE_LENGTH, ArraySubType = UnmanagedType.U1)]
            public Char[] name;                                             // 项目名称
            [MarshalAsAttribute(UnmanagedType.ByValArray, SizeConst = YD_MAX_VALUE_LENGTH, ArraySubType = UnmanagedType.U1)]
            public Char[] recipe;                                           // 配方名称
        }

        // 运动坐标
        [StructLayoutAttribute(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 8)]
        public struct YD_MotionCoords
        {
            [MarshalAsAttribute(UnmanagedType.ByValArray, SizeConst = YD_MAX_MOTION_COORD_NUMBER, ArraySubType = UnmanagedType.U2)]
            public UInt16[] cards;                                          // 卡编号数组 [0, N]
            [MarshalAsAttribute(UnmanagedType.ByValArray, SizeConst = YD_MAX_MOTION_COORD_NUMBER, ArraySubType = UnmanagedType.U2)]
            public UInt16[] axises;                                         // 轴序号数组 [1, M]
            [MarshalAsAttribute(UnmanagedType.ByValArray, SizeConst = YD_MAX_MOTION_COORD_NUMBER, ArraySubType = UnmanagedType.U1)]
            public Byte[] types;                                            // 运动类型数组
            [MarshalAsAttribute(UnmanagedType.ByValArray, SizeConst = YD_MAX_MOTION_COORD_NUMBER, ArraySubType = UnmanagedType.U1)]
            public Byte[] directions;                                       // 运动方向数组
            [MarshalAsAttribute(UnmanagedType.ByValArray, SizeConst = YD_MAX_MOTION_COORD_NUMBER, ArraySubType = UnmanagedType.R8)]
            public Double[] targets;                                        // 运动目标数组
            [MarshalAsAttribute(UnmanagedType.ByValArray, SizeConst = YD_MAX_MOTION_COORD_NUMBER, ArraySubType = UnmanagedType.R8)]
            public Double[] velocities;                                     // 运动速度数组
            public Byte number;                                             // 运动坐标个数
        }
        // 变量信息
        [StructLayoutAttribute(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 8)]
        public struct YD_VariableInfo
        {
            public UInt64 variable_id;                                       // 变量id
            [MarshalAsAttribute(UnmanagedType.ByValArray, SizeConst = YD_MAX_NAME_LENGTH, ArraySubType = UnmanagedType.U1)]
            public Char[] variable_name;                                    // 变量名称
            public Byte variable_type;                                      // 变量类型
            public Byte value_type;                                         // 数值类型
            [MarshalAsAttribute(UnmanagedType.ByValArray, SizeConst = YD_MAX_VALUE_LENGTH, ArraySubType = UnmanagedType.U1)]
            public Char[] max_value;                                        // 最大值
            [MarshalAsAttribute(UnmanagedType.ByValArray, SizeConst = YD_MAX_VALUE_LENGTH, ArraySubType = UnmanagedType.U1)]
            public Char[] min_value;                                        // 最小值
        }

        // IO信息
        [StructLayoutAttribute(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 8)]
        public struct YD_IOInfo
        {
            public UInt16 card;                                             // 卡编号 [0, N]
            public UInt16 type;                                             // 类型
            public UInt16 index;                                            // 序号
            [MarshalAsAttribute(UnmanagedType.ByValArray, SizeConst = YD_MAX_NAME_LENGTH, ArraySubType = UnmanagedType.U1)]
            public Char[] name;                                             // 名称
            [MarshalAsAttribute(UnmanagedType.ByValArray, SizeConst = YD_MAX_NAME_LENGTH, ArraySubType = UnmanagedType.U1)]
            public Char[] label;                                            // 标识
            public Byte enable;                                             // 是否使能
            public Byte reverse;                                            // 是否反转
        }

        // 运动轴信息
        [StructLayoutAttribute(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 8)]
        public struct YD_AxisInfo
        {
            public UInt16 card;                                             // 卡编号 [0, N]
            public UInt16 axis;                                             // 轴序号 [1, M]
            [MarshalAsAttribute(UnmanagedType.ByValArray, SizeConst = YD_MAX_NAME_LENGTH, ArraySubType = UnmanagedType.U1)]
            public Char[] name;                                             // 轴名称
            public Byte enable;                                             // 是否使能
            public Double equivalent;                                       // 脉冲当量
        }
		
		// 运动轴运动参数
        [StructLayoutAttribute(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 8)]
		public struct YD_AxisMoveConfig
		{
			public Double max_velocity;										// 最大速度
			public Double max_acceleration;									// 最大加速度
			public Double max_deceleration;									// 最大减速度
			public Double takeoff_velocity;									// 起跳速度
			public Double max_manual_velocity;								// 最大手动速度
			public Double smooth_stop_deceleration;							// 平停减速度
			public Double urgent_stop_deceleration;							// 急停减速度
			public UInt32 smooth_time;										// 平滑时间
			public Double smooth_factor;									// 平滑系数
			public Double arrive_error;										// 到位误差
			public UInt32 arrive_timeout;									// 到位超时
			public UInt32 stoped_delay;										// 停稳延时
		}
		
		// 运动轴限位参数
        [StructLayoutAttribute(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 8)]
		public struct YD_AxisLimitConfig
		{
			public Byte soft_limit_enable;									// 软限位启用
			public Double soft_positive_limit;								// 正向软限位
			public Double soft_negative_limit;								// 负向软限位
			public Byte hard_positive_limit_enable;							// 正向硬限位启用
			public Byte hard_negative_limit_enable;							// 负向硬限位启用
		}
		
		// 运动轴回原点参数
        [StructLayoutAttribute(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 8)]
		public struct YD_AxisHomeConfig
		{
			public Byte priority;											// 回原点优先级
			public Byte mode;												// 回原点模式
			public Double search_distance;									// 搜索距离
			public Double move_velocity;									// 移动速度
			public Double search_high_velocity;								// 搜索速度（高速）
			public Double search_low_velocity;								// 搜索速度（低速）
			public Double origin_offset;									// 原点偏移量
			public Byte capture_electric_level;								// 原点捕获电平选中
		}

        // 运动轴状态
        [StructLayoutAttribute(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 8)]
        public struct YD_AxisStates
        {
            public Byte driver_alarm;                                       // 驱动报警标志
            public Byte follow_error;                                       // 跟随误差标志
            public Byte positive_limit;                                     // 正向限位标志
            public Byte negative_limit;                                     // 负向限位标志
            public Byte smooth_stop;                                        // 平滑停止标志
            public Byte urgent_stop;                                        // 紧急停止标志
            public Byte servo_on;                                           // 伺服使能标志
            public Byte profile_move;                                       // 运动状态标志
            public Byte motor_arrive;                                       // 电机到位标志
            public Byte home_signal;                                        // 原点信号标志
            public Byte home_moved;                                         // 回零状态标志
            public UInt32 profile_mode;                                     // 运动模式
            public Double target_position;                                  // 目标位置
            public Double target_velocity;                                  // 目标速度
            public Double profile_position;                                 // 规划位置
            public Double profile_velocity;                                 // 规划速度
            public Double encoder_position;                                 // 编码器位置（反馈位置）
            public Double encoder_velocity;                                 // 编码器速度（反馈速度）
        }

        // 气油缸信息
        [StructLayoutAttribute(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 8)]
        public struct YD_CylinderInplace
        {
            public Byte inplace_type;                                       // 到位类型
            public UInt32 refer_di_device;                                  // 关联di所属设备id
            public UInt16 refer_di_type;                                    // 关联di类型
            public UInt16 refer_di_index;                                   // 关联di序号
            public UInt32 delay_time;                                       // 延迟时间：毫秒
            public UInt32 alarm_time;							            // 报警时间：毫秒
        }
        [StructLayoutAttribute(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 8)]
        public struct YD_CylinderCoil
        {
            public UInt32 refer_do_device;                                  // 关联do所属设备id
            public UInt16 refer_do_type;                                    // 关联do类型
            public UInt16 refer_do_index;                                   // 关联do序号
            public Byte refer_do_value;						                // 关联do动作值
        }
        [StructLayoutAttribute(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 8)]
        public struct YD_CylinderInfo
        {
            public UInt32 id;                                               // 气油缸id
            [MarshalAsAttribute(UnmanagedType.ByValArray, SizeConst = YD_MAX_NAME_LENGTH, ArraySubType = UnmanagedType.U1)]
            public Char[] name;                                             // 气油缸名称
            public Byte enable;                                             // 是否使能
            [MarshalAsAttribute(UnmanagedType.ByValArray, SizeConst = YD_MAX_NAME_LENGTH, ArraySubType = UnmanagedType.U1)]
            public Char[] direction1_name;                                  // 方向一名称
            public YD_CylinderInplace direction1_inplace;                   // 方向一到位参数
            public YD_CylinderCoil direction1_coil;					        // 方向一电磁阀
            [MarshalAsAttribute(UnmanagedType.ByValArray, SizeConst = YD_MAX_NAME_LENGTH, ArraySubType = UnmanagedType.U1)]
            public Char[] direction2_name;                                  // 方向二名称
            public YD_CylinderInplace direction2_inplace;                   // 方向二到位参数
            public YD_CylinderCoil direction2_coil;					        // 方向二电磁阀
        }

        // 气油缸状态
        [StructLayoutAttribute(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 8)]
        public struct YD_DirectionState
        {
            public Byte refer_di_state;                                     // 关联DI状态
            public Byte inplace_state;                                      // 到位状态
            public Byte alarm_state;						                // 报警状态
        }
        [StructLayoutAttribute(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 8)]
        public struct YD_CylinderStates
        {
            public YD_DirectionState direction1_state;                      // 方向一状态
            public YD_DirectionState direction2_state;					    // 方向二状态
        }

        /// <summary>
        /// 获取项目信息
        /// </summary>
        /// <param name="project"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_get_project_info", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_get_project_info(out YD_Project project);

        /// <summary>
        /// 获取模块名称
        /// </summary>
        /// <param name="buffer"></param>
        /// <param name="size"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_get_module_name", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_get_module_name(StringBuilder buffer, Int32 size);

        /// <summary>
        /// 输出日志
        /// </summary>
        /// <param name="level"></param>
        /// <param name="log"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_output_log", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_output_log(Byte level, String log);

        /// <summary>
        /// 初始化
        /// </summary>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_initialize", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_initialize();

        /// <summary>
        /// 反初始化
        /// </summary>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_uninitialize", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_uninitialize();

        /// <summary>
        /// 获取错误信息
        /// </summary>
        /// <param name="buffer"></param>
        /// <param name="size"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_get_error_msg", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_get_error_msg(StringBuilder buffer, Int32 size);

        /// <summary>
        /// 获取逻辑控制器状态
        /// </summary>
        /// <param name="status"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_get_controller_status", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_get_controller_status(out Byte status);

        /// <summary>
        /// 获取逻辑控制器模式
        /// </summary>
        /// <param name="mode"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_get_controller_mode", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_get_controller_mode(out Byte mode);

        /// <summary>
        /// 启动逻辑控制器
        /// </summary>
        /// <param name="timeout"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_start_controller", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_start_controller(UInt32 timeout = 3000);

        /// <summary>
        /// 停止逻辑控制器
        /// </summary>
        /// <param name="timeout"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_stop_controller", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_stop_controller(UInt32 timeout = 3000);

        /// <summary>
        /// 暂停逻辑控制器
        /// </summary>
        /// <param name="timeout"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_pause_controller", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_pause_controller(UInt32 timeout = 3000);

        /// <summary>
        /// 恢复逻辑控制器
        /// </summary>
        /// <param name="timeout"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_restore_controller", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_restore_controller(UInt32 timeout = 3000);

        /// <summary>
        /// 切换逻辑控制器手动模式
        /// </summary>
        /// <param name="timeout"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_switch_controller_to_manual_mode", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_switch_controller_to_manual_mode(UInt32 timeout = 3000);

        /// <summary>
        /// 切换逻辑控制器自动模式
        /// </summary>
        /// <param name="timeout"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_switch_controller_to_automatic_mode", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_switch_controller_to_automatic_mode(UInt32 timeout = 3000);

        /// <summary>
        /// 获取指定ID的变量
        /// </summary>
        /// <param name="id"></param>
        /// <param name="pVariableInfo"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_get_variable_by_id", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_get_variable_by_id(UInt64 id, out YD_VariableInfo pVariableInfo);

        /// <summary>
        /// 获取指定名称的变量
        /// </summary>
        /// <param name="name"></param>
        /// <param name="pVariableInfo"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_get_variable_by_name", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_get_variable_by_name(String name, out YD_VariableInfo pVariableInfo);

        /// <summary>
        /// 获取指定变量布尔数值
        /// </summary>
        /// <param name="id"></param>
        /// <param name="value"></param>
        /// <param name="timestamp"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_get_variable_boolean", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_get_variable_boolean(UInt64 id, out Boolean value, out UInt64 timestamp);

        /// <summary>
        /// 设置指定变量布尔数值
        /// </summary>
        /// <param name="id"></param>
        /// <param name="value"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_set_variable_boolean", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_set_variable_boolean(UInt64 id, Boolean value);

        /// <summary>
        /// 获取指定变量有符号8位整型数值
        /// </summary>
        /// <param name="id"></param>
        /// <param name="value"></param>
        /// <param name="timestamp"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_get_variable_int8", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_get_variable_int8(UInt64 id, out SByte value, out UInt64 timestamp);

        /// <summary>
        /// 设置指定变量有符号8位整型数值
        /// </summary>
        /// <param name="id"></param>
        /// <param name="value"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_set_variable_int8", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_set_variable_int8(UInt64 id, SByte value);

        /// <summary>
        /// 获取指定变量无符号8位整型数值
        /// </summary>
        /// <param name="id"></param>
        /// <param name="value"></param>
        /// <param name="timestamp"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_get_variable_uint8", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_get_variable_uint8(UInt64 id, out Byte value, out UInt64 timestamp);

        /// <summary>
        /// 设置指定变量无符号8位整型数值
        /// </summary>
        /// <param name="id"></param>
        /// <param name="value"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_set_variable_uint8", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_set_variable_uint8(UInt64 id, Byte value);

        /// <summary>
        /// 获取指定变量有符号16位整型数值
        /// </summary>
        /// <param name="id"></param>
        /// <param name="value"></param>
        /// <param name="timestamp"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_get_variable_int16", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_get_variable_int16(UInt64 id, out Int16 value, out UInt64 timestamp);

        /// <summary>
        /// 设置指定变量有符号16位整型数值
        /// </summary>
        /// <param name="id"></param>
        /// <param name="value"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_set_variable_int16", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_set_variable_int16(UInt64 id, Int16 value);

        /// <summary>
        /// 获取指定变量无符号16位整型数值
        /// </summary>
        /// <param name="id"></param>
        /// <param name="value"></param>
        /// <param name="timestamp"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_get_variable_uint16", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_get_variable_uint16(UInt64 id, out UInt16 value, out UInt64 timestamp);

        /// <summary>
        /// 设置指定变量无符号16位整型数值
        /// </summary>
        /// <param name="id"></param>
        /// <param name="value"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_set_variable_uint16", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_set_variable_uint16(UInt64 id, UInt16 value);

        /// <summary>
        /// 获取指定变量有符号32位整型数值
        /// </summary>
        /// <param name="id"></param>
        /// <param name="value"></param>
        /// <param name="timestamp"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_get_variable_int32", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_get_variable_int32(UInt64 id, out Int32 value, out UInt64 timestamp);

        /// <summary>
        /// 设置指定变量有符号32位整型数值
        /// </summary>
        /// <param name="id"></param>
        /// <param name="value"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_set_variable_int32", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_set_variable_int32(UInt64 id, Int32 value);

        /// <summary>
        /// 获取指定变量无符号32位整型数值
        /// </summary>
        /// <param name="id"></param>
        /// <param name="value"></param>
        /// <param name="timestamp"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_get_variable_uint32", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_get_variable_uint32(UInt64 id, out UInt32 value, out UInt64 timestamp);

        /// <summary>
        /// 设置指定变量无符号32位整型数值
        /// </summary>
        /// <param name="id"></param>
        /// <param name="value"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_set_variable_uint32", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_set_variable_uint32(UInt64 id, UInt32 value);

        /// <summary>
        /// 获取指定变量有符号64位整型数值
        /// </summary>
        /// <param name="id"></param>
        /// <param name="value"></param>
        /// <param name="timestamp"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_get_variable_int64", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_get_variable_int64(UInt64 id, out Int64 value, out UInt64 timestamp);

        /// <summary>
        /// 设置指定变量有符号64位整型数值
        /// </summary>
        /// <param name="id"></param>
        /// <param name="value"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_set_variable_int64", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_set_variable_int64(UInt64 id, Int64 value);

        /// <summary>
        /// 获取指定变量无符号64位整型数值
        /// </summary>
        /// <param name="id"></param>
        /// <param name="value"></param>
        /// <param name="timestamp"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_get_variable_uint64", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_get_variable_uint64(UInt64 id, out UInt64 value, out UInt64 timestamp);

        /// <summary>
        /// 设置指定变量无符号64位整型数值
        /// </summary>
        /// <param name="id"></param>
        /// <param name="value"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_set_variable_uint64", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_set_variable_uint64(UInt64 id, UInt64 value);

        /// <summary>
        /// 获取指定变量单精度浮点型数值
        /// </summary>
        /// <param name="id"></param>
        /// <param name="value"></param>
        /// <param name="timestamp"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_get_variable_float", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_get_variable_float(UInt64 id, out Single value, out UInt64 timestamp);

        /// <summary>
        /// 设置指定变量单精度浮点型数值
        /// </summary>
        /// <param name="id"></param>
        /// <param name="value"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_set_variable_float", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_set_variable_float(UInt64 id, Single value);

        /// <summary>
        /// 获取指定变量双精度浮点型数值
        /// </summary>
        /// <param name="id"></param>
        /// <param name="value"></param>
        /// <param name="timestamp"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_get_variable_double", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_get_variable_double(UInt64 id, out Double value, out UInt64 timestamp);

        /// <summary>
        /// 设置指定变量双精度浮点型数值
        /// </summary>
        /// <param name="id"></param>
        /// <param name="value"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_set_variable_double", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_set_variable_double(UInt64 id, Double value);

        /// <summary>
        /// 获取指定变量字符串数值
        /// </summary>
        /// <param name="id"></param>
        /// <param name="value"></param>
        /// <param name="size"></param>
        /// <param name="timestamp"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_get_variable_string", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_get_variable_string(UInt64 id, StringBuilder value, Int32 size, out UInt64 timestamp);

        /// <summary>
        /// 设置指定变量字符串数值
        /// </summary>
        /// <param name="id"></param>
        /// <param name="value"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_set_variable_string", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_set_variable_string(UInt64 id, String value);

        /// <summary>
        /// 获取指定变量运动坐标
        /// </summary>
        /// <param name="id"></param>
        /// <param name="pMotionCoords"></param>
        /// <param name="timestamp"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_get_variable_motion_coords", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_get_variable_motion_coords(UInt64 id, out YD_MotionCoords pMotionCoords, out UInt64 timestamp);

        /// <summary>
        /// 设置指定变量运动坐标
        /// </summary>
        /// <param name="id"></param>
        /// <param name="pMotionCoords"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_set_variable_motion_coords", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_set_variable_motion_coords(UInt64 id, ref YD_MotionCoords pMotionCoords);

        /// <summary>
        /// 获取指定id的DI输入
        /// </summary>
        /// <param name="card"></param>
        /// <param name="type"></param>
        /// <param name="index"></param>
        /// <param name="pDIInfo"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_get_digital_input_by_id", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_get_digital_input_by_id(UInt16 card, UInt16 type, UInt16 index, out YD_IOInfo pDIInfo);

        /// <summary>
        /// 获取指定名称的DI输入
        /// </summary>
        /// <param name="name"></param>
        /// <param name="pDIInfo"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_get_digital_input_by_name", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_get_digital_input_by_name(String name, out YD_IOInfo pDIInfo);

        /// <summary>
        /// 获取DI输入状态
        /// </summary>
        /// <param name="card"></param>
        /// <param name="type"></param>
        /// <param name="index"></param>
        /// <param name="value"></param>
        /// <param name="timestamp"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_get_digital_input_status", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_get_digital_input_status(UInt16 card, UInt16 type, UInt16 index, out Boolean value, out UInt64 timestamp);

        /// <summary>
        /// 获取指定id的DO输出
        /// </summary>
        /// <param name="card"></param>
        /// <param name="type"></param>
        /// <param name="index"></param>
        /// <param name="pDOInfo"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_get_digital_output_by_id", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_get_digital_output_by_id(UInt16 card, UInt16 type, UInt16 index, out YD_IOInfo pDOInfo);

        /// <summary>
        /// 获取指定名称的DO输出
        /// </summary>
        /// <param name="name"></param>
        /// <param name="pDOInfo"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_get_digital_output_by_name", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_get_digital_output_by_name(String name, out YD_IOInfo pDOInfo);

        /// <summary>
        /// 获取DO输出状态
        /// </summary>
        /// <param name="card"></param>
        /// <param name="type"></param>
        /// <param name="index"></param>
        /// <param name="value"></param>
        /// <param name="timestamp"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_get_digital_output_status", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_get_digital_output_status(UInt16 card, UInt16 type, UInt16 index, out Boolean value, out UInt64 timestamp);

        /// <summary>
        /// 控制DO输出
        /// </summary>
        /// <param name="card"></param>
        /// <param name="type"></param>
        /// <param name="index"></param>
        /// <param name="value"></param>
        /// <param name="timeout"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_set_digital_output_status", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_set_digital_output_status(UInt16 card, UInt16 type, UInt16 index, Boolean value, UInt32 timeout = 3000);

        /// <summary>
        /// 获取指定id的运动轴
        /// </summary>
        /// <param name="card"></param>
        /// <param name="axis"></param>
        /// <param name="pAxisInfo"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_get_axis_by_id", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_get_axis_by_id(UInt16 card, UInt16 axis, out YD_AxisInfo pAxisInfo);

        /// <summary>
        /// 获取指定名称的运动轴
        /// </summary>
        /// <param name="name"></param>
        /// <param name="pAxisInfo"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_get_axis_by_name", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_get_axis_by_name(String name, out YD_AxisInfo pAxisInfo);

        /// <summary>
        /// 指定轴打开使能
        /// </summary>
        /// <param name="card"></param>
        /// <param name="axis"></param>
        /// <param name="timeout"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_enable_axis", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_enable_axis(UInt16 card, UInt16 axis, UInt32 timeout = 3000);

        /// <summary>
        /// 指定轴关闭使能
        /// </summary>
        /// <param name="card"></param>
        /// <param name="axis"></param>
        /// <param name="timeout"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_disable_axis", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_disable_axis(UInt16 card, UInt16 axis, UInt32 timeout = 3000);

        /// <summary>
        /// 指定轴报警清除
        /// </summary>
        /// <param name="card"></param>
        /// <param name="axis"></param>
        /// <param name="timeout"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_clear_axis_alarm", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_clear_axis_alarm(UInt16 card, UInt16 axis, UInt32 timeout = 3000);

        /// <summary>
        /// 指定轴位置清零
        /// </summary>
        /// <param name="card"></param>
        /// <param name="axis"></param>
        /// <param name="timeout"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_zero_axis_position", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_zero_axis_position(UInt16 card, UInt16 axis, UInt32 timeout = 3000);

        /// <summary>
        /// 获取指定轴状态
        /// </summary>
        /// <param name="card"></param>
        /// <param name="axis"></param>
        /// <param name="pAxisStates"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_get_axis_states", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_get_axis_states(UInt16 card, UInt16 axis, out YD_AxisStates pAxisStates);

        /// <summary>
        /// 启动指定轴指定轴回零运动
        /// </summary>
        /// <param name="card"></param>
        /// <param name="axis"></param>
        /// <param name="timeout"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_start_axis_home_move", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_start_axis_home_move(UInt16 card, UInt16 axis, UInt32 timeout = 3000);

        /// <summary>
        /// 启动指定轴绝对运动
        /// </summary>
        /// <param name="card"></param>
        /// <param name="axis"></param>
        /// <param name="position"></param>
        /// <param name="velocity"></param>
        /// <param name="timeout"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_start_axis_absolute_move", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_start_axis_absolute_move(UInt16 card, UInt16 axis, Double position, Double velocity, UInt32 timeout = 3000);

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
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_start_axis_relative_move", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_start_axis_relative_move(UInt16 card, UInt16 axis, Double distance, Double velocity, Byte direction, UInt32 timeout = 3000);

        /// <summary>
        /// 启动指定轴Jog运动
        /// </summary>
        /// <param name="card"></param>
        /// <param name="axis"></param>
        /// <param name="velocity"></param>
        /// <param name="direction"></param>
        /// <param name="timeout"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_start_axis_jog_move", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_start_axis_jog_move(UInt16 card, UInt16 axis, Double velocity, Byte direction, UInt32 timeout = 3000);

        /// <summary>
        /// 启动多轴运动
        /// </summary>
        /// <param name="pMotionCoords"></param>
        /// <param name="timeout"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_start_multi_axis_moves", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_start_multi_axis_moves(ref YD_MotionCoords pMotionCoords, UInt32 timeout = 3000);

        /// <summary>
        /// 停止指定轴运动
        /// </summary>
        /// <param name="card"></param>
        /// <param name="axis"></param>
        /// <param name="urgent"></param>
        /// <param name="timeout"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_stop_axis_move", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_stop_axis_move(UInt16 card, UInt16 axis, Boolean urgent, UInt32 timeout = 3000);

        /// <summary>
        /// 获取指定轴驱动报警标志
        /// </summary>
        /// <param name="card"></param>
        /// <param name="axis"></param>
        /// <param name="flag"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_get_axis_driver_alarm_flag", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_get_axis_driver_alarm_flag(UInt16 card, UInt16 axis, out Boolean flag);

        /// <summary>
        /// 获取跟随误差标志
        /// </summary>
        /// <param name="card"></param>
        /// <param name="axis"></param>
        /// <param name="flag"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_get_axis_follow_error_flag", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_get_axis_follow_error_flag(UInt16 card, UInt16 axis, out Boolean flag);

        /// <summary>
        /// 获取正向限位标志
        /// </summary>
        /// <param name="card"></param>
        /// <param name="axis"></param>
        /// <param name="flag"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_get_axis_positive_limit_flag", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_get_axis_positive_limit_flag(UInt16 card, UInt16 axis, out Boolean flag);

        /// <summary>
        /// 获取负向限位标志
        /// </summary>
        /// <param name="card"></param>
        /// <param name="axis"></param>
        /// <param name="flag"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_get_axis_negative_limit_flag", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_get_axis_negative_limit_flag(UInt16 card, UInt16 axis, out Boolean flag);

        /// <summary>
        /// 获取平滑停止标志
        /// </summary>
        /// <param name="card"></param>
        /// <param name="axis"></param>
        /// <param name="flag"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_get_axis_smooth_stop_flag", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_get_axis_smooth_stop_flag(UInt16 card, UInt16 axis, out Boolean flag);

        /// <summary>
        /// 获取紧急停止标志
        /// </summary>
        /// <param name="card"></param>
        /// <param name="axis"></param>
        /// <param name="flag"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_get_axis_urgent_stop_flag", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_get_axis_urgent_stop_flag(UInt16 card, UInt16 axis, out Boolean flag);

        /// <summary>
        /// 获取伺服使能标志
        /// </summary>
        /// <param name="card"></param>
        /// <param name="axis"></param>
        /// <param name="flag"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_get_axis_servo_on_flag", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_get_axis_servo_on_flag(UInt16 card, UInt16 axis, out Boolean flag);

        /// <summary>
        /// 获取规划运动标志
        /// </summary>
        /// <param name="card"></param>
        /// <param name="axis"></param>
        /// <param name="flag"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_get_axis_profile_move_flag", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_get_axis_profile_move_flag(UInt16 card, UInt16 axis, out Boolean flag);

        /// <summary>
        /// 获取电机到位标志
        /// </summary>
        /// <param name="card"></param>
        /// <param name="axis"></param>
        /// <param name="flag"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_get_axis_motor_arrive_flag", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_get_axis_motor_arrive_flag(UInt16 card, UInt16 axis, out Boolean flag);

        /// <summary>
        /// 获取原点信号标志
        /// </summary>
        /// <param name="card"></param>
        /// <param name="axis"></param>
        /// <param name="flag"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_get_axis_home_signal_flag", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_get_axis_home_signal_flag(UInt16 card, UInt16 axis, out Boolean flag);

        /// <summary>
        /// 获取回零状态标志
        /// </summary>
        /// <param name="card"></param>
        /// <param name="axis"></param>
        /// <param name="flag"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_get_axis_home_moved_flag", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_get_axis_home_moved_flag(UInt16 card, UInt16 axis, out Boolean flag);

        /// <summary>
        /// 获取运动模式
        /// </summary>
        /// <param name="card"></param>
        /// <param name="axis"></param>
        /// <param name="mode"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_get_axis_profile_mode", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_get_axis_profile_mode(UInt16 card, UInt16 axis, out UInt32 mode);

        /// <summary>
        /// 获取目标位置
        /// </summary>
        /// <param name="card"></param>
        /// <param name="axis"></param>
        /// <param name="position"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_get_axis_target_position", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_get_axis_target_position(UInt16 card, UInt16 axis, out Double position);

        /// <summary>
        /// 获取目标速度
        /// </summary>
        /// <param name="card"></param>
        /// <param name="axis"></param>
        /// <param name="velocity"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_get_axis_target_velocity", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_get_axis_target_velocity(UInt16 card, UInt16 axis, out Double velocity);

        /// <summary>
        /// 获取规划位置
        /// </summary>
        /// <param name="card"></param>
        /// <param name="axis"></param>
        /// <param name="position"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_get_axis_profile_position", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_get_axis_profile_position(UInt16 card, UInt16 axis, out Double position);

        /// <summary>
        /// 获取规划速度
        /// </summary>
        /// <param name="card"></param>
        /// <param name="axis"></param>
        /// <param name="velocity"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_get_axis_profile_velocity", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_get_axis_profile_velocity(UInt16 card, UInt16 axis, out Double velocity);

        /// <summary>
        /// 获取编码器位置（反馈位置）
        /// </summary>
        /// <param name="card"></param>
        /// <param name="axis"></param>
        /// <param name="position"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_get_axis_encoder_position", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_get_axis_encoder_position(UInt16 card, UInt16 axis, out Double position);

        /// <summary>
        /// 获取编码器速度（反馈速度）
        /// </summary>
        /// <param name="card"></param>
        /// <param name="axis"></param>
        /// <param name="velocity"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_get_axis_encoder_velocity", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_get_axis_encoder_velocity(UInt16 card, UInt16 axis, out Double velocity);
		
		/// <summary>
		/// 获取回零状态
		/// </summary>
		/// <param name="card"></param>
		/// <param name="axis"></param>
		/// <param name="status"></param>
		/// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_get_axis_home_move_status", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_get_axis_home_move_status(UInt16 card, UInt16 axis, out Byte status);
		
		/// <summary>
		/// 更新回零状态
		/// </summary>
		/// <param name="card"></param>
		/// <param name="axis"></param>
		/// <param name="status"></param>
		/// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_set_axis_home_move_status", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_set_axis_home_move_status(UInt16 card, UInt16 axis, Byte status);

		/// <summary>
		/// 根据轴号获取运动参数
		/// </summary>
		/// <param name="card"></param>
		/// <param name="axis"></param>
		/// <param name="pMoveConfig"></param>
		/// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_get_axis_move_config_by_id", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
		public static extern Int32 yd_get_axis_move_config_by_id(UInt16 card, UInt16 axis, out YD_AxisMoveConfig pMoveConfig);

		/// <summary>
		/// 根据轴名称获取运动参数
		/// </summary>
		/// <param name="name"></param>
		/// <param name="pMoveConfig"></param>
		/// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_get_axis_move_config_by_name", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
		public static extern Int32 yd_get_axis_move_config_by_name(String name, out YD_AxisMoveConfig pMoveConfig);

		/// <summary>
		/// 根据轴号获取限位参数
		/// </summary>
		/// <param name="card"></param>
		/// <param name="axis"></param>
		/// <param name="pLimitConfig"></param>
		/// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_get_axis_limit_config_by_id", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
		public static extern Int32 yd_get_axis_limit_config_by_id(UInt16 card, UInt16 axis, out YD_AxisLimitConfig pLimitConfig);

		/// <summary>
		/// 根据轴名称获取限位参数
		/// </summary>
		/// <param name="name"></param>
		/// <param name="pLimitConfig"></param>
		/// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_get_axis_limit_config_by_name", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
		public static extern Int32 yd_get_axis_limit_config_by_name(String name, out YD_AxisLimitConfig pLimitConfig);
		
		/// <summary>
		/// 设置轴软限位
		/// </summary>
		/// <param name="card"></param>
		/// <param name="axis"></param>
		/// <param name="positive_limit"></param>
		/// <param name="negative_limit"></param>
		/// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_set_axis_soft_limit", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
		public static extern Int32 yd_set_axis_soft_limit(UInt16 card, UInt16 axis, Double positive_limit, Double negative_limit, UInt32 timeout = 3000);

		/// <summary>
		/// 根据轴号获取运动轴回原点参数
		/// </summary>
		/// <param name="card"></param>
		/// <param name="axis"></param>
		/// <param name="pHomeConfig"></param>
		/// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_get_axis_home_config_by_id", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
		public static extern Int32 yd_get_axis_home_config_by_id(UInt16 card, UInt16 axis, out YD_AxisHomeConfig pHomeConfig);

		/// <summary>
		/// 根据轴名称获取运动轴回原点参数
		/// </summary>
		/// <param name="name"></param>
		/// <param name="pHomeConfig"></param>
		/// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_get_axis_home_config_by_name", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
		public static extern Int32 yd_get_axis_home_config_by_name(String name, out YD_AxisHomeConfig pHomeConfig);

        /// <summary>
        /// 根据id获取气油缸信息
        /// </summary>
        /// <param name="id"></param>
        /// <param name="pCylinderInfo"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_get_cylinder_by_id", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_get_cylinder_by_id(UInt32 id, out YD_CylinderInfo pCylinderInfo);

        /// <summary>
        /// 根据名称获取气油缸信息
        /// </summary>
        /// <param name="name"></param>
        /// <param name="pCylinderInfo"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_get_cylinder_by_name", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_get_cylinder_by_name(String name, out YD_CylinderInfo pCylinderInfo);

        /// <summary>
        /// 获取气油缸状态
        /// </summary>
        /// <param name="id"></param>
        /// <param name="pCylinderStates"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_get_cylinder_states", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_get_cylinder_states(UInt32 id, out YD_CylinderStates pCylinderStates);

        /// <summary>
        /// 控制气油缸运动
        /// </summary>
        /// <param name="id"></param>
        /// <param name="direction"></param>
        /// <returns></returns>
        [DllImport(YD_MOTION_API_LIBRARY, EntryPoint = "yd_control_cylinder_move", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Int32 yd_control_cylinder_move(UInt32 id, Byte direction, UInt32 timeout = 3000);
    }

    // 控制器
    public static class YDController
    {
		// 成员变量
		private static StringBuilder m_sbufLastError = new StringBuilder(200);
		// 获取错误信息
		public static String GetLastError()
		{
			return m_sbufLastError.ToString();
		}
        // 获取状态
        public static Byte GetStatus()
        {
            Byte ucStatus = 0;
            if (CMotionApi.YD_API_ERROR_SUCCESS != CMotionApi.yd_get_controller_status(out ucStatus))
            {
				CMotionApi.yd_get_error_msg(m_sbufLastError, 200);
            }
            return ucStatus;
        }

        // 获取模式
        public static Byte GetMode()
        {
            Byte ucMode = 0;
            if (CMotionApi.YD_API_ERROR_SUCCESS != CMotionApi.yd_get_controller_mode(out ucMode))
            {
				CMotionApi.yd_get_error_msg(m_sbufLastError, 200);
            }
            return ucMode;
        }

        // 启动
        public static Boolean Start(UInt32 uiTimeout = 3000)
        {
            if (CMotionApi.YD_API_ERROR_SUCCESS != CMotionApi.yd_start_controller(uiTimeout))
            {
				CMotionApi.yd_get_error_msg(m_sbufLastError, 200);
                return false;
            }
            return true;
        }

        // 停止
        public static Boolean Terminate(UInt32 uiTimeout = 3000)
        {
            if (CMotionApi.YD_API_ERROR_SUCCESS != CMotionApi.yd_stop_controller(uiTimeout))
            {
				CMotionApi.yd_get_error_msg(m_sbufLastError, 200);
                return false;
            }
            return true;
        }

        // 暂停
        public static Boolean Pause(UInt32 uiTimeout = 3000)
        {
            if (CMotionApi.YD_API_ERROR_SUCCESS != CMotionApi.yd_pause_controller(uiTimeout))
            {
				CMotionApi.yd_get_error_msg(m_sbufLastError, 200);
                return false;
            }
            return true;
        }

        // 恢复
        public static Boolean Restore(UInt32 uiTimeout = 3000)
        {
            if (CMotionApi.YD_API_ERROR_SUCCESS != CMotionApi.yd_restore_controller(uiTimeout))
            {
				CMotionApi.yd_get_error_msg(m_sbufLastError, 200);
                return false;
            }
            return true;
        }

        // 切换手动模式
        public static Boolean SwitchManualMode(UInt32 uiTimeout = 3000)
        {
            if (CMotionApi.YD_API_ERROR_SUCCESS != CMotionApi.yd_switch_controller_to_manual_mode(uiTimeout))
            {
				CMotionApi.yd_get_error_msg(m_sbufLastError, 200);
                return false;
            }
            return true;
        }

        // 切换自动模式
        public static Boolean SwitchAutomaticMode(UInt32 uiTimeout = 3000)
        {
            if (CMotionApi.YD_API_ERROR_SUCCESS != CMotionApi.yd_switch_controller_to_automatic_mode(uiTimeout))
            {
				CMotionApi.yd_get_error_msg(m_sbufLastError, 200);
                return false;
            }
            return true;
        }
    }

    // 只读变量类
    public class YDROVariable<T>
    {
        // 成员变量
        private UInt64 m_ullId = 0;
        private String m_strName = "";
        private T m_maxValue;
        private T m_minValue;
        private Byte m_ucValueType = 0;
        private UInt64 m_ullTimestamp = 0;
		private StringBuilder m_sbufLastError = new StringBuilder(200);
        // 带参数构造函数
        public YDROVariable(UInt64 ullId, String strName, T maxValue, T minValue)
        {
            this.m_ullId = ullId;
            this.m_strName = strName;
            this.m_maxValue = maxValue;
            this.m_minValue = minValue;
            if (typeof(System.Boolean) == typeof(T))
            {
                this.m_ucValueType = CMotionApi.YD_API_VALUE_TYPE_BOOL;
            }
            else if (typeof(System.Byte) == typeof(T))
            {
                this.m_ucValueType = CMotionApi.YD_API_VALUE_TYPE_UINT8;
            }
            else if (typeof(System.SByte) == typeof(T))
            {
                this.m_ucValueType = CMotionApi.YD_API_VALUE_TYPE_INT8;
            }
            else if (typeof(System.UInt16) == typeof(T))
            {
                this.m_ucValueType = CMotionApi.YD_API_VALUE_TYPE_UINT16;
            }
            else if (typeof(System.Int16) == typeof(T))
            {
                this.m_ucValueType = CMotionApi.YD_API_VALUE_TYPE_INT16;
            }
            else if (typeof(System.UInt32) == typeof(T))
            {
                this.m_ucValueType = CMotionApi.YD_API_VALUE_TYPE_UINT32;
            }
            else if (typeof(System.Int32) == typeof(T))
            {
                this.m_ucValueType = CMotionApi.YD_API_VALUE_TYPE_INT32;
            }
            else if (typeof(System.UInt64) == typeof(T))
            {
                this.m_ucValueType = CMotionApi.YD_API_VALUE_TYPE_UINT64;
            }
            else if (typeof(System.Int64) == typeof(T))
            {
                this.m_ucValueType = CMotionApi.YD_API_VALUE_TYPE_INT64;
            }
            else if (typeof(System.Single) == typeof(T))
            {
                this.m_ucValueType = CMotionApi.YD_API_VALUE_TYPE_FLOAT;
            }
            else if (typeof(System.Double) == typeof(T))
            {
                this.m_ucValueType = CMotionApi.YD_API_VALUE_TYPE_DOUBLE;
            }
            else if (typeof(System.String) == typeof(T))
            {
                this.m_ucValueType = CMotionApi.YD_API_VALUE_TYPE_STRING;
            }
            else if (typeof(CMotionApi.YD_MotionCoords) == typeof(T))
            {
                this.m_ucValueType = CMotionApi.YD_API_VALUE_TYPE_MOTION_COORDS;
            }
        }
        public YDROVariable(UInt64 ullId, String strName, Byte ucValueType)
        {
            this.m_ullId = ullId;
            this.m_strName = strName;
            this.m_ucValueType = ucValueType;
        }
		// 获取错误信息
		public String GetLastError()
		{
			return this.m_sbufLastError.ToString();
		}
        // 获取数值类型
        public Byte GetValueType()
        {
            return this.m_ucValueType;
        }
        // 获取数值
        public T GetValue()
        {
            if (CMotionApi.YD_API_VALUE_TYPE_BOOL == this.m_ucValueType)
            {
                Boolean bValue = false;
                if (CMotionApi.YD_API_ERROR_SUCCESS != CMotionApi.yd_get_variable_boolean(
                    this.m_ullId,
                    out bValue,
                    out this.m_ullTimestamp))
                {
					CMotionApi.yd_get_error_msg(this.m_sbufLastError, 200);
                }
                return (T)(Object)bValue;
            }
            else if (CMotionApi.YD_API_VALUE_TYPE_UINT8 == this.m_ucValueType)
            {
                Byte ucValue = 0;
                if (CMotionApi.YD_API_ERROR_SUCCESS != CMotionApi.yd_get_variable_uint8(
                    this.m_ullId,
                    out ucValue,
                    out this.m_ullTimestamp))
                {
					CMotionApi.yd_get_error_msg(this.m_sbufLastError, 200);
                }
                return (T)(Object)ucValue;
            }
            else if (CMotionApi.YD_API_VALUE_TYPE_INT8 == this.m_ucValueType)
            {
                SByte cValue = 0;
                if (CMotionApi.YD_API_ERROR_SUCCESS != CMotionApi.yd_get_variable_int8(
                    this.m_ullId,
                    out cValue,
                    out this.m_ullTimestamp))
                {
					CMotionApi.yd_get_error_msg(this.m_sbufLastError, 200);
                }
                return (T)(Object)cValue;
            }
            else if (CMotionApi.YD_API_VALUE_TYPE_UINT16 == this.m_ucValueType)
            {
                UInt16 usValue = 0;
                if (CMotionApi.YD_API_ERROR_SUCCESS != CMotionApi.yd_get_variable_uint16(
                    this.m_ullId,
                    out usValue,
                    out this.m_ullTimestamp))
                {
					CMotionApi.yd_get_error_msg(this.m_sbufLastError, 200);
                }
                return (T)(Object)usValue;
            }
            else if (CMotionApi.YD_API_VALUE_TYPE_INT16 == this.m_ucValueType)
            {
                Int16 sValue = 0;
                if (CMotionApi.YD_API_ERROR_SUCCESS != CMotionApi.yd_get_variable_int16(
                    this.m_ullId,
                    out sValue,
                    out this.m_ullTimestamp))
                {
					CMotionApi.yd_get_error_msg(this.m_sbufLastError, 200);
                }
                return (T)(Object)sValue;
            }
            else if (CMotionApi.YD_API_VALUE_TYPE_UINT32 == this.m_ucValueType)
            {
                UInt32 uiValue = 0;
                if (CMotionApi.YD_API_ERROR_SUCCESS != CMotionApi.yd_get_variable_uint32(
                    this.m_ullId,
                    out uiValue,
                    out this.m_ullTimestamp))
                {
					CMotionApi.yd_get_error_msg(this.m_sbufLastError, 200);
                }
                return (T)(Object)uiValue;
            }
            else if (CMotionApi.YD_API_VALUE_TYPE_INT32 == this.m_ucValueType)
            {
                Int32 iValue = 0;
                if (CMotionApi.YD_API_ERROR_SUCCESS != CMotionApi.yd_get_variable_int32(
                    this.m_ullId,
                    out iValue,
                    out this.m_ullTimestamp))
                {
					CMotionApi.yd_get_error_msg(this.m_sbufLastError, 200);
                }
                return (T)(Object)iValue;
            }
            else if (CMotionApi.YD_API_VALUE_TYPE_UINT64 == this.m_ucValueType)
            {
                UInt64 ullValue = 0;
                if (CMotionApi.YD_API_ERROR_SUCCESS != CMotionApi.yd_get_variable_uint64(
                    this.m_ullId,
                    out ullValue,
                    out this.m_ullTimestamp))
                {
					CMotionApi.yd_get_error_msg(this.m_sbufLastError, 200);
                }
                return (T)(Object)ullValue;
            }
            else if (CMotionApi.YD_API_VALUE_TYPE_INT64 == this.m_ucValueType)
            {
                Int64 llValue = 0;
                if (CMotionApi.YD_API_ERROR_SUCCESS != CMotionApi.yd_get_variable_int64(
                    this.m_ullId,
                    out llValue,
                    out this.m_ullTimestamp))
                {
					CMotionApi.yd_get_error_msg(this.m_sbufLastError, 200);
                }
                return (T)(Object)llValue;
            }
            else if (CMotionApi.YD_API_VALUE_TYPE_FLOAT == this.m_ucValueType)
            {
                Single fValue = 0;
                if (CMotionApi.YD_API_ERROR_SUCCESS != CMotionApi.yd_get_variable_float(
                    this.m_ullId,
                    out fValue,
                    out this.m_ullTimestamp))
                {
					CMotionApi.yd_get_error_msg(this.m_sbufLastError, 200);
                }
                return (T)(Object)fValue;
            }
            else if (CMotionApi.YD_API_VALUE_TYPE_DOUBLE == this.m_ucValueType)
            {
                Double dblValue = 0;
                if (CMotionApi.YD_API_ERROR_SUCCESS != CMotionApi.yd_get_variable_double(
                    this.m_ullId,
                    out dblValue,
                    out this.m_ullTimestamp))
                {
					CMotionApi.yd_get_error_msg(this.m_sbufLastError, 200);
                }
                return (T)(Object)dblValue;
            }
            else if (CMotionApi.YD_API_VALUE_TYPE_STRING == this.m_ucValueType)
            {
                StringBuilder strValue = new StringBuilder(CMotionApi.YD_MAX_VALUE_LENGTH);
                if (CMotionApi.YD_API_ERROR_SUCCESS != CMotionApi.yd_get_variable_string(
                    this.m_ullId,
                    strValue,
                    CMotionApi.YD_MAX_VALUE_LENGTH,
                    out this.m_ullTimestamp))
                {
					CMotionApi.yd_get_error_msg(this.m_sbufLastError, 200);
                }
                return (T)(Object)strValue.ToString();
            }
            else if (CMotionApi.YD_API_VALUE_TYPE_MOTION_COORDS == this.m_ucValueType)
            {
                CMotionApi.YD_MotionCoords coordValue = new CMotionApi.YD_MotionCoords();
                if (CMotionApi.YD_API_ERROR_SUCCESS != CMotionApi.yd_get_variable_motion_coords(
                    this.m_ullId,
                    out coordValue,
                    out this.m_ullTimestamp))
                {
					CMotionApi.yd_get_error_msg(this.m_sbufLastError, 200);
                }
                return (T)(Object)coordValue;
            }
            else
            {
                return (T)(Object)(Byte)0;
            }
        }
    }
	
	// 可读可写变量类
    public class YDRWVariable<T>
    {
        // 成员变量
        private UInt64 m_ullId = 0;
        private String m_strName = "";
        private T m_maxValue;
        private T m_minValue;
        private Byte m_ucValueType = 0;
        private UInt64 m_ullTimestamp = 0;
		private StringBuilder m_sbufLastError = new StringBuilder(200);
        // 带参数构造函数
        public YDRWVariable(UInt64 ullId, String strName, T maxValue, T minValue)
        {
            this.m_ullId = ullId;
            this.m_strName = strName;
            this.m_maxValue = maxValue;
            this.m_minValue = minValue;
            if (typeof(System.Boolean) == typeof(T))
            {
                this.m_ucValueType = CMotionApi.YD_API_VALUE_TYPE_BOOL;
            }
            else if (typeof(System.Byte) == typeof(T))
            {
                this.m_ucValueType = CMotionApi.YD_API_VALUE_TYPE_UINT8;
            }
            else if (typeof(System.SByte) == typeof(T))
            {
                this.m_ucValueType = CMotionApi.YD_API_VALUE_TYPE_INT8;
            }
            else if (typeof(System.UInt16) == typeof(T))
            {
                this.m_ucValueType = CMotionApi.YD_API_VALUE_TYPE_UINT16;
            }
            else if (typeof(System.Int16) == typeof(T))
            {
                this.m_ucValueType = CMotionApi.YD_API_VALUE_TYPE_INT16;
            }
            else if (typeof(System.UInt32) == typeof(T))
            {
                this.m_ucValueType = CMotionApi.YD_API_VALUE_TYPE_UINT32;
            }
            else if (typeof(System.Int32) == typeof(T))
            {
                this.m_ucValueType = CMotionApi.YD_API_VALUE_TYPE_INT32;
            }
            else if (typeof(System.UInt64) == typeof(T))
            {
                this.m_ucValueType = CMotionApi.YD_API_VALUE_TYPE_UINT64;
            }
            else if (typeof(System.Int64) == typeof(T))
            {
                this.m_ucValueType = CMotionApi.YD_API_VALUE_TYPE_INT64;
            }
            else if (typeof(System.Single) == typeof(T))
            {
                this.m_ucValueType = CMotionApi.YD_API_VALUE_TYPE_FLOAT;
            }
            else if (typeof(System.Double) == typeof(T))
            {
                this.m_ucValueType = CMotionApi.YD_API_VALUE_TYPE_DOUBLE;
            }
            else if (typeof(System.String) == typeof(T))
            {
                this.m_ucValueType = CMotionApi.YD_API_VALUE_TYPE_STRING;
            }
            else if (typeof(CMotionApi.YD_MotionCoords) == typeof(T))
            {
                this.m_ucValueType = CMotionApi.YD_API_VALUE_TYPE_MOTION_COORDS;
            }
        }
        public YDRWVariable(UInt64 ullId, String strName, Byte ucValueType)
        {
            this.m_ullId = ullId;
            this.m_strName = strName;
            this.m_ucValueType = ucValueType;
        }
		// 获取错误信息
		public String GetLastError()
		{
			return this.m_sbufLastError.ToString();
		}
        // 获取数值类型
        public Byte GetValueType()
        {
            return this.m_ucValueType;
        }
        // 最大值
        public T GetMaxValue()
        {
            return this.m_maxValue;
        }
        // 最小值
        public T GetMinValue()
        {
            return this.m_minValue;
        }
        // 获取数值
        public T GetValue()
        {
            if (CMotionApi.YD_API_VALUE_TYPE_BOOL == this.m_ucValueType)
            {
                Boolean bValue = false;
                if (CMotionApi.YD_API_ERROR_SUCCESS != CMotionApi.yd_get_variable_boolean(
                    this.m_ullId,
                    out bValue,
                    out this.m_ullTimestamp))
                {
					CMotionApi.yd_get_error_msg(this.m_sbufLastError, 200);
                }
                return (T)(Object)bValue;
            }
            else if (CMotionApi.YD_API_VALUE_TYPE_UINT8 == this.m_ucValueType)
            {
                Byte ucValue = 0;
                if (CMotionApi.YD_API_ERROR_SUCCESS != CMotionApi.yd_get_variable_uint8(
                    this.m_ullId,
                    out ucValue,
                    out this.m_ullTimestamp))
                {
					CMotionApi.yd_get_error_msg(this.m_sbufLastError, 200);
                }
                return (T)(Object)ucValue;
            }
            else if (CMotionApi.YD_API_VALUE_TYPE_INT8 == this.m_ucValueType)
            {
                SByte cValue = 0;
                if (CMotionApi.YD_API_ERROR_SUCCESS != CMotionApi.yd_get_variable_int8(
                    this.m_ullId,
                    out cValue,
                    out this.m_ullTimestamp))
                {
					CMotionApi.yd_get_error_msg(this.m_sbufLastError, 200);
                }
                return (T)(Object)cValue;
            }
            else if (CMotionApi.YD_API_VALUE_TYPE_UINT16 == this.m_ucValueType)
            {
                UInt16 usValue = 0;
                if (CMotionApi.YD_API_ERROR_SUCCESS != CMotionApi.yd_get_variable_uint16(
                    this.m_ullId,
                    out usValue,
                    out this.m_ullTimestamp))
                {
					CMotionApi.yd_get_error_msg(this.m_sbufLastError, 200);
                }
                return (T)(Object)usValue;
            }
            else if (CMotionApi.YD_API_VALUE_TYPE_INT16 == this.m_ucValueType)
            {
                Int16 sValue = 0;
                if (CMotionApi.YD_API_ERROR_SUCCESS != CMotionApi.yd_get_variable_int16(
                    this.m_ullId,
                    out sValue,
                    out this.m_ullTimestamp))
                {
					CMotionApi.yd_get_error_msg(this.m_sbufLastError, 200);
                }
                return (T)(Object)sValue;
            }
            else if (CMotionApi.YD_API_VALUE_TYPE_UINT32 == this.m_ucValueType)
            {
                UInt32 uiValue = 0;
                if (CMotionApi.YD_API_ERROR_SUCCESS != CMotionApi.yd_get_variable_uint32(
                    this.m_ullId,
                    out uiValue,
                    out this.m_ullTimestamp))
                {
					CMotionApi.yd_get_error_msg(this.m_sbufLastError, 200);
                }
                return (T)(Object)uiValue;
            }
            else if (CMotionApi.YD_API_VALUE_TYPE_INT32 == this.m_ucValueType)
            {
                Int32 iValue = 0;
                if (CMotionApi.YD_API_ERROR_SUCCESS != CMotionApi.yd_get_variable_int32(
                    this.m_ullId,
                    out iValue,
                    out this.m_ullTimestamp))
                {
					CMotionApi.yd_get_error_msg(this.m_sbufLastError, 200);
                }
                return (T)(Object)iValue;
            }
            else if (CMotionApi.YD_API_VALUE_TYPE_UINT64 == this.m_ucValueType)
            {
                UInt64 ullValue = 0;
                if (CMotionApi.YD_API_ERROR_SUCCESS != CMotionApi.yd_get_variable_uint64(
                    this.m_ullId,
                    out ullValue,
                    out this.m_ullTimestamp))
                {
					CMotionApi.yd_get_error_msg(this.m_sbufLastError, 200);
                }
                return (T)(Object)ullValue;
            }
            else if (CMotionApi.YD_API_VALUE_TYPE_INT64 == this.m_ucValueType)
            {
                Int64 llValue = 0;
                if (CMotionApi.YD_API_ERROR_SUCCESS != CMotionApi.yd_get_variable_int64(
                    this.m_ullId,
                    out llValue,
                    out this.m_ullTimestamp))
                {
					CMotionApi.yd_get_error_msg(this.m_sbufLastError, 200);
                }
                return (T)(Object)llValue;
            }
            else if (CMotionApi.YD_API_VALUE_TYPE_FLOAT == this.m_ucValueType)
            {
                Single fValue = 0;
                if (CMotionApi.YD_API_ERROR_SUCCESS != CMotionApi.yd_get_variable_float(
                    this.m_ullId,
                    out fValue,
                    out this.m_ullTimestamp))
                {
					CMotionApi.yd_get_error_msg(this.m_sbufLastError, 200);
                }
                return (T)(Object)fValue;
            }
            else if (CMotionApi.YD_API_VALUE_TYPE_DOUBLE == this.m_ucValueType)
            {
                Double dblValue = 0;
                if (CMotionApi.YD_API_ERROR_SUCCESS != CMotionApi.yd_get_variable_double(
                    this.m_ullId,
                    out dblValue,
                    out this.m_ullTimestamp))
                {
					CMotionApi.yd_get_error_msg(this.m_sbufLastError, 200);
                }
                return (T)(Object)dblValue;
            }
            else if (CMotionApi.YD_API_VALUE_TYPE_STRING == this.m_ucValueType)
            {
                StringBuilder strValue = new StringBuilder(CMotionApi.YD_MAX_VALUE_LENGTH);
                if (CMotionApi.YD_API_ERROR_SUCCESS != CMotionApi.yd_get_variable_string(
                    this.m_ullId,
                    strValue,
                    CMotionApi.YD_MAX_VALUE_LENGTH,
                    out this.m_ullTimestamp))
                {
					CMotionApi.yd_get_error_msg(this.m_sbufLastError, 200);
                }
                return (T)(Object)strValue.ToString();
            }
            else if (CMotionApi.YD_API_VALUE_TYPE_MOTION_COORDS == this.m_ucValueType)
            {
                CMotionApi.YD_MotionCoords coordValue = new CMotionApi.YD_MotionCoords();
                if (CMotionApi.YD_API_ERROR_SUCCESS != CMotionApi.yd_get_variable_motion_coords(
                    this.m_ullId,
                    out coordValue,
                    out this.m_ullTimestamp))
                {
					CMotionApi.yd_get_error_msg(this.m_sbufLastError, 200);
                }
                return (T)(Object)coordValue;
            }
            else
            {
                return (T)(Object)(Byte)0;
            }
        }
        // 更新数值
        public Boolean SetValue(T value)
        {
            if (CMotionApi.YD_API_VALUE_TYPE_BOOL == this.m_ucValueType)
            {
                if (CMotionApi.YD_API_ERROR_SUCCESS != CMotionApi.yd_set_variable_boolean(
                    this.m_ullId,
                    (Boolean)(Object)value))
                {
					CMotionApi.yd_get_error_msg(this.m_sbufLastError, 200);
                    return false;
                }
                return true;
            }
            else if (CMotionApi.YD_API_VALUE_TYPE_UINT8 == this.m_ucValueType)
            {
                if (CMotionApi.YD_API_ERROR_SUCCESS != CMotionApi.yd_set_variable_uint8(
                    this.m_ullId,
                    (Byte)(Object)value))
                {
					CMotionApi.yd_get_error_msg(this.m_sbufLastError, 200);
                    return false;
                }
                return true;
            }
            else if (CMotionApi.YD_API_VALUE_TYPE_INT8 == this.m_ucValueType)
            {
                if (CMotionApi.YD_API_ERROR_SUCCESS != CMotionApi.yd_set_variable_int8(
                    this.m_ullId,
                    (SByte)(Object)value))
                {
					CMotionApi.yd_get_error_msg(this.m_sbufLastError, 200);
                    return false;
                }
                return true;
            }
            else if (CMotionApi.YD_API_VALUE_TYPE_UINT16 == this.m_ucValueType)
            {
                if (CMotionApi.YD_API_ERROR_SUCCESS != CMotionApi.yd_set_variable_uint16(
                    this.m_ullId,
                    (UInt16)(Object)value))
                {
					CMotionApi.yd_get_error_msg(this.m_sbufLastError, 200);
                    return false;
                }
                return true;
            }
            else if (CMotionApi.YD_API_VALUE_TYPE_INT16 == this.m_ucValueType)
            {
                if (CMotionApi.YD_API_ERROR_SUCCESS != CMotionApi.yd_set_variable_int16(
                    this.m_ullId,
                    (Int16)(Object)value))
                {
					CMotionApi.yd_get_error_msg(this.m_sbufLastError, 200);
                    return false;
                }
                return true;
            }
            else if (CMotionApi.YD_API_VALUE_TYPE_UINT32 == this.m_ucValueType)
            {
                if (CMotionApi.YD_API_ERROR_SUCCESS != CMotionApi.yd_set_variable_uint32(
                    this.m_ullId,
                    (UInt32)(Object)value))
                {
					CMotionApi.yd_get_error_msg(this.m_sbufLastError, 200);
                    return false;
                }
                return true;
            }
            else if (CMotionApi.YD_API_VALUE_TYPE_INT32 == this.m_ucValueType)
            {
                if (CMotionApi.YD_API_ERROR_SUCCESS != CMotionApi.yd_set_variable_int32(
                    this.m_ullId,
                    (Int32)(Object)value))
                {
					CMotionApi.yd_get_error_msg(this.m_sbufLastError, 200);
                    return false;
                }
                return true;
            }
            else if (CMotionApi.YD_API_VALUE_TYPE_UINT64 == this.m_ucValueType)
            {
                if (CMotionApi.YD_API_ERROR_SUCCESS != CMotionApi.yd_set_variable_uint64(
                    this.m_ullId,
                    (UInt64)(Object)value))
                {
					CMotionApi.yd_get_error_msg(this.m_sbufLastError, 200);
                    return false;
                }
                return true;
            }
            else if (CMotionApi.YD_API_VALUE_TYPE_INT64 == this.m_ucValueType)
            {
                if (CMotionApi.YD_API_ERROR_SUCCESS != CMotionApi.yd_set_variable_int64(
                    this.m_ullId,
                    (Int64)(Object)value))
                {
					CMotionApi.yd_get_error_msg(this.m_sbufLastError, 200);
                    return false;
                }
                return true;
            }
            else if (CMotionApi.YD_API_VALUE_TYPE_FLOAT == this.m_ucValueType)
            {
                if (CMotionApi.YD_API_ERROR_SUCCESS != CMotionApi.yd_set_variable_float(
                    this.m_ullId,
                    (Single)(Object)value))
                {
					CMotionApi.yd_get_error_msg(this.m_sbufLastError, 200);
                    return false;
                }
                return true;
            }
            else if (CMotionApi.YD_API_VALUE_TYPE_DOUBLE == this.m_ucValueType)
            {
                if (CMotionApi.YD_API_ERROR_SUCCESS != CMotionApi.yd_set_variable_double(
                    this.m_ullId,
                    (Double)(Object)value))
                {
					CMotionApi.yd_get_error_msg(this.m_sbufLastError, 200);
                    return false;
                }
                return true;
            }
            else if (CMotionApi.YD_API_VALUE_TYPE_STRING == this.m_ucValueType)
            {
                if (CMotionApi.YD_API_ERROR_SUCCESS != CMotionApi.yd_set_variable_string(
                    this.m_ullId,
                    (String)(Object)value))
                {
					CMotionApi.yd_get_error_msg(this.m_sbufLastError, 200);
                    return false;
                }
                return true;
            }
            else if (CMotionApi.YD_API_VALUE_TYPE_MOTION_COORDS == this.m_ucValueType)
            {
                CMotionApi.YD_MotionCoords coords = (CMotionApi.YD_MotionCoords)(Object)value;
                if (CMotionApi.YD_API_ERROR_SUCCESS != CMotionApi.yd_set_variable_motion_coords(
                    this.m_ullId,
                    ref coords))
                {
					CMotionApi.yd_get_error_msg(this.m_sbufLastError, 200);
                    return false;
                }
                return true;
            }
            return false;
        }
    }

    // 数字输入类
    public class YDDigitalInput
    {
        // 成员变量
        private UInt16 m_usCard = 0;
        private UInt16 m_usType = 0;
        private UInt16 m_usIndex = 0;
        private String m_strName = "";
        private UInt64 m_ullTimestamp = 0;
		private StringBuilder m_sbufLastError = new StringBuilder(200);
        // 带参数构造函数
        public YDDigitalInput(UInt16 usCard, UInt16 usType, UInt16 usIndex, String strName)
        {
            this.m_usCard = usCard;
            this.m_usType = usType;
            this.m_usIndex = usIndex;
            this.m_strName = strName;
        }
		// 获取错误信息
		public String GetLastError()
		{
			return this.m_sbufLastError.ToString();
		}
        // 获取状态
        public Boolean GetStatus()
        {
            Boolean bStatus = false;
            if (CMotionApi.YD_API_ERROR_SUCCESS != CMotionApi.yd_get_digital_input_status(
                this.m_usCard,
                this.m_usType,
                this.m_usIndex,
                out bStatus,
                out this.m_ullTimestamp))
            {
				CMotionApi.yd_get_error_msg(this.m_sbufLastError, 200);
            }
            return bStatus;
        }
    }

    // 数字输出类
    public class YDDigitalOutput
    {
        // 成员变量
        private UInt16 m_usCard = 0;
        private UInt16 m_usType = 0;
        private UInt16 m_usIndex = 0;
        private String m_strName = "";
        private UInt64 m_ullTimestamp = 0;
		private StringBuilder m_sbufLastError = new StringBuilder(200);
        // 带参数构造函数
        public YDDigitalOutput(UInt16 usCard, UInt16 usType, UInt16 usIndex, String strName)
        {
            this.m_usCard = usCard;
            this.m_usType = usType;
            this.m_usIndex = usIndex;
            this.m_strName = strName;
        }
		// 获取错误信息
		public String GetLastError()
		{
			return this.m_sbufLastError.ToString();
		}
        // 获取状态
        public Boolean GetStatus()
        {
            Boolean bStatus = false;
            if (CMotionApi.YD_API_ERROR_SUCCESS != CMotionApi.yd_get_digital_output_status(
                this.m_usCard,
                this.m_usType,
                this.m_usIndex,
                out bStatus,
                out this.m_ullTimestamp))
            {
				CMotionApi.yd_get_error_msg(this.m_sbufLastError, 200);
            }
            return bStatus;
        }
        // 更新状态
        public Boolean SetStatus(Boolean bStatus)
        {
            if (CMotionApi.YD_API_ERROR_SUCCESS != CMotionApi.yd_set_digital_output_status(
                this.m_usCard,
                this.m_usType,
                this.m_usIndex,
                bStatus))
            {
				CMotionApi.yd_get_error_msg(this.m_sbufLastError, 200);
                return false;
            }
            return true;
        }
    }	

    // 运动轴
    public class YDAxis
    {
        // 成员变量
        private UInt16 m_usCard = 0;
        private UInt16 m_usAxis = 0;
        private String m_strName = "";
		private CMotionApi.YD_AxisMoveConfig m_moveConfig = new CMotionApi.YD_AxisMoveConfig();
		private CMotionApi.YD_AxisLimitConfig m_limitConfig = new CMotionApi.YD_AxisLimitConfig();
		private CMotionApi.YD_AxisHomeConfig m_homeConfig = new CMotionApi.YD_AxisHomeConfig();
		private YDDigitalInput m_diPositiveLimit;
		private YDDigitalInput m_diNegativeLimit;
		private YDDigitalInput m_diDriverAlarm;
		private YDDigitalInput m_diHomeSignal;
		private YDDigitalInput m_diMotorArrive;
		private StringBuilder m_sbufLastError = new StringBuilder(200);
        // 带参数构造函数
        public YDAxis(UInt16 usCard, UInt16 usAxis, String strName)
        {
            this.m_usCard = usCard;
            this.m_usAxis = usAxis;
            this.m_strName = strName;
			if (CMotionApi.YD_API_ERROR_SUCCESS != CMotionApi.yd_get_axis_move_config_by_id(this.m_usCard, this.m_usAxis, out this.m_moveConfig))
			{
				CMotionApi.yd_get_error_msg(this.m_sbufLastError, 200);
			}
			if (CMotionApi.YD_API_ERROR_SUCCESS != CMotionApi.yd_get_axis_limit_config_by_id(this.m_usCard, this.m_usAxis, out this.m_limitConfig))
			{
				CMotionApi.yd_get_error_msg(this.m_sbufLastError, 200);
			}
			if (CMotionApi.YD_API_ERROR_SUCCESS != CMotionApi.yd_get_axis_home_config_by_id(this.m_usCard, this.m_usAxis, out this.m_homeConfig))
			{
				CMotionApi.yd_get_error_msg(this.m_sbufLastError, 200);
			}
			this.m_diPositiveLimit = new YDDigitalInput(this.m_usCard, CMotionApi.YD_API_DITYPE_POSITIVE_LIMIT, this.m_usAxis, this.m_strName + "_正向限位");
			this.m_diNegativeLimit = new YDDigitalInput(this.m_usCard, CMotionApi.YD_API_DITYPE_NEGATIVE_LIMIT, this.m_usAxis, this.m_strName + "_负向限位");
			this.m_diDriverAlarm = new YDDigitalInput(this.m_usCard, CMotionApi.YD_API_DITYPE_DRIVER_ALARM, this.m_usAxis, this.m_strName + "_驱动报警");
			this.m_diHomeSignal = new YDDigitalInput(this.m_usCard, CMotionApi.YD_API_DITYPE_HOME_SIGNAL, this.m_usAxis, this.m_strName + "_原点信号");
			this.m_diMotorArrive = new YDDigitalInput(this.m_usCard, CMotionApi.YD_API_DITYPE_MOTOR_ARRIVE, this.m_usAxis, this.m_strName + "_电机到位");
        }
		// 获取错误信息
		public String GetLastError()
		{
			return this.m_sbufLastError.ToString();
		}
		// 获取卡号
		public UInt16 Card()
		{
			return this.m_usCard;
		}
		// 获取轴号
		public UInt16 Axis()
		{
			return this.m_usAxis;
		}
		// 获取名称
		public String Name()
		{
			return this.m_strName;
		}
		// 获取运动参数
		public CMotionApi.YD_AxisMoveConfig GetMoveConfig()
		{
			return this.m_moveConfig;
		}
		// 获取限位参数
		public CMotionApi.YD_AxisLimitConfig GetLimitConfig()
		{
			return this.m_limitConfig;
		}
		// 获取回原点参数
		public CMotionApi.YD_AxisHomeConfig GetHomeConfig()
		{
			return this.m_homeConfig;
		}
		// 获取正向限位DI状态
		public Boolean GetPositiveLimitDI()
		{
			return this.m_diPositiveLimit.GetStatus();
		}
		// 获取负向限位DI状态
		public Boolean GetNegativeLimitDI()
		{
			return this.m_diNegativeLimit.GetStatus();
		}
		// 获取驱动报警DI状态
		public Boolean GetDriverAlarmDI()
		{
			return this.m_diDriverAlarm.GetStatus();
		}
		// 获取原点信号DI状态
		public Boolean GetHomeSignalDI()
		{
			return this.m_diHomeSignal.GetStatus();
		}
		// 获取电机到位DI状态
		public Boolean GetMotorArriveDI()
		{
			return this.m_diMotorArrive.GetStatus();
		}
        // 使能轴
        public Boolean Enable(UInt32 uiTimeout = 3000)
        {
            Int32 iResult = CMotionApi.yd_enable_axis(this.m_usCard, this.m_usAxis, uiTimeout);
            if (CMotionApi.YD_API_ERROR_SUCCESS != iResult)
            {
				CMotionApi.yd_get_error_msg(this.m_sbufLastError, 200);
                return false;
            }
            return true;
        }
        // 禁用轴
        public Boolean Disable(UInt32 uiTimeout = 3000)
        {
            Int32 iResult = CMotionApi.yd_disable_axis(this.m_usCard, this.m_usAxis, uiTimeout);
            if (CMotionApi.YD_API_ERROR_SUCCESS != iResult)
            {
				CMotionApi.yd_get_error_msg(this.m_sbufLastError, 200);
                return false;
            }
            return true;
        }
        // 清除报警状态
        public Boolean ClearAlarms(UInt32 uiTimeout = 3000)
        {
            Int32 iResult = CMotionApi.yd_clear_axis_alarm(this.m_usCard, this.m_usAxis, uiTimeout);
            if (CMotionApi.YD_API_ERROR_SUCCESS != iResult)
            {
				CMotionApi.yd_get_error_msg(this.m_sbufLastError, 200);
                return false;
            }
            return true;
        }
        // 位置清零
        public Boolean ZeroPosition(UInt32 uiTimeout = 3000)
        {
            Int32 iResult = CMotionApi.yd_zero_axis_position(this.m_usCard, this.m_usAxis, uiTimeout);
            if (CMotionApi.YD_API_ERROR_SUCCESS != iResult)
            {
				CMotionApi.yd_get_error_msg(this.m_sbufLastError, 200);
                return false;
            }
            return true;
        }
		// 设置默认软限位
		public Boolean SetDefaultSoftLimit(UInt32 uiTimeout = 3000)
		{
			if (0 == this.m_limitConfig.soft_limit_enable) 
			{
				return true;
			}
			return this.SetCustomizedSoftLimit(this.m_limitConfig.soft_positive_limit, this.m_limitConfig.soft_negative_limit);
		}
		// 设置自定义软限位
		public Boolean SetCustomizedSoftLimit(Double dblPositiveLimit, Double dblNegativeLimit, UInt32 uiTimeout = 3000)
		{
            Int32 iResult = CMotionApi.yd_set_axis_soft_limit(this.m_usCard, this.m_usAxis, dblPositiveLimit, dblNegativeLimit, uiTimeout);
            if (CMotionApi.YD_API_ERROR_SUCCESS != iResult)
            {
				CMotionApi.yd_get_error_msg(this.m_sbufLastError, 200);
                return false;
            }
            return true;
		}
        // 启动回零运动
        public Boolean StartHomeMove(UInt32 uiTimeout = 3000)
        {
            Int32 iResult = CMotionApi.yd_start_axis_home_move(this.m_usCard, this.m_usAxis, uiTimeout);
            if (CMotionApi.YD_API_ERROR_SUCCESS != iResult)
            {
				CMotionApi.yd_get_error_msg(this.m_sbufLastError, 200);
                return false;
            }
            return true;
        }
        // 启动绝对运动
        public Boolean StartAbsoluteMove(Double dblPosition, Double dblVelocity, UInt32 uiTimeout = 3000)
        {
            Int32 iResult = CMotionApi.yd_start_axis_absolute_move(
                this.m_usCard,
                this.m_usAxis,
                dblPosition,
                dblVelocity,
                uiTimeout);
            if (CMotionApi.YD_API_ERROR_SUCCESS != iResult)
            {
				CMotionApi.yd_get_error_msg(this.m_sbufLastError, 200);
                return false;
            }
            return true;
        }
        // 启动相对运动
        public Boolean StartRelativeMove(Double dblDistance, Double dblVelocity, UInt32 uiTimeout = 3000)
        {
			Byte ucDirection = CMotionApi.YD_API_MOVE_DIRECTION_POSITIVE;
			if (dblDistance < 0) 
			{
				dblDistance = -dblDistance;
				ucDirection = CMotionApi.YD_API_MOVE_DIRECTION_NEGATIVE;
			}
            Int32 iResult = CMotionApi.yd_start_axis_relative_move(
                this.m_usCard,
                this.m_usAxis,
                dblDistance,
                dblVelocity,
                ucDirection,
                uiTimeout);
            if (CMotionApi.YD_API_ERROR_SUCCESS != iResult)
            {
				CMotionApi.yd_get_error_msg(this.m_sbufLastError, 200);
                return false;
            }
            return true;
        }
        // 启动Jog运动
        public Boolean StartJogMove(Double dblVelocity, UInt32 uiTimeout = 3000)
        {
			Byte ucDirection = CMotionApi.YD_API_MOVE_DIRECTION_POSITIVE;
			if (dblVelocity < 0)
			{
				dblVelocity = -dblVelocity;
				ucDirection = CMotionApi.YD_API_MOVE_DIRECTION_NEGATIVE;
			}
            Int32 iResult = CMotionApi.yd_start_axis_jog_move(
                this.m_usCard,
                this.m_usAxis,
                dblVelocity,
                ucDirection,
                uiTimeout);
            if (CMotionApi.YD_API_ERROR_SUCCESS != iResult)
            {
				CMotionApi.yd_get_error_msg(this.m_sbufLastError, 200);
                return false;
            }
            return true;
        }
        // 停止运动
        public Boolean StopMove(Boolean bUrgent, UInt32 uiTimeout = 3000)
        {
            Int32 iResult = CMotionApi.yd_stop_axis_move(
                this.m_usCard,
                this.m_usAxis,
                bUrgent,
                uiTimeout);
            if (CMotionApi.YD_API_ERROR_SUCCESS != iResult)
            {
				CMotionApi.yd_get_error_msg(this.m_sbufLastError, 200);
                return false;
            }
            return true;
        }
        // 是否规划运动中
        public Boolean IsProfileMoving()
        {
            Boolean bFlag = false;
            if (CMotionApi.YD_API_ERROR_SUCCESS != CMotionApi.yd_get_axis_profile_move_flag(
                this.m_usCard,
                this.m_usAxis,
                out bFlag))
            {
				CMotionApi.yd_get_error_msg(this.m_sbufLastError, 200);
                return false;
            }
            return bFlag;
        }
        // 获取驱动报警标志
        public Boolean GetDriverAlarmFlag()
        {
            Boolean bFlag = false;
            if (CMotionApi.YD_API_ERROR_SUCCESS != CMotionApi.yd_get_axis_driver_alarm_flag(
                this.m_usCard,
                this.m_usAxis,
                out bFlag))
            {
				CMotionApi.yd_get_error_msg(this.m_sbufLastError, 200);
                return false;
            }
            return bFlag;
        }
        // 获取跟随误差标志
        public Boolean GetFollowErrorFlag()
        {
            Boolean bFlag = false;
            if (CMotionApi.YD_API_ERROR_SUCCESS != CMotionApi.yd_get_axis_follow_error_flag(
                this.m_usCard,
                this.m_usAxis,
                out bFlag))
            {
				CMotionApi.yd_get_error_msg(this.m_sbufLastError, 200);
                return false;
            }
            return bFlag;
        }
        // 获取正向限位标志
        public Boolean GetPositiveLimitFlag()
        {
            Boolean bFlag = false;
            if (CMotionApi.YD_API_ERROR_SUCCESS != CMotionApi.yd_get_axis_positive_limit_flag(
                this.m_usCard,
                this.m_usAxis,
                out bFlag))
            {
				CMotionApi.yd_get_error_msg(this.m_sbufLastError, 200);
                return false;
            }
            return bFlag;
        }
        // 获取负向限位标志
        public Boolean GetNegativeLimitFlag()
        {
            Boolean bFlag = false;
            if (CMotionApi.YD_API_ERROR_SUCCESS != CMotionApi.yd_get_axis_negative_limit_flag(
                this.m_usCard,
                this.m_usAxis,
                out bFlag))
            {
				CMotionApi.yd_get_error_msg(this.m_sbufLastError, 200);
                return false;
            }
            return bFlag;
        }
        // 获取平滑停止标志
        public Boolean GetSmoothStopFlag()
        {
            Boolean bFlag = false;
            if (CMotionApi.YD_API_ERROR_SUCCESS != CMotionApi.yd_get_axis_smooth_stop_flag(
                this.m_usCard,
                this.m_usAxis,
                out bFlag))
            {
				CMotionApi.yd_get_error_msg(this.m_sbufLastError, 200);
                return false;
            }
            return bFlag;
        }
        // 获取紧急停止标志
        public Boolean GetUrgentStopFlag()
        {
            Boolean bFlag = false;
            if (CMotionApi.YD_API_ERROR_SUCCESS != CMotionApi.yd_get_axis_urgent_stop_flag(
                this.m_usCard,
                this.m_usAxis,
                out bFlag))
            {
				CMotionApi.yd_get_error_msg(this.m_sbufLastError, 200);
                return false;
            }
            return bFlag;
        }
        // 获取伺服使能标志
        public Boolean GetServoOnFlag()
        {
            Boolean bFlag = false;
            if (CMotionApi.YD_API_ERROR_SUCCESS != CMotionApi.yd_get_axis_servo_on_flag(
                this.m_usCard,
                this.m_usAxis,
                out bFlag))
            {
				CMotionApi.yd_get_error_msg(this.m_sbufLastError, 200);
                return false;
            }
            return bFlag;
        }
        // 获取电机到位标志
        public Boolean GetMotorArriveFlag()
        {
            Boolean bFlag = false;
            if (CMotionApi.YD_API_ERROR_SUCCESS != CMotionApi.yd_get_axis_motor_arrive_flag(
                this.m_usCard,
                this.m_usAxis,
                out bFlag))
            {
				CMotionApi.yd_get_error_msg(this.m_sbufLastError, 200);
                return false;
            }
            return bFlag;
        }
        // 获取原点信号标志
        public Boolean GetHomeSignalFlag()
        {
            Boolean bFlag = false;
            if (CMotionApi.YD_API_ERROR_SUCCESS != CMotionApi.yd_get_axis_home_signal_flag(
                this.m_usCard,
                this.m_usAxis,
                out bFlag))
            {
				CMotionApi.yd_get_error_msg(this.m_sbufLastError, 200);
                return false;
            }
            return bFlag;
        }
		// 获取回原点状态
		public Byte GetHomeMoveStatus()
		{
			Byte ucStatus = 0;
            if (CMotionApi.YD_API_ERROR_SUCCESS != CMotionApi.yd_get_axis_home_move_status(
                this.m_usCard,
                this.m_usAxis,
                out ucStatus))
            {
				CMotionApi.yd_get_error_msg(this.m_sbufLastError, 200);
            }
            return ucStatus;
		}
		// 更新回原点状态
		public Boolean SetHomeMoveStatus(Byte ucStatus)
		{
            if (CMotionApi.YD_API_ERROR_SUCCESS != CMotionApi.yd_set_axis_home_move_status(
                this.m_usCard,
                this.m_usAxis,
                ucStatus))
            {
				CMotionApi.yd_get_error_msg(this.m_sbufLastError, 200);
				return false;
            }
			return true;
		}
        // 获取目标位置
        public Double GetTargetPosition()
        {
            Double dblValue = 0;
            if (CMotionApi.YD_API_ERROR_SUCCESS != CMotionApi.yd_get_axis_target_position(
                this.m_usCard,
                this.m_usAxis,
                out dblValue))
            {
				CMotionApi.yd_get_error_msg(this.m_sbufLastError, 200);
            }
            return dblValue;
        }
        // 获取目标速度
        public Double GetTargetVelocity()
        {
            Double dblValue = 0;
            if (CMotionApi.YD_API_ERROR_SUCCESS != CMotionApi.yd_get_axis_target_velocity(
                this.m_usCard,
                this.m_usAxis,
                out dblValue))
            {
				CMotionApi.yd_get_error_msg(this.m_sbufLastError, 200);
            }
            return dblValue;
        }
        // 获取规划位置
        public Double GetProfilePosition()
        {
            Double dblValue = 0;
            if (CMotionApi.YD_API_ERROR_SUCCESS != CMotionApi.yd_get_axis_profile_position(
                this.m_usCard,
                this.m_usAxis,
                out dblValue))
            {
				CMotionApi.yd_get_error_msg(this.m_sbufLastError, 200);
            }
            return dblValue;
        }
        // 获取规划速度
        public Double GetProfileVelocity()
        {
            Double dblValue = 0;
            if (CMotionApi.YD_API_ERROR_SUCCESS != CMotionApi.yd_get_axis_profile_velocity(
                this.m_usCard,
                this.m_usAxis,
                out dblValue))
            {
				CMotionApi.yd_get_error_msg(this.m_sbufLastError, 200);
            }
            return dblValue;
        }
        // 获取编码器位置
        public Double GetEncoderPosition()
        {
            Double dblValue = 0;
            if (CMotionApi.YD_API_ERROR_SUCCESS != CMotionApi.yd_get_axis_encoder_position(
                this.m_usCard,
                this.m_usAxis,
                out dblValue))
            {
				CMotionApi.yd_get_error_msg(this.m_sbufLastError, 200);
            }
            return dblValue;
        }
        // 获取编码器速度
        public Double GetEncoderVelocity()
        {
            Double dblValue = 0;
            if (CMotionApi.YD_API_ERROR_SUCCESS != CMotionApi.yd_get_axis_encoder_velocity(
                this.m_usCard,
                this.m_usAxis,
                out dblValue))
            {
				CMotionApi.yd_get_error_msg(this.m_sbufLastError, 200);
            }
            return dblValue;
        }
    }

    // 气油缸类
    public class YDCylinder
    {
        // 成员变量
        private UInt32 m_uiId = 0;
        private String m_strName = "";
        // 带参数构造函数
        public YDCylinder(UInt32 uiId, String strName)
        {
            this.m_uiId = uiId;
            this.m_strName = strName;
        }
    }
	
	// 时间戳辅助类
	public static class CTimestampHelper
	{
		private static readonly DateTimeOffset g_UnixEpoch = new DateTimeOffset(1970, 1, 1, 0, 0, 0, TimeSpan.Zero);
		// 获取1970至今的秒数
        public static UInt64 CurrentSeconds()
        {
            var ts = DateTime.Now - new DateTime(1970, 1, 1, 0, 0, 0, 0);
            return Convert.ToUInt64(ts.TotalSeconds);
        }
		// 获取1970至今的毫秒数
        public static UInt64 CurrentMilliseconds()
        {
            var ts = DateTime.Now - new DateTime(1970, 1, 1, 0, 0, 0, 0);
            return Convert.ToUInt64(ts.TotalMilliseconds);
        }
		// 获取1970至今的微秒数
		public static UInt64 CurrentMicroseconds()
		{
			TimeSpan duration = DateTimeOffset.UtcNow - g_UnixEpoch;
			return Convert.ToUInt64(duration.Ticks / 10);
		}
	}
}

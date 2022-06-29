Imports System
Imports System.Text
Imports System.Runtime.InteropServices

Module YudaoMotionApi
    ' 接口包装类
    Public Class CMotionApi
        '字符常量
        Public Const YD_MOTION_API_LIBRARY As String = "dependences/yd_motion_api.dll"  'API库名称

        '接口错误代码定义
        Public Const YD_API_ERROR_SUCCESS As Int32 = 0                      '成功
        Public Const YD_API_ERROR_FAILED As Int32 = -1                      '失败
        Public Const YD_API_ERROR_NOT_INITIALIZED As Int32 = -2             '未初始化
        Public Const YD_API_ERROR_NOT_FOUND As Int32 = -3                   '不存在
        Public Const YD_API_ERROR_INVALID_INPUT As Int32 = -4               '输入参数无效
        Public Const YD_API_ERROR_DISMATCHED As Int32 = -5                  '类型不匹配
        Public Const YD_API_ERROR_UNAUTHORIZED As Int32 = -6                '未授权
        Public Const YD_API_ERROR_OPERATION_FORBIDDEN As Int32 = -7         '操作被禁止
        Public Const YD_API_ERROR_TIMEOUT As Int32 = -8                     '超时
        Public Const YD_API_ERROR_OUTSIDE_RANGE As Int32 = -9               '越界
        Public Const YD_API_ERROR_MEMORY_OVERFLOW As Int32 = -100           '内存溢出

        '数值类型定义
        Public Const YD_API_VALUE_TYPE_BOOL As Byte = 2                     '布尔型
        Public Const YD_API_VALUE_TYPE_INT8 As Byte = 3                     '有符号8位整型
        Public Const YD_API_VALUE_TYPE_UINT8 As Byte = 4                    '无符号8位整型
        Public Const YD_API_VALUE_TYPE_INT16 As Byte = 5                    '有符号16位整型
        Public Const YD_API_VALUE_TYPE_UINT16 As Byte = 6                   '无符号16位整型
        Public Const YD_API_VALUE_TYPE_INT32 As Byte = 7                    '有符号32位整型
        Public Const YD_API_VALUE_TYPE_UINT32 As Byte = 8                   '无符号32位整型
        Public Const YD_API_VALUE_TYPE_INT64 As Byte = 9                    '有符号64位整型
        Public Const YD_API_VALUE_TYPE_UINT64 As Byte = 10                  '无符号64位整型
        Public Const YD_API_VALUE_TYPE_FLOAT As Byte = 11                   '单精度浮点型
        Public Const YD_API_VALUE_TYPE_DOUBLE As Byte = 12                  '双精度浮点型
        Public Const YD_API_VALUE_TYPE_STRING As Byte = 13                  '字符串
        Public Const YD_API_VALUE_TYPE_MOTION_COORDS As Byte = 17           '运动坐标

        '运动类型定义
        Public Const YD_API_MOVE_TYPE_ABSOLUTE As Byte = 11                 '绝对运动
        Public Const YD_API_MOVE_TYPE_RELATIVE As Byte = 12                 '相对运动
        Public Const YD_API_MOVE_TYPE_JOG As Byte = 13                      'Jog运动

        '变量类型定义
        Public Const YD_API_VARIABLE_TYPE_DI As Byte = 1                    'DI变量，只读
        Public Const YD_API_VARIABLE_TYPE_DO As Byte = 2                    'DO变量，读/写
        Public Const YD_API_VARIABLE_TYPE_AI As Byte = 3                    'AI变量，只读
        Public Const YD_API_VARIABLE_TYPE_AO As Byte = 4                    'AO变量，读/写
        Public Const YD_API_VARIABLE_TYPE_SYSTEM As Byte = 5                '系统变量，只读
        Public Const YD_API_VARIABLE_TYPE_MOTION As Byte = 6                '运动变量，只读
        Public Const YD_API_VARIABLE_TYPE_CYLINDER As Byte = 7              '气油缸变量，只读
        Public Const YD_API_VARIABLE_TYPE_CONFIG As Byte = 8                '配置变量，读/写
        Public Const YD_API_VARIABLE_TYPE_VIRTUAL As Byte = 9               '虚拟变量，读/写
        Public Const YD_API_VARIABLE_TYPE_CONTROL As Byte = 10              '控制变量，读/写
        Public Const YD_API_VARIABLE_TYPE_LOGIC As Byte = 11                '逻辑变量，读/写
        Public Const YD_API_VARIABLE_TYPE_SAFE As Byte = 12                 '安全变量，只读
		Public Const YD_API_VARIABLE_TYPE_GLOBAL As Byte = 91				'全局变量，读/写
		Public Const YD_API_VARIABLE_TYPE_RECIPE As Byte = 92				'配方变量，读/写
		Public Const YD_API_VARIABLE_TYPE_LOCAL As Byte = 93				'临时变量，读/写

        '运动方向定义
        Public Const YD_API_MOVE_DIRECTION_POSITIVE As Byte = 1             '正方向运动
        Public Const YD_API_MOVE_DIRECTION_NEGATIVE As Byte = 2             '负方向运动

        'DI类型定义
        Public Const YD_API_DITYPE_GENERAL As Byte = 0                      '通用输入
        Public Const YD_API_DITYPE_POSITIVE_LIMIT As Byte = 1               '正限位
        Public Const YD_API_DITYPE_NEGATIVE_LIMIT As Byte = 2               '负限位
        Public Const YD_API_DITYPE_DRIVER_ALARM As Byte = 3                 '驱动报警
        Public Const YD_API_DITYPE_HOME_SIGNAL As Byte = 4                  '原点信号
        Public Const YD_API_DITYPE_MOTOR_ARRIVE As Byte = 5                 '电机到位

        'DO类型定义
        Public Const YD_API_DOTYPE_GENERAL As Byte = 0                      '通用输出
        Public Const YD_API_DOTYPE_DRIVER_ENABLE As Byte = 1                '驱动使能
        Public Const YD_API_DOTYPE_ALARM_CLEAR As Byte = 2                  '报警清除

        '控制器模式
        Public Const YD_API_CONTROLLER_MODE_MANUAL As Byte = 0              '手动模式
        Public Const YD_API_CONTROLLER_MODE_AUTOMATIC As Byte = 1           '自动模式

		'轴回零状态
		Public Const YD_API_AXIS_HOME_MOVE_NOT_EXECUTED As Byte = 0			'未回零
		Public Const YD_API_AXIS_HOME_MOVE_IN_PROCESSING As Byte = 1		'回零中
		Public Const YD_API_AXIS_HOME_MOVE_EXECUTED As Byte = 2				'已回零

        '控制器状态
        Public Const YD_API_CONTROLLER_STATUS_STOPED As Byte = 0            '已停止
        Public Const YD_API_CONTROLLER_STATUS_RUNNING As Byte = 1           '运行中
        Public Const YD_API_CONTROLLER_STATUS_SUSPENDED As Byte = 2         '已暂停
        Public Const YD_API_CONTROLLER_STATUS_RESTORED As Byte = 3          '已恢复

        '气油缸运动方向
        Public Const YD_API_CYLINDER_MOVE_DIRECTION1 As Byte = 1            '方向一运动
        Public Const YD_API_CYLINDER_MOVE_DIRECTION2 As Byte = 2            '方向二运动

        '气油缸到位类型
        Public Const YD_API_CYLINDER_DELAYED_ARRIVE As Byte = 1             '延时等待
        Public Const YD_API_CYLINDER_DION_ARRIVE As Byte = 2                'DI有效到位
        Public Const YD_API_CYLINDER_DION_DELAYED_ARRIVE As Byte = 3        'DI有效+延时等待到位
        Public Const YD_API_CYLINDER_AXIS_ENCODER_ARRIVE As Byte = 4        '编码器到位		
		
		'运动轴回原点模式
		Public Const YD_API_HOMEMODE_NONE As Byte = 0												'不用回原点
		Public Const YD_API_HOMEMODE_CHECKSIGNAL_BY_POSITIVEMOVE_IF_NEGATIVELIMIT_ON As Byte = 1 	'轴先运动到负限位，然后向正方向查找原点信号，当检测到原点信号时立即停止，当前位置为原点
		Public Const YD_API_HOMEMODE_CHECKSIGNAL_BY_NEGATIVEMOVE_IF_POSITIVELIMIT_ON As Byte = 2 	'轴先运动到正限位，然后向负方向查找原点信号，当检测到原点信号时立即停止，当前位置为原点
		Public Const YD_API_HOMEMODE_CHECKSIGNAL_BY_ANTICLOCKWISEMOVE As Byte = 3					'旋转轴向负方向（逆时针）查找原点信号，当检测到原点信号时 立即停止，当前位置为原点
		Public Const YD_API_HOMEMODE_CHECKSIGNAL_BY_CLOCKWISEMOVE As Byte = 4						'旋转轴向正方向（顺时针）查找原点信号，当检测到原点信号时 立即停止，当前位置为原点
		Public Const YD_API_HOMEMODE_IF_POSITIVELIMIT_ON As Byte = 5								'将该轴的负限位作为原点信号
		Public Const YD_API_HOMEMODE_IF_NEGATIVELIMIT_ON As Byte = 6								'将该轴的正限位作为原点信号
		
		'电平捕捉类型
		Public Const YD_API_ELECTRIC_CAPTURE_RISING_EDGE As Byte = 1 								'上升沿触发
		Public Const YD_API_ELECTRIC_CAPTURE_FALLING_EDGE As Byte = 2 								'下降沿触发
		
		'限位类型
		Public Const YD_API_LIMIT_TYPE_POSITIVE As Byte = 1 										'正限位
		Public Const YD_API_LIMIT_TYPE_NEGATIVE As Byte = 2 										'负限位
		
		'回原点查找方向
		Public Const YD_API_HOMECHECK_DIRECTION_POSITIVE As Byte = 1 											'正向
		Public Const YD_API_HOMECHECK_DIRECTION_NEGATIVE As Byte = 2 											'负向
		Public Const YD_API_HOMECHECK_DIRECTION_CLOCKWISE As Byte = YD_API_HOMECHECK_DIRECTION_POSITIVE 		'顺时针
		Public Const YD_API_HOMECHECK_DIRECTION_ANTICLOCKWISE As Byte = YD_API_HOMECHECK_DIRECTION_NEGATIVE 	'逆时针
		
		'跨语言函数结果
		Public Const YD_API_CROSS_RESULT_SUCCESS As Int32 = 0				'成功
		Public Const YD_API_CROSS_RESULT_FAILED As Int32 = -1				'失败
		Public Const YD_API_CROSS_RESULT_RETRY As Int32 = 1					'重试

        '最大数量定义
        Public Const YD_MAX_MOTION_COORD_NUMBER As Byte = 32                '运动坐标最大轴数
        Public Const YD_MAX_NAME_LENGTH As Byte = 64                        '名称最大长度
        Public Const YD_MAX_VALUE_LENGTH As Byte = 64                       '数值最大长度

        '日志级别
        Public Const YD_API_LOG_LEVEL_TRACE As Byte = 1                     '跟踪
        Public Const YD_API_LOG_LEVEL_DEBUG As Byte = 2                     '调试
        Public Const YD_API_LOG_LEVEL_INFO As Byte = 3                      '信息
        Public Const YD_API_LOG_LEVEL_WARN As Byte = 4                      '警告
        Public Const YD_API_LOG_LEVEL_ERROR As Byte = 5                     '错误
        Public Const YD_API_LOG_LEVEL_CRITICAL As Byte = 6                  '致命

        '项目信息
        <StructLayoutAttribute(LayoutKind.Sequential, CharSet:=CharSet.Ansi, Pack:=8)>
        Public Structure YD_Project
            Dim version As UInt32                                           '版本号
            <MarshalAsAttribute(UnmanagedType.ByValArray, SizeConst:=YD_MAX_VALUE_LENGTH, ArraySubType:=UnmanagedType.U1)>
            Dim name As Char()                                              '项目名称
            <MarshalAsAttribute(UnmanagedType.ByValArray, SizeConst:=YD_MAX_VALUE_LENGTH, ArraySubType:=UnmanagedType.U1)>
            Dim recipe As Char()                                            '配方名称
        End Structure

        '运动坐标
        <StructLayoutAttribute(LayoutKind.Sequential, CharSet:=CharSet.Ansi, Pack:=8)>
        Public Structure YD_MotionCoords
            <MarshalAs(UnmanagedType.ByValArray, SizeConst:=YD_MAX_MOTION_COORD_NUMBER, ArraySubType:=UnmanagedType.U2)>
            Dim cards() As UInt16                                           '卡编号数组 [0, N]
            <MarshalAs(UnmanagedType.ByValArray, SizeConst:=YD_MAX_MOTION_COORD_NUMBER, ArraySubType:=UnmanagedType.U2)>
            Dim axises() As UInt16                                          '轴序号数组 [1, M]
            <MarshalAs(UnmanagedType.ByValArray, SizeConst:=YD_MAX_MOTION_COORD_NUMBER, ArraySubType:=UnmanagedType.U1)>
            Dim types() As Byte                                             '运动类型数组
            <MarshalAs(UnmanagedType.ByValArray, SizeConst:=YD_MAX_MOTION_COORD_NUMBER, ArraySubType:=UnmanagedType.U1)>
            Dim directions() As Byte                                        '运动方向数组
            <MarshalAs(UnmanagedType.ByValArray, SizeConst:=YD_MAX_MOTION_COORD_NUMBER, ArraySubType:=UnmanagedType.R8)>
            Dim targets() As Double                                         '运动目标数组
            <MarshalAs(UnmanagedType.ByValArray, SizeConst:=YD_MAX_MOTION_COORD_NUMBER, ArraySubType:=UnmanagedType.R8)>
            Dim velocities() As Double                                      '运动速度数组
            Dim number As Byte                                              '运动坐标个数
        End Structure

        '变量信息
        <StructLayoutAttribute(LayoutKind.Sequential, CharSet:=CharSet.Ansi, Pack:=8)>
        Public Structure YD_VariableInfo
            Dim variable_id As UInt64                                       '变量id
            <MarshalAs(UnmanagedType.ByValArray, SizeConst:=YD_MAX_NAME_LENGTH, ArraySubType:=UnmanagedType.U1)>
            Dim variable_name() As Char                                     '变量名称
            Dim variable_type As Byte                                       '变量类型
            Dim value_type As Byte                                          '数值类型
            <MarshalAs(UnmanagedType.ByValArray, SizeConst:=YD_MAX_VALUE_LENGTH, ArraySubType:=UnmanagedType.U1)>
            Dim max_value() As Char                                         '最大值
            <MarshalAs(UnmanagedType.ByValArray, SizeConst:=YD_MAX_VALUE_LENGTH, ArraySubType:=UnmanagedType.U1)>
            Dim min_value() As Char                                         '最小值
        End Structure

        'IO信息
        <StructLayoutAttribute(LayoutKind.Sequential, CharSet:=CharSet.Ansi, Pack:=8)>
        Public Structure YD_IOInfo
            Dim card As UInt16                                              '卡编号 [0, N]
            Dim type As UInt16                                              '类型
            Dim index As UInt16                                             '序号
            <MarshalAs(UnmanagedType.ByValArray, SizeConst:=YD_MAX_NAME_LENGTH, ArraySubType:=UnmanagedType.U1)>
            Dim name() As Char                                              '名称
            <MarshalAs(UnmanagedType.ByValArray, SizeConst:=YD_MAX_NAME_LENGTH, ArraySubType:=UnmanagedType.U1)>
            Dim label() As Char                                             '标识
            Dim enable As Byte                                              '是否使能
            Dim reverse As Byte                                             '是否反转
        End Structure

        '运动轴信息
        <StructLayoutAttribute(LayoutKind.Sequential, CharSet:=CharSet.Ansi, Pack:=8)>
        Public Structure YD_AxisInfo
            Dim card As UInt16                                              '卡编号 [0, N]
            Dim axis As UInt16                                              '轴序号 [1, M]
            <MarshalAs(UnmanagedType.ByValArray, SizeConst:=YD_MAX_NAME_LENGTH, ArraySubType:=UnmanagedType.U1)>
            Dim name() As Char                                              '名称
            Dim enable As Byte                                              '是否使能
            Dim equivalent As Double                                        '脉冲当量
        End Structure
		
		'运动轴回原点参数
        <StructLayoutAttribute(LayoutKind.Sequential, CharSet:=CharSet.Ansi, Pack:=8)>
		Public Structure YD_AxisHomeConfig
			Dim priority As Byte;											'回原点优先级
			Dim mode As Byte;												'回原点模式
			Dim search_distance As Double;									'搜索距离
			Dim move_velocity As Double;									'移动速度
			Dim search_high_velocity As Double;								'搜索速度（高速）
			Dim search_low_velocity As Double;								'搜索速度（低速）
			Dim origin_offset As Double;									'原点偏移量
			Dim capture_electric_level As Byte;								'原点捕获电平选中
		End Structure

        '运动轴状态
        <StructLayoutAttribute(LayoutKind.Sequential, CharSet:=CharSet.Ansi, Pack:=8)>
        Public Structure YD_AxisStates
            Dim driver_alarm As Byte                                        '驱动报警标志
            Dim follow_error As Byte                                        '跟随误差标志
            Dim positive_limit As Byte                                      '是否使能
            Dim negative_limit As Byte                                      '负向限位标志
            Dim smooth_stop As Byte                                         '平滑停止标志
            Dim urgent_stop As Byte                                         '紧急停止标志
            Dim servo_on As Byte                                            '伺服使能标志
            Dim profile_move As Byte                                        '运动状态标志
            Dim motor_arrive As Byte                                        '电机到位标志
            Dim home_signal As Byte                                         '原点信号标志
            Dim home_moved As Byte                                          '回零状态标志
            Dim profile_mode As UInt32                                      '运动模式
            Dim target_position As Double                                   '目标位置
            Dim target_velocity As Double                                   '目标速度
            Dim profile_position As Double                                  '规划位置
            Dim profile_velocity As Double                                  '规划速度
            Dim encoder_position As Double                                  '编码器位置（反馈位置）
            Dim encoder_velocity As Double                                  '编码器速度（反馈速度）
        End Structure

        '气油缸信息
        <StructLayoutAttribute(LayoutKind.Sequential, CharSet:=CharSet.Ansi, Pack:=8)>
        Public Structure YD_CylinderInplace
            Dim inplace_type As Byte                                        '到位类型
            Dim refer_di_device As UInt32                                   '关联di所属设备id
            Dim refer_di_type As UInt16                                     '关联di类型
            Dim refer_di_index As UInt16                                    '关联di序号
            Dim delay_time As UInt32                                        '延迟时间：毫秒
            Dim alarm_time As UInt32                                        '报警时间：毫秒
        End Structure
        <StructLayoutAttribute(LayoutKind.Sequential, CharSet:=CharSet.Ansi, Pack:=8)>
        Public Structure YD_CylinderCoil
            Dim refer_do_device As UInt32                                   '关联do所属设备id
            Dim refer_do_type As UInt16                                     '关联do类型
            Dim refer_do_index As UInt16                                    '关联do序号
            Dim refer_do_value As Byte                                      '关联do动作值
        End Structure
        <StructLayoutAttribute(LayoutKind.Sequential, CharSet:=CharSet.Ansi, Pack:=8)>
        Public Structure YD_CylinderInfo
            Dim id As UInt32                                                '气油缸id
            <MarshalAsAttribute(UnmanagedType.ByValArray, SizeConst:=YD_MAX_NAME_LENGTH, ArraySubType:=UnmanagedType.U1)>
            Dim name() As Char                                              '气油缸名称
            Dim enable As Byte                                              '是否使能
            <MarshalAsAttribute(UnmanagedType.ByValArray, SizeConst:=YD_MAX_NAME_LENGTH, ArraySubType:=UnmanagedType.U1)>
            Dim direction1_name() As Char                                   '方向一名称
            Dim direction1_inplace As YD_CylinderInplace                    '方向一到位参数
            Dim direction1_coil As YD_CylinderCoil                          '方向一电磁阀
            <MarshalAsAttribute(UnmanagedType.ByValArray, SizeConst:=YD_MAX_NAME_LENGTH, ArraySubType:=UnmanagedType.U1)>
            Dim direction2_name() As Char                                   '方向二名称
            Dim direction2_inplace As YD_CylinderInplace                    '方向二到位参数
            Dim direction2_coil As YD_CylinderCoil                          '方向二电磁阀
        End Structure

        '气油缸状态
        <StructLayoutAttribute(LayoutKind.Sequential, CharSet:=CharSet.Ansi, Pack:=8)>
        Public Structure YD_DirectionState
            Dim refer_di_state As Byte                                      '关联DI状态
            Dim inplace_state As Byte                                       '到位状态
            Dim alarm_state As Byte                                         '报警状态
        End Structure
        <StructLayoutAttribute(LayoutKind.Sequential, CharSet:=CharSet.Ansi, Pack:=8)>
        Public Structure YD_CylinderStates
            Dim direction1_state As YD_DirectionState                       '方向一状态
            Dim direction2_state As YD_DirectionState                       '方向二状态
        End Structure

        ''' <summary>
        ''' 获取项目信息
        ''' </summary>
        ''' <param name="project"></param>
        ''' <returns></returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_get_project_info", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_get_project_info(ByRef project As YD_Project) As Int32
        End Function

        ''' <summary>
        ''' 获取模块名称
        ''' </summary>
        ''' <param name="buffer"></param>
        ''' <param name="size"></param>
        ''' <returns></returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_get_module_name", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_get_module_name(ByVal buffer As StringBuilder, ByVal size As Int32) As Int32
        End Function

        ''' <summary>
        ''' 输出日志
        ''' </summary>
        ''' <param name="level"></param>
        ''' <param name="log"></param>
        ''' <returns></returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_output_log", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_output_log(ByVal level As Byte, ByVal log As String) As Int32
        End Function

        ''' <summary>
        ''' 获取错误信息
        ''' </summary>
        ''' <param name="buffer"></param>
        ''' <param name="size"></param>
        ''' <returns></returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_get_error_msg", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_get_error_msg(ByVal buffer As StringBuilder, ByVal size As Int32) As Int32
        End Function


        ''' <summary>
        ''' 获取逻辑控制器状态
        ''' </summary>
        ''' <param name="status">出参：Byte型引用，运行状态</param>
        ''' <returns>错误代码</returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_get_controller_status", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_get_controller_status(ByRef status As Byte) As Int32
        End Function

        ''' <summary>
        ''' 获取逻辑控制器模式
        ''' </summary>
        ''' <param name="mode">出参：Byte型引用，工作模式</param>
        ''' <returns>错误代码</returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_get_controller_mode", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_get_controller_mode(ByRef mode As Byte) As Int32
        End Function

        ''' <summary>
        ''' 启动逻辑控制器
        ''' </summary>
        ''' <param name="timeout">可选超时时间，单位：毫秒</param>
        ''' <returns>错误代码</returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_start_controller", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_start_controller(Optional ByVal timeout As UInt32 = 3000) As Int32
        End Function

        ''' <summary>
        ''' 停止逻辑控制器
        ''' </summary>
        ''' <param name="timeout">可选超时时间，单位：毫秒</param>
        ''' <returns>错误代码</returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_stop_controller", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_stop_controller(Optional ByVal timeout As UInt32 = 3000) As Int32
        End Function

        ''' <summary>
        ''' 暂停逻辑控制器
        ''' </summary>
        ''' <param name="timeout">可选超时时间，单位：毫秒</param>
        ''' <returns>错误代码</returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_pause_controller", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_pause_controller(Optional ByVal timeout As UInt32 = 3000) As Int32
        End Function

        ''' <summary>
        ''' 恢复逻辑控制器
        ''' </summary>
        ''' <param name="timeout">可选超时时间，单位：毫秒</param>
        ''' <returns>错误代码</returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_restore_controller", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_restore_controller(Optional ByVal timeout As UInt32 = 3000) As Int32
        End Function

        ''' <summary>
        ''' 切换逻辑控制器手动模式
        ''' </summary>
        ''' <param name="timeout">可选超时时间，单位：毫秒</param>
        ''' <returns>错误代码</returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_switch_controller_to_manual_mode", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_switch_controller_to_manual_mode(Optional ByVal timeout As UInt32 = 3000) As Int32
        End Function

        ''' <summary>
        ''' 切换逻辑控制器自动模式
        ''' </summary>
        ''' <param name="timeout">可选超时时间，单位：毫秒</param>
        ''' <returns>错误代码</returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_switch_controller_to_automatic_mode", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_switch_controller_to_automatic_mode(Optional ByVal timeout As UInt32 = 3000) As Int32
        End Function

        ''' <summary>
        ''' 获取指定ID的变量
        ''' </summary>
        ''' <param name="id">入参：变量id</param>
        ''' <param name="pVariableInfo">出参：YD_VariableInfo类型引用变量</param>
        ''' <returns>错误代码</returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_get_variable_by_id", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_get_variable_by_id(ByVal id As UInt64, ByRef pVariableInfo As YD_VariableInfo) As Int32
        End Function

        ''' <summary>
        ''' 获取指定名称的变量
        ''' </summary>
        ''' <param name="name">入参：变量名称</param>
        ''' <param name="pVariableInfo">出参：YD_VariableInfo类型引用变量</param>
        ''' <returns>错误代码</returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_get_variable_by_name", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_get_variable_by_name(ByVal name As String, ByRef pVariableInfo As YD_VariableInfo) As Int32
        End Function

        ''' <summary>
        ''' 获取指定变量布尔数值
        ''' </summary>
        ''' <param name="id">入参：变量id</param>
        ''' <param name="value">出参：最新数值</param>
        ''' <param name="timestamp">出参：最后更新时间，可选</param>
        ''' <returns>错误代码</returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_get_variable_boolean", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_get_variable_boolean(ByVal id As UInt64, ByRef value As Boolean, Optional ByRef timestamp As UInt64 = Nothing) As Int32
        End Function

        ''' <summary>
        ''' 设置指定变量布尔数值
        ''' </summary>
        ''' <param name="id">入参：变量id</param>
        ''' <param name="value">入参：待更新数值</param>
        ''' <returns>错误代码</returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_set_variable_boolean", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_set_variable_boolean(ByVal id As UInt64, ByVal value As Boolean) As Int32
        End Function

        ''' <summary>
        ''' 获取指定变量有符号8位整型数值
        ''' </summary>
        ''' <param name="id">入参：变量id</param>
        ''' <param name="value">出参：最新数值</param>
        ''' <param name="timestamp">出参：最后更新时间，可选</param>
        ''' <returns></returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_get_variable_int8", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_get_variable_int8(ByVal id As UInt64, ByRef value As SByte, Optional ByRef timestamp As UInt64 = Nothing) As Int32
        End Function

        ''' <summary>
        ''' 设置指定变量有符号8位整型数值
        ''' </summary>
        ''' <param name="id">入参：变量id</param>
        ''' <param name="value">出参：最新数值</param>
        ''' <returns></returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_set_variable_int8", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_set_variable_int8(ByVal id As UInt64, ByVal value As SByte) As Int32
        End Function

        ''' <summary>
        ''' 获取指定变量无符号8位整型数值
        ''' </summary>
        ''' <param name="id">入参：变量id</param>
        ''' <param name="value">出参：最新数值</param>
        ''' <param name="timestamp">出参：最后更新时间，可选</param>
        ''' <returns></returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_get_variable_uint8", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_get_variable_uint8(ByVal id As UInt64, ByRef value As Byte, Optional ByRef timestamp As UInt64 = Nothing) As Int32
        End Function

        ''' <summary>
        ''' 设置指定变量无符号8位整型数值
        ''' </summary>
        ''' <param name="id">入参：变量id</param>
        ''' <param name="value">出参：最新数值</param>
        ''' <returns></returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_set_variable_uint8", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_set_variable_uint8(ByVal id As UInt64, ByVal value As Byte) As Int32
        End Function

        ''' <summary>
        ''' 获取指定变量有符号16位整型数值
        ''' </summary>
        ''' <param name="id">入参：变量id</param>
        ''' <param name="value">出参：最新数值</param>
        ''' <param name="timestamp">出参：最后更新时间，可选</param>
        ''' <returns></returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_get_variable_int16", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_get_variable_int16(ByVal id As UInt64, ByRef value As Int16, Optional ByRef timestamp As UInt64 = Nothing) As Int32
        End Function

        ''' <summary>
        ''' 设置指定变量有符号16位整型数值
        ''' </summary>
        ''' <param name="id">入参：变量id</param>
        ''' <param name="value">出参：最新数值</param>
        ''' <returns></returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_set_variable_int16", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_set_variable_int16(ByVal id As UInt64, ByVal value As Int16) As Int32
        End Function

        ''' <summary>
        ''' 获取指定变量无符号16位整型数值
        ''' </summary>
        ''' <param name="id">入参：变量id</param>
        ''' <param name="value">出参：最新数值</param>
        ''' <param name="timestamp">出参：最后更新时间，可选</param>
        ''' <returns></returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_get_variable_uint16", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_get_variable_uint16(ByVal id As UInt64, ByRef value As UInt16, Optional ByRef timestamp As UInt64 = Nothing) As Int32
        End Function

        ''' <summary>
        ''' 设置指定变量无符号16位整型数值
        ''' </summary>
        ''' <param name="id">入参：变量id</param>
        ''' <param name="value">出参：最新数值</param>
        ''' <returns></returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_set_variable_uint16", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_set_variable_uint16(ByVal id As UInt64, ByVal value As UInt16) As Int32
        End Function

        ''' <summary>
        ''' 获取指定变量有符号32位整型数值
        ''' </summary>
        ''' <param name="id">入参：变量id</param>
        ''' <param name="value">出参：最新数值</param>
        ''' <param name="timestamp">出参：最后更新时间，可选</param>
        ''' <returns>错误代码</returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_get_variable_int32", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_get_variable_int32(ByVal id As UInt64, ByRef value As Int32, Optional ByRef timestamp As UInt64 = Nothing) As Int32
        End Function

        ''' <summary>
        ''' 设置指定变量有符号32位整型数值
        ''' </summary>
        ''' <param name="id">入参：变量id</param>
        ''' <param name="value">入参：待更新数值</param>
        ''' <returns>错误代码</returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_set_variable_int32", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_set_variable_int32(ByVal id As UInt64, ByVal value As Int32) As Int32
        End Function

        ''' <summary>
        ''' 获取指定变量无符号32位整型数值
        ''' </summary>
        ''' <param name="id">入参：变量id</param>
        ''' <param name="value">出参：最新数值</param>
        ''' <param name="timestamp">出参：最后更新时间，可选</param>
        ''' <returns>错误代码</returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_get_variable_uint32", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_get_variable_uint32(ByVal id As UInt64, ByRef value As UInt32, Optional ByRef timestamp As UInt64 = Nothing) As Int32
        End Function

        ''' <summary>
        ''' 设置指定变量无符号32位整型数值
        ''' </summary>
        ''' <param name="id">入参：变量id</param>
        ''' <param name="value">入参：待更新数值</param>
        ''' <returns>错误代码</returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_set_variable_uint32", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_set_variable_uint32(ByVal id As UInt64, ByVal value As UInt32) As Int32
        End Function

        ''' <summary>
        ''' 获取指定变量有符号64位整型数值
        ''' </summary>
        ''' <param name="id">入参：变量id</param>
        ''' <param name="value">出参：最新数值</param>
        ''' <param name="timestamp">出参：最后更新时间，可选</param>
        ''' <returns>错误代码</returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_get_variable_int64", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_get_variable_int64(ByVal id As UInt64, ByRef value As Int64, Optional ByRef timestamp As UInt64 = Nothing) As Int32
        End Function

        ''' <summary>
        ''' 设置指定变量有符号64位整型数值
        ''' </summary>
        ''' <param name="id">入参：变量id</param>
        ''' <param name="value">入参：待更新数值</param>
        ''' <returns>错误代码</returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_set_variable_int64", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_set_variable_int64(ByVal id As UInt64, ByVal value As Int64) As Int32
        End Function

        ''' <summary>
        ''' 获取指定变量无符号64位整型数值
        ''' </summary>
        ''' <param name="id">入参：变量id</param>
        ''' <param name="value">出参：最新数值</param>
        ''' <param name="timestamp">出参：最后更新时间，可选</param>
        ''' <returns>错误代码</returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_get_variable_uint64", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_get_variable_uint64(ByVal id As UInt64, ByRef value As UInt64, Optional ByRef timestamp As UInt64 = Nothing) As Int32
        End Function

        ''' <summary>
        ''' 设置指定变量无符号64位整型数值
        ''' </summary>
        ''' <param name="id">入参：变量id</param>
        ''' <param name="value">入参：待更新数值</param>
        ''' <returns>错误代码</returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_set_variable_uint64", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_set_variable_uint64(ByVal id As UInt64, ByVal value As UInt64) As Int32
        End Function

        ''' <summary>
        ''' 获取指定变量单精度浮点型数值
        ''' </summary>
        ''' <param name="id">入参：变量id</param>
        ''' <param name="value">出参：最新数值</param>
        ''' <param name="timestamp">出参：最后更新时间，可选</param>
        ''' <returns>错误代码</returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_get_variable_float", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_get_variable_float(ByVal id As UInt64, ByRef value As Single, Optional ByRef timestamp As UInt64 = Nothing) As Int32
        End Function

        ''' <summary>
        ''' 设置指定变量单精度浮点型数值
        ''' </summary>
        ''' <param name="id">入参：变量id</param>
        ''' <param name="value">入参：待更新数值</param>
        ''' <returns>错误代码</returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_set_variable_float", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_set_variable_float(ByVal id As UInt64, ByVal value As Single) As Int32
        End Function

        ''' <summary>
        ''' 获取指定变量双精度浮点型数值
        ''' </summary>
        ''' <param name="id">入参：变量id</param>
        ''' <param name="value">出参：最新数值</param>
        ''' <param name="timestamp">出参：最后更新时间，可选</param>
        ''' <returns>错误代码</returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_get_variable_double", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_get_variable_double(ByVal id As UInt64, ByRef value As Double, Optional ByRef timestamp As UInt64 = Nothing) As Int32
        End Function

        ''' <summary>
        ''' 设置指定变量双精度浮点型数值
        ''' </summary>
        ''' <param name="id">入参：变量id</param>
        ''' <param name="value">入参：待更新数值</param>
        ''' <returns>错误代码</returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_set_variable_double", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_set_variable_double(ByVal id As UInt64, ByVal value As Double) As Int32
        End Function

        ''' <summary>
        ''' 获取指定变量字符串数值
        ''' </summary>
        ''' <param name="id">入参：变量id</param>
        ''' <param name="value">出参：最新数值，字符数组</param>
        ''' <param name="size">入参：字符数值大小</param>
        ''' <param name="timestamp">出参：最后更新时间，可选</param>
        ''' <returns>错误代码</returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_get_variable_string", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_get_variable_string(ByVal id As UInt64, ByVal value As StringBuilder, ByVal size As Int32, Optional ByRef timestamp As UInt64 = Nothing) As Int32
        End Function

        ''' <summary>
        ''' 设置指定变量字符串数值
        ''' </summary>
        ''' <param name="id">入参：变量id</param>
        ''' <param name="value">入参：待更新数值</param>
        ''' <returns>错误代码</returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_set_variable_string", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_set_variable_string(ByVal id As UInt64, ByVal value As String) As Int32
        End Function

        ''' <summary>
        ''' 获取指定变量运动坐标
        ''' </summary>
        ''' <param name="id">入参：变量id</param>
        ''' <param name="pMotionCoords">出参：YD_MotionCoords类型变量</param>
        ''' <param name="timestamp">出参：最后更新时间，可选</param>
        ''' <returns>错误代码</returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_get_variable_motion_coords", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_get_variable_motion_coords(ByVal id As UInt64, ByRef pMotionCoords As YD_MotionCoords, Optional ByRef timestamp As UInt64 = Nothing) As Int32
        End Function

        ''' <summary>
        ''' 设置指定变量运动坐标
        ''' </summary>
        ''' <param name="id">入参：变量id</param>
        ''' <param name="pMotionCoords">入参：YD_MotionCoords类型变量</param>
        ''' <returns>错误代码</returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_set_variable_motion_coords", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_set_variable_motion_coords(ByVal id As UInt64, ByRef pMotionCoords As YD_MotionCoords) As Int32
        End Function

        ''' <summary>
        ''' 获取指定id的DI输入
        ''' </summary>
        ''' <param name="card"></param>
        ''' <param name="type"></param>
        ''' <param name="index"></param>
        ''' <param name="pDIInfo"></param>
        ''' <returns></returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_get_digital_input_by_id", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_get_digital_input_by_id(ByVal card As UInt16, ByVal type As UInt16, ByVal index As UInt16, ByRef pDIInfo As YD_IOInfo) As Int32
        End Function

        ''' <summary>
        ''' 获取指定名称的DI输入
        ''' </summary>
        ''' <param name="name">入参：DI名称</param>
        ''' <param name="pDIInfo">出参：YD_IOInfo型引用</param>
        ''' <returns>错误代码</returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_get_digital_input_by_name", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_get_digital_input_by_name(ByVal name As String, ByRef pDIInfo As YD_IOInfo) As Int32
        End Function

        ''' <summary>
        ''' 获取DI输入状态
        ''' </summary>
        ''' <param name="card"></param>
        ''' <param name="type"></param>
        ''' <param name="index"></param>
        ''' <param name="value"></param>
        ''' <param name="timestamp"></param>
        ''' <returns></returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_get_digital_input_status", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_get_digital_input_status(ByVal card As UInt16, ByVal type As UInt16, ByVal index As UInt16, ByRef value As Boolean, Optional ByRef timestamp As UInt64 = Nothing) As Int32
        End Function

        ''' <summary>
        ''' 获取指定id的DO输出
        ''' </summary>
        ''' <param name="card"></param>
        ''' <param name="type"></param>
        ''' <param name="index"></param>
        ''' <param name="pDOInfo"></param>
        ''' <returns></returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_get_digital_output_by_id", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_get_digital_output_by_id(ByVal card As UInt16, ByVal type As UInt16, ByVal index As UInt16, ByRef pDOInfo As YD_IOInfo) As Int32
        End Function

        ''' <summary>
        ''' 获取指定名称的DO输出
        ''' </summary>
        ''' <param name="name">入参：DO名称</param>
        ''' <param name="pDOInfo">出参：YD_IOInfo引用</param>
        ''' <returns>错误代码</returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_get_digital_output_by_name", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_get_digital_output_by_name(ByVal name As String, ByRef pDOInfo As YD_IOInfo) As Int32
        End Function

        ''' <summary>
        ''' 获取DO输出状态
        ''' </summary>
        ''' <param name="card"></param>
        ''' <param name="type"></param>
        ''' <param name="index"></param>
        ''' <param name="value"></param>
        ''' <param name="timestamp"></param>
        ''' <returns></returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_get_digital_output_status", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_get_digital_output_status(ByVal card As UInt16, ByVal type As UInt16, ByVal index As UInt16, ByRef value As Boolean, Optional ByRef timestamp As UInt64 = Nothing) As Int32
        End Function

        ''' <summary>
        ''' 控制DO输出
        ''' </summary>
        ''' <param name="card"></param>
        ''' <param name="type"></param>
        ''' <param name="index"></param>
        ''' <param name="value"></param>
        ''' <param name="timeout"></param>
        ''' <returns></returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_set_digital_output_status", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_set_digital_output_status(ByVal card As UInt16, ByVal type As UInt16, ByVal index As UInt16, ByVal value As Boolean, Optional ByVal timeout As UInt32 = 3000) As Int32
        End Function

        ''' <summary>
        ''' 获取指定id的运动轴
        ''' </summary>
        ''' <param name="card">入参：卡序号</param>
        ''' <param name="axis">入参：轴序号</param>
        ''' <param name="pAxisInfo">出参：YD_AxisInfo引用</param>
        ''' <returns>错误代码</returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_get_axis_by_id", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_get_axis_by_id(ByVal card As UInt16, ByVal axis As UInt16, ByRef pAxisInfo As YD_AxisInfo) As Int32
        End Function

        ''' <summary>
        ''' 获取指定名称的运动轴
        ''' </summary>
        ''' <param name="name">入参：轴名称</param>
        ''' <param name="pAxisInfo">出参：YD_AxisInfo引用</param>
        ''' <returns>错误代码</returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_get_axis_by_name", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_get_axis_by_name(ByVal name As String, ByRef pAxisInfo As YD_AxisInfo) As Int32
        End Function

        ''' <summary>
        ''' 指定轴打开使能
        ''' </summary>
        ''' <param name="card">入参：卡序号</param>
        ''' <param name="axis">入参：轴序号</param>
        ''' <param name="timeout">入参：可选超时时间，单位：毫秒</param>
        ''' <returns>错误代码</returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_enable_axis", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_enable_axis(ByVal card As UInt16, ByVal axis As UInt16, Optional ByVal timeout As UInt32 = 3000) As Int32
        End Function

        ''' <summary>
        ''' 指定轴关闭使能
        ''' </summary>
        ''' <param name="card">入参：卡序号</param>
        ''' <param name="axis">入参：轴序号</param>
        ''' <param name="timeout">入参：可选超时时间，单位：毫秒</param>
        ''' <returns>错误代码</returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_disable_axis", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_disable_axis(ByVal card As UInt16, ByVal axis As UInt16, Optional ByVal timeout As UInt32 = 3000) As Int32
        End Function

        ''' <summary>
        ''' 指定轴报警清除
        ''' </summary>
        ''' <param name="card">入参：卡序号</param>
        ''' <param name="axis">入参：轴序号</param>
        ''' <param name="timeout">入参：可选超时时间，单位：毫秒</param>
        ''' <returns>错误代码</returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_clear_axis_alarm", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_clear_axis_alarm(ByVal card As UInt16, ByVal axis As UInt16, Optional ByVal timeout As UInt32 = 3000) As Int32
        End Function

        ''' <summary>
        ''' 指定轴位置清零
        ''' </summary>
        ''' <param name="card">入参：卡序号</param>
        ''' <param name="axis">入参：轴序号</param>
        ''' <param name="timeout">入参：可选超时时间，单位：毫秒</param>
        ''' <returns>错误代码</returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_zero_axis_position", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_zero_axis_position(ByVal card As UInt16, ByVal axis As UInt16, Optional ByVal timeout As UInt32 = 3000) As Int32
        End Function

        ''' <summary>
        ''' 获取指定轴状态
        ''' </summary>
        ''' <param name="card">入参：卡序号</param>
        ''' <param name="axis">入参：轴序号</param>
        ''' <param name="pAxisStates">出参：YD_AxisStates型引用</param>
        ''' <returns>错误代码</returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_get_axis_states", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_get_axis_states(ByVal card As UInt16, ByVal axis As UInt16, ByRef pAxisStates As YD_AxisStates) As Int32
        End Function

        ''' <summary>
        ''' 启动指定轴指定轴回零运动
        ''' </summary>
        ''' <param name="card">入参：卡序号</param>
        ''' <param name="axis">入参：轴序号</param>
        ''' <param name="timeout">入参：可选超时时间，单位：毫秒</param>
        ''' <returns>错误代码</returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_start_axis_home_move", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_start_axis_home_move(ByVal card As UInt16, ByVal axis As UInt16, Optional ByVal timeout As UInt32 = 3000) As Int32
        End Function

        ''' <summary>
        ''' 启动指定轴绝对运动
        ''' </summary>
        ''' <param name="card">入参：卡序号</param>
        ''' <param name="axis">入参：轴序号</param>
        ''' <param name="position">入参：目标位置</param>
        ''' <param name="velocity">入参：运动速度</param>
        ''' <param name="timeout">入参：可选超时时间，单位：毫秒</param>
        ''' <returns>错误代码</returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_start_axis_absolute_move", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_start_axis_absolute_move(ByVal card As UInt16, ByVal axis As UInt16, ByVal position As Double, ByVal velocity As Double, Optional ByVal timeout As UInt32 = 3000) As Int32
        End Function

        ''' <summary>
        ''' 启动指定轴相对运动
        ''' </summary>
        ''' <param name="card">入参：卡序号</param>
        ''' <param name="axis">入参：轴序号</param>
        ''' <param name="distance">入参：运动距离</param>
        ''' <param name="velocity">入参：运动速度</param>
        ''' <param name="direction">入参：运动方向</param>
        ''' <param name="timeout">入参：可选超时时间，单位：毫秒</param>
        ''' <returns>错误代码</returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_start_axis_relative_move", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_start_axis_relative_move(ByVal card As UInt16, ByVal axis As UInt16, ByVal distance As Double, ByVal velocity As Double, ByVal direction As Byte, Optional ByVal timeout As UInt32 = 3000) As Int32
        End Function

        ''' <summary>
        ''' 启动指定轴Jog运动
        ''' </summary>
        ''' <param name="card">入参：卡序号</param>
        ''' <param name="axis">入参：轴序号</param>
        ''' <param name="velocity">入参：运动速度</param>
        ''' <param name="direction">入参：运动方向</param>
        ''' <param name="timeout">入参：可选超时时间，单位：毫秒</param>
        ''' <returns>错误代码</returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_start_axis_jog_move", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_start_axis_jog_move(ByVal card As UInt16, ByVal axis As UInt16, ByVal velocity As Double, ByVal direction As Byte, Optional ByVal timeout As UInt32 = 3000) As Int32
        End Function

        ''' <summary>
        ''' 启动多轴运动
        ''' </summary>
        ''' <param name="card">入参：卡序号</param>
        ''' <param name="axis">入参：轴序号</param>
        ''' <param name="pMotionCoords">入参：YD_MotionCoords型引用</param>
        ''' <param name="timeout">入参：可选超时时间，单位：毫秒</param>
        ''' <returns>错误代码</returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_start_multi_axis_moves", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_start_multi_axis_moves(ByRef pMotionCoords As YD_MotionCoords, Optional ByVal timeout As UInt32 = 3000) As Int32
        End Function

        ''' <summary>
        ''' 停止指定轴运动
        ''' </summary>
        ''' <param name="card">入参：卡序号</param>
        ''' <param name="axis">入参：轴序号</param>
        ''' <param name="urgent">入参：是否急停</param>
        ''' <param name="timeout">入参：可选超时时间，单位：毫秒</param>
        ''' <returns>错误代码</returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_stop_axis_move", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_stop_axis_move(ByVal card As UInt16, ByVal axis As UInt16, ByVal urgent As Boolean, Optional ByVal timeout As UInt32 = 3000) As Int32
        End Function

        ''' <summary>
        ''' 获取指定轴驱动报警标志
        ''' </summary>
        ''' <param name="card"></param>
        ''' <param name="axis"></param>
        ''' <param name="flag"></param>
        ''' <returns></returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_get_axis_driver_alarm_flag", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_get_axis_driver_alarm_flag(ByVal card As UInt16, ByVal axis As UInt16, ByRef flag As Boolean) As Int32
        End Function

        ''' <summary>
        ''' 获取跟随误差标志
        ''' </summary>
        ''' <param name="card"></param>
        ''' <param name="axis"></param>
        ''' <param name="flag"></param>
        ''' <returns></returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_get_axis_follow_error_flag", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_get_axis_follow_error_flag(ByVal card As UInt16, ByVal axis As UInt16, ByRef flag As Boolean) As Int32
        End Function

        ''' <summary>
        ''' 获取正向限位标志
        ''' </summary>
        ''' <param name="card"></param>
        ''' <param name="axis"></param>
        ''' <param name="flag"></param>
        ''' <returns></returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_get_axis_positive_limit_flag", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_get_axis_positive_limit_flag(ByVal card As UInt16, ByVal axis As UInt16, ByRef flag As Boolean) As Int32
        End Function

        ''' <summary>
        ''' 获取负向限位标志
        ''' </summary>
        ''' <param name="card"></param>
        ''' <param name="axis"></param>
        ''' <param name="flag"></param>
        ''' <returns></returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_get_axis_negative_limit_flag", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_get_axis_negative_limit_flag(ByVal card As UInt16, ByVal axis As UInt16, ByRef flag As Boolean) As Int32
        End Function

        ''' <summary>
        ''' 获取平滑停止标志
        ''' </summary>
        ''' <param name="card"></param>
        ''' <param name="axis"></param>
        ''' <param name="flag"></param>
        ''' <returns></returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_get_axis_smooth_stop_flag", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_get_axis_smooth_stop_flag(ByVal card As UInt16, ByVal axis As UInt16, ByRef flag As Boolean) As Int32
        End Function

        ''' <summary>
        ''' 获取紧急停止标志
        ''' </summary>
        ''' <param name="card"></param>
        ''' <param name="axis"></param>
        ''' <param name="flag"></param>
        ''' <returns></returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_get_axis_urgent_stop_flag", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_get_axis_urgent_stop_flag(ByVal card As UInt16, ByVal axis As UInt16, ByRef flag As Boolean) As Int32
        End Function

        ''' <summary>
        ''' 获取伺服使能标志
        ''' </summary>
        ''' <param name="card"></param>
        ''' <param name="axis"></param>
        ''' <param name="flag"></param>
        ''' <returns></returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_get_axis_servo_on_flag", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_get_axis_servo_on_flag(ByVal card As UInt16, ByVal axis As UInt16, ByRef flag As Boolean) As Int32
        End Function

        ''' <summary>
        ''' 获取规划运动标志
        ''' </summary>
        ''' <param name="card"></param>
        ''' <param name="axis"></param>
        ''' <param name="flag"></param>
        ''' <returns></returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_get_axis_profile_move_flag", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_get_axis_profile_move_flag(ByVal card As UInt16, ByVal axis As UInt16, ByRef flag As Boolean) As Int32
        End Function

        ''' <summary>
        ''' 获取电机到位标志
        ''' </summary>
        ''' <param name="card"></param>
        ''' <param name="axis"></param>
        ''' <param name="flag"></param>
        ''' <returns></returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_get_axis_motor_arrive_flag", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_get_axis_motor_arrive_flag(ByVal card As UInt16, ByVal axis As UInt16, ByRef flag As Boolean) As Int32
        End Function

        ''' <summary>
        ''' 获取原点信号标志
        ''' </summary>
        ''' <param name="card"></param>
        ''' <param name="axis"></param>
        ''' <param name="flag"></param>
        ''' <returns></returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_get_axis_home_signal_flag", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_get_axis_home_signal_flag(ByVal card As UInt16, ByVal axis As UInt16, ByRef flag As Boolean) As Int32
        End Function

        ''' <summary>
        ''' 获取回零状态标志
        ''' </summary>
        ''' <param name="card"></param>
        ''' <param name="axis"></param>
        ''' <param name="flag"></param>
        ''' <returns></returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_get_axis_home_moved_flag", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_get_axis_home_moved_flag(ByVal card As UInt16, ByVal axis As UInt16, ByRef flag As Boolean) As Int32
        End Function

        ''' <summary>
        ''' 获取运动模式
        ''' </summary>
        ''' <param name="card"></param>
        ''' <param name="axis"></param>
        ''' <param name="mode"></param>
        ''' <returns></returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_get_axis_profile_mode", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_get_axis_profile_mode(ByVal card As UInt16, ByVal axis As UInt16, ByRef mode As UInt32) As Int32
        End Function

        ''' <summary>
        ''' 获取目标位置
        ''' </summary>
        ''' <param name="card"></param>
        ''' <param name="axis"></param>
        ''' <param name="position"></param>
        ''' <returns></returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_get_axis_target_position", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_get_axis_target_position(ByVal card As UInt16, ByVal axis As UInt16, ByRef position As Double) As Int32
        End Function

        ''' <summary>
        ''' 获取目标速度
        ''' </summary>
        ''' <param name="card"></param>
        ''' <param name="axis"></param>
        ''' <param name="velocity"></param>
        ''' <returns></returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_get_axis_target_velocity", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_get_axis_target_velocity(ByVal card As UInt16, ByVal axis As UInt16, ByRef velocity As Double) As Int32
        End Function

        ''' <summary>
        ''' 获取规划位置
        ''' </summary>
        ''' <param name="card"></param>
        ''' <param name="axis"></param>
        ''' <param name="position"></param>
        ''' <returns></returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_get_axis_profile_position", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_get_axis_profile_position(ByVal card As UInt16, ByVal axis As UInt16, ByRef position As Double) As Int32
        End Function

        ''' <summary>
        ''' 获取规划速度
        ''' </summary>
        ''' <param name="card"></param>
        ''' <param name="axis"></param>
        ''' <param name="velocity"></param>
        ''' <returns></returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_get_axis_profile_velocity", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_get_axis_profile_velocity(ByVal card As UInt16, ByVal axis As UInt16, ByRef velocity As Double) As Int32
        End Function

        ''' <summary>
        ''' 获取编码器位置（反馈位置）
        ''' </summary>
        ''' <param name="card"></param>
        ''' <param name="axis"></param>
        ''' <param name="position"></param>
        ''' <returns></returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_get_axis_encoder_position", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_get_axis_encoder_position(ByVal card As UInt16, ByVal axis As UInt16, ByRef position As Double) As Int32
        End Function

        ''' <summary>
        ''' 获取编码器速度（反馈速度）
        ''' </summary>
        ''' <param name="card"></param>
        ''' <param name="axis"></param>
        ''' <param name="velocity"></param>
        ''' <returns></returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_get_axis_encoder_velocity", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_get_axis_encoder_velocity(ByVal card As UInt16, ByVal axis As UInt16, ByRef velocity As Double) As Int32
        End Function
		
		''' <summary>
		''' 获取回零状态
		''' </summary>
		''' <param name="card"></param>
		''' <param name="axis"></param>
		''' <param name="status"></param>
		''' <returns></returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_get_axis_home_move_status", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_get_axis_home_move_status(ByVal card As UInt16, ByVal axis As UInt16, ByRef status As Byte) As Int32 
		End Function
		
		''' <summary>
		''' 更新回零状态
		''' </summary>
		''' <param name="card"></param>
		''' <param name="axis"></param>
		''' <param name="status"></param>
		''' <returns></returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_set_axis_home_move_status", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_set_axis_home_move_status(ByVal card As UInt16, ByVal axis As UInt16, ByVal status As Byte) As Int32 
		End Function		
		
		''' <summary>
		''' 根据轴号获取运动轴回原点参数
		''' </summary>
		''' <param name="card"></param>
		''' <param name="axis"></param>
		''' <param name="pHomeConfig"></param>
		''' <returns></returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_get_axis_home_config_by_id", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
		Public Shared Function yd_get_axis_home_config_by_id(ByVal card As UInt16, ByVal axis As UInt16, ByRef pHomeConfig As YD_AxisHomeConfig)
		End Function

		''' <summary>
		''' 根据轴名称获取运动轴回原点参数
		''' </summary>
		''' <param name="name"></param>
		''' <param name="pHomeConfig"></param>
		''' <returns></returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_get_axis_home_config_by_name", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
		Public Shared Function yd_get_axis_home_config_by_name(ByVal name As String, ByRef pHomeConfig As YD_AxisHomeConfig)
		End Function

        ''' <summary>
        ''' 根据id获取气油缸信息
        ''' </summary>
        ''' <param name="id"></param>
        ''' <param name="pCylinderInfo"></param>
        ''' <returns></returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_get_cylinder_by_id", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_get_cylinder_by_id(ByVal id As UInt32, ByRef pCylinderInfo As YD_CylinderInfo) As Int32
        End Function

        ''' <summary>
        ''' 根据名称获取气油缸信息
        ''' </summary>
        ''' <param name="name"></param>
        ''' <param name="pCylinderInfo"></param>
        ''' <returns></returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_get_cylinder_by_name", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_get_cylinder_by_name(ByVal name As String, ByRef pCylinderInfo As YD_CylinderInfo) As Int32
        End Function

        ''' <summary>
        ''' 获取气油缸状态
        ''' </summary>
        ''' <param name="id"></param>
        ''' <param name="pCylinderStates"></param>
        ''' <returns></returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_get_cylinder_states", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_get_cylinder_states(ByVal id As UInt32, ByRef pCylinderStates As YD_CylinderStates) As Int32
        End Function

        ''' <summary>
        ''' 控制气油缸运动
        ''' </summary>
        ''' <param name="id"></param>
        ''' <param name="direction"></param>
        ''' <returns></returns>
        <DllImport(YD_MOTION_API_LIBRARY, EntryPoint:="yd_control_cylinder_move", CharSet:=CharSet.Ansi, CallingConvention:=CallingConvention.StdCall)>
        Public Shared Function yd_control_cylinder_move(ByVal id As UInt32, ByVal direction As Byte, Optional ByVal timeout As UInt32 = 3000) As Int32
        End Function
    End Class

    '控制器
    Public Class YDController
        '获取状态
        Public Shared Function GetStatus() As Byte
            Dim ucStatus As Byte = 0
            If CMotionApi.YD_API_ERROR_SUCCESS <> CMotionApi.yd_get_controller_status(ucStatus) Then
            End If
            Return ucStatus
        End Function

        '获取模式
        Public Shared Function GetMode() As Byte
            Dim ucMode As Byte = 0
            If CMotionApi.YD_API_ERROR_SUCCESS <> CMotionApi.yd_get_controller_mode(ucMode) Then
            End If
            Return ucMode
        End Function

        '启动
        Public Shared Function Start(Optional ByVal uiTimeout As UInt32 = 3000) As Boolean
            If CMotionApi.YD_API_ERROR_SUCCESS <> CMotionApi.yd_start_controller(uiTimeout) Then
                Return False
            End If
            Return True
        End Function

        '停止
        Public Shared Function Terminate(Optional ByVal uiTimeout As UInt32 = 3000) As Boolean
            If CMotionApi.YD_API_ERROR_SUCCESS <> CMotionApi.yd_stop_controller(uiTimeout) Then
                Return False
            End If
            Return True
        End Function

        '暂停
        Public Shared Function Pause(Optional ByVal uiTimeout As UInt32 = 3000) As Boolean
            If CMotionApi.YD_API_ERROR_SUCCESS <> CMotionApi.yd_pause_controller(uiTimeout) Then
                Return False
            End If
            Return True
        End Function

        '恢复
        Public Shared Function Restore(Optional ByVal uiTimeout As UInt32 = 3000) As Boolean
            If CMotionApi.YD_API_ERROR_SUCCESS <> CMotionApi.yd_restore_controller(uiTimeout) Then
                Return False
            End If
            Return True
        End Function

        '切换手动模式
        Public Shared Function SwitchManualMode(Optional ByVal uiTimeout As UInt32 = 3000) As Boolean
            If CMotionApi.YD_API_ERROR_SUCCESS <> CMotionApi.yd_switch_controller_to_manual_mode(uiTimeout) Then
                Return False
            End If
            Return True
        End Function

        '切换自动模式
        Public Shared Function SwitchAutomaticMode(Optional ByVal uiTimeout As UInt32 = 3000) As Boolean
            If CMotionApi.YD_API_ERROR_SUCCESS <> CMotionApi.yd_switch_controller_to_automatic_mode(uiTimeout) Then
                Return False
            End If
            Return True
        End Function
    End Class

    '只读变量类
    Public Class YDROVariable(Of T)
        '成员变量
        Private m_ullId As UInt64 = 0
        Private m_strName As String = ""
        Private m_maxValue As T
        Private m_minValue As T
        Private m_ucValueType As Byte = 0
        Private m_ullTimestamp As UInt64 = 0
        '带参数构造函数
        Public Sub New(ByVal ullId As UInt64, ByVal strName As String, ByVal maxValue As T, ByVal minValue As T)
            Me.m_ullId = ullId
            Me.m_strName = strName
            Me.m_maxValue = maxValue
            Me.m_minValue = minValue
            If TypeOf m_maxValue Is System.Boolean Then
                Me.m_ucValueType = CMotionApi.YD_API_VALUE_TYPE_BOOL
            ElseIf TypeOf m_maxValue Is System.Byte Then
                Me.m_ucValueType = CMotionApi.YD_API_VALUE_TYPE_UINT8
            ElseIf TypeOf m_maxValue Is System.SByte Then
                Me.m_ucValueType = CMotionApi.YD_API_VALUE_TYPE_INT8
            ElseIf TypeOf m_maxValue Is System.UInt16 Then
                Me.m_ucValueType = CMotionApi.YD_API_VALUE_TYPE_UINT16
            ElseIf TypeOf m_maxValue Is System.Int16 Then
                Me.m_ucValueType = CMotionApi.YD_API_VALUE_TYPE_INT16
            ElseIf TypeOf m_maxValue Is System.UInt32 Then
                Me.m_ucValueType = CMotionApi.YD_API_VALUE_TYPE_UINT32
            ElseIf TypeOf m_maxValue Is System.Int32 Then
                Me.m_ucValueType = CMotionApi.YD_API_VALUE_TYPE_INT32
            ElseIf TypeOf m_maxValue Is System.UInt64 Then
                Me.m_ucValueType = CMotionApi.YD_API_VALUE_TYPE_UINT64
            ElseIf TypeOf m_maxValue Is System.Int64 Then
                Me.m_ucValueType = CMotionApi.YD_API_VALUE_TYPE_INT64
            ElseIf TypeOf m_maxValue Is System.Single Then
                Me.m_ucValueType = CMotionApi.YD_API_VALUE_TYPE_FLOAT
            ElseIf TypeOf m_maxValue Is System.Double Then
                Me.m_ucValueType = CMotionApi.YD_API_VALUE_TYPE_DOUBLE
            ElseIf TypeOf m_maxValue Is System.String Then
                Me.m_ucValueType = CMotionApi.YD_API_VALUE_TYPE_STRING
            ElseIf TypeOf m_maxValue Is CMotionApi.YD_MotionCoords Then
                Me.m_ucValueType = CMotionApi.YD_API_VALUE_TYPE_MOTION_COORDS
            End If
        End Sub
        Public Sub New(ByVal ullId As UInt64, ByVal strName As String, ByVal ucValueType As Byte)
            Me.m_ullId = ullId
            Me.m_strName = strName
            Me.m_ucValueType = ucValueType
        End Sub
        '获取数值类型
        Public Function GetValueType() As Byte
            Return Me.m_ucValueType
        End Function
        '获取数值
        Public Function GetValue() As T
            If CMotionApi.YD_API_VALUE_TYPE_BOOL = Me.m_ucValueType Then
                Dim bValue As Boolean = False
                If CMotionApi.YD_API_ERROR_SUCCESS <> CMotionApi.yd_get_variable_boolean(Me.m_ullId, bValue, Me.m_ullTimestamp) Then
                End If
                Return CObj(bValue)
            End If
            If CMotionApi.YD_API_VALUE_TYPE_UINT8 = Me.m_ucValueType Then
                Dim ucValue As Byte = 0
                If CMotionApi.YD_API_ERROR_SUCCESS <> CMotionApi.yd_get_variable_uint8(Me.m_ullId, ucValue, Me.m_ullTimestamp) Then
                End If
                Return CObj(ucValue)
            End If
            If CMotionApi.YD_API_VALUE_TYPE_INT8 = Me.m_ucValueType Then
                Dim cValue As SByte = 0
                If CMotionApi.YD_API_ERROR_SUCCESS <> CMotionApi.yd_get_variable_int8(Me.m_ullId, cValue, Me.m_ullTimestamp) Then
                End If
                Return CObj(cValue)
            End If
            If CMotionApi.YD_API_VALUE_TYPE_UINT16 = Me.m_ucValueType Then
                Dim usValue As UInt16 = 0
                If CMotionApi.YD_API_ERROR_SUCCESS <> CMotionApi.yd_get_variable_uint16(Me.m_ullId, usValue, Me.m_ullTimestamp) Then
                End If
                Return CObj(usValue)
            End If
            If CMotionApi.YD_API_VALUE_TYPE_INT16 = Me.m_ucValueType Then
                Dim sValue As Int16 = 0
                If CMotionApi.YD_API_ERROR_SUCCESS <> CMotionApi.yd_get_variable_int16(Me.m_ullId, sValue, Me.m_ullTimestamp) Then
                End If
                Return CObj(sValue)
            End If
            If CMotionApi.YD_API_VALUE_TYPE_UINT32 = Me.m_ucValueType Then
                Dim uiValue As UInt32 = 0
                If CMotionApi.YD_API_ERROR_SUCCESS <> CMotionApi.yd_get_variable_uint32(Me.m_ullId, uiValue, Me.m_ullTimestamp) Then
                End If
                Return CObj(uiValue)
            End If
            If CMotionApi.YD_API_VALUE_TYPE_INT32 = Me.m_ucValueType Then
                Dim iValue As Int32 = 0
                If CMotionApi.YD_API_ERROR_SUCCESS <> CMotionApi.yd_get_variable_int32(Me.m_ullId, iValue, Me.m_ullTimestamp) Then
                End If
                Return CObj(iValue)
            End If
            If CMotionApi.YD_API_VALUE_TYPE_UINT64 = Me.m_ucValueType Then
                Dim ullValue As UInt64 = 0
                If CMotionApi.YD_API_ERROR_SUCCESS <> CMotionApi.yd_get_variable_uint64(Me.m_ullId, ullValue, Me.m_ullTimestamp) Then
                End If
                Return CObj(ullValue)
            End If
            If CMotionApi.YD_API_VALUE_TYPE_INT64 = Me.m_ucValueType Then
                Dim llValue As Int64 = 0
                If CMotionApi.YD_API_ERROR_SUCCESS <> CMotionApi.yd_get_variable_int64(Me.m_ullId, llValue, Me.m_ullTimestamp) Then
                End If
                Return CObj(llValue)
            End If
            If CMotionApi.YD_API_VALUE_TYPE_FLOAT = Me.m_ucValueType Then
                Dim fValue As Single = 0
                If CMotionApi.YD_API_ERROR_SUCCESS <> CMotionApi.yd_get_variable_float(Me.m_ullId, fValue, Me.m_ullTimestamp) Then
                End If
                Return CObj(fValue)
            End If
            If CMotionApi.YD_API_VALUE_TYPE_DOUBLE = Me.m_ucValueType Then
                Dim dblValue As Double = 0
                If CMotionApi.YD_API_ERROR_SUCCESS <> CMotionApi.yd_get_variable_double(Me.m_ullId, dblValue, Me.m_ullTimestamp) Then
                End If
                Return CObj(dblValue)
            End If
            If CMotionApi.YD_API_VALUE_TYPE_STRING = Me.m_ucValueType Then
                Dim strValue As StringBuilder = New StringBuilder(CMotionApi.YD_MAX_VALUE_LENGTH)
                If CMotionApi.YD_API_ERROR_SUCCESS <> CMotionApi.yd_get_variable_string(Me.m_ullId, strValue, CMotionApi.YD_MAX_VALUE_LENGTH, Me.m_ullTimestamp) Then
                End If
                Return CObj(strValue.ToString())
            End If
            If CMotionApi.YD_API_VALUE_TYPE_MOTION_COORDS = Me.m_ucValueType Then
                Dim coordValue As CMotionApi.YD_MotionCoords = New CMotionApi.YD_MotionCoords()
                If CMotionApi.YD_API_ERROR_SUCCESS <> CMotionApi.yd_get_variable_motion_coords(Me.m_ullId, coordValue, Me.m_ullTimestamp) Then
                End If
                Return CObj(coordValue)
            End If
            Dim ucDefault As Byte = 0
            Return CObj(ucDefault)
        End Function
    End Class
	

    '可读可写变量类
    Public Class YDRWVariable(Of T)
        '成员变量
        Private m_ullId As UInt64 = 0
        Private m_strName As String = ""
        Private m_maxValue As T
        Private m_minValue As T
        Private m_ucValueType As Byte = 0
        Private m_ullTimestamp As UInt64 = 0
        '带参数构造函数
        Public Sub New(ByVal ullId As UInt64, ByVal strName As String, ByVal maxValue As T, ByVal minValue As T)
            Me.m_ullId = ullId
            Me.m_strName = strName
            Me.m_maxValue = maxValue
            Me.m_minValue = minValue
            If TypeOf m_maxValue Is System.Boolean Then
                Me.m_ucValueType = CMotionApi.YD_API_VALUE_TYPE_BOOL
            ElseIf TypeOf m_maxValue Is System.Byte Then
                Me.m_ucValueType = CMotionApi.YD_API_VALUE_TYPE_UINT8
            ElseIf TypeOf m_maxValue Is System.SByte Then
                Me.m_ucValueType = CMotionApi.YD_API_VALUE_TYPE_INT8
            ElseIf TypeOf m_maxValue Is System.UInt16 Then
                Me.m_ucValueType = CMotionApi.YD_API_VALUE_TYPE_UINT16
            ElseIf TypeOf m_maxValue Is System.Int16 Then
                Me.m_ucValueType = CMotionApi.YD_API_VALUE_TYPE_INT16
            ElseIf TypeOf m_maxValue Is System.UInt32 Then
                Me.m_ucValueType = CMotionApi.YD_API_VALUE_TYPE_UINT32
            ElseIf TypeOf m_maxValue Is System.Int32 Then
                Me.m_ucValueType = CMotionApi.YD_API_VALUE_TYPE_INT32
            ElseIf TypeOf m_maxValue Is System.UInt64 Then
                Me.m_ucValueType = CMotionApi.YD_API_VALUE_TYPE_UINT64
            ElseIf TypeOf m_maxValue Is System.Int64 Then
                Me.m_ucValueType = CMotionApi.YD_API_VALUE_TYPE_INT64
            ElseIf TypeOf m_maxValue Is System.Single Then
                Me.m_ucValueType = CMotionApi.YD_API_VALUE_TYPE_FLOAT
            ElseIf TypeOf m_maxValue Is System.Double Then
                Me.m_ucValueType = CMotionApi.YD_API_VALUE_TYPE_DOUBLE
            ElseIf TypeOf m_maxValue Is System.String Then
                Me.m_ucValueType = CMotionApi.YD_API_VALUE_TYPE_STRING
            ElseIf TypeOf m_maxValue Is CMotionApi.YD_MotionCoords Then
                Me.m_ucValueType = CMotionApi.YD_API_VALUE_TYPE_MOTION_COORDS
            End If
        End Sub
        Public Sub New(ByVal ullId As UInt64, ByVal strName As String, ByVal ucValueType As Byte)
            Me.m_ullId = ullId
            Me.m_strName = strName
            Me.m_ucValueType = ucValueType
        End Sub
        '获取数值类型
        Public Function GetValueType() As Byte
            Return Me.m_ucValueType
        End Function
        '最大值
        Public Function GetMaxValue() As T
            Return Me.m_maxValue
        End Function
        '最小值
        Public Function GetMinValue() As T
            Return Me.m_minValue
        End Function
        '获取数值
        Public Function GetValue() As T
            If CMotionApi.YD_API_VALUE_TYPE_BOOL = Me.m_ucValueType Then
                Dim bValue As Boolean = False
                If CMotionApi.YD_API_ERROR_SUCCESS <> CMotionApi.yd_get_variable_boolean(Me.m_ullId, bValue, Me.m_ullTimestamp) Then
                End If
                Return CObj(bValue)
            End If
            If CMotionApi.YD_API_VALUE_TYPE_UINT8 = Me.m_ucValueType Then
                Dim ucValue As Byte = 0
                If CMotionApi.YD_API_ERROR_SUCCESS <> CMotionApi.yd_get_variable_uint8(Me.m_ullId, ucValue, Me.m_ullTimestamp) Then
                End If
                Return CObj(ucValue)
            End If
            If CMotionApi.YD_API_VALUE_TYPE_INT8 = Me.m_ucValueType Then
                Dim cValue As SByte = 0
                If CMotionApi.YD_API_ERROR_SUCCESS <> CMotionApi.yd_get_variable_int8(Me.m_ullId, cValue, Me.m_ullTimestamp) Then
                End If
                Return CObj(cValue)
            End If
            If CMotionApi.YD_API_VALUE_TYPE_UINT16 = Me.m_ucValueType Then
                Dim usValue As UInt16 = 0
                If CMotionApi.YD_API_ERROR_SUCCESS <> CMotionApi.yd_get_variable_uint16(Me.m_ullId, usValue, Me.m_ullTimestamp) Then
                End If
                Return CObj(usValue)
            End If
            If CMotionApi.YD_API_VALUE_TYPE_INT16 = Me.m_ucValueType Then
                Dim sValue As Int16 = 0
                If CMotionApi.YD_API_ERROR_SUCCESS <> CMotionApi.yd_get_variable_int16(Me.m_ullId, sValue, Me.m_ullTimestamp) Then
                End If
                Return CObj(sValue)
            End If
            If CMotionApi.YD_API_VALUE_TYPE_UINT32 = Me.m_ucValueType Then
                Dim uiValue As UInt32 = 0
                If CMotionApi.YD_API_ERROR_SUCCESS <> CMotionApi.yd_get_variable_uint32(Me.m_ullId, uiValue, Me.m_ullTimestamp) Then
                End If
                Return CObj(uiValue)
            End If
            If CMotionApi.YD_API_VALUE_TYPE_INT32 = Me.m_ucValueType Then
                Dim iValue As Int32 = 0
                If CMotionApi.YD_API_ERROR_SUCCESS <> CMotionApi.yd_get_variable_int32(Me.m_ullId, iValue, Me.m_ullTimestamp) Then
                End If
                Return CObj(iValue)
            End If
            If CMotionApi.YD_API_VALUE_TYPE_UINT64 = Me.m_ucValueType Then
                Dim ullValue As UInt64 = 0
                If CMotionApi.YD_API_ERROR_SUCCESS <> CMotionApi.yd_get_variable_uint64(Me.m_ullId, ullValue, Me.m_ullTimestamp) Then
                End If
                Return CObj(ullValue)
            End If
            If CMotionApi.YD_API_VALUE_TYPE_INT64 = Me.m_ucValueType Then
                Dim llValue As Int64 = 0
                If CMotionApi.YD_API_ERROR_SUCCESS <> CMotionApi.yd_get_variable_int64(Me.m_ullId, llValue, Me.m_ullTimestamp) Then
                End If
                Return CObj(llValue)
            End If
            If CMotionApi.YD_API_VALUE_TYPE_FLOAT = Me.m_ucValueType Then
                Dim fValue As Single = 0
                If CMotionApi.YD_API_ERROR_SUCCESS <> CMotionApi.yd_get_variable_float(Me.m_ullId, fValue, Me.m_ullTimestamp) Then
                End If
                Return CObj(fValue)
            End If
            If CMotionApi.YD_API_VALUE_TYPE_DOUBLE = Me.m_ucValueType Then
                Dim dblValue As Double = 0
                If CMotionApi.YD_API_ERROR_SUCCESS <> CMotionApi.yd_get_variable_double(Me.m_ullId, dblValue, Me.m_ullTimestamp) Then
                End If
                Return CObj(dblValue)
            End If
            If CMotionApi.YD_API_VALUE_TYPE_STRING = Me.m_ucValueType Then
                Dim strValue As StringBuilder = New StringBuilder(CMotionApi.YD_MAX_VALUE_LENGTH)
                If CMotionApi.YD_API_ERROR_SUCCESS <> CMotionApi.yd_get_variable_string(Me.m_ullId, strValue, CMotionApi.YD_MAX_VALUE_LENGTH, Me.m_ullTimestamp) Then
                End If
                Return CObj(strValue.ToString())
            End If
            If CMotionApi.YD_API_VALUE_TYPE_MOTION_COORDS = Me.m_ucValueType Then
                Dim coordValue As CMotionApi.YD_MotionCoords = New CMotionApi.YD_MotionCoords()
                If CMotionApi.YD_API_ERROR_SUCCESS <> CMotionApi.yd_get_variable_motion_coords(Me.m_ullId, coordValue, Me.m_ullTimestamp) Then
                End If
                Return CObj(coordValue)
            End If
            Dim ucDefault As Byte = 0
            Return CObj(ucDefault)
        End Function
        '更新数值
        Public Function SetValue(ByVal value As T) As Boolean
            If CMotionApi.YD_API_VALUE_TYPE_BOOL = Me.m_ucValueType Then
                Dim bValue As Boolean = CType(CObj(value), Boolean)
                If CMotionApi.YD_API_ERROR_SUCCESS <> CMotionApi.yd_set_variable_boolean(Me.m_ullId, bValue) Then
                    Return False
                End If
                Return True
            End If
            If CMotionApi.YD_API_VALUE_TYPE_UINT8 = Me.m_ucValueType Then
                Dim ucValue As Byte = CType(CObj(value), Byte)
                If CMotionApi.YD_API_ERROR_SUCCESS <> CMotionApi.yd_set_variable_uint8(Me.m_ullId, ucValue) Then
                    Return False
                End If
                Return True
            End If
            If CMotionApi.YD_API_VALUE_TYPE_INT8 = Me.m_ucValueType Then
                Dim cValue As SByte = CType(CObj(value), SByte)
                If CMotionApi.YD_API_ERROR_SUCCESS <> CMotionApi.yd_set_variable_int8(Me.m_ullId, cValue) Then
                    Return False
                End If
                Return True
            End If
            If CMotionApi.YD_API_VALUE_TYPE_UINT16 = Me.m_ucValueType Then
                Dim usValue As UInt16 = CType(CObj(value), UInt16)
                If CMotionApi.YD_API_ERROR_SUCCESS <> CMotionApi.yd_set_variable_uint16(Me.m_ullId, usValue) Then
                    Return False
                End If
                Return True
            End If
            If CMotionApi.YD_API_VALUE_TYPE_INT16 = Me.m_ucValueType Then
                Dim sValue As Int16 = CType(CObj(value), Int16)
                If CMotionApi.YD_API_ERROR_SUCCESS <> CMotionApi.yd_set_variable_int16(Me.m_ullId, sValue) Then
                    Return False
                End If
                Return True
            End If
            If CMotionApi.YD_API_VALUE_TYPE_UINT32 = Me.m_ucValueType Then
                Dim uiValue As UInt32 = CType(CObj(value), UInt32)
                If CMotionApi.YD_API_ERROR_SUCCESS <> CMotionApi.yd_set_variable_uint32(Me.m_ullId, uiValue) Then
                    Return False
                End If
                Return True
            End If
            If CMotionApi.YD_API_VALUE_TYPE_INT32 = Me.m_ucValueType Then
                Dim iValue As Int32 = CType(CObj(value), Int32)
                If CMotionApi.YD_API_ERROR_SUCCESS <> CMotionApi.yd_set_variable_int32(Me.m_ullId, iValue) Then
                    Return False
                End If
                Return True
            End If
            If CMotionApi.YD_API_VALUE_TYPE_UINT64 = Me.m_ucValueType Then
                Dim ullValue As UInt64 = CType(CObj(value), UInt64)
                If CMotionApi.YD_API_ERROR_SUCCESS <> CMotionApi.yd_set_variable_uint64(Me.m_ullId, ullValue) Then
                    Return False
                End If
                Return True
            End If
            If CMotionApi.YD_API_VALUE_TYPE_INT64 = Me.m_ucValueType Then
                Dim llValue As Int64 = CType(CObj(value), Int64)
                If CMotionApi.YD_API_ERROR_SUCCESS <> CMotionApi.yd_set_variable_int64(Me.m_ullId, llValue) Then
                    Return False
                End If
                Return True
            End If
            If CMotionApi.YD_API_VALUE_TYPE_FLOAT = Me.m_ucValueType Then
                Dim fValue As Single = CType(CObj(value), Single)
                If CMotionApi.YD_API_ERROR_SUCCESS <> CMotionApi.yd_set_variable_float(Me.m_ullId, fValue) Then
                    Return False
                End If
                Return True
            End If
            If CMotionApi.YD_API_VALUE_TYPE_DOUBLE = Me.m_ucValueType Then
                Dim dblValue As Double = CType(CObj(value), Double)
                If CMotionApi.YD_API_ERROR_SUCCESS <> CMotionApi.yd_set_variable_double(Me.m_ullId, dblValue) Then
                    Return False
                End If
                Return True
            End If
            If CMotionApi.YD_API_VALUE_TYPE_STRING = Me.m_ucValueType Then
                Dim strValue As String = CType(CObj(value), String)
                If CMotionApi.YD_API_ERROR_SUCCESS <> CMotionApi.yd_set_variable_string(Me.m_ullId, strValue) Then
                    Return False
                End If
                Return True
            End If
            If CMotionApi.YD_API_VALUE_TYPE_MOTION_COORDS = Me.m_ucValueType Then
                Dim coordValue As CMotionApi.YD_MotionCoords = CType(CObj(value), CMotionApi.YD_MotionCoords)
                If CMotionApi.YD_API_ERROR_SUCCESS <> CMotionApi.yd_set_variable_motion_coords(Me.m_ullId, coordValue) Then
                    Return False
                End If
                Return True
            End If
            Return False
        End Function
    End Class

    '数字输入类
    Public Class YDDigitalInput
        '成员变量
        Private m_usCard As UInt16 = 0
        Private m_usType As UInt16 = 0
        Private m_usIndex As UInt16 = 0
        Private m_strName As String = ""
        Private m_ullTimestamp As UInt64 = 0
        '带参数构造函数
        Public Sub New(ByVal usCard As UInt16, ByVal usType As UInt16, ByVal usIndex As UInt16, ByVal strName As String)
            Me.m_usCard = usCard
            Me.m_usType = usType
            Me.m_usIndex = usIndex
            Me.m_strName = strName
        End Sub
        '获取状态
        Public Function GetStatus() As Boolean
            Dim bStatus As Boolean = False
            If CMotionApi.YD_API_ERROR_SUCCESS <> CMotionApi.yd_get_digital_input_status(Me.m_usCard, Me.m_usType, Me.m_usIndex, bStatus, Me.m_ullTimestamp) Then
            End If
            Return bStatus
        End Function
    End Class

    '数字输出类
    Public Class YDDigitalOutput
        '成员变量
        Private m_usCard As UInt16 = 0
        Private m_usType As UInt16 = 0
        Private m_usIndex As UInt16 = 0
        Private m_strName As String = ""
        Private m_ullTimestamp As UInt64 = 0
        '带参数构造函数
        Public Sub New(ByVal usCard As UInt16, ByVal usType As UInt16, ByVal usIndex As UInt16, ByVal strName As String)
            Me.m_usCard = usCard
            Me.m_usType = usType
            Me.m_usIndex = usIndex
            Me.m_strName = strName
        End Sub
        '获取状态
        Public Function GetStatus() As Boolean
            Dim bStatus As Boolean = False
            If CMotionApi.YD_API_ERROR_SUCCESS <> CMotionApi.yd_get_digital_output_status(Me.m_usCard, Me.m_usType, Me.m_usIndex, bStatus, Me.m_ullTimestamp) Then
            End If
            Return bStatus
        End Function
        '更新状态
        Public Function SetStatus(ByVal bStatus As Boolean) As Boolean
            If CMotionApi.YD_API_ERROR_SUCCESS <> CMotionApi.yd_set_digital_output_status(Me.m_usCard, Me.m_usType, Me.m_usIndex, bStatus) Then
                Return False
            End If
            Return True
        End Function
    End Class

    '运动轴
    Public Class YDAxis
        '成员变量
        Private m_usCard As UInt16 = 0
        Private m_usAxis As UInt16 = 0
        Private m_strName As String = ""
		Private m_homeConfig As CMotionApi.YD_AxisHomeConfig = New CMotionApi.YD_AxisHomeConfig()
        '带参数构造函数
        Public Sub New(ByVal usCard As UInt16, ByVal usAxis As UInt16, ByVal strName As String)
            Me.m_usCard = usCard
            Me.m_usAxis = usAxis
            Me.m_strName = strName
			CMotionApi.yd_get_axis_home_config_by_id(Me.m_usCard, Me.m_usAxis, Me.m_homeConfig)
        End Sub
		'获取卡号
		Public Function Card() As UInt16
			return Me.m_usCard
		End Function
		'获取轴号
		Public Function Axis() As UInt16
			return Me.m_usAxis
		End Function
		'获取名称
		Public Function Name() As String
			return Me.m_strName
		End Function
		'获取回原点参数
		Public Function GetHomeConfig() As CMotionApi.YD_AxisHomeConfig
			Return m_homeConfig
		End Function
		'获取到位误差
		Public Function GetArriveError() As Double
			return 0.02
		End Function
		'获取到位超时
		Public Function GetArriveTimeout() As UInt32
			return 2000
		End Function
		'获取正向限位DI状态
		Public Function GetPositiveLimitDI() As Boolean
			return this.m_diPositiveLimit.GetStatus()
		End Function
		'获取负向限位DI状态
		Public FunctionGetNegativeLimitDI() As Boolean
			return this.m_diNegativeLimit.GetStatus()
		End Function
		'获取驱动报警DI状态
		Public Function GetDriverAlarmDI() As Boolean
			return this.m_diDriverAlarm.GetStatus()
		End Function
		'获取原点信号DI状态
		Public Function GetHomeSignalDI() As Boolean
			return this.m_diHomeSignal.GetStatus()
		End Function
		'获取电机到位DI状态
		Public Function GetMotorArriveDI() As Boolean
			return this.m_diMotorArrive.GetStatus()
		End Function
        '使能轴
        Public Function Enable(Optional ByVal uiTimeout As UInt32 = 3000) As Boolean
            Dim iResult As Int32 = CMotionApi.yd_enable_axis(Me.m_usCard, Me.m_usAxis, uiTimeout)
            If CMotionApi.YD_API_ERROR_SUCCESS <> iResult Then
                Return False
            End If
            Return True
        End Function
        '禁用轴
        Public Function Disable(Optional ByVal uiTimeout As UInt32 = 3000) As Boolean
            Dim iResult As Int32 = CMotionApi.yd_disable_axis(Me.m_usCard, Me.m_usAxis, uiTimeout)
            If CMotionApi.YD_API_ERROR_SUCCESS <> iResult Then
                Return False
            End If
            Return True
        End Function
        '清除报警状态
        Public Function ClearAlarms(Optional ByVal uiTimeout As UInt32 = 3000) As Boolean
            Dim iResult As Int32 = CMotionApi.yd_clear_axis_alarm(Me.m_usCard, Me.m_usAxis, uiTimeout)
            If CMotionApi.YD_API_ERROR_SUCCESS <> iResult Then
                Return False
            End If
            Return True
        End Function
        '位置清零
        Public Function ZeroPosition(Optional ByVal uiTimeout As UInt32 = 3000) As Boolean
            Dim iResult As Int32 = CMotionApi.yd_zero_axis_position(Me.m_usCard, Me.m_usAxis, uiTimeout)
            If CMotionApi.YD_API_ERROR_SUCCESS <> iResult Then
                Return False
            End If
            Return True
        End Function
        '启动回零运动
        Public Function StartHomeMove(Optional ByVal uiTimeout As UInt32 = 3000) As Boolean
            Dim iResult As Int32 = CMotionApi.yd_start_axis_home_move(Me.m_usCard, Me.m_usAxis, uiTimeout)
            If CMotionApi.YD_API_ERROR_SUCCESS <> iResult Then
                Return False
            End If
            Return True
        End Function
        '启动绝对运动
        Public Function StartAbsoluteMove(ByVal dblPosition As Double, ByVal dblVelocity As Double, Optional ByVal uiTimeout As UInt32 = 3000) As Boolean
            Dim iResult As Int32 = CMotionApi.yd_start_axis_absolute_move(
                Me.m_usCard,
                Me.m_usAxis,
                dblPosition,
                dblVelocity,
                uiTimeout)
            If CMotionApi.YD_API_ERROR_SUCCESS <> iResult Then
                Return False
            End If
            Return True
        End Function
        '启动相对运动
        Public Function StartRelativeMove(ByVal dblDistance As Double, ByVal dblVelocity As Double, Optional ByVal uiTimeout As UInt32 = 3000) As Boolean
            Dim iResult As Int32 = CMotionApi.yd_start_axis_relative_move(
                Me.m_usCard,
                Me.m_usAxis,
                dblDistance,
                dblVelocity,
                IIf(dblDistance >= 0, CMotionApi.YD_API_MOVE_DIRECTION_POSITIVE, CMotionApi.YD_API_MOVE_DIRECTION_NEGATIVE),
                uiTimeout)
            If CMotionApi.YD_API_ERROR_SUCCESS <> iResult Then
                Return False
            End If
            Return True
        End Function
        '启动Jog运动
        Public Function StartJogMove(ByVal dblVelocity As Double, Optional ByVal uiTimeout As UInt32 = 3000) As Boolean
            Dim iResult As Int32 = CMotionApi.yd_start_axis_jog_move(
                Me.m_usCard,
                Me.m_usAxis,
                dblVelocity,
                IIf(dblVelocity >= 0, CMotionApi.YD_API_MOVE_DIRECTION_POSITIVE, CMotionApi.YD_API_MOVE_DIRECTION_NEGATIVE),
                uiTimeout)
            If CMotionApi.YD_API_ERROR_SUCCESS <> iResult Then
                Return False
            End If
            Return True
        End Function
        '停止运动
        Public Function StopMove(ByVal bUrgent As Boolean, Optional ByVal uiTimeout As UInt32 = 3000) As Boolean
            Dim iResult As Int32 = CMotionApi.yd_stop_axis_move(Me.m_usCard, Me.m_usAxis, bUrgent, uiTimeout)
            If CMotionApi.YD_API_ERROR_SUCCESS <> iResult Then
                Return False
            End If
            Return True
        End Function
        '是否规划运动中
        Public Function IsProfileMoving() As Boolean
            Dim bFlag As Boolean = False
            If CMotionApi.YD_API_ERROR_SUCCESS <> CMotionApi.yd_get_axis_profile_move_flag(Me.m_usCard, Me.m_usAxis, bFlag) Then
                Return False
            End If
            Return bFlag
        End Function
        '获取驱动报警标志
        Public Function GetDriverAlarmFlag() As Boolean
            Dim bFlag As Boolean = False
            If CMotionApi.YD_API_ERROR_SUCCESS <> CMotionApi.yd_get_axis_driver_alarm_flag(Me.m_usCard, Me.m_usAxis, bFlag) Then
                Return False
            End If
            Return bFlag
        End Function
        '获取跟随误差标志
        Public Function GetFollowErrorFlag() As Boolean
            Dim bFlag As Boolean = False
            If CMotionApi.YD_API_ERROR_SUCCESS <> CMotionApi.yd_get_axis_follow_error_flag(Me.m_usCard, Me.m_usAxis, bFlag) Then
                Return False
            End If
            Return bFlag
        End Function
        '获取正向限位标志
        Public Function GetPositiveLimitFlag() As Boolean
            Dim bFlag As Boolean = False
            If CMotionApi.YD_API_ERROR_SUCCESS <> CMotionApi.yd_get_axis_positive_limit_flag(Me.m_usCard, Me.m_usAxis, bFlag) Then
                Return False
            End If
            Return bFlag
        End Function
        '获取负向限位标志
        Public Function GetNegativeLimitFlag() As Boolean
            Dim bFlag As Boolean = False
            If CMotionApi.YD_API_ERROR_SUCCESS <> CMotionApi.yd_get_axis_negative_limit_flag(Me.m_usCard, Me.m_usAxis, bFlag) Then
                Return False
            End If
            Return bFlag
        End Function
        '获取平滑停止标志
        Public Function GetSmoothStopFlag() As Boolean
            Dim bFlag As Boolean = False
            If CMotionApi.YD_API_ERROR_SUCCESS <> CMotionApi.yd_get_axis_smooth_stop_flag(Me.m_usCard, Me.m_usAxis, bFlag) Then
                Return False
            End If
            Return bFlag
        End Function
        '获取紧急停止标志
        Public Function GetUrgentStopFlag() As Boolean
            Dim bFlag As Boolean = False
            If CMotionApi.YD_API_ERROR_SUCCESS <> CMotionApi.yd_get_axis_urgent_stop_flag(Me.m_usCard, Me.m_usAxis, bFlag) Then
                Return False
            End If
            Return bFlag
        End Function
        '获取伺服使能标志
        Public Function GetServoOnFlag() As Boolean
            Dim bFlag As Boolean = False
            If CMotionApi.YD_API_ERROR_SUCCESS <> CMotionApi.yd_get_axis_servo_on_flag(Me.m_usCard, Me.m_usAxis, bFlag) Then
                Return False
            End If
            Return bFlag
        End Function
        '获取电机到位标志
        Public Function GetMotorArriveFlag() As Boolean
            Dim bFlag As Boolean = False
            If CMotionApi.YD_API_ERROR_SUCCESS <> CMotionApi.yd_get_axis_motor_arrive_flag(Me.m_usCard, Me.m_usAxis, bFlag) Then
                Return False
            End If
            Return bFlag
        End Function
        '获取原点信号标志
        Public Function GetHomeSignalFlag() As Boolean
            Dim bFlag As Boolean = False
            If CMotionApi.YD_API_ERROR_SUCCESS <> CMotionApi.yd_get_axis_home_signal_flag(Me.m_usCard, Me.m_usAxis, bFlag) Then
                Return False
            End If
            Return bFlag
        End Function
		'获取回原点状态
		Public Function GetHomeMoveStatus() As Byte 
			Dim ucStatus As Byte = 0
            If CMotionApi.YD_API_ERROR_SUCCESS != CMotionApi.yd_get_axis_home_move_status(
                Me.m_usCard,
                Me.m_usAxis,
                ucStatus) Then
            End If
            Return ucStatus;
		End Function
		'更新回原点状态
		Public Function SetHomeMoveStatus(ByVal ucStatus As Byte) As Boolean
            If CMotionApi.YD_API_ERROR_SUCCESS != CMotionApi.yd_set_axis_home_move_status(
                Me.m_usCard,
                Me.m_usAxis,
                ucStatus) Then 
                Return false;
            End If
			Return true;
		End Function
        '获取目标位置
        Public Function GetTargetPosition() As Double
            Dim dblValue As Double = 0
            If CMotionApi.YD_API_ERROR_SUCCESS <> CMotionApi.yd_get_axis_target_position(Me.m_usCard, Me.m_usAxis, dblValue) Then
            End If
            Return dblValue
        End Function
        '获取目标速度
        Public Function GetTargetVelocity() As Double
            Dim dblValue As Double = 0
            If CMotionApi.YD_API_ERROR_SUCCESS <> CMotionApi.yd_get_axis_target_velocity(Me.m_usCard, Me.m_usAxis, dblValue) Then
            End If
            Return dblValue
        End Function
        '获取规划位置
        Public Function GetProfilePosition() As Double
            Dim dblValue As Double = 0
            If CMotionApi.YD_API_ERROR_SUCCESS <> CMotionApi.yd_get_axis_profile_position(Me.m_usCard, Me.m_usAxis, dblValue) Then
            End If
            Return dblValue
        End Function
        '获取规划速度
        Public Function GetProfileVelocity() As Double
            Dim dblValue As Double = 0
            If CMotionApi.YD_API_ERROR_SUCCESS <> CMotionApi.yd_get_axis_profile_velocity(Me.m_usCard, Me.m_usAxis, dblValue) Then
            End If
            Return dblValue
        End Function
        '获取编码器位置
        Public Function GetEncoderPosition() As Double
            Dim dblValue As Double = 0
            If CMotionApi.YD_API_ERROR_SUCCESS <> CMotionApi.yd_get_axis_encoder_position(Me.m_usCard, Me.m_usAxis, dblValue) Then
            End If
            Return dblValue
        End Function
        '获取编码器速度
        Public Function GetEncoderVelocity() As Double
            Dim dblValue As Double = 0
            If CMotionApi.YD_API_ERROR_SUCCESS <> CMotionApi.yd_get_axis_encoder_velocity(Me.m_usCard, Me.m_usAxis, dblValue) Then
            End If
            Return dblValue
        End Function
    End Class

    '气油缸类
    Public Class YDCylinder
        '成员变量
        Private m_uiId As UInt32 = 0
        Private m_strName As String = ""
        '带参数构造函数
        Public Sub New(ByVal uiId As UInt32, ByVal strName As String)
            Me.m_uiId = uiId
            Me.m_strName = strName
        End Sub
    End Class
	
	'时间戳辅助类
	Public Class CTimestampHelper
		Private Shared Readonly DateTimeOffset g_UnixEpoch = New DateTimeOffset(1970, 1, 1, 0, 0, 0, TimeSpan.Zero)
		'获取1970至今的秒数
        Public Function CurrentSeconds() As UInt64
            Dim ts = DateTime.Now - New DateTime(1970, 1, 1, 0, 0, 0, 0)
            Return Convert.ToUInt64(ts.TotalSeconds)
        End Function
		'获取1970至今的毫秒数
        Public Function CurrentMilliseconds() As UInt64
            Dim ts = DateTime.Now - New DateTime(1970, 1, 1, 0, 0, 0, 0)
            Return Convert.ToUInt64(ts.TotalMilliseconds)
        End Function
		'获取1970至今的微秒数
		Public Function CurrentMicroseconds() As UInt64
			Dim duration As TimeSpan = DateTimeOffset.UtcNow - g_UnixEpoch
			Return Convert.ToUInt64(duration.Ticks / 10)
		End Function
	End Class

End Module

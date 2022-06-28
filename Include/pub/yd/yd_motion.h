#pragma once

#include "yddef.h"
#include "mod.h"
#include "mod_macro.h"

namespace yd
{
	namespace motion
	{
		// 值ID常量定义
		constexpr uint16 VALUEID_BIT_DRIVER_ALARM = 1;	// 驱动器报警标志
		constexpr uint16 VALUEID_BIT_FOLLOW_ERROR = 2;	// 跟随误差标志
		constexpr uint16 VALUEID_BIT_POSITIVE_LIMIT = 3;// 正限位触发标志
		constexpr uint16 VALUEID_BIT_NEGATIVE_LIMIT = 4;// 负限位触发标志
		constexpr uint16 VALUEID_BIT_SMOOTH_STOP = 5;	// 平滑停止标志
		constexpr uint16 VALUEID_BIT_URGENT_STOP = 6;	// 紧急停止标志
		constexpr uint16 VALUEID_BIT_SERVO_ON = 7;		// 伺服使能标志
		constexpr uint16 VALUEID_BIT_PROFILE_MOVE = 8;	// 规划运动标志
		constexpr uint16 VALUEID_BIT_MOTOR_ARRIVE = 9;	// 电机到位标志
		constexpr uint16 VALUEID_BIT_HOME_SIGNAL = 10;	// 原点信号
		constexpr uint16 VALUEID_BIT_HOME_MOVED = 11;	// 是否已回零
		constexpr uint16 VALUEID_BIT_DRIVER_ENABLE = 12;// 驱动使能
		constexpr uint16 VALUEID_BIT_HOME_STATUS = 13;	// 回零状态
		constexpr uint16 VALUEID_MOVE_MODE = 20;		// 运动模式
		constexpr uint16 VALUEID_PROFILE_POSITION = 21;	// 规划位置
		constexpr uint16 VALUEID_PROFILE_VELOCITY = 22;	// 规划速度
		constexpr uint16 VALUEID_PROFILE_ACCELERATION = 23;	// 规划加速度
		constexpr uint16 VALUEID_PROFILE_DECELERATION = 24;	// 规划减速度
		constexpr uint16 VALUEID_ENCODER_POSITION = 25;	// 编码器位置
		constexpr uint16 VALUEID_ENCODER_VELOCITY = 26;	// 编码器速度
		constexpr uint16 VALUEID_ENCODER_ACCELERATION = 27;	// 编码器加速度
		constexpr uint16 VALUEID_ENCODER_DECELERATION = 28;	// 编码器减速度
		constexpr uint16 VALUEID_ENCODER_PROFILE_POSITION_OFFSET = 29;	// 编码器与规划位置差
		constexpr uint16 VALUEID_ENCODER_CAPTURE_MODE = 30;	// 编码器捕获方式
		constexpr uint16 VALUEID_ENCODER_CAPTURE_STATUS = 31;	// 编码器捕获状态
		constexpr uint16 VALUEID_ENCODER_CAPTURE_VALUE = 32;	// 编码器捕获值
		constexpr uint16 VALUEID_TARGET_POSITION = 33;		// 目标位置
		constexpr uint16 VALUEID_TARGET_VELOCITY = 34;		// 目标速度

		constexpr uint16 VALUEID_CYLINDER_DIRECTION1_ARRIVED = 1;	// 气油缸方向一到位信号
		constexpr uint16 VALUEID_CYLINDER_DIRECTION2_ARRIVED = 2;	// 气油缸方向二到位信号
		constexpr uint16 VALUEID_CYLINDER_DIRECTION1_ALARMED = 3;	// 气油缸方向一告警状态		
		constexpr uint16 VALUEID_CYLINDER_DIRECTION2_ALARMED = 4;	// 气油缸方向二告警状态
		constexpr uint16 VALUEID_CYLINDER_DIRECTION1_MOVING = 5;	// 气油缸方向一运动中
		constexpr uint16 VALUEID_CYLINDER_DIRECTION2_MOVING = 6;	// 气油缸方向二运动中
		constexpr uint16 VALUEID_CYLINDER_DIRECTION1_ALARM_ENABLED = 7;	// 气油缸方向一告警使能
		constexpr uint16 VALUEID_CYLINDER_DIRECTION2_ALARM_ENABLED = 8;	// 气油缸方向二告警使能

		// 配置类型定义
		constexpr uint8 MC_SETUP_TARGET_POSITION = 1;
		constexpr uint8 MC_SETUP_TARGET_VELOCITY = 2;
		constexpr uint8 MC_SETUP_PROFILE_POSITION = 3;
		constexpr uint8 MC_SETUP_PROFILE_VELOCITY = 4;

		// 运动接口名称定义
		constexpr char METHOD_NAME_OPEN[] = "MC_Open";
		constexpr char METHOD_NAME_CLOSE[] = "MC_Close";
		constexpr char METHOD_NAME_RESET[] = "MC_Reset";
		constexpr char METHOD_NAME_STOP[] = "MC_Stop";
		constexpr char METHOD_NAME_READ[] = "MC_Read";
		constexpr char METHOD_NAME_ZERO_AXIS[] = "MC_ZeroAxis";
		constexpr char METHOD_NAME_ENABLE_AXIS[] = "MC_EnableAxis";
		constexpr char METHOD_NAME_CLEAR_AXIS[] = "MC_ClearAxis";
		constexpr char METHOD_NAME_STOP_MOVE_SMOOTHLY[] = "MC_StopMoveSmoothly";
		constexpr char METHOD_NAME_STOP_MOVE_URGENTLY[] = "MC_StopMoveUrgently";
		constexpr char METHOD_NAME_START_ABSOLUTE_MOVE[] = "MC_StartAbsoluteMove";
		constexpr char METHOD_NAME_START_RELATIVE_MOVE[] = "MC_StartRelativeMove";
		constexpr char METHOD_NAME_START_JOG_MOVE[] = "MC_StartJogMove";
		constexpr char METHOD_NAME_START_MULTIAXISES_MOVE[] = "MC_StartMultiAxisesMove";
		constexpr char METHOD_NAME_WAIT_FOR_INPLACE[] = "MC_WaitForInplace";
		constexpr char METHOD_NAME_SEND_DO_CONTROL[] = "MC_SendDOControl";
		constexpr char METHOD_NAME_SEND_AO_CONTROL[] = "MC_SendAOControl";
		constexpr char METHOD_NAME_GET_DISTATUS[] = "MC_GetDIStatus";
		constexpr char METHOD_NAME_GET_DOSTATUS[] = "MC_GetDOStatus";
		constexpr char METHOD_NAME_GET_AIVALUE[] = "MC_GetAIValue";
		constexpr char METHOD_NAME_GET_AOVALUE[] = "MC_GetAOValue";
		constexpr char METHOD_NAME_SET_TARGET_POSITION[] = "MC_SetTargetPosition";
		constexpr char METHOD_NAME_GET_TARGET_POSITION[] = "MC_GetTargetPosition";
		constexpr char METHOD_NAME_SET_TARGET_VELOCITY[] = "MC_SetTargetVelocity";
		constexpr char METHOD_NAME_GET_TARGET_VELOCITY[] = "MC_GetTargetVelocity";
		constexpr char METHOD_NAME_SET_PROFILE_POSITION[] = "MC_SetProfilePosition";
		constexpr char METHOD_NAME_GET_PROFILE_POSITION[] = "MC_GetProfilePosition";
		constexpr char METHOD_NAME_SET_PROFILE_VELOCITY[] = "MC_SetProfileVelocity";
		constexpr char METHOD_NAME_GET_PROFILE_VELOCITY[] = "MC_GetProfileVelocity";
		constexpr char METHOD_NAME_SET_ENCODER_POSITION[] = "MC_SetEncoderPosition";
		constexpr char METHOD_NAME_GET_ENCODER_POSITION[] = "MC_GetEncoderPosition";
		constexpr char METHOD_NAME_SET_ENCODER_VELOCITY[] = "MC_SetEncoderVelocity";
		constexpr char METHOD_NAME_GET_ENCODER_VELOCITY[] = "MC_GetEncoderVelocity";
		constexpr char METHOD_NAME_SET_SOFTWARE_LIMIT[] = "MC_SetSoftwareLimit";

		// 执行结果
		AUTO_DATA_BEGIN(Result, "执行结果")
			FIELD(int32, error_code, "错误代码", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::string, error_msg, "错误描述", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(int64, time_consumed, "执行时间：微秒", "", "", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(Result)

			// 卡参数
			AUTO_DATA_BEGIN(CardRef, "卡编号")
			FIELD(uint16, card, "卡号", "0", "200", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(CardRef)

			// 轴参数
			AUTO_DATA_BEGIN(AxisEnable, "轴使能")
			FIELD(uint16, card, "卡号", "0", "200", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint16, axis, "轴序号", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(bool, enable, "轴序号", "", "", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(AxisEnable)

			// 轴参数
			AUTO_DATA_BEGIN(AxisRef, "轴序号")
			FIELD(uint16, card, "卡号", "0", "200", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint16, axis, "轴序号", "", "", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(AxisRef)
			AUTO_DATA_BEGIN(AxisRefs, "多轴序号")
			FIELD(uint16, card, "卡号", "0", "200", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::vector<uint16>, axises, "轴列表", "", "", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(AxisRefs)

			// 停止参数
			AUTO_DATA_BEGIN(StopRef, "停止参数")
			FIELD(uint16, card, "卡号", "0", "200", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint16, axis, "轴序号", "1", "400", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(bool, urgent, "是否紧急停止", "0", "1", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(StopRef)

			// 绝对运动
			AUTO_DATA_BEGIN(AbsoluteMove, "绝对运动")
			FIELD(uint16, card, "卡号", "0", "200", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint16, axis, "轴序号", "1", "400", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(double, position, "目标位置", "-999999", "999999", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(double, velocity, "运动速度", "-999999", "999999", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint32, smooth_time, "平滑时间", "0", "5000", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(double, smooth_factor, "平滑系数", "-1000", "1000", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint8, direction, "运动方向", "1", "10", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(AbsoluteMove)

			// 相对运动
			AUTO_DATA_BEGIN(RelativeMove, "相对运动")
			FIELD(uint16, card, "卡号", "0", "200", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint16, axis, "轴序号", "1", "400", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(double, distance, "运动距离：毫米", "-999999", "999999", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(double, velocity, "运动速度", "-999999", "999999", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint32, smooth_time, "平滑时间", "0", "5000", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(double, smooth_factor, "平滑系数", "-1000", "1000", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint8, direction, "运动方向", "1", "10", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(RelativeMove)

			// Jog运动
			AUTO_DATA_BEGIN(JogMove, "Jog运动参数")
			FIELD(uint16, card, "卡号", "0", "200", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint16, axis, "轴序号", "1", "400", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(double, velocity, "运动速度", "- 999999", "999999", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint32, smooth_time, "平滑时间", "0", "5000", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(double, smooth_factor, "平滑系数", "-1000", "1000", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint8, direction, "运动方向", "1", "10", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(JogMove)

			// 多轴运动
			AUTO_DATA_BEGIN(MultiAxisesMove, "多轴运动")
			FIELD(uint64, coords_referid, "坐标数据变量id", "", "", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(MultiAxisesMove)

			// DO控制
			AUTO_DATA_BEGIN(DOControl, "DO控制")
			FIELD(uint16, card, "卡号", "0", "200", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint16, index, "DO序号", "1", "64", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint16, type, "DO类型", "1", "16", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(bool, status, "状态", "0", "1", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(DOControl)

			// DO控制
			AUTO_DATA_BEGIN(AOControl, "AO控制")
			FIELD(uint16, card, "卡号", "0", "200", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint16, index, "AO序号", "1", "64", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(double, value, "数值", "-999999", "999999", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(AOControl)

			// 位置参数
			AUTO_DATA_BEGIN(Position, "位置")
			FIELD(uint16, card, "卡号", "0", "200", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint16, axis, "轴序号", "1", "400", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(double, position, "位置值：毫米", "-999999", "999999", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(Position)

			// 速度参数
			AUTO_DATA_BEGIN(Velocity, "速度")
			FIELD(uint16, card, "卡号", "0", "200", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint16, axis, "轴序号", "1", "400", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(double, velocity, "速度值：毫米/秒", "-999999", "999999", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(Velocity)

			// 到位等待参数
			AUTO_DATA_BEGIN(AxisInplace, "轴序号")
			FIELD(uint16, card, "卡号", "0", "200", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint16, axis, "轴序号", "0", "200", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint8, inplace_type, "到位等待类型", "0", "200", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(double, customized_error, "自定义误差带", "-999999", "999999", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(AxisInplace)

			// 软件限位参数
			AUTO_DATA_BEGIN(SoftLimit, "轴序号")
			FIELD(uint16, card, "卡号", "0", "200", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint16, axis, "轴序号", "0", "200", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(double, positive_limit, "正限位", "-999999", "999999", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(double, negative_limit, "负限位", "-999999", "999999", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(SoftLimit)

			// 状态索引
			AUTO_DATA_BEGIN(StatusRef, "状态索引")
			FIELD(uint16, card, "卡号", "0", "200", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint16, index, "序号", "1", "64", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint16, type, "类型", "1", "16", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(StatusRef)
	}
}

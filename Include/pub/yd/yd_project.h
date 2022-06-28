#pragma once

#include "yd_motion.h"

namespace yd
{
	// 业务逻辑数据结构
	namespace lg {
		// 流程结构
		AUTO_DATA_BEGIN(LogicProcess, "逻辑流程")
			FIELD(uint32, id, "流程id", "0", "60000", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::string, name, "流程名称", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint8, type, "流程类型", "0", "200", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint32, parent_id, "父节点id", "0", "60000", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint8, parent_category, "父节点类别", "0", "60000", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint32, previous_id, "前一个流程id", "0", "60000", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint32, next_id, "下一个流程id", "0", "60000", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(bool, sync_mode, "异步模式", "0", "1", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(int64, module_pointer, "模块指针地址", "", "", FIELD_EXTEND_TYPE_ADDRESS)
			AUTO_DATA_END(LogicProcess)
			AUTO_DATA_BEGIN(InitializeModule, "初始化模块")
			FIELD(uint32, device_id, "设备id", "0", "60000", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(InitializeModule)
			AUTO_DATA_BEGIN(UninitializeModule, "反初始化模块")
			FIELD(uint32, device_id, "设备id", "0", "60000", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(UninitializeModule)
			AUTO_DATA_BEGIN(AbsoluteMoveModule, "绝对运动模块")
			FIELD(uint32, device_id, "设备id", "0", "60000", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint16, axis_index, "轴序号", "0", "200", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint64, position_referid, "目标位置关联id", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint64, velocity_referid, "运动速度关联id", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint64, direction_referid, "运动方向关联id", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint64, safeguard_referid, "安全保护关联变量id", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint8, inplace_wait_type, "到位等待类型", "0", "10", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(double, inplace_wait_value, "到位等待数值", "-999999", "999999", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(AbsoluteMoveModule)
			AUTO_DATA_BEGIN(RelativeMoveModule, "相对运动模块")
			FIELD(uint32, device_id, "设备id", "0", "60000", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint16, axis_index, "轴序号", "0", "200", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint64, distance_referid, "运动距离关联id", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint64, velocity_referid, "运动速度关联id", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint64, direction_referid, "运动方向关联id", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint64, safeguard_referid, "安全保护关联变量id", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint8, inplace_wait_type, "到位等待类型", "0", "10", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(double, inplace_wait_value, "到位等待数值", "-999999", "999999", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(RelativeMoveModule)
			AUTO_DATA_BEGIN(JogMoveModule, "Jog运动模块")
			FIELD(uint32, device_id, "设备id", "0", "60000", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint16, axis_index, "轴序号", "0", "200", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint64, velocity_referid, "运动速度关联id", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint64, safeguard_referid, "安全保护关联变量id", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint64, direction_referid, "运动方向关联id", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint8, inplace_wait_type, "到位等待类型", "0", "10", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(double, inplace_wait_value, "到位等待数值", "-999999", "999999", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(JogMoveModule)
			AUTO_DATA_BEGIN(MultAxisesMoveModule, "多轴运动模块")
			FIELD(uint64, coords_referid, "运动坐标关联id", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::vector<uint64>, enabled_axisids, "使能的运动轴id列表", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint64, safeguard_referid, "安全保护关联变量id", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint8, inplace_wait_type, "到位等待类型", "0", "10", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(double, inplace_wait_value, "到位等待数值", "-999999", "999999", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(MultAxisesMoveModule)
			AUTO_DATA_BEGIN(HomeMoveModule, "回零运动模块")
			FIELD(uint32, device_id, "设备id", "0", "60000", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint16, axis_index, "轴序号", "0", "200", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint64, safeguard_referid, "安全保护关联变量id", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint8, inplace_wait_type, "到位等待类型", "0", "10", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(double, inplace_wait_value, "到位等待数值", "-999999", "999999", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(HomeMoveModule)
			AUTO_DATA_BEGIN(HomeStopModule, "回零急停模块")
			FIELD(uint32, device_id, "设备id", "0", "60000", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint16, axis_index, "轴序号", "0", "200", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint64, safeguard_referid, "安全保护关联变量id", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint8, inplace_wait_type, "到位等待类型", "0", "10", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(double, inplace_wait_value, "到位等待数值", "-999999", "999999", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(HomeStopModule)
			AUTO_DATA_BEGIN(StopMoveModule, "停止运动模块")
			FIELD(uint32, device_id, "设备id", "0", "60000", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint16, axis_index, "轴序号", "0", "200", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint64, method_referid, "停止方式关联id", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint64, safeguard_referid, "安全保护关联变量id", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint8, inplace_wait_type, "到位等待类型", "0", "10", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(double, inplace_wait_value, "到位等待数值", "-999999", "999999", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(StopMoveModule)
			AUTO_DATA_BEGIN(DOControlModule, "DO控制模块")
			FIELD(uint32, device_id, "设备id", "0", "60000", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint16, do_index, "类型+DO序号", "0", "20000", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(bool, do_status, "DO状态", "0", "1", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(DOControlModule)
			AUTO_DATA_BEGIN(AOControlModule, "AO控制模块")
			FIELD(uint32, device_id, "设备id", "0", "60000", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint16, ao_index, "类型+AO序号", "0", "20000", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint64, value_referid, "AO数值关联id", "", "", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(AOControlModule)
			AUTO_DATA_BEGIN(Condition, "条件项")
			FIELD(uint32, condition_id, "条件id", "0", "60000", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint64, parameter_id, "关联变量id", "0", "60000", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint8, compare_operator, "比较运算符", "0", "6", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::string, judge_value, "判定数值", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::string, allow_error, "允许误差", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(bool, not_operator, "是否取反", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint16, judge_order, "判定顺序", "0", "20000", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(Condition)
			AUTO_DATA_BEGIN(ConditionModule, "条件模块")
			FIELD(uint8, logic_operator, "逻辑运算符", "0", "3", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::vector<Condition*>, listConditions, "判定条件项", "0", "20000", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(ConditionModule)
			AUTO_DATA_BEGIN(IfElseModule, "IfElse判定模块")
			FIELD(uint32, ref_condition_id, "关联条件id", "0", "20000", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::vector<uint32>, listTrueProcessIds, "条件成立时后续流程Id列表", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::vector<uint32>, listFalseProcessIds, "条件不成立时后续流程Id列表", "", "", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(IfElseModule)
			AUTO_DATA_BEGIN(IfModule, "If判定模块")
			FIELD(uint32, ref_condition_id, "关联条件id", "0", "20000", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::vector<uint32>, listProcessIds, "条件成立时子流程Id列表", "", "", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(IfModule)
			AUTO_DATA_BEGIN(ConditionLoopModule, "条件循环模块")
			FIELD(uint32, ref_condition_id, "关联条件id", "0", "20000", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::vector<uint32>, listProcessIds, "条件成立时循环流程Id列表", "", "", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(ConditionLoopModule)
			AUTO_DATA_BEGIN(CounterLoopModule, "计数循环模块")
			FIELD(uint32, loop_counter, "循环次数", "0", "200000", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::vector<uint32>, listProcessIds, "次数满足时循环流程Id列表", "", "", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(CounterLoopModule)
			AUTO_DATA_BEGIN(BreakModule, "跳出模块")
			FIELD(uint32, near_loopid, "临近循环流程id", "", "", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(BreakModule)
			AUTO_DATA_BEGIN(DelayModule, "延时模块")
			FIELD(uint64, delay_time, "等待时间/关联变量id", "", "", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(DelayModule)
			AUTO_DATA_BEGIN(MessageAction, "消息动作")
			FIELD(uint8, action_type, "动作类型", "0", "10", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::string, action_name, "动作名称", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(bool, selected, "是否选择", "0", "1", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(MessageAction)
			AUTO_DATA_BEGIN(MessageModule, "消息模块")
			FIELD(uint8, level, "消息级别", "0", "10", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::string, content, "消息内容", "0", "10", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(MessageAction*, pAction1, "动作1，对应类型为1的配置", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(MessageAction*, pAction2, "动作2，对应类型为2的配置", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(MessageAction*, pAction3, "动作3，对应类型为3的配置", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(MessageAction*, pAction4, "动作4，对应类型为4的配置", "", "", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(MessageModule)
			AUTO_DATA_BEGIN(TaskCallerModule, "子例程模块")
			FIELD(uint32, task_id, "关联任务id", "", "", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(TaskCallerModule)
			AUTO_DATA_BEGIN(ProgramModule, "可编程模块")
			FIELD(uint64, safeguard_referid, "安全保护关联变量id", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint32, wait_time, "等待时间", "0", "600000", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint8, script_type, "脚本类型", "0", "10", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint32, data_cache_size, "数据缓存大小：字节", "0", "600000", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(ProgramModule)
			AUTO_DATA_BEGIN(CylinderModule, "气油缸模块")
			FIELD(uint32, device_id, "气油缸id", "0", "60000", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint8, control_direction, "控制方向", "0", "2", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(CylinderModule)
			AUTO_DATA_BEGIN(AxisInplaceWait, "轴到位等待")
			FIELD(uint32, inplace_id, "等待id", "0", "60000", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint32, device_id, "设备id", "0", "60000", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint16, axis_index, "轴序号", "0", "200", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint8, inplace_wait_type, "到位等待类型", "0", "10", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(double, inplace_wait_value, "到位等待数值", "-999999", "999999", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(AxisInplaceWait)
			AUTO_DATA_BEGIN(InplaceWaitModule, "到位等待模块")
			FIELD(uint8, logic_operator, "逻辑运算符", "0", "3", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::vector<AxisInplaceWait*>, listAxisInplaceWaits, "轴到位等待列表", "", "", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(InplaceWaitModule)
			AUTO_DATA_BEGIN(TaskStateWaitModule, "任务等待模块")
			FIELD(uint32, task_id, "关联任务id", "0", "60000", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint8, expected_state, "预期状态", "0", "100", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(TaskStateWaitModule)
			AUTO_DATA_BEGIN(JumpToModule, "跳转模块")
			FIELD(uint32, process_id, "关联流程id", "0", "60000", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(JumpToModule)
			// 逻辑子任务结构
			AUTO_DATA_BEGIN(LogicSubTask, "逻辑子任务")
			FIELD(uint32, id, "子任务id", "0", "60000", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint32, parent_id, "父任务id", "0", "60000", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::string, name, "子任务名称", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint8, type, "子任务类型", "0", "200", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(bool, enable, "是否使能", "0", "1", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint8, execute_method, "执行方式", "0", "100", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::vector<uint32>, listProcessIds, "流程Id列表", "", "", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(LogicSubTask)
			// 任务结构
			AUTO_DATA_BEGIN(LogicTask, "逻辑任务")
			FIELD(uint32, id, "任务id", "1", "60000", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::string, name, "任务名称", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint8, type, "任务类型", "0", "200", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(bool, enable, "是否使能", "0", "1", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint8, execute_method, "执行方式", "0", "100", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::vector<uint32>, listProcessIds, "流程Id列表", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::vector<uint32>, listSubTaskIds, "子任务Id列表", "", "", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(LogicTask)
			// IfElse流程数据
			AUTO_DATA_BEGIN(IfElseProcess, "IfElse流程数据")
			FIELD(LogicProcess*, pProcess, "IfElse流程", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(IfElseModule*, pModule, "IfElse模块数据", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(LogicProcess*, pConditionProcess, "条件流程", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(ConditionModule*, pConditionModule, "条件模块数据", "", "", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(IfElseProcess)
			// If流程数据
			AUTO_DATA_BEGIN(IfProcess, "If流程数据")
			FIELD(LogicProcess*, pProcess, "If流程", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(IfModule*, pModule, "If模块数据", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(LogicProcess*, pConditionProcess, "条件流程", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(ConditionModule*, pConditionModule, "条件模块数据", "", "", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(IfProcess)
			// Condition流程数据
			AUTO_DATA_BEGIN(ConditionLoopProcess, "Condition流程数据")
			FIELD(LogicProcess*, pProcess, "Condition流程", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(ConditionLoopModule*, pModule, "Condition模块数据", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(LogicProcess*, pConditionProcess, "条件流程", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(ConditionModule*, pConditionModule, "条件模块数据", "", "", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(ConditionLoopProcess)
	}

	// 设备数据结构
	namespace dev {
		// 设备类型
		AUTO_DATA_BEGIN(DIType, "DI类型")
			FIELD(uint8, id, "类型id", "0", "200", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::string, name, "类型名称", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint16, number, "个数", "0", "200", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(DIType)
			AUTO_DATA_BEGIN(DOType, "DO类型")
			FIELD(uint8, id, "类型id", "0", "200", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::string, name, "类型名称", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint16, number, "个数", "0", "200", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(DOType)
			AUTO_DATA_BEGIN(AIType, "AI类型")
			FIELD(uint8, id, "类型id", "0", "200", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::string, name, "类型名称", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint16, number, "个数", "0", "200", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(AIType)
			AUTO_DATA_BEGIN(AOType, "AO类型")
			FIELD(uint8, id, "类型id", "0", "200", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::string, name, "类型名称", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint16, number, "个数", "0", "200", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(AOType)
			AUTO_DATA_BEGIN(DeviceType, "设备类型")
			FIELD(uint32, id, "类型id", "0", "600000", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::string, name, "类型名称", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::string, model, "型号", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::string, vendor, "厂商", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::string, library, "组件库", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(bool, extended, "是否扩展", "0", "1", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint16, card_number, "卡个数", "0", "200", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint16, card_start, "起始卡号", "0", "200", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint16, card_end, "结束卡号", "0", "200", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint16, axis_number, "轴个数", "0", "200", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint16, axis_start, "起始轴号", "0", "200", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint16, axis_end, "结束轴号", "0", "200", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::vector<DIType*>, listDITypes, "DI类型列表", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::vector<AIType*>, listAITypes, "AI类型列表", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::vector<DOType*>, listDOTypes, "DO类型列表", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::vector<AOType*>, listAOTypes, "AO类型列表", "", "", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(DeviceType)

			// 基本设备
			AUTO_DATA_BEGIN(Device, "基本设备")
			FIELD(uint32, id, "设备id", "0", "60000", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::string, name, "设备名称", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint32, type_id, "类型id", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::string, type_name, "类型名称", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::string, model, "型号", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::string, vendor, "厂商", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::string, library, "组件库", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::string, remarks, "备注", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(bool, enable, "是否使能", "0", "1", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(Device)

			// 运动控制设备
			AUTO_DATA_BEGIN(MCCard, "卡")
			FIELD(uint16, index, "卡序号", "0", "60000", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::string, name, "卡名称", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::string, config, "配置文件", "", "", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(MCCard)
			AUTO_DATA_BEGIN(MCSWLimit, "软件限位")
			FIELD(bool, enable, "软限位启用", "0", "1", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(double, positive, "正向软限位", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(double, negative, "负向软限位", "", "", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(MCSWLimit)
			AUTO_DATA_BEGIN(MCHWLimit, "硬件限位")
			FIELD(bool, positive_enable, "正向限位启用", "0", "1", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(bool, negative_enable, "负向限位启用", "0", "1", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(MCHWLimit)
			AUTO_DATA_BEGIN(MCHome, "回零参数")
			FIELD(uint8, priority, "回零优先级", "0", "10", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint8, mode, "自动回原点模式", "0", "10", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(double, search_distance, "搜索距离", "0", "1", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(double, move_velocity, "复位移动速度", "0", "1", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(double, search_high_velocity, "搜索速度（高速）", "0", "1", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(double, search_low_velocity, "搜索速度（低速）", "0", "1", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(double, origin_offset, "原点偏移量", "0", "1", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint8, capture_electric_level, "原点捕获电平选中", "0", "1", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(MCHome)
			AUTO_DATA_BEGIN(MCAxis, "轴")
			FIELD(uint16, index, "轴序号", "0", "60000", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::string, name, "轴名称", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(bool, enable, "是否使能", "0", "1", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(double, equivalent, "脉冲当量", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(double, max_velocity, "最大速度", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(double, max_acceleration, "最大加速度", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(double, max_deceleration, "最大减速度", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(double, smooth_stop_deceleration, "平停减速度", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(double, urgent_stop_deceleration, "急停减速度", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(double, arrive_error, "到位误差", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint32, arrive_timeout, "到位超时", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(bool, use_hw_encoder, "使用编码器", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(bool, use_abs_encoder, "绝对值编码器", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint8, pause_mode, "暂停处理模式", "0", "10", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint8, manual_control_mode, "手动控制模式", "0", "10", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::string, remarks, "备注", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(MCSWLimit, sw_limit, "软件限位", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(MCHWLimit, hw_limit, "硬件限位", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(MCHome, home, "回零参数", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint32, stoped_delay, "停稳延时", "0", "1", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(double, takeoff_velocity, "起跳速度", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(double, max_manual_velocity, "最大手动运动速度", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint32, smooth_time, "平滑时间", "0", "5000", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(double, smooth_factor, "平滑系数", "-1000", "1000", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint32, home_logic_subtask, "回零逻辑子任务id", "0", "60000", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint32, suspend_logic_subtask, "暂停逻辑子任务id", "0", "60000", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint32, restore_logic_subtask, "回复逻辑子任务id", "0", "60000", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(MCAxis)
			AUTO_DATA_BEGIN(MCDI, "DI")
			FIELD(uint16, index, "序号", "0", "32", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::string, name, "名称", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint8, type, "类型", "0", "32", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(bool, enable, "是否使能", "0", "1", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::string, label, "标识", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(bool, reverse, "是否反转", "0", "1", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::string, remarks, "备注", "", "", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(MCDI)
			AUTO_DATA_BEGIN(MCDIGroup, "DI组")
			FIELD(uint8, type, "类型", "0", "32", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::vector<MCDI*>, listDIs, "DI列表", "", "", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(MCDIGroup)
			AUTO_DATA_BEGIN(MCDO, "DO")
			FIELD(uint16, index, "序号", "0", "32", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::string, name, "名称", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint8, type, "类型", "0", "32", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(bool, enable, "是否使能", "0", "1", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::string, label, "标识", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(bool, reverse, "是否反转", "0", "1", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::string, remarks, "备注", "", "", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(MCDO)
			AUTO_DATA_BEGIN(MCDOGroup, "DI组")
			FIELD(uint8, type, "类型", "0", "32", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::vector<MCDO*>, listDOs, "DO列表", "", "", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(MCDOGroup)
			AUTO_DATA_BEGIN(MCDevice, "运动控制设备")
			FIELD(Device, base, "基本信息", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(MCCard, card, "卡参数", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::vector<MCAxis*>, listAxises, "轴列表", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::vector<MCDIGroup*>, listDIGroups, "DI组列表", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::vector<MCDOGroup*>, listDOGroups, "DO组列表", "", "", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(MCDevice)
			AUTO_DATA_BEGIN(MCCardInfo, "卡信息")
			FIELD(uint32, device_id, "设备id", "0", "60000", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::string, device_name, "设备名称", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint16, card_index, "卡序号", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::string, card_name, "卡名称", "", "", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(MCCardInfo)
			AUTO_DATA_BEGIN(MCAxisInfo, "轴信息")
			FIELD(uint32, device_id, "设备id", "0", "60000", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::string, device_name, "设备名称", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint16, card_index, "卡序号", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::string, card_name, "卡名称", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint16, axis_index, "轴序号", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::string, axis_name, "轴名称", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(bool, enable, "是否使能", "0", "1", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(double, equivalent, "脉冲当量", "", "", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(MCAxisInfo)
			AUTO_DATA_BEGIN(MCAxisMoveSetup, "轴运动参数")
			FIELD(uint32, device_id, "设备id", "0", "60000", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint16, axis_index, "轴序号", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(double, max_velocity, "最大速度", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(double, max_acceleration, "最大加速度", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(double, max_deceleration, "最大减速度", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(double, takeoff_velocity, "起跳速度", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(double, max_manual_velocity, "最大手动运动速度", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint32, smooth_time, "平滑时间", "0", "5000", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(double, smooth_factor, "平滑系数", "-1000", "1000", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(MCAxisMoveSetup)

			// 气油缸
			AUTO_DATA_BEGIN(CylinderRefer, "气油缸关联")
			FIELD(uint32, device_id, "设备id", "0", "60000", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint16, card, "卡序号", "0", "60000", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint16, axis, "轴序号", "", "", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(CylinderRefer)
			AUTO_DATA_BEGIN(CylinderInput, "气油缸输入")
			FIELD(uint8, type, "到位类型", "0", "60000", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint32, refer_device_id, "关联设备id", "0", "60000", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint16, refer_index, "关联序号", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(double, action_value, "判定值", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint32, delay_time, "延迟时间", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint32, alarm_time, "报警时间", "", "", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(CylinderInput)
			AUTO_DATA_BEGIN(CylinderOutput, "气油缸输出")
			FIELD(uint32, refer_device_id, "关联设备id", "0", "60000", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint16, refer_index, "关联序号", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(double, action_value, "动作值", "", "", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(CylinderOutput)
			AUTO_DATA_BEGIN(Cylinder, "气油缸")
			FIELD(Device, base, "基本信息", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::string, direction1_name, "方向一名称", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::string, direction2_name, "方向二名称", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(CylinderInput, direction1_inplace, "方向一到位信号", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(CylinderInput, direction2_inplace, "方向二到位信号", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(CylinderOutput, direction1_control, "方向一控制输出", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(CylinderOutput, direction2_control, "方向二控制输出", "", "", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(Cylinder)

			// I/O信息
			AUTO_DATA_BEGIN(IOInfo, "I/O信息")
			FIELD(uint64, variable_id, "变量id", "0", "60000", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint32, device_id, "设备id", "0", "60000", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint16, card_no, "卡序号", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::string, device_name, "设备名称", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint16, io_index, "IO序号", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::string, io_name, "IO名称", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::string, io_label, "IO标签", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(bool, enable, "是否使能", "0", "1", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(bool, reverse, "是否反转", "0", "1", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(IOInfo)
	}

	// 权限数据结构
	namespace usr {
		// 用户管理
		AUTO_DATA_BEGIN(Privilege, "权限")
			FIELD(uint32, id, "权限ID", "1", "60000", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint8, type, "权限类型", "0", "3", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::string, name, "权限名称", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint32, function_id, "功能id", "1", "60000", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::string, function_name, "功能名称", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(bool, default_function, "是否为默认功能", "0", "1", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(Privilege)
			AUTO_DATA_BEGIN(Role, "用户角色")
			FIELD(uint32, id, "角色ID", "1", "60000", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint8, type, "角色类型", "0", "5", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::string, name, "角色名称", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(bool, default_role, "是否为默认角色", "0", "1", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::vector<Privilege*>, listPrivileges, "角色权限列表", "", "", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(Role)
			AUTO_DATA_BEGIN(User, "用户")
			FIELD(uint32, id, "用户ID", "1", "60000", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint32, parent_id, "上级用户ID", "1", "60000", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint32, role, "用户角色d", "1", "60000", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::string, name, "用户名称", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::string, real_name, "真实姓名", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::string, password, "密码", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::string, telephone, "电话号码", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::string, register_date, "注册日期", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::string, expires_date, "失效日期", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(bool, default_user, "是否为默认用户", "0", "1", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(User)
	}

	// 系统变量
	namespace vr {
		AUTO_DATA_BEGIN(SystemVariable, "系统变量")
			FIELD(uint16, main_group_id, "主分组id", "1", "60000", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint16, sub_group_id, "次分组id", "1", "60000", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint64, parent_id, "父级id", "1", "60000", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint64, variable_id, "变量id", "1", "60000", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint8, variable_type, "变量类型", "1", "200", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint8, value_type, "数值类型", "1", "200", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint8, access_type, "访问类型", "1", "200", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::string, parent_name, "父级名称", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::string, variable_name, "变量名称", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::string, current_value, "当前值", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::string, init_value, "初始值", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::string, min_value, "最小值", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::string, max_value, "最大值", "", "", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(SystemVariable)
			AUTO_DATA_BEGIN(VariableGroup, "变量组")
			FIELD(uint16, parent_id, "父分组id", "1", "60000", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint16, group_id, "分组id", "1", "60000", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::string, group_name, "分组名称", "", "", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(VariableGroup)
			AUTO_DATA_BEGIN(SafeVariable, "安全变量")
			FIELD(uint16, main_group_id, "主分组id", "1", "60000", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint16, sub_group_id, "次分组id", "1", "60000", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint64, variable_id, "变量id", "1", "60000", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::string, variable_name, "变量名称", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint8, logic_operator, "逻辑运算符", "0", "3", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::vector<lg::Condition*>, listConditions, "判定条件项", "0", "20000", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(SafeVariable)
	}

	// 接口
	namespace lib {
		AUTO_DATA_BEGIN(MethodObject, "方法对象")
			FIELD(uint32, id, "id", "1", "60000", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint32, refer_id, "关联id", "1", "60000", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint8, type, "类型", "1", "200", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::string, name, "名称", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::string, alias, "别名", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::string, library, "组件库", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(std::string, digest, "摘要", "", "", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(MethodObject)
	}

	// 项目参数
	namespace prj {
		AUTO_DATA_BEGIN(DataServer, "数据服务器")
			FIELD(std::string, address, "地址", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint16, port, "端口", "1", "65535", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint32, time_out, "超时时间", "1", "999999", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(DataServer)
	}

	// 高级功能
	namespace adv {
		AUTO_DATA_BEGIN(ExtendScript, "自定义脚本")
			FIELD(std::string, script_name, "脚本名称", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint8, script_type, "脚本类型", "1", "100", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint8, execute_mode, "执行方式", "1", "100", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint32, timer_interval, "定时间隔", "1", "60000", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint64, safeguard_referid, "安全保护关联变量id", "", "", FIELD_EXTEND_TYPE_NORMAL)
			FIELD(uint32, data_cache_size, "数据缓存大小：字节", "0", "600000", FIELD_EXTEND_TYPE_NORMAL)
			AUTO_DATA_END(ExtendScript)
	}

	// 用户管理接口
	namespace usr {
		interface IUserManager : public ICountor
		{
		public:
			// 是否变更
			virtual bool IsChanged() const = 0;

			// 获取错误信息
			virtual const char* GetErrorMsg() = 0;

			// 获取错误代码
			virtual int32 GetErrorCode() = 0;

			// 用户登录
			virtual bool Login(const std::string& strUserName, const std::string& strPassword, User*& pUser, Role*& pRole) = 0;

			// 用户登出
			virtual bool Logout(const std::string& strUserName) = 0;

			// 是否已经登录
			virtual bool IsLogined(const std::string& strUserName) = 0;

			// 更新登录
			virtual bool UpdateLogin(const std::string& strUserName) = 0;

			// 指定名称用户是否存在
			virtual bool IsUserExisting(const std::string& strUserName) = 0;

			// 指定id用户是否存在
			virtual bool IsUserExisting(uint32 uiUserId) = 0;

			// 创建用户：如果用户存在则返回已经存在的用户
			virtual bool CreateUser(const std::string& strUserName, User*& pUser, const User* pCopyFrom = nullptr) = 0;

			// 根据名称获取用户
			virtual bool GetUser(const std::string& strUserName, User*& pUser) = 0;

			// 根据id获取用户
			virtual bool GetUser(uint32 uiUserId, User*& pUser) = 0;

			// 获取所有用户
			virtual bool GetUsers(std::vector<User*>& listUsers) = 0;

			// 根据名称删除用户
			virtual bool DeleteUser(const std::string& strUserName) = 0;

			// 根据id删除用户
			virtual bool DeleteUser(uint32 uiUserId) = 0;

			// 删除所有用户
			virtual bool DeleteUsers() = 0;

			// 指定名称角色是否存在
			virtual bool IsRoleExisting(const std::string& strRoleName) = 0;

			// 指定id角色是否存在
			virtual bool IsRoleExisting(uint32 uiRoleId) = 0;

			// 获取系统角色id
			virtual uint32 GetSystemRoleId(uint8 ucRoleType) = 0;

			// 创建角色：如果角色存在则返回已经存在的角色
			virtual bool CreateRole(const std::string& strRoleName, Role*& pRole, const Role* pCopyFrom = nullptr) = 0;

			// 根据名称获取角色
			virtual bool GetRole(const std::string& strRoleName, Role*& pRole) = 0;

			// 根据id获取角色
			virtual bool GetRole(uint32 uiRoleId, Role*& pRole) = 0;

			// 获取所有角色
			virtual bool GetRoles(std::vector<Role*>& listRoles) = 0;

			// 根据名称删除角色
			virtual bool DeleteRole(const std::string& strRoleName) = 0;

			// 根据id删除角色
			virtual bool DeleteRole(uint32 uiRoleId) = 0;

			// 删除所有角色
			virtual bool DeleteRoles() = 0;

			// 指定名称权限是否存在
			virtual bool IsRolePrivilegeExisting(uint32 uiRoleId, const std::string& strPrivilegName) = 0;

			// 指定id权限是否存在
			virtual bool IsRolePrivilegeExisting(uint32 uiRoleId, uint32 uiPrivilegeId) = 0;

			// 创建权限：如果同名权限存在则返回已经存在的
			virtual bool CreateRolePrivilege(uint32 uiRoleId, const std::string& strPrivilegeName, Privilege*& pPrivilege, const Privilege* pCopyFrom = nullptr) = 0;

			// 根据名称获取权限
			virtual bool GetRolePrivilege(uint32 uiRoleId, const std::string& strPrivilegeName, Privilege*& pPrivilege) = 0;

			// 根据id获取权限
			virtual bool GetRolePrivilege(uint32 uiRoleId, uint32 uiPrivilegeId, Privilege*& pPrivilege) = 0;

			// 获取所有权限
			virtual bool GetRolePrivileges(uint32 uiRoleId, std::vector<Privilege*>& listPrivileges) = 0;

			// 根据名称删除权限
			virtual bool DeleteRolePrivilege(uint32 uiRoleId, const std::string& strPrivilegeName) = 0;

			// 根据id删除权限
			virtual bool DeleteRolePrivilege(uint32 uiRoleId, uint32 uiPrivilegeId) = 0;

			// 删除所有权限
			virtual bool DeleteRolePrivileges(uint32 uiRoleId) = 0;

			// 清理
			virtual void Clear() = 0;
		};
	}

	namespace dev {
		// 设备管理器接口
		interface IDeviceManager : public ICountor
		{
		public:
			// 是否变更
			virtual bool IsChanged() const = 0;

			// 获取错误
			virtual const char* GetErrorMsg() = 0;

			// 获取所有预定义设备类型
			virtual bool GetPredefinedDeviceTypes(std::vector<DeviceType*>& listDeviceTypes) = 0;

			// 获取指定预定义设备类型
			virtual bool GetPredefinedDeviceType(uint32 uiTypeId, DeviceType*& pDeviceType) = 0;

			// 获取指定设备类型
			virtual bool GetDeviceType(uint32 uiDeviceId, DeviceType*& pDeviceType) = 0;

			// 获取指定设备名称
			virtual const char* GetDeviceName(uint32 uiDeviceId) = 0;

			// 获取指定设备类型id
			virtual uint32 GetDeviceTypeId(uint32 uiDeviceId) = 0;

			// 获取指定设备类型名称
			virtual const char* GetDeviceTypeName(uint32 uiDeviceId) = 0;

			// 指定设备是否使能
			virtual bool IsDeviceEnabled(uint32 uiDeviceId) = 0;
			virtual bool IsDeviceEnabled(const std::string& strDeviceName) = 0;

			// 指定设备是否存在
			virtual bool IsDeviceExisting(uint32 uiDeviceId) = 0;
			virtual bool IsDeviceExisting(const std::string& strDeviceName) = 0;

			// 获取所有设备
			virtual bool GetDevices(std::vector<Device*>& listDevices) = 0;

			// 获取指定设备
			virtual bool GetDevice(uint32 uiDeviceId, Device*& pDevice) = 0;
			virtual bool GetDevice(const std::string& strDeviceName, Device*& pDevice) = 0;

			// 获取所有设备id
			virtual bool GetDeviceIds(const std::string& strTypeName, std::vector<uint32>& listDeviceIds) = 0;

			// 获取所有运动控制设备
			virtual bool GetMotionDevices(std::vector<MCDevice*>& listMCDevices) = 0;

			// 创建运动控制设备
			virtual bool CreateMotionDevice(const std::string& strName, DeviceType* pDeviceType, MCDevice*& pMCDevice) = 0;

			// 获取运动控制设备
			virtual bool GetMotionDevice(uint32 uiDeviceId, MCDevice*& pMCDevice) = 0;
			virtual bool GetMotionDevice(const std::string& strDeviceName, MCDevice*& pMCDevice) = 0;
			virtual bool GetMotionDeviceByCardNo(uint16 usCardNo, MCDevice*& pMCDevice) = 0;
			virtual bool GetMotionDeviceByCardName(const std::string& strCardName, MCDevice*& pMCDevice) = 0;

			// 更新运动控制设备名称：-1--更新失败/0--更新成功/1--名称重复
			virtual int32 UpdateMotionDeviceName(uint32 uiDeviceIdToUpdate, const std::string& strNewDeviceName) = 0;

			// 更新运动控制轴名称：-1--更新失败/0--更新成功/1--名称重复
			virtual int32 UpdateMotionAxisName(uint32 uiDeviceIdOfAxis, uint16 usAxisIndexToUpdate, const std::string& strNewAxisName) = 0;

			// 指定名称运动控制轴是否存在
			virtual bool IsMotionAxisExisting(const std::string& strAxisName) = 0;

			// 删除运动控制设备
			virtual bool DeleteMotionDevice(uint32 uiDeviceId) = 0;
			virtual bool DeleteMotionDevice(const std::string& strDeviceName) = 0;

			// 获取运动控制卡信息
			virtual bool GetMotionCardInfos(std::vector<MCCardInfo*>& listMCCardInfos) = 0;

			// 获取运动控制轴信息
			virtual bool GetMotionAxisInfos(std::vector<MCAxisInfo*>& listMCAxisInfos, bool bIncludeDisabled = false) = 0;
			virtual bool GetMotionAxisInfo(uint16 usCard, uint16 usAxis, MCAxisInfo*& pMCAxisInfo) = 0;
			virtual bool GetMotionAxisInfo(const std::string& strAxisName, MCAxisInfo*& pMCAxisInfo) = 0;

			// 获取运动控制轴运动设定
			virtual bool GetMotionAxisMoveSetups(std::vector<MCAxisMoveSetup*>& listMCAxisMoveSetups) = 0;

			// 获取所有气油缸
			virtual bool GetCylinders(std::vector<Cylinder*>& listCylinders) = 0;

			// 创建气油缸
			virtual bool CreateCylinder(const std::string& strName, DeviceType* pDeviceType, Cylinder*& pCylinder) = 0;

			// 获取气油缸
			virtual bool GetCylinder(uint32 uiDeviceId, Cylinder*& pCylinder) = 0;
			virtual bool GetCylinder(const std::string& strDeviceName, Cylinder*& pCylinder) = 0;

			// 更新气油缸名称：-1--更新失败/0--更新成功/1--名称重复
			virtual int32 UpdateCylinderName(uint32 uiDeviceIdToUpdate, const std::string& strNewDeviceName) = 0;

			// 删除气油缸
			virtual bool DeleteCylinder(uint32 uiDeviceId) = 0;
			virtual bool DeleteCylinder(const std::string& strDeviceName) = 0;

			// 更新DI名称：-1--更新失败/0--更新成功/1--名称重复
			virtual int32 UpdateDIName(uint32 uiDeviceIdOfDI, uint8 ucDIGroupType, uint16 usDIIndexToUpdate, const std::string& strNewDIName) = 0;

			// 更新DO名称：-1--更新失败/0--更新成功/1--名称重复
			virtual int32 UpdateDOName(uint32 uiDeviceIdOfDO, uint8 ucDOGroupType, uint16 usDOIndexToUpdate, const std::string& strNewDOName) = 0;

			// 更新AI名称：-1--更新失败/0--更新成功/1--名称重复
			virtual int32 UpdateAIName(uint32 uiDeviceIdOfAI, uint8 ucAIGroupType, uint16 usAIIndexToUpdate, const std::string& strNewAIName) = 0;

			// 更新AO名称：-1--更新失败/0--更新成功/1--名称重复
			virtual int32 UpdateAOName(uint32 uiDeviceIdOfAO, uint8 ucAOGroupType, uint16 usAOIndexToUpdate, const std::string& strNewAOName) = 0;

			// 获取DI信息
			virtual bool GetDIInfos(std::vector<IOInfo*>& listDIInfos, bool bIncludeDisabled = false) = 0;
			virtual bool GetDIInfo(const std::string& strDIName, IOInfo*& pDIInfo) = 0;
			virtual bool GetDIInfo(uint64 ullDIVariableId, IOInfo*& pDIInfo) = 0;
			virtual bool GetDIInfo(uint16 usCard, uint16 usType, uint16 usIndex, IOInfo*& pDIInfo) = 0;

			// 获取DO信息
			virtual bool GetDOInfos(std::vector<IOInfo*>& listDOInfos, bool bIncludeDisabled = false) = 0;
			virtual bool GetDOInfo(const std::string& strDOName, IOInfo*& pDOInfo) = 0;
			virtual bool GetDOInfo(uint64 ullDOVariableId, IOInfo*& pDOInfo) = 0;
			virtual bool GetDOInfo(uint16 usCard, uint16 usType, uint16 usIndex, IOInfo*& pDOInfo) = 0;

			// 获取AI信息
			virtual bool GetAIInfos(std::vector<IOInfo*>& listAIInfos, bool bIncludeDisabled = false) = 0;
			virtual bool GetAIInfo(const std::string& strAIName, IOInfo*& pAIInfo) = 0;
			virtual bool GetAIInfo(uint64 ullVariableId, IOInfo*& pAIInfo) = 0;
			virtual bool GetAIInfo(uint16 usCard, uint16 usType, uint16 usIndex, IOInfo*& pAIInfo) = 0;

			// 获取AO信息
			virtual bool GetAOInfos(std::vector<IOInfo*>& listAOInfos, bool bIncludeDisabled = false) = 0;
			virtual bool GetAOInfo(const std::string& strAOName, IOInfo*& pAOInfo) = 0;
			virtual bool GetAOInfo(uint64 ullVariableId, IOInfo*& pAOInfo) = 0;
			virtual bool GetAOInfo(uint16 usCard, uint16 usType, uint16 usIndex, IOInfo*& pAOInfo) = 0;

			// 指定名称DI是否存在
			virtual bool IsDIExisting(const std::string& strDIName) = 0;

			// 指定名称DO是否存在
			virtual bool IsDOExisting(const std::string& strDOName) = 0;

			// 指定名称AI是否存在
			virtual bool IsAIExisting(const std::string& strAIName) = 0;

			// 指定名称AO是否存在
			virtual bool IsAOExisting(const std::string& strAOName) = 0;

			// 清理
			virtual void Clear() = 0;
		};
	}

	namespace lg {
		// 逻辑管理器接口
		interface ILogicManager : public ICountor
		{
		public:
			// 是否变更
			virtual bool IsChanged() const = 0;

			// 获取错误
			virtual const char* GetErrorMsg() = 0;

			// 任务是否存在
			virtual bool IsTaskExisting(uint32 uiTaskId) = 0;
			virtual bool IsTaskExisting(const std::string& strTaskName) = 0;

			// 更新任务名称：-1--更新失败/0--更新成功/1--名称重复
			virtual int32 UpdateTaskName(uint32 uiTaskIdToUpdate, const std::string& strNewTaskName) = 0;

			// 获取所有逻辑任务名称
			virtual bool GetTaskNames(std::map<uint32, std::string>& mapId2Name) = 0;

			// 获取所有逻辑流程名称
			virtual bool GetProcessNames(std::map<uint32, std::string>& mapId2Name) = 0;

			// 获取所有逻辑任务
			virtual bool GetTasks(std::vector<LogicTask*>& listTasks) = 0;

			// 创建逻辑任务
			virtual bool CreateTask(LogicTask*& pTask) = 0;

			// 根据XML文件创建逻辑任务
			virtual bool CreateTaskFromXMLFile(const std::string& strXMLFilePath) = 0;

			// 根据XML字符串创建逻辑任务
			virtual bool CreateTaskFromXMLContent(const std::string& strXMLContent) = 0;

			// 获取逻辑任务
			virtual bool GetTask(uint32 uiTaskId, LogicTask*& pTask) = 0;

			// 删除逻辑任务
			virtual bool DeleteTask(uint32 uiTaskId) = 0;

			// 获取逻辑任务id
			virtual uint32 GetTaskId(const std::string& strTaskName) = 0;

			// 获取逻辑任务类型（适用于任务/子文件）
			virtual uint8 GetTaskType(uint32 uiTaskId) = 0;
			virtual uint8 GetTaskType(const std::string& strTaskName) = 0;

			// 获取所有逻辑子任务
			virtual bool GetSubTasks(uint32 uiTaskId, std::vector<LogicSubTask*>& listSubTasks) = 0;

			// 创建逻辑子任务
			virtual bool CreateSubTask(uint32 uiTaskId, LogicSubTask*& pSubTask) = 0;

			// 获取逻辑子任务
			virtual bool GetSubTask(uint32 uiSubTaskId, LogicSubTask*& pSubTask) = 0;

			// 删除逻辑子任务
			virtual bool DeleteSubTask(uint32 uiTaskId, uint32 uiSubTaskId) = 0;

			// 获取逻辑子任务id
			virtual uint32 GetSubTaskId(const std::string& strSubTaskName) = 0;

			// 移动逻辑子任务
			virtual bool MoveSubTask(uint32 uiOldTaskId, uint32 uiNewTaskId, uint32 uiSubTaskId) = 0;

			// 获取逻辑任务XML格式化流程
			virtual bool GetTaskXmlizedProcesses(uint32 uiTaskId, std::string& strXmlizedProcesses) = 0;

			// 获取所有逻辑过程
			virtual bool GetAllProcesses(std::vector<LogicProcess*>& listProcesses) = 0;

			// 获取指定id逻辑过程
			virtual bool GetProcesses(std::vector<uint32>& listProcessIds, std::vector<LogicProcess*>& listProcesses) = 0;
			virtual bool GetOrderedProcesses(std::vector<uint32>& listProcessIds, std::vector<LogicProcess*>& listProcesses) = 0;

			// 获取所有逻辑过程id
			virtual bool GetAllProcessIds(std::vector<uint32>& listProcessIds) = 0;
			virtual bool GetTaskProcessIds(uint32 uiTaskId, std::vector<uint32>& listProcessIds) = 0;
			virtual bool GetSubTaskProcessIds(uint32 uiSubTaskId, std::vector<uint32>& listProcessIds) = 0;

			// 获取指定任务逻辑过程
			virtual bool GetTaskProcesses(uint32 uiTaskId, std::vector<LogicProcess*>& listProcesses) = 0;
			virtual bool GetSubTaskProcesses(uint32 uiSubTaskId, std::vector<LogicProcess*>& listProcesses) = 0;

			// 获取指定任务开始过程
			virtual bool GetTaskBeginProcess(uint32 uiTaskId, LogicProcess*& pProcess) = 0;
			virtual bool GetSubTaskBeginProcess(uint32 uiSubTaskId, LogicProcess*& pProcess) = 0;

			// 获取指定任务结束过程
			virtual bool GetTaskEndProcesses(uint32 uiTaskId, std::vector<LogicProcess*>& listProcesses) = 0;
			virtual bool GetSubTaskEndProcesses(uint32 uiSubTaskId, std::vector<LogicProcess*>& listProcesses) = 0;

			// 获取指定任务排序过程
			virtual bool GetTaskOrderedProcesses(uint32 uiTaskId, std::vector<LogicProcess*>& listProcesses) = 0;
			virtual bool GetSubTaskOrderedProcesses(uint32 uiSubTaskId, std::vector<LogicProcess*>& listProcesses) = 0;

			// 创建指定任务逻辑过程
			virtual bool CreateTaskProcess(uint32 uiTaskId, LogicProcess*& pProcess, uint8 ucProcessType = 0) = 0;
			virtual bool CreateSubTaskProcess(uint32 uiSubTaskId, LogicProcess*& pProcess, uint8 ucProcessType = 0) = 0;

			// 创建指定任务IfElse过程
			virtual bool CreateTaskIfElseProcess(uint32 uiTaskId, IfElseProcess*& pIfElseProcess) = 0;
			virtual bool CreateSubTaskIfElseProcess(uint32 uiSubTaskId, IfElseProcess*& pIfElseProcess) = 0;

			// 创建指定任务If过程
			virtual bool CreateTaskIfProcess(uint32 uiTaskId, IfProcess*& pIfProcess) = 0;
			virtual bool CreateSubTaskIfProcess(uint32 uiSubTaskId, IfProcess*& pIfProcess) = 0;

			// 创建指定任务Condition循环过程
			virtual bool CreateTaskConditionLoopProcess(uint32 uiTaskId, ConditionLoopProcess*& pConditionProcess) = 0;
			virtual bool CreateSubTaskConditionLoopProcess(uint32 uiSubTaskId, ConditionLoopProcess*& pConditionProcess) = 0;

			// 删除指定任务逻辑过程
			virtual bool DeleteTaskProcess(uint32 uiTaskId, uint32 uiProcessId) = 0;
			virtual bool DeleteSubTaskProcess(uint32 uiSubTaskId, uint32 uiProcessId) = 0;

			// 逻辑过程是否存在
			virtual bool IsProcessExisting(uint32 uiProcessId) = 0;
			virtual bool IsProcessExisting(const std::string& strProcessName) = 0;

			// 获取逻辑过程
			virtual bool GetProcess(uint32 uiProcessId, LogicProcess*& pProcess) = 0;

			// 获取IfElse过程
			virtual bool GetIfElseProcess(uint32 uiProcessId, IfElseProcess*& pIfElseProcess) = 0;

			// 获取If过程
			virtual bool GetIfProcess(uint32 uiProcessId, IfProcess*& pIfProcess) = 0;

			// 获取Condition循环过程
			virtual bool GetConditionLoopProcess(uint32 uiProcessId, ConditionLoopProcess*& pConditionLoopProcess) = 0;

			// 获取逻辑过程id
			virtual uint32 GetProcessId(const std::string& strProcessName) = 0;

			// 更新过程名称：-1--更新失败/0--更新成功/1--名称重复
			virtual int32 UpdateProcessName(uint32 uiTaskIdOfProcess, uint32 uiProcessIdToUpdate, const std::string& strNewProcessName) = 0;

			// 移动流程到指定流程之前
			virtual bool MoveTaskProcess(uint32 uiTaskId, uint32 uiProcessIdToMove, uint32 uiProcessIdToLocate) = 0;
			virtual bool MoveSubTaskProcess(uint32 uiSubTaskId, uint32 uiProcessIdToMove, uint32 uiProcessIdToLocate) = 0;

			// 连接流程到指定流程之后：如果指定流程null，则作为第一个流程
			virtual bool ConnectProcess(uint32 uiParentId, LogicProcess* pPreviousProcess, LogicProcess* pCurrentProcess) = 0;
			virtual bool ConnectProcess(uint32 uiParentId, uint32 uiPreviousProcessId, uint32 uiCurrentProcessId) = 0;

			// 创建流程条件项：uiProcessId表示IfElse控件id或按条件循环控件id
			virtual bool CreateCondition(uint32 uiProcessId, Condition*& pCondition) = 0;

			// 删除流程条件项：uiProcessId表示IfElse控件id或按条件循环控件id，uiConditionId表示条件id
			virtual bool DeleteCondition(uint32 uiProcessId, uint32 uiConditionId) = 0;

			// 创建轴等待项：uiProcessId表示运动等待控件id
			virtual bool CreateAxisInplaceWait(uint32 uiProcessId, AxisInplaceWait*& pAxisInplaceWait) = 0;

			// 删除轴等待项：uiProcessId表示运动等待控件id，uiInplaceId表示轴等待id
			virtual bool DeleteAxisInplaceWait(uint32 uiProcessId, uint32 uiInplaceId) = 0;

			// 附加初始化模块至指定流程：出参返回已经存在的模块或者创建的模块
			virtual bool AttachInitializeModule(uint32 uiProcessId, InitializeModule*& pModule) = 0;

			// 附加反初始化模块至指定流程：出参返回已经存在的模块或者创建的模块
			virtual bool AttachUninitializeModule(uint32 uiProcessId, UninitializeModule*& pModule) = 0;

			// 附加绝对运动模块至指定流程：出参返回已经存在的模块或者创建的模块
			virtual bool AttachAbsoluteMoveModule(uint32 uiProcessId, AbsoluteMoveModule*& pModule) = 0;

			// 附加相对运动模块至指定流程：出参返回已经存在的模块或者创建的模块
			virtual bool AttachRelativeMoveModule(uint32 uiProcessId, RelativeMoveModule*& pModule) = 0;

			// 附加Jog运动模块至指定流程：出参返回已经存在的模块或者创建的模块
			virtual bool AttachJogMoveModule(uint32 uiProcessId, JogMoveModule*& pModule) = 0;

			// 附加多轴运动模块至指定流程：出参返回已经存在的模块或者创建的模块
			virtual bool AttachMultiAxisesMoveModule(uint32 uiProcessId, MultAxisesMoveModule*& pModule) = 0;

			// 附加回零运动模块至指定流程：出参返回已经存在的模块或者创建的模块
			virtual bool AttachHomeMoveModule(uint32 uiProcessId, HomeMoveModule*& pModule) = 0;

			// 附加原点停止模块至指定流程：出参返回已经存在的模块或者创建的模块
			virtual bool AttachHomeStopModule(uint32 uiProcessId, HomeStopModule*& pModule) = 0;

			// 附加停止运动模块至指定流程：出参返回已经存在的模块或者创建的模块
			virtual bool AttachStopMoveModule(uint32 uiProcessId, StopMoveModule*& pModule) = 0;

			// 附加DO控制模块至指定流程：出参返回已经存在的模块或者创建的模块
			virtual bool AttachDOControlModule(uint32 uiProcessId, DOControlModule*& pModule) = 0;

			// 附加AO控制模块至指定流程：出参返回已经存在的模块或者创建的模块
			virtual bool AttachAOControlModule(uint32 uiProcessId, AOControlModule*& pModule) = 0;

			// 附加IF-ELSE模块至指定流程：出参返回已经存在的模块或者创建的模块
			virtual bool AttachIfElseModule(uint32 uiProcessId, IfElseModule*& pModule) = 0;

			// 附加IF模块至指定流程：出参返回已经存在的模块或者创建的模块
			virtual bool AttachIfModule(uint32 uiProcessId, IfModule*& pModule) = 0;

			// 附加条件循环模块至指定流程：出参返回已经存在的模块或者创建的模块
			virtual bool AttachConditionLoopModule(uint32 uiProcessId, ConditionLoopModule*& pModule) = 0;

			// 附加计数循环模块至指定流程：出参返回已经存在的模块或者创建的模块
			virtual bool AttachCounterLoopModule(uint32 uiProcessId, CounterLoopModule*& pModule) = 0;

			// 附加跳出循环模块至指定流程：出参返回已经存在的模块或者创建的模块
			virtual bool AttachBreakModule(uint32 uiProcessId, BreakModule*& pModule) = 0;

			// 附加延时等待模块至指定流程：出参返回已经存在的模块或者创建的模块
			virtual bool AttachDelayModule(uint32 uiProcessId, DelayModule*& pModule) = 0;

			// 附加消息模块至指定流程：出参返回已经存在的模块或者创建的模块
			virtual bool AttachMessageModule(uint32 uiProcessId, MessageModule*& pModule) = 0;

			// 附加子例程模块至指定流程：出参返回已经存在的模块或者创建的模块
			virtual bool AttachTaskCallerModule(uint32 uiProcessId, TaskCallerModule*& pModule) = 0;

			// 附加可编程模块至指定流程：出参返回已经存在的模块或者创建的模块
			virtual bool AttachProgramModule(uint32 uiProcessId, ProgramModule*& pModule) = 0;

			// 附加气油缸模块至指定流程：出参返回已经存在的模块或者创建的模块
			virtual bool AttachCylinderModule(uint32 uiProcessId, CylinderModule*& pModule) = 0;

			// 附加条件模块至指定流程：出参返回已经存在的模块或者创建的模块
			virtual bool AttachConditionModule(uint32 uiProcessId, ConditionModule*& pModule) = 0;

			// 附加到位等待至指定流程：出参返回已经存在的模块或者创建的模块
			virtual bool AttachInplaceWaitModule(uint32 uiProcessId, InplaceWaitModule*& pModule) = 0;

			// 附加任务等待至指定流程：出参返回已经存在的模块或者创建的模块
			virtual bool AttachTaskStateWaitModule(uint32 uiProcessId, TaskStateWaitModule*& pModule) = 0;

			// 附加跳转模块至指定流程：出参返回已经存在的模块或者创建的模块
			virtual bool AttachJumpToModule(uint32 uiProcessId, JumpToModule*& pModule) = 0;

			// 关联条件模块到指定流程：即将条件模块关联到指定的IfElse或Condition流程模块
			virtual bool MappingConditionModule(uint32 uiConditionProcessId, uint32 uiTargetProcessId) = 0;

			// 清理
			virtual void Clear() = 0;
		};
	}

	// 变量管理器接口
	namespace vr {
		// 变量分组接口
		interface IVariableGroupManager : public ICountor
		{
			// 是否变更
			virtual bool IsChanged() const = 0;

			// 获取错误
			virtual const char* GetErrorMsg() = 0;

			// 分组是否存在
			virtual bool IsGroupExisting(uint16 usGroupId) = 0;
			virtual bool IsGroupExisting(const std::string& strGroupName) = 0;

			// 更新分组名称：-1--更新失败/0--更新成功/1--名称重复
			virtual int32 UpdateGroupName(uint16 usGroupIdToUpdate, const std::string& strNewGroupName) = 0;

			// 创建主分组
			virtual bool CreateMainGroup(VariableGroup*& pVariableGroup) = 0;

			// 创建次分组
			virtual bool CreateSubGroup(uint16 usMainGroupId, VariableGroup*& pVariableGroup) = 0;

			// 获取主分组
			virtual bool GetMainGroups(std::vector<VariableGroup*>& listVariableGroups) = 0;

			// 获取次分组
			virtual bool GetSubGroups(uint16 usMainGroupId, std::vector<VariableGroup*>& listVariableGroups) = 0;

			// 删除分组
			virtual bool DeleteGroup(uint16 usGroupId) = 0;

			// 清理
			virtual void Clear() = 0;
		};
		// 普通变量接口
		interface INormalVariableManager : public ICountor
		{
			// 是否变更
			virtual bool IsChanged() const = 0;

			// 获取错误
			virtual const char* GetErrorMsg() = 0;

			// 变量是否存在
			virtual bool IsVariableExisting(uint64 ullVariableId) = 0;
			virtual bool IsVariableExisting(const std::string& strVariableName) = 0;

			// 创建变量
			virtual bool CreateVariable(uint16 usMainGroupId, uint16 usSubGroupId, uint8 ucValueType, SystemVariable*& pVariable) = 0;
			virtual bool CreateVariables(uint16 usMainGroupId, uint16 usSubGroupId, uint8 ucValueType, uint8 ucNumber, std::vector<SystemVariable*>& listVariables) = 0;

			// 获取变量
			virtual bool GetVariable(uint64 ullVariableId, SystemVariable*& pVariable) = 0;
			virtual bool GetAllVariables(std::vector<SystemVariable*>& listVariables) = 0;
			virtual bool GetGroupedVariables(uint16 usGroupId, std::vector<SystemVariable*>& listVariables) = 0;

			// 删除指定变量
			virtual bool DeleteVariable(uint64 ullVariableId) = 0;

			// 更新变量名称：-1--更新失败/0--更新成功/1--名称重复
			virtual int32 UpdateVariableName(uint64 ullVariableIdToUpdate, const std::string& strNewVariableName) = 0;

			// 指定变量分组
			virtual bool GroupVariable(uint64 ullVariableId, uint16 usMainGroupId, uint16 usSubGroupId) = 0;
			virtual bool GroupVariables(std::vector<uint64>& listVariableIds, uint16 usMainGroupId, uint16 usSubGroupId) = 0;

			// 删除指定分组变量
			virtual bool DeleteGroupVariables(uint16 usGroupId) = 0;

			// 更新变量值
			virtual bool UpdateVariableValue(uint64 ullVariableId, const std::string& strVariableValue) = 0;

			// 清理
			virtual void Clear() = 0;
		};
		// 全局变量
		using IGlobalVariableManager = INormalVariableManager;
		// 临时变量
		using ILocalVariableManager = INormalVariableManager;
		// 配方变量
		using IRecipeVariableManager = INormalVariableManager;
		// 安全变量
		interface ISafeVariableManager : public ICountor
		{
			// 是否变更
			virtual bool IsChanged() const = 0;

			// 获取错误
			virtual const char* GetErrorMsg() = 0;

			// 变量是否存在
			virtual bool IsVariableExisting(uint64 ullVariableId) = 0;
			virtual bool IsVariableExisting(const std::string& strVariableName) = 0;

			// 创建变量
			virtual bool CreateVariable(uint16 usMainGroupId, uint16 usSubGroupId, SafeVariable*& pVariable) = 0;
			virtual bool CreateVariables(uint16 usMainGroupId, uint16 usSubGroupId, uint8 ucNumber, std::vector<SafeVariable*>& listVariables) = 0;

			// 获取变量
			virtual bool GetVariable(uint64 ullVariableId, SafeVariable*& pVariable) = 0;
			virtual bool GetAllVariables(std::vector<SafeVariable*>& listVariables) = 0;
			virtual bool GetGroupedVariables(uint16 usGroupId, std::vector<SafeVariable*>& listVariables) = 0;

			// 删除指定变量
			virtual bool DeleteVariable(uint64 ullVariableId) = 0;

			// 更新变量名称：-1--更新失败/0--更新成功/1--名称重复
			virtual int32 UpdateVariableName(uint64 ullVariableIdToUpdate, const std::string& strNewVariableName) = 0;

			// 指定变量分组
			virtual bool GroupVariable(uint64 ullVariableId, uint16 usMainGroupId, uint16 usSubGroupId) = 0;
			virtual bool GroupVariables(std::vector<uint64>& listVariableIds, uint16 usMainGroupId, uint16 usSubGroupId) = 0;

			// 删除指定分组变量
			virtual bool DeleteGroupVariables(uint16 usGroupId) = 0;

			// 创建条件项：ullVariableId表示变量id
			virtual bool CreateCondition(uint64 ullVariableId, lg::Condition*& pCondition) = 0;

			// 删除条件项：ullVariableId表示变量id，uiConditionId表示条件id
			virtual bool DeleteCondition(uint64 ullVariableId, uint32 uiConditionId) = 0;

			// 转换普通变量
			virtual bool ToNormalVariables(std::vector<SystemVariable*>& listVariables) = 0;

			// 清理
			virtual void Clear() = 0;

		};
		// 设备变量接口
		interface IDeviceVariableManager : public ICountor
		{
			// 获取DI变量
			virtual bool GetDIVariables(std::vector<SystemVariable*>& listVariables) = 0;

			// 获取DO变量
			virtual bool GetDOVariables(std::vector<SystemVariable*>& listVariables) = 0;

			// 获取AI变量
			virtual bool GetAIVariables(std::vector<SystemVariable*>& listVariables) = 0;

			// 获取AO变量
			virtual bool GetAOVariables(std::vector<SystemVariable*>& listVariables) = 0;

			// 获取运动轴变量
			virtual bool GetAxisVariables(std::vector<SystemVariable*>& listVariables) = 0;

			// 获取气油缸变量
			virtual bool GetCylinderVariables(std::vector<SystemVariable*>& listVariables) = 0;

			// 获取系统变量
			virtual bool GetSystemVariables(std::vector<SystemVariable*>& listVariables) = 0;

			// 获取所有变量
			virtual bool GetAllVariables(std::vector<SystemVariable*>& listVariables) = 0;
		};
	}

	// 高级功能接口
	namespace adv {
		// 自定义脚本接口
		interface IExtendScriptManager : public ICountor
		{
		public:
			// 是否变更
			virtual bool IsChanged() const = 0;

			// 获取错误
			virtual const char* GetErrorMsg() = 0;

			// 清理
			virtual void Clear() = 0;

			// 脚本是否存在
			virtual bool IsExisting(const std::string& strScriptName) = 0;

			// 获取脚本
			virtual bool GetScript(const std::string& strScriptName, adv::ExtendScript*& pExtendScript) = 0;
			virtual bool GetScripts(std::vector<adv::ExtendScript*>& listExtendScripts) = 0;

			// 创建脚本：-1--失败/0--成功/1--名称重复
			virtual int32 CreateScript(const std::string& strScriptName, adv::ExtendScript*& pExtendScript) = 0;

			// 更新脚本：-1--失败/0--成功/1--名称重复
			virtual int32 UpdateScript(const std::string& strOldScriptName, adv::ExtendScript* pExtendScript) = 0;

			// 删除脚本：-1--失败/0--成功/1--不存在
			virtual int32 DeleteScript(const std::string& strScriptName) = 0;
		};
	}

	// 项目参数管理器接口
	namespace prj {
		interface IWorkingParamManager : public ICountor
		{
			// 是否变更
			virtual bool IsChanged() const = 0;

			// 获取错误
			virtual const char* GetErrorMsg() = 0;

			// 清理
			virtual void Clear() = 0;

			// 设置默认配方
			virtual bool SetDefaultRecipe(const std::string& strRecipeName) = 0;

			// 获取默认配方
			virtual const char* GetDefaultRecipe() = 0;

			// 设置回零脚本类型
			virtual bool SetHomeMoveScriptType(uint8 ucScriptType) = 0;

			// 获取回零脚本类型
			virtual uint8 GetHomeMoveScriptType() const = 0;

			// 在线调试功能是否打开
			virtual bool IsOnlineDebugOpened() const = 0;

			// 打开/关闭在线调试功能
			virtual bool OpenOnlineDebug(bool bOpen) = 0;

			// 获取数据网关参数
			virtual bool GetDataGateway(std::string& strAddress, uint16& usPort, uint32& uiTimeout) = 0;

			// 设置数据网关参数
			virtual bool SetDataGateway(const std::string& strAddress, uint16 usPort, uint32 uiTimeout) = 0;

			// 获取数据接收器参数
			virtual bool GetDataReceivers(std::vector<prj::DataServer*>& listDataReceivers) = 0;

			// 添加数据接收器参数
			virtual bool AddDataReceiver(const std::string& strAddress, uint16 usPort, uint32 uiTimeout) = 0;
		};
	}

	// 项目管理器接口
	interface IProjectManager : public ICountor
	{
	public:
		// 枚举项目名称
		virtual bool EnumuerateProjects(std::vector<std::string>& listProjectNames) = 0;

		// 项目是否存在
		virtual bool IsProjectExisting(const std::string& strProjectName) = 0;

		// 项目是否打开
		virtual bool IsProjectOpened() = 0;
		virtual bool IsProjectOpened(const std::string& strProjectName) = 0;

		// 打开项目
		virtual bool OpenProject(const std::string& strProjectName) = 0;

		// 创建项目
		virtual bool CreateProject(const std::string& strProjectName) = 0;

		// 保存项目
		virtual bool SaveProject() = 0;

		// 另存项目
		virtual bool SaveProjectAs(const std::string& strProjectNewName) = 0;
		virtual bool SaveProjectAs(const std::string& strProjectOldName, const std::string& strProjectNewName) = 0;

		// 关闭项目
		virtual bool CloseProject() = 0;

		// 获取当前打开的项目
		virtual const char* GetCurrentProject() = 0;

		// 重命名项目
		virtual bool RenameProject(const std::string& strProjectNewName) = 0;
		virtual bool RenameProject(const std::string& strProjectOldName, const std::string& strProjectNewName) = 0;

		// 删除项目
		virtual bool DeleteProject() = 0;
		virtual bool DeleteProject(const std::string& strProjectName) = 0;

		// 枚举配方名称
		virtual bool EnumuerateRecipes(std::vector<std::string>& listRecipeNames) = 0;

		// 配方是否存在
		virtual bool IsRecipeExisting(const std::string& strRecipeName) = 0;

		// 配方是否打开
		virtual bool IsRecipeOpened() = 0;
		virtual bool IsRecipeOpened(const std::string& strRecipeName) = 0;

		// 新建配方
		virtual bool CreateRecipe(const std::string& strRecipeName) = 0;

		// 打开配方
		virtual bool OpenRecipe(const std::string& strRecipeName) = 0;

		// 保存配方
		virtual bool SaveRecipe() = 0;

		// 另存配方
		virtual bool SaveRecipeAs(const std::string& strRecipeNewName) = 0;
		virtual bool SaveRecipeAs(const std::string& strRecipeOldName, const std::string& strRecipeNewName) = 0;

		// 获取当前打开的配方
		virtual const char* GetCurrentRecipe() = 0;

		// 重命名配方
		virtual bool RenameRecipe(const std::string& strRecipeNewName) = 0;
		virtual bool RenameRecipe(const std::string& strRecipeOldName, const std::string& strRecipeNewName) = 0;

		// 删除配方
		virtual bool DeleteRecipe() = 0;
		virtual bool DeleteRecipe(const std::string& strRecipeName) = 0;

		// 是否变更
		virtual bool IsChanged() const = 0;

		// 获取错误
		virtual const char* GetErrorMsg() = 0;

		// 获取工作参数管理器接口
		virtual bool GetWorkingParamManager(prj::IWorkingParamManager*& pWorkingParamManager) = 0;

		// 获取用户管理接口
		virtual bool GetUserManager(usr::IUserManager*& pUserManager) = 0;

		// 获取设备管理器接口
		virtual bool GetDeviceManager(dev::IDeviceManager*& pDeviceManager) = 0;

		// 获取逻辑管理器接口
		virtual bool GetLogicManager(lg::ILogicManager*& pLogicManager) = 0;

		// 获取变量分组管理器接口
		virtual bool GetVariableGroupManager(vr::IVariableGroupManager*& pVariableGroupManager) = 0;

		// 获取安全变量管理器接口
		virtual bool GetSafeVariableManager(vr::ISafeVariableManager*& pSafeVariableManager) = 0;

		// 获取全局变量管理器接口
		virtual bool GetGlobalVariableManager(vr::IGlobalVariableManager*& pGlobalVariableManager) = 0;

		// 获取配方变量管理器接口
		virtual bool GetRecipeVariableManager(vr::IRecipeVariableManager*& pRecipeVariableManager) = 0;

		// 获取临时变量管理器接口
		virtual bool GetLocalVariableManager(vr::ILocalVariableManager*& pLocalVariableManager) = 0;

		// 获取设备变量管理器接口
		virtual bool GetDeviceVariableManager(vr::IDeviceVariableManager*& pDeviceVariableManager) = 0;

		// 获取自定义脚本管理接口
		virtual bool GetExtendScriptManager(yd::adv::IExtendScriptManager*& pExtendScriptManager) = 0;

		// 更新变量分组名称：-1--更新失败/0--更新成功/1--名称重复
		virtual int32 UpdateVariableGroupName(uint16 usGroupIdToUpdate, const std::string& strNewGroupName) = 0;

		// 更新逻辑任务名称：-1--更新失败/0--更新成功/1--名称重复
		virtual int32 UpdateLogicTaskName(uint32 uiTaskIdToUpdate, const std::string& strNewTaskName) = 0;

		// 更新逻辑过程名称：-1--更新失败/0--更新成功/1--名称重复
		virtual int32 UpdateLogicProcessName(uint32 uiTaskIdOfProcess, uint32 uiProcessIdToUpdate, const std::string& strNewProcessName) = 0;

		// 更新运动控制设备名称：-1--更新失败/0--更新成功/1--名称重复
		virtual int32 UpdateMotionDeviceName(uint32 uiDeviceIdToUpdate, const std::string& strNewDeviceName) = 0;

		// 更新运动控制轴名称：-1--更新失败/0--更新成功/1--名称重复
		virtual int32 UpdateMotionAxisName(uint32 uiDeviceIdOfAxis, uint16 usAxisIndexToUpdate, const std::string& strNewAxisName) = 0;

		// 更新气油缸名称：-1--更新失败/0--更新成功/1--名称重复
		virtual int32 UpdateCylinderName(uint32 uiDeviceIdToUpdate, const std::string& strNewDeviceName) = 0;

		// 更新DI名称：-1--更新失败/0--更新成功/1--名称重复
		virtual int32 UpdateDIName(uint32 uiDeviceIdOfDI, uint8 ucDIGroupType, uint16 usDIIndexToUpdate, const std::string& strNewDIName) = 0;

		// 更新DO名称：-1--更新失败/0--更新成功/1--名称重复
		virtual int32 UpdateDOName(uint32 uiDeviceIdOfDO, uint8 ucDOGroupType, uint16 usDOIndexToUpdate, const std::string& strNewDOName) = 0;

		// 更新AI名称：-1--更新失败/0--更新成功/1--名称重复
		virtual int32 UpdateAIName(uint32 uiDeviceIdOfAI, uint8 ucAIGroupType, uint16 usAIIndexToUpdate, const std::string& strNewAIName) = 0;

		// 更新AO名称：-1--更新失败/0--更新成功/1--名称重复
		virtual int32 UpdateAOName(uint32 uiDeviceIdOfAO, uint8 ucAOGroupType, uint16 usAOIndexToUpdate, const std::string& strNewAOName) = 0;

		// 获取所有变量
		virtual bool GetAllVariables(VRVARIABLES* pVariables) = 0;
		virtual bool GetAllVariables(std::vector<vr::SystemVariable*>& listVariables) = 0;

		// 获取流程接口方法对象
		virtual bool GetLogicProcessMethodObjects(std::vector<lib::MethodObject*>& listMethodObjects) = 0;

		// 获取指定流程接口方法对象
		virtual bool GetLogicProcessMethodObject(uint32 uiProcessId, std::vector<lib::MethodObject*>& listMethodObjects) = 0;

		// 获取设备接口方法对象
		virtual bool GetDeviceMethodObjects(std::vector<lib::MethodObject*>& listMethodObjects) = 0;

		// 获取指定设备接口方法对象
		virtual bool GetDeviceMethodObject(uint32 uiDeviceId, std::vector<lib::MethodObject*>& listMethodObjects) = 0;

		// 导出CSharp静态类
		virtual bool ExportCSharpStaticClasses(std::string& strContent) = 0;

		// 导出VB静态类
		virtual bool ExportVBStaticClasses(std::string& strContent) = 0;

		// 清理
		virtual void Clear() = 0;
	};

	typedef IProjectManager* (*funcGetIProjectManager)(uint32, const char*, uint8);
}

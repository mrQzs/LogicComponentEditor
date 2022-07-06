using System;
using System.Text;
using System.Runtime.InteropServices;
using YudaoMotionApi;

namespace YudaoMotionCollections
{
	// 运动轴静态容器类
	public static class YDAxisCollection
	{
		// 导出的运动轴实例
		public static YDAxis AX轴 = new YDAxis(0, 1, "AX轴");
		public static YDAxis AY轴 = new YDAxis(0, 2, "AY轴");
		public static YDAxis AZ轴 = new YDAxis(0, 3, "AZ轴");
		public static YDAxis A旋转轴 = new YDAxis(0, 4, "A旋转轴");
	}

	// 只读变量容器类
	public static class YDROVariableCollection
	{
		// 导出的变量实例
		public static YDROVariable<Boolean> AX轴_驱动器报警标志 = new YDROVariable<Boolean>(600001001000001, "AX轴_驱动器报警标志", true, false);
		public static YDROVariable<Boolean> AX轴_跟随误差标志 = new YDROVariable<Boolean>(600001001000002, "AX轴_跟随误差标志", true, false);
		public static YDROVariable<Boolean> AX轴_正限位触发标志 = new YDROVariable<Boolean>(600001001000003, "AX轴_正限位触发标志", true, false);
		public static YDROVariable<Boolean> AX轴_负限位触发标志 = new YDROVariable<Boolean>(600001001000004, "AX轴_负限位触发标志", true, false);
		public static YDROVariable<Boolean> AX轴_平滑停止标志 = new YDROVariable<Boolean>(600001001000005, "AX轴_平滑停止标志", true, false);
		public static YDROVariable<Boolean> AX轴_紧急停止标志 = new YDROVariable<Boolean>(600001001000006, "AX轴_紧急停止标志", true, false);
		public static YDROVariable<Boolean> AX轴_伺服使能标志 = new YDROVariable<Boolean>(600001001000007, "AX轴_伺服使能标志", true, false);
		public static YDROVariable<Boolean> AX轴_规划运动标志 = new YDROVariable<Boolean>(600001001000008, "AX轴_规划运动标志", true, false);
		public static YDROVariable<Boolean> AX轴_电机到位标志 = new YDROVariable<Boolean>(600001001000009, "AX轴_电机到位标志", true, false);
		public static YDROVariable<Boolean> AX轴_原点信号 = new YDROVariable<Boolean>(600001001000010, "AX轴_原点信号", true, false);
		public static YDROVariable<Boolean> AX轴_是否回零 = new YDROVariable<Boolean>(600001001000011, "AX轴_是否回零", true, false);
		public static YDROVariable<Boolean> AX轴_驱动使能 = new YDROVariable<Boolean>(600001001000012, "AX轴_驱动使能", true, false);
		public static YDROVariable<Byte> AX轴_回零状态 = new YDROVariable<Byte>(600001001000013, "AX轴_回零状态", 1, 0);
		public static YDROVariable<UInt32> AX轴_运动模式 = new YDROVariable<UInt32>(600001001000020, "AX轴_运动模式", 1000, 0);
		public static YDROVariable<Double> AX轴_目标位置 = new YDROVariable<Double>(600001001000033, "AX轴_目标位置", 999999, -999999);
		public static YDROVariable<Double> AX轴_目标速度 = new YDROVariable<Double>(600001001000034, "AX轴_目标速度", 999999, -999999);
		public static YDROVariable<Double> AX轴_规划位置 = new YDROVariable<Double>(600001001000021, "AX轴_规划位置", 999999, -999999);
		public static YDROVariable<Double> AX轴_规划速度 = new YDROVariable<Double>(600001001000022, "AX轴_规划速度", 999999, -999999);
		public static YDROVariable<Double> AX轴_规划加速度 = new YDROVariable<Double>(600001001000023, "AX轴_规划加速度", 999999, -999999);
		public static YDROVariable<Double> AX轴_规划减速度 = new YDROVariable<Double>(600001001000024, "AX轴_规划减速度", 999999, -999999);
		public static YDROVariable<Double> AX轴_编码器位置 = new YDROVariable<Double>(600001001000025, "AX轴_编码器位置", 999999, -999999);
		public static YDROVariable<Double> AX轴_编码器速度 = new YDROVariable<Double>(600001001000026, "AX轴_编码器速度", 999999, -999999);
		public static YDROVariable<Double> AX轴_编码器加速度 = new YDROVariable<Double>(600001001000027, "AX轴_编码器加速度", 999999, -999999);
		public static YDROVariable<Double> AX轴_编码器减速度 = new YDROVariable<Double>(600001001000028, "AX轴_编码器减速度", 999999, -999999);
		public static YDROVariable<Double> AX轴_编码器与规划位置差 = new YDROVariable<Double>(600001001000029, "AX轴_编码器与规划位置差", 999999, -999999);
		public static YDROVariable<UInt32> AX轴_编码器捕获方式 = new YDROVariable<UInt32>(600001001000030, "AX轴_编码器捕获方式", 600000, 0);
		public static YDROVariable<UInt32> AX轴_编码器捕获状态 = new YDROVariable<UInt32>(600001001000031, "AX轴_编码器捕获状态", 600000, 0);
		public static YDROVariable<Double> AX轴_编码器捕获值 = new YDROVariable<Double>(600001001000032, "AX轴_编码器捕获值", 999999, -999999);
		public static YDROVariable<Boolean> AY轴_驱动器报警标志 = new YDROVariable<Boolean>(600001002000001, "AY轴_驱动器报警标志", true, false);
		public static YDROVariable<Boolean> AY轴_跟随误差标志 = new YDROVariable<Boolean>(600001002000002, "AY轴_跟随误差标志", true, false);
		public static YDROVariable<Boolean> AY轴_正限位触发标志 = new YDROVariable<Boolean>(600001002000003, "AY轴_正限位触发标志", true, false);
		public static YDROVariable<Boolean> AY轴_负限位触发标志 = new YDROVariable<Boolean>(600001002000004, "AY轴_负限位触发标志", true, false);
		public static YDROVariable<Boolean> AY轴_平滑停止标志 = new YDROVariable<Boolean>(600001002000005, "AY轴_平滑停止标志", true, false);
		public static YDROVariable<Boolean> AY轴_紧急停止标志 = new YDROVariable<Boolean>(600001002000006, "AY轴_紧急停止标志", true, false);
		public static YDROVariable<Boolean> AY轴_伺服使能标志 = new YDROVariable<Boolean>(600001002000007, "AY轴_伺服使能标志", true, false);
		public static YDROVariable<Boolean> AY轴_规划运动标志 = new YDROVariable<Boolean>(600001002000008, "AY轴_规划运动标志", true, false);
		public static YDROVariable<Boolean> AY轴_电机到位标志 = new YDROVariable<Boolean>(600001002000009, "AY轴_电机到位标志", true, false);
		public static YDROVariable<Boolean> AY轴_原点信号 = new YDROVariable<Boolean>(600001002000010, "AY轴_原点信号", true, false);
		public static YDROVariable<Boolean> AY轴_是否回零 = new YDROVariable<Boolean>(600001002000011, "AY轴_是否回零", true, false);
		public static YDROVariable<Boolean> AY轴_驱动使能 = new YDROVariable<Boolean>(600001002000012, "AY轴_驱动使能", true, false);
		public static YDROVariable<Byte> AY轴_回零状态 = new YDROVariable<Byte>(600001002000013, "AY轴_回零状态", 1, 0);
		public static YDROVariable<UInt32> AY轴_运动模式 = new YDROVariable<UInt32>(600001002000020, "AY轴_运动模式", 1000, 0);
		public static YDROVariable<Double> AY轴_目标位置 = new YDROVariable<Double>(600001002000033, "AY轴_目标位置", 999999, -999999);
		public static YDROVariable<Double> AY轴_目标速度 = new YDROVariable<Double>(600001002000034, "AY轴_目标速度", 999999, -999999);
		public static YDROVariable<Double> AY轴_规划位置 = new YDROVariable<Double>(600001002000021, "AY轴_规划位置", 999999, -999999);
		public static YDROVariable<Double> AY轴_规划速度 = new YDROVariable<Double>(600001002000022, "AY轴_规划速度", 999999, -999999);
		public static YDROVariable<Double> AY轴_规划加速度 = new YDROVariable<Double>(600001002000023, "AY轴_规划加速度", 999999, -999999);
		public static YDROVariable<Double> AY轴_规划减速度 = new YDROVariable<Double>(600001002000024, "AY轴_规划减速度", 999999, -999999);
		public static YDROVariable<Double> AY轴_编码器位置 = new YDROVariable<Double>(600001002000025, "AY轴_编码器位置", 999999, -999999);
		public static YDROVariable<Double> AY轴_编码器速度 = new YDROVariable<Double>(600001002000026, "AY轴_编码器速度", 999999, -999999);
		public static YDROVariable<Double> AY轴_编码器加速度 = new YDROVariable<Double>(600001002000027, "AY轴_编码器加速度", 999999, -999999);
		public static YDROVariable<Double> AY轴_编码器减速度 = new YDROVariable<Double>(600001002000028, "AY轴_编码器减速度", 999999, -999999);
		public static YDROVariable<Double> AY轴_编码器与规划位置差 = new YDROVariable<Double>(600001002000029, "AY轴_编码器与规划位置差", 999999, -999999);
		public static YDROVariable<UInt32> AY轴_编码器捕获方式 = new YDROVariable<UInt32>(600001002000030, "AY轴_编码器捕获方式", 600000, 0);
		public static YDROVariable<UInt32> AY轴_编码器捕获状态 = new YDROVariable<UInt32>(600001002000031, "AY轴_编码器捕获状态", 600000, 0);
		public static YDROVariable<Double> AY轴_编码器捕获值 = new YDROVariable<Double>(600001002000032, "AY轴_编码器捕获值", 999999, -999999);
		public static YDROVariable<Boolean> AZ轴_驱动器报警标志 = new YDROVariable<Boolean>(600001003000001, "AZ轴_驱动器报警标志", true, false);
		public static YDROVariable<Boolean> AZ轴_跟随误差标志 = new YDROVariable<Boolean>(600001003000002, "AZ轴_跟随误差标志", true, false);
		public static YDROVariable<Boolean> AZ轴_正限位触发标志 = new YDROVariable<Boolean>(600001003000003, "AZ轴_正限位触发标志", true, false);
		public static YDROVariable<Boolean> AZ轴_负限位触发标志 = new YDROVariable<Boolean>(600001003000004, "AZ轴_负限位触发标志", true, false);
		public static YDROVariable<Boolean> AZ轴_平滑停止标志 = new YDROVariable<Boolean>(600001003000005, "AZ轴_平滑停止标志", true, false);
		public static YDROVariable<Boolean> AZ轴_紧急停止标志 = new YDROVariable<Boolean>(600001003000006, "AZ轴_紧急停止标志", true, false);
		public static YDROVariable<Boolean> AZ轴_伺服使能标志 = new YDROVariable<Boolean>(600001003000007, "AZ轴_伺服使能标志", true, false);
		public static YDROVariable<Boolean> AZ轴_规划运动标志 = new YDROVariable<Boolean>(600001003000008, "AZ轴_规划运动标志", true, false);
		public static YDROVariable<Boolean> AZ轴_电机到位标志 = new YDROVariable<Boolean>(600001003000009, "AZ轴_电机到位标志", true, false);
		public static YDROVariable<Boolean> AZ轴_原点信号 = new YDROVariable<Boolean>(600001003000010, "AZ轴_原点信号", true, false);
		public static YDROVariable<Boolean> AZ轴_是否回零 = new YDROVariable<Boolean>(600001003000011, "AZ轴_是否回零", true, false);
		public static YDROVariable<Boolean> AZ轴_驱动使能 = new YDROVariable<Boolean>(600001003000012, "AZ轴_驱动使能", true, false);
		public static YDROVariable<Byte> AZ轴_回零状态 = new YDROVariable<Byte>(600001003000013, "AZ轴_回零状态", 1, 0);
		public static YDROVariable<UInt32> AZ轴_运动模式 = new YDROVariable<UInt32>(600001003000020, "AZ轴_运动模式", 1000, 0);
		public static YDROVariable<Double> AZ轴_目标位置 = new YDROVariable<Double>(600001003000033, "AZ轴_目标位置", 999999, -999999);
		public static YDROVariable<Double> AZ轴_目标速度 = new YDROVariable<Double>(600001003000034, "AZ轴_目标速度", 999999, -999999);
		public static YDROVariable<Double> AZ轴_规划位置 = new YDROVariable<Double>(600001003000021, "AZ轴_规划位置", 999999, -999999);
		public static YDROVariable<Double> AZ轴_规划速度 = new YDROVariable<Double>(600001003000022, "AZ轴_规划速度", 999999, -999999);
		public static YDROVariable<Double> AZ轴_规划加速度 = new YDROVariable<Double>(600001003000023, "AZ轴_规划加速度", 999999, -999999);
		public static YDROVariable<Double> AZ轴_规划减速度 = new YDROVariable<Double>(600001003000024, "AZ轴_规划减速度", 999999, -999999);
		public static YDROVariable<Double> AZ轴_编码器位置 = new YDROVariable<Double>(600001003000025, "AZ轴_编码器位置", 999999, -999999);
		public static YDROVariable<Double> AZ轴_编码器速度 = new YDROVariable<Double>(600001003000026, "AZ轴_编码器速度", 999999, -999999);
		public static YDROVariable<Double> AZ轴_编码器加速度 = new YDROVariable<Double>(600001003000027, "AZ轴_编码器加速度", 999999, -999999);
		public static YDROVariable<Double> AZ轴_编码器减速度 = new YDROVariable<Double>(600001003000028, "AZ轴_编码器减速度", 999999, -999999);
		public static YDROVariable<Double> AZ轴_编码器与规划位置差 = new YDROVariable<Double>(600001003000029, "AZ轴_编码器与规划位置差", 999999, -999999);
		public static YDROVariable<UInt32> AZ轴_编码器捕获方式 = new YDROVariable<UInt32>(600001003000030, "AZ轴_编码器捕获方式", 600000, 0);
		public static YDROVariable<UInt32> AZ轴_编码器捕获状态 = new YDROVariable<UInt32>(600001003000031, "AZ轴_编码器捕获状态", 600000, 0);
		public static YDROVariable<Double> AZ轴_编码器捕获值 = new YDROVariable<Double>(600001003000032, "AZ轴_编码器捕获值", 999999, -999999);
		public static YDROVariable<Boolean> A旋转轴_驱动器报警标志 = new YDROVariable<Boolean>(600001004000001, "A旋转轴_驱动器报警标志", true, false);
		public static YDROVariable<Boolean> A旋转轴_跟随误差标志 = new YDROVariable<Boolean>(600001004000002, "A旋转轴_跟随误差标志", true, false);
		public static YDROVariable<Boolean> A旋转轴_正限位触发标志 = new YDROVariable<Boolean>(600001004000003, "A旋转轴_正限位触发标志", true, false);
		public static YDROVariable<Boolean> A旋转轴_负限位触发标志 = new YDROVariable<Boolean>(600001004000004, "A旋转轴_负限位触发标志", true, false);
		public static YDROVariable<Boolean> A旋转轴_平滑停止标志 = new YDROVariable<Boolean>(600001004000005, "A旋转轴_平滑停止标志", true, false);
		public static YDROVariable<Boolean> A旋转轴_紧急停止标志 = new YDROVariable<Boolean>(600001004000006, "A旋转轴_紧急停止标志", true, false);
		public static YDROVariable<Boolean> A旋转轴_伺服使能标志 = new YDROVariable<Boolean>(600001004000007, "A旋转轴_伺服使能标志", true, false);
		public static YDROVariable<Boolean> A旋转轴_规划运动标志 = new YDROVariable<Boolean>(600001004000008, "A旋转轴_规划运动标志", true, false);
		public static YDROVariable<Boolean> A旋转轴_电机到位标志 = new YDROVariable<Boolean>(600001004000009, "A旋转轴_电机到位标志", true, false);
		public static YDROVariable<Boolean> A旋转轴_原点信号 = new YDROVariable<Boolean>(600001004000010, "A旋转轴_原点信号", true, false);
		public static YDROVariable<Boolean> A旋转轴_是否回零 = new YDROVariable<Boolean>(600001004000011, "A旋转轴_是否回零", true, false);
		public static YDROVariable<Boolean> A旋转轴_驱动使能 = new YDROVariable<Boolean>(600001004000012, "A旋转轴_驱动使能", true, false);
		public static YDROVariable<Byte> A旋转轴_回零状态 = new YDROVariable<Byte>(600001004000013, "A旋转轴_回零状态", 1, 0);
		public static YDROVariable<UInt32> A旋转轴_运动模式 = new YDROVariable<UInt32>(600001004000020, "A旋转轴_运动模式", 1000, 0);
		public static YDROVariable<Double> A旋转轴_目标位置 = new YDROVariable<Double>(600001004000033, "A旋转轴_目标位置", 999999, -999999);
		public static YDROVariable<Double> A旋转轴_目标速度 = new YDROVariable<Double>(600001004000034, "A旋转轴_目标速度", 999999, -999999);
		public static YDROVariable<Double> A旋转轴_规划位置 = new YDROVariable<Double>(600001004000021, "A旋转轴_规划位置", 999999, -999999);
		public static YDROVariable<Double> A旋转轴_规划速度 = new YDROVariable<Double>(600001004000022, "A旋转轴_规划速度", 999999, -999999);
		public static YDROVariable<Double> A旋转轴_规划加速度 = new YDROVariable<Double>(600001004000023, "A旋转轴_规划加速度", 999999, -999999);
		public static YDROVariable<Double> A旋转轴_规划减速度 = new YDROVariable<Double>(600001004000024, "A旋转轴_规划减速度", 999999, -999999);
		public static YDROVariable<Double> A旋转轴_编码器位置 = new YDROVariable<Double>(600001004000025, "A旋转轴_编码器位置", 999999, -999999);
		public static YDROVariable<Double> A旋转轴_编码器速度 = new YDROVariable<Double>(600001004000026, "A旋转轴_编码器速度", 999999, -999999);
		public static YDROVariable<Double> A旋转轴_编码器加速度 = new YDROVariable<Double>(600001004000027, "A旋转轴_编码器加速度", 999999, -999999);
		public static YDROVariable<Double> A旋转轴_编码器减速度 = new YDROVariable<Double>(600001004000028, "A旋转轴_编码器减速度", 999999, -999999);
		public static YDROVariable<Double> A旋转轴_编码器与规划位置差 = new YDROVariable<Double>(600001004000029, "A旋转轴_编码器与规划位置差", 999999, -999999);
		public static YDROVariable<UInt32> A旋转轴_编码器捕获方式 = new YDROVariable<UInt32>(600001004000030, "A旋转轴_编码器捕获方式", 600000, 0);
		public static YDROVariable<UInt32> A旋转轴_编码器捕获状态 = new YDROVariable<UInt32>(600001004000031, "A旋转轴_编码器捕获状态", 600000, 0);
		public static YDROVariable<Double> A旋转轴_编码器捕获值 = new YDROVariable<Double>(600001004000032, "A旋转轴_编码器捕获值", 999999, -999999);
		public static YDROVariable<Boolean> 前进后退气油缸前进_到位信号 = new YDROVariable<Boolean>(700002000000001, "前进后退气油缸前进_到位信号", true, false);
		public static YDROVariable<Boolean> 前进后退气油缸后退_到位信号 = new YDROVariable<Boolean>(700002000000002, "前进后退气油缸后退_到位信号", true, false);
		public static YDROVariable<Boolean> 前进后退气油缸前进_到位报警 = new YDROVariable<Boolean>(700002000000003, "前进后退气油缸前进_到位报警", true, false);
		public static YDROVariable<Boolean> 前进后退气油缸后退_到位报警 = new YDROVariable<Boolean>(700002000000004, "前进后退气油缸后退_到位报警", true, false);
		public static YDROVariable<Boolean> 前进后退气油缸前进_运动中 = new YDROVariable<Boolean>(700002000000005, "前进后退气油缸前进_运动中", true, false);
		public static YDROVariable<Boolean> 前进后退气油缸后退_运动中 = new YDROVariable<Boolean>(700002000000006, "前进后退气油缸后退_运动中", true, false);
		public static YDROVariable<Boolean> 前进后退气油缸前进_报警使能 = new YDROVariable<Boolean>(700002000000007, "前进后退气油缸前进_报警使能", true, false);
		public static YDROVariable<Boolean> 前进后退气油缸后退_报警使能 = new YDROVariable<Boolean>(700002000000008, "前进后退气油缸后退_报警使能", true, false);
		public static YDROVariable<Boolean> 上升下降气油缸上升_到位信号 = new YDROVariable<Boolean>(700003000000001, "上升下降气油缸上升_到位信号", true, false);
		public static YDROVariable<Boolean> 上升下降气油缸下降_到位信号 = new YDROVariable<Boolean>(700003000000002, "上升下降气油缸下降_到位信号", true, false);
		public static YDROVariable<Boolean> 上升下降气油缸上升_到位报警 = new YDROVariable<Boolean>(700003000000003, "上升下降气油缸上升_到位报警", true, false);
		public static YDROVariable<Boolean> 上升下降气油缸下降_到位报警 = new YDROVariable<Boolean>(700003000000004, "上升下降气油缸下降_到位报警", true, false);
		public static YDROVariable<Boolean> 上升下降气油缸上升_运动中 = new YDROVariable<Boolean>(700003000000005, "上升下降气油缸上升_运动中", true, false);
		public static YDROVariable<Boolean> 上升下降气油缸下降_运动中 = new YDROVariable<Boolean>(700003000000006, "上升下降气油缸下降_运动中", true, false);
		public static YDROVariable<Boolean> 上升下降气油缸上升_报警使能 = new YDROVariable<Boolean>(700003000000007, "上升下降气油缸上升_报警使能", true, false);
		public static YDROVariable<Boolean> 上升下降气油缸下降_报警使能 = new YDROVariable<Boolean>(700003000000008, "上升下降气油缸下降_报警使能", true, false);
		public static YDROVariable<Boolean> 气油缸1前进到位 = new YDROVariable<Boolean>(100001000000001, "气油缸1前进到位", true, false);
		public static YDROVariable<Boolean> 气油缸1后退到位 = new YDROVariable<Boolean>(100001000000002, "气油缸1后退到位", true, false);
		public static YDROVariable<Boolean> 气油缸2上升到位 = new YDROVariable<Boolean>(100001000000003, "气油缸2上升到位", true, false);
		public static YDROVariable<Boolean> 气油缸2下降到位 = new YDROVariable<Boolean>(100001000000004, "气油缸2下降到位", true, false);
		public static YDROVariable<Boolean> AX轴正向限位 = new YDROVariable<Boolean>(100001000001001, "AX轴正向限位", true, false);
		public static YDROVariable<Boolean> AY轴正向限位 = new YDROVariable<Boolean>(100001000001002, "AY轴正向限位", true, false);
		public static YDROVariable<Boolean> AZ轴正向限位 = new YDROVariable<Boolean>(100001000001003, "AZ轴正向限位", true, false);
		public static YDROVariable<Boolean> AX轴负向限位 = new YDROVariable<Boolean>(100001000002001, "AX轴负向限位", true, false);
		public static YDROVariable<Boolean> AY轴负向限位 = new YDROVariable<Boolean>(100001000002002, "AY轴负向限位", true, false);
		public static YDROVariable<Boolean> AZ轴负向限位 = new YDROVariable<Boolean>(100001000002003, "AZ轴负向限位", true, false);
		public static YDROVariable<Boolean> AX轴驱动报警 = new YDROVariable<Boolean>(100001000003001, "AX轴驱动报警", true, false);
		public static YDROVariable<Boolean> AY轴驱动报警 = new YDROVariable<Boolean>(100001000003002, "AY轴驱动报警", true, false);
		public static YDROVariable<Boolean> AZ轴驱动报警 = new YDROVariable<Boolean>(100001000003003, "AZ轴驱动报警", true, false);
		public static YDROVariable<Boolean> AX轴原点信号 = new YDROVariable<Boolean>(100001000004001, "AX轴原点信号", true, false);
		public static YDROVariable<Boolean> AY轴原点信号 = new YDROVariable<Boolean>(100001000004002, "AY轴原点信号", true, false);
		public static YDROVariable<Boolean> AZ轴原点信号 = new YDROVariable<Boolean>(100001000004003, "AZ轴原点信号", true, false);
		public static YDROVariable<Boolean> AX轴电机到位 = new YDROVariable<Boolean>(100001000005001, "AX轴电机到位", true, false);
		public static YDROVariable<Boolean> AY轴电机到位 = new YDROVariable<Boolean>(100001000005002, "AY轴电机到位", true, false);
		public static YDROVariable<Boolean> AZ轴电机到位 = new YDROVariable<Boolean>(100001000005003, "AZ轴电机到位", true, false);
		public static YDROVariable<Boolean> AX轴原点位置检查 = new YDROVariable<Boolean>(1210002000002001, "AX轴原点位置检查", true, false);
		public static YDROVariable<Boolean> AY轴原点位置检查 = new YDROVariable<Boolean>(1210002000002002, "AY轴原点位置检查", true, false);
		public static YDROVariable<Boolean> AZ轴原点位置检查 = new YDROVariable<Boolean>(1210002000002003, "AZ轴原点位置检查", true, false);
	}

	// 可读可写变量容器类
	public static class YDRWVariableCollection
	{
		// 导出的变量实例
		public static YDROVariable<Byte> 工作状态 = new YDROVariable<Byte>(1, "工作状态", 10, 0);
		public static YDROVariable<Byte> 控制模式 = new YDROVariable<Byte>(2, "控制模式", 10, 0);
		public static YDROVariable<Double> 全局速度百分比 = new YDROVariable<Double>(3, "全局速度百分比", 100, 0);
		public static YDROVariable<Boolean> 气油缸1前进控制 = new YDROVariable<Boolean>(200001000000001, "气油缸1前进控制", true, false);
		public static YDROVariable<Boolean> 气油缸1后退控制 = new YDROVariable<Boolean>(200001000000002, "气油缸1后退控制", true, false);
		public static YDROVariable<Boolean> 气油缸2上升下降控制 = new YDROVariable<Boolean>(200001000000003, "气油缸2上升下降控制", true, false);
		public static YDROVariable<Boolean> 箱内照明 = new YDROVariable<Boolean>(200001000000004, "箱内照明", true, false);
		public static YDROVariable<Boolean> A工位照明 = new YDROVariable<Boolean>(200001000000005, "A工位照明", true, false);
		public static YDROVariable<Boolean> B工位照明 = new YDROVariable<Boolean>(200001000000006, "B工位照明", true, false);
		public static YDRWVariable<Byte> 工作状态 = new YDRWVariable<Byte>(1, "工作状态", 10, 0);
		public static YDRWVariable<Byte> 控制模式 = new YDRWVariable<Byte>(2, "控制模式", 10, 0);
		public static YDRWVariable<CMotionApi.YD_MotionCoords> AXYZ坐标 = new YDRWVariable<CMotionApi.YD_MotionCoords>(910001000012013, "AXYZ坐标", CMotionApi.YD_API_VALUE_TYPE_MOTION_COORDS);
		public static YDRWVariable<CMotionApi.YD_MotionCoords> AXY坐标 = new YDRWVariable<CMotionApi.YD_MotionCoords>(910001000012014, "AXY坐标", CMotionApi.YD_API_VALUE_TYPE_MOTION_COORDS);
		public static YDRWVariable<Double> AX轴零点位置 = new YDRWVariable<Double>(910001000012001, "AX轴零点位置", 1000, 0);
		public static YDRWVariable<Double> AX轴目标位置 = new YDRWVariable<Double>(910001000012002, "AX轴目标位置", 1000, 0);
		public static YDRWVariable<Double> AX轴运动距离 = new YDRWVariable<Double>(910001000012003, "AX轴运动距离", 1000, 0);
		public static YDRWVariable<Double> AX轴运动速度 = new YDRWVariable<Double>(910001000012004, "AX轴运动速度", 1000, 0);
		public static YDRWVariable<Double> AY轴零点位置 = new YDRWVariable<Double>(910001000012005, "AY轴零点位置", 1000, 0);
		public static YDRWVariable<Double> AY轴目标位置 = new YDRWVariable<Double>(910001000012006, "AY轴目标位置", 1000, 0);
		public static YDRWVariable<Double> AY轴运动距离 = new YDRWVariable<Double>(910001000012007, "AY轴运动距离", 1000, 0);
		public static YDRWVariable<Double> AY轴运动速度 = new YDRWVariable<Double>(910001000012008, "AY轴运动速度", 1000, 0);
		public static YDRWVariable<Double> AZ轴零点位置 = new YDRWVariable<Double>(910001000012009, "AZ轴零点位置", 1000, 0);
		public static YDRWVariable<Double> AZ轴目标位置 = new YDRWVariable<Double>(910001000012010, "AZ轴目标位置", 1000, 0);
		public static YDRWVariable<Double> AZ轴运动距离 = new YDRWVariable<Double>(910001000012011, "AZ轴运动距离", 1000, 0);
		public static YDRWVariable<Double> AZ轴运动速度 = new YDRWVariable<Double>(910001000012012, "AZ轴运动速度", 1000, 0);
		public static YDRWVariable<Boolean> Bool测试变量 = new YDRWVariable<Boolean>(910001000012101, "Bool测试变量", true, false);
		public static YDRWVariable<SByte> Int8测试变量 = new YDRWVariable<SByte>(910001000012102, "Int8测试变量", 100, -100);
		public static YDRWVariable<Byte> UInt8测试变量 = new YDRWVariable<Byte>(910001000012103, "UInt8测试变量", 200, 0);
		public static YDRWVariable<Int16> Int16测试变量 = new YDRWVariable<Int16>(910001000012104, "Int16测试变量", 500, -600);
		public static YDRWVariable<UInt16> UInt16测试变量 = new YDRWVariable<UInt16>(910001000012105, "UInt16测试变量", 1000, 0);
		public static YDRWVariable<Int32> Int32测试变量 = new YDRWVariable<Int32>(910001000012106, "Int32测试变量", 1000, -1000);
		public static YDRWVariable<UInt32> UInt32测试变量 = new YDRWVariable<UInt32>(910001000012107, "UInt32测试变量", 60000, 0);
		public static YDRWVariable<Int64> Int64测试变量 = new YDRWVariable<Int64>(910001000012108, "Int64测试变量", 1000000, -1000000);
		public static YDRWVariable<UInt64> UInt64测试变量 = new YDRWVariable<UInt64>(910001000012109, "UInt64测试变量", 1000000, 0);
		public static YDRWVariable<Single> Float测试变量 = new YDRWVariable<Single>(910001000012110, "Float测试变量", 200, -200);
		public static YDRWVariable<Double> Double测试变量 = new YDRWVariable<Double>(910001000012111, "Double测试变量", 6000, -6000);
		public static YDRWVariable<String> String测试变量 = new YDRWVariable<String>(910001000012112, "String测试变量", CMotionApi.YD_API_VALUE_TYPE_STRING);
	}

	// 数字输入容器类
	public static class YDDigitalInputCollection
	{
		// 导出的数字输入实例
		public static YDDigitalInput 气油缸1前进到位 = new YDDigitalInput(0, 0, 1, "气油缸1前进到位");
		public static YDDigitalInput 气油缸1后退到位 = new YDDigitalInput(0, 0, 2, "气油缸1后退到位");
		public static YDDigitalInput 气油缸2上升到位 = new YDDigitalInput(0, 0, 3, "气油缸2上升到位");
		public static YDDigitalInput 气油缸2下降到位 = new YDDigitalInput(0, 0, 4, "气油缸2下降到位");
		public static YDDigitalInput AX轴正向限位 = new YDDigitalInput(0, 1, 1, "AX轴正向限位");
		public static YDDigitalInput AY轴正向限位 = new YDDigitalInput(0, 1, 2, "AY轴正向限位");
		public static YDDigitalInput AZ轴正向限位 = new YDDigitalInput(0, 1, 3, "AZ轴正向限位");
		public static YDDigitalInput AX轴负向限位 = new YDDigitalInput(0, 2, 1, "AX轴负向限位");
		public static YDDigitalInput AY轴负向限位 = new YDDigitalInput(0, 2, 2, "AY轴负向限位");
		public static YDDigitalInput AZ轴负向限位 = new YDDigitalInput(0, 2, 3, "AZ轴负向限位");
		public static YDDigitalInput AX轴驱动报警 = new YDDigitalInput(0, 3, 1, "AX轴驱动报警");
		public static YDDigitalInput AY轴驱动报警 = new YDDigitalInput(0, 3, 2, "AY轴驱动报警");
		public static YDDigitalInput AZ轴驱动报警 = new YDDigitalInput(0, 3, 3, "AZ轴驱动报警");
		public static YDDigitalInput AX轴原点信号 = new YDDigitalInput(0, 4, 1, "AX轴原点信号");
		public static YDDigitalInput AY轴原点信号 = new YDDigitalInput(0, 4, 2, "AY轴原点信号");
		public static YDDigitalInput AZ轴原点信号 = new YDDigitalInput(0, 4, 3, "AZ轴原点信号");
		public static YDDigitalInput AX轴电机到位 = new YDDigitalInput(0, 5, 1, "AX轴电机到位");
		public static YDDigitalInput AY轴电机到位 = new YDDigitalInput(0, 5, 2, "AY轴电机到位");
		public static YDDigitalInput AZ轴电机到位 = new YDDigitalInput(0, 5, 3, "AZ轴电机到位");
	}

	// 数字输出容器类
	public static class YDDigitalOutputCollection
	{
		// 导出的数字输出实例
		public static YDDigitalOutput 气油缸1前进控制 = new YDDigitalOutput(0, 0, 1, "气油缸1前进控制");
		public static YDDigitalOutput 气油缸1后退控制 = new YDDigitalOutput(0, 0, 2, "气油缸1后退控制");
		public static YDDigitalOutput 气油缸2上升下降控制 = new YDDigitalOutput(0, 0, 3, "气油缸2上升下降控制");
		public static YDDigitalOutput 箱内照明 = new YDDigitalOutput(0, 0, 4, "箱内照明");
		public static YDDigitalOutput A工位照明 = new YDDigitalOutput(0, 0, 5, "A工位照明");
		public static YDDigitalOutput B工位照明 = new YDDigitalOutput(0, 0, 6, "B工位照明");
	}

	// 气油缸容器类
	public static class YDCylinderCollection
	{
		// 导出的气油缸实例
	}
}

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
	}

	// 只读变量容器类
	public static class YDROVariableCollection
	{
		// 导出的变量实例
	}

	// 可读可写变量容器类
	public static class YDRWVariableCollection
	{
		// 导出的变量实例
		public static YDROVariable<Byte> 工作状态 = new YDROVariable<Byte>(1, "工作状态", 10, 0);
		public static YDROVariable<Byte> 控制模式 = new YDROVariable<Byte>(2, "控制模式", 10, 0);
		public static YDROVariable<Double> 全局速度百分比 = new YDROVariable<Double>(3, "全局速度百分比", 100, 0);
	}

	// 数字输入容器类
	public static class YDDigitalInputCollection
	{
		// 导出的数字输入实例
	}

	// 数字输出容器类
	public static class YDDigitalOutputCollection
	{
		// 导出的数字输出实例
	}

	// 气油缸容器类
	public static class YDCylinderCollection
	{
		// 导出的气油缸实例
	}
}

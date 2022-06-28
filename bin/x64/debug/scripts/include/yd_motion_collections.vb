Imports System
Imports System.Text
Imports System.Runtime.InteropServices
Imports YudaoMotionApi

Module YudaoMotionCollections
	'运动轴静态容器类
	Public Class YDAxisCollection
		'导出的运动轴实例
	End Class

	'只读变量容器类
	Public Class YDROVariableCollection
		'导出的变量实例
		Public Shared 工作状态 As YDROVariable(Of Byte) = New YDROVariable(Of Byte)(1, "工作状态", 1000, 0)
		Public Shared 控制模式 As YDROVariable(Of Byte) = New YDROVariable(Of Byte)(2, "控制模式", 1000, 0)
		Public Shared 全局速度百分比 As YDROVariable(Of Double) = New YDROVariable(Of Double)(3, "全局速度百分比", 100, 0)
	End Class

	'可读可写变量容器类
	Public Class YDRWVariableCollection
		'导出的变量实例
		Public Shared test As YDRWVariable(Of Boolean) = New YDRWVariable(Of Boolean)(9110001000000001, "test", True, False)
	End Class

	'数字输入容器类
	Public Class YDDigitalInputCollection
		'导出的数字输入实例
	End Class

	'数字输出容器类
	Public Class YDDigitalOutputCollection
		'导出的数字输出实例
	End Class

	'气油缸容器类
	Public Class YDCylinderCollection
		'导出的气油缸实例
	End Class
End Module

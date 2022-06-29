Imports System
Imports System.Runtime.InteropServices
Imports System.Threading
Imports System.Text
Imports YudaoMotionApi
Imports YudaoMotionCollections

Module YDApplication
	' 入口类
	Public Class YDEntry
		' 入口函数
		Public Function Execute(ByRef iResult As Int32) As Int32
			' 编写自定义代码（不能包含阻塞代码）
			Return iResult
		End Function
	End Class
End Module
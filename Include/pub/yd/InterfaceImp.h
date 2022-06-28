#pragma once
#include "yddef.h"

namespace yd
{
	class InterfaceImp :
		public IInterface
	{
		//获取错误代码
		virtual int32 GetLastErrorCode();

		//获取错误描述
		virtual const char* GetLastErrorMsg();

		//接口状态
		virtual uint8 GetStatus();

		//初始化组件对象
		virtual bool Init(IEvent* pHandler, uint64 handledata);

		//指派操作函数
		virtual bool Invoke(const char* name, IAutoData* inParam, uint64 userdata, IAutoData* outRet = nullptr);

		//无参数指派操作函数
		virtual bool Invoke(const char* name, uint64 userdata);


		//反初始化组件对象
		virtual void Uninit();
	};
}



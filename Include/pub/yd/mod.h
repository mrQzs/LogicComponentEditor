#pragma once

#include <yddef.h>

namespace yd
{	
	//AOI图像传递接口
	struct IAOIImage : public ICountor
	{
		//图像宽度
		virtual uint32 GetWidth() = 0;

		//图像高度
		virtual uint32 GetHeight() = 0;

		//图像颜色深度
		virtual uint32 GetDepth() = 0;

		//图像数据的大小
		virtual uint32 GetSize() = 0;

		//图像数据
		virtual byte* GetData()=0;
	};

	//通用的设备接口
	interface IDevice
	{
	};

	//算法接口
	interface IAlgorithm
	{

	};

	//逻辑控制接口
	interface ILogic
	{

	};

	//相机接口
	interface ICamera : public IDevice
	{
		//采集一次图像
		virtual bool Grab(IAOIImage*& outImage, IAutoData* inparams) = 0;

	};

	//PLC接口
	interface IPlc : public IDevice
	{

	};

	//运动控制卡接口
	interface IMotion : public IDevice
	{

	};
}
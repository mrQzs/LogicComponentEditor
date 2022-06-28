#include "InterfaceImp.h"

namespace yd
{
	//获取错误代码
	int32 InterfaceImp::GetLastErrorCode() {
		return 0;
	}

	//获取错误描述
	const char* InterfaceImp::GetLastErrorMsg() {
		return "";
	}

	uint8 InterfaceImp::GetStatus()
	{
		return INTERFACE_STATUS_UNINIT;
	}

	bool InterfaceImp::Init(IEvent* pHandler, uint64 handledata)
	{
		return false;
	}

	bool InterfaceImp::Invoke(const char* name, IAutoData* inParam, uint64 userdata, IAutoData* outRet)
	{
		return false;
	}

	bool InterfaceImp::Invoke(const char* name, uint64 userdata)
	{
		return false;
	}

	void InterfaceImp::Uninit()
	{
	}
}


#include "FactoryImp.h"

namespace yd
{
	//获取对象工厂相关信息
	uint32 FactoryImp::GetVersion()
	{
		return m_version;
	}
	const char* FactoryImp::GetName()
	{
		return m_name.c_str();
	}
	const char* FactoryImp::GetDesc()
	{
		return m_desc.c_str();
	}

	uint32 FactoryImp::GetAutoDataCount()
	{
		return (uint32)m_vecAutoDataInfo.size();
	}

	//获取工厂支持的接口数量
	uint32 FactoryImp::GetInterfaceCount()
	{
		return (uint32)m_vecInterfaceInfo.size();
	}

	bool FactoryImp::GetAutoDataInfo(uint32 index, IAutoDataInfo*& info)
	{
		size_t count = m_vecAutoDataInfo.size();
		if (index>=0 && index<count)
		{
			m_vecAutoDataInfo[index]->AddRef();
			info = m_vecAutoDataInfo[index];
			return true;
		}
		return false;
	}

	//获取接口信息
	bool FactoryImp::GetInterfaceInfo(uint32 index, IInterfaceInfo*& info)
	{
		size_t count = m_vecInterfaceInfo.size();
		if (index>=0 && index<count)
		{
			m_vecInterfaceInfo[index]->AddRef();
			info = m_vecInterfaceInfo[index];
			return true;
		}
		return false;
	}

	bool FactoryImp::GetAutoDataInfo(IAutoDataInfo*& info, uint64 id)
	{
		for (size_t i = 0; i < m_vecAutoDataInfo.size(); i++)
		{
			if (m_vecAutoDataInfo[i]->TypeID() == id)
			{
				m_vecAutoDataInfo[i]->AddRef();
				info = m_vecAutoDataInfo[i];

				return true;
			}
		}
		return false;
	}

	bool FactoryImp::GetInterfaceInfo(IInterfaceInfo*& info, uint64 id)
	{
		for (size_t i = 0; i < m_vecInterfaceInfo.size(); i++)
		{
			if (m_vecInterfaceInfo[i]->TypeID() == id)
			{
				m_vecInterfaceInfo[i]->AddRef();
				info = m_vecInterfaceInfo[i];

				return true;
			}
		}

		return false;
	}

	//ChangePassword
	//创建自动数据接口
	bool FactoryImp::CreateData(uint64 id, IAutoData** outObj, IAutoData* fromObj = nullptr)
	{
		for (size_t i = 0; i < m_vecAutoDataInfo.size(); i++)
		{
			if (m_vecAutoDataInfo[i]->TypeID() == id)
			{
				(*outObj) = m_vecAutoDataInfo[i]->CreateData(fromObj);

				return (*outObj) != nullptr;
			}
		}
		return false;
	}

	//创建一个接口
	bool FactoryImp::CreateInterface(IAutoData* propertys, IEvent* pHandler, uint64 handledata, uint64 id, IInterface*& outObj, const char* nameit)
	{
		for (size_t i=0;i<m_vecInterfaceInfo.size();i++)
		{
			if (m_vecInterfaceInfo[i]->TypeID()==id)
			{
				outObj = m_vecInterfaceInfo[i]->CreateInterface();

				return outObj != nullptr;
			}
		}
		
		return false;
	}
}

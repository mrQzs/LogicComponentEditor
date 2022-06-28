#pragma once
#include "ObjectPool.h"
#include "pubfuncs.h"
#include "yddef.h"
namespace yd
{
	
	using funcCreateInterface = std::function<IInterface* ()>;

	class InterfaceInfo:public IInterfaceInfo,public Base::Countor<InterfaceInfo>
	{

	public:
		InterfaceInfo(uint64 id,uint32 ver,LPCSTR name,LPCSTR classtype,LPCSTR desc,bool issafe,
			funcCreateInterface func,uint64 propertyid)
		{
			m_id = id;
			m_ver = ver;
			m_strName=name;
			m_strDesc=desc;
			m_isThreadSafe = issafe;
			m_strClassType = classtype;
			m_funcCreate = func;
			m_propertyid = propertyid;
		}

		bool AddMethodInfo(LPCSTR name,LPCSTR desc,uint64 inparamid,LPCSTR inname,uint64 outparam_id,LPCSTR outname)
		{
			
			methodinfo info;
			SAFE_STRCOPY(info.name, name);
			SAFE_STRCOPY(info.desc, desc);
			SAFE_STRCOPY(info.inparam_name, inname);
			SAFE_STRCOPY(info.outparam_name, outname);
			info.inparam_id = inparamid;
			info.outparam_id = outparam_id;
			m_vecMethodList.push_back(info);
			return true;
		}

		
		IInterface* CreateInterface()
		{
			if (m_funcCreate)
			{
				return m_funcCreate();
			}

			return false;
		}
		virtual uint32 AddRef()
		{
			return Base::Countor<InterfaceInfo>::AddRef();
		}
		virtual uint32 Release()
		{
			return Base::Countor<InterfaceInfo>::Release();
		}

		//接口对象ID
		virtual uint64 TypeID()
		{
			return m_id;
		}

		//接口对象名称
		virtual const char* TypeName()
		{
			return m_strName.c_str();
		}

		//类型名，可有多级分类，使用“:”为类级分隔符
		virtual const char* TypeClass()
		{
			return m_strClassType.c_str();
		}

		virtual const byte* Icon(uint32& icoSize)
		{
			icoSize = (uint32)m_vecIconBuff.size();
			return (const byte*)&m_vecIconBuff[0];
		}

		//接口对象版本
		virtual uint32 GetVer()
		{
			return m_ver;
		}

		//接口对象描述
		virtual const char* Desc()
		{
			return m_strDesc.c_str();
		}

		virtual bool IsThreadSafe() { return m_isThreadSafe; };

		virtual bool IsSupportInterface(uint64 interfaceid) { return false; };
		//
		virtual uint64 GetPropertyID()
		{
			
			return m_propertyid;
		}

		//获取方法数量
		virtual uint32 GetMethodCount()
		{
			return (uint32)m_vecMethodList.size();
		}

		//获取方法信息
		virtual bool GetMethodInfo(uint32 index, methodinfo& outinfo)
		{
			if (index>=0 && index<m_vecMethodList.size())
			{
				outinfo = m_vecMethodList[index];
				return true;
			}
			return false;
		}

private:
		uint64 m_id = 0;
		uint32 m_ver = 0;
		bool m_isThreadSafe = false;
		std::string m_strName;
		std::string m_strDesc;
		std::string m_strClassType;
		
		uint64 m_propertyid = 0;
		std::vector<methodinfo> m_vecMethodList;
		funcCreateInterface m_funcCreate;

		std::vector<byte> m_vecIconBuff;

	};
}



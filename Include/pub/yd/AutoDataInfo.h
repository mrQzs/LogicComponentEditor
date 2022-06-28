#pragma once
#include "yddef.h"
#include "ObjectPool.h"
#include "pubfuncs.h"
namespace yd
{

	using funcCreateData = std::function<IAutoData* (IAutoData* fromObj)>;

	class AutoDataInfo :public IAutoDataInfo, public Base::Countor<AutoDataInfo>
	{
	public:
		AutoDataInfo(uint64 id, LPCSTR name, LPCSTR desc, funcCreateData func)
		{
			m_id = id;
			m_strName = name;
			m_strDesc = desc;
			m_funcCreate = func;
		}

		bool AddMemberInfo(uint8 dt,uint64 id,LPCSTR name, LPCSTR desc,bool isarray,const char* lpszMinValue,const char* lpszMaxValue/*added by steven,20211111*/, uint64 ullExtendType/*added by steven,20220107*/)
		{

			datamemberinfo info;
			info.dt = dt;
			info.id = id;
			info.isarray = isarray;
			SAFE_STRCOPY(info.name, name);
			SAFE_STRCOPY(info.desc, desc);
			// added by steven,20211111
			SAFE_STRCOPY(info.minValue, lpszMinValue);
			SAFE_STRCOPY(info.maxValue, lpszMaxValue);
			// end of added,20211111
			info.extend_type = ullExtendType;// added by steven,20220107
			m_vecMemberList.push_back(info);
			return true;
		}

		IAutoData* CreateData(IAutoData* fromObj)
		{
			if (m_funcCreate)
			{
				return m_funcCreate(fromObj);
			}

			return false;
		}

		IAutoData* CreateData(const byte* buff, uint32 dsize)
		{
			if (m_funcCreate)
			{
				IAutoData* pData = m_funcCreate(nullptr);
				if (pData)
				{
					if (pData->SetData(buff,dsize)>0)
					{
						return pData;
					}
					pData->Release();
					pData = nullptr;
				}
				return pData;
			}

			return false;
		}

		virtual uint32 AddRef()
		{
			return Base::Countor<AutoDataInfo>::AddRef();
		}
		virtual uint32 Release()
		{
			return Base::Countor<AutoDataInfo>::Release();
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

		//获取数据成员数量
		virtual uint32 GetMemberCount()
		{
			return (uint32)m_vecMemberList.size();
		}

		//获取数据成员信息,可用于生成其它语言的结构代码
		virtual bool GetMemberInfo(uint32 index, datamemberinfo& outinfo)
		{
			if (index >= 0 && index < m_vecMemberList.size())
			{
				outinfo = m_vecMemberList[index];
				return true;
			}
			return false;
		}
		virtual bool GetMemberInfo(const std::string& name, datamemberinfo& outinfo) {
			for (auto& mem : m_vecMemberList) {
				if (0 == strcmp(name.c_str(), mem.name)) {
					outinfo = mem;
					return true;
				}
			}
			return false;
		}
		//获取数据成员id
		virtual uint64 GetMemberId(uint32 index) {
			datamemberinfo meminfo;
			if (this->GetMemberInfo(index, meminfo)) {
				return meminfo.id;
			}
			else {
				return 0;
			}
		}
		virtual uint64 GetMemberId(const std::string& name) {
			for (auto& mem : m_vecMemberList) {
				if (0 == strcmp(name.c_str(), mem.name)) {
					return mem.id;
				}
			}
			return 0;
		}

	private:
		uint64 m_id = 0;
		bool m_isarray = 0;
		uint8 m_dt= DATA_TYPE_NULL;
		std::string m_strName;
		std::string m_strDesc;

		std::vector<datamemberinfo> m_vecMemberList;
		funcCreateData m_funcCreate;
	};
}



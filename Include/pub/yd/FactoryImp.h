#pragma once
#include "InterfaceInfo.h"
#include "AutoDataInfo.h"
#include <string>
#include <functional>
#include <map>
#include <vector>

#define REG_AUTODATA(__classname)  reg_autodata<__classname>();
#define REG_INTERFACE(__classname)  reg_interface<__classname>();
namespace yd
{
	

	
	class FactoryImp :
		public IFactory
	{
	public:
		//获取对象工厂相关信息
		virtual uint32 GetVersion();
		virtual const char* GetName();
		virtual const char* GetDesc();

		//获取工厂支持的自动结构数量
		virtual uint32 GetAutoDataCount();

		//获取工厂支持的接口数量
		virtual uint32 GetInterfaceCount();

		//获取接口信息
		virtual bool GetAutoDataInfo(uint32 index, IAutoDataInfo*& info);

		//获取接口信息
		virtual bool GetInterfaceInfo(uint32 index, IInterfaceInfo*& info);

		//用ID获取自动结构信息
		virtual bool GetAutoDataInfo(IAutoDataInfo*& info, uint64 id);

		//用ID获取接口信息
		virtual bool GetInterfaceInfo(IInterfaceInfo*& info, uint64 id);

		//创建自动数据接口
		virtual bool CreateData(uint64 id, IAutoData** outObj, IAutoData* fromObj);

		//创建一个接口
		virtual bool CreateInterface(IAutoData* propertys, IEvent* pHandler, uint64 handledata,uint64 id, IInterface*& outObj, const char* nameit = nullptr);

protected:
		template<class _regclass>
		void reg_interface()
		{
			_regclass obj;
			yd::InterfaceInfo* info = new yd::InterfaceInfo(
				_regclass::s_modid(),
				obj.GetVer(),
				_regclass::s_modname(),
				_regclass::s_modclasstype(),
				_regclass::s_moddesc(),_regclass::s_IsThreadSafe(),[]() { return new _regclass(); },
				_regclass::s_propertyid());
			
			//yd::methodlist* lst = &_regclass::s_methodlist();
			for (size_t i = 0; i < _regclass::s_methodlist().size();i++)
			{
				info->AddMethodInfo(_regclass::s_methodlist()[i]->name, _regclass::s_methodlist()[i]->desc,
					_regclass::s_methodlist()[i]->inparam_id,
					_regclass::s_methodlist()[i]->inparam_name,
					_regclass::s_methodlist()[i]->outparam_id,
					_regclass::s_methodlist()[i]->outparam_name);
			}
			m_vecInterfaceInfo.push_back(info);
			
		}

		template<class _regclass>
		void reg_autodata()
		{
			_regclass obj;
			yd::AutoDataInfo* info = new yd::AutoDataInfo(
				_regclass::s_code(),
				_regclass::s_name(),
				_regclass::s_desc(), [](yd::IAutoData* fromObj) { return new _regclass(); });
			//const fieldlist& members = _regclass::s_fieldlist();
			for (size_t i = 0; i < _regclass::s_fieldlist().size(); i++)
			{
				info->AddMemberInfo((uint8)_regclass::s_fieldlist()[i]._dbo_type,
					_regclass::s_fieldlist()[i]._hash_code,
					_regclass::s_fieldlist()[i]._field_name.c_str(),
					_regclass::s_fieldlist()[i]._field_desc.c_str(),
					_regclass::s_fieldlist()[i]._is_array,
					_regclass::s_fieldlist()[i]._min_value.c_str(),/*added by steven,20211111*/
					_regclass::s_fieldlist()[i]._max_value.c_str()/*added by steven,20211111*/,
					_regclass::s_fieldlist()[i]._extend_type/*added by steven,20220107*/);
			}
			m_vecAutoDataInfo.push_back(info);

		}

protected:

		//对象工厂的版本
		uint32 m_version;

		//对象工厂的名称
		std::string m_name;

		//对象工厂的描述
		std::string m_desc;

		std::vector<InterfaceInfo*> m_vecInterfaceInfo;
		std::vector<AutoDataInfo*> m_vecAutoDataInfo;
	};

}


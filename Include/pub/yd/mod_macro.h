#pragma once

#include "yddef.h"
#include "pubfuncs.h"
#include <AutoStruct.h>
#include <vector>
#include "ObjectPool.h"
#include "IDCreator.h"

constexpr uint64 OFFSET_VARIABLE_TYPE	= 100000000000000;
constexpr uint64 OFFSET_DEVICE_ID		= 1000000000;
constexpr uint64 OFFSET_AXIS			= 1000000;
constexpr uint64 OFFSET_VALUE_TYPE		= 1000;
constexpr uint64 OFFSET_VALUE_ID		= 1;
// 生成变量Id
inline uint64 GenerateVariableId(
	uint64 ullVariableType,
	uint64 ullDeviceId,
	uint64 ullAxis,
	uint64 ullValueType,
	uint64 ullValueId) {
	return ullVariableType * OFFSET_VARIABLE_TYPE + 
		ullDeviceId * OFFSET_DEVICE_ID + 
		ullAxis * OFFSET_AXIS +
		ullValueType * OFFSET_VALUE_TYPE +
		ullValueId * OFFSET_VALUE_ID;
}
inline uint64 GenerateMultiAxisCoordVariablId(uint32 uiDeviceId) {
	return GenerateVariableId(VARIABLE_TYPE_CONTROL, uiDeviceId, 0, 0, 0);
}
inline uint64 GenerateDIVariableId(uint32 uiDeviceId, uint16 usDIType, uint16 usDIIndex) {
	return GenerateVariableId(VARIABLE_TYPE_DI, uiDeviceId, 0, usDIType, usDIIndex);
}
inline uint64 GenerateDOVariableId(uint32 uiDeviceId, uint16 usDOType, uint16 usDOIndex) {
	return GenerateVariableId(VARIABLE_TYPE_DO, uiDeviceId, 0, usDOType, usDOIndex);
}
inline uint64 GenerateAIVariableId(uint32 uiDeviceId, uint16 usAIType, uint16 usAIIndex) {
	return GenerateVariableId(VARIABLE_TYPE_AI, uiDeviceId, 0, usAIType, usAIIndex);
}
inline uint64 GenerateAOVariableId(uint32 uiDeviceId, uint16 usAOType, uint16 usAOIndex) {
	return GenerateVariableId(VARIABLE_TYPE_AO, uiDeviceId, 0, usAOType, usAOIndex);
}
inline uint64 GenerateAxisDataVariableId(uint32 uiDeviceId, uint16 usAxis, uint16 usValueId) {
	return GenerateVariableId(VARIABLE_TYPE_AXIS, uiDeviceId, usAxis, 0, usValueId);
}
inline uint64 GenerateAxisConfigVariableId(uint32 uiDeviceId, uint16 usAxis, uint16 usValueId) {
	return GenerateVariableId(VARIABLE_TYPE_CONFIG, uiDeviceId, usAxis, 0, usValueId);
}
inline uint64 GenerateCylinderVariableId(uint32 uiDeviceId, uint16 usValueId) {
	return GenerateVariableId(VARIABLE_TYPE_CYLINDER, uiDeviceId, 0, 0, usValueId);
}
inline uint64 GenerateLogicVariableId(uint8 ucLogicType, uint32 uiLogicId) {
	return GenerateVariableId(VARIABLE_TYPE_LOGIC, uiLogicId, 0, ucLogicType, 0);
}
// 分解变量
inline void ParseVariableId(
	const uint64& ullVariableId,
	uint16& usVariableType,
	uint32& uiDeviceId,
	uint16& usAxis,
	uint16& usValueType,
	uint16& usValueId) {
	usVariableType = (uint16)(ullVariableId / OFFSET_VARIABLE_TYPE);
	uiDeviceId = (uint32)((ullVariableId % OFFSET_VARIABLE_TYPE) / OFFSET_DEVICE_ID);
	usAxis = (uint16)((ullVariableId % OFFSET_DEVICE_ID) / OFFSET_AXIS);
	usValueType = (uint16)((ullVariableId % OFFSET_AXIS) / OFFSET_VALUE_TYPE);
	usValueId = (uint16)(ullVariableId % OFFSET_VALUE_TYPE);
}

typedef unsigned long long ull; //less typing

template <size_t I>
constexpr ull timeseed(const char* p, ull b) //Recursive function
{
	return timeseed<I - 1>(p, p[I] >= 48 && p[I] <= 57 ? b * 10 + p[I] : b);
}

template <>
constexpr ull timeseed<size_t(-1)>(const char* p, ull b) //Base case
{
	return b;
}

template <size_t I>
constexpr ull myhash(const char* p, ull b) //Recursive function
{
	return myhash<I - 1>(p, (b ^ p[I]) * timeseed< sizeof(__DATE__) - 2>(__DATE__, 0));
}

template <>
constexpr ull myhash<size_t(-1)>(const char* p, ull b) //Base case
{
	return b;
}

//This macro generates a variable of a given name with a hash of that name
#define CTH_GEN(x) constexpr static ull GID_##x = myhash<sizeof(#x) - 2>(#x, timeseed< sizeof(__TIME__)-2>(__TIME__, 0))
#define GEN_ID(x) myhash<sizeof(x) - 2>(x, timeseed< sizeof(__TIME__)-2>(__TIME__, 0))
namespace yd
{
	//特化STL的字符串类型
	template<>
	struct type_helper<yd::IAutoData*> :public type_helper_autodata_ptr<yd::IAutoData*> {
		static const stru_size_t dtsize = PTR_TYPE;
		static const bool isenum = false;
		static const bool isarray = false;
		static const bool isautodata = true;
		static const size_t code() { return typeid(IAutoData*).hash_code(); }
		static bool getarraysize(void* pMember, uint32& outSize)
		{
			return false;
		}
		static bool setarraysize(void* pMember, uint32& newSize)
		{
			return false;
		}
		static bool read(void* pMember, byte* pBuff, const stru_size_t inBuffSize, stru_size_t& outBuffSize)
		{
			IAutoData* ptr = *(IAutoData**)pMember;
			outBuffSize = ptr->GetData(pBuff, inBuffSize);
			return true;

		};
		static bool write(void* pMember, byte* pBuff, const stru_size_t inBuffSize, stru_size_t& outBuffSize)
		{
			IAutoData* ptr = *(IAutoData**)pMember;
			outBuffSize = ptr->SetData(pBuff, inBuffSize);
			return outBuffSize>0;
		};
		static bool datasize(void* pMember, uint32& outSize)
		{
			IAutoData* ptr = *(IAutoData**)pMember;
			outSize = ptr->GetSize();
			return true;
		}
		static bool get_val(void* pMember, void* outVal, size_t typecode)
		{
			IAutoData* ptr = *(IAutoData**)pMember;
			if (ptr->TypeID() == typecode || typeid(AutoStruct*).hash_code() == typecode)
			{
				AutoStruct** p = (AutoStruct**)(outVal);
				*p = *(AutoStruct**)pMember;
				return true;
			}
			return false;
		}
		static bool set_val(void* pMember, void* newVal, size_t typecode)
		{
			// 			_ty& field = *((_ty*)pMember);
			// 			field = *(newVal._Cast<_ty>());
			return true;
		}
		static bool get_item(void* pMember, uint32 itemindex, void* outVal, size_t typecode)
		{
			return false;
		}
		static bool set_item(void* pMember, uint32 itemindex, void* newVal, size_t typecode)
		{
			return false;
		}
	};
	VECTOR_REG(yd::IAutoData*);
	LIST_REG(yd::IAutoData*);



	typedef std::function<bool(IInterface* inobj, IAutoData* inParam, uint64 userdata, IAutoData* outRet)> funcCmd;
	struct methodinfoex :public yd::methodinfo
	{
		funcCmd _func;
	};

	using methodlist = std::vector<methodinfo*> ;

	struct CAutoData:public IAutoData,public AutoStruct
	{
	public:
		virtual uint64 TypeID()
		{
			return get_code();
		}
		virtual uint32 GetSize()
		{
			// added by steven,20211012,计算实例之间偏移量
			CalculateInstanceDifference();
			// end of added,20211012
			return get_size();
		}
		virtual uint32 GetData(byte*& outdata, uint32 maxsize)
		{
			// added by steven,20211012,计算实例之间偏移量
			CalculateInstanceDifference();
			// end of added,20211012
			stru_size_t outsize=0;
			if (write(outdata,maxsize,outsize))
			{
				return outsize;
			}

			return 0;
			
		}
		virtual uint32 SetData(const byte* pdata, uint32 dsize)
		{
			// added by steven,20211012,计算实例之间偏移量
			CalculateInstanceDifference();
			// end of added,20211012
			stru_size_t outsize = 0;
			if (read((byte*)pdata, dsize, outsize))
			{
				return outsize;
			}
			return 0;
		}
		virtual uint32 GetMemberCount()
		{
			return (uint32)get_fieldlist().size();
		}
		virtual bool GetMemberInfo(uint32 index, datamemberinfo& outinfo)
		{
			if (index>=0 && index < GetMemberCount())
			{
				outinfo.dt = (uint8)get_fieldlist()[index]._dbo_type;
				outinfo.id = get_fieldlist()[index]._hash_code;
				SAFE_STRCOPY(outinfo.name, get_fieldlist()[index]._field_name.c_str());
				SAFE_STRCOPY(outinfo.desc, get_fieldlist()[index]._field_desc.c_str());
				// added by steven,20211111
				SAFE_STRCOPY(outinfo.minValue, get_fieldlist()[index]._min_value.c_str());
				SAFE_STRCOPY(outinfo.maxValue, get_fieldlist()[index]._max_value.c_str());
				// end of added,20211111
				outinfo.extend_type = get_fieldlist()[index]._extend_type;// added by steven,20220107
				outinfo.isarray = get_fieldlist()[index]._is_array;
				return true;
			}
			return false;
		}
		virtual bool GetMemberInfo(const std::string& name, datamemberinfo& outinfo) {
			return this->GetMemberInfo(this->GetMemberIndex(name.c_str()), outinfo);
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
			return this->GetMemberId(this->GetMemberIndex(name.c_str()));
		}
		virtual uint32 GetMemberIndex(const char* name)
		{
			const fieldlist& members = get_fieldlist();
			for (uint32 i = 0; i < members.size(); i++)
			{
				if (members[i]._field_name == name) return i;
			}
			return 0xffffffff;
		}

		//added by steven,20211111
		//获取指定索引数据成员值范围
		virtual bool GetMemberValueRange(uint32 index, ValueRange* pValueRange) {
			if (nullptr == pValueRange) {
				return false;
			}
			datamemberinfo dataInfo;
			if (!this->GetMemberInfo(index, dataInfo)) {
				return false;
			}
			pValueRange->dataType = dataInfo.dt;
			SAFE_STRCOPY(pValueRange->minValue, dataInfo.minValue);
			SAFE_STRCOPY(pValueRange->maxValue, dataInfo.maxValue);
			pValueRange->valid = (strlen(pValueRange->minValue) > 0 && strlen(pValueRange->maxValue) > 0);

			return pValueRange->valid;
		}
		//end of added,20211111

		virtual bool GetArraySize(uint32 index, uint32& outSize)
		{
			return get_member_size(index,outSize);
		}
		virtual bool SetArraySize(uint32 index, uint32 newSize)
		{
			return set_member_size(index,newSize);
		}
		virtual bool GetMember(size_t index, void* outVal, size_t typecode)
		{
			// added by steven,20211012,计算实例之间偏移量
			CalculateInstanceDifference();
			// end of added,20211012
			return get_member(index, outVal, typecode);
		}
		virtual bool GetMemberItem(size_t index, uint32 itemindex, void* outVal, size_t typecode)
		{
			// added by steven,20211012,计算实例之间偏移量
			CalculateInstanceDifference();
			// end of added,20211012
			return get_item(index, itemindex, outVal, typecode);
		}
		virtual bool SetMember(size_t index, void* inVal, size_t typecode)
		{
			// added by steven,20211012,计算实例之间偏移量
			CalculateInstanceDifference();
			// end of added,20211012
			return set_member(index, inVal, typecode);
		}
		virtual bool SetMemberItem(size_t index, uint32 itemindex, void* inVal, size_t typecode)
		{
			// added by steven,20211012,计算实例之间偏移量
			CalculateInstanceDifference();
			// end of added,20211012
			return set_item(index, itemindex, inVal, typecode);
		}
		// added by steven,20211012,计算实例之间偏移量
	protected:
		void CalculateInstanceDifference() {
			if (0x0FFFFFFFFFFFFFFF == _difference_to_real_instance) {
				_difference_to_real_instance = (byte*)this - (byte*)get_instance();
			}
		}
		// end of added,20211012
	};
	
	class __method_register__
	{
	public:
		__method_register__(methodlist& methodlst,
			LPCSTR methodname, LPCSTR methoddesc,
			uint64 inid, LPCSTR inname,
			uint64 outid, LPCSTR outname,
			funcCmd reqfunc)
		{//初始化成员定义
#ifndef _M_CEE
			methodinfoex* method = new methodinfoex();
			SAFE_STRCOPY(method->name,methodname);
			SAFE_STRCOPY(method->desc, methoddesc);
			method->inparam_id = inid;
			method->outparam_id = outid;
			SAFE_STRCOPY(method->inparam_name, inname);
			SAFE_STRCOPY(method->outparam_name, outname);
			method->_func = reqfunc;
			methodlst.push_back(method);
#endif
		}
	};

}


#pragma region _def




#pragma region INTERFACE

#define INTERFACE_DEF(__THISCLASS,_TYPECLASS,_DESC,_PROPERTY)               \
typedef __THISCLASS thisClass;                                              \
protected:                                                                  \
int32 m_iLastErrorCode = 0;													\
std::string m_strLastErrorMsg = "";											\
uint8 m_status;																\
IDataManager* m_pDataManager = nullptr;										\
IEvent* m_pEventHandler = nullptr;											\
IInteractAction* m_pInteractAction = nullptr;								\
uint64  m_ullEventData = 0;													\
IAutoData* m_pExtendData = nullptr;											\
_PROPERTY* m_pParams=nullptr;												\
uint64 m_ullTimeout=0;														\
void* m_lpRefererence = nullptr;													\
public:                                                                        \
	static bool& s_IsThreadSafe(){ static bool issafe=false; return issafe;};   \
	static methodlist& s_methodlist(){static methodlist __class_##metlist##__;return __class_##metlist##__;}  \
	static uint64 s_modid(){return typeid(thisClass).hash_code();}									\
	static LPCSTR s_modname(){return #__THISCLASS;}	                           \
	static LPCSTR s_moddesc(){return _DESC;}                                   \
	static LPCSTR s_modclasstype(){ return _TYPECLASS;}    \
	virtual uint32 AddRef(){ return Base::Countor<__THISCLASS>::AddRef();};					\
	virtual uint32 Release() { return Base::Countor<__THISCLASS>::Release(); };				\
	virtual uint64 TypeID() { return s_modid(); };								\
	virtual const char* TypeName() {return s_modname();};												\
	virtual const char* TypeClass(){ return s_modclasstype();};       \
	virtual const char* Desc() {return s_moddesc();};												\
	virtual const byte* Icon(uint32& icoSize){ icoSize=0;return nullptr;};			\
	virtual bool IsThreadSafe(){return s_IsThreadSafe();};    \
	virtual uint32 GetMethodCount() { return (uint32)s_methodlist().size();};											\
	virtual bool GetMethodInfo(uint32 index, methodinfo& outinfo){            \
		if (index >= 0 && index < GetMethodCount())                            \
		{                                                                  \
			memcpy(&outinfo,&s_methodlist()[index],sizeof(methodinfo));     \
			return true;                                       \
		}                                                                  \
		return false;                                                    \
	}																	\
	virtual const char* GetName(){    \
		static IDCreator<0> gid;    \
		static std::string sName =std::string(s_modname()) + "-" + gid.GetIDString();     \
		return sName.c_str();   \
	};						\
	virtual int32 GetLastErrorCode() {return m_iLastErrorCode;};				\
	virtual const char* GetLastErrorMsg() {return m_strLastErrorMsg.c_str();}	\
	virtual uint8 GetStatus() {return m_status;};									\
	virtual bool Invoke(const char* lpszMethodName, IAutoData* pInputData, uint64 ullUserData, IAutoData* pOutputData =nullptr) {		\
		for (int i=0;i< s_methodlist().size();i++)		\
		{														\
			if (strcmp(lpszMethodName, s_methodlist()[i]->name) == 0)			\
			{														\
				return ((methodinfoex*)s_methodlist()[i])->_func(this, pInputData, ullUserData, pOutputData);			\
			}														\
		}															\
		return false;												\
	};		\
	virtual void Uninit() {};    \
	static uint64 s_propertyid(){return _PROPERTY::s_code();}    \
	virtual bool Init(IDataManager* pDataManager, IEvent* pEventHandler, uint64 ullEventData, IAutoData* pExtendData, uint64 ullTimeout, IInteractAction* pInteractAction, void* lpRefer) {		\
			m_pDataManager = pDataManager;							\
			m_pEventHandler = pEventHandler;						\
			m_ullEventData = ullEventData;							\
			m_pExtendData = pExtendData;							\
			m_ullTimeout = ullTimeout;								\
			m_pInteractAction = pInteractAction;					\
			m_lpRefererence = lpRefer;								\
			if (pEventHandler){			\
				m_pParams = (_PROPERTY*)AutoStruct::BuildStruct(_PROPERTY::s_code());					\
			}					\
			return true;					\
	};		\
	virtual uint64 GetPropertyID(){return s_propertyid();};  \
	virtual bool GetProperty(size_t index, void* outVal, size_t typecode){    \
					if(m_pParams) return m_pParams->GetMember(index,outVal,typecode);   \
					return false;   \
				 };  \
	virtual bool GetPropertyItem(size_t index, uint32 itemindex, void* outVal, size_t typecode){    \
					if(m_pParams) return m_pParams->GetMemberItem(index,itemindex,outVal,typecode);   \
					return false;   \
				 };  \
	virtual bool SetProperty(size_t index, void* inVal, size_t typecode){    \
					if(m_pParams) return m_pParams->SetMember(index,inVal,typecode);   \
					return false;   \
				 };  \
	virtual bool SetPropertyItem(size_t index, uint32 itemindex, void* inVal, size_t typecode){    \
					if(m_pParams) return m_pParams->SetMemberItem(index,itemindex,inVal,typecode);   \
					return false;   \
				 };  \
	virtual bool GetPropertySize(uint32 index, uint32& outSize){    \
		if (m_pParams) return m_pParams->get_member_size(index,outSize);   \
		return false;   \
	}   \
	virtual bool SetPropertySize(uint32 index, uint32 newSize){    \
		if(m_pParams) return m_pParams->set_member_size(index,newSize);   \
					return false;   \
	}   \
	virtual void FireMessage(const char* msg,...){};			\
	virtual void FireInterfaceStatus(uint8 status){};			\
	virtual void FireExecRet(IAutoData* pData){};

#pragma endregion


#pragma region MEDTHOD
#define REG_MEDTHOD4(cmd_name,cmd_desc,outtype) public: virtual bool cmd_name(uint64 userdata,outtype* outRet=nullptr)=0;  \
	private:                                                                       \
	class __method_register_##cmd_name##_class__ {                   \
    public:                                                                    \
        __method_register_##cmd_name##_class__(){                       \
            static __method_register__ reg_##cmd_name(  \
                thisClass::s_methodlist(),                                 \
                #cmd_name,                                               \
				cmd_desc,                                               \
				0,                                    \
				"",													\
				outtype::s_code(),                                    \
				#outtype,													\
				[](IInterface* inobj, IAutoData* inParam, uint64 userdata,IAutoData* outRet) {      \
					return ((thisClass*)inobj)->##cmd_name(userdata,(outtype*)outRet);      \
				});                                  \
        }                                                               \
    }__method__##cmd_name##_register;
#define REG_MEDTHOD6(cmd_name,cmd_desc,intype,outtype) public: virtual bool cmd_name(intype* inobj,uint64 userdata,outtype* outRet=nullptr)=0;  \
	private:                                                                       \
	class __method_register_##cmd_name##_class__  {                          \
    public:                                                                    \
        __method_register_##cmd_name##_class__()   {                                 \
            static __method_register__ reg_##cmd_name(  \
                thisClass::s_methodlist(),                                 \
                #cmd_name,                                               \
				cmd_desc,                                               \
				intype::s_code(),                                    \
				#intype,													\
				outtype::s_code(),                                    \
				#outtype,													\
				[](IInterface* inobj, IAutoData* inParam, uint64 userdata,IAutoData* outRet) {      \
					return ((thisClass*)inobj)->##cmd_name((intype*)inParam,userdata,(outtype*)outRet);      \
				});                                  \
        }                                                               \
    }__method__##cmd_name##_register;
#define METHOD_3(name,desc,outparam) REG_MEDTHOD4(name,desc,outparam)
#define METHOD_4(name,desc,inparam,outparam) REG_MEDTHOD6(name,desc,inparam,outparam)

#define METHOD(...) INVOKE_VAR_MACRO(METHOD_,__VA_ARGS__);
#pragma endregion MEDTHOD


//自动结构的宏定义

#define AUTO_DATA_BEGIN(__CLASSNAME,__DESC)  \
struct __CLASSNAME;   \
template<> struct type_helper<__CLASSNAME*>: public type_helper_autodata_ptr<__CLASSNAME>{};  \
VECTOR_REG(__CLASSNAME*);  \
LIST_REG(__CLASSNAME*);   \
struct __CLASSNAME :public yd::CAutoData,public Base::Countor<__CLASSNAME>{   \
		STRU_DEF(__CLASSNAME,__DESC);   \
		uint32 AddRef(){return Base::Countor<__CLASSNAME>::AddRef(); };  \
		uint32 Release() { return Base::Countor<__CLASSNAME>::Release();};  \
		virtual const char* TypeName(){ return #__CLASSNAME; };
#define AUTO_DATA_END(__CLASSNAME)  };REG_STRU(__CLASSNAME)  \
template<> struct type_helper<__CLASSNAME>: public type_helper_autodata<__CLASSNAME>{};  \
VECTOR_REG(__CLASSNAME);  \
LIST_REG(__CLASSNAME);


#define INTERFACE_BEGIN_4(_classname,_typeclass,_desc,_property) struct _classname:public IInterface, public Base::Countor<_classname>  \
{  INTERFACE_DEF(_classname,_typeclass,_desc,_property)    \
virtual bool IsSupportInterface(uint64 interfaceid){return false;};   \
virtual bool GetInterface(uint64 interfaceid,IInterface*& outInterface){ return false;};
#define INTERFACE_BEGIN_5(_classname,_typeclass,_desc,_property,_base1) struct _classname:public IInterface,public Base::Countor<_classname>,  \
public _base1{  INTERFACE_DEF(_classname,_typeclass,_desc,_property)    \
virtual bool IsSupportInterface(uint64 interfaceid){   \
			if(typeid(_base1).hash_code()==interfaceid){  \
				return true;   \
				}    \
			return false;    \
		};   \
virtual bool GetInterface(uint64 interfaceid,IInterface*& outInterface){   \
			if(typeid(_base1).hash_code()==interfaceid){  \
				this->AddRef();outInterface = this;return true;   \
				}    \
			return false;    \
		};
#define INTERFACE_BEGIN_6(_classname,_typeclass,_desc,_property,_base1,_base2) struct _classname:public IInterface,public Base::Countor<_classname>,  \
public _base1,_base2{  INTERFACE_DEF(_classname,_typeclass,_desc,_property)    \
virtual bool IsSupportInterface(uint64 interfaceid){   \
			if(typeid(_base1).hash_code()==interfaceid || typeid(_base2).hash_code()==interfaceid){  \
				return true;   \
				}    \
			return false;    \
		};   \
virtual bool GetInterface(uint64 interfaceid,IInterface*& outInterface){   \
			if(typeid(_base1).hash_code()==interfaceid || typeid(_base2).hash_code()==interfaceid){  \
				this->AddRef();outInterface = this;return true;   \
				}    \
			return false;    \
		};
#define INTERFACE_BEGIN_7(_classname,_typeclass,_desc,_property,_base1,_base2,_base3) struct _classname:public IInterface,public Base::Countor<_classname>,  \
public _base1,_base2,_base3{  INTERFACE_DEF(_classname,_typeclass,_desc,_property)    \
virtual bool IsSupportInterface(uint64 interfaceid){   \
			if(typeid(_base1).hash_code()==interfaceid    \
				|| typeid(_base2).hash_code()==interfaceid   \
				|| typeid(_base3).hash_code() == interfaceid){  \
				return true;   \
				}    \
			return false;    \
		};   \
virtual bool GetInterface(uint64 interfaceid,IInterface*& outInterface){   \
			if(typeid(_base1).hash_code()==interfaceid   \
				|| typeid(_base2).hash_code() == interfaceid   \
				|| typeid(_base3).hash_code() == interfaceid){  \
				this->AddRef();outInterface = this;return true;   \
				}    \
			return false;    \
		};
#define INTERFACE_BEGIN_8(_classname,_typeclass,_desc,_property,_base1,_base2,_base3,_base4) struct _classname:public IInterface,public Base::Countor<_classname>,  \
public _base1,_base2,_base3,_base4{  INTERFACE_DEF(_classname,_typeclass,_desc,_property)    \
virtual bool IsSupportInterface(uint64 interfaceid){   \
			if(typeid(_base1).hash_code()==interfaceid   \
				|| typeid(_base2).hash_code() == interfaceid   \
				|| typeid(_base3).hash_code() == interfaceid   \
				|| typeid(_base4).hash_code() == interfaceid){  \
				return true;   \
				}    \
			return false;    \
		};   \
virtual bool GetInterface(uint64 interfaceid,IInterface*& outInterface){   \
			if(typeid(_base1).hash_code()==interfaceid   \
				|| typeid(_base2).hash_code() == interfaceid   \
				|| typeid(_base3).hash_code() == interfaceid   \
				|| typeid(_base4).hash_code() == interfaceid){  \
				this->AddRef();outInterface = this;return true;   \
				}    \
			return false;    \
		};
#define INTERFACE_BEGIN_9(_classname,_typeclass,_desc,_property,_base1,_base2,_base3,_base4,_base5) struct _classname:public IInterface,public Base::Countor<_classname>,  \
public _base1,_base2,_base3,_base4,_base5{  INTERFACE_DEF(_classname,_typeclass,_desc,_property)    \
virtual bool IsSupportInterface(uint64 interfaceid){   \
			if(typeid(_base1).hash_code()==interfaceid   \
				|| typeid(_base2).hash_code() == interfaceid   \
				|| typeid(_base3).hash_code() == interfaceid   \
				|| typeid(_base4).hash_code() == interfaceid   \
				|| typeid(_base5).hash_code() == interfaceid){  \
				return true;   \
				}    \
			return false;    \
		};   \
virtual bool GetInterface(uint64 interfaceid,IInterface*& outInterface){   \
			if(typeid(_base1).hash_code()==interfaceid   \
				|| typeid(_base2).hash_code() == interfaceid   \
				|| typeid(_base3).hash_code() == interfaceid   \
				|| typeid(_base4).hash_code() == interfaceid   \
				|| typeid(_base5).hash_code() == interfaceid){  \
				this->AddRef();outInterface = this;return true;   \
				}    \
			return false;    \
		};
#define INTERFACE_BEGIN_10(_classname,_typeclass,_desc,_property,_base1,_base2,_base3,_base4,_base5,_base6) struct _classname:public IInterface,public Base::Countor<_classname>,  \
public _base1,_base2,_base3,_base4,_base5,_base6{  INTERFACE_DEF(_classname,_typeclass,_desc,_property)    \
virtual bool IsSupportInterface(uint64 interfaceid){   \
			if(typeid(_base1).hash_code()==interfaceid   \
				|| typeid(_base2).hash_code() == interfaceid   \
				|| typeid(_base3).hash_code() == interfaceid   \
				|| typeid(_base4).hash_code() == interfaceid   \
				|| typeid(_base5).hash_code() == interfaceid   \
				|| typeid(_base6).hash_code() == interfaceid){  \
				return true;   \
				}    \
			return false;    \
		};   \
virtual bool GetInterface(uint64 interfaceid,IInterface*& outInterface){   \
			if(typeid(_base1).hash_code()==interfaceid   \
				|| typeid(_base2).hash_code() == interfaceid   \
				|| typeid(_base3).hash_code() == interfaceid   \
				|| typeid(_base4).hash_code() == interfaceid   \
				|| typeid(_base5).hash_code() == interfaceid   \
				|| typeid(_base6).hash_code() == interfaceid){  \
				this->AddRef();outInterface = this;return true;   \
				}    \
			return false;    \
		};
#define INTERFACE_END(_classname) };

#define INTERFACE_BEGIN(...) INVOKE_VAR_MACRO(INTERFACE_BEGIN_,__VA_ARGS__);





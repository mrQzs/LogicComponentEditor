#pragma once

#include <platform.h>
#include <functional>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <algorithm>
#include <sstream>
#include <fstream>
//#include <json11/json11.hpp>
//#include <tinyxml2/tinyxml2.h>
//#include <serializer/baseline_serializer.h>
//#include <serializer/baseline_deserializer.h>
#include <optional>

//using namespace tinyxml2;
#pragma warning(disable:4100)

// template <typename T>
// std::string SerializeToString(const T& t) {
// 	std::stringstream os;
// 	std::shared_ptr<Serializer> serializer(new BaselineSerializer(os));
// 	serializer->Serialize(t);
// 	return os.str();
// }
// 
// template <typename T>
// std::optional<T> ParseFromString(const std::string& str) {
// 	std::stringstream os;
// 	os << str;
// 	std::shared_ptr<Deserializer> deserializer(new BaselineDeserializer(os));
// 	T ret;
// 	if (deserializer->Deserialize(ret)) {
// 		return ret;
// 	}
// 	else {
// 		return {};
// 	}
// }

//获取成员变量的偏移量
#define __OFFSET__(__THECLASS,__MEMBER_NAME) ((uint32)((size_t)&((__THECLASS *)0)->__MEMBER_NAME))

//用于可变参数宏的定义
#define PRIVATE_ARGS_GLUE(x, y) x y
#define PRIVATE_MACRO_VAR_ARGS_IMPL_COUNT(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, N, ...) N
#define PRIVATE_MACRO_VAR_ARGS_IMPL(args) PRIVATE_MACRO_VAR_ARGS_IMPL_COUNT args
#define COUNT_MACRO_VAR_ARGS(...) PRIVATE_MACRO_VAR_ARGS_IMPL((__VA_ARGS__, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0))
#define PRIVATE_MACRO_CHOOSE_HELPER2(M, count)  M##count
#define PRIVATE_MACRO_CHOOSE_HELPER1(M, count) PRIVATE_MACRO_CHOOSE_HELPER2(M, count)
#define PRIVATE_MACRO_CHOOSE_HELPER(M, count)   PRIVATE_MACRO_CHOOSE_HELPER1(M, count)
#define INVOKE_VAR_MACRO(M, ...) PRIVATE_ARGS_GLUE(PRIVATE_MACRO_CHOOSE_HELPER(M, COUNT_MACRO_VAR_ARGS(__VA_ARGS__)), (__VA_ARGS__))

//自动结构的宏定义
#define AUTO_STRU_BEGIN(__CLASSNAME,_DESC) struct __CLASSNAME :public AutoStruct{ STRU_DEF(__CLASSNAME,_DESC);

//注册自动结构，用于自动结构的动态创建
#define REG_STRU(__THISCLASS) const AutoRegistor __THISCLASS##_regist(__THISCLASS::s_code(), []() {return new __THISCLASS(); });



//注册类的序列化支持宏
#pragma region STRU_DEF
#define STRU_DEF(__THISCLASS,__DESC)										\
using  thisClass=__THISCLASS;                                                 \
private:                                                                       \
	static stru_size_t s_static_size(){						\
		static stru_size_t static_size = 0;											\
		if(static_size>0) return static_size;						\
		const fieldlist& members = s_fieldlist();								\
		for (size_t i = 0; i < members.size(); i++){								\
			if (members[i]._store_size == PTR_TYPE) {static_size = PTR_TYPE;break;}			\
			static_size += members[i]._store_size;								\
		}																		\
		return static_size;														\
	}																		\
public:																			\
	static const char* s_desc(){ return __DESC;};    \
	static const char* s_name(){return #__THISCLASS;};     \
	static size_t s_code(){return typeid(__THISCLASS).hash_code();}                \
	static fieldlist& s_fieldlist() {  \
					static fieldlist __class_##memlist##__;							\
        return __class_##memlist##__;                                          \
    }														                   \
    virtual fieldlist& get_fieldlist(){                              \
        return s_fieldlist();													\
    }																		   \
	virtual size_t get_code(){return s_code();};								\
	virtual const char* get_name(){return s_name();};     \
	virtual stru_size_t get_static_size(){							\
		static stru_size_t static_size = s_static_size();						\
		return static_size;	}													\
	virtual void* get_pointer(){ return this;}


#pragma endregion


//FIELD定义宏
#pragma region FIELD


template<typename _Ty>
struct IsDBField
{
	constexpr static const bool getvalue()
	{
		static_assert (0, "DBO is not support this type, that only support real type and string!");
		return false;
	}
	static const bool value = getvalue();

};

#define DBOBJ_TYPE_TEMPLATE(__Type) template<> struct IsDBField<__Type>{static const bool value = true;};
DBOBJ_TYPE_TEMPLATE(std::string);
DBOBJ_TYPE_TEMPLATE(bool);
DBOBJ_TYPE_TEMPLATE(int8);
DBOBJ_TYPE_TEMPLATE(uint8);
DBOBJ_TYPE_TEMPLATE(int16);
DBOBJ_TYPE_TEMPLATE(uint16);
DBOBJ_TYPE_TEMPLATE(int32);
DBOBJ_TYPE_TEMPLATE(uint32);
DBOBJ_TYPE_TEMPLATE(int64);
DBOBJ_TYPE_TEMPLATE(uint64);
DBOBJ_TYPE_TEMPLATE(float);
DBOBJ_TYPE_TEMPLATE(double);

#define FIELD_REG(__FIELD_NAME,__FIELD_DESC,__FIELD_MIN,__FIELD_MAX/*added by steven,20211111*/,__EXTEND_TYPE/*added by steven,20220107*/)  \
private:                                                                       \
	class _field_register_##__FIELD_NAME##_                                   \
    {                                                                          \
    public:                                                                    \
        _field_register_##__FIELD_NAME##_()                                   \
        {                                                                      \
            static field_register reg_##__FIELD_NAME(  \
                thisClass::s_fieldlist(),  \
				typeid(__FIELD_NAME).name(),  \
				#__FIELD_NAME,  \
				__FIELD_DESC,  \
				__FIELD_MIN,/*added by steven,20211111*/\
				__FIELD_MAX,/*added by steven,20211111*/\
				__EXTEND_TYPE,/*added by steven,20220107*/\
				type_helper<decltype(__FIELD_NAME)>::code(),   \
				type_helper<decltype(__FIELD_NAME)>::isarray,    \
				type_helper<decltype(__FIELD_NAME)>::isenum,    \
				type_helper<decltype(__FIELD_NAME)>::isautodata,    \
				__OFFSET__(thisClass,__FIELD_NAME),                             \
				type_helper<decltype(__FIELD_NAME)>::dtsize,               \
				type_helper<decltype(__FIELD_NAME)>::read,  \
				type_helper<decltype(__FIELD_NAME)>::write,			\
				type_helper<decltype(__FIELD_NAME)>::datasize,			\
				type_helper<decltype(__FIELD_NAME)>::getarraysize,			\
				type_helper<decltype(__FIELD_NAME)>::setarraysize,			\
				type_helper<decltype(__FIELD_NAME)>::get_val,			\
				type_helper<decltype(__FIELD_NAME)>::set_val,			\
				type_helper<decltype(__FIELD_NAME)>::get_item,			\
				type_helper<decltype(__FIELD_NAME)>::set_item,			\
				type_helper<decltype(__FIELD_NAME)>::fromstring,			\
				type_helper<decltype(__FIELD_NAME)>::tostring);			\
        }                                                                      \
    }__FIELD_NAME##_register;

#define FIELD_6(__FIELD_TYPE,__FIELD_NAME,__FIELD_DESC,__FIELD_MIN,__FIELD_MAX/*added by steven,20211111*/,__EXTEND_TYPE/*added by steven,20220107*/)                          \
public:                                                                        \
      __FIELD_TYPE __FIELD_NAME;											\
FIELD_REG(__FIELD_NAME,__FIELD_DESC,__FIELD_MIN,__FIELD_MAX/*added by steven,20211111*/,__EXTEND_TYPE/*added by steven,20220107*/)

#define FIELD_7(__FIELD_TYPE1,__FIELD_TYPE2,__FIELD_NAME,__FIELD_DESC,__FIELD_MIN,__FIELD_MAX/*added by steven,20211111*/,__EXTEND_TYPE/*added by steven,20220107*/)                          \
public:                                                                        \
      __FIELD_TYPE1##,##__FIELD_TYPE2 __FIELD_NAME;											\
FIELD_REG(__FIELD_NAME,__FIELD_DESC,__FIELD_MIN,__FIELD_MAX/*added by steven,20211111*/,__EXTEND_TYPE/*added by steven,20220107*/)

#define FIELD_8(__FIELD_TYPE1,__FIELD_TYPE2,__FIELD_TYPE3,__FIELD_NAME,__FIELD_DESC,__FIELD_MIN,__FIELD_MAX/*added by steven,20211111*/,__EXTEND_TYPE/*added by steven,20220107*/)                          \
public:                                                                        \
      __FIELD_TYPE1##,##__FIELD_TYPE2##,##__FIELD_TYPE3 __FIELD_NAME;											\
FIELD_REG(__FIELD_NAME,__FIELD_DESC,__FIELD_MIN,__FIELD_MAX/*added by steven,20211111*/,__EXTEND_TYPE/*added by steven,20220107*/)

#define FIELD_9(__FIELD_TYPE1,__FIELD_TYPE2,__FIELD_TYPE3,__FIELD_TYPE4,__FIELD_NAME,__FIELD_DESC,__FIELD_MIN,__FIELD_MAX/*added by steven,20211111*/,__EXTEND_TYPE/*added by steven,20220107*/)                          \
public:                                                                        \
      __FIELD_TYPE1##,##__FIELD_TYPE2##,##__FIELD_TYPE3##,##__FIELD_TYPE4 __FIELD_NAME;											\
FIELD_REG(__FIELD_NAME,__FIELD_DESC,__FIELD_MIN,__FIELD_MAX/*added by steven,20211111*/,__EXTEND_TYPE/*added by steven,20220107*/)

#define FIELD_10(__FIELD_TYPE1,__FIELD_TYPE2,__FIELD_TYPE3,__FIELD_TYPE4,__FIELD_TYPE5,__FIELD_NAME,__FIELD_DESC,__FIELD_MIN,__FIELD_MAX/*added by steven,20211111*/,__EXTEND_TYPE/*added by steven,20220107*/)                          \
public:                                                                        \
      __FIELD_TYPE1##,##__FIELD_TYPE2##,##__FIELD_TYPE3##,##__FIELD_TYPE4##,##__FIELD_TYPE5 __FIELD_NAME;											\
FIELD_REG(__FIELD_NAME,__FIELD_DESC,__FIELD_MIN,__FIELD_MAX/*added by steven,20211111*/,__EXTEND_TYPE/*added by steven,20220107*/)

#define FIELD_11(__FIELD_TYPE1,__FIELD_TYPE2,__FIELD_TYPE3,__FIELD_TYPE4,__FIELD_TYPE5,__FIELD_TYPE6,__FIELD_NAME,__FIELD_DESC,__FIELD_MIN,__FIELD_MAX/*added by steven,20211111*/,__EXTEND_TYPE/*added by steven,20220107*/)                          \
public:                                                                        \
      __FIELD_TYPE1##,##__FIELD_TYPE2##,##__FIELD_TYPE3##,##__FIELD_TYPE4##,##__FIELD_TYPE5##,##__FIELD_TYPE6 __FIELD_NAME;											\
FIELD_REG(__FIELD_NAME,__FIELD_DESC,__FIELD_MIN,__FIELD_MAX/*added by steven,20211111*/,__EXTEND_TYPE/*added by steven,20220107*/)

#define FIELD_12(__FIELD_TYPE1,__FIELD_TYPE2,__FIELD_TYPE3,__FIELD_TYPE4,__FIELD_TYPE5,__FIELD_TYPE6,__FIELD_TYPE7,__FIELD_NAME,__FIELD_DESC,__FIELD_MIN,__FIELD_MAX/*added by steven,20211111*/,__EXTEND_TYPE/*added by steven,20220107*/)                          \
public:                                                                        \
      __FIELD_TYPE1##,##__FIELD_TYPE2##,##__FIELD_TYPE3##,##__FIELD_TYPE4##,##__FIELD_TYPE5##,##__FIELD_TYPE6##,##__FIELD_TYPE7 __FIELD_NAME;											\
FIELD_REG(__FIELD_NAME,__FIELD_DESC,__FIELD_MIN,__FIELD_MAX/*added by steven,20211111*/,__EXTEND_TYPE/*added by steven,20220107*/)

#define FIELD_13(__FIELD_TYPE1,__FIELD_TYPE2,__FIELD_TYPE3,__FIELD_TYPE4,__FIELD_TYPE5,__FIELD_TYPE6,__FIELD_TYPE7,__FIELD_TYPE8,__FIELD_NAME,__FIELD_DESC,__FIELD_MIN,__FIELD_MAX/*added by steven,20211111*/,__EXTEND_TYPE/*added by steven,20220107*/)                          \
public:                                                                        \
      __FIELD_TYPE1##,##__FIELD_TYPE2##,##__FIELD_TYPE3##,##__FIELD_TYPE4##,##__FIELD_TYPE5##,##__FIELD_TYPE6##,##__FIELD_TYPE7##,##__FIELD_TYPE8 __FIELD_NAME;											\
FIELD_REG(__FIELD_NAME,__FIELD_DESC,__FIELD_MIN,__FIELD_MAX/*added by steven,20211111*/,__EXTEND_TYPE/*added by steven,20220107*/)


#define FIELD(...) INVOKE_VAR_MACRO(FIELD_,__VA_ARGS__);
#pragma endregion

//namespace AUTO
//{	
	//结构的大小定义
typedef uint32 stru_size_t;
static const stru_size_t PTR_TYPE = sizeof(stru_size_t) == 2 ? 0xFFFF : sizeof(stru_size_t) == 4 ? 0xFFFFFFFF : 0;
typedef std::function<bool(void*, byte*, const stru_size_t, stru_size_t&)> funcReadWrite;
typedef std::function<bool(void*, uint32&)> funcSize;
typedef std::function<bool(void*, void*, size_t typecode)> funcGetSetMember;
typedef std::function<bool(void*, uint32, void*, size_t typecode)> funcGetSetItem;
typedef std::function<bool(void*, std::stringstream&, const char*)> funcToString;
typedef std::function<bool(void*, std::string&, const char*)> funcFromString;

//结构字段信息
struct field_info
{
	field_info(
		const char* type_name,
		const char* field_name,
		const char* field_desc,
		// added by steven,20211111
		const char* min_value,
		const char* max_value,
		// end of added,20211111
		uint64 extend_type,// added by steven,20220107
		size_t hash_code,
		bool isarray,
		bool isenum,
		bool isautodata,
		stru_size_t store_size,
		stru_size_t pos_offset,
		funcReadWrite funcRead,
		funcReadWrite funcWrite,
		funcSize datasize,
		funcSize get_array_size,
		funcSize set_array_size,
		funcGetSetMember funcGetMember,
		funcGetSetMember funcSetMember,
		funcGetSetItem funcGetItem,
		funcGetSetItem funcSetItem,
		funcFromString funcfromstring,
		funcToString functotring)
	{
		_hash_code = hash_code;//字段类型的Hashcode
		_type_name = type_name;//字段类型名
		_field_name = field_name;//字段名称
		_field_desc = field_desc;//字段描述
		// added by steven,20211111
		_min_value = min_value;
		_max_value = max_value;
		// end of added,20211111
		_extend_type = extend_type;// added by steven,20220107
		_store_size = store_size;//字段存取方式与大小 0xFFFF/0xFFFFFFFF表示动态指针，存数据在动态数据区，0表示是空数据，其它表示存在静态数据区大小
		_pos_offset = pos_offset;//字段在结构中的偏移位置
		_funcRead = funcRead;//字段读方法
		_funcWrite = funcWrite;//字段写方法	
		_funcDataSize = datasize;
		_funcGetArraySize = get_array_size;
		_funcSetArraySize = set_array_size;
		_is_array = isarray;
		_funcGetMember = funcGetMember; //获取字段值
		_funcSetMember = funcSetMember; //设置字段值
		_funcGetItem = funcGetItem;    //获取容器子项值
		_funcSetItem = funcSetItem;   //设置容器子项值
		_funcFromString = funcfromstring;
		_funcToString = functotring;
		if (!isenum)
		{
			if (_hash_code == typeid(bool).hash_code())
			{
				_dbo_type = DATA_TYPE_BOOL;
			}
			else if (_hash_code == typeid(int8).hash_code())
			{
				_dbo_type = DATA_TYPE_INT8;
			}
			else if (_hash_code == typeid(uint8).hash_code())
			{
				_dbo_type = DATA_TYPE_UINT8;
			}
			else if (_hash_code == typeid(int16).hash_code())
			{
				_dbo_type = DATA_TYPE_INT16;
			}
			else if (_hash_code == typeid(uint16).hash_code())
			{
				_dbo_type = DATA_TYPE_UINT16;
			}
			else if (_hash_code == typeid(int32).hash_code())
			{
				_dbo_type = DATA_TYPE_INT32;
			}
			else if (_hash_code == typeid(uint32).hash_code())
			{
				_dbo_type = DATA_TYPE_UINT32;
			}
			else if (_hash_code == typeid(int64).hash_code())
			{
				_dbo_type = DATA_TYPE_INT64;
			}
			else if (_hash_code == typeid(uint64).hash_code())
			{
				_dbo_type = DATA_TYPE_UINT64;
			}
			else if (_hash_code == typeid(float).hash_code())
			{
				_dbo_type = DATA_TYPE_FLOAT;
			}
			else if (_hash_code == typeid(double).hash_code())
			{
				_dbo_type = DATA_TYPE_DOUBLE;
			}
			else if (_hash_code == typeid(std::string).hash_code())
			{
				_dbo_type = DATA_TYPE_STRING;
			}
			else
			{
				if (isautodata)
				{
					_dbo_type = DATA_TYPE_AUTODATA;
				}
				else
				{
					_dbo_type = DATA_TYPE_REALTYPE;
				}

			}
		}
		else
		{
			_dbo_type = DATA_TYPE_ENUM;
		}
	}



	uint8 _dbo_type = DATA_TYPE_NULL;//字段值类型
	bool        _is_array = false;//是否数组，如果是数组，则为vector容器	
	size_t _hash_code = 0;//字段类型的Hashcode
	std::string _type_name;//字段类型名
	std::string _field_name;//字段名称
	std::string _field_desc;//字段描述
	stru_size_t	_store_size = 0;//字段存取方式与大小 0xFFFF/0xFFFFFFFF表示动态指针，存数据在动态数据区，0表示是空数据，其它表示存在静态数据区大小
	stru_size_t	_pos_offset = 0;//字段在结构中的偏移位置
	funcReadWrite _funcRead;//字段读方法
	funcReadWrite _funcWrite;//字段写方法		
	funcSize    _funcDataSize;   //字段获取内存占用大小
	funcGetSetMember _funcGetMember; //获取字段值
	funcGetSetMember _funcSetMember; //设置字段值
	funcGetSetItem _funcGetItem;    //获取容器子项值
	funcGetSetItem _funcSetItem;   //设置容器子项值
	funcSize _funcGetArraySize;
	funcSize _funcSetArraySize;
	funcFromString _funcFromString;
	funcToString _funcToString;
	// added by steven,20211111
	std::string _min_value;
	std::string _max_value;
	// end of added,20211111
	uint64 _extend_type;// added by steven,20220107


};

typedef std::vector<field_info> fieldlist;

class field_register
{
public:
	field_register(
		fieldlist& memlist,
		const char* type_name,
		const char* field_name,
		const char* field_desc,
		// added by steven,20211111
		const char* min_value,
		const char* max_value,
		// end of added,20211111
		uint64 extend_type,// added by steven,20220107
		size_t hash_code,
		bool isarray,
		bool isenum,
		bool isautodata,
		stru_size_t pos_offset,
		stru_size_t store_size,
		funcReadWrite funcRead,
		funcReadWrite funcWrite,
		funcSize data_size,
		funcSize get_array_size,
		funcSize set_array_size,
		funcGetSetMember funcGetMember,
		funcGetSetMember funcSetMember,
		funcGetSetItem funcGetItem,
		funcGetSetItem funcSetItem,
		funcFromString funcfromstring,
		funcToString functotring)
	{//初始化成员定义
		field_info field(
			type_name,
			field_name,
			field_desc,
			// added by steven,20211111
			min_value,
			max_value,
			// end of added,20211111
			extend_type,// added by steven,20220107
			hash_code,
			isarray,
			isenum,
			isautodata,
			store_size,
			pos_offset,
			funcRead,
			funcWrite,
			data_size,
			get_array_size,
			set_array_size,
			funcGetMember,
			funcSetMember,
			funcGetItem,
			funcSetItem,
			funcfromstring,
			functotring);
		memlist.push_back(field);
	}
};


class AutoStruct
{
	friend class AutoRegistor;
	stru_size_t _size = 0;
public:
	AutoStruct() = default;
	~AutoStruct() = default;

	virtual void* get_pointer() = 0;
	virtual size_t get_code() = 0;
	virtual const char* get_name() = 0;
	virtual fieldlist& get_fieldlist() = 0;

	//************************************
	// description: 获取静态数据的大小
	// Method:     get_static_size
	// Access:     public 
	// Returns:    uint32 返回静态数据大小,如果非静态数据，返回0
	//************************************
	virtual stru_size_t get_static_size() = 0;

	template<typename _tyCast>
	bool get_member(uint32 index, _tyCast& outVal)
	{
		return get_member(index, &outVal, typeid(_tyCast).hash_code());
	}

	template<typename _tyCast>
	bool set_member(uint32 index, _tyCast& newVal)
	{
		return set_member(index, &newVal, typeid(_tyCast).hash_code());
	}

	template<typename _tyCast>
	bool get_item(uint32 index, uint32 itemindex, _tyCast& outVal)
	{
		return get_item(index, itemindex, &outVal, typeid(_tyCast).hash_code());
	}
	template<typename _tyCast>
	bool set_item(uint32 index, uint32 itemindex, _tyCast& newVal)
	{
		return get_item(index, itemindex, &newVal, typeid(_tyCast).hash_code());
	}

	bool get_member_size(uint32 index, uint32& outSize)
	{
		if (index >= 0 && index < get_fieldlist().size())
		{

			const field_info& info = get_fieldlist()[index];
			void* pMember = get_member_pointer(info._pos_offset);

			return info._funcGetArraySize(pMember, outSize);

		}
		return false;
	}
	bool set_member_size(uint32 index, uint32 newSize)
	{
		if (index >= 0 && index < get_fieldlist().size())
		{

			const field_info& info = get_fieldlist()[index];
			void* pMember = get_member_pointer(info._pos_offset);

			return info._funcSetArraySize(pMember, newSize);

		}
		return false;
	}

	//************************************
	// description: 获取结构的数据大小，如果结构是静态数据，请使用get_static_size来获取大小
	// Method:     get_size
	// Access:     public 
	// Parameter:  bool isUpdate		是否读取最新大小，true会重新计算结构的大小，false直接返回上次计算的大小，
	// Returns:    uint32 返回结构数据的大小，包含静态数据和动态数据
	//************************************
	stru_size_t get_size(bool isUpdate = false)
	{
		//如果是静态大小，直接返回结构的大小
		if (get_static_size() != PTR_TYPE) return get_static_size();

		//如果未更新过Size，或者强制更新
		if (_size == 0 || isUpdate == true)
		{
			stru_size_t ssize = 0;
			fieldlist& fields = get_fieldlist();
			for (size_t i = 0; i < fields.size(); i++)
			{
				uint32 outSize = 0;
				void* pMember = get_member_pointer(fields[i]._pos_offset);
				if (fields[i]._funcDataSize(pMember, outSize))
				{
					ssize += outSize;
				}

			}
			_size = ssize;
		}

		return _size;
	}

	//************************************
	// description:				从缓存中读取数据到字段成员
	// Method:     read
	// Access:     public 
	// Returns:    bool      返回读取结果 
	// Parameter:  byte * pBuff				要读取缓存中数据，
	// Parameter:  const uint16 inBuffSize  要读取缓存的大小
	// Parameter:  uint16 & outBuffSize		已读取缓存的大小。
	//************************************
	bool read(byte* pBuff, const stru_size_t inBuffSize, stru_size_t& outBuffSize)
	{
		outBuffSize = 0;
		const fieldlist& members = get_fieldlist();

		//待读取缓存为空，返回
		if (pBuff == nullptr || inBuffSize == 0)
		{
			_ASSERT(false);
			return false;
		}

		//如果无字段成员的空结构，返回失败；
		if (members.size() == 0)
		{
			_ASSERT(false);
			return false;
		}

		//获取静态数据大小
		// stru_size_t static_data_size = get_static_size();

		//如果结构是静态类型,直接复制内存,返回成功
		// deleted by steven,20211012,由于字节对其的问题导致直接内存复制失败
		/*
		if (static_data_size != PTR_TYPE)
		{
			void* pMember = get_member_pointer(members[0]._pos_offset);
			memcpy(pMember, pBuff, static_data_size);
			outBuffSize = static_data_size;
			return true;
		}
		*/
		// end of deleted,20211012

		//数据尾指针
		const byte* const pDataEnd = pBuff + inBuffSize;
		//数据指针
		byte* pData = pBuff;

		//读取结构字段成员列表
		for (size_t i = 0; i < members.size(); i++)
		{
			//成员指针
			void* pMember = get_member_pointer(members[i]._pos_offset);

			//读取缓存大小
			stru_size_t buffsize = (stru_size_t)(pDataEnd - pData);

			stru_size_t readsize = 0;

			if (members[i]._funcRead(pMember, pData, buffsize, readsize))
			{
				pData += readsize;
			}
			else
			{
				_ASSERT(false);
				return false;
			}

		}
		outBuffSize = (stru_size_t)(pData - pBuff);
		return true;
	};

	//************************************
	// description:				把成员字段数据写入到缓存中
	// Method:     write
	// Access:     public 
	// Returns:    bool		返回写入结果
	// Parameter:  byte * pBuff				要写数据的缓存，
	// Parameter:  const uint16 inBuffSize	要写入缓存的大小
	// Parameter:  uint16 & outBuffSize		已写缓存的大小。
	//************************************
	bool write(byte* pBuff, const stru_size_t inBuffSize, stru_size_t& outBuffSize)
	{
		outBuffSize = 0;
		const fieldlist& members = get_fieldlist();

		//待写入缓存为空，返回失败
		if (pBuff == nullptr || inBuffSize == 0)
		{
			_ASSERT(false);
			return false;
		}

		//如果无字段成员的空结构，返回失败；
		if (members.size() == 0)
		{
			_ASSERT(false);
			return false;
		}

		//如果缓存不足写入，返回失败；
		if (get_size() > inBuffSize)
		{
			_ASSERT(false);
			return false;
		}

		//获取静态数据大小
		// stru_size_t static_data_size = get_static_size();

		//如果结构是静态类型,直接复制内存,返回成功
		// deleted by steven,20211012,由于字节对其的问题导致直接内存复制失败
		/*
		if (static_data_size != PTR_TYPE)
		{
			void* pMember = get_member_pointer(members[0]._pos_offset);
			memcpy(pBuff, pMember, static_data_size);
			outBuffSize = static_data_size;
			return true;
		}
		*/
		// end of added,201211012

		//数据尾指针
		const byte* const pDataEnd = pBuff + inBuffSize;
		//数据指针
		byte* pData = pBuff;

		//写入结构字段成员列表
		for (size_t i = 0; i < members.size(); i++)
		{
			//成员指针
			void* pMember = get_member_pointer(members[i]._pos_offset);

			//写入缓存大小
			stru_size_t buffsize = (stru_size_t)(pDataEnd - pData);

			stru_size_t writesize = 0;

			if (members[i]._funcWrite(pMember, pData, buffsize, writesize))
			{
				pData += writesize;

			}
			else
			{
				_ASSERT(false);
				return false;
			}

		}

		outBuffSize = (stru_size_t)(pData - pBuff);
		return true;
	}

	//从字符串中读到内容，支持XML格式和JSON格式
	bool fromstring(std::string& strSrc, const char* format = "xml")
	{
		// 			XMLDocument doc;
		// 			if (doc.Parse(strSrc.c_str())==XML_SUCCESS)
		// 			{
		// 				XMLElement* root = doc.RootElement();
		// 				if (root && root->Name() && strcmp(root->Name(),"autostruct")==0)
		// 				{
		// 					uint64 code = root->Int64Attribute("typeid");
		// 					if (code == get_code())
		// 					{
		// 						std::map<std::string, XMLElement*> mapElement;
		// 						for (XMLElement* currentele = root->FirstChildElement(); currentele != nullptr;
		// 							currentele = currentele->NextSiblingElement())
		// 						{
		// 							if (currentele->Name() && strcmp(currentele->Name(),"field")==0 && currentele->Attribute("name"))
		// 							{
		// 								mapElement[currentele->Attribute("name")] = currentele;
		// 							}
		// 						}
		// 
		// 						const fieldlist& members = get_fieldlist();
		// 						for (size_t i = 0; i < members.size(); i++)
		// 						{
		// 							//查找元素是否存在
		// 							auto it = mapElement.find(members[i]._field_name);
		// 							if (it==mapElement.end())
		// 							{
		// 								return false;
		// 							}
		// 
		// 							//验证元素属性
		// 							if (it->second->Attribute("typeid")==nullptr || members[i]._hash_code!=(size_t)it->second->Int64Attribute("typeid")
		// 								|| it->second->Attribute("isarray") == nullptr || members[i]._is_array != it->second->BoolAttribute("isarray")
		// 								|| it->second->Attribute("type") == nullptr || members[i]._dbo_type != it->second->IntAttribute("type")
		// 								)
		// 							{
		// 								return false;
		// 							}
		// 
		// 							std::string strSrc;
		// 
		// 							if (XMLElement* content = it->second->FirstChildElement())
		// 							{
		// 								XMLPrinter printer;
		// 								content->Accept(&printer);
		// 								strSrc = printer.CStr();
		// 							}
		// 							else
		// 							{
		// 								strSrc = it->second->GetText();
		// 							}
		// 
		// 							void* pMember = (void*)(((byte*)this) + members[i]._pos_offset);							
		// 							if (members[i]._funcFromString(pMember,strSrc , format) == false)
		// 							{
		// 								return false;
		// 							}
		// 
		// 						}
		// 
		// 						return true;
		// 					}
		// 				}
		// 			}
		return false;
	}

	//序列化输出到字符串，支持XML格式和JSON格式
	bool tostring(std::string& strDest, const char* format = "xml")
	{
		std::stringstream ss;
		if (strcmp(format, "xml") == 0)
		{
			ss << "<autostruct typeid=\"" << get_code() << "\">\n";

			const fieldlist& members = get_fieldlist();
			for (size_t i = 0; i < members.size(); i++)
			{

				ss << "<field typeid=\"" << members[i]._hash_code << "\"";
				ss << " name=\"" << members[i]._field_name.c_str() << "\"";
				ss << " isarray=\"" << members[i]._is_array << "\"";
				ss << " type=\"" << members[i]._dbo_type << "\"";

				void* pMember = get_member_pointer(members[i]._pos_offset);

				if (members[i]._funcToString(pMember, ss, format) == false)
				{
					return false;
				}

				ss << "</field>\n";
			}


			ss << "</autostruct>\n";

			strDest += ss.str();

			return true;
		}
		else if (strcmp(format, "json") == 0)
		{
			return true;
		}
		return false;
	}

	//写入到文件中
	bool writefile(const char* filename, const char* format = "xml")
	{
		if (strcmp(filename, "") == 0) {
			return false;
		}

		std::ofstream outFile;
		//打开文件
		outFile.open(filename, std::ios::binary);
		if (!outFile.is_open()) {

			return false;
		}

		stru_size_t buffsize = get_size();
		if (buffsize > 0)
		{
			char* buff = new char[buffsize];
			stru_size_t outsize = 0;
			if (write((byte*)buff, buffsize, outsize))
			{
				outFile.write(buff, outsize);
				outFile.close();
				return true;
			}
		}
		return false;
	}

	//从文件中读取
	bool readfile(const char* filename, const char* format = "xml")
	{
		if (strcmp(filename, "") == 0) {
			return false;
		}
		std::ifstream inFile;
		//打开文件
		inFile.open(filename, std::ios::binary);
		if (!inFile.is_open()) {

			return false;
		}


		//获取文件长度
		inFile.seekg(0, std::ios::end);
		int64 bytes = inFile.tellg();
		inFile.seekg(0, std::ios::beg);

		if (bytes > 0)
		{
			char* buff = new char[bytes];
			//读取文件
			inFile.read(buff, bytes);//注意指针转为char*

			stru_size_t outsize = 0;

			bool ret = read((byte*)buff, (stru_size_t)bytes, outsize);
			delete[]buff;
			return ret;
		}

		inFile.close();

		return false;
	}

public:
	static bool isAutoObj(size_t code)
	{
		if (codes().find(code) != codes().end())
		{
			return true;
		}
		return false;
	}
	static AutoStruct* BuildStruct(AutoStruct* pSrc)
	{

		return nullptr;
	}
	static AutoStruct* BuildStruct(size_t code, byte* pBuff, uint32 dataSize)
	{
		AutoStruct* pStru = BuildStruct(code);
		if (pStru)
		{
			stru_size_t outSize = 0;
			if (pStru->read(pBuff, dataSize, outSize))
			{
				return pStru;
			}
			delete pStru;
			pStru = nullptr;
			;
		}

		return pStru;
	}
	static AutoStruct* BuildStruct(size_t code)
	{
		auto it = get_create_map().find(code);
		if (it != get_create_map().end())
		{
			return it->second();
		}
		return nullptr;
	}
protected:

	static std::set<size_t>& codes() {
		static std::set<size_t> scodes;
		return scodes;
	};
	static void addObjCode(size_t code)
	{
		codes().insert(code);
	}
	static std::map<size_t, std::function<AutoStruct* ()>>& get_create_map()
	{
		static std::map<size_t, std::function<AutoStruct* ()>> map_create;
		return map_create;
	}

	void* get_member_pointer(uint32 offset)
	{
		return (void*)((byte*)get_pointer() + offset);
	}
	bool get_member(size_t index, void* outVal, size_t typecode)
	{
		if (index >= 0 && index < get_fieldlist().size())
		{

			const field_info& info = get_fieldlist()[index];
			// void* pMember = (void*)(((byte*)this) + info._pos_offset);
			// added by steven,20211012,增加实例之间的偏移量
			void* pMember = get_data_address(info._pos_offset);
			// end of added,20211012

			return info._funcGetMember(pMember, outVal, typecode);

		}
		return false;
	}
	bool set_member(size_t index, void* newVal, size_t typecode)
	{
		if (index >= 0 && index < get_fieldlist().size())
		{

			const field_info& info = get_fieldlist()[index];
			// void* pMember = (void*)(((byte*)this) + info._pos_offset);
			// added by steven,20211012,增加实例之间的偏移量
			void* pMember = get_data_address(info._pos_offset);
			// end of added,20211012

			return info._funcSetMember(pMember, newVal, typecode);

		}
		return false;
	}
	bool get_item(size_t index, uint32 itemindex, void* outVal, size_t typecode)
	{
		if (index >= 0 && index < get_fieldlist().size())
		{
			const field_info& info = get_fieldlist()[index];
			if (info._is_array)
			{
				// void* pMember = (void*)(((byte*)this) + info._pos_offset);
				// added by steven,20211012,增加实例之间的偏移量
				void* pMember = get_data_address(info._pos_offset);
				// end of added,20211012
				return info._funcGetItem(pMember, itemindex, outVal, typecode);
			}

		}
		return false;
	}
	bool set_item(size_t index, uint32 itemindex, void* newVal, size_t typecode)
	{
		if (index >= 0 && index < get_fieldlist().size())
		{
			const field_info& info = get_fieldlist()[index];
			if (info._is_array)
			{
				// void* pMember = (void*)(((byte*)this) + info._pos_offset);
				// added by steven,20211012,增加实例之间的偏移量
				void* pMember = get_data_address(info._pos_offset);
				// end of added,20211012
				return info._funcSetItem(pMember, itemindex, newVal, typecode);
			}

		}
		return false;
	}

	// added by steven,20211012,具体实例与this偏移量
protected:
	static inline int64	_difference_to_real_instance = 0x0FFFFFFFFFFFFFFF;

protected:
	// 获取数据地址
	void* get_data_address(int64 offset_pos) {
		if (0x0FFFFFFFFFFFFFFF != _difference_to_real_instance) {
			return (void*)(((byte*)this) + offset_pos + _difference_to_real_instance);
		}
		else {
			return (void*)(((byte*)this) + offset_pos);
		}
	}

	// 获取实例
	void* get_instance() {
		return (void*)this;
	}
	// end of added,20211012		
};

class AutoRegistor
{
public:
	AutoRegistor(size_t code, std::function<AutoStruct* ()> funcCreate)
	{
		AutoStruct::addObjCode(code);
		std::map<size_t, std::function<AutoStruct* ()>>& m = AutoStruct::get_create_map();
		auto it = m.find(code);
		if (it == m.end())
		{
			m[code] = funcCreate;
			return;
		}
		//_ASSERT(false);
	}
};


template<typename tyname>
struct  type_helper;

//不受支持的类型
template<typename tyname>
struct  type_helper_nosupport
{
	/*static const stru_size_t dtsize = tyname::不支持这个类型();
	static const bool isenum = tyname::不支持这个类型();
	static const bool isarray = tyname::不支持这个类型();
	static const bool isautodata = tyname::不支持这个类型();
	static const size_t code()
	{
		static_assert (0, "不支持读取这个类型数据 ");
		return 0;
	}
	static bool getarraysize(void* pMember, uint32& outSize)
	{
		static_assert (0, "不支持读取这个类型数据 ");
		return false;
	}
	static bool setarraysize(void* pMember, uint32& newSize)
	{
		static_assert (0, "不支持读取这个类型数据 ");
		return false;
	}
	static bool read(void* pMember, byte* pBuff, const stru_size_t inBuffSize, stru_size_t& outBuffSize)
	{
		static_assert (0, "不支持读取这个类型数据 ");
		return false;
	};
	static bool write(void* pMember, byte* pBuff, const stru_size_t inBuffSize, stru_size_t& outBuffSize)
	{
		static_assert (0, "不支持写入这个类型数据 ");
		return false;
	};
	static bool datasize(void* pMember, uint32& outSize)
	{
		static_assert (0, "不支持获取这个类型的大小 ");
		return false;
	}
	static bool get_val(void* pMember, void* outVal)
	{
		static_assert (0, "不支持这个类型 ");
		return false;
	}
	static bool set_val(void* pMember, void* newVal)
	{
		static_assert (0, "不支持这个类型 ");
		return false;
	}
	static bool get_item(void* pMember, uint32 itemindex, void* outVal)
	{
		static_assert (0, "不支持这个类型 ");
		return false;
	}
	static bool set_item(void* pMember, uint32 itemindex, void* outVal)
	{
		static_assert (0, "不支持这个类型 ");
		return false;
	}*/
};

//基本类型（不可定义指针，引用的类型）模板
template<typename tyname>
struct  type_helper_base
{
	static const stru_size_t dtsize = sizeof(tyname);
	static const bool isenum = std::is_enum<tyname>::value;
	static const bool isarray = false;
	static const bool isautodata = false;
	static const size_t code() { return typeid(tyname).hash_code(); }
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
		byte* pEnd = pBuff + inBuffSize;
		if ((pBuff + dtsize) <= pEnd)
		{
			memcpy(pMember, pBuff, dtsize);
			outBuffSize = dtsize;
			return true;
		}
		return false;
	};
	static bool write(void* pMember, byte* pBuff, const uint16 inBuffSize, stru_size_t& outBuffSize)
	{
		byte* pEnd = pBuff + inBuffSize;
		if ((pBuff + dtsize) <= pEnd)
		{
			memcpy(pBuff, pMember, dtsize);
			outBuffSize = dtsize;
			return true;
		}
		return false;
	};
	static bool tostring(void* pMember, std::stringstream& ssDest, const char* format)
	{
		if (strcmp(format, "xml") == 0)
		{
			ssDest << *(tyname*)pMember;
			return true;
		}
		else if (strcmp(format, "json") == 0)
		{
		}
		return false;
	}
	static bool fromstring(void* pMember, std::string& strSrc, const char* format)
	{
		if (strcmp(format, "xml") == 0)
		{
			if (std::is_integral<tyname>::value || std::is_floating_point<tyname>::value)
			{
				std::istringstream(strSrc) >> *(tyname*)pMember;
			}


		}
		else if (strcmp(format, "json") == 0)
		{
		}
		return false;
	}
	static bool datasize(void* pMember, uint32& outSize)
	{
		outSize = dtsize;
		return true;
	}
	static bool get_val(void* pMember, void* outVal, size_t typecode)
	{
		if (typeid(tyname).hash_code() == typecode)
		{
			tyname& field = *((tyname*)pMember);
			tyname& to = *((tyname*)outVal);
			to = field;
			return true;
		}
		return false;
	}
	static bool set_val(void* pMember, void* newVal, size_t typecode)
	{
		if (typeid(tyname).hash_code() == typecode)
		{
			tyname& field = *((tyname*)pMember);
			field = *((tyname*)newVal);
			return true;
		}
		return false;

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

//枚举模板
template<typename tyname>
struct  type_helper_enum
{
	static const stru_size_t dtsize = sizeof(tyname);
	static const bool isenum = true;
	static const bool isarray = false;
	static const bool isautodata = false;
	static const size_t code() { return typeid(tyname).hash_code(); }
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
		byte* pEnd = pBuff + inBuffSize;
		if ((pBuff + dtsize) <= pEnd)
		{
			memcpy(pMember, pBuff, dtsize);
			outBuffSize = dtsize;
			return true;
		}
		return false;
	};
	static bool write(void* pMember, byte* pBuff, const uint16 inBuffSize, stru_size_t& outBuffSize)
	{
		byte* pEnd = pBuff + inBuffSize;
		if ((pBuff + dtsize) <= pEnd)
		{
			memcpy(pBuff, pMember, dtsize);
			outBuffSize = dtsize;
			return true;
		}
		return false;
	};
	static bool tostring(void* pMember, std::stringstream& ssDest, const char* format)
	{
		if (strcmp(format, "xml") == 0)
		{
			ssDest << (int64) * (tyname*)pMember;
			return true;
		}
		else if (strcmp(format, "json") == 0)
		{
		}
		return false;
	}
	static bool fromstring(void* pMember, std::string& strSrc, const char* format)
	{
		if (strcmp(format, "xml") == 0)
		{

			int64 val = 0;
			std::istringstream(strSrc) >> val;
			*(tyname*)pMember = (tyname)val;

		}
		else if (strcmp(format, "json") == 0)
		{
		}
		return false;
	}
	static bool datasize(void* pMember, uint32& outSize)
	{
		outSize = dtsize;
		return true;
	}
	static bool get_val(void* pMember, void* outVal, size_t typecode)
	{
		if (typeid(tyname).hash_code() == typecode)
		{
			tyname& field = *((tyname*)pMember);
			tyname& to = *((tyname*)outVal);
			to = field;
			return true;
		}
		return false;
	}
	static bool set_val(void* pMember, void* newVal, size_t typecode)
	{
		if (typeid(tyname).hash_code() == typecode)
		{
			tyname& field = *((tyname*)pMember);
			field = *((tyname*)newVal);
			return true;
		}
		return false;

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

//实结构类型（不可定义指针，引用的类型）模板
template<typename tyname>
struct  type_helper_real
{
	static const stru_size_t dtsize = sizeof(tyname);
	static const bool isenum = std::is_enum<tyname>::value;
	static const bool isarray = false;
	static const bool isautodata = false;
	static const size_t code() { return typeid(tyname).hash_code(); }
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
		byte* pEnd = pBuff + inBuffSize;
		if ((pBuff + dtsize) <= pEnd)
		{
			memcpy(pMember, pBuff, dtsize);
			outBuffSize = dtsize;
			return true;
		}
		return false;
	};
	static bool write(void* pMember, byte* pBuff, const uint16 inBuffSize, stru_size_t& outBuffSize)
	{
		byte* pEnd = pBuff + inBuffSize;
		if ((pBuff + dtsize) <= pEnd)
		{
			memcpy(pBuff, pMember, dtsize);
			outBuffSize = dtsize;
			return true;
		}
		return false;
	};
	static bool tostring(void* pMember, std::stringstream& ssDest, const char* format)
	{
		tyname& field = *((tyname*)pMember);
		if (strcmp(format, "xml") == 0)
		{
			//std::string str = SerializeToString(field);
			//ssDest << str;
			return true;
		}
		else if (strcmp(format, "json") == 0)
		{
		}
		return false;
	}
	static bool fromstring(void* pMember, std::string& strSrc, const char* format)
	{
		if (strcmp(format, "xml") == 0)
		{

		}
		else if (strcmp(format, "json") == 0)
		{
		}
		return false;
	}
	static bool datasize(void* pMember, uint32& outSize)
	{
		outSize = dtsize;
		return true;
	}
	static bool get_val(void* pMember, void* outVal, size_t typecode)
	{
		if (typeid(tyname).hash_code() == typecode)
		{
			tyname& field = *((tyname*)pMember);
			tyname& to = *((tyname*)outVal);
			to = field;
			return true;
		}
		return false;
	}
	static bool set_val(void* pMember, void* newVal, size_t typecode)
	{
		if (typeid(tyname).hash_code() == typecode)
		{
			tyname& field = *((tyname*)pMember);
			field = *((tyname*)newVal);
			return true;
		}
		return false;

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



//单参数容器模板
template<class _ty>
struct type_helper_single
{
	static const stru_size_t dtsize = PTR_TYPE;
	static const bool isenum = std::is_enum<_ty::value_type>::value;
	static const bool isarray = true;
	static const bool isautodata = type_helper<_ty::value_type>::isautodata;
	static const size_t code() { return typeid(_ty::value_type).hash_code(); }
	static bool getarraysize(void* pMember, uint32& outSize)
	{
		_ty& field = *((_ty*)pMember);
		outSize = (uint32)field.size();
		return true;
	}
	static bool setarraysize(void* pMember, uint32& newSize)
	{
		_ty& field = *((_ty*)pMember);
		field.resize(newSize);
		return true;
	}
	static bool read(void* pMember, byte* pBuff, const stru_size_t inBuffSize, stru_size_t& outBuffSize)
	{
		_ty& field = *((_ty*)pMember);
		outBuffSize = 0;
		byte* pEnd = pBuff + inBuffSize;
		byte* pData = pBuff;
		stru_size_t total = 0;

		if (pData + sizeof(total) <= pEnd)
		{

			memcpy(&total, pData, sizeof(total));
			pData += sizeof(total);

			if (total == 0)//如果总数为0，返回完成
			{
				outBuffSize = sizeof(total);
				return true;
			}

			field.resize(total);

			for (auto it = field.begin(); it != field.end(); it++)
			{
				stru_size_t inReadSize = (stru_size_t)(pEnd - pData);
				stru_size_t outReadSize = 0;
				if (type_helper<_ty::value_type>::read((void*)&(*it), pData, inReadSize, outReadSize))
				{
					pData += outReadSize;
				}
				else
				{
					return false;
				}

			}
			outBuffSize = (stru_size_t)(pData - pBuff);
			return true;
		}

		return false;
	};
	static bool write(void* pMember, byte* pBuff, const stru_size_t inBuffSize, stru_size_t& outBuffSize)
	{
		_ty& field = *((_ty*)pMember);
		outBuffSize = 0;
		byte* pEnd = pBuff + inBuffSize;
		byte* pData = pBuff;
		stru_size_t total = (stru_size_t)field.size();

		if (pData + sizeof(total) <= pEnd)
		{

			memcpy(pData, &total, sizeof(total));
			pData += sizeof(total);

			if (total == 0)//如果总数为0，返回完成
			{
				outBuffSize = sizeof(total);
				return true;
			}

			for (auto it = field.begin(); it != field.end(); it++)
			{
				stru_size_t inWriteSize = (stru_size_t)(pEnd - pData);
				stru_size_t outWriteSize = 0;
				if (type_helper<_ty::value_type>::write((void*)&(*it), pData, inWriteSize, outWriteSize))
				{
					pData += outWriteSize;
				}
				else
				{
					return false;
				}

			}
			outBuffSize = (stru_size_t)(pData - pBuff);
			return true;
		}

		return false;
	};
	static bool tostring(void* pMember, std::stringstream& ssDest, const char* format)
	{
		_ty& field = *((_ty*)pMember);
		if (strcmp(format, "xml") == 0)
		{
			for (auto it = field.begin(); it != field.end(); it++)
			{
				ssDest << "<item>\n";
				type_helper<_ty::value_type>::tostring((void*)&(*it), ssDest, format);
				ssDest << "</item>\n";
			}

			return true;
		}
		else if (strcmp(format, "json") == 0)
		{
		}
		return false;
	}
	static bool fromstring(void* pMember, std::string& strSrc, const char* format)
	{
		if (strcmp(format, "xml") == 0)
		{
		}
		else if (strcmp(format, "json") == 0)
		{
		}
		return false;
	}
	static bool datasize(void* pMember, uint32& outSize)
	{
		_ty& field = *((_ty*)pMember);

		for (auto it = field.begin(); it != field.end(); it++)
		{
			uint32 s = 0;
			if (type_helper<_ty::value_type>::datasize((void*)&(*it), s))
			{
				outSize += s;
			}
		}
		// 			for each (const _ty::value_type & item in field)
		// 			{
		// 				uint32 s = 0;
		// 				if (type_helper<_ty::value_type>::datasize((void*)&item,s))
		// 				{
		// 					outSize += s;
		// 				}
		// 				
		// 			}
		outSize += sizeof(stru_size_t);
		return true;
	}
	static bool get_val(void* pMember, void* outVal, size_t typecode)
	{
		return false;
	}
	static bool set_val(void* pMember, void* newVal, size_t typecode)
	{
		return false;
	}
	static bool get_item(void* pMember, uint32 itemindex, void* outVal, size_t typecode)
	{
		_ty& field = *((_ty*)pMember);
		if (itemindex >= 0 || itemindex < field.size())
		{
			int i = 0;

			for (auto it = field.begin(); it != field.end(); it++)
			{
				if (i == itemindex)
				{
					return type_helper<_ty::value_type>::get_val((void*)&(*it), outVal, typecode);
				}
				i++;
			}
			// 				for each (const _ty::value_type & item in field)
			// 				{
			// 					if (i == itemindex)
			// 					{
			// 						
			// 						return type_helper<_ty::value_type>::get_val((void*)&item,outVal,typecode);
			// 					}
			// 					i++;
			// 				}
		}

		return false;
	}
	static bool set_item(void* pMember, uint32 itemindex, void* newVal, size_t typecode)
	{
		_ty& field = *((_ty*)pMember);
		if (itemindex >= 0 || itemindex < field.size())
		{
			int i = 0;

			for (auto it = field.begin(); it != field.end(); it++)
			{
				if (i == itemindex)
				{
					return type_helper<_ty::value_type>::set_val((void*)&(*it), newVal, typecode);
				}
				i++;
			}
			// 				int i = 0;
			// 				for each (const _ty::value_type & item in field)
			// 				{
			// 					if (i == itemindex)
			// 					{
			// 						return type_helper<_ty::value_type>::set_val((void*)&item, newVal, typecode);
			// 					}
			// 				}
		}

		return false;
	}

};

//单参数容器元素为指针的模板
template<class _ty>
struct type_helper_single_ptr
{
	static const stru_size_t dtsize = PTR_TYPE;
	static const bool isenum = std::is_enum<_ty::value_type>::value;
	static const bool isarray = true;
	static const bool isautodata = type_helper<_ty::value_type>::isautodata;
	static const size_t code() { return typeid(_ty::value_type).hash_code(); }
	static bool getarraysize(void* pMember, uint32& outSize)
	{
		_ty& field = *((_ty*)pMember);
		outSize = (uint32)field.size();
		return true;
	}
	static bool setarraysize(void* pMember, uint32& newSize)
	{
		_ty& field = *((_ty*)pMember);
		field.resize(newSize);
		return true;
	}
	static bool read(void* pMember, byte* pBuff, const stru_size_t inBuffSize, stru_size_t& outBuffSize)
	{
		// 			tyname& field = *((tyname*)pMember);
		// 			outBuffSize = 0;
		// 			byte* pEnd = pBuff + inBuffSize;
		// 			byte* pData = pBuff;
		// 			stru_size_t total = 0;
		// 
		// 			if (pData + sizeof(total) <= pEnd)
		// 			{
		// 
		// 				memcpy(&total, pData, sizeof(total));
		// 				pData += sizeof(total);
		// 
		// 				if (total == 0)//如果总数为0，返回完成
		// 				{
		// 					outBuffSize = sizeof(total);
		// 					return true;
		// 				}
		// 
		// 				field.resize(total);
		// 
		// 				for each (const tyname::value_type & item in field)
		// 				{
		// 					stru_size_t inReadSize = (stru_size_t)(pEnd - pData);
		// 					stru_size_t outReadSize = 0;
		// 					if (type_helper<tyname::value_type>::read((void*)&item, pData, inReadSize, outReadSize))
		// 					{
		// 						pData += outReadSize;
		// 					}
		// 					else
		// 					{
		// 						return false;
		// 					}
		// 
		// 				}
		// 				outBuffSize = (stru_size_t)(pData - pBuff);
		// 				return true;
		// 			}

		return false;
	};
	static bool write(void* pMember, byte* pBuff, const stru_size_t inBuffSize, stru_size_t& outBuffSize)
	{
		// 			tyname& field = *((tyname*)pMember);
		// 			outBuffSize = 0;
		// 			byte* pEnd = pBuff + inBuffSize;
		// 			byte* pData = pBuff;
		// 			stru_size_t total = (stru_size_t)field.size();
		// 
		// 			if (pData + sizeof(total) <= pEnd)
		// 			{
		// 
		// 				memcpy(pData, &total, sizeof(total));
		// 				pData += sizeof(total);
		// 
		// 				if (total == 0)//如果总数为0，返回完成
		// 				{
		// 					outBuffSize = sizeof(total);
		// 					return true;
		// 				}
		// 
		// 				for each (const tyname::value_type & item in field)
		// 				{
		// 					stru_size_t inWriteSize = (stru_size_t)(pEnd - pData);
		// 					stru_size_t outWriteSize = 0;
		// 					if (type_helper<tyname::value_type>::write((void*)&item, pData, inWriteSize, outWriteSize))
		// 					{
		// 						pData += outWriteSize;
		// 					}
		// 					else
		// 					{
		// 						return false;
		// 					}
		// 
		// 				}
		// 				outBuffSize = (stru_size_t)(pData - pBuff);
		// 				return true;
		// 			}

		return false;
	};
	static bool tostring(void* pMember, std::stringstream& ssDest, const char* format)
	{
		_ty& field = *((_ty*)pMember);
		if (strcmp(format, "xml") == 0)
		{
			for (auto it = field.begin(); it != field.end(); it++)
			{
				ssDest << "<item>\n";
				type_helper<_ty::value_type>::tostring((void*)(*it), ssDest, format);
				ssDest << "</item>\n";
			}

			return true;
		}
		else if (strcmp(format, "json") == 0)
		{
		}
		return false;
	}
	static bool fromstring(void* pMember, std::string& strSrc, const char* format)
	{
		if (strcmp(format, "xml") == 0)
		{
		}
		else if (strcmp(format, "json") == 0)
		{
		}
		return false;
	}
	static bool datasize(void* pMember, uint32& outSize)
	{
		_ty& field = *((_ty*)pMember);
		return type_helper_single<_ty>::datasize(&field, outSize);
		// 			_ty& field = *((_ty*)pMember);
		// 
		// 			for each (const _ty::value_type & item in field)
		// 			{
		// 				uint32 s = 0;
		// 				if (type_helper<_ty::value_type>::datasize((void*)&item, s))
		// 				{
		// 					outSize += s;
		// 				}
		// 
		// 			}
		// 			outSize += sizeof(stru_size_t);
		// 			return true;
	}
	static bool get_val(void* pMember, void* outVal, size_t typecode)
	{
		return false;
	}
	static bool set_val(void* pMember, void* newVal, size_t typecode)
	{
		return false;
	}
	static bool get_item(void* pMember, uint32 itemindex, void* outVal, size_t typecode)
	{
		_ty& field = *((_ty*)pMember);

		return type_helper_single<_ty>::get_item(&field, itemindex, outVal, typecode);
		// 			if (itemindex >= 0 || itemindex < field.size())
		// 			{
		// 				int i = 0;
		// 				for each (const _ty::value_type & item in field)
		// 				{
		// 					if (i == itemindex)
		// 					{
		// 
		// 						return type_helper<_ty::value_type>::get_val((void*)&item, outVal, typecode);
		// 					}
		// 				}
		// 			}
		// 
		// 			return false;
	}
	static bool set_item(void* pMember, uint32 itemindex, void* newVal, size_t typecode)
	{
		_ty& field = *((_ty*)pMember);

		return type_helper_single<_ty>::set_item(&field, itemindex, newVal, typecode);
		// 			if (itemindex >= 0 || itemindex < field.size())
		// 			{
		// 				int i = 0;
		// 				for each (const _ty::value_type & item in field)
		// 				{
		// 					if (i == itemindex)
		// 					{
		// 						return type_helper<_ty::value_type>::set_val((void*)&item, newVal, typecode);
		// 					}
		// 				}
		// 			}
		// 
		// 			return false;
	}

};


//AutoStruct类型的模板
template<class _ty>
struct type_helper_autodata
{
	static const stru_size_t dtsize = PTR_TYPE;
	static const bool isenum = false;
	static const bool isarray = false;
	static const bool isautodata = true;
	static const size_t code() { return typeid(_ty).hash_code(); }
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
		_ty* ptr = (_ty*)pMember;
		return ptr->read(pBuff, inBuffSize, outBuffSize);

	};
	static bool write(void* pMember, byte* pBuff, const stru_size_t inBuffSize, stru_size_t& outBuffSize)
	{
		_ty* ptr = (_ty*)pMember;
		return ptr->write(pBuff, inBuffSize, outBuffSize);
	};
	static bool tostring(void* pMember, std::stringstream& ssDest, const char* format)
	{
		if (strcmp(format, "xml") == 0)
		{
			_ty* ptr = (_ty*)pMember;
			std::string str;
			if (ptr->tostring(str, format))
			{
				ssDest << str;
				return true;
			}
			return false;
		}
		else if (strcmp(format, "json") == 0)
		{
		}
		return false;
	}
	static bool fromstring(void* pMember, std::string& strSrc, const char* format)
	{
		if (strcmp(format, "xml") == 0)
		{
		}
		else if (strcmp(format, "json") == 0)
		{
		}
		return false;
	}
	static bool datasize(void* pMember, uint32& outSize)
	{
		_ty* ptr = (_ty*)pMember;
		outSize = ptr->get_size();
		return true;
	}
	static bool get_val(void* pMember, void* outVal, size_t typecode)
	{
		if (typeid(_ty*).hash_code() == typecode || typeid(AutoStruct*).hash_code() == typecode || typeid(yd::IAutoData*).hash_code() == typecode/*added by steven,20211112*/)
		{
			AutoStruct** p = (AutoStruct**)(outVal);
			*p = (AutoStruct*)pMember;
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

//AutoStruct类型的指针模板
template<class _ty>
struct type_helper_autodata_ptr
{
	static const stru_size_t dtsize = PTR_TYPE;
	static const bool isenum = false;
	static const bool isarray = false;
	static const bool isautodata = true;
	static const size_t code() { return typeid(_ty).hash_code(); }
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
		_ty* ptr = *((_ty**)pMember);
		return ptr->read(pBuff, inBuffSize, outBuffSize);

	};
	static bool write(void* pMember, byte* pBuff, const stru_size_t inBuffSize, stru_size_t& outBuffSize)
	{
		_ty* ptr = *((_ty**)pMember);
		return ptr->write(pBuff, inBuffSize, outBuffSize);
	};
	static bool tostring(void* pMember, std::stringstream& ssDest, const char* format)
	{
		_ty* ptr = *((_ty**)pMember);
		return type_helper_autodata<_ty>::tostring(ptr, ssDest, format);

	}
	static bool fromstring(void* pMember, std::string& strSrc, const char* format)
	{
		_ty* ptr = *((_ty**)pMember);
		return type_helper_autodata<_ty>::fromstring(ptr, strSrc, format);

	}
	static bool datasize(void* pMember, uint32& outSize)
	{
		_ty* ptr = *((_ty**)pMember);
		outSize = ptr->get_size();
		return true;
	}
	static bool get_val(void* pMember, void* outVal, size_t typecode)
	{
		if (typeid(_ty*).hash_code() == typecode || typeid(AutoStruct*).hash_code() == typecode || typeid(yd::IAutoData*).hash_code() == typecode/*added by steven,20211112*/)
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

//分离出非容器中的enum类型
//传递容器类型和AutoStruct类型，其它已被剥离	
template<typename tyname>
struct  type_helper
{
	static const stru_size_t dtsize = std::conditional <
		std::is_enum<tyname>::value,		//是否为enum类型
		type_helper_enum<tyname>,			//分离出enum类型,使用实类型模板
		type_helper_nosupport<tyname> //不支持类型
	>::type::dtsize;
	static const bool isenum = std::is_enum<tyname>::value;
	static const bool isarray = false;
	static const bool isautodata = false;
	static const size_t code()
	{
		return std::conditional <
			std::is_enum<tyname>::value,		//是否为enum类型
			type_helper_enum<tyname>,			//分离出enum类型,使用实类型模板
			type_helper_nosupport<tyname>		//不支持类型
		>::type::code();
	}
	static bool getarraysize(void* pMember, uint32& outSize)
	{
		return std::conditional <
			std::is_enum<tyname>::value,		//是否为enum类型
			type_helper_enum<tyname>,			//分离出enum类型,使用实类型模板
			type_helper_nosupport<tyname>		//不支持类型
		>::type::getarraysize(pMember, outSize);
	}
	static bool setarraysize(void* pMember, uint32& newSize)
	{
		return std::conditional <
			std::is_enum<tyname>::value,		//是否为enum类型
			type_helper_enum<tyname>,			//分离出enum类型,使用实类型模板
			type_helper_nosupport<tyname>		//不支持类型
		>::type::setarraysize(pMember, newSize);
	}
	static bool read(void* pMember, byte* pBuff, const stru_size_t inBuffSize, stru_size_t& outBuffSize)
	{
		return std::conditional <
			std::is_enum<tyname>::value,		//是否为enum类型
			type_helper_enum<tyname>,			//分离出enum类型,使用实类型模板
			type_helper_nosupport<tyname>		//传递容器类型和AutoStruct子类型;
		>::type::read(pMember, pBuff, inBuffSize, outBuffSize);
	};
	static bool write(void* pMember, byte* pBuff, const stru_size_t inBuffSize, stru_size_t& outBuffSize)
	{
		return std::conditional <
			std::is_enum<tyname>::value,		//是否为enum类型
			type_helper_enum<tyname>,			//分离出enum类型,使用实类型模板
			type_helper_nosupport<tyname>		//传递容器类型和AutoStruct子类型;
		>::type::write(pMember, pBuff, inBuffSize, outBuffSize);
	};
	static bool tostring(void* pMember, std::stringstream& ssDest, const char* format)
	{
		return std::conditional <
			std::is_enum<tyname>::value,		//是否为enum类型
			type_helper_enum<tyname>,			//分离出enum类型,使用实类型模板
			type_helper_nosupport<tyname>		//传递容器类型和AutoStruct子类型;
		>::type::tostring(pMember, ssDest, format);
	}
	static bool fromstring(void* pMember, std::string& strSrc, const char* format)
	{
		return std::conditional <
			std::is_enum<tyname>::value,		//是否为enum类型
			type_helper_enum<tyname>,			//分离出enum类型,使用实类型模板
			type_helper_nosupport<tyname>		//传递容器类型和AutoStruct子类型;
		>::type::fromstring(pMember, strSrc, format);
	}
	static bool datasize(void* pMember, uint32& outSize)
	{
		return std::conditional <
			std::is_enum<tyname>::value,		//是否为enum类型
			type_helper_enum<tyname>,			//分离出enum类型,使用实类型模板
			type_helper_nosupport<tyname>		//传递容器类型和AutoStruct子类型;
		>::type::datasize(pMember, outSize);
	}
	static bool get_val(void* pMember, void* outVal, size_t typecode)
	{
		return std::conditional <
			std::is_enum<tyname>::value,		//是否为enum类型
			type_helper_enum<tyname>,			//分离出enum类型,使用实类型模板
			type_helper_nosupport<tyname>		//传递容器类型和AutoStruct子类型;
		>::type::get_val(pMember, outVal, typecode);
	}
	static bool set_val(void* pMember, void* newVal, size_t typecode)
	{
		return std::conditional <
			std::is_enum<tyname>::value,		//是否为enum类型
			type_helper_enum<tyname>,			//分离出enum类型,使用实类型模板
			type_helper_nosupport<tyname>		//传递容器类型和AutoStruct子类型;
		>::type::set_val(pMember, newVal, typecode);
	}
	static bool get_item(void* pMember, uint32 itemindex, void* outVal, size_t typecode)
	{
		return std::conditional <
			std::is_enum<tyname>::value,		//是否为enum类型
			type_helper_enum<tyname>,			//分离出enum类型,使用实类型模板
			type_helper_nosupport<tyname>		//传递容器类型和AutoStruct子类型;
		>::type::get_item(pMember, itemindex, outVal, typecode);
	}
	static bool set_item(void* pMember, uint32 itemindex, void* newVal, size_t typecode)
	{
		return std::conditional <
			std::is_enum<tyname>::value,		//是否为enum类型
			type_helper_enum<tyname>,			//分离出enum类型,使用实类型模板
			type_helper_nosupport<tyname>		//传递容器类型和AutoStruct子类型;
		>::type::set_item(pMember, itemindex, newVal, typecode);
	}

};




//#define AUTO_LIST
#ifdef AUTO_LIST
	//特化单参数容器类型存取（不包含指针类型,引用的类型）
#define LIST_REG(__Type) template<>  struct  type_helper<std::list<__Type>>:public type_helper_single<std::list<__Type>>{}
#else
#define LIST_REG(__Type) 
#endif

//#define AUTO_VECTOR
#ifdef AUTO_VECTOR
	//特化单参数容器类型存取（不包含指针类型,引用的类型）
#define VECTOR_REG(__Type) template<>  struct  type_helper<std::vector<__Type>>:public type_helper_single<std::vector<__Type>>{}
#else
#define VECTOR_REG(__Type) 
#endif

//特化枚举类型存取（不包含指针类型,引用的类型）
#define ENUM_TYPE_REG(__Type) template<>  struct  type_helper<__Type>:public type_helper_enum<__Type>{};  \
	LIST_REG(__Type);  \
	VECTOR_REG(__Type);

	//特化实类型存取（不包含指针类型,引用的类型）
#define REAL_TYPE_REG(__Type) template<>  struct  type_helper<__Type>:public type_helper_real<__Type>{};  \
	LIST_REG(__Type);  \
	VECTOR_REG(__Type);

	//特化实类型存取（不包含指针类型,引用的类型）
#define BASE_TYPE_REG(__Type) template<>  struct  type_helper<__Type>:public type_helper_base<__Type>{};  \
	LIST_REG(__Type);  \
	VECTOR_REG(__Type);

	//实类型（完全不包含指针的类型）的特化
BASE_TYPE_REG(bool);
BASE_TYPE_REG(int8);
BASE_TYPE_REG(uint8);
BASE_TYPE_REG(int16);
BASE_TYPE_REG(uint16);
BASE_TYPE_REG(int32);
BASE_TYPE_REG(uint32);
BASE_TYPE_REG(int64);
BASE_TYPE_REG(uint64);
BASE_TYPE_REG(float);
BASE_TYPE_REG(double);

//特化STL的字符串类型
template<>
struct type_helper<std::string>
{
	static const stru_size_t dtsize = PTR_TYPE;
	static const bool isenum = false;
	static const bool isarray = false;
	static const bool isautodata = false;
	static const size_t code() { return typeid(std::string).hash_code(); }
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
		outBuffSize = 0;
		std::string* ptr = (std::string*)pMember;
		byte* pEnd = pBuff + inBuffSize;
		byte* pData = pBuff;
		stru_size_t total = 0;

		if (pBuff + sizeof(total) <= pEnd)
		{
			memcpy(&total, pData, sizeof(total));
			pData += sizeof(total);

			if (total == 0)//如果总数为0，返回完成
			{
				outBuffSize = sizeof(total);
				return true;
			}

			ptr->reserve((size_t)total);
			ptr->resize(total);

			//最多可读取数量 
			stru_size_t canreadsize = inBuffSize - sizeof(total);

			//当前可读取数量
			stru_size_t copysize = std::min<stru_size_t>(canreadsize, total);

			//获取待读取的数据的指针
			byte* p = ((byte*)ptr->data());

			if (copysize)
			{
				//读取数据
				memcpy(p, pData, copysize);
				pData += copysize;
			}

			outBuffSize = (stru_size_t)(pData - pBuff);

			return true;
		}

		return false;
	};
	static bool write(void* pMember, byte* pBuff, const stru_size_t inBuffSize, stru_size_t& outBuffSize)
	{
		outBuffSize = 0;
		std::string* ptr = (std::string*)pMember;
		byte* pEnd = pBuff + inBuffSize;
		byte* pData = pBuff;
		stru_size_t total = (stru_size_t)ptr->size();

		if (pBuff + sizeof(total) <= pEnd)
		{
			memcpy(pData, &total, sizeof(total));
			pData += sizeof(total);

			if (total == 0)//如果总数为0，返回完成
			{
				outBuffSize = sizeof(total);
				return true;
			}

			//最多可写入数量 
			stru_size_t canwritesize = inBuffSize - sizeof(total);

			//当前可写入数量
			stru_size_t copysize = std::min<stru_size_t>(canwritesize, total);

			//获取待读取的数据的指针
			byte* p = ((byte*)ptr->data());

			if (copysize)
			{
				//读取数据
				memcpy(pData, p, copysize);
				pData += copysize;
			}

			outBuffSize = (stru_size_t)(pData - pBuff);
			return true;

		}
		return false;
	};
	static bool tostring(void* pMember, std::stringstream& ssDest, const char* format)
	{
		if (strcmp(format, "xml") == 0)
		{
			// ssDest << "<![CDATA["<<*(std::string*)pMember<<"]]>" ;
			ssDest << *(std::string*)pMember;
			return true;
		}
		else if (strcmp(format, "json") == 0)
		{
		}
		return false;
	}
	static bool fromstring(void* pMember, std::string& strSrc, const char* format)
	{
		if (strcmp(format, "xml") == 0)
		{

			*(std::string*)pMember = strSrc;

		}
		else if (strcmp(format, "json") == 0)
		{
		}
		return false;
	}
	static bool datasize(void* pMember, uint32& outSize)
	{
		std::string* ptr = (std::string*)pMember;
		outSize = (stru_size_t)(ptr->size() + sizeof(stru_size_t));
		return true;
	}
	static bool get_val(void* pMember, void* outVal, size_t typecode)
	{
		if (typeid(std::string).hash_code() == typecode)
		{
			std::string& field = *((std::string*)pMember);
			*((std::string*)outVal) = field;
			return true;
		}
		return false;

	}
	static bool set_val(void* pMember, void* newVal, size_t typecode)
	{
		if (typeid(std::string).hash_code() == typecode)
		{
			std::string& field = *((std::string*)pMember);
			field = *((std::string*)newVal);
			return true;
		}
		return false;
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
VECTOR_REG(std::string);
LIST_REG(std::string);

//


//}
#define AUTO_STRU_END(__CLASSNAME)  };REG_STRU(__CLASSNAME)  \
template<> struct type_helper<__CLASSNAME>: public type_helper_autodata<__CLASSNAME>{};  \
template<> struct type_helper<__CLASSNAME*>: public type_helper_autodata_ptr<__CLASSNAME*>{};  \
VECTOR_REG(__CLASSNAME);  \
LIST_REG(__CLASSNAME);			\
VECTOR_REG(__CLASSNAME*);  \
LIST_REG(__CLASSNAME*);

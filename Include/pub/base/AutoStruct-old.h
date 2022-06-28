#pragma once

#include <platform.h>
#include <functional>
#include <string>
#include <vector>
#include <set>
#include <list>
#include <queue>
#include <deque>
#include <stack>
#include <unordered_set>
#include <map>


#pragma warning(disable:4100)


//获取成员变量的偏移量
#define __OFFSET__(__THECLASS,__MEMBER_NAME) ((uint32)((size_t)&((__THECLASS *)0)->__MEMBER_NAME))

//用于可变参数宏的定义
#define PRIVATE_ARGS_GLUE(x, y) x y
#define PRIVATE_MACRO_VAR_ARGS_IMPL_COUNT(_1,_2,_3,_4,_5,_6,_7,_8,_9, _10, N, ...) N
#define PRIVATE_MACRO_VAR_ARGS_IMPL(args) PRIVATE_MACRO_VAR_ARGS_IMPL_COUNT args
#define COUNT_MACRO_VAR_ARGS(...) PRIVATE_MACRO_VAR_ARGS_IMPL((__VA_ARGS__,10, 9,8,7,6,5,4,3,2,1,0))
#define PRIVATE_MACRO_CHOOSE_HELPER2(M,count)  M##count
#define PRIVATE_MACRO_CHOOSE_HELPER1(M,count) PRIVATE_MACRO_CHOOSE_HELPER2(M,count)
#define PRIVATE_MACRO_CHOOSE_HELPER(M,count)   PRIVATE_MACRO_CHOOSE_HELPER1(M,count)
#define INVOKE_VAR_MACRO(M,...) PRIVATE_ARGS_GLUE(PRIVATE_MACRO_CHOOSE_HELPER(M,COUNT_MACRO_VAR_ARGS(__VA_ARGS__)), (__VA_ARGS__))

//自动结构的宏定义
#define AUTO_STRU_BEGIN(__CLASSNAME) struct __CLASSNAME :public AUTO::AutoStruct{ STRU_DEF(__CLASSNAME,false);

//注册自动结构，用于自动结构的动态创建
#define REG_STRU(__THISCLASS) const AUTO::CStruRegistor __THISCLASS##_regist(__THISCLASS::code(), []() {return new __THISCLASS(); });



//注册类的序列化支持宏
#pragma region STRU_DEF
#define STRU_DEF(__THISCLASS,__ISDBO)										\
using  thisClass=__THISCLASS;                                                 \
private:                                                                       \
	static const bool IsDBOType = __ISDBO;                                     \
	static AUTO::fieldlist& s_fieldlist()										\
	{																		   \
		static AUTO::fieldlist __class_##memlist##__;							\
        return __class_##memlist##__;                                          \
    }														                   \
	static AUTO::stru_size_t s_static_size()											\
		{																		\
		AUTO::stru_size_t static_size = 0;											\
		const AUTO::fieldlist& members = s_fieldlist();								\
		for (size_t i = 0; i < members.size(); i++)								\
		{																		\
			if (members[i]._store_size == AUTO::PTR_TYPE) return AUTO::PTR_TYPE;			\
			static_size += members[i]._store_size;								\
		}																		\
		return static_size;														\
		}																		\
public:																			\
	static size_t code()														\
	{																		   \
		static size_t code = typeid(__THISCLASS).hash_code();					\
		return code;															\
    }														                   \
    virtual AUTO::fieldlist& get_fieldlist()									\
    {                                                                          \
        return s_fieldlist();													\
    }																		   \
	virtual size_t get_code(){return code();};								\
	virtual AUTO::stru_size_t get_static_size()										\
	{																			\
		static AUTO::stru_size_t static_size = s_static_size();						\
		return static_size;														\
	}																			\
	virtual bool get_isDBO(){return __ISDBO;}

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

#define FIELD_REG(__FIELD_NAME,__FIELD_DESC)  \
private:                                                                       \
	static const bool _type_##__FIELD_NAME = std::conditional<IsDBOType,IsDBField<decltype(__FIELD_NAME)>,std::is_same<bool,decltype(IsDBOType)>>::type::value ;  \
	class _field_register_##__FIELD_NAME##_                                   \
    {                                                                          \
    public:                                                                    \
        _field_register_##__FIELD_NAME##_()                                   \
        {                                                                      \
            static AUTO::field_register reg_##__FIELD_NAME(  \
                thisClass::s_fieldlist(),  \
				typeid(__FIELD_NAME).name(),  \
				#__FIELD_NAME,  \
				__FIELD_DESC,  \
				typeid(__FIELD_NAME).hash_code(),   \
				AUTO::type_helper<decltype(__FIELD_NAME)>::isarray,    \
				std::is_enum<decltype(__FIELD_NAME)>::value,    \
				__OFFSET__(thisClass,__FIELD_NAME),                             \
				AUTO::type_helper<decltype(__FIELD_NAME)>::dtsize,               \
				AUTO::type_helper<decltype(__FIELD_NAME)>::read,  \
				AUTO::type_helper<decltype(__FIELD_NAME)>::write,			\
				AUTO::type_helper<decltype(__FIELD_NAME)>::size);  \
        }                                                                      \
    }__FIELD_NAME##_register;

#define FIELD_3(__FIELD_TYPE,__FIELD_NAME,__FIELD_DESC)                          \
public:                                                                        \
      __FIELD_TYPE __FIELD_NAME;											\
FIELD_REG(__FIELD_NAME,__FIELD_DESC)

#define FIELD_4(__FIELD_TYPE1,__FIELD_TYPE2,__FIELD_NAME,__FIELD_DESC)                          \
public:                                                                        \
      __FIELD_TYPE1##,##__FIELD_TYPE2 __FIELD_NAME;											\
FIELD_REG(__FIELD_NAME,__FIELD_DESC)

#define FIELD_5(__FIELD_TYPE1,__FIELD_TYPE2,__FIELD_TYPE3,__FIELD_NAME,__FIELD_DESC)                          \
public:                                                                        \
      __FIELD_TYPE1##,##__FIELD_TYPE2##,##__FIELD_TYPE3 __FIELD_NAME;											\
FIELD_REG(__FIELD_NAME,__FIELD_DESC)

#define FIELD_6(__FIELD_TYPE1,__FIELD_TYPE2,__FIELD_TYPE3,__FIELD_TYPE4,__FIELD_NAME,__FIELD_DESC)                          \
public:                                                                        \
      __FIELD_TYPE1##,##__FIELD_TYPE2##,##__FIELD_TYPE3##,##__FIELD_TYPE4 __FIELD_NAME;											\
FIELD_REG(__FIELD_NAME,__FIELD_DESC)

#define FIELD_7(__FIELD_TYPE1,__FIELD_TYPE2,__FIELD_TYPE3,__FIELD_TYPE4,__FIELD_TYPE5,__FIELD_NAME,__FIELD_DESC)                          \
public:                                                                        \
      __FIELD_TYPE1##,##__FIELD_TYPE2##,##__FIELD_TYPE3##,##__FIELD_TYPE4##,##__FIELD_TYPE5 __FIELD_NAME;											\
FIELD_REG(__FIELD_NAME,__FIELD_DESC)

#define FIELD_8(__FIELD_TYPE1,__FIELD_TYPE2,__FIELD_TYPE3,__FIELD_TYPE4,__FIELD_TYPE5,__FIELD_TYPE6,__FIELD_NAME,__FIELD_DESC)                          \
public:                                                                        \
      __FIELD_TYPE1##,##__FIELD_TYPE2##,##__FIELD_TYPE3##,##__FIELD_TYPE4##,##__FIELD_TYPE5##,##__FIELD_TYPE6 __FIELD_NAME;											\
FIELD_REG(__FIELD_NAME,__FIELD_DESC)

#define FIELD_9(__FIELD_TYPE1,__FIELD_TYPE2,__FIELD_TYPE3,__FIELD_TYPE4,__FIELD_TYPE5,__FIELD_TYPE6,__FIELD_TYPE7,__FIELD_NAME,__FIELD_DESC)                          \
public:                                                                        \
      __FIELD_TYPE1##,##__FIELD_TYPE2##,##__FIELD_TYPE3##,##__FIELD_TYPE4##,##__FIELD_TYPE5##,##__FIELD_TYPE6##,##__FIELD_TYPE7 __FIELD_NAME;											\
FIELD_REG(__FIELD_NAME,__FIELD_DESC)

#define FIELD_10(__FIELD_TYPE1,__FIELD_TYPE2,__FIELD_TYPE3,__FIELD_TYPE4,__FIELD_TYPE5,__FIELD_TYPE6,__FIELD_TYPE7,__FIELD_TYPE8,__FIELD_NAME,__FIELD_DESC)                          \
public:                                                                        \
      __FIELD_TYPE1##,##__FIELD_TYPE2##,##__FIELD_TYPE3##,##__FIELD_TYPE4##,##__FIELD_TYPE5##,##__FIELD_TYPE6##,##__FIELD_TYPE7##,##__FIELD_TYPE8 __FIELD_NAME;											\
FIELD_REG(__FIELD_NAME,__FIELD_DESC)


#define FIELD(...) INVOKE_VAR_MACRO(FIELD_,__VA_ARGS__);
#pragma endregion

namespace AUTO
{
	//基本数据类型
	enum enumDBOType :uint8
	{
		emDT_NULL,
		emDT_ENUM,
		emDT_CHAR,
		emDT_UCHAR,
		emDT_SHORT,
		emDT_USHORT,
		emDT_INT32,
		emDT_UINT32,
		emDT_INT64,
		emDT_UINT64,
		emDT_FLOAT,
		emDT_DOUBLE,
		emDT_STRING,
		emDT_DATA,
	};

	class AutoStruct;
	struct dataval
	{
		dataval()
		{
			memset(this, 0, sizeof(dataval));
		}
		~dataval()
		{
			if (dt == emDT_STRING && valString.len && valString.pData)
			{
				LPSTR p = valString.pData;
				valString.len = 0;
				valString.pData = 0;
				delete[] p;
			}
		}
		void setstring(LPCSTR str)
		{
			if (dt == emDT_STRING && valString.len && valString.pData)
			{
				LPSTR p = valString.pData;
				valString.len = 0;
				valString.pData = 0;
				delete[] p;
			}

			if (str)
			{
				dt = emDT_STRING;
				valString.len = (uint32)strlen(str) + 1;
				valString.pData = new char[valString.len];
				memset(valString.pData, 0, valString.len);
				if (valString.len)
				{
					strcpy_s(valString.pData, valString.len, str);
				}
			}

		}
		struct strval
		{
			uint32 len;
			char* pData;
		};
		enumDBOType dt;
		union
		{
			int8 valInt8;
			uint8 valUint8;
			int16 valInt16;
			uint16 valUint16;
			int32 valInt32;
			uint32 valUint32;
			int64 valInt64;
			uint64 valUint64;
			float valFloat;
			double valDouble;
			AutoStruct* valAutoData;
			strval valString;
		};
	};




	//结构的大小定义
	typedef uint32 stru_size_t;
	static const stru_size_t PTR_TYPE = sizeof(stru_size_t) == 2 ? 0xFFFF : sizeof(stru_size_t) == 4 ? 0xFFFFFFFF : 0;
	typedef std::function<bool(void* pMember, byte* pBuff, const stru_size_t inBuffSize, stru_size_t& outBuffSize)> funcReadWrite;
	typedef std::function<stru_size_t(void* pMember)> funcSize;

	//结构字段信息
	struct field_info
	{
		field_info(LPCSTR type_name, LPCSTR field_name, LPCSTR field_desc, size_t hash_code, bool isarray, bool isenum, stru_size_t store_size, stru_size_t pos_offset,
			funcReadWrite funcRead, funcReadWrite funcWrite, funcSize size)
		{
			_hash_code = hash_code;//字段类型的Hashcode
			_type_name = type_name;//字段类型名
			_field_name = field_name;//字段名称
			_field_desc = field_desc;//字段描述
			_store_size = store_size;//字段存取方式与大小 0xFFFF/0xFFFFFFFF表示动态指针，存数据在动态数据区，0表示是空数据，其它表示存在静态数据区大小
			_pos_offset = pos_offset;//字段在结构中的偏移位置
			_funcRead = funcRead;//字段读方法
			_funcWrite = funcWrite;//字段写方法	
			_funcSize = size;
			_is_array = isarray;
			if (!isenum)
			{
				if (_hash_code == typeid(int8).hash_code())
				{
					_dbo_type = emDT_CHAR;
				}
				else if (_hash_code == typeid(uint8).hash_code())
				{
					_dbo_type = emDT_UCHAR;
				}
				else if (_hash_code == typeid(int16).hash_code())
				{
					_dbo_type = emDT_SHORT;
				}
				else if (_hash_code == typeid(uint16).hash_code())
				{
					_dbo_type = emDT_USHORT;
				}
				else if (_hash_code == typeid(int32).hash_code())
				{
					_dbo_type = emDT_INT32;
				}
				else if (_hash_code == typeid(uint32).hash_code())
				{
					_dbo_type = emDT_UINT32;
				}
				else if (_hash_code == typeid(int64).hash_code())
				{
					_dbo_type = emDT_INT64;
				}
				else if (_hash_code == typeid(uint64).hash_code())
				{
					_dbo_type = emDT_UINT64;
				}
				else if (_hash_code == typeid(float).hash_code())
				{
					_dbo_type = emDT_FLOAT;
				}
				else if (_hash_code == typeid(double).hash_code())
				{
					_dbo_type = emDT_DOUBLE;
				}
				else if (_hash_code == typeid(std::string).hash_code())
				{
					_dbo_type = emDT_STRING;
				}
				else
				{
					_dbo_type = emDT_DATA;
				}
			}
			else
			{
				_dbo_type = emDT_ENUM;
			}
		}



		enumDBOType _dbo_type = emDT_NULL;//字段值类型
		bool        _is_array = false;//是否数组，如果是数组，则为vector容器
		size_t _hash_code = 0;//字段类型的Hashcode
		std::string _type_name;//字段类型名
		std::string _field_name;//字段名称
		std::string _field_desc;//字段描述
		stru_size_t	_store_size = 0;//字段存取方式与大小 0xFFFF/0xFFFFFFFF表示动态指针，存数据在动态数据区，0表示是空数据，其它表示存在静态数据区大小
		stru_size_t	_pos_offset = 0;//字段在结构中的偏移位置
		funcReadWrite _funcRead;//字段读方法
		funcReadWrite _funcWrite;//字段写方法		
		funcSize    _funcSize;
	};

	typedef std::vector<field_info> fieldlist;

	class field_register
	{
	public:
		field_register(fieldlist& memlist, LPCSTR type_name, LPCSTR field_name, LPCSTR field_desc, size_t hash_code, bool isarray, bool isenum,
			stru_size_t pos_offset, stru_size_t store_size,
			funcReadWrite funcRead, funcReadWrite funcWrite, funcSize size)
		{//初始化成员定义
			field_info field(type_name, field_name, field_desc, hash_code, isarray, isenum, store_size, pos_offset, funcRead, funcWrite, size);
			memlist.push_back(field);
		}
	};


	class AutoStruct
	{
		friend class CStruRegistor;
		stru_size_t _size = 0;
	public:
		AutoStruct() = default;
		~AutoStruct() = default;

		virtual fieldlist& get_fieldlist() = 0;
		virtual size_t get_code() = 0;
		virtual bool get_isDBO() = 0;

		//************************************
		// description: 获取静态数据的大小
		// Method:     get_static_size
		// Access:     public 
		// Returns:    uint32 返回静态数据大小,如果非静态数据，返回0
		//************************************
		virtual stru_size_t get_static_size() = 0;

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

			//如果不更新当前大小，直接返回上次计算结果
			if (isUpdate == false) return _size;


			stru_size_t ssize = 0;
			fieldlist& fields = get_fieldlist();
			for (size_t i = 0; i < fields.size(); i++)
			{
				ssize += fields[i]._funcSize((void*)(((byte*)this) + fields[i]._pos_offset));
			}
			_size = ssize;
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
		bool ReadFrom(byte* pBuff, const stru_size_t inBuffSize, stru_size_t& outBuffSize)
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
			stru_size_t static_data_size = get_static_size();

			//如果结构是静态类型,直接复制内存,返回成功
			if (static_data_size != PTR_TYPE)
			{
				void* p = (void*)(((byte*)this) + members[0]._pos_offset);
				memcpy(p, pBuff, static_data_size);
				outBuffSize = static_data_size;
				return true;
			}

			//数据尾指针
			const byte* const pDataEnd = pBuff + inBuffSize;
			//数据指针
			byte* pData = pBuff;

			//读取结构字段成员列表
			for (size_t i = 0; i < members.size(); i++)
			{
				//成员指针
				void* pMember = (void*)(((byte*)this) + members[i]._pos_offset);

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
		bool WriteTo(byte* pBuff, const stru_size_t inBuffSize, stru_size_t& outBuffSize)
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
			stru_size_t static_data_size = get_static_size();

			//如果结构是静态类型,直接复制内存,返回成功
			if (static_data_size != PTR_TYPE)
			{
				void* p = (void*)(((byte*)this) + members[0]._pos_offset);
				memcpy(pBuff, p, static_data_size);
				outBuffSize = static_data_size;
				return true;
			}

			//数据尾指针
			const byte* const pDataEnd = pBuff + inBuffSize;
			//数据指针
			byte* pData = pBuff;

			//写入结构字段成员列表
			for (size_t i = 0; i < members.size(); i++)
			{
				//成员指针
				void* pMember = (void*)(((byte*)this) + members[i]._pos_offset);

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

	public:

		static std::set<size_t>& codes() {
			static std::set<size_t> scodes;
			return scodes;
		};
		static bool isAutoObj(size_t code)
		{
			if (codes().find(code) != codes().end())
			{
				return true;
			}
			return false;
		}
		static void addObjCode(size_t code)
		{
			codes().insert(code);
		}
		static AutoStruct* BuildStruct(size_t code, byte* pBuff, uint32 dataSize)
		{
			AutoStruct* pStru = BuildStruct(code);
			if (pStru)
			{
				stru_size_t outSize = 0;
				if (pStru->ReadFrom(pBuff, dataSize, outSize))
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
	private:
		static std::map<size_t, std::function<AutoStruct* ()>>& get_create_map()
		{
			static std::map<size_t, std::function<AutoStruct* ()>> map_create;
			return map_create;
		}
	};

	class CStruRegistor
	{
	public:
		CStruRegistor(size_t code, std::function<AutoStruct* ()> funcCreate)
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

	//实类型（完全不包含指针，引用的类型）模板
	template<typename tyname>
	struct  type_helper_real
	{
		static const stru_size_t dtsize = sizeof(tyname);
		static const bool isarray = false;
		static bool arraysize(void* pMember)
		{
			return 0;
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
		static stru_size_t size(void* pMember)
		{	

			return dtsize;
		}
	};
		
	template<typename tyname>
	struct  type_helper_nosupport
	{
		static const stru_size_t dtsize = tyname::不支持这个类型();
		static const bool isarray = tyname::不支持这个类型();
		static bool arraysize(void* pMember)
		{
			static_assert (0, "不支持读取这个类型数据");
			return 0;
		}
		static bool read(void* pMember, byte* pBuff, const stru_size_t inBuffSize, stru_size_t& outBuffSize)
		{
			static_assert (0, "不支持读取这个类型数据");
			return false;
		};
		static bool write(void* pMember, byte* pBuff, const stru_size_t inBuffSize, stru_size_t& outBuffSize)
		{
			static_assert (0, "不支持写入这个类型数据");
			return false;
		};
		static stru_size_t size(void* pMember)
		{
			static_assert (0, "不支持获取这个类型的大小");
			return 0;
		}
	};
	
	//单参数容器获到大小函数模板
	template<typename tyname>
	stru_size_t size_single(tyname& field)
	{
		stru_size_t size = 0;
		for each (const tyname::value_type & item in field)
		{
			size += type_helper<tyname::value_type>::size((void*)&item);
		}
		return size + sizeof(stru_size_t);
	}

	template<class _ty>
	struct type_helper_single_list
	{
		static const stru_size_t dtsize = PTR_TYPE;
		static const bool isarray = true;
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
		static stru_size_t size(void* pMember)
		{
			std::list<_ty>* ptr = (std::list<_ty>*)pMember;
			return size_single<std::list<_ty>>(*ptr);
// 			_ty& field = *((_ty*)pMember);
// 			stru_size_t size = 0;
// 			for each (const valtype & item in field)
// 			{
// 				size += type_helper<_valtype>::size((void*)&item);
// 			}
// 			return size + sizeof(stru_size_t);
		}
	};


	//分离出非容器中的enum类型
	//传递容器类型和AutoStruct类型，其它已被剥离	
	template<typename tyname>
	struct  type_helper
	{
		static const stru_size_t dtsize = std::conditional <
			std::is_enum<tyname>::value,		//是否为enum类型
			type_helper_real<tyname>,			//分离出enum类型,使用实类型模板
			type_helper_nosupport<tyname> //不支持类型
		>::type::dtsize;
		static const bool isarray = std::conditional <
			std::is_enum<tyname>::value,		//是否为enum类型
			type_helper_real<tyname>,			//分离出enum类型,使用实类型模板
			type_helper_nosupport<tyname> //不支持类型
		>::type::isarray;

		static bool arraysize(void* pMember)
		{
			return std::conditional <
				std::is_enum<tyname>::value,		//是否为enum类型
				type_helper_real<tyname>,			//分离出enum类型,使用实类型模板
				type_helper_nosupport<tyname>		//不支持类型
			>::type::arraysize(pMember);
		}

		static bool read(void* pMember, byte* pBuff, const stru_size_t inBuffSize, stru_size_t& outBuffSize)
		{
			return std::conditional <
				std::is_enum<tyname>::value,		//是否为enum类型
				type_helper_real<tyname>,			//分离出enum类型,使用实类型模板
				type_helper_nosupport<tyname>		//传递容器类型和AutoStruct子类型;
			>::type::read(pMember, pBuff, inBuffSize, outBuffSize);
		};
		static bool write(void* pMember, byte* pBuff, const stru_size_t inBuffSize, stru_size_t& outBuffSize)
		{
			return std::conditional <
				std::is_enum<tyname>::value,		//是否为enum类型
				type_helper_real<tyname>,			//分离出enum类型,使用实类型模板
				type_helper_nosupport<tyname>		//传递容器类型和AutoStruct子类型;
			>::type::write(pMember, pBuff, inBuffSize, outBuffSize);
		};
		static stru_size_t size(void* pMember)
		{
			return std::conditional <
				std::is_enum<tyname>::value,		//是否为enum类型
				type_helper_real<tyname>,			//分离出enum类型,使用实类型模板
				type_helper_nosupport<tyname>		//传递容器类型和AutoStruct子类型;
			>::type::size(pMember);
		}

	};


	

//#define AUTO_LIST
#ifdef AUTO_LIST
	//特化单参数容器类型存取（不包含指针类型,引用的类型）
#define LIST_TEMPLATE(__Type) template<>  struct  type_helper<std::list<__Type>>:public AUTO::type_helper_single<std::list<__Type>,__Type>{}
#define OBJ_LIST_TEMPLATE(__Type) template<>  struct  type_helper<std::list<__Type>>:public AUTO::type_helper_single<std::list<AutoStruct>,AutoStruct>{}
#else
#define LIST_TEMPLATE(__Type) 
#define OBJ_LIST_TEMPLATE(__Type) 
#endif

//#define AUTO_VECTOR
#ifdef AUTO_VECTOR
	//特化单参数容器类型存取（不包含指针类型,引用的类型）
#define VECTOR_TEMPLATE(__Type) template<>  struct  type_helper<std::vector<__Type>>:public AUTO::type_helper_single<std::vector<__Type>>{}
#define OBJ_VECTOR_TEMPLATE(__Type) template<>  struct  type_helper<std::vector<__Type>>:public AUTO::type_helper_single<std::vector<AutoStruct>>{}
#else
#define VECTOR_TEMPLATE(__Type) 
#define OBJ_VECTOR_TEMPLATE(__Type)
#endif


	//特化实类型存取（不包含指针类型,引用的类型）
#define REAL_TYPE_TEMPLATE(__Type) template<>  struct  type_helper<__Type>:public AUTO::type_helper_real<__Type>{};  \
	LIST_TEMPLATE(__Type);  \
	VECTOR_TEMPLATE(__Type);

	//实类型（完全不包含指针的类型）的特化
	REAL_TYPE_TEMPLATE(bool);
	//REAL_TYPE_TEMPLATE(int8);
	//REAL_TYPE_TEMPLATE(uint8);
	//REAL_TYPE_TEMPLATE(int16);
	//REAL_TYPE_TEMPLATE(uint16);
	//REAL_TYPE_TEMPLATE(int32);
	//REAL_TYPE_TEMPLATE(uint32);
	//REAL_TYPE_TEMPLATE(int64);
	//REAL_TYPE_TEMPLATE(uint64);
	//REAL_TYPE_TEMPLATE(float);
	//REAL_TYPE_TEMPLATE(double);
	
	//特化STL的字符串类型
	template<>
	struct type_helper<std::string>
	{
		static const stru_size_t dtsize = PTR_TYPE;
		static const bool isarray = false;
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
		static stru_size_t size(void* pMember)
		{
			std::string* ptr = (std::string*)pMember;
			return (stru_size_t)(ptr->size()+sizeof(stru_size_t));
		}
	};
	//VECTOR_TEMPLATE(std::string);
	//LIST_TEMPLATE(std::string);

	//AutoStruct类型的特化
	template<>
	struct type_helper<AutoStruct>
	{
		static const stru_size_t dtsize = PTR_TYPE;
		static const bool isarray = false;
		static bool read(void* pMember, byte* pBuff, const stru_size_t inBuffSize, stru_size_t& outBuffSize)
		{
			AutoStruct* ptr = (AutoStruct*)pMember;
			return ptr->ReadFrom(pBuff, inBuffSize, outBuffSize);
			
		};
		static bool write(void* pMember, byte* pBuff, const stru_size_t inBuffSize, stru_size_t& outBuffSize)
		{
			AutoStruct* ptr = (AutoStruct*)pMember;
			return ptr->WriteTo(pBuff, inBuffSize, outBuffSize);
		};
		static stru_size_t size(void* pMember)
		{
			AutoStruct* ptr = (AutoStruct*)pMember;
			return ptr->get_size();
		}
	};
	//VECTOR_TEMPLATE(AutoStruct);
	//LIST_TEMPLATE(AutoStruct);

#define AUTO_STRU_END(__CLASSNAME)  };REG_STRU(__CLASSNAME)
//template<> struct type_helper<__CLASSNAME>: public AUTO::type_helper<AUTO::AutoStruct>{};  \
//OBJ_VECTOR_TEMPLATE(__CLASSNAME);  \
//OBJ_LIST_TEMPLATE(__CLASSNAME);
}

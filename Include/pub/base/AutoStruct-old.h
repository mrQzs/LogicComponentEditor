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


//��ȡ��Ա������ƫ����
#define __OFFSET__(__THECLASS,__MEMBER_NAME) ((uint32)((size_t)&((__THECLASS *)0)->__MEMBER_NAME))

//���ڿɱ������Ķ���
#define PRIVATE_ARGS_GLUE(x, y) x y
#define PRIVATE_MACRO_VAR_ARGS_IMPL_COUNT(_1,_2,_3,_4,_5,_6,_7,_8,_9, _10, N, ...) N
#define PRIVATE_MACRO_VAR_ARGS_IMPL(args) PRIVATE_MACRO_VAR_ARGS_IMPL_COUNT args
#define COUNT_MACRO_VAR_ARGS(...) PRIVATE_MACRO_VAR_ARGS_IMPL((__VA_ARGS__,10, 9,8,7,6,5,4,3,2,1,0))
#define PRIVATE_MACRO_CHOOSE_HELPER2(M,count)  M##count
#define PRIVATE_MACRO_CHOOSE_HELPER1(M,count) PRIVATE_MACRO_CHOOSE_HELPER2(M,count)
#define PRIVATE_MACRO_CHOOSE_HELPER(M,count)   PRIVATE_MACRO_CHOOSE_HELPER1(M,count)
#define INVOKE_VAR_MACRO(M,...) PRIVATE_ARGS_GLUE(PRIVATE_MACRO_CHOOSE_HELPER(M,COUNT_MACRO_VAR_ARGS(__VA_ARGS__)), (__VA_ARGS__))

//�Զ��ṹ�ĺ궨��
#define AUTO_STRU_BEGIN(__CLASSNAME) struct __CLASSNAME :public AUTO::AutoStruct{ STRU_DEF(__CLASSNAME,false);

//ע���Զ��ṹ�������Զ��ṹ�Ķ�̬����
#define REG_STRU(__THISCLASS) const AUTO::CStruRegistor __THISCLASS##_regist(__THISCLASS::code(), []() {return new __THISCLASS(); });



//ע��������л�֧�ֺ�
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


//FIELD�����
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
	//������������
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




	//�ṹ�Ĵ�С����
	typedef uint32 stru_size_t;
	static const stru_size_t PTR_TYPE = sizeof(stru_size_t) == 2 ? 0xFFFF : sizeof(stru_size_t) == 4 ? 0xFFFFFFFF : 0;
	typedef std::function<bool(void* pMember, byte* pBuff, const stru_size_t inBuffSize, stru_size_t& outBuffSize)> funcReadWrite;
	typedef std::function<stru_size_t(void* pMember)> funcSize;

	//�ṹ�ֶ���Ϣ
	struct field_info
	{
		field_info(LPCSTR type_name, LPCSTR field_name, LPCSTR field_desc, size_t hash_code, bool isarray, bool isenum, stru_size_t store_size, stru_size_t pos_offset,
			funcReadWrite funcRead, funcReadWrite funcWrite, funcSize size)
		{
			_hash_code = hash_code;//�ֶ����͵�Hashcode
			_type_name = type_name;//�ֶ�������
			_field_name = field_name;//�ֶ�����
			_field_desc = field_desc;//�ֶ�����
			_store_size = store_size;//�ֶδ�ȡ��ʽ���С 0xFFFF/0xFFFFFFFF��ʾ��ָ̬�룬�������ڶ�̬��������0��ʾ�ǿ����ݣ�������ʾ���ھ�̬��������С
			_pos_offset = pos_offset;//�ֶ��ڽṹ�е�ƫ��λ��
			_funcRead = funcRead;//�ֶζ�����
			_funcWrite = funcWrite;//�ֶ�д����	
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



		enumDBOType _dbo_type = emDT_NULL;//�ֶ�ֵ����
		bool        _is_array = false;//�Ƿ����飬��������飬��Ϊvector����
		size_t _hash_code = 0;//�ֶ����͵�Hashcode
		std::string _type_name;//�ֶ�������
		std::string _field_name;//�ֶ�����
		std::string _field_desc;//�ֶ�����
		stru_size_t	_store_size = 0;//�ֶδ�ȡ��ʽ���С 0xFFFF/0xFFFFFFFF��ʾ��ָ̬�룬�������ڶ�̬��������0��ʾ�ǿ����ݣ�������ʾ���ھ�̬��������С
		stru_size_t	_pos_offset = 0;//�ֶ��ڽṹ�е�ƫ��λ��
		funcReadWrite _funcRead;//�ֶζ�����
		funcReadWrite _funcWrite;//�ֶ�д����		
		funcSize    _funcSize;
	};

	typedef std::vector<field_info> fieldlist;

	class field_register
	{
	public:
		field_register(fieldlist& memlist, LPCSTR type_name, LPCSTR field_name, LPCSTR field_desc, size_t hash_code, bool isarray, bool isenum,
			stru_size_t pos_offset, stru_size_t store_size,
			funcReadWrite funcRead, funcReadWrite funcWrite, funcSize size)
		{//��ʼ����Ա����
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
		// description: ��ȡ��̬���ݵĴ�С
		// Method:     get_static_size
		// Access:     public 
		// Returns:    uint32 ���ؾ�̬���ݴ�С,����Ǿ�̬���ݣ�����0
		//************************************
		virtual stru_size_t get_static_size() = 0;

		//************************************
		// description: ��ȡ�ṹ�����ݴ�С������ṹ�Ǿ�̬���ݣ���ʹ��get_static_size����ȡ��С
		// Method:     get_size
		// Access:     public 
		// Parameter:  bool isUpdate		�Ƿ��ȡ���´�С��true�����¼���ṹ�Ĵ�С��falseֱ�ӷ����ϴμ���Ĵ�С��
		// Returns:    uint32 ���ؽṹ���ݵĴ�С��������̬���ݺͶ�̬����
		//************************************
		stru_size_t get_size(bool isUpdate = false)
		{
			//����Ǿ�̬��С��ֱ�ӷ��ؽṹ�Ĵ�С
			if (get_static_size() != PTR_TYPE) return get_static_size();

			//��������µ�ǰ��С��ֱ�ӷ����ϴμ�����
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
		// description:				�ӻ����ж�ȡ���ݵ��ֶγ�Ա
		// Method:     read
		// Access:     public 
		// Returns:    bool      ���ض�ȡ��� 
		// Parameter:  byte * pBuff				Ҫ��ȡ���������ݣ�
		// Parameter:  const uint16 inBuffSize  Ҫ��ȡ����Ĵ�С
		// Parameter:  uint16 & outBuffSize		�Ѷ�ȡ����Ĵ�С��
		//************************************
		bool ReadFrom(byte* pBuff, const stru_size_t inBuffSize, stru_size_t& outBuffSize)
		{
			outBuffSize = 0;
			const fieldlist& members = get_fieldlist();

			//����ȡ����Ϊ�գ�����
			if (pBuff == nullptr || inBuffSize == 0)
			{
				_ASSERT(false);
				return false;
			}

			//������ֶγ�Ա�Ŀսṹ������ʧ�ܣ�
			if (members.size() == 0)
			{
				_ASSERT(false);
				return false;
			}

			//��ȡ��̬���ݴ�С
			stru_size_t static_data_size = get_static_size();

			//����ṹ�Ǿ�̬����,ֱ�Ӹ����ڴ�,���سɹ�
			if (static_data_size != PTR_TYPE)
			{
				void* p = (void*)(((byte*)this) + members[0]._pos_offset);
				memcpy(p, pBuff, static_data_size);
				outBuffSize = static_data_size;
				return true;
			}

			//����βָ��
			const byte* const pDataEnd = pBuff + inBuffSize;
			//����ָ��
			byte* pData = pBuff;

			//��ȡ�ṹ�ֶγ�Ա�б�
			for (size_t i = 0; i < members.size(); i++)
			{
				//��Աָ��
				void* pMember = (void*)(((byte*)this) + members[i]._pos_offset);

				//��ȡ�����С
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
		// description:				�ѳ�Ա�ֶ�����д�뵽������
		// Method:     write
		// Access:     public 
		// Returns:    bool		����д����
		// Parameter:  byte * pBuff				Ҫд���ݵĻ��棬
		// Parameter:  const uint16 inBuffSize	Ҫд�뻺��Ĵ�С
		// Parameter:  uint16 & outBuffSize		��д����Ĵ�С��
		//************************************
		bool WriteTo(byte* pBuff, const stru_size_t inBuffSize, stru_size_t& outBuffSize)
		{
			outBuffSize = 0;
			const fieldlist& members = get_fieldlist();

			//��д�뻺��Ϊ�գ�����ʧ��
			if (pBuff == nullptr || inBuffSize == 0)
			{
				_ASSERT(false);
				return false;
			}

			//������ֶγ�Ա�Ŀսṹ������ʧ�ܣ�
			if (members.size() == 0)
			{
				_ASSERT(false);
				return false;
			}

			//������治��д�룬����ʧ�ܣ�
			if (get_size() > inBuffSize)
			{
				_ASSERT(false);
				return false;
			}

			//��ȡ��̬���ݴ�С
			stru_size_t static_data_size = get_static_size();

			//����ṹ�Ǿ�̬����,ֱ�Ӹ����ڴ�,���سɹ�
			if (static_data_size != PTR_TYPE)
			{
				void* p = (void*)(((byte*)this) + members[0]._pos_offset);
				memcpy(pBuff, p, static_data_size);
				outBuffSize = static_data_size;
				return true;
			}

			//����βָ��
			const byte* const pDataEnd = pBuff + inBuffSize;
			//����ָ��
			byte* pData = pBuff;

			//д��ṹ�ֶγ�Ա�б�
			for (size_t i = 0; i < members.size(); i++)
			{
				//��Աָ��
				void* pMember = (void*)(((byte*)this) + members[i]._pos_offset);

				//д�뻺���С
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

	//ʵ���ͣ���ȫ������ָ�룬���õ����ͣ�ģ��
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
		static const stru_size_t dtsize = tyname::��֧���������();
		static const bool isarray = tyname::��֧���������();
		static bool arraysize(void* pMember)
		{
			static_assert (0, "��֧�ֶ�ȡ�����������");
			return 0;
		}
		static bool read(void* pMember, byte* pBuff, const stru_size_t inBuffSize, stru_size_t& outBuffSize)
		{
			static_assert (0, "��֧�ֶ�ȡ�����������");
			return false;
		};
		static bool write(void* pMember, byte* pBuff, const stru_size_t inBuffSize, stru_size_t& outBuffSize)
		{
			static_assert (0, "��֧��д�������������");
			return false;
		};
		static stru_size_t size(void* pMember)
		{
			static_assert (0, "��֧�ֻ�ȡ������͵Ĵ�С");
			return 0;
		}
	};
	
	//�����������񵽴�С����ģ��
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
			// 				if (total == 0)//�������Ϊ0���������
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
			// 				if (total == 0)//�������Ϊ0���������
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


	//������������е�enum����
	//�����������ͺ�AutoStruct���ͣ������ѱ�����	
	template<typename tyname>
	struct  type_helper
	{
		static const stru_size_t dtsize = std::conditional <
			std::is_enum<tyname>::value,		//�Ƿ�Ϊenum����
			type_helper_real<tyname>,			//�����enum����,ʹ��ʵ����ģ��
			type_helper_nosupport<tyname> //��֧������
		>::type::dtsize;
		static const bool isarray = std::conditional <
			std::is_enum<tyname>::value,		//�Ƿ�Ϊenum����
			type_helper_real<tyname>,			//�����enum����,ʹ��ʵ����ģ��
			type_helper_nosupport<tyname> //��֧������
		>::type::isarray;

		static bool arraysize(void* pMember)
		{
			return std::conditional <
				std::is_enum<tyname>::value,		//�Ƿ�Ϊenum����
				type_helper_real<tyname>,			//�����enum����,ʹ��ʵ����ģ��
				type_helper_nosupport<tyname>		//��֧������
			>::type::arraysize(pMember);
		}

		static bool read(void* pMember, byte* pBuff, const stru_size_t inBuffSize, stru_size_t& outBuffSize)
		{
			return std::conditional <
				std::is_enum<tyname>::value,		//�Ƿ�Ϊenum����
				type_helper_real<tyname>,			//�����enum����,ʹ��ʵ����ģ��
				type_helper_nosupport<tyname>		//�����������ͺ�AutoStruct������;
			>::type::read(pMember, pBuff, inBuffSize, outBuffSize);
		};
		static bool write(void* pMember, byte* pBuff, const stru_size_t inBuffSize, stru_size_t& outBuffSize)
		{
			return std::conditional <
				std::is_enum<tyname>::value,		//�Ƿ�Ϊenum����
				type_helper_real<tyname>,			//�����enum����,ʹ��ʵ����ģ��
				type_helper_nosupport<tyname>		//�����������ͺ�AutoStruct������;
			>::type::write(pMember, pBuff, inBuffSize, outBuffSize);
		};
		static stru_size_t size(void* pMember)
		{
			return std::conditional <
				std::is_enum<tyname>::value,		//�Ƿ�Ϊenum����
				type_helper_real<tyname>,			//�����enum����,ʹ��ʵ����ģ��
				type_helper_nosupport<tyname>		//�����������ͺ�AutoStruct������;
			>::type::size(pMember);
		}

	};


	

//#define AUTO_LIST
#ifdef AUTO_LIST
	//�ػ��������������ʹ�ȡ��������ָ������,���õ����ͣ�
#define LIST_TEMPLATE(__Type) template<>  struct  type_helper<std::list<__Type>>:public AUTO::type_helper_single<std::list<__Type>,__Type>{}
#define OBJ_LIST_TEMPLATE(__Type) template<>  struct  type_helper<std::list<__Type>>:public AUTO::type_helper_single<std::list<AutoStruct>,AutoStruct>{}
#else
#define LIST_TEMPLATE(__Type) 
#define OBJ_LIST_TEMPLATE(__Type) 
#endif

//#define AUTO_VECTOR
#ifdef AUTO_VECTOR
	//�ػ��������������ʹ�ȡ��������ָ������,���õ����ͣ�
#define VECTOR_TEMPLATE(__Type) template<>  struct  type_helper<std::vector<__Type>>:public AUTO::type_helper_single<std::vector<__Type>>{}
#define OBJ_VECTOR_TEMPLATE(__Type) template<>  struct  type_helper<std::vector<__Type>>:public AUTO::type_helper_single<std::vector<AutoStruct>>{}
#else
#define VECTOR_TEMPLATE(__Type) 
#define OBJ_VECTOR_TEMPLATE(__Type)
#endif


	//�ػ�ʵ���ʹ�ȡ��������ָ������,���õ����ͣ�
#define REAL_TYPE_TEMPLATE(__Type) template<>  struct  type_helper<__Type>:public AUTO::type_helper_real<__Type>{};  \
	LIST_TEMPLATE(__Type);  \
	VECTOR_TEMPLATE(__Type);

	//ʵ���ͣ���ȫ������ָ������ͣ����ػ�
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
	
	//�ػ�STL���ַ�������
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

				if (total == 0)//�������Ϊ0���������
				{
					outBuffSize = sizeof(total);
					return true;
				}

				ptr->reserve((size_t)total);
				ptr->resize(total);

				//���ɶ�ȡ���� 
				stru_size_t canreadsize = inBuffSize - sizeof(total);

				//��ǰ�ɶ�ȡ����
				stru_size_t copysize = std::min<stru_size_t>(canreadsize, total);

				//��ȡ����ȡ�����ݵ�ָ��
				byte* p = ((byte*)ptr->data());

				if (copysize)
				{
					//��ȡ����
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

				if (total == 0)//�������Ϊ0���������
				{
					outBuffSize = sizeof(total);
					return true;
				}

				//����д������ 
				stru_size_t canwritesize = inBuffSize - sizeof(total);

				//��ǰ��д������
				stru_size_t copysize = std::min<stru_size_t>(canwritesize, total);

				//��ȡ����ȡ�����ݵ�ָ��
				byte* p = ((byte*)ptr->data());

				if (copysize)
				{
					//��ȡ����
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

	//AutoStruct���͵��ػ�
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

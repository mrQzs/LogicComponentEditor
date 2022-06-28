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
#include <any>


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
#define REG_STRU(__THISCLASS) const AUTO::AutoRegistor __THISCLASS##_regist(__THISCLASS::code(), []() {return new __THISCLASS(); });



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
	virtual bool get_isDBO(){return __ISDBO;}								\
	virtual bool get_mem_val(uint32 index, std::any& outVal)						\
	{																				\
		const AUTO::fieldlist& members = s_fieldlist();						\
		if (index>=0 && index<members.size())						\
		{																				\
			void* pMember = (void*)(((byte*)this) + members[index]._pos_offset);						\
			return members[index]._funcGetMember(pMember,outVal);						\
		}																				\
		return false;																				\
	}																				\
	virtual bool set_mem_val(uint32 index, std::any& newVal)						\
	{																				\
		const AUTO::fieldlist& members = s_fieldlist();						\
		if (index >= 0 && index < members.size())						\
		{																				\
			void* pMember = (void*)(((byte*)this) + members[index]._pos_offset);						\
			return members[index]._funcSetMember(pMember, newVal);						\
		}																				\
		return false;																				\
	}																				\
	virtual bool get_item_val(uint32 memindex, uint32 itemindex, std::any& outVal)			\
	{																				\
		const AUTO::fieldlist& members = s_fieldlist();											\
		if (memindex >= 0 && memindex < members.size())											\
		{																				\
			void* pMember = (void*)(((byte*)this) + members[memindex]._pos_offset);		\
			return members[memindex]._funcGetItem(pMember,itemindex, outVal);				\
		}																				\
		return false;																				\
	}																				\
	virtual bool set_item_val(uint32 memindex, uint32 itemindex, std::any& newVal)			\
	{				\
		const AUTO::fieldlist& members = s_fieldlist();				\
		if (memindex >= 0 && memindex < members.size())				\
		{				\
			void* pMember = (void*)(((byte*)this) + members[memindex]._pos_offset);				\
			return members[memindex]._funcSetItem(pMember, itemindex, newVal);				\
		}				\
		return false;					\
	}

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
				AUTO::type_helper<decltype(__FIELD_NAME)>::code(),   \
				AUTO::type_helper<decltype(__FIELD_NAME)>::isarray,    \
				AUTO::type_helper<decltype(__FIELD_NAME)>::isenum,    \
				AUTO::type_helper<decltype(__FIELD_NAME)>::isautodata,    \
				__OFFSET__(thisClass,__FIELD_NAME),                             \
				AUTO::type_helper<decltype(__FIELD_NAME)>::dtsize,               \
				AUTO::type_helper<decltype(__FIELD_NAME)>::read,  \
				AUTO::type_helper<decltype(__FIELD_NAME)>::write,			\
				AUTO::type_helper<decltype(__FIELD_NAME)>::size,			\
				AUTO::type_helper<decltype(__FIELD_NAME)>::get_val,			\
				AUTO::type_helper<decltype(__FIELD_NAME)>::set_val,			\
				AUTO::type_helper<decltype(__FIELD_NAME)>::get_item,			\
				AUTO::type_helper<decltype(__FIELD_NAME)>::set_item);  \
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
		emDT_BOOL,
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
		emDT_ENUM,
		emDT_AUTODATA,
		emDT_REALTYPE,
	};

	//�ṹ�Ĵ�С����
	typedef uint32 stru_size_t;
	static const stru_size_t PTR_TYPE = sizeof(stru_size_t) == 2 ? 0xFFFF : sizeof(stru_size_t) == 4 ? 0xFFFFFFFF : 0;
	typedef std::function<bool(void*, byte* , const stru_size_t , stru_size_t& )> funcReadWrite;
	typedef std::function<stru_size_t(void* )> funcSize;
	typedef std::function<bool(void*,  std::any&)> funcGetSetMember;
	typedef std::function<bool(void*, uint32 , std::any& )> funcGetSetItem;


	//�ṹ�ֶ���Ϣ
	struct field_info
	{
		field_info(LPCSTR type_name, LPCSTR field_name, LPCSTR field_desc, size_t hash_code,
			bool isarray, bool isenum,bool isautodata, stru_size_t store_size, stru_size_t pos_offset,
			funcReadWrite funcRead, funcReadWrite funcWrite, funcSize size,
			funcGetSetMember funcGetMember,funcGetSetMember funcSetMember,
			funcGetSetItem funcGetItem,funcGetSetItem funcSetItem)
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
			_funcGetMember=funcGetMember; //��ȡ�ֶ�ֵ
			_funcSetMember=funcSetMember; //�����ֶ�ֵ
			_funcGetItem=funcGetItem;    //��ȡ��������ֵ
			_funcSetItem=funcSetItem;   //������������ֵ
			if (!isenum)
			{
				if (_hash_code == typeid(bool).hash_code())
				{
					_dbo_type = emDT_BOOL;
				}
				else if(_hash_code == typeid(int8).hash_code())
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
					if (isautodata)
					{
						_dbo_type = emDT_AUTODATA;
					}
					else
					{
						_dbo_type = emDT_REALTYPE;
					}
					
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
		funcSize    _funcSize;   //�ֶλ�ȡ�ڴ�ռ�ô�С
		funcGetSetMember _funcGetMember; //��ȡ�ֶ�ֵ
		funcGetSetMember _funcSetMember; //�����ֶ�ֵ
		funcGetSetItem _funcGetItem;    //��ȡ��������ֵ
		funcGetSetItem _funcSetItem;   //������������ֵ

	};

	typedef std::vector<field_info> fieldlist;

	class field_register
	{
	public:
		field_register(fieldlist& memlist, LPCSTR type_name, LPCSTR field_name, LPCSTR field_desc, size_t hash_code,
			bool isarray, bool isenum,bool isautodata,
			stru_size_t pos_offset, stru_size_t store_size,
			funcReadWrite funcRead, funcReadWrite funcWrite, funcSize size,
			funcGetSetMember funcGetMember, funcGetSetMember funcSetMember,
			funcGetSetItem funcGetItem, funcGetSetItem funcSetItem)
		{//��ʼ����Ա����
			field_info field(type_name, field_name, field_desc, hash_code, isarray, isenum,isautodata, store_size, pos_offset,
				funcRead, funcWrite, size,funcGetMember,funcSetMember,funcGetItem,funcSetItem);
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


		virtual size_t get_code() = 0;
		virtual bool get_isDBO() = 0;
		virtual fieldlist& get_fieldlist() = 0; 

		template<typename _tyCast>
		bool get_member_val(uint32 index, _tyCast& outVal)
		{			
			if (index>=0 && index < get_fieldlist().size())
			{
				const field_info& info = get_fieldlist()[index];

				return info._funcGetMember((((byte*)this) + info._pos_offset), outVal);
// 				if (info._dbo_type==emDT_AUTODATA)
// 				{//�����AUTODATA
// 					if (std::is_pointer<_tyCast>::value)
// 					{//�����ȡ����Ϊָ������
// 						if (typeid(_tyCast) == typeid(AutoStruct*) ||
// 							typeid(decltype(*outVal)).hash_code()== info._hash_code)
// 						{
// 							
// 							outVal = (_tyCast)(((byte*)this) + info._pos_offset);
// 						}
// 					}else if (typeid(_tyCast) == typeid(std::string))
// 					{//���Ϊ�ַ���
// 						int aaa = 0;
// 					}
// 					
// 				}

			}
			return false;
		}
 		virtual bool set_mem_val(uint32 index, std::any& outVal) = 0;
 		virtual bool get_item_val(uint32 memindex,uint32 itemindex, std::any& outVal) = 0;
 		virtual bool set_item_val(uint32 memindex, uint32 itemindex, std::any& outVal) = 0;

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
		static bool isAutoObj(size_t code)
		{
			if (codes().find(code) != codes().end())
			{
				return true;
			}
			return false;
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

	//ʵ���ͣ���ȫ������ָ�룬���õ����ͣ�ģ��
	template<typename tyname>
	struct  type_helper_real
	{
		static const bool isnum = std::is_integral<tyname>::value;
		static const bool isfloat = std::is_floating_point<tyname>::value;
		static const stru_size_t dtsize = sizeof(tyname);
		static const bool isenum = std::is_enum<tyname>::value;
		static const bool isarray = false;
		static const bool isautodata = false;
		static const size_t code() { return typeid(tyname).hash_code(); }
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
		template<typename _tyCast>
		static bool get_val(void* pMember, _tyCast& outVal)
		{
			tyname& field = *((tyname*)pMember);
			if (typeid(tyname)==typeid(_tyCast))
			{				
				outVal = field;
				return true;
			}else if (isnum || isfloat)
			{
				if ((isnum && std::is_integral<_tyCast>::value) ||
					(isfloat && std::is_floating_point<_tyCast>::value))
				{
					if (sizeof(_tyCast)>=sizeof(tyname))
					{
						outVal = field;
						return true;
					}
				}

				if (typeid(_tyCast)== typeid(std::string))
				{
					stringstream ss;
					ss << field;
					ss.flush();
					outVal = ss.str();
					return true;
				}
			}
			return false;
		}
		template<typename _tyCast>
		static bool set_val(void* pMember, _tyCast& newVal)
		{
			tyname& field = *((tyname*)pMember);
			if (typeid(tyname) == typeid(_tyCast))
			{
				field = newVal;
				return true;
			}
			else if (isnum || isfloat)
			{
				if ((isnum && std::is_integral<_tyCast>::value) ||
					(isfloat && std::is_floating_point<_tyCast>::value))
				{
					if (sizeof(_tyCast) <= sizeof(tyname))
					{
						field = newVal;
						return true;
					}
				}

			}
			return false;
		}
		template<typename _tyCast>
		static bool get_item(void* pMember, uint32 itemindex, _tyCast& outVal)
		{
			return false;
		}
		template<typename _tyCast>
		static bool set_item(void* pMember, uint32 itemindex, _tyCast& newVal)
		{
			return false;
		}
	};
	
	//����֧�ֵ�����
	template<typename tyname>
	struct  type_helper_nosupport
	{
		static const stru_size_t dtsize = tyname::��֧���������();
		static const bool isenum = tyname::��֧���������();
		static const bool isarray = tyname::��֧���������();
		static const bool isautodata =tyname::��֧���������();
		static const size_t code() 
		{ 
			static_assert (0, "��֧�ֶ�ȡ�����������");
			return 0;
		}
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
		template<typename _tyCast>
		static bool get_val(void* pMember, _tyCast& outVal)
		{
			static_assert (0, "��֧���������");
			return false;
		}
		template<typename _tyCast>
		static bool set_val(void* pMember, _tyCast& newVal)
		{
			static_assert (0, "��֧���������");
			return false;
		}
		template<typename _tyCast>
		static bool get_item(void* pMember, uint32 itemindex, _tyCast& outVal)
		{
			static_assert (0, "��֧���������");
			return false;
		}
		template<typename _tyCast>
		static bool set_item(void* pMember, uint32 itemindex, _tyCast& newVal)
		{
			static_assert (0, "��֧���������");
			return false;
		}
	};
	
	
	//����������ģ��
	template<class _ty>
	struct type_helper_single
	{
		static const stru_size_t dtsize = PTR_TYPE;
		static const bool isenum = std::is_enum<_ty::value_type>::value;
		static const bool isarray = true;
		static const bool isautodata = type_helper<_ty::value_type>::isautodata;
		static const size_t code() { return typeid(_ty::value_type).hash_code(); }
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
			_ty& field = *((_ty*)pMember);
			stru_size_t size = 0;
			for each (const _ty::value_type & item in field)
			{
				size += type_helper<_ty::value_type>::size((void*)&item);
			}
			return size + sizeof(stru_size_t);
		}
		template<typename _tyCast>
		static bool get_val(void* pMember, _tyCast& outVal)
		{
			return false;
		}
		template<typename _tyCast>
		static bool set_val(void* pMember, _tyCast& newVal)
		{			
			return false;
		}
		template<typename _tyCast>
		static bool get_item(void* pMember, uint32 itemindex, _tyCast& outVal)
		{
			_ty& field = *((_ty*)pMember);
			if (itemindex>=0 || itemindex<field.size())
			{
				int i = 0;
				for each (const _ty::value_type & item in field)
				{
					if (i == itemindex)
					{
						outVal = item;
						return true;
					}
				}
			}
			
			return false;
		}
		template<typename _tyCast>
		static bool set_item(void* pMember, uint32 itemindex, _tyCast& newVal)
		{
			_ty& field = *((_ty*)pMember);
			if (itemindex >= 0 || itemindex < field.size())
			{
				int i = 0;
				for each (const _ty::value_type & item in field)
				{
					if (i == itemindex)
					{
						*(const_cast<_ty::value_type*>(&item)) = *(newVal._Cast<_ty::value_type>());
						return true;
					}
				}
			}

			return false;
		}

	};


	//AutoStruct���͵�ģ��
	template<class _ty>
	struct type_helper_autodata
	{
		static const stru_size_t dtsize = PTR_TYPE;
		static const bool isenum = false;
		static const bool isarray = false;
		static const bool isautodata = true;
		static const size_t code() { return typeid(_ty).hash_code(); }
		static bool read(void* pMember, byte* pBuff, const stru_size_t inBuffSize, stru_size_t& outBuffSize)
		{
			_ty* ptr = (_ty*)pMember;
			return ptr->ReadFrom(pBuff, inBuffSize, outBuffSize);

		};
		static bool write(void* pMember, byte* pBuff, const stru_size_t inBuffSize, stru_size_t& outBuffSize)
		{
			_ty* ptr = (_ty*)pMember;
			return ptr->WriteTo(pBuff, inBuffSize, outBuffSize);
		};
		static stru_size_t size(void* pMember)
		{
			_ty* ptr = (_ty*)pMember;
			return ptr->get_size();
		}
		template<typename _tyCast>
		static bool get_val(void* pMember, _tyCast& outVal)
		{
			_ty& field = *((_ty*)pMember);
			outVal = field;
			return true;
		}
		template<typename _tyCast>
		static bool set_val(void* pMember, _tyCast& newVal)
		{
			_ty& field = *((_ty*)pMember);
			field = *(newVal._Cast<_ty>());
			return true;
		}
		template<typename _tyCast>
		static bool get_item(void* pMember, uint32 itemindex, _tyCast& outVal)
		{
			return false;
		}
		template<typename _tyCast>
		static bool set_item(void* pMember, uint32 itemindex, _tyCast& newVal)
		{
			return false;
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
		static const bool isenum = std::is_enum<tyname>::value;
		static const bool isarray = false;
		static const bool isautodata = false;
		static const size_t code() 
		{ 
			return std::conditional <
				std::is_enum<tyname>::value,		//�Ƿ�Ϊenum����
				type_helper_real<tyname>,			//�����enum����,ʹ��ʵ����ģ��
				type_helper_nosupport<tyname>		//��֧������
			>::type::code();
		}
		static uint32 arraysize(void* pMember)
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
		template<typename _tyCast>
		static bool get_val(void* pMember, _tyCast& outVal)
		{
			return std::conditional <
				std::is_enum<tyname>::value,		//�Ƿ�Ϊenum����
				type_helper_real<tyname>,			//�����enum����,ʹ��ʵ����ģ��
				type_helper_nosupport<tyname>		//�����������ͺ�AutoStruct������;
			>::type::get_val(pMember,outVal);
		}
		template<typename _tyCast>
		static bool set_val(void* pMember, _tyCast& newVal)
		{
			return std::conditional <
				std::is_enum<tyname>::value,		//�Ƿ�Ϊenum����
				type_helper_real<tyname>,			//�����enum����,ʹ��ʵ����ģ��
				type_helper_nosupport<tyname>		//�����������ͺ�AutoStruct������;
			>::type::set_val(pMember, newVal);
		}
		template<typename _tyCast>
		static bool get_item(void* pMember, uint32 itemindex, _tyCast& outVal)
		{
			return std::conditional <
				std::is_enum<tyname>::value,		//�Ƿ�Ϊenum����
				type_helper_real<tyname>,			//�����enum����,ʹ��ʵ����ģ��
				type_helper_nosupport<tyname>		//�����������ͺ�AutoStruct������;
			>::type::get_item(pMember,itemindex, outVal);
		}
		template<typename _tyCast>
		static bool set_item(void* pMember, uint32 itemindex, _tyCast& newVal)
		{
			return std::conditional <
				std::is_enum<tyname>::value,		//�Ƿ�Ϊenum����
				type_helper_real<tyname>,			//�����enum����,ʹ��ʵ����ģ��
				type_helper_nosupport<tyname>		//�����������ͺ�AutoStruct������;
			>::type::set_item(pMember,itemindex, newVal);
		}

	};


	

//#define AUTO_LIST
#ifdef AUTO_LIST
	//�ػ��������������ʹ�ȡ��������ָ������,���õ����ͣ�
#define LIST_REG(__Type) template<>  struct  type_helper<std::list<__Type>>:public type_helper_single<std::list<__Type>>{}
#else
#define LIST_REG(__Type) 
#endif

//#define AUTO_VECTOR
#ifdef AUTO_VECTOR
	//�ػ��������������ʹ�ȡ��������ָ������,���õ����ͣ�
#define VECTOR_REG(__Type) template<>  struct  type_helper<std::vector<__Type>>:public type_helper_single<std::vector<__Type>>{}
#else
#define VECTOR_REG(__Type) 
#endif


	//�ػ�ʵ���ʹ�ȡ��������ָ������,���õ����ͣ�
#define REAL_TYPE_REG(__Type) template<>  struct  type_helper<__Type>:public type_helper_real<__Type>{};  \
	LIST_REG(__Type);  \
	VECTOR_REG(__Type);

	//ʵ���ͣ���ȫ������ָ������ͣ����ػ�
	REAL_TYPE_REG(bool);
	REAL_TYPE_REG(int8);
	REAL_TYPE_REG(uint8);
	REAL_TYPE_REG(int16);
	REAL_TYPE_REG(uint16);
	REAL_TYPE_REG(int32);
	REAL_TYPE_REG(uint32);
	REAL_TYPE_REG(int64);
	REAL_TYPE_REG(uint64);
	REAL_TYPE_REG(float);
	REAL_TYPE_REG(double);
	
	//�ػ�STL���ַ�������
	template<>
	struct type_helper<std::string>
	{
		static const stru_size_t dtsize = PTR_TYPE;
		static const bool isenum = false;
		static const bool isarray = false;
		static const bool isautodata = false;
		static const size_t code() { return typeid(std::string).hash_code(); }
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
		template<typename _tyCast>
		static bool get_val(void* pMember, _tyCast& outVal)
		{
			std::string& field = *((std::string*)pMember);
			outVal = field;
			return true;
		}
		template<typename _tyCast>
		static bool set_val(void* pMember, _tyCast& newVal)
		{
			std::string& field = *((std::string*)pMember);
			field = *(newVal._Cast<std::string>());
			return true;
		}
		template<typename _tyCast>
		static bool get_item(void* pMember, uint32 itemindex, _tyCast& outVal)
		{
			return false;
		}
		template<typename _tyCast>
		static bool set_item(void* pMember, uint32 itemindex, _tyCast& newVal)
		{
			return false;
		}
	};
	VECTOR_REG(std::string);
	LIST_REG(std::string);

	

#define AUTO_STRU_END(__CLASSNAME)  };REG_STRU(__CLASSNAME)  \
template<> struct type_helper<__CLASSNAME>: public AUTO::type_helper_autodata<__CLASSNAME>{};  \
VECTOR_REG(__CLASSNAME);  \
LIST_REG(__CLASSNAME);
}

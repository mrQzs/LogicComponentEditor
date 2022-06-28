
#pragma once

#include "platform.h"
#include "Singleton.h"
#include <deque>
#include <list>
#include <memory>  
#include <vector>  
#include <atomic>
#include <functional>  

namespace Base {

	template <typename OBJ>
	class CBuffPool : public Singleton<CBuffPool<OBJ>>
	{
		friend class Singleton<CBuffPool<OBJ>>;
		using ObjectDeque = std::deque<OBJ*>;
		using ObjectList = std::list<OBJ*>;

	protected:
		CBuffPool(void)
		{
			m_iMaxQueueSize = 10000; //队列大小可能修改调整
		}

		~CBuffPool(void)
		{
			{
				std::lock_guard<std::mutex> lock(m_mtxDeque);

				m_deque.clear();
			}


			std::lock_guard<std::mutex> lock1(m_mtxList);

			typename ObjectList::iterator itor = m_list.begin();
			while (itor != m_list.end())
			{
				if (NULL != *itor)
				{
					delete *itor;
				}
				itor = m_list.erase(itor);
			}

		}

	public:
		void SetMaxSize(int size)
		{
			m_iMaxQueueSize = size;
		}

		OBJ *CreateObject(OBJ* fromObj = nullptr)
		{
			OBJ* pObj = NULL;

			std::lock_guard<std::mutex> lock(m_mtxDeque);

			if (m_deque.size() == 0)
			{
				pObj = new OBJ;
				std::lock_guard<std::mutex> lock1(m_mtxList);
				m_list.push_back(pObj);
				m_iCreateNum++;
			}
			else
			{
				pObj = m_deque.front();
				m_deque.pop_front();
			}
			if (fromObj)
			{
				memcpy(pObj, fromObj, sizeof(OBJ));
			}
			else
				memset(pObj, 0, sizeof(OBJ));
			return pObj;
		}

		virtual int	Recycle(OBJ *pObj)
		{

			std::lock_guard<std::mutex> lock(m_mtxDeque);

			if ((int)m_deque.size() < m_iMaxQueueSize)
			{
				m_deque.push_back(pObj);
			}
			else
			{
				delete pObj;

				std::lock_guard<std::mutex> lock1(m_mtxList);
				m_iCreateNum--;
				typename ObjectList::iterator itor = m_list.begin();
				while (itor != m_list.end())
				{
					if (*itor == pObj)
					{
						itor = m_list.erase(itor);
						break;
					}
					itor++;
				}

			}

			return 0;
		}

		int GetDequeSize()
		{
			m_mtxDeque.lock();
			int size = m_deque.size();
			m_mtxDeque.unlock();
			return size;
		}

	protected:
		ObjectDeque			m_deque;
		std::mutex			m_mtxDeque;
		int					m_iMaxQueueSize;
		int					m_iCreateNum;

		ObjectList			m_list;
		std::mutex            m_mtxList;
	};

	template <typename OBJ>
	class CObjPool : public Singleton<CObjPool<OBJ>>
	{
		friend class Singleton<CObjPool<OBJ>>;
		using ObjectDeque = std::deque<OBJ*>;
		using ObjectList = std::list<OBJ*>;

	protected:
		CObjPool(void)
		{
			m_iMaxQueueSize = 10000; //队列大小可能修改调整
			m_iCreateNum = 0;
		}

		~CObjPool(void)
		{
			
			{
				std::lock_guard<std::mutex> lock(m_mtxDeque);

				m_deque.clear();
			}
				
				
				std::lock_guard<std::mutex> lock1(m_mtxList);

				typename ObjectList::iterator itor = m_list.begin();
				while (itor != m_list.end())
				{
					if (NULL != *itor)
					{
						delete *itor;
					}
					itor = m_list.erase(itor);
				}

		}

	public:
		void SetMaxSize(int size)
		{
			m_iMaxQueueSize = size;
		}

		OBJ *CreateObject()
		{
			OBJ* pObj = NULL;

			std::lock_guard<std::mutex> lock(m_mtxDeque);

			if (m_deque.size() == 0)
			{
				pObj = new OBJ;				

				std::lock_guard<std::mutex> lock1(m_mtxList);
				m_list.push_back(pObj);
				m_iCreateNum++;

			}
			else
			{
				pObj = m_deque.front();
				m_deque.pop_front();
			}
			pObj->doReset();
			return pObj;
		}

		virtual int	Recycle(OBJ *pObj)
		{

			std::lock_guard<std::mutex> lock(m_mtxDeque);

			if ((int)m_deque.size() < m_iMaxQueueSize)
			{
				m_deque.push_back(pObj);
			}
			else
			{
				delete pObj;			

				std::lock_guard<std::mutex> lock1(m_mtxList);
				m_iCreateNum--;
				typename ObjectList::iterator itor = m_list.begin();
				while (itor != m_list.end())
				{
					if (*itor == pObj)
					{
						itor = m_list.erase(itor);
						break;
					}
					itor++;
				}

			}

			return 0;
		}

		int GetCreateNum()
		{
			return m_iCreateNum;
		}

		int GetDequeSize()
		{
			m_mtxDeque.lock();
			int size = m_deque.size();
			m_mtxDeque.unlock();
			return size;
		}

	protected:
		ObjectDeque			m_deque;
		std::mutex			m_mtxDeque;
		int					m_iMaxQueueSize;
		int					m_iCreateNum;	

		ObjectList			m_list;
		std::mutex            m_mtxList;

	};
	template<class _imp>
	class Countor
	{
	public:
		Countor()
		{
			_Countor = { 1 };
		}
		virtual ~Countor() {};
		uint32 AddRef()
		{
			return _Countor.fetch_add(1);

		}
		virtual uint32 Release()
		{
			if (_Countor.fetch_sub(1) == 1)
			{
				delete (_imp*)this;
				return 0;
			}

			return _Countor;
		}	
	protected:
		std::atomic<uint32> _Countor;
	};
	
	template<class _poolobj>
	class CountorWithPool :public Countor<CountorWithPool<_poolobj>>
	{
		typedef Countor<CountorWithPool<_poolobj>> __parentclass;
		friend class CObjPool<_poolobj>;
	protected:
		CountorWithPool()
		{
		}
		virtual ~CountorWithPool() {};

		void doReset() {
			__parentclass::_Countor = { 1 };
			Reset();
		};
	public:
		
		
		virtual uint32 Release()
		{
			if (__parentclass::_Countor.fetch_sub(1) == 1)
			{
				CObjPool<_poolobj>::instance()->Recycle((_poolobj*)this);

			}

			return __parentclass::_Countor;

		}
		virtual void Reset()=0;

		static _poolobj* New()
		{
			return CObjPool<_poolobj>::instance()->CreateObject();
		}

	};

	template <class _T>
	class AutoBuff
	{
	public:
		typedef _T* _typename;
		AutoBuff(const _typename ptr)
		{
			_ptr = nullptr;
			if (ptr != nullptr)
			{
				_ptr = ptr;
			}
		}		
		~AutoBuff()
		{
			if (_ptr != nullptr)
			{
				_typename ptr = _ptr;
				_ptr = nullptr;
				CBuffPool<_T>::instance()->Recycle(_ptr);
			}
		}
		AutoBuff<_T>& operator=(const _typename ptr) {

			if (_ptr != nullptr)
			{
				_typename p = _ptr;
				_ptr = nullptr;
				CBuffPool<_T>::instance()->Recycle(p);
			}
			if (ptr != nullptr)
			{
				_ptr = ptr;
			}
			return *this;
		}
		_typename operator->() { return _ptr; }
		operator _typename() { return _ptr; }
		operator bool() { return _ptr ? true : false; }

	private:
		AutoBuff() = delete;
		AutoBuff(AutoBuff<_T>&) = delete;
		_typename _ptr;
	};
	
	template <class _T, bool isAddRef = false>
	class AutoObj
	{
	public:
		typedef _T* _typename;
		AutoObj(const _typename ptr)
		{
			_ptr = nullptr;
			if (ptr != nullptr)
			{
				if (isAddRef)
				{
					ptr->AddRef();
				}

				_ptr = ptr;
			}

		}
		~AutoObj()
		{
			if (_ptr != nullptr)
			{
				_typename ptr = _ptr;
				_ptr = nullptr;
				ptr->Release();
			}
		}
		bool isValid()
		{
			return _ptr ? true : false;
		}

		AutoObj<_T>& operator=(const _typename ptr) {

			if (_ptr != nullptr)
			{
				_typename ptr = _ptr;
				_ptr = nullptr;
				ptr->Release();
			}
			if (ptr != nullptr)
			{
				ptr->AddRef();
				_ptr = ptr;
			}
			return *this;
		}

		//对象==对象
		bool operator==(const AutoObj<_T> &obj) const
		{
			return (_ptr == obj._ptr);
		}
		//对象==指针
		bool operator==(const _typename ptr)const {
			return (_ptr == ptr);
		}
		//对象!=对象
		bool operator!=(const AutoObj<_T> &obj) const
		{
			return (_ptr != obj._ptr);
		}
		//对象!=指针
		bool operator!=(const _typename ptr)const {
			return (_ptr != ptr);
		}
		_typename operator->() { return _ptr; }
		operator _typename() { return _ptr; }
		operator bool() { return isValid(); }

	private:
		AutoObj() = delete;
		_typename _ptr;
	};
}

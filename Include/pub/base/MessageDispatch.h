#pragma once
#include "Singleton.h"
#include "ObjectPool.h"

namespace Base
{
	template<typename _obj>
	struct MsgData :public Base::CountorWithPool<MsgData<_obj>>
	{
		
		virtual void Reset()
		{
			memset(&_data, 0, sizeof(_obj));
		};

		void SetData(_obj& obj)
		{
			memcpy(&_data, &obj, sizeof(_obj));
		}

		_obj _data;
	};


	template<class msgObj>
	class CMessageDispatch :public Singleton<CMessageDispatch<msgObj>>
	{		
	public:
		typedef MsgData<msgObj>								_funcparam;
		typedef std::function<void(_funcparam* msg)>		_functype;
		typedef vector<_functype>							_funclist;
		bool RegMessage(std::function<void(MsgData<msgObj>* msg)> func)
		{
			AUTOLOCK(m_mtxlist);
			m_funclist.push_back(func);
			return true;
		}

		void DispatchMessage(msgObj& msgobj)
		{
			MsgData<msgObj>* msg = MsgData<msgObj>::New();
			msg->SetData(msgobj);
			m_tpDispatch.enqueue([this, msg]() {
				AUTOLOCK(m_mtxlist);
				for (size_t t = 0;t < m_funclist.size();t++)
				{
					m_funclist[t](msg);
				}

				msg->Release();
			});

		};



	private:
		Base::threadpools m_tpDispatch;
		std::mutex m_mtxlist;
		_funclist m_funclist;
	};


}

#define REG_MESSAGE(t,memfunc) Base::CMessageDispatch<t>::instance()->RegMessage([this](Base::CMessageDispatch<t>::_funcparam* msg){ \
		memfunc(msg); \
	})
#define POST_MESSAGE(t,obj) Base::CMessageDispatch<t>::instance()->DispatchMessage(obj)

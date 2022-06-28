/*
* 文件名称：Singleton.h
* 文件标识：
* 摘　　要：单件模版类
*/

#ifndef SINGLETON_H
#define SINGLETON_H

//////////////////////////////////////////////////////////////////////////
// class Singleton 
//////////////////////////////////////////////////////////////////////////
#include <mutex>

namespace Base
{
	class nocopyable
	{
	private:
		nocopyable(const nocopyable& x) = delete;
		nocopyable& operator=(const nocopyable&x) = delete;
	public:
		nocopyable() = default;
		~nocopyable() = default;
	};

	template <class T>
	class Singleton
	{
	public:
		static T* instance()
		{
			if (0 == s_instance)
			{
				s_mutex.lock();
				if (0 == s_instance)
				{
					s_instance = new T;
				}
				s_mutex.unlock();
			}

			return s_instance;
		}

		static void unInstance()
		{
			if (0 != s_instance)
			{
				s_mutex.lock();
				if (0 != s_instance)
				{
					delete s_instance;
					s_instance = 0;
				}
				s_mutex.unlock();
			}
		}

	protected:
		Singleton() {}
		virtual ~Singleton() {}

	private:
		Singleton(const Singleton<T> &); //不实现 
		Singleton<T>& operator= (const Singleton<T> &); //不实现

		static T* s_instance;
		static std::mutex s_mutex;
	};

	template <class T>
	T* Singleton<T>::s_instance = 0;

	template <class T>
	std::mutex Singleton<T>::s_mutex;

	//////////////////////////////////////////////////////////////////////////
	// class SingletonStatic
	//////////////////////////////////////////////////////////////////////////
	template <class T>
	class SingletonStatic
	{
	public:
		static T* instance()
		{
			return &s_instance;
		}

	protected:
		SingletonStatic() {}
		virtual ~SingletonStatic() {}

	private:
		SingletonStatic(const SingletonStatic<T> &); //不实现 
		SingletonStatic<T>& operator= (const SingletonStatic<T> &); //不实现

		static T s_instance;
	};

	template <class T>
	T SingletonStatic<T>::s_instance;

	//////////////////////////////////////////////////////////////////////////

};

#endif

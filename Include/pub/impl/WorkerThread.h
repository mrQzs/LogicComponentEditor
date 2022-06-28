#pragma once

#include "ThreadPool.h"
#include "platform.h"
#include "pubfuncs.h"
#include <map>

#define __USE_GLOBAL_WORKERS_LOCK__
#ifdef __USE_GLOBAL_WORKERS_LOCK__
static std::mutex	g_mtxWorkerThreads;
#endif

namespace yd
{
	// 工作线程基类
	class CWorkerThread
	{
	public:
		// 带参数构造函数
		CWorkerThread(uint64 ullDataId, void* pData) : m_ullDataId(ullDataId), m_pData(pData) {
		}
		// 虚拟析构函数
		virtual ~CWorkerThread() {
		}

	public:
		// 线程入口
		static int64 ThreadEntry(void* lpThis) {
			if (nullptr != lpThis) {
				return static_cast<CWorkerThread*>(lpThis)->DoThread();
			}
			else {
				return -1;
			}
		}

	public:
		// 线程处理函数
		virtual int64 DoThread() = 0;

	public:
		// 运行标志
		void SetRunning(bool bRunning) {
			m_bRunning = bRunning;
		}
		bool IsRunning() const {
			return m_bRunning;
		}

		// 退出标志
		void NotifyQuit(bool bQuit) {
			m_bNeedQuit = bQuit;
		}
		bool NeedQuit() const {
			return m_bNeedQuit;
		}

		// 数据
		uint64 GetDataId() const {
			return m_ullDataId;
		}
		void* GetData() {
			return m_pData;
		}

		// 线程id
		auto GetThreadId() {
			return std::this_thread::get_id();
		}

	private:
		uint64	m_ullDataId{ 0 };
		void* m_pData{ nullptr };
		bool	m_bNeedQuit{ false };
		bool	m_bRunning{ false };

	protected:
		const std::chrono::milliseconds	THREAD_INTERVAL = std::chrono::milliseconds(1);
	};

	// 工作线程池管理类
	class CWorkerThreadPool
	{
	public:
		CWorkerThreadPool() {
			m_mapId2WorkerThread.clear();
			m_mapId2WorkerResult.clear();
		}

	public:
		// 获取活跃任务数
		size_t GetActiveThreadNumber() const {
			return m_mapId2WorkerThread.size();
		}

		// 启动线程池
		bool StartPool(size_t nNumberOfhreads) {
			if (nNumberOfhreads <= 0) {
				return false;
			}
			if (!m_threadpool.start(nNumberOfhreads)) {
				return false;
			}
			m_nNumberOfhreads = nNumberOfhreads;
			return true;
		}

		// 停止线程池
		bool StopPool() {
			m_threadpool.stop();
			m_nNumberOfhreads = 0;
			return true;
		}

		// 线程池是否运行
		bool IsPoolRunning() const {
			return (m_nNumberOfhreads > 0 && !m_threadpool.is_stopped());
		}

		// 添加工作任务
		bool EnqueueWorker(uint64 ullWorkerId, CWorkerThread* pWorker) {
#ifdef __USE_GLOBAL_WORKERS_LOCK__
			AUTOLOCK(g_mtxWorkerThreads);
#endif
			if (m_nNumberOfhreads <= 0) {
				return false;
			}
			if (ullWorkerId <= 0) {
				return false;
			}
			auto iterWorker = m_mapId2WorkerThread.find(ullWorkerId);
			if (iterWorker != m_mapId2WorkerThread.end() && nullptr != iterWorker->second) {
				if (iterWorker->second->IsRunning()) {
					return true;
				}
				delete iterWorker->second;
				iterWorker->second = nullptr;
			}
			auto iterResult = m_mapId2WorkerResult.find(ullWorkerId);
			if (iterResult != m_mapId2WorkerResult.end()) {
				m_mapId2WorkerResult.erase(iterResult);
			}
			// 任务入列
			m_mapId2WorkerThread[ullWorkerId] = pWorker;
			m_mapId2WorkerResult[ullWorkerId] = m_threadpool.enqueue(CWorkerThread::ThreadEntry, pWorker);
			return true;
		}

		// 任一任务是否运行
		bool IsAnyWorkerRunning() {
			if (!this->IsPoolRunning()) {
				return false;
			}
			for (auto iter = m_mapId2WorkerThread.begin(); iter != m_mapId2WorkerThread.end(); iter++) {
				if (nullptr != iter->second && iter->second->IsRunning()) {
					return true;
				}
			}
			return false;
		}

		// 指定工作任务是否运行
		bool IsWorkerRunning(uint64 ullWorkerId) {
			auto iterWorker = m_mapId2WorkerThread.find(ullWorkerId);
			if (iterWorker != m_mapId2WorkerThread.end() && nullptr != iterWorker->second) {
				if (iterWorker->second->IsRunning()) {
					return true;
				}
			}
			return false;
		}

		// 获取指定工作任务结果
		bool GetWorkerResult(uint64 ullWorkerId, int64& llResult) {
			if (this->IsWorkerRunning(ullWorkerId)) {
				return false;
			}
#ifdef __USE_GLOBAL_WORKERS_LOCK__
			AUTOLOCK(g_mtxWorkerThreads);
#endif
			auto iterWorker = m_mapId2WorkerThread.find(ullWorkerId);
			if (iterWorker != m_mapId2WorkerThread.end() && nullptr != iterWorker->second) {
				delete iterWorker->second;
				iterWorker->second = nullptr;
				m_mapId2WorkerThread.erase(iterWorker);
				auto iterResult = m_mapId2WorkerResult.find(ullWorkerId);
				if (iterResult != m_mapId2WorkerResult.end()) {
					llResult = iterResult->second.get();
					m_mapId2WorkerResult.erase(iterResult);
				}
				return true;
			}
			return false;
		}

		// 获取所有工作任务结果
		bool GetWorkersResult(std::map<uint64, int64>& mapId2ThreadResult) {
			mapId2ThreadResult.clear();
			if (this->IsAnyWorkerRunning()) {
				return false;
			}
#ifdef __USE_GLOBAL_WORKERS_LOCK__
			AUTOLOCK(g_mtxWorkerThreads);
#endif
			for (auto iter = m_mapId2WorkerThread.begin(); iter != m_mapId2WorkerThread.end(); iter++) {
				if (nullptr != iter->second) {
					delete iter->second;
					iter->second = nullptr;
				}
			}
			m_mapId2WorkerThread.clear();
			for (auto iter = m_mapId2WorkerResult.begin(); iter != m_mapId2WorkerResult.end(); iter++) {
				mapId2ThreadResult[iter->first] = iter->second.get();
			}
			m_mapId2WorkerResult.clear();

			return true;
		}

		// 通知指定任务退出
		bool NotifyWorkerQuit(uint64 ullWorkerId, bool bNeedQuit) {
#ifdef __USE_GLOBAL_WORKERS_LOCK__
			AUTOLOCK(g_mtxWorkerThreads);
#endif
			auto iterWorker = m_mapId2WorkerThread.find(ullWorkerId);
			if (iterWorker == m_mapId2WorkerThread.end() || nullptr == iterWorker->second) {
				return false;
			}
			iterWorker->second->NotifyQuit(bNeedQuit);
			return true;
		}

		// 通知所有工作任务退出
		bool NotifyWorkersQuit(bool bNeedQuit) {
#ifdef __USE_GLOBAL_WORKERS_LOCK__
			AUTOLOCK(g_mtxWorkerThreads);
#endif
			for (auto iter = m_mapId2WorkerThread.begin(); iter != m_mapId2WorkerThread.end(); iter++) {
				if (nullptr != iter->second) {
					iter->second->NotifyQuit(bNeedQuit);
				}
			}
			return true;
		}

	private:
		size_t									m_nNumberOfhreads{ 0 };
		std::map<uint64, CWorkerThread*>		m_mapId2WorkerThread;
		std::map<uint64, std::future<int64>>	m_mapId2WorkerResult;
		Base::ThreadPool						m_threadpool;
	};
}

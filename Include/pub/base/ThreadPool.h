#pragma once

#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>

namespace Base {
	class ThreadPool {
	public:
		// 构造函数，可设置启动的线程数量
		ThreadPool() : stoped(true)
		{

		}

		// 添加一个任务到线程池中执行
		template<class F, class... Args>
		auto enqueue(F&& f, Args&&... args)
			->std::future<typename std::result_of<F(Args...)>::type>;

		// 停止所有线程
		~ThreadPool()
		{
			stop();
		}

		bool start(size_t threads)
		{
			{
				std::unique_lock<std::mutex> lock(queue_mutex);
				if (stoped == false)
				{
					return false;
				}
				stoped = false;
			}
			for (size_t i = 0; i < threads; ++i)
				workers.emplace_back(
					[this]
			{
				for (;;)
				{
					std::function<void()> task;

					{
						std::unique_lock<std::mutex> lock(this->queue_mutex);
						this->condition.wait(lock,
							[this] { return this->stoped || !this->tasks.empty(); });
						if (this->stoped && this->tasks.empty())
							return;
						task = std::move(this->tasks.front());
						this->tasks.pop();
					}

					task();
				}
			}
			);

			return true;
		}

		void stop()
		{
			{
				std::unique_lock<std::mutex> lock(queue_mutex);
				if (stoped)
				{
					return;
				}
				stoped = true;
			}
			condition.notify_all();
			for (std::thread &worker : workers)
				worker.join();
			workers.clear();
		}

		// added by steven,20211025
		// 是否停止
		bool is_stopped() const {
			return stoped;
		}
		// end of added,20211025

	private:
		// 线程列表
		std::vector< std::thread > workers;
		//任务队列
		std::queue< std::function<void()> > tasks;

		// 同步信号
		std::mutex queue_mutex;
		std::condition_variable condition;
		bool stoped;
	};

	template<class F, class... Args>
	auto ThreadPool::enqueue(F&& f, Args&&... args)
		->std::future<typename std::result_of<F(Args...)>::type>
	{
		using return_type = typename std::result_of<F(Args...)>::type;

		auto task = std::make_shared< std::packaged_task<return_type()> >(
			std::bind(std::forward<F>(f), std::forward<Args>(args)...)
			);

		std::future<return_type> res = task->get_future();
		{
			std::unique_lock<std::mutex> lock(queue_mutex);

			//线程池停止后，不允许再执行任务
			if (stoped)
				throw std::runtime_error("enqueue on stopped ThreadPool");

			tasks.emplace([task]() { (*task)(); });
		}
		condition.notify_one();
		return res;
	}



#define  MAX_THREAD_NUM 256

	//线程池,可以提交变参函数或拉姆达表达式的匿名函数执行,可以获取执行返回值
	//不支持类成员函数, 支持类静态成员函数或全局函数,Opteron()函数等
	class threadpools
	{
		using Task = std::function<void()>;
		// 线程池
		std::vector<std::thread> pool;
		// 任务队列
		std::queue<Task> tasks;
		// 同步
		std::mutex m_lock;
		// 条件阻塞
		std::condition_variable cv_task;
		// 是否关闭提交
		std::atomic<bool> stoped;
		//空闲线程数量
		std::atomic<int>  idlThrNum;

	public:
		inline threadpools(unsigned short size = 1) :stoped{ false }
		{
			idlThrNum = size < 1 ? 1 : size;
			for (size = 0; size < idlThrNum; ++size)
			{   //初始化线程数量
				pool.emplace_back(
					[this]
				{ // 工作线程函数
					while (!this->stoped)
					{
						std::function<void()> task;
						{   // 获取一个待执行的 task
							// unique_lock 相比 lock_guard 的好处是：可以随时 unlock() 和 lock()
							std::unique_lock<std::mutex> lock{ this->m_lock };
							this->cv_task.wait(lock,
								[this] {
								return this->stoped.load() || !this->tasks.empty();
							}
							); // wait 直到有 task
							if (this->stoped && this->tasks.empty())
								return;
							task = std::move(this->tasks.front()); // 取一个 task
							this->tasks.pop();
						}
						idlThrNum--;
						task();
						idlThrNum++;
					}
				}
				);
			}
		}
		inline ~threadpools()
		{
			stoped.store(true);
			cv_task.notify_all(); // 唤醒所有线程执行
			for (std::thread& thread : pool) {
				//thread.detach(); // 让线程“自生自灭”
				if (thread.joinable())
					thread.join(); // 等待任务结束， 前提：线程一定会执行完
			}
		}

	public:
		// 提交一个任务
		// 调用.get()获取返回值会等待任务执行完,获取返回值
		// 有两种方法可以实现调用类成员，
		// 一种是使用   bind： .commit(std::bind(&Dog::sayHello, &dog));
		// 一种是用 mem_fn： .commit(std::mem_fn(&Dog::sayHello), &dog)
		template<class F, class... Args>
		auto enqueue(F&& f, Args&&... args) ->std::future<decltype(f(args...))>
		{
			if (stoped.load())    // stop == true ??
				throw std::runtime_error("commit on ThreadPool is stopped.");

			using RetType = decltype(f(args...)); // typename std::result_of<F(Args...)>::type, 函数 f 的返回值类型
			auto task = std::make_shared<std::packaged_task<RetType()> >(
				std::bind(std::forward<F>(f), std::forward<Args>(args)...)
				);    // wtf !
			std::future<RetType> future = task->get_future();
			{    // 添加任务到队列
				 //对当前块的语句加锁  lock_guard 是 mutex 的 stack 封装类，构造的时候 lock()，析构的时候 unlock()
				std::lock_guard<std::mutex> lock{ m_lock };
				tasks.emplace(
					[task]()
				{ // push(Task{...})
					(*task)();
				}
				);
			}
			cv_task.notify_one(); // 唤醒一个线程执行

			return future;
		}

		//空闲线程数量
		int idlCount() { return idlThrNum; }

	};
}



//example:
/*
int main()
{

	ThreadPool pool(4);
	std::vector< std::future<int> > results;

	for (int i = 0; i < 8; ++i) {
		results.emplace_back(
			pool.enqueue([i] {
			std::cout << "hello " << i << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(1));
			std::cout << "world " << i << std::endl;
			return i*i;
		})
			);
	}

	for (auto && result : results)
		std::cout << result.get() << ' ';
	std::cout << std::endl;

	return 0;
}

//创建四个线程的线程池
ThreadPool pool(4);

// 执行一个任务并保存 future
auto result = pool.enqueue([](int answer) { return answer; }, 42);

//从future获取执行的结果
std::cout << result.get() << std::endl;

*/

#pragma once

#include <deque>
#include <vector>

#include "condition_variable.h"
#include "mutex.h"

class Task;
class Thread;

class ThreadPool {
	public:
		ThreadPool();
		explicit ThreadPool(size_t pool_size);
		~ThreadPool();

		void Initialze();
		void Destroy();
		void Schedule(Task* task);

	private:
		friend class Thread;
		void Execute();

		size_t pool_size_;
		volatile bool stop_requested_;
		std::vector<Thread*> workers_;
		std::deque<Task*> task_queue_;
		Mutex task_queue_mutex_;
		ConditionVariable task_queue_condition_variable_;
};


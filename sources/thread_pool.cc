#include "thread_pool.h"

#include <iostream>
#include <sstream>
#include <string>

#include "condition_variable.h"
#include "mutex.h"
#include "task.h"
#include "thread.h"

using namespace std;

namespace {
	const int kDefaultPoolSize = 10;
}  // namespace

ThreadPool::ThreadPool()
	: pool_size_(kDefaultPoolSize), stop_requested_(true) { }

ThreadPool::ThreadPool(size_t pool_size)
	: pool_size_(pool_size), stop_requested_(true) { }

ThreadPool::~ThreadPool() { Destroy(); }

void ThreadPool::Initialze() {
	for (size_t count = 0; count < pool_size_; ++count) {
		stringstream ss;
		ss << "worker_" << count;
		Thread* worker = new Thread(*this, ss.str());
		worker->Start();
		workers_.push_back(worker);
	}

	stop_requested_ = false;
}

void ThreadPool::Destroy() {
	stop_requested_ = true;
	task_queue_condition_variable_.Broadcast();
	for (auto worker: workers_) {
		worker->Stop();
	}
}

void ThreadPool::Schedule(Task* task) {
	if (stop_requested_) {
		Initialze();
	}

	task_queue_mutex_.Lock();
	task_queue_.push_back(task);
	task_queue_condition_variable_.SignalOne();
	task_queue_mutex_.Unlock();
}

void ThreadPool::Execute() {
	while (true) {

		task_queue_mutex_.Lock();
		while (!stop_requested_ && !task_queue_.empty()) {
			task_queue_condition_variable_.Wait(task_queue_mutex_);
		}

		if (stop_requested_) {
			task_queue_mutex_.Unlock();
			return;
		}

		Task* t = task_queue_.front();
		task_queue_.pop_front();
		task_queue_mutex_.Unlock();

		t->Execute();
	}
}


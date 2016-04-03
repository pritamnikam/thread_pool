#pragma once

#include <pthread.h>
#include <string>

using namespace std;

class ThreadPool;
class Thread {
	public:
		Thread(ThreadPool& pool, string thread_name);
		virtual ~Thread();

		void Start();
		void Stop();

		virtual void Run();

	private:
		static void* ThreadStart(void* obj);

		ThreadPool& pool_;
		string thread_name_;
		pthread_t tid_;
};


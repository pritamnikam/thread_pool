#pragma once

#include <pthread.h>

class Mutex {
	public:
		Mutex();
		~Mutex();

		void Lock();
		void Unlock();
	private:
		friend class ConditionVariable;
		pthread_mutex_t lock_;
};



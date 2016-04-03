#pragma once

#include <pthread.h>

class Mutex;
class ConditionVariable {
	public:
		ConditionVariable();
		~ConditionVariable();

		void Wait(const Mutex& mutex);
		void SignalOne();
		void Broadcast();

	private:
		pthread_cond_t condition_variable_;
};


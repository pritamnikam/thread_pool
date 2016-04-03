#include "condition_variable.h"

#include "mutex.h"

ConditionVariable::ConditionVariable() {
        condition_variable_ = PTHREAD_COND_INITIALIZER;
	pthread_cond_init(&condition_variable_, nullptr);
}

ConditionVariable::~ConditionVariable() {
	pthread_cond_destroy(&condition_variable_);
}

void ConditionVariable::Wait(const Mutex& mutex) {
	pthread_cond_wait(&condition_variable_, &mutex.lock_);
}

void ConditionVariable::SignalOne() {
	pthread_cond_signal(&condition_variable_);
}

void ConditionVariable::Broadcast() {
	pthread_cond_broadcast(&condition_variable_);
}


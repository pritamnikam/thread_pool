#include "mutex.h"

Mutex::Mutex() {
        lock_ = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_init(&lock_, nullptr);
}

Mutex::~Mutex() {
	pthread_mutex_destroy(&lock_);
}

void Mutex::Lock() {
	pthread_mutex_lock(&lock_);
}

void Mutex::Unlock() {
	pthread_mutex_unlock(&lock_);
}


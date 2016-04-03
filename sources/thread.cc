#include "thread.h"

#include <string>
#include "thread_pool.h"

using namespace std;

Thread::Thread(ThreadPool& pool, string thread_name) : pool_(pool), thread_name_(thread_name) {
}

Thread::~Thread() {
}

void Thread::Start() {
	pthread_create(&tid_, nullptr, ThreadStart, (void*) this);
	pthread_setname_np(tid_, thread_name_.c_str());
}

void Thread::Stop() {
}

void Thread::Run() {
	pool_.Execute();
}

void* Thread::ThreadStart(void* obj) {
	Thread* this_thread = reinterpret_cast<Thread*>(obj);
	this_thread->Run();
	return nullptr;
}


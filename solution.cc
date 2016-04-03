#include <iostream>

#include "thread_pool.h"
#include "task.h"

using namespace std;

int main() {
  // M = 10 tasks
  // N = 3 threads
  ThreadPool t(3);
  for (int m = 0; m <10; ++m) {
    t.Schedule(new Task);
  }
  return 0;
}

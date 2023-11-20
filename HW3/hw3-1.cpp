#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

int counter = 0;

void countt(int index) { 
  static mutex io_mutex;
  int num = 1000000;
  while (num--) {}
  while (true){ // spinlock
    lock_guard<mutex> lock(io_mutex);
    if (index == counter){
      cout << "I'm thread " << index << ", local count: 1000000\n";
      counter++;
      break;
    }
  }
}
 
int main(void) {
  thread t[100];

  for (int i = 0; i < 100; i++)
    t[i] = thread(countt, i);

  for (int i = 0; i < 100; i++)
    t[i].join();
}

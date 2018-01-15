#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

static const int num_threads = 10;

std::mutex mtx;

//This function will be called from a thread

void call_from_thread(int tid) {
 std::chrono::milliseconds ms{500};
  mtx.lock();
  std::cout << "Launched by thread part 1:" << tid << std::endl;
  mtx.unlock();
  std::this_thread::sleep_for(ms);
  mtx.lock();
  std::cout << "Launched by thread part 2:" << tid << std::endl;
  mtx.unlock();
}

int main() {
    std::thread t[num_threads];

    //Launch a group of threads
    for (int i = 0; i < num_threads; ++i) {
        t[i] = std::thread(call_from_thread, i);
    }

    //  mtx.lock();
    std::cout << "Launched from the main\n";
    //  mtx.unlock();

    //Join the threads with the main thread
    for (int i = 0; i < num_threads; ++i) {
        t[i].join();
    }

    return 0;
}

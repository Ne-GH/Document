#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>


std::mutex mutex;
std::condition_variable cv;
bool flag = false;

void print_id(int id) {
    std::unique_lock lock(mutex);
    // 参数1 : 锁
    // 参数2 : 返回值为true,则不阻塞。 返回值为false,则解锁mutex并阻塞（wait）
    // 没有参数2时，默认返回false
    cv.wait(lock, [id]{ return flag == true; });
    std::cout << "id: " << id << std::endl;
}

void go() {
    std::lock_guard lock(mutex);
    flag = true;
    cv.notify_all();    // 唤醒所有线程
    // cv.notify_one();    // 只唤醒一个
}


int main () {
    std::thread thread_arr[10];
    for (int i = 0; i < 10; i++) {
        thread_arr[i] = std::thread(print_id, i);
    }
    std::cout << "thread is ready ... " << std::endl;

    go();

    for (auto &thread : thread_arr) {
        thread.join();
    }



    return 0;
}

#include <iostream>
#include <mutex>
#include <thread>


std::mutex mutex;
void func_adopt_lock() {
    mutex.lock();
    // do ...

    // 方案1 :
    // mutex.unlock();
    // 如果mutex没有调用unlock，则上锁失败，一直阻塞
    // std::lock_guard lock(mutex);

    // 方案2 : 参数2使用adopt_lock
    // 使用该构造函数的时候，不对传入的mutex上锁,因此不会阻塞在这里
    std::lock_guard lock(mutex,std::adopt_lock);

    // 输出当前CPU支持的线程数量
    std::cout << std::thread::hardware_concurrency() << std::endl;


    // do ...
}

// lock_guard实现
template <typename Mutex>
struct lock_guard {
    explicit lock_guard(Mutex& mutex) : mutex_(mutex) {
        mutex_.lock();
    }
    lock_guard(Mutex& mutex, std::adopt_lock_t) : mutex_(mutex) { }
    ~lock_guard() {
        mutex_.unlock();
    }
    lock_guard(const lock_guard&) = delete;
    lock_guard& operator=(const lock_guard&) = delete;
private:
    Mutex &mutex_;

};



void func_lock_guard() {
    ::lock_guard lock(mutex);
}


void func_lock_unique() {

    // do ...
    // 方案1
    {
        std::lock_guard lock(mutex);
    }
    // 方案2
    // 有参数2时不对mutex上锁
    // mutex.lock();
    // std::unique_lock lock2(mutex, std::adopt_lock);
    std::unique_lock lock(mutex);
    lock.unlock();

    // do ...

}

int main () {

    func_adopt_lock();
    func_lock_guard();

    return 0;
}

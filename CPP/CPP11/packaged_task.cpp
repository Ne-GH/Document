#include <iostream>
#include <future>
#include <thread>

int add(int n) {
    if (n == 0 || n == 1)
        return n;
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    std::cout << n << std::endl;
    return add(n - 1) + n;
}

int main () {

    // packaged_task 用于 包装任意可调用目标，使得能异步调用它，其返回值或所抛出的异常能被存储于能通过std::future对象访问的共享状态中
    std::packaged_task<int(int)> task([] (const int n){
        std::cout << std::this_thread::get_id() << std::endl;
        return add(n);
    });
    std::future<int> ret = task.get_future();
    task(10);

    std::cout << ret.get() << std::endl;
    // packaged_task 默认没有创建新线程
    std::cout << std::this_thread::get_id() << std::endl;

    std::packaged_task<int(int)> task_thread([] (const int n){
        std::cout << std::this_thread::get_id() << std::endl;
        return add(n);
    });
    std::future<int> ret_thread = task_thread.get_future();
    // 用此方法可将任务移入线程,并获取返回值
    std::thread thread(std::move(task_thread),10);
    thread.join();
    std::cout << ret_thread.get() << std::endl;
    return 0;
}

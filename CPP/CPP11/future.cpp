#include <iostream>
#include <future>

int add(int n) {
    if (n == 0 || n == 1)
        return n;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    return add(n - 1) + n;
}

int main () {


    // future 表示“将来”, 配合 std::async创建一个异步任务
    // 最常用的成员函数是get/wait
    // get 调用的时候，要求线程必须执行完毕，并拿到返回值结果, 如果线程没有执行完，会一直等待，类似join
    // wait用于等待线程返回，本身不返回结果，类似于join
    std::future<int> ret = std::async(add, 10);
    std::future_status status;

    do {

        // wait_for 会阻塞当前线程
        status = ret.wait_for(std::chrono::milliseconds(1000));

        // 没有创建线程，且未调用get时为此状态
        if (status == std::future_status::deferred) {
            std::cout << "deferred" << std::endl; }
        else if (status == std::future_status::timeout) {
            std::cout << "timeout" << std::endl;
        }
        else if (status == std::future_status::ready) {
            std::cout << "ready" << std::endl;
        }
        std::cout << "while" << std::endl;
    } while (status != std::future_status::ready);

    ret.wait(); // 可省略
    std::cout << ret.get() << std::endl;

    return 0;
}

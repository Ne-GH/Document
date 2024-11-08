#include <iostream>
#include <future>

constexpr int add(int n) {
    if (n == 0 || n == 1)
        return n;
    return add(n - 1) + n;
}

// thread 和 async 的区别
// thread 一定会创建线程，如果资源不足会产生错误
// async 不一定会创建线程，可能不创建线程，且不会因为资源不足产生错误
int main () {


    // 参数 std::launch::deferred, 表示延迟调用, 即不会创建线程, 在调用get/wait时开始执行
    // 参数 std::launch::async(默认), 强制创建线程并运行, 线程创建失败时会产生错误（崩溃）
    // 参数 async | async ，表示是否创建线程由系统决定，如果资源紧张则不创建
    std::future<int> ret = std::async(add, 10);
    ret.wait(); // wait可省略
    std::cout << ret.get() << std::endl;




    return 0;
}

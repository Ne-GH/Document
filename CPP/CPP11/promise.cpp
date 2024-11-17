#include <future>
#include <thread>
#include <iostream>

void func(std::promise<int> &pr, int num) {
    int ret = 0;
    for (int i = 0; i < num; i++)
        ret += i;

    pr.set_value(ret);
}


int main () {

    std::promise<int> pr;
    std::thread thread(func,std::ref(pr),10);
    thread.join();

    std::future<int> future = pr.get_future();
    auto result = future.get();
    std::cout << result << std::endl;


    return 0;
}

#include <iostream>
#include <future>
#include <atomic>

int main () {

    int flag{};
    // 对于普通变量来说，flag += 1分为以下三个步骤
    // movl flag, %eax
    // incl %eax
    // movl %eax, flag
    flag += 1;

    // 对于atomic类型来说，这些操作是原子的，不可分割的
    std::atomic<int> flag_atomic{};
    flag_atomic += 1;





    return 0;
}

#include <cassert>

// consteval C++20
// 仅能修饰函数，明确限制函数只能在编译阶段执行
consteval auto add(auto l,auto r) -> decltype(l + r) {
    return l + r;
}

int main() {

    // const
    const int const_val = 10;

    // constexpr C++11
    // 修饰表达式（变量和函数），在编译期完成计算
    constexpr int constexpr_val1 = 10;
    constexpr int consteval_val2 = add(1,2);
    assert(consteval_val2 == 3);


    // constinit C++20
    // 修饰static 和 thread-local变量
    constinit static int constinit_val = add(1,2);
    assert(constinit_val == 3);




    return 0;
}

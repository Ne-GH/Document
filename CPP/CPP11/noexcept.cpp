#include <iostream>

// C++11 noexcept
// 说明符
// 运算符

// 仅异常不同不能被重载
// C++17 前异常说明符不是函数类型的一部分，C++17之后是函数类型的一部分

// 说明符，保证func不抛出异常
void func() noexcept {
    std::cout << "func" << std::endl;
}

// noexcept 和 noexcept(true等价)
void func2() noexcept(true) {
    std::cout << "func2" << std::endl;
}


// 不写noexcept 或者 写 noexcept(false) 均表示可能抛出异常
void func3() noexcept(false) {
    std::cout << "func3" << std::endl;
}

// C++17 弃用，C++20 移除
// 和noexcept(true)相同
void func4() throw() {
    std::cout << "func4" << std::endl;
}

// noexcept(func4)  =>  true
// noexcept(true)
// 这样可以使异常说明符与另一个函数相同
void func5() noexcept(noexcept(func4)) {
    std::cout << "func5" << std::endl;
}




int main () {

    // noexcept 运算符用来检测函数是否会抛出异常
    // noexcept是不求值表达式，因此不会真正调用函数
    std::cout << noexcept(func()) << std::endl;
    std::cout << noexcept(func2()) << std::endl;
    std::cout << noexcept(func3()) << std::endl;


    return 0;
}

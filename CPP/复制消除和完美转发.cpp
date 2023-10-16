#include <iostream>

struct X {
    X() {
        std::cout << "默认构造函数" << std::endl;
    }
    // 用移动构造函数比拷贝构造函数开销要小
    X(X && ) {
        std::cout << "移动构造函数" << std::endl;
    }
    X(const X &) {
        std::cout << "拷贝构造函数" << std::endl;
    }
    auto operator = (const X && x) {
        std::cout << "移动赋值运算符" << std::endl;
    }

};

X fun() {
    X x;
    return x;
}

void f1(X &&);
void f2(X &&);
void f3(X &&);
void f4(X &&);

void f(X && x) {
    std::cout << &x << std::endl;
    f1(std::forward<X>(std::move(x)));
}
void f1(X && x) {
    std::cout << &x << std::endl;
    f2(std::forward<X>(std::move(x)));

}
void f2(X && x) {
    std::cout << &x << std::endl;
    f3(std::forward<X>(std::move(x)));
}
void f3(X && x) {
    std::cout << &x << std::endl;
    f4(std::forward<X>(std::move(x)));
}
void f4(X && x) {
    std::cout << &x << std::endl;
}

int main() {

    X x;// 左值
    // std::move返回亡值，右值分为纯右值和亡值，都可以调用移动构造函数或者移动赋值运算符
    X x2 = std::move(x);
    const X& x2_ = x; // const T& 可以绑定右值
    X();
    X x3 = X(); // 有赋值消除，因此不会构造两个对象，在c++17之前是普遍存在的，c++17之后是强制的

    // 复制消除,只在fun中生成x时调用一次默认构造函数
    X x4 = fun();
    x4 = fun(); // 此处不会复制消除，而是调用了一次移动赋值运算符
    x4 = std::move(fun());// 同样不会进行复制消除

    std::cout << "forward:" << std::endl;
    f(std::move(x4));

    return 0;
}

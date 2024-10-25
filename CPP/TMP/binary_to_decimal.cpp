#include <iostream>

// 传入的是一个二进制形式的10进制数字,例如，1101,该int数字被认为是二进制形式的
template <int N>
struct Binary {
    static constexpr int value = Binary<N/10>::value * 2 + N % 10;
};
template<>
struct Binary<0> {
    static constexpr int value = 0;
};

int main() {

    std::cout << Binary<0>::value << std::endl;
    std::cout << Binary<1>::value << std::endl;
    std::cout << Binary<10>::value << std::endl;
    std::cout << Binary<11>::value << std::endl;
    std::cout << Binary<100>::value << std::endl;
    std::cout << Binary<101>::value << std::endl;




    return 0;
}

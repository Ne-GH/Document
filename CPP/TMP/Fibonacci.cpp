#include <iostream>

template <size_t N>
struct Fibonacci {
    inline static int value = Fibonacci<N - 1>::value + Fibonacci<N - 2>::value;
};

template <>
struct Fibonacci<0> {
    enum { value = 1 };
};
template <>
struct Fibonacci<1> {
    enum { value = 1 };
};

int main () {


    std::cout << Fibonacci<0>::value << std::endl;
    std::cout << Fibonacci<1>::value << std::endl;
    std::cout << Fibonacci<2>::value << std::endl;
    std::cout << Fibonacci<3>::value << std::endl;
    std::cout << Fibonacci<4>::value << std::endl;
    std::cout << Fibonacci<5>::value << std::endl;
    std::cout << Fibonacci<6>::value << std::endl;
    std::cout << Fibonacci<7>::value << std::endl;


    return 0;
}

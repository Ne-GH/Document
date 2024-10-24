#include <cstddef>
#include <iostream>
#include <iterator>

template <size_t N>
struct Factorial {
    inline static int value = Factorial<N - 1>::value * N;
};
template <>
struct Factorial<0> {
    inline static int value = 1;

};

int main () {

    std::cout << Factorial<0>::value << std::endl;
    std::cout << Factorial<1>::value << std::endl;
    std::cout << Factorial<2>::value << std::endl;
    std::cout << Factorial<3>::value << std::endl;
    std::cout << Factorial<4>::value << std::endl;


}

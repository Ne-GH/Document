#include <iostream>
#include <type_traits>

int main () {

    int val{};
    std::cout << std::is_void<decltype(val)>::value << std::endl;
    std::cout << std::is_void_v<decltype(val)> << std::endl;

    std::cout << std::is_integral_v<decltype(val)> << std::endl;

    std::cout << std::is_pointer_v<decltype(val)> << std::endl;

    std::cout << std::is_reference_v<decltype(val)> << std::endl;

    typename std::remove_reference<decltype(val)>::type ref{};

    // 更多请参见cppreference中type_traits中内容




    return 0;
}

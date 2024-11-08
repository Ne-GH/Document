#include <iostream>
#include <string>


int main () {

    // 配合正则会很方便
    // 考虑正则表达式： \w{2}\s*\d{5}
    //              \\w{2}\\s*\\d{5}
    // 不使用原始字符串字面量时不够直观
    std::string str = R"(\\\\"\")";
    std::cout << str << std::endl;


    return 0;
}


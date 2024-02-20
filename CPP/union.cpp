#include <iostream>

// 全局的匿名union必须为static
static union {
    char C;
    int I;
    double D;
};

// union可以拥有构造函数和析构函数，但是不能作为基类，不能有虚函数，不能有引用类型的成员，不能有protected 成员或 private 成员
union Union {
    Union() {
        std::cout << "Union" << std::endl;
    }
    ~Union() {
        std::cout << "~Union" << std::endl;
    }

    int INT;
    double Double;
};
int main() {

    Union U;
    U.INT = 10;
    std::cout << U.INT << std::endl;

    union {
        char C;
        int I;
        double D;
    };


    // 全局匿名union中的I
    ::I = 10;
    std::cout << ::I << std::endl;

    // 当前作用域中匿名union中的I
    I = 20;
    std::cout << I << std::endl;

    return 0;
}

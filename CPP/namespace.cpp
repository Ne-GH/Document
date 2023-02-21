#include <iostream>
#include <iterator>

// 定义命名空间
namespace My_std {
    void Testfun();
    namespace Myname1 {
        int T1 = 10;
    }
    namespace Myname2 {
        int T1 = 20;
    }
    inline namespace Myname3 {
        int T1 = 30;
    }
    inline namespace Myname4 {
        // 如果内联中出现重复定义,那么error
        // int T1 = 40;
    }
}
void My_std::Testfun(){
    std::cout << "My_std::Testfun" << std::endl;
    return;
}
void Testfun(){
    std::cout << "::Testfun" << std::endl;
}
int main(){

    My_std::Testfun();
    ::Testfun();
    std::cout << My_std::Myname1::T1 << std::endl;
    std::cout << My_std::T1 << std::endl;


    // 定义命名空间的别名
    namespace My = My_std;
    std::cout << My::T1 << std::endl;
    namespace My1 = My_std::Myname1;
    std::cout << My1::T1 << std::endl;
    return 0;
}

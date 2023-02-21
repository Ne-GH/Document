#include <iostream>

using namespace std;

// 嵌套命名空间
namespace A::B::C {
    int ABCval;
}
//等价于\
    namespace A{    \
        namespace B{\
            namespace C{\
                int ABCval;\
            }\
        }\
    }


// 异常声明作为类型的一部分
// exfun 和noexfun的类型不同,将一个可能抛出异常的指针赋给一个保证不抛出异常的函数指针,调用时可能会抛出异常
// 但是重载签名完全相同只有异常声明不同的函数是不允许的,就像不允许重载只有返回值不同的函数一样
// 其他规则不受影响,例如:依旧不能忽略基类中的noexcept声明
void exfun(){}
void noexfun()noexcept{}
// void (*pfun)()noexcept = exfun;  C++17 起ERROR
void (*pfun)() = noexfun;           // 依旧有效



int main(){

    // 新的求值顺序
    // e1[e2],e1.e2,e1.*e2,e1->*e2,e1<<e2,e1>>e2
    // e1保证在e2之前求值
    // 所有的赋值运算 e2 = e1 ,e2 += e1 ,e2 *= e1 ...
    // 右侧的e1保证在左侧的e2之前求值
    // new Type(e)
    // 保证内存分配发生在e求值之前,新的对象的初始化操作保证在第一次使用该对象之前完成
    //
    // 但函数调用中的参数计算顺序依然未定义





    // 更宽松的用整形初始化枚举值的规则
    // 指明底层类型的无作用域枚举类型
    enum Enum:char{};
    Enum e1{10};            // C++17 OK
    // 默认底层类型的有作用域枚举类型
    enum class Enumm {mon,tue,wed};
    Enumm e2{0};            // C++17 ok
    // 指明底层类型的有作用域枚举类型
    enum class Enummm:char{mon,tue,wed};
    Enummm e3{0};           // C++17 ok
    // 无明确底层类型的无作用域枚举类型
    enum UnEnum {mon,tue,wed};
    // UnEnum ue{0};        // C++17 Error





    // 修正auto
    // C++17 之前 auto vals{1} 或 auto vals={1} ,vals都是一个std::initializer_list<>
    // 修正后,直接初始化{} 和 拷贝初始化={} 有了显著的区别
    auto autoval{1};            // int
    // auto autovals{1,2,3}     // ERROR
    auto autoval1 = {1};        // std::initializer_list<>
    auto autoval2 = {1,2,3};    // std::initializer_list<>





    // 直接支持16进制浮点数字面量
    // 有效数字/尾数用16进制,以2为底的指数用10进制
    double doubleval = 0x1.4p+5;// 1.4(16)==1.25(10) ( 4/16 == 0.25/10,所以1.4(16)==1.25(10)) 即 1.25*2^5
    cout << doubleval << endl;




    // utf8 字符字面量
    auto c = u8'c';     // utf8编码的字符c,C++17中是char ,C++20中可能变为char8_t,因此这里选择auto
    cout << c << endl;
    // u8 前缀只能修饰单字节utf8和US-ASCII编码
    // u 用来修饰两字节UTF-16编码
    // U 用来修饰四字节的UTF-32编码
    // L 用于没有明确编码的宽字符,可能实两个或者四个字节
    



    // 单参数static_assert
    // C++17后原来的static_assert要求的用作错误信息的参数变为可选的
    // 也就是说现在断言失败后输出的诊断信息完全依赖平台的实现
    



    // 预处理条件 __has_include(<filename>)
    // 如果#include<filename>有效,那么__has_include(filename)被求值为1
    // __has_include 是纯粹的预处理指令,因此不能作为if的条件
    





    return 0;
}

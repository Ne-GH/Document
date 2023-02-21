#include <iostream>
#include <thread>
using namespace std;

class Mc{
    // C++不允许在类中初始化非常量的静态成员
    // static int val = 10;     ERROR
    static int val1;



    // 通过使用thread_local可以为每一个线程创建一个内联变量
    inline static int value0;                   // 整个程序只有一个
    inline static thread_local int value1;      // 一个线程有一个
    int  value2;                                // 每个实例有一个
};
// 可以在类定义的外部定义并初始化非常量的静态成员,但是如果这个文件被多个文件同时包含会引发链接错误,除非该变量或实体被定义为inline,否则在同一个编译单元内,只能被定义一次
int Mc::val1 = 10;

class Mcc{
    // C++17之后可以对已经有完整类型的非常量静态成员进行初始化
    inline static int val = 10;


    // C++11/14 是声明
    // C++17是定义, C++17constexptr隐含inline
    // 等价于static constexpr inline int vall = 10
    static constexpr int vall = 100;
};

class Mccc{
public:
    int val = 10;
    Mccc(){}
    Mccc(int i):val(i){}
    static Mccc M;
};
// 仍需拥有完整声明后再定义
inline Mccc Mccc::M{100};


int main(){


    Mccc mccc;
    cout << mccc.val << endl;
    cout << mccc.M.val << endl;

    // 类似指针,指向了同一个地址,因此无论查找多少层都是static Mccc自身
    cout << "Mccc::M.val" << ":" << &Mccc::M.val << endl;
    cout << "Mccc::M.M.val" << ":" << &Mccc::M.M.val << endl;
    cout << "Mccc::M.M.M.val" << ":" << &Mccc::M.M.M.val << endl;


    return 0;
}

/*********************************************************************
 * Auther : yongheng
 * Date : 2022/10/01 23:10
*********************************************************************/
#include <iostream>
/*********************************************************************
 * using 声明扩展后可以支持逗号分隔符的名称列表,这个特性可以用于参数包
*********************************************************************/
class Base{
public:
    void a();
    void b();
    void c();
};
class Derived:private Base{
public:
    /* 在C++17之前需要使用3个using声明 */
    using Base::a,Base::b,Base::c;
};


/*********************************************************************
 * 变长的using声明
 * 逗号分割的using声明允许我们在泛型代码中从可变数量的所有基类中派生同一种运算,
 * 这项技术很酷的应用是创建一个重载的lambda的集合
*********************************************************************/
template<typename ...Ts>
struct overload : Ts...{
    using Ts::operator()...;
};
/* 基类的类型从传入的参数中推导 */
template <typename ...Ts>
overload(Ts ...) -> overload<Ts ...>;

/*********************************************************************
 * 使用变长using声明继承构造函数
*********************************************************************/
/* 除了逐个声明继承构造函数之外,现在还支持如下的方式:
 * 声明一个可变参数类模板Multi,让他继承每一个参数类型的基类
*/
template <typename T>
class Base1{
    T value{};
public:
    Base1(){

    }
    Base1(T v) : value{v}{

    }
};
template<typename ... Types>
class Multi : private Base1<Types>...{
public:
    /* 继承所有构造函数 */
    using Base1<Types>::Base1...;
    /* 理论上可以通过以下声明来支持Multi<>进行赋值操作 */
    using Base1<Types>::operator = ...;

};

int main(){

    auto twice = overload {
        [](std::string &s){ s += s;},
        [](auto &v) { v *= 2; }
    };
    int i = 42;
    twice(i);
    std::cout << "i:" << i << std::endl;
    std::string s = "hi";
    twice(s);
    std::cout << "s:" << s << std::endl;

    /* 有了所有基类构造函数的using声明,可以继承每个类型对应的构造函数 */
    /* 可以使用每一个相应的构造函数来声明对象 */
    /* 根据新的语言规则,每一个初始化会调用匹配基类的相应构造函数和所有其他基类的默认构造函数 */
    /* 例如,m2的声明会调用Base<int> Base<std::string> Base<bool>的默认构造函数 */
    using MultiSB = Multi<int,std::string,bool>;
    MultiSB m1 = 42;
    MultiSB m2 = std::string("hello");
    MultiSB m3 = true;


    return 0;
}
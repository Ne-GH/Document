/*********************************************************************
 * Auther : yongheng
 * Date : 2022/10/01 21:13
*********************************************************************/

#include <iostream>
/*********************************************************************
 * 自从C++17起,可以使用占位符类型(auto 和 decltype(auto)) 作为非类型模板参数的类型
 * 这意味着我们可以写出泛型代码来处理不同类型的非类型模板参数
*********************************************************************/

template <auto N>
class S{

};


/*********************************************************************
 * 输出所有参数-改进版
*********************************************************************/
template<auto Sep = ' ',typename  First,typename ...Args>
void Print(const First first,const Args&... args){
    std::cout << first;
    auto outWidthSep = [](const auto &arg){
        std::cout << Sep << arg;
    };
    (... , outWidthSep(args));
    std::cout << '\n';
}


/*********************************************************************
 * auto 模板参数的另一个应用是可以让我们更轻易的定义编译期常量
*********************************************************************/
/* CPP17 前 */
template<typename T,T v>
struct  constant{
    static constexpr T val = v;
};
using i = constant<int,42>;
using c = constant<char,'x'>;
using b = constant<bool,true>;
/* CPP17 后 */
template<auto v>
struct constant17{
    static constexpr auto val = v;
};
using i17 = constant17<42>;
using c17 = constant17<'x'>;
using b17 = constant17<true>;


/*********************************************************************
 * 使用decltype(auto)模板参数
 * 根据decltype的规则,如果使用decltype(auto)来推导表达式而不是变量名,
 * 那么推导的结果将依赖于表达式的值类型
 * prvalue (例如临时变量) 推导出 type
 * lvalue  (例如有名字的对象) 推导出type &
 * xvalue  (例如用std::move()标记的对象) 推导出 type &&
*********************************************************************/
template<decltype(auto) N>
struct  C{
    void PrintN() const {
        std::cout << "N:" << N << '\n';
    }
};

int main(){

    S<42> s1;       /* ok, S 中的 N 的类型是 int */
    S<'a'> s2;      /* ok, S 中的 N 的类型是 char*/

/*  S<2.5> s3;      */
/* error, 不能用这个特性来实例化不允许作为模板参数的类型,模板参数类型不能是 double */

    /* 可以自定义间隔填充 */
    Print(1,2,3,4,5);
    Print<'+'>(1,2,3,4,5);
    static const char sep[] = "...";
    Print<sep>(1,2,3,4,5);

    static const int c = 42;
    C<c> c1;        /* N的类型为const int */
    C<(c)> c2;      /* N的类型为Const int &,N是C的引用 */
    c1.PrintN();
    c2.PrintN();
    static int vi = 42;
    C<(vi)> c3;     /* N的类型为int &,N是vi的引用 */
    vi = 77;
    c3.PrintN();


    return 0;
}
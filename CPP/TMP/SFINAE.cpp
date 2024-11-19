#include <iostream>

/*******************************************************************************
 * SFINAE
 * 代换失败不是错误(Substitution Failure Is Not An Error)
 * 当模板形参在替换成显式指定的类型或推导出的类型失败时，从重载集中丢弃这个特化，而非导致编译失败
 *
 * 如果对代换后的类型/表达式的求值导致副作用，例如实例化某模板特化、生成某隐式定义的成员函数等，那么这些副作用中的错误都被当做硬错误。
*******************************************************************************/

template <typename T>
struct B {
    using type = typename T::type;
};

template <
    typename T,
    typename U = typename T::type,      // T为void时，此处为void::type, 由于"模板形参在替换成显式指定的类型或推导出的类型失败"因此是SFINAE
    typename V = typename B<T>::type >  // T为void时，此处为硬错误，但是被上面短路，提前结束，因此此处不会发生编译错误
void func(int) {
    std::cout << "int" << std::endl;
}
template <typename T>
void func(double) {
    std::cout << "double" << std::endl;
}

// 在返回类型中使用SFINAE, 使得参数T支持 operator + ()
// 如果使用SFINAE, 参数类型出现错误时：由于代换失败，从重载集合中丢弃这个特化，最后在没有其他匹配的情况下，得到“没有找到匹配的重载函数”的错误
// 如果此处没有使用SFINAE, 此处会实例化模板，此后发现该类型没有operator + (), 产生实例化模板错误(一般不易阅读)
// 因此使用SFINAE有以下好处
//      1. 简化编译错误
//      2. 提高编译速度, 代换失败后没有模板实例化过程
template <typename T>
auto add(const T &left, const T &right) -> decltype(left + right) {
    return left + right;
}

// 标准库对SFINAE的支持，C++11引入了enable_if
// 以下为实现
template <bool flag, typename T = void>
struct enable_if {};

template <typename T>
struct enable_if<true,T> {
    using type = T;
};

// 使用
/*
用法 1
template <typename T, typename SFINAE =
    std::enable_if_t<std::is_same_v<T,int>>
    >
用法2, 和用法1 作用相同
*/
template <typename T, std::enable_if_t<std::is_same_v<T,int>,int> = 0>
void func_enable_if(T val) {
    std::cout << "enable_if int" << std::endl;
}




// C++14引入
template <bool flag,typename T>
using enable_if_t = typename enable_if<flag,T>::type;

// 自定义的数组实现
template<class Ty, std::size_t size>
struct array {
    Ty arr[size];
};
// 如果不使用SFINAE约束，则array会使用第一个参数的类型
template <typename T,typename... Args>
array(T,Args ...)
    -> array<std::enable_if_t<(std::is_same_v<T,Args>&& ...), T>, sizeof...(Args) + 1>;


// void_t C++17 用来检测SFINAE中的非良构类型
template <typename ...Args>
using void_t = void;

// 要求T 有 operator + (), 有 type, 有value 有 f
// 其中 decltype(T{} + T{}) 还约束了T要支持默认构造, 解决方案是使用 declval
template <typename T, typename SFINAE =
    std::void_t<decltype(T{} + T{}), typename T::type, decltype(&T::value), decltype(&T::f)>
    >
decltype(std::declval<T>().value) add_void_t(const T &left,const T &right) {
    return left.value + right.value;
}

// declval 用于将任意类型转换成引用类型，只能用于不求值语境，且不要求有定义
// 不能被实际调用，无返回值，返回类型为T &&
// 此时的T,仅需要支持 operator + () ,而无需支持默认构造
template <typename T, typename SFINAE =
    std::void_t<
        decltype(std::declval<T>() + std::declval<T>()),
        decltype(std::declval<T>().f())
    >
>
decltype(std::declval<T>().value) add_declval(const T &left,const T &right) {
    return left.value + right.value;
}


template<typename T,typename T2 = void>
struct X{
    static void f() { std::puts("主模板"); }
};

template<typename T>
struct X<T, std::void_t<typename T::type>>{
    using type = typename T::type;
    static void f() { std::puts("偏特化 T::type"); }
};

struct Test { using type = int; };
struct Test2 { };


int main() {
    struct C {
        using type = int;
        int value{};
        void f() const ;
        C operator + (const C&) const {
            return *this;
        }
    };

    func<B<C>>(1);
    func<void>(1);

    add(1,2);

    // 硬错误
    // add(C{},C{});

    func_enable_if(1);
    // 硬错误
    // func_enable_if(C{});

    ::array arr_int { 1, 2, 3, 4, 5};
    ::array arr_double { 1.0, 2.1, 3.3, 4.0};

    add_void_t(C{},C{});

    add_declval(C{},C{});

    X<Test>::f();
    X<Test2>::f();

    return 0;
}


/***************************************
 * author : yongheng
 * date  : 2022/09/30 19:01
 *
***************************************/

#include <iostream>
#include <string>

template<typename T>
std::string asString(T x){
    /* is_same 用来判断两个类型是否相同 */
    if constexpr (std::is_same_v<T,std::string>){
        return x;
    }
    /* is_arithmetic 用来判读指定类型是否为算术类型 */
    else if constexpr (std::is_arithmetic_v<T>){
        return std::to_string(x);
    }
    else{
        return std::to_string(x);
    }
}

auto fun(){
    if constexpr (sizeof(int) > 4){
        return 42;
    }
    else{
        // 如果没有下面的else return,那么使用运行时if将会编译错误,因为返回类型可能是int,也可能是void
        return 42u;

    }
}

auto max(){

    /* 这种省略else的运行时if,不能改为编译时,因为如果if成立,那么会推导出两个返回类型,否则可以编译 */
    if(sizeof(int) > 4)
        return 1;
    return;
}

/***************************************
 * 编译期if不会像运行期一样进行短路运算,
 * 因此如果后面的条件依赖于前面的条件,应该写为嵌套形式
***************************************/
template<typename T>
constexpr auto bar(const T& val){
    if constexpr (std::is_integral<T>::value && T{} < 10) {
        return val * 2;
    }
    return val;
}

// 此处无代码:
// 编译期if使我们几乎拥有编译期switch,进而调用不同的函数等?
// 但是不同的是 重载函数遵循最佳匹配语义 , 编译期if遵循最先匹配语义


/*********************************************************************
 * 编译期if同样可以使用初始化语句
*********************************************************************/
template<typename T>
void bar(const T x) {
    if constexpr (auto obj = foo(x); std::is_same_v<decltype(obj), T>) {
        std::cout << "foo(x) yields same type\n";
    }
    else {
        std::cout << "foo(x) yields different type\n";
    }
}
int main(){

    std::cout << asString(42) << std::endl;
    std::cout << asString(std::string("Hello")) << std::endl;
//    std::cout << asString("hello") << std::endl;


    return 0;
}
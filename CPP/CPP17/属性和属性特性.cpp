#include <iostream>

using namespace std;

// nodiscard 属性鼓励编译器在返回值未被使用的时候发出警告(可能不给)
// 如果nodiscard在基类中,不会被继承
[[nodiscard]]
int fun(int val){
    return val * val;
}

// 弃用标记，当使用弃用内容时，将使用括号中的字符串进行警告
// 可标记枚举值 命名空间 和 函数
namespace [[deprecated]]MeSpace {  };
enum NUMS{ ONE[[deprecated]] = 1 , TWO = 2};
[[deprecated("这个函数已经被弃用")]]
void Fun(){
    cout << "this is functiuon" << endl;
}



int main(){

    Fun();
    int num = ONE;


    fun(10);
    (void)fun(10);      // 将返回值强制转换为void,可禁用/忽略nodiscard属性的警告


    // [[maybe_unused]]属性可以避免编译期在某个变量未被使用时发出警告,可用于类的声明,typedef/using,变量,非静态数据成员,函数,枚举,枚举值
    [[maybe_unused]]int val = 10;

    // [[fallthrough]]属性避免switch语句中某个标签缺少break语句时发出警告
    switch([[maybe_unused]]int vall = 10;val){
        case 1:
            break;
        case 2:
            [[fallthrough]];
        case 3:
            [[fallthrough]];
        default:
            break;
    }
    return 0;
}

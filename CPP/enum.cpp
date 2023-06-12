#include <iostream>

using namespace std;

// 如果不添加作用域，那么不同的enum中的枚举类型不能相同
// 限定作用域的enum
enum class EnumClass{
    OneClass = 10,
    TwoClass = 20
};
enum Enum{
    One = 1,
    Two = 2
};
enum EnumINT:char{
    ZeroINT = 'A'
};
int main(){

    EnumClass EC = EnumClass::OneClass;

    cout << (int)EC << endl;
    
    cout << ZeroINT << endl;
    cout << One << endl;

    return 0;
}

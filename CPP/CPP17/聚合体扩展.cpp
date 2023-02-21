#include <iostream>
using namespace std;

struct Key{
    int val{10};
    int key{20};
};

struct MoreKey:Key{
    // 如果觉得对实例使用聚合体比较危险,可以对每个成员设置成员初始值
    int More{30};
};

int main(){

    // C风格的初始化
    Key KeyC = {1,2};

    // C++11起,可以忽略'='
    Key KeyCpp11{2,3};

    // C++17起,聚合体可以拥有基类
    // 内部嵌套的初始值列表将按继承时基类声明的顺序传递给基类
    MoreKey More17_1{{3,4},5};
    MoreKey More17_2{4,5,6};
    MoreKey More17_3{{},7};     // 等价于{{默认/0,默认/0},7}
    
    // 确认是否符合聚合体
    cout << is_aggregate<decltype(More17_1)>::value << endl;
        
    





    return 0;
}

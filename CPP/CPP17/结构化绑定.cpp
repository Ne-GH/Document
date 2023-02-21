#include <iostream>
#include <string>
#include <tuple>
#include <typeinfo>
#include <map>
#include <array>
#include <tuple>

using std::cin,std::cout,std::endl,std::string,std::map;

struct Mystruct{
    int i = 0;
    double dou = 0.0;
    string str;
};
int main(){

    struct Mystruct Ms {1,2.0};
    // auto [v1,v2] = Ms;   ERROR

    // 结构化绑定时有一个隐藏的匿名对象,结构化绑定时引入新变量都指向这个匿名对象的成员/元素
    // v1,v2,v3都是这个匿名结构体中相应元素的别名
    auto [v1,v2,v3] = Ms;
    // 等价于:
    // auto te = Ms;    匿名的te对象遵守通常的内存对齐
    // auto v1 = te.i;
    // auto v2 = te.dou;
    // auto v3 = te.str;
    auto [v4,v5,v6]{Ms};
    auto &[v7,v8,v9](Ms);

    // 结构化绑定只能同时声明,不能同时使用,不过我们可以使用如下方法同时改变他们的值
    std::tie(v1,v2,v3) = std::tuple<int,double,std::string>(10,20.0,"30");

    cout << typeid(v1).name() << endl;
    cout << typeid(v2).name() << endl;
    cout << typeid(v3).name() << endl;
    cout << typeid(v4).name() << endl;
    cout << typeid(v5).name() << endl;
    cout << typeid(v6).name() << endl;
    cout << typeid(v7).name() << endl;
    cout << typeid(v8).name() << endl;
    cout << typeid(v9).name() << endl;
//

    map<int,string>mp;
    mp[0] = "123";
    mp[1] = "456";
    mp[2] = "789";

    for(auto te : mp){
        cout << te.first << ":" << te.second << endl;
    }
    for(auto [key,val] : mp){
        cout << key << ":" << val << endl;
    }


    return 0;
}

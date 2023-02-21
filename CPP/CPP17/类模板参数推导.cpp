/*
*    Time: 08/18/22 00:02:28
*    Create By yongheng
*/

#include <iostream>
#include <functional>
#include <tuple>
#include <utility>
#include <vector>
#include <typeinfo>
#include <iostream>
#include <string>
using namespace std;

template<typename T,int SZ>
class MyClass{
public:
    //\
    MyClass(T(&)[SZ])   // 同下,但是没有得到字符串
    MyClass(T(& str)[SZ]){
        cout << "str:" << str << endl;
        cout << "Size:" << SZ << endl;
    }

};


template<typename...args>
auto MakeVector(args&... elem){
    return vector{elem...};
}

template <typename CB>
class CountCalls{
    CB callback;
    long calls = 0;
public:
    CountCalls(CB cb):callback(cb){  }
    template<typename... Args>
    decltype(auto) operator()(Args&&... args){
        ++calls;
        return callback(forward<Args>(args)...);
    }
    long count() const{
        return calls;
    }
};


template<typename T1,typename T2,typename T3>
class C{
public:
    C(T1 t1,T2 t2,T3 t3){
        cout << "init class C" << endl;
    }
};

template <typename T1>
struct S{
    T1 _s;
    // 推导指引和类的构造函数会产生竞争,类模板参数推导时会根据重载情况选择最佳的构造函数/推导指引
    // 优先级相同时,优先选择推导指引
    // 如下:
    // S(int) -> S<long>;
    // S s{1} 1是int,和推导指引更匹配,因此选择推导指引,T是int
    // S s{'c'} c 是char,和int 不匹配,故选择构造函数,T是char
    S(const T1 &s):_s(s){}
    void Str(){
        cout << "S:" << _s << endl;
        cout << "Type:" << typeid(T1).name() << endl;
    }
};
// 重载推导规则可使在推导时类型发生退化
S(const char *)->S<string>;
template <typename T1>
S(T1)->S<T1>;
// explicit 让使用赋值进行的推导无效,直接初始化和右侧显式推导依然有效
template<typename T>
explicit S(T)->T<T*>;
// S s(1)    -->    S<int *> s
// S s = {1}    -->  S<int> s




int main(int argc,char *argv[]){


    // 被推导为 tuple<int,double,char>
    // 推导过程中不会进行隐式转换
    tuple t{1,1.0,'0'};
    MyClass mc("this is class MyClass");


    // 默认使用拷贝的方式进行推导
    vector<int> v1{1};      // vector<int>
    vector<int> v2{v1};     // vector<int>
    auto v3 = vector{v1};   // vector<int>
    vector v4{v1,v2};       // vector<vector<int>>
    for(auto arr : v4){
        for(auto num : arr){
            cout << num << " ";
        }
        cout << endl;
    }

    auto x1 = MakeVector(v1);       // vector<int> 或者 vector<vector<int>> ,目前各个平台的实现尚有不同
    auto x2 = MakeVector(v1,v2);    // vector<int>
    
    vector x3{9,8,7,6,5,4,3,2,1};
    CountCalls sc{[](auto x,auto y){return x>y;}};
    sort(x3.begin(),x3.end(),ref(sc));

    cout << "sort:" << sc.count() << endl;
    

    // 不允许只指明一部分模板参数,即使是空的模板参数<>也不被允许,即,如果需要指明,需指明所有,否则就应全部推导
    C<int,int,char> c1(1,2,'c');    // OK
//  C<int,int,>c2(1,2,'c');         // ERROR
//  C<>c3(1,2,'c')                  // ERROR

        
    // OK
    S s1("123456");
    S s2 = {"123456"};
    S s3 = S{"123456"};

    // ERROR
    // 不能不使用花括号初始化聚合体
//  S s4 = "123456";
//  S s5("123456");

    s.Str();





    return 0;
}

/*
*    Time: 02/05/23 18:19:27
*    Create By yongheng
*/

#include <iostream>
#include <string>

#define MES(mes) cout << #mes << endl

using namespace std;

class Test{
    int _val;
public:
    // 默认构造函数
    Test() = default;
    // 在构造函数只有一个参数的时候，explicit关键字可以禁止该参数类型向当前类的隐式转换
    explicit Test(int val) : _val(val) {  }

    // 委托构造函数
    Test(int val1,int val2) : Test(val1+val2) {  }

    // 三/五法则
    // 拷贝构造函数
    Test(const Test& other){
        MES("拷贝构造函数");
        _val = other._val;
    }
    // Test(const Test& other) = delete ; 阻止拷贝
    Test& operator = (const Test &other){
        MES("赋值运算符");
        if(this != &other){
            _val = other._val;
        }
        return *this;
    }
    // Test operator = (const Test& other); 阻止赋值
    ~Test() = default;

    // 移动构造函数,noexcept 表示不出异常
    Test(Test&& other) noexcept {
        MES("移动构造函数");
        _val = move(other._val);
    }
    // 重载移动赋值运算符
    Test& operator = (Test&& other) noexcept {
        MES("移动赋值运算符");
        if(this != &other) {
            _val = move(other._val);
        }
        return *this;
    }
    

};

int main(int argc,char *argv[]){

    Test t1(0);
    Test t2 = t1;       // 拷贝构造函数
    Test t3 = move(t2); // 移动构造函数
    
    t2 = t1;            // 赋值运算符
    t3 = move(t2);      // 移动赋值运算符
    
    



    return 0;
}

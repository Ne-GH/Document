#include <iostream>

using namespace std;

class T{
public:
    int val;
    int key;
    T():val(0),key(0){}
    // 删除拷贝构造函数
    T(T &) = delete;
    T(T &&) = delete;
    // 使用移动构造函数
    // T(T &&obj){
        // this->val= obj.val;
        // this->key = obj.key;
    // }
};

T ret(){
    // 返回的临时对象会被用来实质化一个新的对象,作为实质化的结果,纯右值在赋值时不调用构造函数
    // 实质化的过程中没有创建新的不同的对象
    // 因为prvalue不再是对象而是可以被用来初始化对象的表达式,所以当使用prvalue来初始化对象时不再需要prvalue是可移动的
    // 不调用构造函数可以提高性能
    return T{};
}
void fun(T te){
    cout << te.val << endl;
}
int main(){

    fun(ret());



    return 0;
}

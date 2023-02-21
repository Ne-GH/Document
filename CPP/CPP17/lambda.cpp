#include <iostream>

using namespace std;

class C{
private:
    int val;
public:
    C(){}
    ~C(){}
    void fun(){
        // 在非静态成员函数里使用lambda时,不能隐式获取该对象成员的使用权,也就是说,不捕获this的话就不能在lambda中使用该对象的任何成员,即便用过this->访问也不行
        // auto t1 = []{cout << val << endl;};      ERROR
        auto t0 = [this]{cout << val << endl;};

        // C++11/14里可以通过值或引用捕获this
        auto t1 = [=]{cout << val << endl;};
        auto t2 = [&]{cout << val << endl;};

        //C++17里可以通过*this显式的捕获当前对象的拷贝
        auto t3 = [*this]{cout << val << endl;};
    }
};

int main(){

    // C++17之后lambda 表达式会尽可能隐式声明constexpr
    auto squ = [](auto val){
        static int calls = 0;       // ok,但是会让该lambda表达式不能称为constexpr
        return val * val;
    };
    cout << squ(10) << endl;

    // C++17后可以指明constexpr以便确认是否可以用于编译期,后面的->int用来指明返回类型
    // 此时squ0运行时确定,lambda表达式编译期确定
    auto squ0 = [](auto val)constexpr->int{
        // static int calls = 0;   ERROR,使用了编译期不允许的特性
        return val * val;
    };
    cout << squ0(10) << endl;

    // squ1 和lamdba 表达式都在编译期确定
    constexpr auto squ1 = [](auto val)constexpr->int{
        return val * val;
    };
    cout << squ1(10) << endl;
    

    // 通过隐含的或者声明的constexpr 我们可以在编译期计算一些东西


    return 0;
}

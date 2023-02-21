/*
 * 此对象为BaseBook的派生类
 */

#include "base.h"

// DerivationBook 继承自BaseBook
// 继承得到的默认为private类型

// 如下的默认继承方式为private,如果想要以public的方式继承则需要使用public
// 如果我们使用了public ,我们可以将派生类的对象绑定到基类的引用或者指针上
//
// class DerivationBook:BaseBook
class DerivationBook: public BaseBook{
public:

    // 通过这个public的函数调用继承得到的private类型的GetBookPrice函数,如果deri中没有重新定义GetBookPrice时,调用基类的,否则,调用派生类的
    void GetBasefun(){
        GetBookPrice(0);
    }

    // 重新定义基类中的虚函数时,定义前的virtule不是必须的
    // override 为C++11中的关键字,表示使用该函数改写基类中的虚函数
    // 同时,编译器将检查该函数是否覆盖了基类中的虚函数,如果没有将在编译时报错
    // 如果我们使用了默认参数,那么实参的值由本次调用的静态类型决定
    // 即,如果参数类型是base,那么即便之后会动态绑定deri,也将使用base的默认参数,所以,如果需要使用默认实参,那么基类和派生类的默认实参最好保持一致
    virtual int GetBookPrice(int num = 20)const override{
        cout << "Derivation Price " << num << endl;
        return BookPrice;
    }
    

};


class Pure : public BaseBook{
public: 
    // 声明一个纯虚函数,表示这个函数无意义,当然我们可以给他一个定义
    // 但是我们的定义要放在类的外面
    // 含有或者没有覆盖直接继承的纯虚函数的类是抽象基类,抽象基类负责定义接口,我们不能直接创建一个抽象基类的对象
    int GetBookPrice(int)const override = 0;
};


// 使用struct定义的类和使用class定义的类,只有默认成员访问说明符和默认派生访问说明符不同,除此之外没有其他不同
struct StructDeri : BaseBook {
public: 
    int nums = 100;
};

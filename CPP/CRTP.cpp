/*******************************************************************************
 * @Author : yongheng
 * @Data   : 2024/10/15 15:18
*******************************************************************************/
#include <iostream>

/*******************************************************************************
 * CRTP的一个典型例子为:std::enable_shared_from_this,该模板在文件"智能指针.cpp"中有过描述
 * CRTP的作用往往是基类需要获取一些派生类信息、成员、方法、类型本身, 通过在基类中实现方法继承来扩展派生类本身
 * 作用： 避免虚函数、动态分配带来的额外运行时代价
 * 注意： CRTP 不能用于动态调度，也就是将一系列继承于不同模板参数的同一个 CRTP 模板类放到同一个容器里。
 *       有些人为了能运行时调度而加入了一个总的基类使得所有 CRTP 虚继承自此，这是完全错误的。
 *       CRTP 是用来消除运行时多态的，加入全局虚基类会凭空创造运行时代价，这就完全抹煞了 CRTP 的作用。
*******************************************************************************/
struct NameBase {
    virtual std::string name() = 0;


};

struct Base1 {
    virtual void drink() {
        std::cout << "drink" << std::endl;
    }
};
struct Base2 {
    virtual void eat() {
        std::cout << "eat" << std::endl;
    }
};

class Derived : virtual Base1, Base2, NameBase{
    std::string name_;
public:
    explicit Derived(std::string name) : name_(std::move(name)) {  }
    void drink() {
        std::cout << name() << " : ";
        Base1::drink();
    }
    void eat() {
        std::cout << name() << " : ";
        Base2::eat();
    }
    std::string name() {
        return name_;
    }
};


// 上方功能的CRTP实现版本
template<typename T>
struct CRTPBase1 {
    void drink() {
        std::cout << static_cast<T *>(this)->name() << " : ";
        std::cout << "drink" << std::endl;
    }
};
template<typename T>
struct CRTPBase2 {
    void eat() {
        std::cout << static_cast<T *>(this)->name() << " : ";
        std::cout << "eat" << std::endl;
    }
};

class CRTPDerived : public CRTPBase1<CRTPDerived>, public CRTPBase2<CRTPDerived> ,public NameBase {
    std::string name_;
public:
    explicit CRTPDerived(std::string name) : name_(std::move(name)) {  }
    std::string name() {
        return name_;
    }
};



/*******************************************************************************
 * 更现代化的CRTP
*******************************************************************************/

template<template<typename ...> typename ...Base>
class MCDerived : public Base<MCDerived<Base...>> ... {
    std::string name_;
public:
    explicit MCDerived(std::string name) :
             Base<MCDerived<Base ...>> {*this} ... , name_(std::move(name))
    {

    }
    std::string name() {
        return name_;
    }
};


/*******************************************************************************
 * C++ 20 约束  +  C++ 23 显式对象形参
*******************************************************************************/
template<typename T>
concept HaveName = requires(T value){
    { value.name() } -> std::same_as<std::string>;
};

struct BaseDrink23 {
    template<typename T>
    void drink(this T& self) requires HaveName<T> {
        std::cout << self.name() << " : ";
        std::cout << "drink" << std::endl;
    }
};
struct BaseEat23 {
    template<typename T>
    void eat(this T& self) requires HaveName<T> {
        std::cout << self.name() << " : ";
        std::cout << "eat" << std::endl;
    }
};

class Derived23 : public BaseDrink23 , public BaseEat23{
    std::string name_;
public:
    Derived23(std::string name) : name_(std::move(name)) {  }
    std::string name() {
        return name_;
    }

};





int main() {
    Derived derived{"derived"};
    derived.eat();
    derived.drink();

    CRTPDerived crtp_derived{"crtp_derive"};
    crtp_derived.eat();
    crtp_derived.drink();


    using DrinkDerived = MCDerived<CRTPBase1>;
    using EatDerived = MCDerived<CRTPBase2>;
    using ModernDerived = MCDerived<CRTPBase1,CRTPBase2>;

    DrinkDerived drink_derived{"modern drink derived"};
    EatDerived eat_derived{"modern eat derived"};
    drink_derived.drink();
    eat_derived.eat();

    ModernDerived modern_derived{"modern both derived"};
    modern_derived.drink();
    modern_derived.eat();


    Derived23 derived23 {"derived23"};
    derived23.eat();
    derived23.drink();





    return 0;
}

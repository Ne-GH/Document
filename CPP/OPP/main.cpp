#include "derivation.h"


// 动态绑定,当我们使用基类的引用或者指针来调用一个虚函数的时候将会发生动态绑定,即根据传入参数的具体类型来调用不同的虚函数版本
// 如果我们不是通过引用或者指针来调用虚函数,那么虚函数的版本将在编译时确定,不会发生动态绑定
void RunFun(BaseBook& base){
    base.GetBookPrice();
}
int main(){
    BaseBook base;
    DerivationBook deri;
    
    // 如果类中存在纯虚函数,那么我们不能直接定义这个类的对象
    // Pure pure;


    // 直接通过对象调用函数,函数的版本在编译时确定,不会发生动态绑定
    base.GetBookPrice();
    deri.GetBookPrice();
    
    // 如果deri中没有重新定义GetBookPrice时,调用基类的,否则,调用派生类的
    deri.GetBasefun();

    // 动态绑定
    RunFun(base);
    RunFun(deri);

    // 将deri的基类部分赋值给base
    base = deri;

    // 使用派生类中基类版本的虚函数
    // 这种形式只能为派生类调用派生类或者调用基类
    // 不能是基类对象调用派生类的虚函数
    deri.BaseBook::GetBookPrice();

    
        



}

/*
 * 此对象为基类base
 */


#include <string>
#include <iostream>
using std::cout;
using std::endl;

class BaseBook{
public:
    // 书籍名称
    std::string Bookname;
    // 书籍价格
    int BookPrice;

    std::string GetBookName()const{
        return Bookname;
    }

    // 定义为虚函数,即希望派生类自己定义自己的版本
    // 任何构造函数之外的非静态函数,都可以是虚函数
    // 如果在基类中定义为虚函数,那么在派生类中也默认为虚函数
    // 如果成员函数没有被定义为虚函数,那么解析过程发生在编译时而非运行时
    virtual int GetBookPrice(int num = 10)const{
        cout << "Base Price " << num << endl; 
        return BookPrice;
    }


    // 如果我们使用final来限定函数,则之后任何试图覆盖的操作都将引发错误
    virtual void No() final {
        cout << "No" << endl;
    }


};

// 使用final限定后,该类不能被继承
class NoBase final{

};

// NotoBase 继承自BaseBook ,同时不能被继承
class NotoBase final : BaseBook{

};


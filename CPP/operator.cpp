#include <fstream>
#include <iostream>
#include <istream>
#include <ostream>


using std::cout,std::endl;
// 重载的运算符的本质是函数
// 我们不能重载内置类型的算数运算符
// 因此我们在这里构造我们自己的类


// 重载运算符应被定义为普通非成员函数还是成员函数规则,如下:
// 赋值(=),下标([]),调用(()),和成员访问箭头(->)运算符必须是成员
// 复合赋值运算符一般应该是成员,但是并非必须~
// 改变对象状态的运算符或者与给定类型密切相关的运算符,自增++,自减--,解引用*,成员访问运算符.通常应该是成员函数
// 具有对称性的运算符可以转换到任意一端的运算对象,例如算术,相等性,关系和位运算符等,因此他们通常应该是普通的非成员函数
class node{
public:
    int id;
    int spend;
    
    // 构造
    node(){
        id = 0;
        spend = 0;
        for(int i = 0;i < 10; ++i){
            nums[i] = i;
        }
    }

    // 我们应该避免除了向bool显式转换以外的转换
    operator bool() const{
        if(id != 0)
            return true;
        return false;
    }

    node operator += (node no){
        node temp;
        temp.spend = this->spend + no.spend;
        return temp;
    }
    node operator -= (node no){
        node temp;
        temp.spend = this->spend - no.spend;
        return temp;
    }
    int operator [] (int num){
        return this->nums[num];
    }
    // 虽然此处未返回引用,但是由于返回了指针,因此我们的修改也会在内存中生效
    int* operator *(){
        return (*this).nums;
    }
    // c++ pirmer 中提到重载的->必须返回类的指针或者自定义了箭头运算符的某个类的对象,但是我们这里返回的显然与此描述不符
    int* operator -> (){
        return this->nums;
    }
    int operator ()(){
        return id;
    }
    // 前置
    node& operator ++(){
        this->id ++;
        return *this;
    }
    // 后置
    node operator ++(int){
        node no = *this;
        this->id ++;
        return no;
    }
    
    
    void* operator new(unsigned long size_t){
        cout << "重载的new" << endl;

        if(void *p = malloc(size_t)){
            return p;
        }
        else
            return NULL;
    }

    void operator delete(void *p){
        free(p);
    }

private:
    int nums[10];



    // 当我们把一个运算符定义为成员函数时,他的左侧对象类型应与重载该符号的类的类型相同
    
     
};

// 非成员函数类型的重载
// 正常情况下我们应该只输入输出,不进行格式控制,这里算是一个反面教材
std::istream& operator >> (std::istream &in,node &no){
    std::cout << "please input node id:";
    in >> no.id;
    std::cout << "please input node spend:";
    in >> no.spend;
    return in;
}
// 输出时node 不必为引用类型,否则不可以cout << no1 + no2 这种样式输出
// 因为no1 + no2运算后为一个右值,对于一个右值自然是不能引用的
std::ostream& operator << (std::ostream &out,node no){
    std::cout << no.id << " ";
    std::cout << no.spend;
    return out;
}
node operator + (node no1,node no2){
    node temp;
    temp.spend += no1.spend;
    temp.spend += no2.spend;
    return temp;
}
node operator - (node no1,node no2){
    node temp;
    temp.spend = no1.spend - no2.spend;
    return temp;
}
bool operator == (node no1,node no2){
    if(no1.id == no2.id)
        return true;
    return false;
}
bool operator != (node no1,node no2){
    if(no1.id != no2.id)
        return true;
    return false;
}
// 返回类型不一定需要是node,但是参数列表必须如此
node operator ""_ms(const char *str,std::size_t len){
    // ... 使用的时候就是"1233"_ms
    return node();
}
int main(){
    node no1,no2;
    // 如果把node的输入输出定义为成员函数,则如下:
    // no1 >> cin;      因为成员函数运算符的左侧为他自身,唯一的参数为运算符右侧的符号

    // 输入输出
    std::cin >> no1 >> no2;
    std::cout << no1 << std::endl << no2 << std::endl;
    // +
    std::cout << no1+no2 << std::endl;
    // -
    std::cout << no1-no2 << std::endl;
    
    // ==
    node no3 = no1 + no2;
    if(no3 == no1 + no2)
        std::cout << "True" << std::endl;

    // []
    std::cout << no1[3] << std::endl;

    // ++
    node no4 = ++ no1;
    std::cout << no4 << std::endl;
    no4 = no1 ++;
    std::cout << no4 << std::endl;

    // *
    (*no1)[5] = 10;
    std::cout << (*no1)[5] << " " ;
    // ->     
    (*no1)[5] = 5;
    std::cout << no1.operator->()[5] << std::endl;

    // () 与构造函数有区别
    std::cout << no2.id << " " << no2() << std::endl;

    // int()
    std::cout << no2 << " " << (bool)no2 << std::endl;

    return 0;
}

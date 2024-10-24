#include <cstdio>
#include <iostream>
#include <ostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;

// 模板定义以关键字template开始,后面跟着模板参数列表
// 即<tempname T1,class T2>类型参数前需要使用tempname或者class,在这里template和class的含义相同,所以可以互换,不过使用template时,我们的意图似乎更加明显,此外值得注意的是,模板参数列表不能为空
// 编译器会根据传入的参数,生成相应的"实例"
// 例如 cmp(1,2);   就会将T替换为int
// 类型参数可以用来指定返回类型或者函数的参数类型,以及在函数体内用于变量声明或类型转换
// 模板中可以使用非类型参数,即正常使用某个类型,不过被实例化时非类型模板参数会被用户提供的或者编译器推断的值代替,例如此处的Tnum,是一个右值,只有直接给出或者在编译前能够推断出来
// 编译器需要知道函数的定义,因此,不能像普通的函数那样将声明和实现分开写,通常将模板类或者模板函数直接定义在头文件中
// 新标准中我们可以为函数和类模板提供默认参数,而更早的C++标准只允许为类模板提供默认实参
// 与函数默认实参一样,对于一个模板参数,只有当他右侧的所有参数都有默认实参时,他才可以有默认实参
// 如果我们为所有参数都提供了默认参数,且我们想要使用这些默认参数,那么我们在实例化的时候需要提供一个空的<>
template <typename T ,int Tnum=123,typename Tstr = std::string>
// 参数尽量设置为const 引用,这样我们可以保证用于不能拷贝的类型,虽然大多数类型都支持拷贝,但是不能拷贝的类确确实实存在,此外如果数据极大时,const &可以使函数运行地更快
inline/*inline 可以放在此处,而不是template之前*/T cmp(T obj1,T obj2,const char (&str)[Tnum],Tstr ts = Tstr()){
    cout << typeid(Tstr).name() << endl;
    if(obj1 < obj2)
        return obj1;
    else
        return obj2;
}

// 当我们不能(或不希望)使用模板时,可以定义类或函数模板的一个特例化版本(用来处理特殊情况)

template<typename T>
T ret(T num){
    cout << "template" << endl;
    return num;
}
// 当我们特例化一个函数模板是,必须为原模板中的每个模板参数都提供实参
// 为了指出我们正在实例化一个模板,应使用关键字template<>
// <>指出我们将为原模板的所有模板参数提供实参
// 当我们定义一个特例化版本时,函数参数类型必须与一个先前声明的模板中对应的类型匹配
// 特例化的本质是一个模板的实例而非重载它,因此特例话不影响函数匹配
// 为了特例化一个模板,原模板的声明必须在作用域中,而且在任何使用模板实例的代码之前,特例化版本的声明也必须在作用域中
template<>
int ret(int num){
    cout << "int_ret" << endl;
    return num;
}


template<typename TType,int T>
void Test(){
    cout << T << endl;
}


// 函数模板可以被另一个模板或者一个普通非模板函数重载,与往常一样,名字相同的函数必须有不同数量或类型的参数
// 调用时,有如下匹配规则
// 如果同样好的函数中只有一个是非模板函数,则选择此函数
// 如果同样好的函数中没有非模板函数,而有多个函数模板,且其中一个模板比其他模板更特例化(能够匹配的参数类型越少,特例化越高,例如T可以匹配所有类型,T *则只能匹配指针类型),则选择此模板
// 否则调用有歧义
template<typename T>
void overload(T num){
    cout << "T" << endl;
}

template<typename T>
void overload(T *p){
    cout << "T *" << endl;
}

void overload(int *p){
    cout << "int *" << endl;
}



// 可变参数模板
// 一个可变参数模板就是一个接受可变数目参数的模板或模板类,可变数目的参数被称为参数包
// 存在两种参数包,模板参数包,表示零个或多个模板参数; 函数参数包,表示零个或多个函数参数
// 我们用一个省略号来指出一个模板参数或者函数参数表示一个包
// 在一个模板参数列表中class... 或 typename... 指出接下来的参数表示零个或多个类型的列表
// 在函数参数列表中,如果一个参数的类型是一个模板参数包,则此参数也是一个函数参数包
template<typename... args>
void print_size(args...fun_args){
    // sizeof...() 返回包中有多少元素,为常量表达式,且不会为其求值
    cout << sizeof...(fun_args) << endl;;
    return;
}

template<typename T>
std::ostream &print(std::ostream &os,const T &t){
    os << t << endl;
    return os;
}
// 对于一个参数包,除了获取大小外,我们能为它做的唯一的事情就是扩展
// 当扩展一个包是,我们还要提供用于每个扩展元素的模式
// 扩展一个包就是将它分解为构成的元素,对每个元素应用模式,获得扩展后的列表
template<typename T,typename... Args>
// 第一个扩展操作为print生成函数参数列表
// 对Args的扩展中,编译器将模式const Args&应用到模板参数包Args中的每个元素
std::ostream &print(std::ostream &os,const T &t,const Args&... rest){
    os << t << ",";
    // 第二个扩展操作为print生成实参列表
    // 此情况下,模式是函数参数包的名字(即rest)
    // 此模式扩展出一个由包中元素组成的,逗号分隔的列表
    print(os,rest...);
    return os;
}



int retnum(int nums){
    cout << "数字是" << nums << endl;
    return nums;
}
template<typename ... Args>
std::ostream &Test_Print(std::ostream &os,const Args&...rest){
    // 相当于
    // print(os,retnum(rest1),retnum(rest2)......);
    // 即对包rest中的每个元素都执行retnum
    print(os,retnum(rest)...);
    return os;
}


int main(){
    int num1,num2;
    cin >> num1 >> num2;

    // 普通模板
    int min = cmp(num1,num2,"12345");
    cout << "MIN:" << min << endl;

    Test<int,111>();

    // 重载
    int nums[3] = {0};
    overload(num1);
    overload(nums);
    overload("123");


    // 可变参数模板
    std::string str("str");
    print_size(1);
    print_size(1,2);
    print(cout,10);
    print(cout,num1,num2,str);
    print(cout,100,200,str);

    // 包扩展
    Test_Print(cout,1,2,3,4);


    // 模板特例化
    ret(str);
    ret(num1);

    return 0;
}

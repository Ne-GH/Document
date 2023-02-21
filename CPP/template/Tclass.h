#include <iostream>
#include <map>

using std::cin;
using std::cout;
using std::endl;

// 声明模板templ,便于添加友元
template<typename T>class Templ;
// 下面声明的两个模板函数相同
// template<typename T> T fun(T te){  }
// template<typename U> U fun(U te){  }

// 类模板用来生成蓝图,与函数模板不同的是,编译器无法为类模板推断模板参数类型,每个实例化出来的类都相互独立
// 因此为了使用类模板,我们需要提供一些额外信息,例如vector<int>,其中int就是我们需要的额外信息,叫做显式模板实参
// 一个模板类或者其中的方法,只有在使用时才会被实例化,如果没有被使用,则不会被实例化
// 我们在此实现一个简化的vector
// 模板参数名不能重用,因此我们不能写出<typename T,typename T>这样的代码
template <typename T>
class Tclass{
    // 如果友元不是模板,那么友元可以访问所有的模板实例
    friend class Temp;
    // 如果友元是模板,类可以授权给所有友元模板实例,也可以只授权给部分特定实例
    // 此处每个Tclass实例将访问权限授予用相同类型实例化的Templ
    // 即,Templ<int>的对象可以访问Tclass<int>的非public成员,但是对Tclass<char>等无特殊访问权限
    friend class Templ<T>;
    // 使用int实例化的Templ是Tclass的一个友元
    friend class Templ<int>;
    // Templl的所有实例都是Tclass的友元,此时不需要前置声明
    // 为了让所有实例成为友元,友元函数必须使用与类模板本身不同的模板参数
    template <typename TT> friend class Templl;
    // 新标准中我们可以生命一个模板类型作为友元
    // 此时使用该类型实例化的类会将该类型声明为友元
    // 如果使用Node实例化Tclass,那么Node就是这个Tclass<Node>的友元
    friend T;


public:


    // 方法
    // 我们在使用一个类模板类型时必须提供模板实参,但在类模板自己的作用域中我们可以直接使用模板名而不提供实参
    // Tclass<T>(){
        // siz = 0;
    // }
    Tclass(){
        // cout << "构造" << endl;
        // num计算该容器中对象的数量
        siz = 0;
    }


    // 重载[],方便访问
    T operator [] (int pos){
        if(pos >= 0 && pos < siz)
            return Types[pos];
        else{
            // 指针越界,此处决定结束这个程序
            printf("下标异常,siz:%d yourpos:%d\n",siz,pos);
            exit(-1);
        }
    }

    // 与普通的类相同,我们的成员函数既可以定义在类的内部,也可以定义在类的外面,每个实例都有自己版本的成员函数,不过在类外定义成员函数,需要以template开头,后面跟着类模板参数列表
    void insert(T Tin){
        Types[siz++] = Tin;
        return ;
    }

    // 清空
    void clear();

    int size(){
        return siz;
    }

    // 类模板的成员模板
    // 对于类模板,我们可以为其定义成员模板,在此情况下,类和成员各自有各自的独立的模板参数
    // 我们在这里尝试定义在类外
    template<typename FUNT> void GetType(FUNT);


private:
    // 成员
    int siz = 0;
    T Types[100];

    // 模板中可以定义static成员
    // 对于每个实例,都会拥有自己的成员
    // 例如,我们通过Tclass<int>定义了T1,T2,T3,此时T1,T2,T3共享这个静态成员 
    // 与其他成员相同的是,只有我们使用时才会实例化
    // 不过与非模板类静态成员不同的是,我们可以通过类类型对象来访问一个类模板的static成员,也可以使用作用域运算符直接访问成员,当然为了通过类直接访问,我们需要使用特定的实例,例如 int t = Tclass<int>::flag;
    static int flag;
};

// 清空  定义
template<typename T>
void Tclass<T>::clear(){
    // 我们此处决定直接舍弃后面的值,无需调用析构,之后如果试图通过[]调用后面的对象,显然无效.
    siz = 0;
    return ;
}

// 对于定义在类外的成员模板必须为类模板和成员模板同时提供模板参数列表,类模板参数列表在前,模板成员的参数在后
// 
template<typename T>
template<typename FUNT>
void Tclass<T>::GetType(FUNT test){
    cout << typeid(test).name() << endl;
}

template<typename T>
class Templ{
    typedef int Tint;

};


// 一个类(无论是普通类还是类模板)可以包含本身是模板的成员函数,这种成员被称为成员模板,成员模板不能是虚函数
// 
class Clas{
public:
    Clas(){

    }

    template<typename T>
        void Test(T test){
            cout << typeid(test).name() << endl;
        }
};



// 我们无法用typedef为模板定义一个引用
// 但是新标准允许我们为类模板定义一个类型别名
template<typename T>
using Tname = std::map<T,T>;
// 此时我们定义Tname<int> IntMap ; IntMap 的类型为map<int,int>



// 也可以如下
template<typename T>
using Tname1 = std::map<T,int>;
// 此时我们定义Tname1<double> Double;   Double 的类型为map<double,int>
// 值得注意的是,如果我们使用了非类型模板参数,那么我们不能再指定其类型
// 例如我们的Double对象中,我们只能指定前面的T,而不能修改后面的int





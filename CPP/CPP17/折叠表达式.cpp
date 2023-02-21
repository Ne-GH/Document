/*********************************************************************
 * Auther : yongheng
 * Date : 2022/10/01 12:45
*********************************************************************/

class Val{
    int _val;
public:
    Val(int val){
        _val = val;
    }

    auto Get(){
        return _val;
    }

};


#include <iostream>

/*********************************************************************
 * 折叠表达式
*********************************************************************/
template <typename... T>
auto foldSum(T... args){
    /* return 后面的()是折叠表达式的一部分,不能省略 */
    /* 如果调用foldSum(47,11,val,-1);  -->  return 47 + 11 + val + -1*/
    /* 如果调用foldSum(std::string("hello") , "world" , "!")
     * --> return std::string("hello") + "world" + "!" */
    /*
     * args的位置十分重要,如果args在后面,会以 后递增式 展开
     * (... + args) ==> ((arg1 + arg2) + arg2) ...;     (推荐,左折叠从左向右求值,符合直觉)
     * 如果args在前面,会以前递增式展开
     * (args + ...) ==> (arg1 + (arg2 + arg3)) ...;
    */

    /*
     * 使用折叠表达式处理空参数包时,将遵循以下规则:
     * 如果使用了 && , 值为 true
     * 如果使用了 || , 值为 false
     * 如果使用了 逗号运算符 ,  值为 void
     * 使用所有其他运算符,都会引发格式错误
    */
    return (... + args);

    /*
     * 如果有一个初始值,以及一个参数包            (省略号两侧的op需要相同
     * return (value op ... op args)        二元左折叠       (推荐,如同推荐一元折叠使用左折叠一样
     * ==> (((value op arg1) op arg2) op arg3) op ...
     * return (args op ... op value)        二元右折叠
     * ==> arg1 op (arg2 op ... (argN op value))
    */

    /*
     * 可以对. -> [] 以外的二元运算符使用折叠表达式
     * (... , foo(args));
     * ==> foo(arg1) , foo(arg2) ...
     * (隐含问题,如果foo的返回类型重载了',' 代码的行为可能会改变,为了保证安全需要强转为void )
     * (... , (void)foo(args));
     * 对于逗号表达式,左折叠和右折叠没有什么区别,都会从左到右运算
    */
}

/*********************************************************************
 * 依次输出参数
*********************************************************************/
template<typename First, typename... Args>
void Print(First first,const Args& ... args){
    /* 实现1 */
    std::cout << first;
    (std::cout << ... << [](const auto& args) -> decltype(auto){
        std::cout << ' ';
        return args;
    }(args)) << "\n";

    /* 实现2 */
/*
    std::cout << first;
    auto outWithSpace = [](const auto &arg){
        std::cout << ' ' << arg;
    };
    (...,outWithSpace(args));
*/
}

int main(){

    Print("hello",std::string("world"),"!");


    return 0;
}
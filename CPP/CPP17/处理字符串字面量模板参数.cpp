/*********************************************************************
 * Auther : yongheng
 * Date : 2022/10/01 16:38
*********************************************************************/


#include <iostream>

template<const char *str>
class Message{
public:
    Message(){
        std::cout << str << std::endl;
    }
};

extern const char hello[] = "hello world";  /* 外部链接 */
const char hello11[] = "hello world c++11";        /* 内部链接 */

void foo(){
    Message<hello> msg;                 /* ok,所有cpp标准 */
    Message<hello11> mes1;               /* C++11 后ok */


    static const char hello17[] = "hello world c++17";
    Message<hello17> msg17;             /* C++17 后ok */


    // Message<"hello"> msgerr;         /* error */
}

/*********************************************************************
 * 该特性解决了C++11 起的一个问题,即C++11可以把指针作为模板实参,
 * 但是不能使用返回指针的编译期函数作为模板实参,C++17之后可以了
 * 此处不再给出代码演示
*********************************************************************/
int main(){

    foo();



    return 0;
}
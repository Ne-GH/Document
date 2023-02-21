/*
*    Time: 02/13/23 16:11:54
*    Create By yongheng
*/

#include <iostream>
#include <any>
using namespace std;

void Demo() {
    std::any a;                     // a为空
    std::any b = 4.3;               // a为double，值为4.3
    a = 42;                         // a为int,值为42
    b = std::string{"hi"};          // a 为string,值为"hi"
    b = "hii"s;

    if (a.type() == typeid(std::string)) {
        auto s = std::any_cast<std::string>(a);
        auto ss = std::any_cast<std::string&>(a);

        // any_cast的参数可以是any对象，也可以是any对象的地址 \
        此时转换的结果是一个相应类型的指针
        auto sss = std::any_cast<std::string>(&a);
    }
    else if (a.type() == typeid(int)) {
        auto num = std::any_cast<int>(a);
    }

    try {
//        auto s = std::any_cast<std::string>(a);
        int num = std::any_cast<int>(a);
    }
    // 如果any_cast 转换失败，会抛出std::bad_any_cast
    catch (std::bad_any_cast& e) {
        std::cerr << "EXCEPTION: " << e.what() << std::endl;
    }


    if(auto p = std::any_cast<string>(&a);p != nullptr){
    }
    // 同理
    if(auto p = std::any_cast<std::string>(&a)){
    }


    // 清空 Any对象
    a = std::any{};
    a = {};
    // 先检查是否有值
    if(a.has_value()){
        a = {};
    }
    a.reset();

    // 存储值类型时会发生退化（数组转指针，顶层引用和const被忽略）
    std::any aa = "hello";
    if(aa.type() == typeid(const char*)){
        cout << "aa is const char *" << endl;
        // true
    }
    else if (aa.type() == typeid(std::string)) {
        // false
    }

    std::any as = "hello"s;
    if(as.type() == typeid(const char*)){
        // false
    }
    else if (as.type() == typeid(std::string)) {
        cout << "as is string" << endl;
        // true
    }


}

int main(int argc,char *argv[]){

    Demo();


    return 0;
}

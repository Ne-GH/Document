/*
*    Time: 02/13/23 15:08:03
*    Create By yongheng
*/

#include <iostream>
#include <variant>

using namespace std;

/*******************************************************************************
 * variant 用于代替union
 * 空variant、有引用成员的variant、有C风格数组成员的variant、有不完全类型（例如void）的variant都不被允许
*******************************************************************************/
void Demo() {
    std::variant<int,std::string> var{"hi"};    // 初始化为string
    std::cout << var.index() << "\n";
    var = 42;
    std::cout << var.index() << "\n";

    try {
        int num = std::get<0>(var); // 通过索引访问
        cout << num << endl;
        var = "string";
        std::string s = std::get<std::string>(var); // 通过类型访问
        cout << s << endl;
    }
    catch (const std::bad_variant_access& e) {
        std::cerr << "EXCEPTION: " << e.what() << "\n";
    }
}

int main(int argc,char *argv[]){

    Demo();



    return 0;
}

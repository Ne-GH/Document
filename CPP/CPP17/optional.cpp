/*
*    Time: 02/12/23 01:19:11
*    Create By yongheng
*/

#include <iostream>
#include <algorithm>
#include <optional>
#include <string>
using namespace std;

/*******************************************************************************
 * 可选的返回值
 * 将string转为int,如果不可转换，则返回std::nullopt
*******************************************************************************/
std::optional<int> StringToInt(const string &string_number){
    try {
        return stoi(string_number);
    }
    catch (...) {
        return std::nullopt;
    }
}
void StringToIntDemo() {
    // 可选的返回值
    for (auto str : {"123"," 077","hello", "0x33","3x3"}) {
        std::optional<int> oi = StringToInt(str);
        if (oi) {
            // cout << "string to int is :" << *oi << endl;
            // 使用value() 在该对象没有值的时候会抛出异常 std::bad_optional_access
            cout << "string to int is :" << oi.value() << endl;
        }
        else {
            cout << "can't string to int" << endl;
        }
    }
}


/*******************************************************************************
 * 可选的参数和数据成员
*******************************************************************************/
class Name {
private:
    std::string _first;
    std::optional<std::string> _middle;
    std::string _last;
public:
    Name (std::string first,
          std::optional<std::string> middle,
          std::string last)
          : _first(first) ,_middle(middle), _last(last) {

    }

    friend std::ostream& operator << (std::ostream& out,const Name& name){
        out << name._first << ' ';
        if (name._middle) {
//            out << name._middle.value() << ' ';
            out << *name._middle << ' ';
        }
        // if 可改写为 \
        out << name._middle.value_or(""); \
        value_or 返回值，value返回引用
        out << name._last;
        return out;
    }
};

void NameDemo() {
    Name n {"jim",std::nullopt,"Knopf"};
    std::cout << n << std::endl;

    Name nn {"Donald","Ervin","Knuth"};
    std::cout << nn << std::endl;
}
int main(int argc,char *argv[]){

//    StringToIntDemo();

    NameDemo();


    return 0;
}


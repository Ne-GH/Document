/*
*    Time: 02/22/23 18:18:55
*    Create By yongheng
*/

#include <iostream>
#include <format>

using namespace std;


int main(int argc,char *argv[]){


// format 中转义字符为{和}，不再是 '\'
    std::cout << std::format("\{{}}") << std::endl;






    return 0;
}

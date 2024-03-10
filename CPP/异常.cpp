/*******************************************************************************
 * author : yongheng
 * date   : 2024/03/10 23:16
*******************************************************************************/

#include <iostream>

class MyException : public std::exception {
public:
    const char *what()  const throw() {
        return "this is my exception";
    }

};

int main() {
    try {
        throw MyException();
    }
    catch (MyException &me) {
        std::cerr << me.what() << std::endl;
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }


    return 0;
}

#include <iostream>

using namespace std;


int main(){

    int success = 10;
    // i 的作用域在整个if,then,else部分都有效,在整个if语句结束的时候i的析构函数会被调用
    if(int i = 10,j = 1000;i != success){
        cout << i << endl;
    }
    else{
        cout << i << endl;
    }
    // i,j 不再有效
    

    switch (int fork = 100;fork) {
        case 10:
            ;
        break;

        default:
            ;
        break;
    }



    return 0;
}

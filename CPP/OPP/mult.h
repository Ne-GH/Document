#include <iostream>

using std::cin;
using std::cout;
using std::endl;

class base{
public:
    base(){
        cout << "base" << endl;
    }
    ~base(){
        cout << "~base" << endl;
    }
    int m = 10;
};
class base1:public virtual base{
public: 
    base1(){
        cout << "base1" << endl;
    }
    ~base1(){
        cout << "~1" << endl;
    }
    int i = 1;
};

class base2:public virtual base{
public:
    base2(){
        cout << "base2" << endl;
    }
    ~base2(){
        cout << "~2" << endl;
    }
    int j = 2;
};
class base3{
public:
    base3(){
        cout << "base3" << endl;
    }
    ~base3(){
        cout << "~3" << endl;
    }
    int k = 3;
};

class T:public virtual base1,public virtual base2,public base3{
public:
    T(){
        cout << i << " " << j << " " << k << endl;
        i = 10;
    }

};


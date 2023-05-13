#include <iostream>
using namespace std;

int Result;
template<int N>
class Fibonacci{
public:
    enum{Result = Fibonacci<N-1>::Result + Fibonacci<N-2>::Result};
};

template<>
class Fibonacci<1>{
public:
    enum{Result = 1};
};
template<>
class Fibonacci<0>{
public:
    enum{Result = 0};
};

int main(){

    int i = 20;
    cout << Fibonacci<20>::Result << endl;
    cout << Fibonacci<30>::Result << endl;


    return 0;
}

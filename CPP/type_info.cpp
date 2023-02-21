#include <iostream>
#include <typeinfo>
using namespace std;

int main(){

    int num;
    typeid(num).name();
    cout << typeid(num).hash_code() << endl;

    return 0;
}

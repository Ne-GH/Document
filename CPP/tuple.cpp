#include <iostream>
#include <tuple>

using namespace std;

typedef tuple<int,double> MA;

MA make(int t1,double t2){
    return make(t1,t2);
}
int main(){

    tuple<int,long,double>t1;
    cout << "t1:" << get<2>(t1) << endl;;
    tuple<int,long,double>t2(1,2,3.0);
    cout << "t2:" << get<2>(t2) << endl;;

    // tuple<int,long,double>t3 = {1,2,4.0}; // 错误
    tuple<int,long,double>t3{1,2,4.0};
    cout << "t3:" << get<2>(t3) << endl;;

    auto t4 = make_tuple(1,2,4.0);
    cout << "t4:" << get<2>(t4) << endl;

    // <
    if(t1 < t2) 
        cout << "t1 < t2 is ok" << endl;
    else
        cout << "t1 < t2 is not" << endl;

    // == 
    if(t3 == t4)
        cout << "t3 == t4 is ok" << endl;
    else
        cout << "t3 == t4 is not" << endl;

    auto te = MA(1,2.0);
    cout << "te:" << get<1>(te) << endl;


    return 0;
}

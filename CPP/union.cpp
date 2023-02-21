#include <iostream>

using namespace std;


static union {
    char C;
    int I;
    double D;
};

union Union{
    Union(){
        cout << "Union" << endl;
    }
    ~Union(){
        cout << "~Union" << endl;
    }

    int INT;
    double Double;
};
int main(){

    Union U;
    U.INT = 10;
    cout << U.INT << endl;

    return 0;
}

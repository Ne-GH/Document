#include <iostream>

using namespace std;

class W{
public:
    class N{
    public:
        int num = 10;
    };
    W(){
        N n;
        cout << n.num << endl;
    }

};

int main(){
    W w;


    return 0;
}

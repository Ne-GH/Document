#include <iostream>
#include <string>
#include <bitset>
using namespace std;

int main(){


    bitset<16>bitset1(0xffff);
    bitset<16>bitset2("1000");
    string s("111000");
    // 从s[2]开始的2个二进制位
    bitset<16>bitset3(s,2,2);
    // 使用s的后4位
    bitset<16>bitset4(s,s.size()-4);
    cout << bitset4.to_string() << endl;
    cout << bitset4.to_ullong() << endl;

    // 若在编译时 bitset 的大小未知，则可使用 std::vector<bool>

    return 0;
}

/*
*    Time: 02/13/23 17:07:29
*    Create By yongheng
*/

#include <iostream>
#include <cstddef>      // std::byte
using namespace std;

/*******************************************************************************
 * byte的实现大小和unsigned char 一样，这意味着不保证是8bit,可能会更多
*******************************************************************************/
void Demo() {
    std::byte b1 {0x3f};
    std::byte b2 {0b111'0000};

    std::byte b3[4] {b1,b2,byte{1}}; // b3[3] 是 0
    if(b1 == b3[0]) {
        b1 <<= 1;
    }
    cout << std::to_integer<int>(b1);

}

int main(int argc,char *argv[]){

    Demo();



    return 0;
}

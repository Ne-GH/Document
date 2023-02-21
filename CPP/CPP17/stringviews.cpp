/*
*    Time: 02/13/23 17:19:11
*    Create By yongheng
*/

#include <iostream>
#include <optional>
#include <charconv>
#include <string_view>
using namespace std;

optional<int> StringToInt(string_view sv) {
    int val;
    auto [ptr,ec] = std::from_chars(sv.data(),sv.data()+sv.size(),val);
    if(ec != std::errc{}) {
        return std::nullopt;
    }
    return val;
}

void Demo() {
    char arr[] = "1234567";
    string_view stringview(arr,5);
    cout << stringview << endl;
    for (auto ch : stringview) {
        cout << ch << ' ';
    }
    cout << endl;


    // string中的substr时间复杂度为o（n），string_view 的时间复杂度为o（1）
    stringview.substr(0,3);

    // remove_suffix：从后面缩小大小
    // remove_prefix：从前面缩小大小
    stringview.remove_prefix(1);
    stringview.remove_prefix(2);

}



int main(int argc,char *argv[]){

    Demo();

    return 0;
}

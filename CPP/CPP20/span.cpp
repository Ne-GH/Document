#include <iostream>
#include <span>
#include <vector>


// span只是视图，仅维护首地址和长度信息

void Print(std::span<auto> arr) {
    std::cout << "len is : " << arr.size() << '\n';
    for (const auto &i : arr) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    std::cout << std::endl;
}


int main() {

    int arr[] = {1,2,3,4,5,6};
    Print<int>(arr);

    std::vector<int> vec = {6,5,4,3,2,1};
    Print<int>(arr);

    return 0;
}

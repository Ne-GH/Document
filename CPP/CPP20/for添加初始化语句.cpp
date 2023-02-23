#include <iostream>
#include <vector>
int main() {

	// 范围for添加初始化语句
	for (std::vector<int> vec{ 1,2,3,4,5,6 }; auto& num : vec) {
		// ...
	}

	return 0;
}
#include <iostream>
#include <ranges>

int main() {

	auto vec = { 0,1,2,3,4,5,6,7,8,9 };
	auto even = [](int i) { return i % 2 == 0; };
	auto square = [](int i) { return i * i; };

	// filter中是需要满足的条件,transform中是需要进行的变换
	// 更多限定操作请参考cppreference的ranges
	for (int i : vec | std::views::filter(even) | std::views::transform(square)) {
		std::cout << i << std::endl;
	}

	

	return 0;
}
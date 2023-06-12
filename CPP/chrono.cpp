#include <iostream>
#include <chrono>
#include <iomanip>

using namespace std;

long long func(long long n) {
	if (n < 2)
		return n;
	return func(n - 1) + func(n - 2);
}


int main() {

	// 1 小时
	chrono::hours H(1);
	// 1 毫秒
	chrono::milliseconds MS(1);
	// 1 微秒
	chrono::microseconds MCS(1);


	// 获取当前时间
	auto tp = chrono::system_clock::now();

	
	std::cout << "当前系统时间: " << tp.time_since_epoch().count() << endl;
	
	time_t now = chrono::system_clock::to_time_t(tp);
	std::cout << "当前时间(time_t): " << now << endl;
	std::cout << put_time(localtime(&now), "%Y-%m-%d %H:%M:%S") << endl;
	

	// 统计运行时间
	auto start = chrono::steady_clock::now();
	func(42);
	auto end = chrono::steady_clock::now();

	// ratio<one,two>中的内容为自定义时间单位
	// 即一秒 增加two / one
	// 默认为ratio<1>, 可省略
	chrono::duration<double,milli> times = end - start;
	std::cout << "函数func运行时间为: " << times.count() << "ms" << endl;

    func(43);
	chrono::duration<double> scends_times = end - start;
	std::cout << "运行时间为: " << scends_times.count() << "s" << endl;

	// time_point
	auto timepoint = chrono::system_clock::now();






	return 0;
}

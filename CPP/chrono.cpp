#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <chrono>

using namespace std;

long long func(long long n) {
	if (n < 2)
		return n;
	return func(n - 1) + func(n - 2);
}


int main() {

	// 1 Сʱ
	chrono::hours H(1);
	// 1 ����
	chrono::milliseconds MS(1);
	// 1 ΢��
	chrono::microseconds MCS(1);


	// ��ȡ��ǰʱ��
	auto tp = chrono::system_clock::now();

	
	std::cout << "��ǰϵͳʱ��: " << tp.time_since_epoch().count() << endl;
	
	time_t now = chrono::system_clock::to_time_t(tp);
	std::cout << "��ǰʱ��(time_t): " << now << endl;
	std::cout << put_time(localtime(&now), "%Y-%m-%d %H:%M:%S") << endl;
	

	// ͳ������ʱ��
	auto start = chrono::steady_clock::now();
	func(42);
	auto end = chrono::steady_clock::now();

	// ratio<one,two>�е�����Ϊ�Զ���ʱ�䵥λ
	// ��һ�� ����two / one
	// Ĭ��Ϊratio<1>, ��ʡ��
	chrono::duration<double,milli> times = end - start;
	std::cout << "����func����ʱ��Ϊ: " << times.count() << endl;


	// time_point
	auto timepoint = chrono::system_clock::now();






	return 0;
}
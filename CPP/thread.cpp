#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

long long func(long long n) {
	
	if (n < 2)
		return n;
	return func(n - 1) + func(n - 2);

	
}


int main() {
	int n = 42;
	// �̺߳���Ϊfunc,����Ϊn,��ֵ
	thread t1(func,n);
	// ͬt1,���ǲ�������Ϊ����
	
	thread t2(func, ref(n));

	
	// t3 ����func,t2�������߳�
	thread t3(move(t2));
	
	thread::id id1 = t1.get_id();
	thread::id id3 = t3.get_id();
	cout << "thread 1 id : " << id1 << endl;
	cout << "thread 3 id : " << id3 << endl;

	cout << "thread 1 handle: " << t1.native_handle() << endl;
	cout << "֧�ֵĲ����߳���" << t1.hardware_concurrency() << endl;

	// t1.join();
	// Detach �̡߳� ����ǰ�̶߳����������ִ��ʵ������̶߳�����룬ʹ���̵߳�ִ�п��Ե������С�һ���߳�ִ����ϣ������������Դ���ᱻ�ͷš�
	t1.detach();
	// ��鵱ǰ���̶߳����Ƿ��ʾ��һ�����ִ���߳�,�Ƿ�ɱ�join
	if (t2.joinable()) {
		t2.join();
	}
	// ����������ǰ�߳�,ϵͳ������һ�̼߳���ִ��
	this_thread::yield();
	t3.join();

	auto t = chrono::system_clock::now();
	// using std::chrono::milliseconds;
	auto s = t + 20s;
	// �߳�������ĳ��ָ����ʱ��(time point)�����̲߳ű����»��ѡ�
	this_thread::sleep_until(s);

	// �߳�����ĳ��ָ����ʱ��Ƭ(time span)�����̲߳ű����»���
	chrono::seconds sf(10);
	this_thread::sleep_for(sf);


	return 0;
}
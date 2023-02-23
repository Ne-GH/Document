#include <iostream>
#include <string>

class Person {
	int _age;
	std::string _name;

public:

	Person() = default;
	~Person() = default;
	Person(int age, std::string name) : _age(age), _name(name) {  }




	// 如果默认生成则会生成< <= > >= ==,根据==会生成!=
	// auto operator<=>(const Person& right) const = default;
	
	// 自定义仅会生成< <= > >=
	// <=> 有三种类型的结果
	// strong_ordering: less(小于),equivalent(等价,f(a)==f(b)),equal(等于),greater(大于)
	// weak_ordering: less,equivalent(f(a)可能不等于f(b)),greater
	// partial_ordering: less ,equivalent(f(a)可能不等于f(b)),greater,unordered(不可比较)
	// strong可隐式转换为weak和partial,weak可隐式转换为partial,该隐式转换仅可单向转换
	auto operator <=>(const Person& right) const {
		if (_age < right._age)
			return std::strong_ordering::less;
		else if (_age == right._age)
			return std::strong_ordering::equal;
		else
			return std::strong_ordering::greater;
	}

	auto operator == (const Person& right) const {
		if (_age == right._age && _name == right._name) {
			return true;
		}
		else {
			return false;
		}
	}
};


int main() {
	Person p1{ 10,"Z" }, p2{20,"W"};

	std::cout << "p1 < p 2" << ((p1 < p2) ? "true" : "false") << std::endl;
	std::cout << "p1 <= p2 " << ((p1 <= p2) ? "true" : "false") << std::endl;
	std::cout << "p1 > p2 " << ((p1 > p2) ? "true" : "false") << std::endl;
	std::cout << "p1 >= p2 " << ((p1 >= p2) ? "true" : "false") << std::endl;
	std::cout << "p1 == p2 " << ((p1 == p2) ? "true" : "false") << std::endl;
	std::cout << "p1 != p2 " << ((p1 != p2) ? "true" : "false") << std::endl;
	

	return 0;
}

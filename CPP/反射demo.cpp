#include <iostream>
#include <string>
#include <map> 
#include <stdexcept>

struct Person {
	int age;
	std::string_view name;
};

// name , 偏移, sizeof
std::map<std::string_view, std::pair<std::size_t, std::size_t>> FieldInfo = {
	{
		{"age",{offsetof(Person,age),sizeof(int)}},
		{"name",{offsetof(Person,name),sizeof(std::string_view)}}
	}
};


void setattr(Person* point, std::string_view name, void* data) {
	if (!FieldInfo.contains(name)) {
		throw std::runtime_error("field not found");
	}
	auto& [offset, size] = FieldInfo[name];
	std::memcpy(reinterpret_cast<char*>(point) + offset, data, size);
}




int main() {

	Person person = { 1,"小明" };
	int age = 10;
	std::string_view name = "小宏";
	setattr(&person, "age", &age);
	setattr(&person, "name", &name);
	std::cout << person.age << " " << person.name << std::endl;


}

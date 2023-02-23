#include <iostream>
#include <format>
#include <chrono>

// 第一个T是自己定义的类型,第二个CharT是为了能支持char和string
/*
template <typename T,typename CharT = char>
class formatter {

	// 解析格式,可通过继承获得
	template <typename FormatContext>
	constexpr auto parse(FormatContext& fc);

	// 通常将内容输出到fc.out()
	template<typename FormatContext>
	auto format(const T& v, FormatContext& fc);

};
*/

class Person {
	std::string _name = "";
	int _age = 0;
public:
	Person(int age, std::string name) : _age(age), _name(name) {  };
	std::string GetName() const {
		return _name;
	}
	int GetAge() const {
		return _age;
	}
};


// 此处用struct,如果使用class 需公开继承并将方法设置为公开
template<>
struct std::formatter<Person> :std::formatter<std::string> {
	template<typename FormatContext>
	auto format(const Person& person,FormatContext& fc) {
		std::format_to(fc.out(), "Name is :");
		std::formatter<string>::format(person.GetName(), fc);
		return std::format_to(fc.out()," Age is {}", person.GetAge());
	}
};




int main() {
	
	// format可选第一个参数为locale，如果存在将使用本地环境特定的格式化

	// {{ }} 分别被替换为 { }
	std::cout << std::format("{{}}") << std::endl;


	int age = 10;
	std::string name = "ZhangSan";
	// Error,因为format的格式化需是常量
	//std::string format = "Name:{},Age:{}";
	//std::cout << std::format(format, name, age) << std::endl;
	
	// format_to 第一个参数是迭代器,之后的参数和format相同
	std::string str = "Name is : ";
	std::format_to(std::back_inserter(str), "{}", name);
	std::cout << str << std::endl;




	// 替换域格式
	// 开始‘{’
	// 可选arg-id,一个非复数，args-id表示args中参数的下标，如果指定必须全部指定，如果忽略必须全部忽略
	// 可选‘:’，后面跟随格式说明，基本类型和标准字符串使用标准格式说明，日期和时间使用chrono格式说明，用户定义类型由用户定义的std::formatter特化决定
	// 终止‘}’
	// 最后一个字符串会被忽略，与printf相同，不再赘述
	std::cout << std::format("{} {}!", "Hello","world", "None") << std::endl;
	std::cout << std::format("{0:+},{0:-},{0: }", 1) << std::endl;
	// 对于不合法的格式化字符串，会抛出std::format_error异常

	// 填充与对齐（可选）：‘{’或‘}’以外的字符，后跟‘<’（左对齐）、‘>’（右对齐）或‘^’（居中）
	// 符号（可选）：+（非负数前插入+）、-（符号仅用于负数，默认行为）、空格（负数使用负号，正数前置空格），
	// #（可选）：转换，对于整数，0b、0、0x分别表示2进制、8进制、16进制，浮点数可用g、G
	// 0（可选）：前导0填充
	// 宽度（可选）：宽度若存在则指定最小宽域
	// 精度（可选）：仅用于浮点和字符串，浮点型不在赘述，对于字符串，表示最多输出几个字符
	// L(可选)：本地环境特定的格式化，仅用于算数类型
	// 类型（可选）：详细参阅 cppreference.com


	Person ps(10, "LiSi");
	std::cout << std::format("{:*^20}", ps) << std::endl;
	

	// 添加对chrono的支持
	auto cur_time = std::chrono::system_clock::now();
	std::cout << "当前时间为: " << std::format("{:%Y-%m-%d %T}",cur_time) << std::endl;
	// 时间间隔
	auto count = std::chrono::minutes(100) + std::chrono::minutes(55);
	std::cout << std::format("{:%H:%M:%S}", count) << std::endl;
	


	return 0;
}



// 这是一个可以传递参数给自定义类型的demo
/*
#include <format>
#include <iostream>
#include <string>
#include <ranges>

class Person {
 public:
  int age;
  std::string name;
};

template <>
struct std::formatter<Person> {
  std::string_view fmt_str;

  template<typename ParseContext>
  constexpr auto parse(ParseContext& ctx) {
    auto begin = ctx.begin();                       // ctx is "x}{:*^10}"
    auto it = std::formatter<int>{}.parse(ctx);     // now, it point to "}{:*^10}"
    it = std::ranges::find(it + 1, ctx.end(), ':'); // now, it point to ":*^10}"
    ctx.advance_to(it + 1);                         // now, ctx is "*^10}"
    it = std::formatter<std::string>{}.parse(ctx);  // now, it point to "}"
    fmt_str = {begin - 2, it + 1};                  // now fmt_str is "{:x}{:*^10}"
    return it;
  }

  template <typename FormatContext>
  auto format(const Person& p, FormatContext& ctx) const {
    return std::vformat_to(ctx.out(), fmt_str, std::make_format_args(p.age, p.name));
  }
};

int main() {
  Person p{ 30,"John Doe" };
  std::cout << std::format("{:x}{:*^10}", p) << '\n';
  std::cout << std::format("The age is {:}, and the name is {: ^5}", p) << '\n';
}
*/
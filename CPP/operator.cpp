#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
/*******************************************************************************
* 重载运算符应被定义为普通非成员函数还是成员函数规则,如下:
* 赋值(=),下标([]),调用(()),和成员访问箭头(->)运算符必须是成员
* 复合赋值运算符一般应该是成员,但是并非必须~
* 改变对象状态的运算符或者与给定类型密切相关的运算符,自增++,自减--,解引用*,成员访问运算符.通常应该是成员函数
* 具有对称性的运算符可以转换到任意一端的运算对象,例如算术,相等性,关系和位运算符等,因此他们通常应该是普通的非成员函数
*******************************************************************************/

class Person {
    int age_{};
    std::string name_;
public:
    Person(const int age, const std::string_view name) : age_(age), name_(name) {
        std::cout << "构造函数" << std::endl;
    }
    ~Person() {
        std::cout << "析构函数" << std::endl;
    }

    Person(const Person &other) : age_(other.age_), name_(other.name_) {  }

    Person(Person &&other) noexcept : age_(other.age_), name_(std::move(other.name_)) {  }

    Person &operator = (const Person &other) {
        age_ = other.age_;
        name_ = other.name_;
        return *this;
    }

    Person &operator = (Person &&other) noexcept {
        age_ = other.age_;
        name_ = std::move(other.name_);
        return *this;
    }


    explicit operator std::string() const {
        return name_;
    }
    explicit operator int() const {
        return age_;
    }

    Person &operator ++ () {
        ++age_;
        return *this;
    }
    Person operator ++ (int) {
        Person tmp = *this;
        ++age_;
        return tmp;
    }
    Person &operator -- () {
        --age_;
        return *this;
    }
    Person operator -- (int) {
        Person tmp = *this;
        -- age_;
        return tmp;
    }

    Person &operator * () {
        return *this;
    }
    Person * operator -> () {
        return this;
    }

    // + - += -= () [],实现略过,此处仅为展示delete使用
    void operator +  (const Person&) = delete;
    void operator -  (const Person&) = delete;
    void operator += (const Person&) = delete;
    void operator -= (const Person&) = delete;


    void* operator new (const size_t size) {
        auto p = static_cast<Person *>(::malloc(size));
        if (p == nullptr) {
            std::get_new_handler()();
            throw std::bad_alloc();
        }
        return p;
    }
    void operator delete(void *p) {
        ::free(p);
        return;
    }
    void* operator new[] (const size_t size) {
        auto p = static_cast<Person *>(::malloc(size));
        if (p == nullptr) {
            std::get_new_handler()();
            throw std::bad_alloc();
        }
        return p;
    }
    void operator delete[] (void *p) {
        free(p);
        return;
    }




    void show() & {
        std::cout << "&" << std::endl;
    }
    void show() && {
        std::cout << "&&" << std::endl;
    }
    void show() const & {
        std::cout << "const &" << std::endl;
    }
    void show() const && {
        std::cout << "const &&" << std::endl;
    }

    friend std::ostream &operator << (std::ostream &os, const Person &p) {
        os << p.age_ << ' ' << p.name_;
        return os;
    }


    /*******************************************************************************
      强序（Strong Ordering）: 对于任意两个元素 a 和 b，如果 a < b，则不可能有 b < a。
      弱序（Weak Ordering）: 可能存在 a < b 和 b < a 的情况。在这种情况下，两个元素被认为是等价的，但不一定是相等的。
    *******************************************************************************/
    /*******************************************************************************
      如果定义了 operator==，那么编译器会自动生成不等运算符。
      类似地，如果定义了三路比较运算符 operator<=>，那么编译器会自动生成四个关系运算符, < <= > >=
      如果定义 operator<=> 为default ，那么编译器会生成 operator== 和 operator<=>
    *******************************************************************************/
    auto operator <=> (const Person &other) const {
        if (const auto cmp = std::strong_order(age_, other.age_); cmp != nullptr)
            return cmp;
        return std::strong_order(other.name_, name_);
    }
    bool operator == (const Person &other) const {
        return name_ == other.name_ && age_ == other.age_;
    }
};

Person operator ""_person(const char *str,std::size_t len){
    // ... 使用的时候就是"xiaoming"_person
    return Person(0,str);
}


int main () {


    std::vector<Person> vec{
        {2,"x"},
        {2,"xiaoming"},
        {1,"John"}
    };

    std::ranges::sort(vec);
    for (const auto & person : vec) {
        std::cout << person << '\n';
    }




    return 0;
}

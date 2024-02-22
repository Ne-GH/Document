#include <iostream>
#include <memory>


class T {
    std::string str;
public:
    T(std::string arg) : str(arg) {
        std::cout << str << "构造函数" << std::endl;
    }

    ~T() {
        std::cout << str << "析构函数" << std::endl;
    }
};




std::unique_ptr<T> RetUniquePtr() {
    return std::make_unique<T>("ret");
}

// unique_ptr 对持有的堆内存具有唯一控制权，引用计数永远为1，unique_ptr对象销毁时会释放其持有的堆内存
void UniquePtr() {

    std::unique_ptr<T> p1(new T("p1"));
    std::unique_ptr<T> p2{ new T("p2")};

    p2.reset(new T{"p3"});

    auto p4 = std::make_unique<T>("p4");
     
    // unique_ptr类型禁止拷贝
    // auto p5 = p4; error

    // 但是通过函数返回的unque_ptr可以,移动构造函数
    auto ret_ptr = RetUniquePtr();

    auto move_ptr(std::move(ret_ptr));
    if (ret_ptr == nullptr) {
        std::cout << "move了ret_ptr,该指针已经为空" << std::endl;
    }

    std::unique_ptr<int[]> arr_p1(new int[10]);
    std::unique_ptr<int[]> arr_p2;
    arr_p2.reset(new int[10]);

    std::unique_ptr<int[]> arr_p3(std::make_unique<int[]>(10));

    auto df = [](T *) {
		std::cout << "deletor func" << std::endl;
        };
    
    // 如果指定了deletor ，则调用deletor(p),而不是delete p，这意味着不会调用p的析构函数
    std::unique_ptr<T,decltype(df)> pp(new T("deletor"), df);
}


class ShareT : public std::enable_shared_from_this<ShareT> {
    std::string str;
public:
    ShareT(std::string arg) : str(arg) {
        std::cout << str << "构造函数" << std::endl;
    }
    ~ShareT() {
        std::cout << str << "析构函数" << std::endl;
    }
    // 返回自身的std::share_ptr对象需要继承std::enable_shared_form_this<>
    std::shared_ptr<ShareT> GetSelf() {
        return shared_from_this();
    }
};


class ShareTT : public std::enable_shared_from_this<ShareTT> {
    std::string str;
    std::shared_ptr<ShareTT> sp;
public:
    ShareTT(std::string arg) : str(arg) {
        std::cout << str << "构造函数" << std::endl;
    }
    ~ShareTT() {
        std::cout << str << "析构函数" << std::endl;
    }
    void func() {
        sp = shared_from_this();
    }

};

void SharePtr() {
    // 初始化方式和unique_ptr相同
    std::shared_ptr<T> p1(new T("p1"));
    // reset时，之前持有的资源会被释放
    p1.reset(new T("p2"));

    std::shared_ptr<T> p3 = std::make_shared<T>("p3");
    std::cout << "计数：" << p3.use_count() << std::endl;
    auto p4(p3);
    std::cout << "计数：" << p3.use_count() << std::endl;
    {
		auto p5 = p3;
		std::cout << "计数：" << p3.use_count() << std::endl;
    }
	std::cout << "计数：" << p3.use_count() << std::endl;


    /*
        当一个类继承自 std::enable_shared_from_this 时，在其内部会包含一个隐藏的 weak_ptr 对象。

		当类的实例被构造为 std::shared_ptr 所管理时，该 weak_ptr 会与这个 std::shared_ptr 关联起来。

		当调用对象的 shared_from_this() 方法时，它会尝试根据与当前对象关联的 weak_ptr 对象来获取一个新的 std::shared_ptr。

		如果当前对象不是通过 std::shared_ptr 管理的，调用 shared_from_this() 将会导致未定义的行为，因为此时 weak_ptr 对象为空。
    */
    std::shared_ptr<ShareT> sp1(new ShareT("sp1"));
    auto sp2 = sp1->GetSelf();
    std::cout << "ShareT 计数" << sp1.use_count() << std::endl;

    ShareT stt("stt");
    // auto sp3 = st.GetSelf(); error
    std::endl(std::cout);
    auto spp = new ShareT("spp");
    // spp->GetSelf(); error




    auto sttp = std::make_shared<ShareTT>("ShareTT");
    // sttp->func();   // error,循环引用，引用计数永远为1，内存泄露
}


// 用来解决share_ptr的循环引用问题
void WeakPtr() {
    // weak_ptr可以从share_ptr或weak_ptr构造
    std::shared_ptr<T> sp(new T("sp"));
    std::cout << sp.use_count() << std::endl;
    // weak_ptr不增加引用计数
    std::weak_ptr<T> wp(sp);
    std::cout << sp.use_count() << std::endl;
    // lock会增加引用计数
    auto spp = wp.lock();
    std::cout << spp.use_count() << std::endl;


    std::weak_ptr<T> sp1;
    {
        std::shared_ptr<T> tmp_share(new T("tmp"));
        sp1 = tmp_share;
        if (sp1.expired()) {
            std::cout << "资源不存在" << std::endl;
        }
        else {
            std::cout << "资源存在" << std::endl;
            sp1;
        }

        // or
        if (auto share = sp1.lock()) {
            *share;     // 访问资源
        }
        else {
            std::cout << "资源不存在" << std::endl;
        }


    }
	if (sp1.expired()) {
		std::cout << "资源不存在" << std::endl;
	}




}



int main() {
    UniquePtr();    
    std::endl(std::cout);
    std::endl(std::cout);
    std::endl(std::cout);
    SharePtr();

    std::endl(std::cout);
    std::endl(std::cout);
    std::endl(std::cout);

    WeakPtr();

    // unique_ptr和裸指针大小相同
    // share_ptr 和 weak_ptr的大小是unique的两倍
    std::cout << sizeof(T*) << std::endl;
    std::cout << sizeof(std::unique_ptr<T>) << std::endl;
    std::cout << sizeof(std::shared_ptr<T>) << std::endl;
    std::cout << sizeof(std::weak_ptr<T>) << std::endl;

    // get方法可以获取智能指针的原始指针



    return 0;
}

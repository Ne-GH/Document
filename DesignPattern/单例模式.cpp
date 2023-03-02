/*
*    Time: 03/02/23 23:35:02
*    Create By yongheng
*/
#include <mutex>
#include <memory>
#include <iostream>

/*
 * 1.私有化构造函数
 * 2.静态成员指向唯一实例
 * 3.公有方法获取唯一实例
 */

// 非线程安全
class One {

    One(){};
    One(const One&);
    One& operator=(const One&);
public:
    static One& GetInstance() {
        static std::unique_ptr<One> instance(new One);
        return *instance;
    }
};

// 线程安全
class OneMutex {
    OneMutex(){};
    OneMutex(const OneMutex &);
    OneMutex& operator=(const OneMutex&);

public:
    static OneMutex& GetInstance() {
        static std::mutex mutex;
        std::lock_guard<std::mutex> lock(mutex);
        static std::unique_ptr<OneMutex> instance(new OneMutex);
        return *instance;
    }

};

int main(int argc,char *argv[]){




    return 0;
}

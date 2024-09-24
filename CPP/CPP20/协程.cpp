
#include <coroutine>
#include <iostream>
#include <thread>
#include <future>
import Mouse;

struct Promise : std::coroutine_handle<> {
    struct promise_type {
        int value;
        Promise get_return_object() {
            return {std::coroutine_handle<promise_type>::from_promise(*this)};
        }

        // 协程函数执行开始时调用该函数
        // 返回值可控制是否一开始就挂起
        std::suspend_never initial_suspend() noexcept {
            return {};
        }

        /*******************************************************************************
         * 协程体执行完成或者抛出异常之后会先清理局部变量，接着调用该函数来方便开发者自行处理其他资源的销毁
         * 该函数也可以返回一个等待体使得当前携程挂起，但之后当前协程应通过 coroutine_handle的destroy销毁而不是使用resume
        *******************************************************************************/
        std::suspend_always final_suspend() noexcept {
            return {};
        }
        /*******************************************************************************
         * 协程体的返回值 ，不返回时是 void return_void()
         * 有返回值时是 void return_value(T value)
         * co_return 100,其中100作为参数进入函数return_value
         * 该值可保存到promise_type中
        *******************************************************************************/
        void return_void() {  }

        /*******************************************************************************
         * 协程体抛出异常时调用该函数
        *******************************************************************************/
        void unhandled_exception() {  }

        std::suspend_always yield_value(int val) {
            value = val;
            return {};

        }
    };

    // 此处通过继承获取，无需手动定义该成员变量
    // std::coroutine_handle<promise_type> handle;

};


/*******************************************************************************
 * co_await 返回类型要求实现指定接口
 * co_yield 没有返回类型要求，只要能调用yield_value()即可
*******************************************************************************/
struct AwaitType {
    int return_value;
    // 返回 false 表示会暂停
    bool await_ready() noexcept {
        return false;
    }
    /*******************************************************************************
     * co_await 暂停后会调用该函数
     * 函数内部通过参数 handle 观察暂停的协程
     * 且该函数负责调度它以在某个执行器上恢复
    *******************************************************************************/
    void await_suspend(std::coroutine_handle<> handle) {
        std::async([=]() {
            std::this_thread::sleep_for(std::chrono::seconds(2));
            handle.resume();
        });
    }

    // 该函数的返回值即 co_await 返回的值
    int await_resume() noexcept {
        return return_value;
    }
};

int main(int argc, char* argv[])
{

    auto lambda = []() -> Promise {
        std::cout << "first output" << std::endl;
        co_await AwaitType{ .return_value = 1000 };
        std::cout << "finish output" << std::endl;
    };
    auto promise = lambda();

    std::cout << "main" << std::endl;

}

// 编译命令如下：
// g++ main.cpp test.cpp -std=c++20 -fmodules-ts
// 第一次编译会因为不存在gcm.cache文件夹导致编译失败，再次执行上述命令即可

// 创建一个模块test
export module test;

auto _Hello() {
    return "Hello";
}

// 导出函数Hello,使之在外部可见
export auto Hello() {
    return _Hello();
}

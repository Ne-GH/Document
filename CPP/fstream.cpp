#include<iostream>
#include<fstream>
#include <istream>
#include <iterator>
#include <string>
#include <strstream>
using namespace std;


std::string func1(std::filesystem::path path) {
    std::ifstream file(path);
    file.unsetf(std::ios::skipws);
    return std::string(std::istream_iterator<char>(file), std::istream_iterator<char>());
}
std::string func2(std::filesystem::path path) {
    std::ifstream file(path);
    return std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
}
std::string func3(std::filesystem::path path) {

    std::ifstream file(path, std::ios::binary | std::ios::ate);

    auto length = file.tellg();
    file.seekg(std::ios::beg);
    std::string ret(length, 0);
    file.read(&ret[0], length);
    
    return ret;
}
std::string func4(std::filesystem::path path) {
    std::ifstream file(path);
    std::stringstream ss;
    ss << file.rdbuf();
    return std::string(ss.str());
}
std::string func5(std::filesystem::path path) {
    std::string ret,tmp;
    std::ifstream file(path);
    while (std::getline(file, tmp)) {
        ret += tmp + '\n';
    }
    return ret;
}




int main() {


    // 输出
//    get             提取字符
//    peek            读取下一个字符，但不会提取它
//    unget           撤销上一个字符的提取
//    putback         往输入流中放置一个字符
//    getline         持续提取字符，直到找到给定字符
//    ignore          持续提取并丢弃字符，直到找到给定字符
//    read            提取一块字符
//    readsome        提取可用的若干块字符
//    gcount          返回上次无格式输入操作提取的字符数量

//    // 输入
//    tellg           返回输入位置指示器
//    seekg           设置输入位置指示器
//    put             插入字符
//    write           插入字符块
//    seekdir         寻位方向类型
//    fill            管理填充字符
//    imbue           设置本地环境
//    rdbuf           管理相关的流缓冲区
//    tie             管理绑定的流
//    narrow          窄化字符
//    widen           拓宽字符
//    flags           管理格式标志
//    setf            设置特定格式标志
//    unsetf          清除特定格式的标志
//    precision       管理浮点操作的精度
//    width           管理域的宽度
//    imbue           设置本地环境
//    getloc          返回当前本地环境


//    文件保护方式选择项：
//    filebuf::openprot;　　　//默认的兼容共享方式
//    filebuf::sh_none;　　　 //独占，不共享
//    filebuf::sh_read;　　　 //读共享
//    filebuf::sh_write;　　　//写共享

//    bool rdstate();               返回流的当前状态标志字
//    bool eof();                   返回非0值表示到达文件尾
//    bool fail();                  返回非0值表示操作失败
//    bool bad();                   返回非0值表示出现错误
//    bool good();                  返回非0值表示流操作正常
//    bool clear(int flag=0);       将流的状态设置为flag
//    tellp()                       返回输出位置指示器
//    seekp()                       设置输出位置指示器
//    tellg()                       返回输入位置指示器
//    seekg()                       设置输入位置指示器
//    flush()                       刷新缓冲区

//    ios::in 	                    打开文件用于读取数据。如果文件不存在，则打开出错。
//    ios::out 	                    打开文件用于写入数据。如果文件不存在，则新建该文件；如果文件原来就存在，则打开时清除原来的内容。
//    ios::app 	                    打开文件，用于在其尾部添加数据。如果文件不存在，则新建该文件，且无论怎么组合都是不存在时创建(每次写入都是追加形式)。
//    ios::ate 	                    打开一个已有的文件，并将文件读指针指向文件末尾。如果文件不存在，则打开出错(初次打开时为追加，之后可以修改)。
//    ios::trunc                    打开文件时会清空内部存储的所有数据，单独使用时与 ios::out 相同。
//    ios::binary 	                以二进制方式打开文件。若不指定此模式，则以文本模式打开。
//    ios::nocreate                 文件不存在时产生错误，常和in或app联合使用
//    ios::noreplace (C++23) 	    以独占模式打开,文件存在时产生错误，常和out联合使用
//    ios::in | ios::out            打开已存在的文件，既可读取其内容，也可向其写入数据。文件刚打开时，原有内容保持不变。如果文件不存在，则打开出错。
//    ios::in | ios::out  	        打开已存在的文件，可以向其写入数据。文件刚打开时，原有内容保持不变。如果文件不存在，则打开出错。
//    ios::in | ios::out | ios::trunc 	fstream 	打开文件，既可读取其内容，也可向其写入数据。如果文件本来就存在，则打开时清除原来的内容；如果文件不存在，则新建该文件。
    fstream file("filename",std::ios::app);

    std::ifstream input_file("filename");
    input_file.unsetf(ios::skipws); // 关闭input_file的忽略空格标志，
                                   // 如果没有,则无法读入空格(默认使用 >> 读入)
    string file_data((istream_iterator<char>(input_file)),istream_iterator<char>());
    // 默认使用 >> 进行格式化输入，效率较低

    ifstream input__file("filename");
    string file__data((istreambuf_iterator<char>(input__file)),istreambuf_iterator<char>());
    // 无需设置unset(ios::skipws),istreambuf_iterator默认不忽略任何字符，只是获取下一个字符




}


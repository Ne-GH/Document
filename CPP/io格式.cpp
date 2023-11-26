#include <ios>
#include <iostream>
#include <iomanip>
using namespace std;
int main(){

    // 改变bool输出状态
    cout << true << " " << false << endl;
    // 向cout写入输出状态
    cout << boolalpha;
    cout << true << " " << false << endl;
    //复原
    cout << noboolalpha;
    cout << true << " " << false << endl;

    // 改变整型输出状态,不会改变浮点型等类型输出
    // 16进制 8进制 10进制
    cout << hex << 1023 << endl;
    cout << oct << 1023 << endl;
    cout << dec << 1023 << endl;
    // 显示进制前缀
    // uppercase 以大写显示十六进制中的数
    cout << showbase;
    cout << hex << 1023 << endl;
    cout << oct << 1023 << endl;
    // 关闭进制显示
    // nouppercase 关闭以大写显示十六进制中的数
    cout << noshowbase;

    // 浮点数
    cout << "当前精度" << cout.precision() << " " ;
    cout << 1.23456789 << endl;
    // 改变当前精度
    cout.precision(3);
    cout << "当前精度:" << cout.precision() << " " << 1.23456789 << endl;
    // 更改当前精度,注意区分precision 和 setprecision的用法
    cout << "设置精度为10:" << setprecision(10) << 1.23456789 << endl;

    


    // 后缀0
    cout.precision(12);
    cout << showpoint << 1.23456789 << endl;
    cout << noshowpoint;

    cout << setprecision(2);
    cout << "当前精度:" << cout.precision() << " " << 1.23456789 << endl;

    // 可以读取空白符
    char ch;
    cin >> noskipws;
    cin >> ch;
    cout << "'" << ch << "'" << endl;;
    // 丢弃空白符
    cin >> skipws;


    
    return 0;
}

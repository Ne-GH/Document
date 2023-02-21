#include <iostream>
#include <regex>
using namespace std;

int main(){

    string pattern("[^c]ei");
    // alpha   单个字母
    pattern = "[[:alpha:]]*" + pattern + "[[:alpha:]]*";
    regex r(pattern);
    smatch results;

    string test_str = "receipt freind theif receive";

    // 将正则表达类r应用于范围test_str上,结果存储在results内
    if(regex_search(test_str,results,r))
        cout << results.str() << endl;

    // it 指示一个范围和一个regex,之后开始匹配,指向一个位置
    // end_it 是空的sregex_iterator 起尾后迭代器作用
    for(sregex_iterator it(test_str.begin(),test_str.end(),r),end_it;
        it != end_it; ++it
        ){
        cout << it->prefix().str() << "   >>>"; 
        cout << it->str() ;
        cout << "<<<   " << it->suffix().str() << endl;
    }

    string str;
    // 数字及字母
    regex regex2("([[:alnum:]]+)+\\.(cpp|Cxx|cC)$",regex::icase);
    smatch smatch2;
    string fmt = "文件名为:$1";
    while(cin >> str){
        // if(regex_search(str,smatch2,regex2)){
            // 第一个子表达式的结果是完整的匹配,下标为0
            // cout << smatch2.str(0) << " ";

            // 第二个子表达式的结果是第一个子表达式部分,下标为1
            // cout << smatch2.str(1) << endl;
        // }
        // cout << regex_replace(str,regex2,fmt) << endl;
        // 不匹配则不输出
        cout << regex_replace(str,regex2,fmt,regex_constants::format_no_copy) << endl;
    }

    return 0;
}

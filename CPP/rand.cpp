/*
 * rand的缺点:
 *     很多程序需要使用不同范围的随机数,想应用需要随机浮点数,一些程序需要非均匀分布的数
 * 而程序员为了解决这种问题会试图转换rand生成的随机数的范围,类型或分布,这样会引入非随机性
 *     所以为了解决这一问题,C++不应该使用rand,而应当使用random中的随机数引擎类和随机数分布类
 */

#include <iostream>
#include <random>
#include <vector>

using namespace std;

unsigned getrand(){
    default_random_engine e;
    return e();
}
int main(){

    // 标准库定义了多个随机数引擎类,区别在于性能和随机性质量不同
    // 随机数引擎类,可以随机生成unsigned
    // 使用1作为种子
    // 与rand类似的,对于给定的发生器,每次运行时会返回相同的数值序列
    default_random_engine e(1);
    // 调用对象可以生成一个unsigned
    cout << e() << endl;
    // 重置引擎状态
    // e.seed();
    // cout << e() << endl;
    // 将引擎状态推进10步
    e.discard(10);
    cout << e() << endl;


    // 随机数分布类
    // 0-9 随机分布
    uniform_int_distribution<unsigned> u(0,9);
    // 0-1 的随机浮点数
    uniform_real_distribution<double> du(0,1);
    cout << u(e) << endl;
    cout << du(e) << endl;

    // 如果存在一个局部的随机数发生器,那么应该将其定义为static的,此处不演示(应该比较好理解,static之后就不会在离开函数作用域后释放)
    auto T1 = getrand();
    auto T2 = getrand();
    if(T1 == T2)
        cout << "==" << endl;
    else
        cout << "!=" << endl;


    // 生成不平均的随机数
    // 均值为4,标准差为1.5
    normal_distribution<> n(4,1.5);
    vector<unsigned>arr(9);
    for(int i = 0;i < 200; ++i){
        int num = n(e);
        if(num < arr.size())
            arr[num]++;
    }

    for(int i = 0;i < arr.size(); ++i){
        cout << i << ":";
        for(int j = 0;j < arr[i]; ++j){
            cout << "*";
        }
        cout << endl;
    }


    // bool 分布的随机类,返回bool类型,true和false的概率默认为0.5
    // 可以如下指定为true的概率
    bernoulli_distribution bo(0.90);
    int bools[2] = {0};
    for(int i = 0;i < 200; ++i){
        bools[bo(e)] ++;
    }
    cout << "true:" << bools[0] << endl;
    cout << "false" << bools[1] << endl;

    return 0;
}

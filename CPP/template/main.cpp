#include "Tclass.h"

    // 当模板被使用时才会实例化意味着,相同的实例可能出现在多个对象文件中,在大的系统中
    // 在多个文件中实例化相同模板的额外开销可能非常严重
    // 在新标准中(C++11)我们可以通过显式实例化来避免额外开销
    // 编译器遇到 extern 声明时,不会在本文件中生成实例化代码
    // 将一个实例化声明为extern意味着承诺程序的其他位置有该实例的一个非extern的生命(定义)
    // 对于一个给定的实例化版本,可能有多个extern声明,但是只需要有一个定义
    // 并且由于编译器在使用一个模板时自动实例化,因此extern声明需要出现在任何使用此实例化版本的代码之前
    // extern template class Tclass<int>;      // 实例化声明
    // template class Tclass<int>;              // 实例化定义
    // 此处如果使用上面的extern声明将导致程序中不存在Tclass<int>的实例化代码,进而编译错误,而使用实例化定义则不会有影响
    

int main(){

    Tclass<int> nums;
    // 插入
    nums.insert(1);
    // size
    cout << nums.size() << endl;
    // 数组中第一个数据
    cout << nums[0] << endl;



    // 成员模板
    Clas Tclas;
    int int1;
    Tclas.Test(int1);
    Tclas.Test(nums);

    nums.GetType(int1);
    nums.GetType(nums);
    



    return 0;
}

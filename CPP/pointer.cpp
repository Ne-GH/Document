#include <iostream>

using namespace std;

class Node{
public:
    Node(){
        cout << "NODE" << endl;
    }
    ~Node(){
        cout << "~NODE" << endl;
    }


    int num = 10;

    void Nodefun(){
        cout << "NODE_FUN" << endl;
    }
};
int main(){

    // 指向成员数据
    int Node:: *p;
    p = &Node::num;

    Node node;
    Node* pnode = &node;
    int Node:: *autop = &Node::num;

    auto s= node.*autop;
    auto ps = pnode->*autop;
    cout << typeid(s).name() << endl;
    cout << s << endl;
    pnode->*autop = 100;
    cout << node.*autop << endl;
    cout << node.num << endl;


    // 指向成员函数
    auto pfun = &Node::Nodefun;
    (node.*pfun)();

    // 前面的()必不可少,因为调用运算符的优先级更高
    void (Node::* pf)() = &Node::Nodefun;
    (node.*pf)();

    using PFUN = 
        void (Node:: *)();

    PFUN usingp = &Node::Nodefun;
    (node.*usingp)();
    return 0;
}

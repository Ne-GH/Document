#include <cstddef>
#include <cstdlib>
#include <iostream>

using namespace std;

class Node{
public: 
    Node(){
        cout << "构造" << endl;
    }
    ~Node(){
        cout << "~析构" << endl;
    }
    int arr[10];

    void* operator new(std::size_t size) noexcept {
        cout << "重载的new" << endl;

        if(void *p = malloc(size)){
            return p;
        }
        else
            return nullptr;
    }
    void* operator new(std::size_t size,void *ptr) {
        std::cout << "重载的布置函数" << std::endl;
        return ptr;
    }

    void operator delete(void *p){
        std::cout << "重载的delete函数" << std::endl;
        free(p);
    }
};
int main(){
    Node *p = (Node *)Node::operator new(sizeof(Node));
    p = new (p)Node;
    delete p;






    return 0;
}

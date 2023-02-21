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

    void* operator new(unsigned long size_t){
        cout << "重载的new" << endl;

        if(void *p = malloc(size_t)){
            return p;
        }
        else
            return NULL;
    }

    void operator delete(void *p){
        free(p);
    }
};
int main(){
    Node *p = (Node *)Node::operator new(sizeof(Node));





    return 0;
}

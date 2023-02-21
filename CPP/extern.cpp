#include <iostream>

using namespace std;

extern "C"{
#include <stdio.h>
    void fun(){

       int num; 
       int *p = &(num = 10);
    }
}

int main(){

    fun();

    return 0;
}

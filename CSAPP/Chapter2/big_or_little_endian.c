/*
 *    Time: 04/09/22 08:49:23
 *    Create by yongheng
 */

#include <stdio.h>
#include <stdint.h>

typedef unsigned char*   byte_pointer;

void show_bytes(byte_pointer start,size_t len){
    size_t i;
    for(i = 0;i < len; ++i){
        printf("%.2x ",start[i]);
    }
    putchar(10);
}

void show_int(int x){
    show_bytes((byte_pointer)&x, sizeof(int));
}

void show_float(float x){
    show_bytes((byte_pointer)&x, sizeof(float));
}

void show_pointer(void *x){
    show_bytes((byte_pointer)&x, sizeof(void *));
}

void test_show_bytes(int val){
    int ival = val;
    float fval = (float)val;
    int *pval = &ival;
    show_int(ival);
    show_float(fval);
    show_pointer(pval);
}

int main(int argc,char *argv[]){

    test_show_bytes(0x12341234);

    show_bytes("abcdef", 7);


    return 0;
}

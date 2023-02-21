/*
 *    Time: 04/09/22 15:08:18
 *    Create by yongheng
 */

#include <stdio.h>

void inplace_swap(int *x,int *y){
    *x ^= *y;
    *y ^= *x;
    *x ^= *y;
}

void print(int *arr,int len){
    for(int i = 0;i < len; ++i)
        printf("%d ",arr[i]);
    putchar(10);
}


int main(int argc,char *argv[]){
    

    int odd_nums[] = {1,2,3,4,5};
    int odd_len = sizeof(odd_nums)/sizeof(int);

    int even_nums[] = {1,2,3,4,5,6};
    int even_len = sizeof(even_nums)/sizeof(int);

    for(int i = 0;i < odd_len/2 ; ++i)
        inplace_swap(&odd_nums[i], &odd_nums[odd_len-i-1]);

    print(odd_nums, odd_len);

    for(int i = 0;i < even_len/2; ++i)
        inplace_swap(&even_nums[i], &even_nums[even_len-i-1]);

    print(even_nums, even_len);

    /*
     * page 39 
     * topic 2.12
     */
    printf("\n\n\n\npage 39.\ntopic 2.12\n");
    int x = 0x87654321;
    printf("%X\n",x&0xff);
    printf("%X\n",x^0xffffff00);
    printf("%X\n",x|0xff);
        

    return 0;
}

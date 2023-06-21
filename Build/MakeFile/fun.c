#include <stdio.h>

int arr[10] = {0,1,2,3,4,5,6,7,8,9};

void printarr(int *arr){
    for(int i = 0;i < 10; ++i){
        printf("%d ",arr[i]);
    }
}

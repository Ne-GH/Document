#include "Array.h"
#include <stdio.h>

int main(){
    struct Array_int arr = ARRAY_ININT;
    
    arr.Insert(&arr,100);
    arr.Insert(&arr,200);
    for(int i = 0;i < arr.size; ++i){
        printf("%d\n",arr.arr[i]);
    }

    arr.Free(&arr);

    struct Array_int vector = ARRAY_ININT;
    vector.Insert(&vector,10);
    vector.Insert(&vector,100);
    for(int i = 0;i < vector.size; ++i){
        printf("%d\n",arr.arr[i]);
    }


    arr.Free(&vector);

    
    struct Array_int array = ARRAY_ININT;

    for(int i = 0;i < 10; ++i){
        array.Insert(&array,i);
    }

    array.Delete(&array,3);

    return 0;
}

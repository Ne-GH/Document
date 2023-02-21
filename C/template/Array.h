#ifndef _Array_H
#define _Array_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


struct Array_int{
    int size;
    int *arr;

    
    // 
    bool (*Insert)(struct Array_int *,int);
    void (*Free)(struct Array_int *);
    void (*Delete)(struct Array_int *,int);
};
bool Insert(struct Array_int *arrp,int num){
    arrp->size ++;
    arrp->arr = (int *)realloc(arrp->arr,sizeof(int)*arrp->size);
    arrp->arr[arrp->size-1] = num;
    return true;
}
void Delete(struct Array_int *arrp,int pos){
    for(int i = pos; i < arrp->size-1; ++i){
        arrp->arr[i] = arrp->arr[i + 1];
    }
    arrp->size --;
    arrp->arr = (int *)realloc(arrp->arr,arrp->size*sizeof(int));
    return;
}
void Free(struct Array_int *arrp){
   free(arrp->arr);     
   return;
}



const struct Array_int ARRAY_ININT = {
    0,
    NULL,
    Insert,
    Free,
    Delete
};



#endif






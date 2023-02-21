#include <stdio.h>
#include <stdlib.h>

#define cout(n) printf("%d ",n)
#define coutend() putchar(10)

int cmp(const void *p1,const void *p2){
    return *((int *)p1) - *((int *)p2);
}
int arr[] = {123,34,52,4,124,5,43,5,234,235,234,5,345,345,34,563,467,457,2123};


int ThreeSelect(int l,int r,int val){

    int Tl = (r-l+1) / 3 + l;
    int Tr = (r-l+1)*2 / 3 + l; 
    /* cout(Tl); */
    /* putchar(' '); */
    /* cout(Tr); */
    /* putchar(Tr); */
    if(val == arr[Tl])
        return Tl;
    if(val == arr[Tr])
        return Tr;

    if(val < arr[Tl])
        return ThreeSelect(l, Tl - 1, val);
    else if(val < arr[Tr] && val > arr[Tl])
        return ThreeSelect(Tl + 1, Tr - 1, val);
    else
        return ThreeSelect(Tr + 1, r , val);
}

int main(){
    
    qsort(arr, 18, sizeof(int), cmp);

    for(int i = 0;i < 18; ++i){
        printf("%4d",arr[i]);
    }
    coutend();

    
    for(int i = 0;i < 18; ++i){
        printf("%4d",ThreeSelect(0, 17, arr[i]));
        fflush(stdout);
    }
    putchar(10);
    /* printf("%d\n",ThreeSelect(0, 17, arr[7])); */

    return 0;
}

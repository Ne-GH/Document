/* #include <dlfcn.h> */
#include <stdio.h>

void Print();
int main(){

    /* Print(); */

    /* void *sop = dlopen("/lib/libmeso.so",RTLD_LAZY); */
    /* if(sop == NULL){ */
        /* printf("Cant open so file\n"); */
        /* return 0; */
    /* } */

    Print();



    /* dlclose(sop); */
    return 0;
}

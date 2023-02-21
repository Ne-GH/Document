#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <threads.h>
#include <time.h>
#include <stdatomic.h>
#define MAX 10000000L

/* _Atomic long count = 0; */
long count = 0;

mtx_t mtx;
int Add(){
    for(long i = 0;i < MAX; ++i){
        mtx_lock(&mtx);
        ++ count;
        mtx_unlock(&mtx);
    }
    return 0;
}

int Dec(){
    for(long i = 0;i < MAX; ++i){
        mtx_lock(&mtx);
        -- count;
        mtx_unlock(&mtx);
    }
    return 0;
}

int main(){
    clock_t cl = clock();


    thrd_t th1,th2;
    /* mtx_init(&mtx, mtx_plain); */
    thrd_create(&th1, Add,NULL);
    thrd_create(&th2, Dec,NULL);

    thrd_join(th1, NULL);
    thrd_join(th2, NULL);

    printf("%ld\n",count);
    printf("CPU:%ldms\n",(clock()-cl)*1000L/CLOCKS_PER_SEC);



    return 0;
}

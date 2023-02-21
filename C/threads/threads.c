#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <threads.h>
#include <unistd.h>

tss_t key;

// 线程存储对象,对象的存储周期等于线程的运行时间,在一个线程内表达式里面的线程对象,将引用这个对象在当前线程的本地实例
thread_local int val = 10;
int Print(void *num){
    for(int i = 0;i < 10; ++i){
        usleep(10);
        printf("Print:%d\n",val);
        val ++;
    }
    /* for(int i = 0;i < 10; ++i){ */
        /* printf("Print:%d\n",*(int *)num); */
        /* (*(int *)num)++; */
    /* } */
    return *(int *)num;
}

int Printf(void *num){
    for(int i = 0;i < 10; ++i){
        usleep(10);
        printf("Printf:%d\n",val);
        val *= 2;
    }
    /* for(int i = 0;i < 10; ++i){ */
        /* printf("Printf:%d\n",*(int *)num); */
        /* (*(int *)num)++; */
    /* } */
    return *(int *)num;
}

void PrintData(){
    for(int i = 0;i < 5; ++i){
        printf("%s\n",(char *)tss_get(key));
        usleep(10);
    }
}
int Data1(void *str){
    size_t len = strlen(str) + 1;
    tss_set(key, malloc(len));
    strcpy((char *)tss_get(key), str);
    PrintData();
    return 0;
}
int Data2(void *str){
    size_t len = strlen(str) + 1;
    if(tss_set(key, malloc(len)) != thrd_success)
        return -1;
    strcpy((char *)tss_get(key), str);
    PrintData();
    return 0;
}
void DeleteData(void * p){
    printf("DeleteData:%s\n",(char *)p);
    free(p);
    return;
}

int main(){

    thrd_t th1,th2;
    int num = 0;
    thrd_create(&th1, Print,&num);
    thrd_create(&th2, Printf,&num);

    int temp = 0;
    thrd_join(th1, &temp);
    printf("join1:%d\n",temp);
    thrd_join(th2, &temp);
    printf("join2:%d\n",temp);
    

    tss_create(&key, DeleteData);
    thrd_t thstr1,thstr2;
    thrd_create(&thstr1,Data1,"Data1");
    thrd_create(&thstr2,Data1,"Data2");

    thrd_join(thstr1, NULL);
    thrd_join(thstr2, NULL);

    tss_delete(key);

    

    return 0;
}

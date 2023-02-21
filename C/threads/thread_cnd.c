#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <threads.h>
#include <time.h>

typedef struct{
    int *data;              // 指向数据数组的指针
    size_t size,count;      // 元素数量的最大值和当前值
    size_t tip,tail;        // tip = 下一个空点的索引
    mtx_t mtx;              // 一个互斥
    cnd_t cndPut,cndGet;    // 两个条件变量
} Buffer;

bool bufInit(Buffer *bufptr,size_t size){
    if((bufptr->data = malloc(size * sizeof(int))) == NULL)
        return false;
    bufptr->size = size;
    bufptr->count = 0;
    bufptr->tip = bufptr->tail = 0;
    return mtx_init(&bufptr->mtx, mtx_plain) == thrd_success
        && cnd_init(&bufptr->cndPut) == thrd_success
        && cnd_init(&bufptr->cndGet) == thrd_success;
}
void bufDestroy(Buffer *bufptr){
    cnd_destroy(&bufptr->cndPut);
    cnd_destroy(&bufptr->cndGet);
    mtx_destroy(&bufptr->mtx);
    free(bufptr->data);
}

bool bufPut(Buffer *bufptr ,int data){
    mtx_lock(&bufptr->mtx);

    // 缓冲区中元素的数量      缓冲区大小
    while(bufptr->count == bufptr->size)
        // 如果缓冲区满了,就阻塞,并唤醒一个等待条件变量endPut的线程
        if(cnd_wait(&bufptr->cndPut, &bufptr->mtx) != thrd_success)
            return false;

    bufptr->data[bufptr->tip] = data;
    // 缓冲区的顶
    bufptr->tip = (bufptr->tip + 1) % bufptr->size;
    ++ bufptr->count;


    mtx_unlock(&bufptr->mtx);
    // 从等待指定条件变量的任意数量线程中唤醒其中一个
    cnd_signal(&bufptr->cndGet);
    return true;
}

// 从缓冲区中移除一个元素
// 最多等待sec秒
bool bufGet(Buffer *bufptr,int *dataPtr,int sec){
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);    // 获得当前时间
    ts.tv_sec += sec;               // +sec 秒延时


    mtx_lock(&bufptr->mtx);
    // 如果缓冲区为空
    while(bufptr->count == 0)
        if(cnd_timedwait(&bufptr->cndGet, 
                         &bufptr->mtx,
                         &ts) != thrd_success)
            return false;

    // 拿到data中的第tail个元素,存如dataPtr中
    *dataPtr = bufptr->data[bufptr->tail];
    // tail 后移
    bufptr->tail = (bufptr->tail + 1) % bufptr->size;
    -- bufptr->count;

    mtx_unlock(&bufptr->mtx);
    cnd_signal(&bufptr->cndPut);

    return true;
}



#define NP 2            // 生产者数量
#define NC 3            // 消费者数量

// 线程函数的参数
struct Arg{
    int id;
    Buffer *bufptr;
};

// 函数声明符_Noreturn 指定函数不能通过执行return语句或到达函数体的末尾来返回,和noreturn相同,noreturn在stdnoreturn.h
_Noreturn void errorExit(const char *msg){
    fprintf(stderr, "%s\n", msg);
    exit(0xff);
}
int producer(void *arg){
    struct Arg *argPtr = (struct Arg *)arg;
    int id = argPtr->id;
    Buffer *bufptr = argPtr->bufptr;
    int count = 0;

    for(int i = 0;i < 10; ++i){
        int data = 10 * id + i;
        if(bufPut(bufptr, data)){
            printf("生产者id:%d\tdata:%d\n",id,data);
            ++ count;
        }
        else{
            fprintf(stderr, "生产者id:%d\tdata%d\n",id,data);
            return -id;
        }
    }
    return count;
}
int consumer(void *arg){
    struct Arg *argPtr = (struct Arg *)arg;
    int id = argPtr->id;
    Buffer *bufptr = argPtr->bufptr;

    int count = 0;
    int data = 0;
    while(bufGet(bufptr, &data, 2)){
        ++ count;
        printf("消费者id:%d\tdata:%d\n",id,count);
    }
    return count;
}

int main(){
    
    printf("生产者-消费者演示\n");

    Buffer buf;
    bufInit(&buf, 5);

          // 生产者,消费者
    thrd_t prod[NP],cons[NC];

    struct Arg prodArg[NP],consArg[NC];
    
    for(int i = 0;i < NP; ++i){
        prodArg[i].id = i + 1;
        prodArg[i].bufptr = &buf;
        if(thrd_create(&prod[i], producer, &prodArg) != thrd_success)
            errorExit("线程错误\n");
    }

    for(int i = 0;i < NC; ++i){
        consArg[i].id = i + 1;
        consArg[i].bufptr = &buf;
        if(thrd_create(&cons[i],consumer,&consArg[i]) != thrd_success)
            errorExit("线程错误\n");
    }

    int res = 0;
    for(int i = 0;i < NP; ++i){
        thrd_join(prod[i], &res);
        printf("生产者%d\t 等待时间:%d\n",prodArg[i].id,res);
    }

    for(int i = 0;i < NC; ++i){
        thrd_join(cons[i], &res);
        printf("消费者:%d\t等待时间:%d\n",consArg[i].id,res);
    }

    bufDestroy(&buf);


    return 0;
}

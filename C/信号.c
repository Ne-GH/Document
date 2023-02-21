#include <stdio.h>

int main(){

    // 发送指定信号
    // int kill(pid_t pid,int signo)    // 发送给指定进程
    // int raise(int signo)             // 发送给自己
    // 这两个函数都是成功返回0,错误返回-1
   

    // abort函数使当前进程接收到信号而异常终止
    // void abort(void)


    // alarm函数可以通知内核在seconds后发送SIGALRM信号,该信号的默认动作是终止当前的进程,返回值是0或者是以前设定的闹钟时间还余下的秒数,seconds为0是,表示取消以前设定的闹钟,函数的返回值依然是之前设置的闹钟剩下的秒数
    // unsigned int alarm(unsigned int seconds)



    // 实际执行信号的处理动作叫做信号递达,信号从产生到递达之间的状态叫做信号未决,进程可以选择阻塞某个信号,被阻塞的信号将保持在未决状态,直到进程解除对此信号的阻塞,才执行递达的动作
    
    
    //sigset_t 类型对于每种信号用一个bit表示 有效 或 无效 状态,至于这个类型内部如果存储这些bit则依赖于实现,直接使用printf输出没有意义
/*  include <signal.h>
    int sigemptyset(sigset_t *set);
    int sigfillset(sigset_t *set);
    int sigaddset(sigset_t *set, int signo);
    int sigdelset(sigset_t *set, int signo);
    int sigismember(const sigset_t *set, int signo);


    函数sigemptyset初始化set所指向的信号集,使其中所有信号的对应bit清零,表示该信号集不包含任何有效信号.函数sigfillset初始化set所指向的信号集,使其中所有信号的对应bit置位,表示该信号集的有效信号包括系统支持的所有信号.注意，在使用sigset_t类型的变量之前，一定要调用sigemptyset或sigfillset做初始化，使信号集处于确定的状态。初始化sigset_t变量之后就可以在调用sigaddset和sigdelset在该信号集中添加或删除某种有效信号。这四个函数都是成功返回0，出错返回-1。sigismember是一个布尔函数，用于判断一个信号集的有效信号中是否包含某种信号，若包含则返回1，不包含则返回0，出错返回-1。 */

/* 
    include <signal.h>
    sigprocmask
    调用函数sigprocmask可以读取或更改进程的信号屏蔽字。sigpending

    int sigpending(sigset_t *set);
    sigpending读取当前进程的未决信号集，通过set参数传出。调用成功则返回0，出错则返回-1。
*/
 

    return 0;
}

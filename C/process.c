#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(){

    /* fork 根据一个现有的进程复制出一个新的进程,原来的进程作为父进程,新进程称为子进程 */

    /* Shell 下输入命令可以运行程序,以ls命令为例,过程如下:
     * fork复制新的Shell进程
     * 新的进程调用exec执行新的程序
     */

    /* 
     * 每次调用system 都是创建了子进程,彼此之间互不影响
     */
    system("cd ..");
    system("ls");

    system("cd ..;ls");


    /* printf PATH */
    /* libc 中定义的全局变量environ指向环境变量表,environ没有包含在任何头文件中,因此使用时要用extern声明 */
    extern char **environ;
    for(int i = 0;environ[i] != NULL; ++i){
        printf("%s\n",environ[i]);
    }

    /* 查看指定PATH的value */
    /* 找到时返回指向value的指针,否则返回NULL */
    printf("Getenv SHELL:%s\n",getenv("SHELL"));


    /* 修改指定PATH */

    /* 成功返回0,否则返回非0
     * 作用:将$name 设置为value
     * 如果name存在,rewrite为非0,覆盖原来的定义
     * 如果name存在,rewrite为0,不覆盖原来的定义,也不报错
     * int setenv(const char* name,const char *value,int rewrite) 
     *
     * 作用:删除name的定义,即使name没有定义,也不返回错误
     * void unsetnev(const char *name)
     */
    /* 通过setenv等函数的修改作用于当前程序的进程,当前程序的父进程不受影响,而不是像system一样作用于当前程序的子进程 */
    setenv("PATH", "NO...", 1);
    printf("Set PATH:%s\n",getenv("PATH"));
    /* fflush(stdout); */


    pid_t pid = fork();/* 父进程调用fork,这是一个系统调用,因此进入内核 */
    /* 内核根据父进程复制出一个子进程,父进程和子进程的PCB信息相同,用户态代码和数据也相同,但之后互不影响,因此子进程的状态和父进程相同,都是做完了初始化刚调用完fork(看起来有两个进程调用了fork并等待返回),还没从系统内核返回,至于哪个进程先被系统调度执行,取决于内核的调度算法 */
    char message[10] = {0};
    int n = 0;
    if(pid < 0){
        perror("fork failed");
        exit(1);
    }
    /* 如果某个时刻子进程被调度执行,从内核返回后就从fork函数返回,保存在变量PID中的返回值是0 */
    else if(pid == 0){
        sprintf(message, "%s", "Child");
        n = 600;
        /* sleep(1); */
    }
    /* 如果某个时刻父进程被调度执行,从内核返回后就从fork函数返回,保存在变量PID中的返回值是子进程的PID,是一个大于0的整数 */
    else {
        sprintf(message, "%s", "Parent");
        n = 300;
        /* sleep(1); */
    }

    for(int i = 0;i < n; ++i){
        printf("%s\n",message);
    }
    /* 关于fork返回值的补充:对于子进程来说,可以使用getpid来获得自己的pid,可以使用getppid来获得父进程的pid,但是对于父进程来说,想要访问子进程只能记录下fork的返回值 */
/* fork的另一个特性是所有由父进程打开的描述符都被复制到子进程中,父,子进程中相同编号的文件描述符在内核中指向同一个file结构体,也就是说,file结构体的引用计数要增加 */
    /* 由于这个程序是在Shell下运行的,因此Shell进程是父进程的父进程,父进程运行时Shell进程处于等待状态,当父进程终止时Shell进程认为命令执行结束了,于是打印Shell提示符,而事实上子进程这时还没结束,所以子进程的消息打印到Shell提示符的后面,这时用户可以正常输入命令,Shell也可以正常执行 */



    /* exec 函数 */
    /* 用fork创建子进程后执行的是和父进程相同的程序(有可能是不同的分支),子进程往往要调用一种exec函数来执行另一个程序,当一个进程调用exec函数时,该进程的用户空间代码和数据完全被新程序替换,从新程序的启动例程开始执行,调用exec不创建新进程,所以调用exec前后当前进程的PID不会改变*/
    /* execl,execv,execle,execve,execlp,execvp 中只有execve是系统调用,其他的五个函数最终都是调用execve实现的 */
    /*  
     * execlp 调用 execvp
     * execl 和execvp 调用 execv
     * execle 和 execv 调用 execve
     */
    
    // 结束子进程
    if(pid == 0)
        return 0;

    char *const ls_argv[] = {"ls","-a",NULL};
    char *const ls_envp[] = {"PATH=/bin:/usr/bin:","TERM=console",NULL};
    execl("/bin/ls", "ls","-a",NULL);


    /* 如果父进程结束,但是子进程还存在,那么就说这个进程是僵尸进程
     * 此时这些子进程的父进程改为init进程,这是一个特殊的进程,通常是/sbin/init ,进程id是1,在系统启动时负责启动各项系统服务,之后负责清理子进程,只要子进程终止,init就会调用wait函数清理他
     */

    /* 
    pid_t wait(int *status)
    pid_t waitpid(pid_t pid, int *status, int options);
    若调用成功则返回清理掉的子进程id，若调用出错则返回-1父进程调用wait或waitpid时可能会阻塞(如果它的所有子进程都还在运行)或者带子进程的终止信息立即返回（如果一个子进程已终止,正等待父进程读取其终止信息)也可能出错立即返回(如果它没有任何子进程)
    这两个函数的区别是：
    如果父进程的所有子进程都还在运行，调用wait将使父进程阻塞，而调用waitpid时如果在options参数中指定WNOHANG可以使父进程不阻塞而立即返回0
    wait等待第一个终止的子进程，而waitpid可以通过pid参数指定等待哪一个子进程
    可见，调用wait和waitpid不仅可以获得子进程的终止信息，还可以使父进程阻塞等待子进程终止，起到进程间同步的作用。如果参数status不是空指针，则子进程的终止信息通过这个参数传出，如果只是为了同步而不关心子进程的终止信息，可以将status参数指定为NULL。
    */




    /* 进程间通信IPC */
    /* 
     * 管道是最基本的IPC机制,由pipe函数创建
     * int pipe(int filedes[2])
     * filedes[0]指向管道的读端
     * filedes[1]指向管道的写端
     * 之后通过read(filedes[0])和write(filedes[1])来读写数据
     * 看起来像在进行文件操作,但实际是在操作内核缓冲区
     * 更详细得说:
     * 父进程在得到一个输入端和一个输出端并fork之后,子进程也得到了同样的输入端和输出端,此时父进程关闭读端口,子进程关闭写端口,这样以来,父进程可以向管道写数据,子进程可以从管道读数据,进而实现了进程间通信
     *
     * 值得注意的是,一个管道只能得到一个单向通信
     */


    return 0;
}

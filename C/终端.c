#include <stdio.h>
#include <unistd.h>

int main(){

    /* 每个进程可以通过/dev/tty访问他的控制终端
     * 每个终端都对应一个不同的设备文件
     * ttyname函数可以由文件描述符查出对应的文件名
     * 该文件描述符必须指向一个终端设备而不能是任意文件
     */

    printf("fd 0:%s\n",ttyname(0));
    printf("fd 1:%s\n",ttyname(1));
    printf("fd 2:%s\n",ttyname(2));
/* 
    一台PC通常只有一套键盘和显示器，也就是只有一套终端设备，但是可以通过Ctrl-Alt-F1~Ctrl-Alt-F6切换到6个字符终端，相当于有6套虚拟的终端设备，它们共用同一套物理终端设备，对应的设备文件分别是/dev/tty1~/dev/tty6，所以称为虚拟终端（Virtual Terminal）。设备文件/dev/tty0表示当前虚拟终端，比如切换到Ctrl-Alt-F1的字符终端时/dev/tty0就表示/dev/tty1，切换到Ctrl-Alt-F2的字符终端时/dev/tty0就表示/dev/tty2，就像/dev/tty一样也是一个通用的接口，但它不能表示图形终端窗口所对应的终端。
*/
    /* 终端登录过程:
     * 系统启动时,init进程根据文件/etc/inittab(不一定) 确定要打开哪些终端
     * 1:2345:respawn:/sbin/getty 9600 tty1
     * 不同的字段用:隔开,开头的1是这一行配置的id，通常要和tty的后缀一致，配置tty2的那一行id就应该是2。第二个字段2345表示运行级别2~5都执行这个配置。最后一个字段/sbin/getty 9600 tty1是init进程要fork/exec的命令，打开终端/dev/tty1，波特率是9600（波特率只对串口和Modem终端有意义），然后提示用户输入帐号。中间的respawn字段表示init进程会监视getty进程的运行状态，一旦该进程终止，init会再次fork/exec这个命令，所以我们从终端退出登录后会再次提示输入帐号。
     * getty根据命令行参数打开终端设备作为它的控制终端，把文件描述符0、1、2都指向控制终端，然后提示用户输入帐号。用户输入帐号之后，getty的任务就完成了，它再执行login程序
    execle("/bin/login", "login", "-p", username, (char *)0, envp);
    login程序提示用户输入密码（输入密码期间关闭终端的回显），然后验证帐号密码的正确性。如果密码不正确，login进程终止，init会重新fork/exec一个getty进程。如果密码正确，login程序设置一些环境变量，设置当前工作目录为该用户的主目录然后执行Shell：
    execl("/bin/bash", "-bash", (char *)0);
    注意argv[0]参数的程序名前面加了一个-，这样bash就知道自己是作为登录Shell启动的，执行登录Shell的启动脚本。从getty开始exec到login，再exec到bash，其实都是同一个进程，因此控制终端没变，文件描述符0、1、2也仍然指向控制终端。由于fork会复制PCB信息，所以由Shell启动的其它进程也都是如此。*/
    return 0;
}

//
// Created by zhang on 2022/9/8.
//

#ifndef ALGORITHM_CODE_PROCESS_CONTROL_H
#define ALGORITHM_CODE_PROCESS_CONTROL_H


/* exit
* getenv   查找环境变量
* putenv   扩充环境
* signal(sig, handler)
* kill(pid, sig)
* */
#include <stdlib.h>
/*
 * perror
 * popen    在shell中创建进程，运行命令并由管道返回结果
 * pclose   关闭管道
 * fgets    从指定的流读取一行
 * */
#include <stdio.h>

/*
 * pause    暂停进程
 * execl, fork, _exit()， sleep, getpid，
 * access   检查文件或文件夹的权限
 * setpgrp  创建进程组，并返回标识符
 * getpgrp  获取当前的进程组标识符
 * environ  环境变量指针， 并以 NULL 结束
 * chdir     改变进程当前目录
 * chroot   改变进程的根目录
 * nice     降低当前进程的优先级，只有超级用于可以增加
 * setsid   创建进程组
 * alarm
 * pause    暂停程序的运行，等待一个信号
 * pipe     建立管道
 * close    关闭写句柄或者读句柄
 * write    管道写入
 * read     管道读取
 * lseek    设置文件的偏移量
 * lockf    对文件进行上锁操作
 * */
#include <unistd.h>
#include <sys/wait.h>

/*
 * 限制进程资源的使用
 * */
#include <sys/time.h>
#include <sys/resource.h>

/*
 * 定义类型 uid_t, gid_t
 * */
#include <sys/types.h>

/*
 * umask    操作文件的掩码
 * */
#include <sys/stat.h>
#include <fcntl.h>  // 当调用exec时，关闭文件
//#include <strings.h>
#include <string.h>

/*
 * 对系统的log文件进行操作
 * */
#include <signal.h>
/*
 * openlog 打开log系统
 * */
#include <syslog.h>

/*
 * 当接收到一个信号时，希望能跳回程序中以前的一个位置执行
 * setjmp   保存程序中的当前位置
 * longjmp  把控制转回到被保存的位置
 * */
#include <setjmp.h>


static int num = 0;
static char namebuf[20];
static char prefix[] = "/tmp/tmp";

void itoa(int i, char* string)
{
    int power, j;

    j = i;
    for (power=1 ; j >= 10; j /= 10)
        power *= 10;
    for (; power>0 ; power /= 10)
    {
        *string++= '0' + i / power;
        i %= power;
    }
    *string='\0';
}

// 得到的可用的文件名，格式为 /tmp/tmp<pid>.<no>
char* gentemp()
{
    int length, pid;

    /*获得进程标识符*/
    pid = getpid();
    strcpy(namebuf, prefix);
    length = strlen(namebuf);
    itoa(pid, &namebuf[length]);
    strcat(namebuf, ".");
    length = strlen(namebuf);
    do {
        itoa(num++, &namebuf[length]);
    } while(access(namebuf, 0) != -1); // 确定文件或文件夹的访问权限，返回 -1 则说明文件不存在
    return namebuf;
}

// 创建一个新的进程，并执行命令
int docommand(char* command)
{
    int pid; /* fork子进程 */
    switch(pid=fork()) {
        case -1:
            perror("fork failed");
            exit(1);
        case 0:
//            sleep(3);
            execl("/bin/sh","sh","-c",command,NULL);
            perror("execl failed");
            exit(1);
        default:
            wait(NULL); // 等待第一个子进程结束，并返回进程的标识符
            printf("ls completed\n");
            exit(0);
    }
}

// 通过环境指针获取环境变量
extern char** environ;
void env_vars()
{
    char** env = environ;

    while (*env)
    {
        printf("%s\n", *env++);
    }
}

// 创建守护进程
#define MAXFD 64

void daemon_init(const char* pname, int facility)
{
    if (fork())
        exit(0);

    setsid();
    signal(SIGHUP, SIG_IGN);

    if (fork())
        exit(0);

    chdir("/");
    umask(0);

    int i;
    for (i = 0; i < MAXFD; i++)
        close(i);
    openlog(pname, LOG_PID, facility);
}

int ntimes = 0;
void p_action() {
    printf("Patent caught signal #%d\n", ++ntimes);
}

void c_action() {
    printf("Child caught signal #%d\n", ++ntimes);
}

void use_signal() {
    int pid, ppid;
    /* 设定父进程的SIGUSR1 */
    signal(SIGUSR1, p_action);
    switch (pid = fork()) {
        case -1: /*fork 失败*/
            perror("synchro");
            exit(1);
        case 0: /*子进程模块*/
            /* 设定子进程的SIGUSR1 */
            signal(SIGUSR1, c_action);
            /* 获得父进程的标识符 */
            ppid = getppid();
            while (1) {
                sleep(1);
                kill(ppid, SIGUSR1);
                pause();
            }
            /*死循环*/ break;
        default: /*父进程模块*/
            while (1) {
                pause();
                sleep(1);
                kill(pid, SIGUSR1);
            }
            /*死循环*/
    }
}

//popen 和 pclose的使用
#define MAXSTRS 5

void pipe_use() {
    int cntr;
    FILE *pipe_fp;
    char *strings[MAXSTRS] = {"roy", "zixia", "gouki", "supper", "mmwan"}; /* 用popen 建立管道 */
    if ((pipe_fp = popen("sort", "w")) == NULL) {
        perror("popen");
        exit(1);
    } /* Processing loop */
    for (cntr = 0; cntr < MAXSTRS; cntr++) {
        fputs(strings[cntr], pipe_fp);
        fputc('\n', pipe_fp);
    }
    /* 关闭管道 */
    pclose(pipe_fp);
}

#define SEQFILE "./sequo"
#define MAXBUF 100

void my_lock(int fd) {
    lseek(fd, 0L, SEEK_SET);
    if (lockf(fd, F_LOCK, 0L) == -1)
    {
        perror("can not lock the file");
        exit(1);
    }
}

void my_unlock(int fd) {
    lseek(fd, 0L, SEEK_SET);
    if (lockf(fd, F_ULOCK, 0L) == -1)
    {
        perror("can not unlock the file");
        exit(1);
    }
}

void process_file_operate() {
    int fd, i, n, pid, seqno;
    char buff[MAXBUF + 1];
    pid = getpid();
    if ((fd = open("data", O_RDWR | O_CREAT)) < 0) {
        perror("Can't open");
        exit(1);
    }
    for (i = 0; i < 5; i++) {
        my_lock(fd);
        lseek(fd, 01, SEEK_SET);
        if ((n = read(fd, buff, MAXBUF)) <= 0) {
            perror("read error");
            exit(1);
        }
        buff[n] = 0;
        if (!(n = sscanf(buff, "%d\n", &seqno))) {
            perror("sscanf error");
            exit(1);
        }
        printf("pid=%d,seq#=%d\n", pid, seqno);
        seqno++;
        sprintf(buff, "%03d\n", seqno);
        n = strlen(buff);
        lseek(fd, 01, SEEK_SET);
        if (write(fd, buff, n) != n) {
            perror("write error");
            exit(1);
        }
        my_unlock(fd);
    }
    close(fd);
}

void test_process()
{
//    char *command = "ls -l";
//    int ret = docommand(command);

//    printf("%s\n", gentemp());
//    printf("%s\n", gentemp());

//    daemon_init("hello", 0);

    // 输出环境变量
    env_vars();

//    use_signal();

//    pipe_use();

//    process_file_operate();
}

#endif //ALGORITHM_CODE_PROCESS_CONTROL_H

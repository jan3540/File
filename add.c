#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

// 信号处理函数，用于通知父进程读取管道
void signal_handler(int signum) {
    // 仅用于通知父进程
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "使用方法: %s <小数1> <小数2>\n", argv[0]);
        return 1;
    }

    double num1 = atof(argv[1]);
    double num2 = atof(argv[2]);
    int fd[2]; // 文件描述符数组用于管道
    pid_t pid;

    // 创建管道
    if (pipe(fd) == -1) {
        fprintf(stderr, "管道创建失败\n");
        return 1;
    }

    pid = fork();

    if (pid < 0) {
        // fork失败
        fprintf(stderr, "创建子进程失败\n");
        return 1;
    } else if (pid == 0) {
        // 子进程
        close(fd[0]); // 关闭读端
        double sum = num1 + num2;
        // 将结果写入管道
        write(fd[1], &sum, sizeof(sum));
        close(fd[1]); // 关闭写端
        // 发送信号给父进程
        kill(getppid(), SIGUSR1);
        exit(0);
    } else {
        // 父进程
        double sum;
        close(fd[1]); // 关闭写端
        // 注册信号处理函数
        signal(SIGUSR1, signal_handler);
        // 等待子进程发送信号
        pause();
        // 从管道读取结果
        read(fd[0], &sum, sizeof(sum));
        printf("计算结果：两数之和为 %.2f\n", sum);
        close(fd[0]); // 关闭读端
        wait(NULL); // 等待子进程结束
    }

    return 0;
}

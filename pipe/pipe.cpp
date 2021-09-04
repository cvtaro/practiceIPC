/**
 * int pipe(int fd[2])
 * fd[0] : 出口
 * fd[1] : 入口
 * pipe をつくってfork() すると、出入口が共有化される。
 * 一方の入口を閉じ、もう一方の出口を閉じれば、データ授受が可能
 * */


#include <cstdio>
#include <cstdlib>
#include <sys/pipe.h>
#include <unistd.h>

int pipe_fd[2];

void child_process() 
{
    char *p = "This is child .\n";
    printf("1 child\n");

    // 子プロセス側の出口を閉じる
    close(pipe_fd[0]);
    printf("2 child\n");

    while (*p) {
        printf("%c - ", *p);
        if (write(pipe_fd[1], p, 1) < 0) {
            perror("write");
            exit(2);
        }
        p++;
    }
    printf("3 child\n");
    exit(1);
}

void parent_prosess()
{
    printf("1 parent\n");

    // 親プロセス側の入口を閉じる
    close(pipe_fd[1]);
    printf("2 parent\n");

    int c, count;
    while ((count = read(pipe_fd[0], &c, 1)) > 0) {
        putchar(c);
    }

    printf("3 parent\n");
    if (count < 0) {
        perror("read");
        exit(1);
    }

    printf("4 parent\n");
    int status;
    if (wait(&status) < 0) {
        perror("wait");
        exit(1);
    }

    printf("5 parent\n");
}

int main()
{
    if (pipe(pipe_fd) < 0) {
        perror("pipe");
        exit(1);
    }

    int child_pid;
    if ((child_pid = fork()) < 0) {
        perror("fork");
        exit(1);
    }

    if (child_pid) {
        parent_prosess();
    } else {
        child_process();
    }

    return 0;
}
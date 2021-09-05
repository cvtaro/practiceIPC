#include <cstdio>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char * argv[]) 
{
    printf("main!\n");
    
    int pid = fork();
    int status;

    if (pid == 0) {
        char * argv_exec[] = {"asdf", "a33r3", "dww3", NULL};
        execv("./exectest.out", argv_exec);
    } else {
        wait(&status);
    }

    printf("main! end\n");

    return 0;
}
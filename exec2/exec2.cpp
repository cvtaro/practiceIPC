/*
 * exec     arg       env       path
 * execl    list      inherit   n
 * execv    vector    inherit   n
 * execle   list      argument  n
 * execve   vector    argument  n
 * execlp   list      inherit   y
 * execvp   vector    inherit   y
 */
 #include <stdio.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <sys/wait.h>


/*
 * proc
 *  |
 * fork -------> proc2
 *  |              |
 * wait           exec
 *  |              |
 *  |   <-------- exit
 */
 int main(void) 
 {
    int child = fork();
    int status;

    if (child < 0) {
      perror("fork");
      exit(1);
    }
    printf("1 pid = %5d, %d\n", child, WEXITSTATUS(status));
    if (child == 0) {
      execl("c", NULL);
    } else {
      printf("2 pid = %5d, %d\n", child, WEXITSTATUS(status));
      if (wait(&status) < 0) {
        perror("wait");
        exit(1);
      }
      printf("3 pid = %5d, %d\n", child, WEXITSTATUS(status));
    }

    return 0;
 }
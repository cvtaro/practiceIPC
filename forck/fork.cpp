#include <iostream>
#include <sys/wait.h>
#include <unistd.h>
#include <cstdio>
#include <cstring>

int main (void)
{
  std::cout << "hello" << std::endl;
  
  char buff[100];
  int pipe_fd[2];
  pipe(pipe_fd);

  pid_t pid = fork();

  if (pid > 0) {
    std::cout << "Parent " << std::endl;
    close(pipe_fd[1]);
    std::cout << "Parent " << std::endl;
    read(pipe_fd[0], buff, sizeof(buff));
    std::cout << buff << " from chiled";
    close(pipe_fd[0]);
    std::cout << "Parent " << std::endl;
    return 0;
  }
  if (pid == 0) {
    std::cout << "Child " << std::endl;
    close(pipe_fd[0]);
    std::cout << "Child " << std::endl;
    fgets(buff, sizeof(buff), stdin);
    write(pipe_fd[1], buff, strlen(buff)+1);
    std::cout << "Child " << std::endl;
    close(pipe_fd[1]);
    std::cout << "Child " << std::endl;
    return 0;
  }
  if (pid < 0) {
    std::cerr << "Error " << std::endl;
    return -1;
  }

  return 0;
}

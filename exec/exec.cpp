#include <iostream>
#include <unistd.h>

int main (void)
{
  // main.exe を起動する
  execl("main.exe", "a0", "a1", "a2");
  // 下は表示されない

  std::cout << "Hello" << std::endl;

  return 0;
}
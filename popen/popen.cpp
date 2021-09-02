#include <iostream>
#include <cstdio>
#include <cstdlib>

int main (void)
{
  const char* command = "main.exe a b c";

  // 外部プロセスの標準出力を取得
  FILE *fp = popen(command, "r");
  if (fp == NULL) {
    return -1; 
  }

  char buff[100];
  while (fgets(buff, sizeof(buff), fp) != NULL)
  {
    std::cout << buff;
  }
  
  pclose(fp);

  return 0;
}
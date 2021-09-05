#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(void) 
{
    int sock;

    // ソケット作成　
    // アドレスファミリ，ソケットタイプ，プロトコル
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("socket");
        return 1;
    }

    return 0;
}
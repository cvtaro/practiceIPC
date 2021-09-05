#include <stdio.h>
#include <stdlib.h>
#include <string.h>         // memset
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>         // write, close
#include <arpa/inet.h>      // inet_addr

int main (void) 
{
    // ソケット作成
    int sock;
    sock = socket(AF_INET, SOCK_STREAM, 0);

    // 接続先設定
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(12345);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    // サーバに接続
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("connect");
        return 1;
    }

    // データ受信
    char buff[32];
    memset(buff, 0, sizeof(buff));

    int n = 0;
    n = read(sock, buff, sizeof(buff));
    if (n < 0) {
        perror("read");
        return 1;
    }
    printf("[c] read n =  %3d, buff = %s \n", n, buff);

    // socket 終了
    close(sock);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main (void) 
{
    // ソケット作成
    int sock;
    sock = socket(AF_INET, SOCK_STREAM, 0);

    // ソケット設定
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(12345);
    addr.sin_addr.s_addr = INADDR_ANY;
    bind(sock, (struct sockaddr *)& addr, sizeof(addr));

    // TCPクライアントからの接続要求待つ
    listen(sock, 5);

    // TCPクライアントからの接続要求を受ける
    struct sockaddr_in addr_client;
    socklen_t len_client = sizeof(addr_client);
    int sock_client;
    sock_client = accept(sock, (struct sockaddr *)&addr_client, &len_client);
    
    // 送信
    write(sock_client, "hello", 5);

    // TCP 終了
    close(sock_client);

    // listenするソケットを終了
    close(sock);

    return 0;
}
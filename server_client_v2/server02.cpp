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
    if (sock < 0) {
        perror("sock");
        return 1;
    }

    // ソケット設定
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(12345);
    addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(sock, (struct sockaddr *)& addr, sizeof(addr)) != 0) {
        perror("bind");
        return 1;
    }

    // TCPクライアントからの接続要求待つ
    if (listen(sock, 5) != 0) {
        perror("lister");
        return 1;
    }

    // TCPクライアントからの接続要求を受ける
    while (1) {
        struct sockaddr_in addr_client;
        socklen_t len_client;
        int sock_client;
        len_client = sizeof(addr_client);

        sock_client = accept(sock, (struct sockaddr *)&addr_client, &len_client);
        if (sock_client < 0) {
            perror("accept");
            break;
        }

        // 送信
        int n;
        n = write(sock_client, "hello", 5);
        if (n < 1) {
            perror("write");
            break;
        }
        
        // TCP 終了
        close(sock_client);
    }

    // listenするソケットを終了
    close(sock);

    return 0;
}
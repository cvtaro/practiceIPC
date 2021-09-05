#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>


int main(void)
{
    int sock_fd;
    int client_sock_fd;
    struct sockaddr_in addr;

    socklen_t len = sizeof(struct sockaddr_in);
    struct sockaddr_in from_addr;

    char buff[1024];

    // 受信バッファを初期化
    memset(buff, 0, sizeof(buff));

    // ソケット生成
    if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
    }

    // 待受のIP，ポート設定
    addr.sin_family = AF_INET;
    addr.sin_port = htons(1234);
    addr.sin_addr.s_addr = INADDR_ANY;

    // バインド
    if (bind(sock_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("bind");
    }

    // 受信待機
    if (listen(sock_fd, SOMAXCONN) < 0) {
        perror("listen");
    }
    // クライアントからのコネクションまち
    if ((client_sock_fd = accept(sock_fd, (struct sockaddr *)&from_addr, &len)) < 0) {
        perror("accept");
    }
    // 受信
    int res_size;
    while (1) {
        res_size = recv(client_sock_fd, buff, sizeof(buff), 0);
        if (res_size == 0) {
            break;
        } else if (res_size == -1) {
            perror("recv");
        } else {
            printf("res : %s\n", buff);
            sleep(1);

            // 応答
            printf("send : %s\n", buff);
            write(client_sock_fd, buff, res_size);
        }
    }
    
    // ソケットクローズ
    close(client_sock_fd);
    close(sock_fd);

    return 0;
}
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(void) {
    int sock_fd;
    struct sockaddr_in addr;

    // ソケット生成
    if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
    }
    // 送信先　アドレス，ポートを設定
    addr.sin_family = AF_INET;
    addr.sin_port = htons(1234);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    // サーバ接続
    connect(sock_fd, (struct sockaddr*)&addr, sizeof(struct sockaddr_in));
    // データ送信
    char send_str[10];
    char res_str[10];
    for (int i = 0; i < 10; i++) {
        sprintf(send_str, "%d", i);
        printf("send : %d\n", i);
        if (send(sock_fd, send_str, 10, 0) < 0) {
            perror("send");
        } else {
            recv("res : %s\n", res_str);
        }
    }

    // ソケットクローズ
    close(sock_fd);

    return 0;
}
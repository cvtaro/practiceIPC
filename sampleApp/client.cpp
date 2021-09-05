#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>


int main(int argc, char const *argv[]) 
{
    printf("[client] start.\n");

    // ソケット作成
    int sock_server;
    sock_server = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_server < 0) {
        perror("sock client");
        return 1;
    }
    printf("[client] sock server opened.\n");
    // 接続設定
    struct sockaddr_in app;
    app.sin_family = AF_INET;
    app.sin_port = htons(5555);
    app.sin_addr.s_addr = inet_addr("127.0.0.1");
    // サーバに接続
    if (connect(sock_server, (struct sockaddr *)&app, sizeof(app)) < 0) {
        perror("connect client");
        close(sock_server);
        return 1;
    }
    printf("[client] connect to server.\n");

    // データを送信
    char req_buff[1024];
    fgets(req_buff, 1024, stdin);
    int req_n = write(sock_server, req_buff, 1024);
    if (req_n < 0) {
        perror("write client");
        close(sock_server);
        return 1;
    }
    printf("[client] write n =  %3d, buff = %s \n", req_n, req_buff);

    // データを受信
    char res_buff[1024];
    memset(res_buff, 0, sizeof(res_buff));
    int res_n = 0;
    res_n = read(sock_server, res_buff, sizeof(res_buff));
    if (res_n < 0) {
        perror("read client");
        close(sock_server);
        return 1;
    }
    printf("[client] read n =  %3d, buff = %s \n", res_n, res_buff);
    
    
    // socket 終了
    close(sock_server);
    printf("[client] sock server closed.\n");

    printf("[client] end.\n");
    return 0;
}
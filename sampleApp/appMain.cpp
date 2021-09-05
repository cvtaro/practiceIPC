#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/wait.h>

#define PIPE_READ   (0)
#define PIPE_WRITE  (1)

int main(void) 
{
    printf("[app  M] start.\n");

    // ソケット作成（server）
    int sock_server;
    sock_server = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_server < 0) { 
        perror("sock appM");
        return 1;
    }
    printf("[app  M] sock server opened.\n");
    // ソケット設定（server）
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(5555);
    server.sin_addr.s_addr = INADDR_ANY;
    // バインド（server）
    const int on = 1;
    if(setsockopt(sock_server, SOL_SOCKET, SO_REUSEADDR, (const char *)&on, sizeof(on)) < 0 ) {
        perror("setsockopt appM");
        return 1;
    } 

    if (bind(sock_server, (struct sockaddr*)&server, sizeof(server)) != 0) {
        perror("bind appM");
        return 1;
    }
    printf("[app  M] sock server binded.\n");
    // 要求待ち（server）
    if(listen(sock_server, 10) != 0) {
        perror("listen appM");
        return 0;
    }
    printf("[app  M] sock server listend.\n");

    /* clientからの要求待ち */
    while (1) {
        printf("[app  M] request waiting ... press [x] to close.\n");
        struct sockaddr_in client;
        socklen_t len_client;
        int sock_client;
        len_client = sizeof(client);
        sock_client = accept(sock_server, (struct sockaddr *)&client, &len_client);
        if (sock_client < 0) {
            perror("accept appM");
            return 1;
        }
        printf("[app  M] accept from %s, port = %5d\n",
            inet_ntoa(client.sin_addr), ntohs(client.sin_port)
        );

        /* clientからの要求が来たら SubApp起動 */
        char req_buff[1024];
        memset(req_buff, 0, sizeof(req_buff));
        int n_req = 0;
        n_req = read(sock_client, req_buff, sizeof(req_buff));
        if (n_req < 0) {
            perror("read appM");
            return 1;
        }
        printf("[app  M] read n =  %3d, buff = %s \n", n_req, req_buff);

        // x 
        if (req_buff[0] == 'x') {
            printf("[app  M] cansel req. \n");
            close(sock_client);
            break;
        }

        /* subアプリ起動 */
        printf("[app  M] chiled process start.\n");
        // sleep(1);
        {
            int pipe_fd[2];
            pipe(pipe_fd);

            int child = fork();
            if (child == 0) {
                close(pipe_fd[PIPE_READ]);  // 子→親への書き込みのためクローズ
                dup2(pipe_fd[PIPE_WRITE], STDOUT_FILENO); // 子→親への入力を標準出力に割当て
                close(pipe_fd[PIPE_WRITE]);  // 割当てたfdのためクローズ

                char * argv_exec[] = {req_buff, NULL};
                execv("./exectest.out", argv_exec);
            } else {
                // wait(&status);
                close(pipe_fd[PIPE_WRITE]); // 子→親への書き込みのためクローズ

                char pipe_buff[1024];
                memset(pipe_buff, 0, sizeof(pipe_buff));
                int pipe_res;
                pipe_res = read(pipe_fd[PIPE_READ], pipe_buff, sizeof(pipe_buff));
                close(pipe_fd[PIPE_READ]);
                printf("[app  M] read res n =  %3d, buff = \n%s\n", pipe_res, pipe_buff);
                wait(0);
            }
        }
        printf("[app  M] chiled process end.\n");

        /* clientへ応答を返す  */
        int n_res = write(sock_client, "res", 5);
        if (n_res < 1) {
            perror("write appM");
            close(sock_client);
            break;
        }
        close(sock_client);
    }
    
    close(sock_server);
    printf("[app  M] sock server closed.\n");

    printf("[app  M] end.\n");
    return 0;
}
// client.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 12345          // 服务器端口号
#define BUFFER_SIZE 1024    // 缓冲区大小

// 去除字符串末尾的换行符
void str_trim_lf(char *arr, int length) {
    for (int i = 0; i < length; i++) {
        if (arr[i] == '\n') {
            arr[i] = '\0';
            break;
        }
    }
}

// 接收消息的线程函数
void *receive_handler(void *sock) {
    int sockfd = *((int *)sock);
    char buffer[BUFFER_SIZE];

    while (1) {
        int receive = recv(sockfd, buffer, BUFFER_SIZE, 0);
        if (receive > 0) {
            printf("%s", buffer);
        } else if (receive == 0) {
            break;
        } else {
            printf("ERROR: 接收失败\n");
        }
        memset(buffer, 0, BUFFER_SIZE);
    }

    return NULL;
}

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    char name[32];
    pthread_t tid;

    // 创建套接字
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("ERROR: 创建套接字失败");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // 本地服务器地址
    server_addr.sin_port = htons(PORT);

    // 连接到服务器
    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("ERROR: 连接服务器失败");
        exit(EXIT_FAILURE);
    }

    printf("请输入您的用户名: ");
    fgets(name, 32, stdin);
    str_trim_lf(name, strlen(name));
    if (strlen(name) > 32 || strlen(name) < 2) {
        printf("用户名必须在2到30个字符之间。\n");
        close(sockfd);
        return 1;
    }

    // 发送用户名到服务器
    send(sockfd, name, 32, 0);

    // 创建接收消息的线程
    pthread_create(&tid, NULL, &receive_handler, (void*)&sockfd);

    while (1) {
        char buffer[BUFFER_SIZE];
        fgets(buffer, BUFFER_SIZE, stdin);
        str_trim_lf(buffer, strlen(buffer));

        if (strcmp(buffer, "exit") == 0) {
            break;
        } else {
            send(sockfd, buffer, BUFFER_SIZE, 0);
        }

        memset(buffer, 0, BUFFER_SIZE);
    }

    close(sockfd);
    return 0;
}

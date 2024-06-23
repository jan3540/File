// server.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 12345          // 服务器端口号
#define MAX_CLIENTS 10      // 最大客户端数量
#define BUFFER_SIZE 1024    // 缓冲区大小

// 客户端结构体
typedef struct {
    struct sockaddr_in address; // 客户端地址
    int sockfd;                 // 套接字文件描述符
    int uid;                    // 用户ID
    char name[32];              // 用户名
} client_t;

client_t *clients[MAX_CLIENTS]; // 客户端列表
pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER; // 互斥锁
static int uid = 10; // 初始用户ID

// 去除字符串末尾的换行符
void str_trim_lf(char *arr, int length) {
    for(int i = 0; i < length; i++) {
        if(arr[i] == '\n') {
            arr[i] = '\0';
            break;
        }
    }
}

// 打印客户端地址
void print_client_addr(struct sockaddr_in addr) {
    printf("%d.%d.%d.%d",
           addr.sin_addr.s_addr & 0xff,
           (addr.sin_addr.s_addr & 0xff00) >> 8,
           (addr.sin_addr.s_addr & 0xff0000) >> 16,
           (addr.sin_addr.s_addr & 0xff000000) >> 24);
}

// 广播消息给所有客户端
void broadcast_message(char *message, int uid) {
    pthread_mutex_lock(&clients_mutex);

    for(int i = 0; i < MAX_CLIENTS; ++i) {
        if(clients[i]) {
            if(clients[i]->uid != uid) {
                if(write(clients[i]->sockfd, message, strlen(message)) < 0) {
                    perror("ERROR: 写入描述符失败");
                    break;
                }
            }
        }
    }

    pthread_mutex_unlock(&clients_mutex);
}

// 添加客户端到列表
void add_client(client_t *client) {
    pthread_mutex_lock(&clients_mutex);

    for(int i = 0; i < MAX_CLIENTS; ++i) {
        if(!clients[i]) {
            clients[i] = client;
            break;
        }
    }

    pthread_mutex_unlock(&clients_mutex);
}

// 从列表中移除客户端
void remove_client(int uid) {
    pthread_mutex_lock(&clients_mutex);

    for(int i = 0; i < MAX_CLIENTS; ++i) {
        if(clients[i]) {
            if(clients[i]->uid == uid) {
                clients[i] = NULL;
                break;
            }
        }
    }

    pthread_mutex_unlock(&clients_mutex);
}

// 处理客户端通信的线程函数
void *handle_client(void *arg) {
    char buffer[BUFFER_SIZE];
    char name[32];
    int leave_flag = 0;

    client_t *cli = (client_t *)arg;

    // 接收客户端用户名
    if(recv(cli->sockfd, name, 32, 0) <= 0 || strlen(name) < 2 || strlen(name) >= 32-1) {
        printf("没有输入用户名。\n");
        leave_flag = 1;
    } else {
        strcpy(cli->name, name);
        sprintf(buffer, "%s 加入了聊天\n", cli->name);
        printf("%s", buffer);
        broadcast_message(buffer, cli->uid);
    }

    bzero(buffer, BUFFER_SIZE);

    while(1) {
        if (leave_flag) {
            break;
        }

        int receive = recv(cli->sockfd, buffer, BUFFER_SIZE, 0);
        if (receive > 0) {
            if(strlen(buffer) > 0) {
                broadcast_message(buffer, cli->uid);
                printf("%s -> %s\n", buffer, cli->name);
                bzero(buffer, BUFFER_SIZE);
            }
        } else if (receive == 0 || strcmp(buffer, "exit") == 0) {
            sprintf(buffer, "%s 离开了聊天\n", cli->name);
            printf("%s", buffer);
            broadcast_message(buffer, cli->uid);
            leave_flag = 1;
        } else {
            printf("ERROR: 接收失败\n");
            leave_flag = 1;
        }

        bzero(buffer, BUFFER_SIZE);
    }

    close(cli->sockfd);
    remove_client(cli->uid);
    free(cli);
    pthread_detach(pthread_self());

    return NULL;
}

int main() {
    int sockfd, new_sock;
    struct sockaddr_in server_addr, cli_addr;
    socklen_t cli_len = sizeof(cli_addr);
    pthread_t tid;

    // 创建套接字
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("ERROR: 创建套接字失败");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // 绑定套接字
    if(bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("ERROR: 绑定失败");
        exit(EXIT_FAILURE);
    }

    // 监听
    if(listen(sockfd, 10) < 0) {
        perror("ERROR: 监听失败");
        exit(EXIT_FAILURE);
    }

    printf("=== 欢迎进入聊天室 ===\n");

    while(1) {
        // 接受客户端连接
        new_sock = accept(sockfd, (struct sockaddr*)&cli_addr, &cli_len);
        if (new_sock < 0) {
            perror("ERROR: 接受连接失败");
            exit(EXIT_FAILURE);
        }

        // 检查最大客户端数
        if((uid - 10 + 1) == MAX_CLIENTS) {
            printf("达到最大客户端数。拒绝: ");
            print_client_addr(cli_addr);
            printf(":%d\n", cli_addr.sin_port);
            close(new_sock);
            continue;
        }

        // 分配客户端
        client_t *cli = (client_t *)malloc(sizeof(client_t));
        cli->address = cli_addr;
        cli->sockfd = new_sock;
        cli->uid = uid++;

        // 添加客户端到列表并创建线程处理通信
        add_client(cli);
        pthread_create(&tid, NULL, &handle_client, (void*)cli);
    }

    return 0;
}

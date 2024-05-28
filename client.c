#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <errno.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define END_OF_FILE "EOF"

void list_files(int server_sock);
void download_file(int server_sock, char *remote_filename, char *local_filename);
void upload_file(int server_sock, char *local_filename, char *remote_filename);
void rename_file(int server_sock, char *oldname, char *newname);
void delete_file(int server_sock, char *filename);

int main() {
    int server_sock;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    // 创建客户端套接字
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock == -1) {
        perror("socket");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    // 连接服务器
    if (connect(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("connect");
        close(server_sock);
        exit(1);
    }

    printf("Connected to server.\n");

    while (1) {
        printf("Enter command: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';

        if (strcmp(buffer, "exit") == 0) break;

        char command[BUFFER_SIZE], arg1[BUFFER_SIZE], arg2[BUFFER_SIZE];
        sscanf(buffer, "%s %s %s", command, arg1, arg2);

        // 发送命令到服务器
        write(server_sock, buffer, strlen(buffer));

        // 根据命令执行相应的功能
        if (strcmp(command, "list") == 0) {
            list_files(server_sock);
        } else if (strcmp(command, "download") == 0) {
            download_file(server_sock, arg1, arg2);
        } else if (strcmp(command, "upload") == 0) {
            upload_file(server_sock, arg1, arg2);
        } else if (strcmp(command, "rename") == 0) {
            rename_file(server_sock, arg1, arg2);
        } else if (strcmp(command, "delete") == 0) {
            delete_file(server_sock, arg1);
        }
    }

    close(server_sock);
    return 0;
}

// 列出服务器端文件
void list_files(int server_sock) {
    char buffer[BUFFER_SIZE];
    int n = read(server_sock, buffer, BUFFER_SIZE - 1);
    if (n > 0) {
        buffer[n] = '\0';
        printf("%s\n", buffer);
    }
}

// 下载文件到客户端本地
void download_file(int server_sock, char *remote_filename, char *local_filename) {
    int file = open(local_filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (file == -1) {
        perror("open");
        return;
    }

    char buffer[BUFFER_SIZE];
    int n;

    while ((n = read(server_sock, buffer, BUFFER_SIZE)) > 0) {
        if (n == 1 && buffer[0] == '\0') break;  // 处理文件结束标志
        write(file, buffer, n);
    }

    close(file);
    printf("File downloaded successfully.\n");
}

// 上传本地文件到服务器端
void upload_file(int server_sock, char *local_filename, char *remote_filename) {
    int file = open(local_filename, O_RDONLY);
    if (file == -1) {
        perror("open");
        return;
    }

    char buffer[BUFFER_SIZE];
    int n;

    // 发送远程文件名
    write(server_sock, remote_filename, strlen(remote_filename) + 1);

    while ((n = read(file, buffer, BUFFER_SIZE)) > 0) {
        write(server_sock, buffer, n);
    }

    // 发送文件结束标志
    write(server_sock, END_OF_FILE, strlen(END_OF_FILE) + 1);
    
    // 接收服务器端确认消息
    n = read(server_sock, buffer, BUFFER_SIZE - 1);
    if (n > 0) {
        buffer[n] = '\0';
        printf("%s", buffer);
    }

    close(file);
}

// 重命名服务器端文件
void rename_file(int server_sock, char *oldname, char *newname) {
    char buffer[BUFFER_SIZE];
    int n = read(server_sock, buffer, BUFFER_SIZE - 1);
    if (n > 0) {
        buffer[n] = '\0';
        printf("%s", buffer);
    }

    fgets(buffer, BUFFER_SIZE, stdin);
    write(server_sock, buffer, 1);

    n = read(server_sock, buffer, BUFFER_SIZE - 1);
    if (n > 0) {
        buffer[n] = '\0';
        printf("%s\n", buffer);
    }
}

// 删除服务器端文件
void delete_file(int server_sock, char *filename) {
    char buffer[BUFFER_SIZE];
    int n = read(server_sock, buffer, BUFFER_SIZE - 1);
    if (n > 0) {
        buffer[n] = '\0';
        printf("%s", buffer);
    }

    fgets(buffer, BUFFER_SIZE, stdin);
    write(server_sock, buffer, 1);

    n = read(server_sock, buffer, BUFFER_SIZE - 1);
    if (n > 0) {
        buffer[n] = '\0';
        printf("%s\n", buffer);
    }
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <dirent.h>
#include <fcntl.h>
#include <errno.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define END_OF_FILE "EOF"

void list_files(int client_sock);
void send_file(int client_sock, char *filename);
void receive_file(int client_sock);
void rename_file(int client_sock, char *oldname, char *newname);
void delete_file(int client_sock, char *filename);

int main() {
    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_size;
    char buffer[BUFFER_SIZE];

    // 创建服务器套接字
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock == -1) {
        perror("socket");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // 设置套接字选项以重用地址
    int opt = 1;
    setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // 绑定套接字到指定端口
    if (bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind");
        close(server_sock);
        exit(1);
    }

    // 监听端口，等待客户端连接
    if (listen(server_sock, 5) == -1) {
        perror("listen");
        close(server_sock);
        exit(1);
    }

    printf("Server is listening on port %d...\n", PORT);

    client_addr_size = sizeof(client_addr);
    // 接受客户端连接
    while ((client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &client_addr_size)) != -1) {
        printf("Client connected.\n");

        while (1) {
            int n = read(client_sock, buffer, BUFFER_SIZE - 1);
            if (n <= 0) break;
            buffer[n] = '\0';

            char command[BUFFER_SIZE], arg1[BUFFER_SIZE], arg2[BUFFER_SIZE];
            sscanf(buffer, "%s %s %s", command, arg1, arg2);

            // 根据命令执行相应的功能
            if (strcmp(command, "list") == 0) {
                list_files(client_sock);
            } else if (strcmp(command, "download") == 0) {
                send_file(client_sock, arg1);
            } else if (strcmp(command, "upload") == 0) {
                receive_file(client_sock);
            } else if (strcmp(command, "rename") == 0) {
                rename_file(client_sock, arg1, arg2);
            } else if (strcmp(command, "delete") == 0) {
                delete_file(client_sock, arg1);
            }
        }

        close(client_sock);
        printf("Client disconnected.\n");
    }

    close(server_sock);
    return 0;
}

// 列出服务器端当前目录的文件
void list_files(int client_sock) {
    DIR *d;
    struct dirent *dir;
    char buffer[BUFFER_SIZE] = "";

    d = opendir(".");
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            strcat(buffer, dir->d_name);
            strcat(buffer, "\n");
        }
        closedir(d);
    }

    write(client_sock, buffer, strlen(buffer));
}

// 发送文件给客户端
void send_file(int client_sock, char *filename) {
    int file = open(filename, O_RDONLY);
    if (file == -1) {
        perror("open");
        return;
    }

    char buffer[BUFFER_SIZE];
    int n;

    while ((n = read(file, buffer, BUFFER_SIZE)) > 0) {
        write(client_sock, buffer, n);
    }

    close(file);
    write(client_sock, "", 1);  // 发送一个空字符来表示文件结束
}

// 接收客户端上传的文件
void receive_file(int client_sock) {
    char filename[BUFFER_SIZE];
    char buffer[BUFFER_SIZE];
    int n;

    // 接收远程文件名
    n = read(client_sock, filename, BUFFER_SIZE);
    if (n <= 0) {
        perror("read filename");
        return;
    }
    filename[n] = '\0';

    int file = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (file == -1) {
        perror("open");
        return;
    }

    while ((n = read(client_sock, buffer, BUFFER_SIZE)) > 0) {
        if (strncmp(buffer, END_OF_FILE, strlen(END_OF_FILE)) == 0) {
            break;  // 检测到文件结束标志
        }
        write(file, buffer, n);
    }

    close(file);
    write(client_sock, "File upload complete.\n", 22);  // 发送确认消息到客户端
}

// 重命名服务器端文件
void rename_file(int client_sock, char *oldname, char *newname) {
    char response[BUFFER_SIZE];
    snprintf(response, sizeof(response), "Do you really want to rename %s to %s? (Y/N): ", oldname, newname);
    write(client_sock, response, strlen(response));

    char confirm[2];
    read(client_sock, confirm, 2);

    if (confirm[0] == 'Y' || confirm[0] == 'y') {
        if (rename(oldname, newname) == 0) {
            strcpy(response, "File renamed successfully.\n");
        } else {
            strcpy(response, "File rename failed.\n");
        }
    } else {
        strcpy(response, "File rename canceled.\n");
    }

    write(client_sock, response, strlen(response));
}

// 删除服务器端文件
void delete_file(int client_sock, char *filename) {
    char response[BUFFER_SIZE];
    snprintf(response, sizeof(response), "Do you really want to delete %s? (Y/N): ", filename);
    write(client_sock, response, strlen(response));

    char confirm[2];
    read(client_sock, confirm, 2);

    if (confirm[0] == 'Y' || confirm[0] == 'y') {
        if (remove(filename) == 0) {
            strcpy(response, "File deleted successfully.\n");
        } else {
            strcpy(response, "File delete failed.\n");
        }
    } else {
        strcpy(response, "File delete canceled.\n");
    }

    write(client_sock, response, strlen(response));
}

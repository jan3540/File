#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_USER 5 // 最大用户数
#define MAX_FILE 5 // 每个用户最多保存的文件数
#define MAX_NAME 20 // 文件名和用户名的最大长度
#define MAX_SIZE 100 // 文件的最大大小（字节）
#define MAX_BLOCK 10 // 磁盘的最大块数
#define BLOCK_SIZE 10 // 每个块的大小（字节）

// 文件结构体，包含文件名，文件大小，文件内容，文件权限，文件所占的磁盘块
typedef struct file {
    char name[MAX_NAME]; // 文件名
    int size; // 文件大小
    char content[MAX_SIZE]; // 文件内容
    int mode; // 文件权限，0表示只读，1表示可写
    int blocks[MAX_SIZE / BLOCK_SIZE + 1]; // 文件所占的磁盘块，-1表示空闲
} file;

// 用户结构体，包含用户名，当前打开的文件，以及用户的目录
typedef struct user {
    char name[MAX_NAME]; // 用户名
    file *open_file; // 当前打开的文件，NULL表示没有打开的文件
    file files[MAX_FILE]; // 用户的目录，存储用户的文件
} user;

// 全局变量，存储用户，磁盘空间，当前用户
user users[MAX_USER]; // 用户数组，存储所有的用户
bool bitmap[MAX_BLOCK]; // 磁盘空间的位图，表示每个块是否被占用，true表示占用，false表示空闲
user *current_user; // 当前用户，指向用户数组中的一个元素，NULL表示没有登录的用户

// 函数声明，实现文件系统的基本操作
void init(); // 初始化函数，初始化用户，磁盘空间，当前用户
void login(char *name); // 登录函数，根据用户名切换当前用户
void logout(); // 登出函数，将当前用户设为NULL
void mycreate(char *name, int mode); // 创建文件函数，根据文件名和权限在当前用户的目录中创建一个文件
void mydelete(char *name); // 删除文件函数，根据文件名在当前用户的目录中删除一个文件
void myopen(char *name); // 打开文件函数，根据文件名在当前用户的目录中打开一个文件
void myclose(); // 关闭文件函数，关闭当前用户打开的文件
void myread(); // 读取文件函数，读取当前用户打开的文件的内容
void mywrite(char *content); // 写入文件函数，向当前用户打开的文件写入内容
void myls(); // 列出文件函数，列出当前用户的目录中的所有文件
void myexit(); // 退出函数，退出程序

// 初始化函数，初始化用户，磁盘空间，当前用户
void init() {
    // 初始化用户数组，给每个用户分配一个名字，初始化其目录和打开的文件
    for (int i = 0; i < MAX_USER; i++) {
        sprintf(users[i].name, "user%d", i + 1); // 用户名为user1, user2, ..., user5
        users[i].open_file = NULL; // 没有打开的文件
        for (int j = 0; j < MAX_FILE; j++) {
            users[i].files[j].name[0] = '\0'; // 目录中的文件名为空
            users[i].files[j].size = 0; // 目录中的文件大小为0
            users[i].files[j].content[0] = '\0'; // 目录中的文件内容为空
            users[i].files[j].mode = 0; // 目录中的文件权限为0
            for (int k = 0; k < MAX_SIZE / BLOCK_SIZE + 1; k++) {
                users[i].files[j].blocks[k] = -1; // 目录中的文件所占的磁盘块为空闲
            }
        }
    }
    // 初始化磁盘空间的位图，将所有的块设为空闲
    for (int i = 0; i < MAX_BLOCK; i++) {
        bitmap[i] = false;
    }
    // 初始化当前用户，设为NULL
    current_user = NULL;
}

// 登录函数，根据用户名切换当前用户
void login(char *name) {
    // 检查是否已经有用户登录
    if (current_user != NULL) {
        printf("请先登出当前用户：%s\n", current_user->name);
        return;
    }
    // 遍历用户数组，寻找匹配的用户名
    for (int i = 0; i < MAX_USER; i++) {
        if (strcmp(users[i].name, name) == 0) {
            // 找到匹配的用户名，将当前用户设为该用户
            current_user = &users[i];
            printf("登录成功，欢迎您：%s\n", current_user->name);
            return;
        }
    }
    // 没有找到匹配的用户名，提示错误信息
    printf("登录失败，没有找到该用户：%s\n", name);
}

// 登出函数，将当前用户设为NULL
void logout() {
    // 检查是否有用户登录
    if (current_user == NULL) {
        printf("没有用户登录\n");
        return;
    }
    // 检查是否有打开的文件
    if (current_user->open_file != NULL) {
        printf("请先关闭打开的文件：%s\n", current_user->open_file->name);
        return;
    }
    // 将当前用户设为NULL，提示登出成功
    printf("登出成功，再见：%s\n", current_user->name);
    current_user = NULL;
}

// 创建文件函数，根据文件名和权限在当前用户的目录中创建一个文件
void mycreate(char *name, int mode) {
    // 检查是否有用户登录
    if (current_user == NULL) {
        printf("没有用户登录\n");
        return;
    }
    // 检查文件名是否合法
    if (strlen(name) == 0 || strlen(name) >= MAX_NAME) {
        printf("文件名不合法\n");
        return;
    }
    // 检查权限是否合法
    if (mode != 0 && mode != 1) {
        printf("权限不合法\n");
        return;
    }
    // 遍历当前用户的目录，寻找空闲的位置
    for (int i = 0; i < MAX_FILE; i++) {
        if (current_user->files[i].name[0] == '\0') {
            // 找到空闲的位置，将文件名，文件大小，文件内容，文件权限复制到该位置
            strcpy(current_user->files[i].name, name);
            current_user->files[i].size = 0;
            current_user->files[i].content[0] = '\0';
            current_user->files[i].mode = mode;
            // 寻找空闲的磁盘块，分配给该文件
            for (int j = 0; j < MAX_BLOCK; j++) {
                if (bitmap[j] == false) {
                    // 找到空闲的磁盘块，将其设为占用，将其编号存储到文件的blocks数组中
                    bitmap[j] = true;
                    current_user->files[i].blocks[0] = j;
                    // 将文件的其他blocks数组中的元素设为-1，表示空闲
                    for (int k = 1; k < MAX_SIZE / BLOCK_SIZE + 1; k++) {
                        current_user->files[i].blocks[k] = -1;
                    }
                    // 提示创建文件成功，返回
                    printf("创建文件成功：%s\n", name);
                    return;
                }
            }
            // 没有找到空闲的磁盘块，提示错误信息，将文件名设为空，返回
            printf("创建文件失败，没有足够的磁盘空间\n");
            current_user->files[i].name[0] = '\0';
            return;
        }
    }
    // 没有找到空闲的位置，提示错误信息
    printf("创建文件失败，没有足够的目录空间\n");
}

// 删除文件函数，根据文件名在当前用户的目录中删除一个文件
void mydelete(char *name) {
    // 检查是否有用户登录
    if (current_user == NULL) {
        printf("没有用户登录\n");
        return;
    }
    // 检查文件名是否合法
    if (strlen(name) == 0 || strlen(name) >= MAX_NAME) {
        printf("文件名不合法\n");
        return;
    }
    // 遍历当前用户的目录，寻找匹配的文件名
    for (int i = 0; i < MAX_FILE; i++) {
        if (strcmp(current_user->files[i].name, name) == 0) {
            // 找到匹配的文件名，检查是否是打开的文件
            if (current_user->open_file == &current_user->files[i]) {
                // 是打开的文件，提示错误信息，返回
                printf("删除文件失败，该文件正在被打开：%s\n", name);
                return;
            }
            // 不是打开的文件，将文件名，文件大小，文件内容，文件权限设为空
            current_user->files[i].name[0] = '\0';
            current_user->files[i].size = 0;
            current_user->files[i].content[0] = '\0';
            current_user->files[i].mode = 0;
            // 遍历文件的blocks数组，将对应的磁盘块设为空闲
            for (int j = 0; j < MAX_SIZE / BLOCK_SIZE + 1; j++) {
                if (current_user->files[i].blocks[j] != -1) {
                    bitmap[current_user->files[i].blocks[j]] = false;
                    current_user->files[i].blocks[j] = -1;
                }
            }
            // 提示删除文件成功，返回
            printf("删除文件成功：%s\n", name);
            return;
        }
    }
    // 没有找到匹配的文件名，提示错误信息
    printf("删除文件失败，没有找到该文件：%s\n", name);
}

// 打开文件函数，根据文件名在当前用户的目录中打开一个文件
void myopen(char *name) {
    // 检查是否有用户登录
    if (current_user == NULL) {
        printf("没有用户登录\n");
        return;
    }
    // 检查文件名是否合法
    if (strlen(name) == 0 || strlen(name) >= MAX_NAME) {
        printf("文件名不合法\n");
        return;
    }
    // 检查是否已经有打开的文件
    if (current_user->open_file != NULL) {
        printf("请先关闭打开的文件：%s\n", current_user->open_file->name);
        return;
    }
    // 遍历当前用户的目录，寻找匹配的文件名
    for (int i = 0; i < MAX_FILE; i++) {
        if (strcmp(current_user->files[i].name, name) == 0) {
            // 找到匹配的文件名，将当前用户的打开的文件设为该文件，提示打开文件成功，返回
            current_user->open_file = &current_user->files[i];
            printf("打开文件成功：%s\n", name);
            return;
        }
    }
    // 没有找到匹配的文件名，提示错误信息
    printf("打开文件失败，没有找到该文件：%s\n", name);
}

// 关闭文件函数，关闭当前用户打开的文件
void myclose() {
    // 检查是否有用户登录
    if (current_user == NULL) {
        printf("没有用户登录\n");
        return;
    }
    // 检查是否有打开的文件
    if (current_user->open_file == NULL) {
        printf("没有打开的文件\n");
        return;
    }
    // 将当前用户的打开的文件设为NULL，提示关闭文件成功，返回
    printf("关闭文件成功：%s\n", current_user->open_file->name);
    current_user->open_file = NULL;
}

// 读取文件函数，读取当前用户打开的文件的内容
void myread() {
    // 检查是否有用户登录
    if (current_user == NULL) {
        printf("没有用户登录\n");
        return;
    }
    // 检查是否有打开的文件
    if (current_user->open_file == NULL) {
        printf("没有打开的文件\n");
        return;
    }
    // 输出当前用户打开的文件的内容，返回
    printf("读取文件成功，文件内容如下：\n%s\n", current_user->open_file->content);
}

// 写入文件函数，向当前用户打开的文件写入内容
void mywrite(char *content) {
    // 检查是否有用户登录
    if (current_user == NULL) {
        printf("没有用户登录\n");
        return;
    }
    // 检查是否有打开的文件
    if (current_user->open_file == NULL) {
        printf("没有打开的文件\n");
        return;
    }
    // 检查当前用户打开的文件是否可写
    if (current_user->open_file->mode == 0) {
        printf("写入文件失败，该文件只读：%s\n", current_user->open_file->name);
        return;
    }
    // 检查写入内容是否合法
    if (strlen(content) == 0 || strlen(content) >= MAX_SIZE) {
        printf("写入内容不合法\n");
        return;
    }
    // 检查写入内容是否超过文件的最大大小
    if (strlen(content) > MAX_SIZE - current_user->open_file->size) {
        printf("写入内容失败，没有足够的文件空间\n");
        return;
    }
    // 将写入内容追加到当前用户打开的文件的内容中，更新文件的大小
    strcat(current_user->open_file->content, content);
    current_user->open_file->size += strlen(content);
    // 寻找空闲的磁盘块，分配给当前用户打开的文件
    for (int i = 0; i < MAX_SIZE / BLOCK_SIZE + 1; i++) {
        if (current_user->open_file->blocks[i] == -1) {
            // 找到空闲的磁盘块，将其设为占用，将其编号存储到文件的blocks数组中
            for (int j = 0; j < MAX_BLOCK; j++) {
                if (bitmap[j] == false) {
                    bitmap[j] = true;
                    current_user->open_file->blocks[i] = j;
                    break;
                }
            }
        }
    }
    // 提示写入文件成功，返回
    printf("写入文件成功：%s\n", current_user->open_file->name);
}

// 列出文件函数，列出当前用户的目录中的所有文件
void myls() {
    // 检查是否有用户登录
    if (current_user == NULL) {
        printf("没有用户登录\n");
        return;
    }
    // 输出当前用户的目录中的所有文件的文件名，文件大小，文件权限
    printf("当前用户的目录如下：\n");
    printf("文件名\t文件大小\t文件权限\n");
    for (int i = 0; i < MAX_FILE; i++) {
        if (current_user->files[i].name[0] != '\0') {
            printf("%s\t%d\t%d\n", current_user->files[i].name, current_user->files[i].size, current_user->files[i].mode);
        }
    }
}

// 退出函数，退出程序
void myexit() {
    // 检查是否有用户登录
    if (current_user == NULL) {
        printf("没有用户登录\n");
        return;
    }
    // 检查是否有打开的文件
    if (current_user->open_file != NULL) {
        printf("请先关闭打开的文件：%s\n", current_user->open_file->name);
        return;
    }
    // 提示退出程序，调用exit函数
    printf("退出程序，谢谢使用\n");
    exit(0);
}

// main 程序，调用文件系统的基本操作
int main() {
    // 初始化文件系统
    init();
    // 登录用户 user1
    login("user1");
    // 创建一个可写的文件 file1
    mycreate("file1", 1);
    // 打开文件 file1
    myopen("file1");
    // 向文件 file1 写入内容 "Hello, world!"
    mywrite("Hello, world!");
    // 关闭文件 file1
    myclose();
    // 创建一个只读的文件 file2
    mycreate("file2", 0);
    // 打开文件 file2
    myopen("file2");
    // 读取文件 file2 的内容
    myread();
    // 关闭文件 file2
    myclose();
    // 列出用户 user1 的目录
    myls();
    // 删除文件 file1
    mydelete("file1");
    // 删除文件 file2
    mydelete("file2");
    // 登出用户 user1
    logout();
    // 退出程序
    myexit();
    // 返回 0
    return 0;
}

#include <stdio.h>
#include <string.h>
// 定义文件系统的一些常量
#define MAX_USER 5 // 最大用户数
#define MAX_FILE 5 // 每个用户最多保存的文件数
#define MAX_NAME 20 // 文件名和用户名的最大长度
#define MAX_BLOCK 100 // 文件系统的最大块数
#define BLOCK_SIZE 512 // 每个块的大小，单位为字节

// 定义文件的保护措施
#define READ 1 // 可读
#define WRITE 2 // 可写
#define EXECUTE 4 // 可执行

// 定义文件的状态
#define CLOSED 0 // 关闭
#define OPENED 1 // 打开

// 定义文件的类型
#define DIR 0 // 目录
#define REG 1 // 普通文件

// 定义文件的结构体
typedef struct file {
    char name[MAX_NAME]; // 文件名
    int type; // 文件类型
    int size; // 文件大小，单位为字节
    int protect; // 文件保护措施
    int status; // 文件状态
    int block[MAX_BLOCK]; // 文件占用的块号
    int block_count; // 文件占用的块数
} file;

// 定义用户的结构体
typedef struct user {
    char name[MAX_NAME]; // 用户名
    file files[MAX_FILE]; // 用户拥有的文件
    int file_count; // 用户拥有的文件数
    int current_file; // 用户当前打开的文件的索引，-1表示没有打开的文件
} user;

// 定义文件系统的结构体
typedef struct file_system {
    user users[MAX_USER]; // 文件系统的用户
    int user_count; // 文件系统的用户数
    int current_user; // 文件系统当前的用户的索引，-1表示没有登录的用户
    char disk[MAX_BLOCK][BLOCK_SIZE]; // 文件系统的磁盘空间
    int free_block[MAX_BLOCK]; // 文件系统的空闲块号
    int free_block_count; // 文件系统的空闲块数
} file_system;

// 初始化文件系统
void init_file_system(file_system *fs) {
    // 初始化用户
    fs->user_count = 0;
    fs->current_user = -1;
    for (int i = 0; i < MAX_USER; i++) {
        fs->users[i].file_count = 0;
        fs->users[i].current_file = -1;
    }
    // 初始化磁盘空间
    fs->free_block_count = MAX_BLOCK;
    for (int i = 0; i < MAX_BLOCK; i++) {
        fs->free_block[i] = i;
    }
}

// 创建一个用户
int create_user(file_system *fs, char *name) {
    // 检查用户是否已满
    if (fs->user_count == MAX_USER) {
        printf("用户已满，无法创建新用户\n");
        return -1;
    }
    // 检查用户名是否重复
    for (int i = 0; i < fs->user_count; i++) {
        if (strcmp(fs->users[i].name[0], name[0]) == 0) {
            printf("用户名已存在，无法创建新用户\n");
            return -1;
        }
    }
    // 创建新用户
    strcpy(fs->users[fs->user_count].name, name);
    fs->user_count++;
    printf("创建用户成功\n");
    return 0;
}

// 删除一个用户
int delete_user(file_system *fs, char *name) {
    // 检查是否有用户登录
    if (fs->current_user != -1) {
        printf("请先退出当前用户\n");
        return -1;
    }
    // 查找要删除的用户
    int index = -1;
    for (int i = 0; i < fs->user_count; i++) {
        if (strcmp(fs->users[i].name[0], name[0]) == 0) {
            index = i;
            break;
        }
    }
    // 检查用户是否存在
    if (index == -1) {
        printf("用户不存在，无法删除\n");
        return -1;
    }
    // 删除用户
    for (int i = index; i < fs->user_count - 1; i++) {
        fs->users[i] = fs->users[i + 1];
    }
    fs->user_count--;
    printf("删除用户成功\n");
    return 0;
}

// 登录一个用户
int login_user(file_system *fs, char *name) {
    // 检查是否有用户登录
    if (fs->current_user != -1) {
        printf("请先退出当前用户\n");
        return -1;
    }
    // 查找要登录的用户
    int index = -1;
    for (int i = 0; i < fs->user_count; i++) {
        if (strcmp(fs->users[i].name[0], name[0]) == 0) {
            index = i;
            break;
        }
    }
    // 检查用户是否存在
    if (index == -1) {
        printf("用户不存在，无法登录\n");
        return -1;
    }
    // 登录用户
    fs->current_user = index;
    printf("登录用户成功\n");
    return 0;
}

// 退出当前用户
int logout_user(file_system *fs) {
    // 检查是否有用户登录
    if (fs->current_user == -1) {
        printf("没有用户登录，无法退出\n");
        return -1;
    }
    // 检查是否有文件打开
    if (fs->users[fs->current_user].current_file != -1) {
        printf("请先关闭当前文件\n");
        return -1;
    }
    // 退出用户
    fs->current_user = -1;
    printf("退出用户成功\n");
    return 0;
}

// 创建一个文件
int mycreate(file_system *fs, char *name, int type, int protect) {
    // 检查是否有用户登录
    if (fs->current_user == -1) {
        printf("没有用户登录，无法创建文件\n");
        return -1;
    }
    // 检查文件类型是否合法
    if (type != DIR && type != REG) {
        printf("文件类型不合法，无法创建文件\n");
        return -1;
    }
    // 检查文件保护措施是否合法
    if (protect < 0 || protect > 7) {
        printf("文件保护措施不合法，无法创建文件\n");
        return -1;
    }
    // 检查文件是否已满
    if (fs->users[fs->current_user].file_count == MAX_FILE) {
        printf("文件已满，无法创建新文件\n");
        return -1;
    }
    // 检查文件名是否重复
    for (int i = 0; i < fs->users[fs->current_user].file_count; i++) {
        if (strcmp(fs->users[fs->current_user].files[i].name, name) == 0) {
            printf("文件名已存在，无法创建新文件\n");
            return -1;
        }
    }
    // 创建新文件
    strcpy(fs->users[fs->current_user].files[fs->users[fs->current_user].file_count].name, name);
    fs->users[fs->current_user].files[fs->users[fs->current_user].file_count].type = type;
    fs->users[fs->current_user].files[fs->users[fs->current_user].file_count].size = 0;
    fs->users[fs->current_user].files[fs->users[fs->current_user].file_count].protect = protect;
    fs->users[fs->current_user].files[fs->users[fs->current_user].file_count].status = CLOSED;
    fs->users[fs->current_user].files[fs->users[fs->current_user].file_count].block_count = 0;
    fs->users[fs->current_user].file_count++;
    printf("创建文件成功\n");
    return 0;
}
// 删除一个文件
int mydelete(file_system *fs, char *name) {
    // 检查是否有用户登录
    if (fs->current_user == -1) {
        printf("没有用户登录，无法删除文件\n");
        return -1;
    }
    // 查找要删除的文件
    int index = -1;
    for (int i = 0; i < fs->users[fs->current_user].file_count; i++) {
        if (strcmp(fs->users[fs->current_user].files[i].name, name) == 0) {
            index = i;
            break;
        }
    }
    // 检查文件是否存在
    if (index == -1) {
        printf("文件不存在，无法删除\n");
        return -1;
    }
    // 检查文件是否打开
    if (fs->users[fs->current_user].files[index].status == OPENED) {
        printf("文件已打开，无法删除\n");
        return -1;
    }
    // 删除文件
    for (int i = 0; i < fs->users[fs->current_user].files[index].block_count; i++) {
        // 释放文件占用的块
        fs->free_block[fs->free_block_count] = fs->users[fs->current_user].files[index].block[i];
        fs->free_block_count++;
    }
    for (int i = index; i < fs->users[fs->current_user].file_count - 1; i++) {
        // 移动文件
        fs->users[fs->current_user].files[i] = fs->users[fs->current_user].files[i + 1];
    }
    fs->users[fs->current_user].file_count--;
    printf("删除文件成功\n");
    return 0;
}

// 打开一个文件
int myopen(file_system *fs, char *name) {
    // 检查是否有用户登录
    if (fs->current_user == -1) {
        printf("没有用户登录，无法打开文件\n");
        return -1;
    }
    // 查找要打开的文件
    int index = -1;
    for (int i = 0; i < fs->users[fs->current_user].file_count; i++) {
        if (strcmp(fs->users[fs->current_user].files[i].name, name) == 0) {
            index = i;
            break;
        }
    }
    // 检查文件是否存在
    if (index == -1) {
        printf("文件不存在，无法打开\n");
        return -1;
    }
    // 检查文件是否已打开
    if (fs->users[fs->current_user].files[index].status == OPENED) {
        printf("文件已打开，无需重复打开\n");
        return -1;
    }
    // 检查是否有其他文件打开
    if (fs->users[fs->current_user].current_file != -1) {
        printf("请先关闭当前文件\n");
        return -1;
    }
    // 打开文件
    fs->users[fs->current_user].files[index].status = OPENED;
    fs->users[fs->current_user].current_file = index;
    printf("打开文件成功\n");
    return 0;
}

// 关闭当前文件
int myclose(file_system *fs) {
    // 检查是否有用户登录
    if (fs->current_user == -1) {
        printf("没有用户登录，无法关闭文件\n");
        return -1;
    }
    // 检查是否有文件打开
    if (fs->users[fs->current_user].current_file == -1) {
        printf("没有文件打开，无法关闭文件\n");
        return -1;
    }
    // 关闭文件
    fs->users[fs->current_user].files[fs->users[fs->current_user].current_file].status = CLOSED;
    fs->users[fs->current_user].current_file = -1;
    printf("关闭文件成功\n");
    return 0;
}

// 读取当前文件的内容
int myread(file_system *fs) {
    // 检查是否有用户登录
    if (fs->current_user == -1) {
        printf("没有用户登录，无法读取文件\n");
        return -1;
    }
    // 检查是否有文件打开
    if (fs->users[fs->current_user].current_file == -1) {
        printf("没有文件打开，无法读取文件\n");
        return -1;
    }
    // 检查文件是否可读
    if ((fs->users[fs->current_user].files[fs->users[fs->current_user].current_file].protect & READ) == 0) {
        printf("文件不可读，无法读取文件\n");
        return -1;
    }
    // 读取文件
    printf("文件内容如下：\n");
    for (int i = 0; i < fs->users[fs->current_user].files[fs->users[fs->current_user].current_file].block_count; i++) {
        // 读取文件占用的块
        printf("%s", (char *)fs->disk[fs->users[fs->current_user].files[fs->users[fs->current_user].current_file].block[i]]);
    }
    printf("\n");
    printf("读取文件成功\n");
    return 0;
}

// 写入当前文件的内容
int mywrite(file_system *fs, char *content) {
    // 检查是否有用户登录
    if (fs->current_user == -1) {
        printf("没有用户登录，无法写入文件\n");
        return -1;
    }
    // 检查是否有文件打开
    if (fs->users[fs->current_user].current_file == -1) {
        printf("没有文件打开，无法写入文件\n");
        return -1;
    }
    // 检查文件是否可写
    if ((fs->users[fs->current_user].files[fs->users[fs->current_user].current_file].protect & WRITE) == 0) {
        printf("文件不可写，无法写入文件\n");
        return -1;
    }
    // 检查文件是否是普通文件
    if (fs->users[fs->current_user].files[fs->users[fs->current_user].current_file].type != REG) {
        printf("文件不是普通文件，无法写入文件\n");
        return -1;
    }
    // 写入文件
    int len = strlen(content); // 写入内容的长度
    int need = (len + BLOCK_SIZE - 1) / BLOCK_SIZE; // 需要的块数
    int have = fs->users[fs->current_user].files[fs->users[fs->current_user].current_file].block_count; // 已有的块数
    int free = fs->free_block_count; // 空闲的块数
    // 检查空间是否足够
    if (need > have + free) {
        printf("空间不足，无法写入文件\n");
        return -1;
    }
    // 释放多余的块
    for (int i = need; i < have; i++) {
        fs->free_block[fs->free_block_count] = fs->users[fs->current_user].files[fs->users[fs->current_user].current_file].block[i];
        fs->free_block_count++;
    }
    // 分配新的块
    for (int i = have; i < need; i++) {
        fs->users[fs->current_user].files[fs->users[fs->current_user].current_file].block[i] = fs->free_block[fs->free_block_count - 1];
        fs->free_block_count--;
    }
    // 更新文件的块数和大小
    fs->users[fs->current_user].files[fs->users[fs->current_user].current_file].block_count = need;
    fs->users[fs->current_user].files[fs->users[fs->current_user].current_file].size = len;
    // 复制内容到磁盘空间
    for (int i = 0; i < need; i++) {
        strncpy(fs->disk[fs->users[fs->current_user].files[fs->users[fs->current_user].current_file].block[i]], content + i * BLOCK_SIZE, BLOCK_SIZE - 1);
fs->disk[fs->users[fs->current_user].files[fs->users[fs->current_user].current_file].block[i]][BLOCK_SIZE - 1] = '\0';
    }
    printf("写入文件成功\n");
    return 0;
}

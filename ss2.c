#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 5

int available[MAX_RESOURCES];       
int max[MAX_PROCESSES][MAX_RESOURCES];   
int allocation[MAX_PROCESSES][MAX_RESOURCES]; 
int need[MAX_PROCESSES][MAX_RESOURCES];   
int process_count = 0;              
int resource_count = 0;             

void initializeSystem();
void addProcess();
void requestResources();
void releaseResources();
void viewSystemStatus();
void displayMenu();
bool isSafeState();
bool canProceed(int process, int request[]);
void calculateNeed();

void initializeSystem() {
    printf("请输入资源种类数 (M > 3) 和每种资源的初始数量，以空格隔开：\n");
    scanf("%d", &resource_count);
    if (resource_count <= 3) {
        printf("资源种类数必须大于3\n");
        exit(1);
    }

    for (int i = 0; i < resource_count; i++) {
        scanf("%d", &available[i]);
    }

    printf("请输入进程数 (N > 5): ");
    scanf("%d", &process_count);
    if (process_count <= 5) {
        printf("进程数必须大于5\n");
        exit(1);
    }

    printf("请输入每个进程对资源的最大需求量，以空格隔开:\n");
    for (int i = 0; i < process_count; i++) {
        printf("进程 %d: ", i + 1);
        for (int j = 0; j < resource_count; j++) {
            scanf("%d", &max[i][j]);
            allocation[i][j] = 0;
        }
    }
    calculateNeed();
}





void addProcess() {
    if (process_count >= MAX_PROCESSES) {
        printf("无法新增进程，达到最大进程数限制\n");
        return;
    }

    printf("新增进程 %d 的最大需求量:\n", process_count + 1);
    for (int i = 0; i < resource_count; i++) {
        printf("资源 %d: ", i + 1);
        scanf("%d", &max[process_count][i]);
        allocation[process_count][i] = 0;
    }
    process_count++;
    calculateNeed();
}

void releaseResources() {
    int process;
    printf("请输入要结束的进程编号 (1-%d): ", process_count);
    scanf("%d", &process);
    process--;

    if (process < 0 || process >= process_count) {
        printf("无效的进程编号\n");
        return;
    }

    for (int i = 0; i < resource_count; i++) {
        available[i] += allocation[process][i];
        allocation[process][i] = 0;
        need[process][i] = max[process][i];
    }

    printf("进程 %d 已结束，资源已归还系统\n", process + 1);
}
 

void requestResources() {
    int process, request[MAX_RESOURCES];
    printf("请输入发起请求的进程编号 (1-%d): ", process_count);
    scanf("%d", &process);
    process--;

    if (process < 0 || process >= process_count) {
        printf("无效的进程编号\n");
        return;
    }

    printf("请输入请求的资源数量:\n");
    for (int i = 0; i < resource_count; i++) {
        printf("资源 %d: ", i + 1);
        scanf("%d", &request[i]);
    }

    if (canProceed(process, request)) {
        printf("资源分配成功\n");
    } else {
        printf("资源分配失败，可能导致死锁\n");
    }
}

bool canProceed(int process, int request[]) {
    for (int i = 0; i < resource_count; i++) {
        if (request[i] > need[process][i] || request[i] > available[i]) {
            return false;
        }
    }

    for (int i = 0; i < resource_count; i++) {
        available[i] -= request[i];
        allocation[process][i] += request[i];
        need[process][i] -= request[i];
    }

    bool safe = isSafeState();

    if (!safe) {
        for (int i = 0; i < resource_count; i++) {
            available[i] += request[i];
            allocation[process][i] -= request[i];
            need[process][i] += request[i];
        }
    }

    return safe;
}

bool isSafeState() {
    int work[MAX_RESOURCES];
    bool finish[MAX_PROCESSES] = { false };

    for (int i = 0; i < resource_count; i++) {
        work[i] = available[i];
    }

    while (true) {
        bool found = false;
        for (int i = 0; i < process_count; i++) {
            if (!finish[i]) {
                bool canAllocate = true;
                for (int j = 0; j < resource_count; j++) {
                    if (need[i][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }

                if (canAllocate) {
                    for (int j = 0; j < resource_count; j++) {
                        work[j] += allocation[i][j];
                    }
                    finish[i] = true;
                    found = true;
                }
            }
        }

        if (!found) {
            break;
        }
    }

    for (int i = 0; i < process_count; i++) {
        if (!finish[i]) {
            return false;
        }
    }

    return true;
}

void viewSystemStatus() {
    printf("系统状态:\n");
    printf("进程数: %d, 资源种类数: %d\n", process_count, resource_count);

    printf("\n系统可用资源:\n");
    for (int i = 0; i < resource_count; i++) {
        printf("资源 %d: %d\n", i + 1, available[i]);
    }

    printf("\n进程资源状态:\n");
    for (int i = 0; i < process_count; i++) {
        printf("进程 %d\n", i + 1);
        printf("最大需求量: ");
        for (int j = 0; j < resource_count; j++) {
            printf("%d ", max[i][j]);
        }
        printf("\n已分配量: ");
        for (int j =0; j < resource_count; j++) {
            printf("%d ", allocation[i][j]);
        }
        printf("\n剩余需求量: ");
        for (int j = 0; j < resource_count; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    printf("\n系统安全序列:\n");
    if (isSafeState()) {
        printf("系统当前处于安全状态\n");
    } else {
        printf("系统当前不处于安全状态\n");
    }
}

void displayMenu() {
    int choice;

    while (true) {
        printf("\n=== 菜单 ===\n");
        printf("1. 初始化系统\n");
        printf("2. 新增进程\n");
        printf("3. 请求资源\n");
        printf("4. 结束进程\n");
        printf("5. 查看系统状态\n");
        printf("6. 退出\n");
        printf("请输入您的选择: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                initializeSystem();
                break;
            case 2:
                addProcess();
                break;
            case 3:
                requestResources();
                break;
            case 4:
                releaseResources();
                break;
            case 5:
                viewSystemStatus();
                break;
            case 6:
                exit(0);
            default:
                printf("无效的选择，请重试\n");
        }
    }
}

void calculateNeed() {
    for (int i = 0; i < process_count; i++) {
        for (int j = 0; j < resource_count; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

void displaySafeSequence() {
    int work[MAX_RESOURCES];
    bool finish[MAX_PROCESSES] = { false };
    int safe_sequence[MAX_PROCESSES];
    int seq_index = 0;

    // 备份当前系统的资源状态
    int temp_available[MAX_RESOURCES];
    for (int i = 0; i < resource_count; i++) {
        temp_available[i] = available[i];
    }

    while (seq_index < process_count) {
        bool found = false;

        for (int i = 0; i < process_count; i++) {
            if (!finish[i]) {
                bool canAllocate = true;
                for (int j = 0; j < resource_count; j++) {
                    if (need[i][j] > temp_available[j]) {
                        canAllocate = false;
                        break;
                    }
                }

                if (canAllocate) {
                    // 更新系统可用资源
                    for (int j = 0; j < resource_count; j++) {
                        temp_available[j] += allocation[i][j];
                    }
                    // 标记进程已完成执行
                    finish[i] = true;
                    // 将进程编号添加到安全序列中
                    safe_sequence[seq_index++] = i;
                    found = true;
                }
            }
        }

        if (!found) {
            printf("系统处于不安全状态，无法找到安全序列\n");
            return;
        }
    }

    // 输出安全序列
    printf("系统安全序列: ");
    for (int i = 0; i < process_count; i++) {
        printf("%d ", safe_sequence[i]);
    }
    printf("\n");
}

int main() {
    displayMenu();
    displaySafeSequence();
    return 0;
}


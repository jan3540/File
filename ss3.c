#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 5

// 定义进程结构体
typedef struct {
    int max[MAX_RESOURCES];         // 最大需求资源
    int allocation[MAX_RESOURCES];  // 已分配资源
    int need[MAX_RESOURCES];        // 还需资源
    bool finished;                  // 是否完成
} Process;

int available[MAX_RESOURCES];  // 系统可用资源
Process processes[MAX_PROCESSES];  // 系统进程
int numProcesses;  // 进程数
int numResources;  // 资源种类数
int safeSequence[MAX_PROCESSES];  // 安全序列
bool isSafe;  // 系统是否处于安全状态

// 函数声明
void initializeSystem();
void displayMenu();
void requestResources();
void releaseResources();
void addProcess();
void removeProcess();
void displayState();
bool isSafeState();
void calculateNeed();
bool canAllocate(int processIndex, int request[]);
void handleRequest(int processIndex, int request[]);
void handleRelease(int processIndex);

int main() {
    initializeSystem();  // 初始化系统
    displayMenu();       // 显示菜单
    return 0;
}

// 初始化系统资源和进程
void initializeSystem() {
    printf("请输入资源种类数(M > 3): ");
    scanf("%d", &numResources);
    if (numResources < 4 || numResources > MAX_RESOURCES) {
        printf("资源种类数必须在 4 到 %d 之间。\n", MAX_RESOURCES);
        exit(1);
    }
    
    printf("请输入每种资源的总数: ");
    for (int i = 0; i < numResources; i++) {
        scanf("%d", &available[i]);
    }
    
    printf("请输入进程数(N > 5): ");
    scanf("%d", &numProcesses);
    if (numProcesses <= 5 || numProcesses > MAX_PROCESSES) {
        printf("进程数必须在 6 到 %d 之间。\n", MAX_PROCESSES);
        exit(1);
    }
    
    // 输入每个进程的最大需求资源
    for (int i = 0; i < numProcesses; i++) {
        printf("请输入进程 %d 的最大资源需求: ", i);
        for (int j = 0; j < numResources; j++) {
            scanf("%d", &processes[i].max[j]);
            processes[i].allocation[j] = 0;  // 初始化已分配资源为 0
        }
        processes[i].finished = false;  // 初始化进程未完成
    }
    
    calculateNeed();  // 计算每个进程的需求
}

// 计算每个进程的需求
void calculateNeed() {
    for (int i = 0; i < numProcesses; i++) {
        for (int j = 0; j < numResources; j++) {
            processes[i].need[j] = processes[i].max[j] - processes[i].allocation[j];
        }
    }
}

// 显示菜单并处理用户输入
void displayMenu() {
    int choice;
    do {
        printf("\n银行家算法菜单\n");
        printf("1. 请求资源\n");
        printf("2. 释放资源\n");
        printf("3. 添加进程\n");
        printf("4. 删除进程\n");
        printf("5. 显示状态\n");
        printf("6. 退出\n");
        printf("请输入你的选择: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                requestResources();  // 请求资源
                break;
            case 2:
                releaseResources();  // 释放资源
                break;
            case 3:
                addProcess();  // 添加进程
                break;
            case 4:
                removeProcess();  // 删除进程
                break;
            case 5:
                displayState();  // 显示状态
                break;
            case 6:
                printf("退出...\n");
                break;
            default:
                printf("无效选择。请重试。\n");
        }
    } while (choice != 6);
}

// 处理资源请求
void requestResources() {
    int processIndex, request[MAX_RESOURCES];
    printf("请输入进程索引 (0 到 %d): ", numProcesses - 1);
    scanf("%d", &processIndex);
    
    if (processIndex < 0 || processIndex >= numProcesses) {
        printf("无效的进程索引。\n");
        return;
    }
    
    printf("请输入资源请求: ");
    for (int i = 0; i < numResources; i++) {
        scanf("%d", &request[i]);
    }
    
    handleRequest(processIndex, request);
}

// 处理资源释放
void releaseResources() {
    int processIndex, release[MAX_RESOURCES];
    printf("请输入进程索引 (0 到 %d): ", numProcesses - 1);
    scanf("%d", &processIndex);
    
    if (processIndex < 0 || processIndex >= numProcesses) {
        printf("无效的进程索引。\n");
        return;
    }
    
    printf("请输入资源释放: ");
    for (int i = 0; i < numResources; i++) {
        scanf("%d", &release[i]);
    }
    
    handleRelease(processIndex);
}

// 处理资源请求的具体逻辑
void handleRequest(int processIndex, int request[]) {
    if (canAllocate(processIndex, request)) {
        // 暂时分配资源
        for (int i = 0; i < numResources; i++) {
            available[i] -= request[i];
            processes[processIndex].allocation[i] += request[i];
            processes[processIndex].need[i] -= request[i];
        }
        
        // 检查系统是否处于安全状态
        if (isSafeState()) {
            printf("资源分配成功。\n");
        } else {
            // 回滚分配
            for (int i = 0; i < numResources; i++) {
                available[i] += request[i];
                processes[processIndex].allocation[i] -= request[i];
                processes[processIndex].need[i] += request[i];
            }
            printf("分配将导致不安全状态。请求被拒绝。\n");
        }
    } else {
        printf("请求无法被满足。\n");
    }
}

// 检查是否可以分配资源
bool canAllocate(int processIndex, int request[]) {
    for (int i = 0; i < numResources; i++) {
        if (request[i] > processes[processIndex].need[i] || request[i] > available[i]) {
            return false;
        }
    }
    return true;
}

// 处理资源释放的具体逻辑
void handleRelease(int processIndex) {
    for (int i = 0; i < numResources; i++) {
        available[i] += processes[processIndex].allocation[i];
        processes[processIndex].allocation[i] = 0;
        processes[processIndex].need[i] = processes[processIndex].max[i];
    }
    printf("资源释放成功。\n");
}

// 添加新进程
void addProcess() {
    if (numProcesses >= MAX_PROCESSES) {
        printf("无法添加更多进程。\n");
        return;
    }
    
    printf("请输入进程 %d 的最大资源需求: ", numProcesses);
    for (int i = 0; i < numResources; i++) {
        scanf("%d", &processes[numProcesses].max[i]);
        processes[numProcesses].allocation[i] = 0;
    }
    processes[numProcesses].finished = false;
    numProcesses++;
    calculateNeed();
    printf("进程添加成功。\n");
}

// 删除进程
void removeProcess() {
    int processIndex;
    printf("请输入要删除的进程索引 (0 到 %d): ", numProcesses - 1);
    scanf("%d", &processIndex);
    
    if (processIndex < 0 || processIndex >= numProcesses) {
        printf("无效的进程索引。\n");
        return;
    }
    
    handleRelease(processIndex);
    
    for (int i = processIndex; i < numProcesses - 1; i++) {
        processes[i] = processes[i + 1];
    }
    numProcesses--;
    printf("进程删除成功。\n");
}

// 显示系统当前状态
void displayState() {
    printf("\n当前系统状态:\n");
    printf("可用资源: ");
    for (int i = 0; i < numResources; i++) {
        printf("%d ", available[i]);
    }
    printf("\n");
    
    printf("进程 最大需求 已分配 还需\n");
    for (int i = 0; i < numProcesses; i++) {
        printf("P%d ", i);
        for (int j = 0; j < numResources; j++) {
            printf("%d ", processes[i].max[j]);
        }
        printf("| ");
        for (int j = 0; j < numResources; j++) {
            printf("%d ", processes[i].allocation[j]);
        }
        printf("| ");
        for (int j = 0; j < numResources; j++) {
            printf("%d ", processes[i].need[j]);
        }
        printf("\n");
    }
    
    printf("当前安全序列: ");
    if (isSafe) {
        for (int i = 0; i < numProcesses; i++) {
            printf("P%d ", safeSequence[i]);
        }
    } else {
        printf("无安全序列。");
    }
    printf("\n");
}

// 检查系统是否处于安全状态
bool isSafeState() {
    int work[MAX_RESOURCES];
    bool finish[MAX_PROCESSES] = {false};
    int safeSequenceIndex = 0;
    
    for (int i = 0; i < numResources; i++) {
        work[i] = available[i];
    }
    
    while (true) {
        bool found = false;
        for (int i = 0; i < numProcesses; i++) {
            if (!finish[i]) {
                bool canProceed = true;
                for (int j = 0; j < numResources; j++) {
                    if (processes[i].need[j] > work[j]) {
                        canProceed = false;
                        break;
                    }
                }
                
                if (canProceed) {
                    for (int j = 0; j < numResources; j++) {
                        work[j] += processes[i].allocation[j];
                    }
                    finish[i] = true;
                    safeSequence[safeSequenceIndex++] = i;
                    found = true;
                }
            }
        }
        
        if (!found) {
            break;
        }
    }
    
    for (int i = 0; i < numProcesses; i++) {
        if (!finish[i]) {
            isSafe = false;
            return false;
        }
    }
    
    isSafe = true;
    return true;
}

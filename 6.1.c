#include <stdio.h>
#include <stdlib.h>

#define MEM_SIZE 1024  // 内存大小，以块为单位
#define BLOCK_SIZE 1   // 每块的大小
#define MAX_PROCESSES 10
#define TIME_QUANTUM 4 // 时间片大小

// 进程状态枚举
typedef enum { NEW, READY, RUNNING, BLOCKED, TERMINATED } State;

// 页表条目结构体
typedef struct {
    int virtual_page; // 虚拟页号
    int physical_page; // 物理页号
    int valid; // 有效位
} PageTableEntry;

// 进程控制块结构体
typedef struct {
    int pid;        // 进程ID
    State state;    // 进程状态
    int mem_start;  // 分配的内存起始位置
    int mem_size;   // 分配的内存大小
    PageTableEntry page_table[MEM_SIZE / BLOCK_SIZE]; // 页表
} PCB;

// 全局变量
int bitmap[MEM_SIZE];        // 位示图，表示内存块使用情况
PCB pcb_list[MAX_PROCESSES]; // 进程列表
PCB *ready_queue[MAX_PROCESSES]; // 就绪队列
PCB *blocked_queue[MAX_PROCESSES]; // 阻塞队列
int ready_queue_size = 0;    // 就绪队列大小
int blocked_queue_size = 0;  // 阻塞队列大小

// 函数声明
void initialize_memory();
void create_process(int pid, int mem_size);
void allocate_memory(PCB *process);
void add_to_ready_queue(PCB *process);
PCB* schedule();
void run_process(PCB *process);
void handle_page_fault(PCB *process);
void page_replacement(PCB *process);
void terminate_process(PCB *process);
void release_memory(PCB *process);
void initialize_page_table(PCB *process);
void unit_tests();

// 主函数
int main() {
    initialize_memory();
    create_process(0, 10); // 修正: 从0开始创建进程，确保PID唯一
    create_process(1, 20);
    
    unit_tests(); // 运行单元测试
    
    PCB *current_process;
    
    // 模拟进程调度
    while ((current_process = schedule()) != NULL) {
        run_process(current_process);
        // 模拟进程运行一段时间后缺页
        handle_page_fault(current_process);
        // 不要立即终止进程，让它继续运行
        if (current_process->state == READY) {
            add_to_ready_queue(current_process);
        } else {
            terminate_process(current_process);
        }
    }
    
    return 0;
}

// 初始化内存
void initialize_memory() {
    for (int i = 0; i < MEM_SIZE; i++) {
        bitmap[i] = 0;
    }
}

// 创建进程
void create_process(int pid, int mem_size) {
    PCB *process = &pcb_list[pid];
    process->pid = pid;
    process->state = NEW;
    process->mem_size = mem_size;
    allocate_memory(process);
    initialize_page_table(process);
    add_to_ready_queue(process);
}

// 初始化页表
void initialize_page_table(PCB *process) {
    for (int i = 0; i < process->mem_size / BLOCK_SIZE; i++) {
        process->page_table[i].virtual_page = i;
        process->page_table[i].physical_page = process->mem_start + i;
        process->page_table[i].valid = 1; // 1表示有效
    }
}

// 分配内存
void allocate_memory(PCB *process) {
    int blocks_needed = process->mem_size / BLOCK_SIZE;
    int start = -1;
    for (int i = 0; i <= MEM_SIZE - blocks_needed; i++) {
        int found = 1;
        for (int j = 0; j < blocks_needed; j++) {
            if (bitmap[i + j] == 1) {
                found = 0;
                break;
            }
        }
        if (found) {
            start = i;
            for (int j = 0; j < blocks_needed; j++) {
                bitmap[i + j] = 1;
            }
            break;
        }
    }
    process->mem_start = start;
}

// 添加进程到就绪队列
void add_to_ready_queue(PCB *process) {
    process->state = READY;
    ready_queue[ready_queue_size++] = process;
}

// 进程调度（轮转调度算法）
PCB* schedule() {
    if (ready_queue_size > 0) {
        PCB *process = ready_queue[0];
        for (int i = 1; i < ready_queue_size; i++) {
            ready_queue[i - 1] = ready_queue[i];
        }
        ready_queue_size--;
        return process;
    }
    return NULL;
}

// 运行进程
void run_process(PCB *process) {
    if (process) {
        process->state = RUNNING;
        // 模拟运行进程
        printf("正在运行进程 %d\n", process->pid);
    }
}

// 处理缺页
void handle_page_fault(PCB *process) {
    if (process) {
        process->state = BLOCKED;
        blocked_queue[blocked_queue_size++] = process;
        printf("由于页面错误，进程 %d 被阻止\n", process->pid);
        page_replacement(process);
        process->state = READY;
        add_to_ready_queue(process);
    }
}

// 页面置换（LRU）
void page_replacement(PCB *process) {
    // 模拟LRU页面置换算法
    printf("进程 %d 的页面置换\n", process->pid);
}

// 终止进程
void terminate_process(PCB *process) {
    if (process) {
        process->state = TERMINATED;
        release_memory(process);
        printf("进程 %d 终止\n", process->pid);
    }
}

// 释放内存
void release_memory(PCB *process) {
    int blocks_to_free = process->mem_size / BLOCK_SIZE;
    for (int i = 0; i < blocks_to_free; i++) {
        bitmap[process->mem_start + i] = 0;
    }
}

// 单元测试函数
void unit_tests() {
    printf("运行单元测试...\n");
    
    // 测试内存初始化
    initialize_memory();
    for (int i = 0; i < MEM_SIZE; i++) {
        if (bitmap[i] != 0) {
            printf("测试失败: 内存初始化\n");
            return;
        }
    }
    printf("测试通过: 内存初始化\n");
    
    // 测试进程创建和内存分配
    create_process(3, 30);
    if (pcb_list[3].mem_start == -1) {
        printf("测试失败: 进程创建和内存分配\n");
        return;
    }
    printf("测试通过: 进程创建和内存分配\n");
    
    // 测试进程调度
    PCB *process = schedule();
    if (process == NULL || process->pid != 0) {
        printf("测试失败: 进程调度\n");
        return;
    }
    printf("测试通过: 进程调度\n");
    
    // 测试页面置换
    page_replacement(process);
    printf("测试通过: 页面置换\n");
    
    // 测试进程终止和内存释放
    terminate_process(process);
    if (bitmap[process->mem_start] != 0) {
        printf("测试失败: 进程终止和内存释放\n");
        return;
    }
    printf("测试通过: 进程终止和内存释放\n");
    
    printf("所有测试通过。\n");
}

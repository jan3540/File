#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 10  // 箱子的大小

sem_t empty_slots;   // 空槽计数信号量
sem_t frames;        // 车架计数信号量
sem_t wheels;        // 车轮计数信号量
pthread_mutex_t box_mutex;  // 箱子互斥锁

void *worker1(void *arg) {
    while (1) {
        sleep(rand() % 3);  // 模拟加工车架的时间
        sem_wait(&empty_slots);  // 减少一个空槽
        pthread_mutex_lock(&box_mutex);  // 访问箱子
        printf("工人1: 生产了一个车架并放入箱中\n");
        sem_post(&frames);  // 增加一个车架
        pthread_mutex_unlock(&box_mutex);  // 释放箱子
    }
    return NULL;
}

void *worker2(void *arg) {
    while (1) {
        sleep(rand() % 2);  // 模拟加工车轮的时间
        sem_wait(&empty_slots);  // 减少一个空槽
        pthread_mutex_lock(&box_mutex);  // 访问箱子
        printf("工人2: 生产了一个车轮并放入箱中\n");
        sem_post(&wheels);  // 增加一个车轮
        pthread_mutex_unlock(&box_mutex);  // 释放箱子
    }
    return NULL;
}

void *worker3(void *arg) {
    int bike_count = 0; // 记录组装的自行车数量
    while (1) {
        sem_wait(&frames);  // 取一个车架
        sem_wait(&wheels);  // 取第一个车轮
        sem_wait(&wheels);  // 取第二个车轮
        pthread_mutex_lock(&box_mutex);  // 访问箱子
        bike_count++;
        printf("工人3: 取出一个车架和两个车轮，组装了一台自行车 (总共组装了 %d 台自行车)\n", bike_count);
        sem_post(&empty_slots);  // 增加一个空槽
        sem_post(&empty_slots);  // 增加另一个空槽
        sem_post(&empty_slots);  // 增加第三个空槽
        pthread_mutex_unlock(&box_mutex);  // 释放箱子
        sleep(rand() % 4);  // 模拟组装自行车的时间
    }
    return NULL;
}

int main() {
    pthread_t tid1, tid2, tid3;

    // 初始化信号量和互斥锁
    sem_init(&empty_slots, 0, N);
    sem_init(&frames, 0, 0);
    sem_init(&wheels, 0, 0);
    pthread_mutex_init(&box_mutex, NULL);

    // 创建线程
    pthread_create(&tid1, NULL, worker1, NULL);
    pthread_create(&tid2, NULL, worker2, NULL);
    pthread_create(&tid3, NULL, worker3, NULL);

    // 等待线程完成
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);

    // 销毁信号量和互斥锁
    sem_destroy(&empty_slots);
    sem_destroy(&frames);
    sem_destroy(&wheels);
    pthread_mutex_destroy(&box_mutex);

    return 0;
}

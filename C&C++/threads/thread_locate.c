#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

// 定义随机递归深度函数
int random_depth(int seed) {
    seed--;
    if (seed == 0) {
        return 0;
    }else{
        retrurn random_depth(seed);
    }
}

// 生成一系列线程，定位线程所在内存地址，栈帧起始和结束，并打印出来
// 定义线程函数
int *thread_func(void *arg) {
    int depth = rand()%100;
    int res =  random_depth(depth);
    printf("Thread ID: %lu\n", pthread_self());
    printf("Stack Frame Start: %p\n", __builtin_frame_address(0));
    printf("Stack Frame End: %p\n", __builtin_frame_address(1));
    return res;
}
int main() {
    pthread_t threads[5];
    // 创建线程
    for (int i = 0; i < 5; i++) {
        pthread_create(&threads[i], NULL, thread_func, NULL);
    }
    // 等待线程结束
    for (int i = 0; i < 5; i++) {
        
        pthread_join(threads[i], NULL);
        printf("Thread %d joined\n", i);
    }
    return 0;
}

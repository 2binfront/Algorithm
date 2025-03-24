#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define THREAD_THRESHOLD 1000 // 小于此阈值使用串行排序
#define PRINT_THRESHOLD 10000 // 小于此阈值打印数组

// 排序参数结构体
typedef struct {
    int* array;
    int left;
    int right;
} SortParams;

// 串行归并排序函数的声明
void merge_sort_serial(int* array, int left, int right);
void merge(int* array, int left, int mid, int right);

// 线程排序函数
void* thread_merge_sort(void* arg) {
    SortParams* params = (SortParams*)arg;
    int left = params->left;
    int right = params->right;
    int* array = params->array;
    
    // 如果数组长度小于阈值，使用串行排序
    if (right - left <= THREAD_THRESHOLD) {
        merge_sort_serial(array, left, right);
        pthread_exit(NULL);
    }
    
    int mid = left + (right - left) / 2;
    
    // 创建两个线程参数
    SortParams leftParams = {array, left, mid};
    SortParams rightParams = {array, mid + 1, right};
    
    pthread_t leftThread, rightThread;
    
    // 创建左半部分排序线程
    if (pthread_create(&leftThread, NULL, thread_merge_sort, &leftParams) != 0) {
        perror("左侧线程创建失败");
        exit(EXIT_FAILURE);
    }
    
    // 创建右半部分排序线程
    if (pthread_create(&rightThread, NULL, thread_merge_sort, &rightParams) != 0) {
        perror("右侧线程创建失败");
        exit(EXIT_FAILURE);
    }
    
    // 等待两个线程完成
    if (pthread_join(leftThread, NULL) != 0) {
        perror("左侧线程加入失败");
        exit(EXIT_FAILURE);
    }
    
    if (pthread_join(rightThread, NULL) != 0) {
        perror("右侧线程加入失败");
        exit(EXIT_FAILURE);
    }
    
    // 合并两个已排序的子数组
    merge(array, left, mid, right);
    
    pthread_exit(NULL);
}

// 串行归并排序
void merge_sort_serial(int* array, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        
        // 递归排序左半部分
        merge_sort_serial(array, left, mid);
        
        // 递归排序右半部分
        merge_sort_serial(array, mid + 1, right);
        
        // 合并两个已排序的子数组
        merge(array, left, mid, right);
    }
}

// 合并两个已排序的子数组
void merge(int* array, int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    // 创建临时数组
    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));
    
    // 复制数据到临时数组
    for (i = 0; i < n1; i++) {
        L[i] = array[left + i];
    }
    for (j = 0; j < n2; j++) {
        R[j] = array[mid + 1 + j];
    }
    
    // 合并临时数组回到原始数组
    i = 0;
    j = 0;
    k = left;
    
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            array[k] = L[i];
            i++;
        } else {
            array[k] = R[j];
            j++;
        }
        k++;
    }
    
    // 复制L[]的剩余元素（如果有）
    while (i < n1) {
        array[k] = L[i];
        i++;
        k++;
    }
    
    // 复制R[]的剩余元素（如果有）
    while (j < n2) {
        array[k] = R[j];
        j++;
        k++;
    }
    
    // 释放临时数组
    free(L);
    free(R);
}

// 打印数组
void print_array(int* array, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int main() {
    // 数组大小
    int size;
    printf("请输入数组大小: ");
    scanf("%d", &size);
    
    // 分配内存并随机填充数组
    int* array = (int*)malloc(size * sizeof(int));
    if (array == NULL) {
        perror("内存分配失败");
        return EXIT_FAILURE;
    }
    
    printf("正在生成随机数据...\n");
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        array[i] = rand() % 10000;
    }
    // 计时排序时间
    clock_t start_time, end_time;
    double cpu_time_used;

    start_time = clock();

    // 如果数组较小，输出排序前的数组
    if (size <= PRINT_THRESHOLD) {
        printf("排序前的数组: ");
        print_array(array, size);
    }
    
    // 设置排序参数
    SortParams params = {array, 0, size - 1};
    
    // 创建主排序线程
    pthread_t mainThread;
    if (pthread_create(&mainThread, NULL, thread_merge_sort, &params) != 0) {
        perror("主线程创建失败");
        free(array);
        return EXIT_FAILURE;
    }
    
    // 等待排序完成
    if (pthread_join(mainThread, NULL) != 0) {
        perror("主线程加入失败");
        free(array);
        return EXIT_FAILURE;
    }
    end_time = clock();
    
    // 如果数组较小，输出排序后的数组
    if (size <= PRINT_THRESHOLD) {
        printf("排序后的数组: ");
        print_array(array, size);
    }
    
    // 计算并输出排序时间
    cpu_time_used = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
    printf("排序时间: %f 秒\n", cpu_time_used);

    // 检查排序结果
    int isSorted = 1;
    for (int i = 1; i < size; i++) {
        if (array[i] < array[i - 1]) {
            isSorted = 0;
            break;
        }
    }
    
    if (isSorted) {
        printf("排序成功!\n");
    } else {
        printf("排序失败!\n");
    }
    
    // 释放内存
    free(array);
    
    return 0;
}

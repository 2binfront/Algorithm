#include <stdio.h>
#include "./os_src/thread.h"
#include <time.h>
#define NTHREADS 1000
static thread_t threads[NTHREADS];

// 编写一个使用线程执行并行矩阵乘法的程序。要将两个矩阵相乘，C=A*B，结果条目C（i，j）是通过取A的第i行和B的第j列的点积来计算的：Ci，j=∑k=0 N-1A（i，k）B（k，j）。我们可以通过创建一个线程来计算C中的每个值（或每行），然后在不同的处理器上并行执行这些线程来划分工作
// 定义矩阵大小
#define N 1000
// 定义两个矩阵
int A[N][N];
int B[N][N];
int C[N][N];
// 定义线程函数
void *matrix_multiply(void *arg) {

    int i = *((int *)arg);
    int j;
    for (j = 0; j < N; j++) {
        int sum = 0;
        int k;
        for (k = 0; k < N; k++) {
            sum += A[i][k] * B[k][j];
        }
        C[i][j] = sum;

    }
}
int main(int argc, char **argv) {
    
    int i;
    int j;
    // 初始化矩阵
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            A[i][j] = i + j;
            B[i][j] = i - j;
        }
    }
    // 创建线程
    for (i = 0; i < N; i++) {
        thread_create(&threads[i], &matrix_multiply, &i);
    }
    // 等待线程结束
    for (i = 0; i < N; i++) {
        thread_join(threads[i]);
    }
    // 输出结果
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }
    return 0;

}

#include <stdio.h>
#include "thread.h"
#include <time.h>
#define NTHREADS 1000

static thread_t threads[NTHREADS];


// 一个简单的循环，不断递增一个计数器，并在该计数器的值可被 10000000 整除时打印一个句点（“.”）

static void simple_loop(int n){
    int i=0;
    while(1){
        i++;
        if(i%10000000==0){
             // 输出句点并刷新缓冲区确保立即显示
            printf(".");
            fflush(stdout);
        }
    }
}

// 反复等待用户输入一行文本，然后打印“谢谢您的输入”

static void user_input(int n){
    char buf[100];
    while(1){
        printf("Please input something: ");
        fgets(buf, 100, stdin);
        printf("Thank you for your input.\n");
    }
}

int main(int argc, char **argv){

        // 创建两个线程，运行上述两个函数

        thread_create(&threads[0], &simple_loop,1);
	   thread_create(&threads[1], &user_input, 1);

       thread_join(threads[0]);
       thread_join(threads[1]);

		return 0;
}

#include <stdio.h>
#include "thread.h"
#include <time.h>
#define NTHREADS 1000

static thread_t threads[NTHREADS];


// 一个简单的循环，不断递增一个计数器，并在该计数器的值可被 10000000 整除时打印一个句点（“.”）
static void simple_loop(){
    int i=0;
    while(1){
        i++;
        if(i%10000000==0){
            printf(".");
        }
    }
}

// 反复等待用户输入一行文本，然后打印“谢谢您的输入”
static void user_input(){
    char buf[100];
    while(1){
        printf("Please input something: ");
        fgets(buf, 100, stdin);
        printf("Thank you for your input.\n");
    }
}

int main(int argc, char **argv){
		clock_t start,end;
		double total_time, create_time, join_time;
		long exitValue;

		int i;

		start = clock();

		clock_t create_start = clock();

        // 创建两个线程，运行上述两个函数
    	thread_create(&threads[0], &simple_loop,NULL);
	    thread_create(&threads[1], &user_input, NULL);

		clock_t create_end = clock();
		create_time = ((double) (create_end - create_start)) / CLOCKS_PER_SEC;

		clock_t join_start = clock();
		
		for (i=0; i<NTHREADS; i++){
				exitValue = thread_join(threads[i]);
		}

		printf("\n%ld\n",exitValue);

		clock_t join_end = clock();
		join_time = ((double) (join_end - join_start)) / CLOCKS_PER_SEC;

		end = clock();

		total_time = ((double) (end - start)) / CLOCKS_PER_SEC;


		printf("\ncreate %d threads cost: %.4f sec",NTHREADS, create_time);
		printf("\njoin %d threads cost: %.4f sec", NTHREADS, join_time);
		printf("\ntotal time: %.4f", total_time);
		printf("\nAverage create and join time: %.6f sec", total_time / NTHREADS);

		printf("\nMain thread done.\n");
		return 0;
}

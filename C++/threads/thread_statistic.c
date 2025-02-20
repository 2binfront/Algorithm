#include <stdio.h>
#include "thread.h"
#include <time.h>
#define NTHREADS 1000

static thread_t threads[NTHREADS];

static void thread_func(int n){
		thread_exit(0);
	//	return n;//never arrive here
}

int main(int argc, char **argv){
		clock_t start,end;
		double total_time, create_time, join_time;
		long exitValue;

		int i;

		start = clock();

		clock_t create_start = clock();

		for (i=0; i<NTHREADS; i++){
				thread_create(&threads[i], &thread_func, i);
		}

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

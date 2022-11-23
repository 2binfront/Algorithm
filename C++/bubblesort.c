#include "stdio.h"
#include "time.h"
#include "stdlib.h"

void bubble(int *a, int len); //排序
void swap(int *p1, int *p2);  //交换数值

int main()
{
    clock_t start, finish;
    double totaltime;
    start = clock();

    int a[] = {5, 45, 12, 36, 2, 7, 91, 8, 44, 77, 35, 65, 78, 12};
    int length = sizeof(a) / sizeof(int); //求数组长度

    printf("原序列为：");
    // index<=length-1
    for (int i = 0; i < length; i++)
    {
        printf("%3d", a[i]);
    }

    bubble(a, length);

    printf("\n冒泡排序后：");
    // index<=length-1
    for (int i = 0; i < length; i++)
    {
        printf("%3d", a[i]);
    }
    printf("\n");

    finish = clock();
    totaltime = (double)(finish - start) / CLOCKS_PER_SEC;
    printf("\n程序运行的时间为: %.5f 秒\n", totaltime);
    system("pause");
}

void swap(int *p1, int *p2) //注意交换数值函数，调用时传入参数是地址，实际就是交换两数值的地址
{
    int temp;
    temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

void bubble(int *a, int len) //数组名表示数组第一个元素的地址，所以用int *a
{
    int i, j;

    for (i = 0; i < len; i++)
    {
        // index<=length-1
        for (j = 0; j < len - i - 1; j++)
        {
            if (a[j] > a[j + 1])
                swap(&a[j], &a[j + 1]); //交换两数值的地址
        }
    }
}
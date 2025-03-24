#include "stdio.h"
#include "time.h"
#include "stdlib.h"

void bubble(int *a, int len); //����
void swap(int *p1, int *p2);  //������ֵ

int main()
{
    clock_t start, finish;
    double totaltime;
    start = clock();

    int a[] = {5, 45, 12, 36, 2, 7, 91, 8, 44, 77, 35, 65, 78, 12};
    int length = sizeof(a) / sizeof(int); //�����鳤��

    printf("ԭ����Ϊ��");
    // index<=length-1
    for (int i = 0; i < length; i++)
    {
        printf("%3d", a[i]);
    }

    bubble(a, length);

    printf("\nð�������");
    // index<=length-1
    for (int i = 0; i < length; i++)
    {
        printf("%3d", a[i]);
    }
    printf("\n");

    finish = clock();
    totaltime = (double)(finish - start) / CLOCKS_PER_SEC;
    printf("\n�������е�ʱ��Ϊ: %.5f ��\n", totaltime);
    system("pause");
}

void swap(int *p1, int *p2) //ע�⽻����ֵ����������ʱ��������ǵ�ַ��ʵ�ʾ��ǽ�������ֵ�ĵ�ַ
{
    int temp;
    temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

void bubble(int *a, int len) //��������ʾ�����һ��Ԫ�صĵ�ַ��������int *a
{
    int i, j;

    for (i = 0; i < len; i++)
    {
        // index<=length-1
        for (j = 0; j < len - i - 1; j++)
        {
            if (a[j] > a[j + 1])
                swap(&a[j], &a[j + 1]); //��������ֵ�ĵ�ַ
        }
    }
}
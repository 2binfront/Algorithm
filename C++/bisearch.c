#include <stdio.h>
#include <stdlib.h>

int binary_search(int arr[], int left, int right, int num)
{
    while (left <= right)
    {
        int mid = (left + right) / 2;
        if (num < arr[mid])
            right = mid - 1;
        else if (num > arr[mid])
            left = mid + 1;
        else
            return mid;
    }
    return -1;
}

int main()
{
    //不完全初始化，末尾自动加0
    int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int right = sizeof(arr) / sizeof(arr[0]);
    int left = 0;
    int num = 0;
    while (1)
    {
        // printf("%d", arr[9]);
        printf("please input the number you want to find:");
        scanf("%d", &num);
        int tmp = binary_search(arr, left, right, num);
        if (tmp != -1)
            printf("the location of number is:%d\n", tmp);
        else
            printf("not exist!\n");
    }

    // system("PAUSE ");
    return 0;
}
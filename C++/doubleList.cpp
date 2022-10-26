//构建双向链表数据结构

#include<stdio.h>

struct doubleList
{
    /* data */
    int val;
    struct doubleList *next;
    struct doubleList *pre;
};

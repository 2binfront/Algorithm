#include <stdio.h>

#define MAXN 100

int graph[MAXN][MAXN];
int match[MAXN];
int visited[MAXN];

int leftCount;
int rightCount;

/*
 * 尝试为左部顶点 u 寻找一个匹配。
 *
 * 返回 1：找到了增广路，匹配成功
 * 返回 0：没有找到增广路
 */
int FindAugmentingPath(int u)
{
    int v;

    for (v = 0; v < rightCount; v++) {
        if (graph[u][v] && !visited[v]) {
            visited[v] = 1;

            /*
             * 情况1：v 尚未匹配，直接匹配。
             *
             * 情况2：v 已经匹配。
             * 尝试让原来与 v 匹配的顶点 match[v]
             * 去寻找其他右部顶点。
             */
            if (match[v] == -1 ||
                FindAugmentingPath(match[v])) {
                match[v] = u;
                return 1;
            }
        }
    }

    return 0;
}

int MaximumMatching(void)
{
    int u;
    int v;
    int result = 0;

    for (v = 0; v < rightCount; v++) {
        match[v] = -1;
    }

    for (u = 0; u < leftCount; u++) {
        for (v = 0; v < rightCount; v++) {
            visited[v] = 0;
        }

        if (FindAugmentingPath(u)) {
            result++;
        }
    }

    return result;
}

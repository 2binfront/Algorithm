#include <stdio.h>

#define MaxVertexNum 100

typedef struct ArcNode {
    int adjvex;               // 该边指向的顶点编号
    struct ArcNode *nextarc;
} ArcNode;

typedef struct VNode {
    ArcNode *firstarc;
} VNode;

typedef struct {
    VNode vertices[MaxVertexNum];
    int vexnum;
} ALGraph;

int path[MaxVertexNum];        // 保存当前路径
int visited[MaxVertexNum];     // 顶点是否在当前路径中
int pathLen = 0;

/* 输出当前路径 */
void PrintPath(void)
{
    int i;

    for (i = 0; i < pathLen; i++) {
        printf("%d", path[i]);

        if (i < pathLen - 1) {
            printf(" -> ");
        }
    }

    printf("\n");
}

/* 输出从当前顶点 u 到目标顶点 vj 的所有简单路径 */
void DFSPath(ALGraph *G, int u, int vj)
{
    ArcNode *p;
    int v;

    /* 将 u 加入当前路径 */
    visited[u] = 1;
    path[pathLen++] = u;

    /* 已到达目标顶点，输出一条简单路径 */
    if (u == vj) {
        PrintPath();
    } else {
        /* 枚举 u 的所有邻接点 */
        p = G->vertices[u].firstarc;

        while (p != NULL) {
            v = p->adjvex;

            /*
             * v 不在当前路径中时才能进入，
             * 从而保证路径中没有重复顶点
             */
            if (visited[v] == 0) {
                DFSPath(G, v, vj);
            }

            p = p->nextarc;
        }
    }

    /*
     * 回溯：
     * 将 u 从当前路径中删除，
     * 使 u 可以出现在其他路径中
     */
    pathLen--;
    visited[u] = 0;
}

void FindAllPaths(ALGraph *G, int vi, int vj)
{
    int i;

    for (i = 0; i < G->vexnum; i++) {
        visited[i] = 0;
    }

    pathLen = 0;
    DFSPath(G, vi, vj);
}

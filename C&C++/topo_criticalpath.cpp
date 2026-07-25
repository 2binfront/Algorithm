#include <stdio.h>
#include <stdlib.h>

#define MAXV 100

/* 边结点 */
typedef struct ArcNode {
    int adjvex;                 /* 该边指向的顶点编号 */
    int weight;                 /* 活动持续时间 */
    struct ArcNode *nextarc;
} ArcNode;

/* 顶点结点 */
typedef struct {
    char data;
    ArcNode *firstarc;
} VNode;

/* 邻接表 */
typedef struct {
    VNode vertices[MAXV];
    int vexnum;
    int arcnum;
} ALGraph;


/* 初始化有向图 */
void InitGraph(ALGraph *G, int vexnum)
{
    int i;

    G->vexnum = vexnum;
    G->arcnum = 0;

    for (i = 0; i < vexnum; i++) {
        G->vertices[i].data = (char)('A' + i);
        G->vertices[i].firstarc = NULL;
    }
}


/*
 * 添加有向边：
 *
 * from -> to
 *
 * weight 表示活动持续时间。
 */
void AddEdge(ALGraph *G, int from, int to, int weight)
{
    ArcNode *p;
    ArcNode *q;

    p = (ArcNode *)malloc(sizeof(ArcNode));

    if (p == NULL) {
        printf("内存分配失败\n");
        exit(EXIT_FAILURE);
    }

    p->adjvex = to;
    p->weight = weight;
    p->nextarc = NULL;

    /*
     * 将边插入邻接链表尾部，
     * 这样遍历顺序与添加顺序一致。
     */
    if (G->vertices[from].firstarc == NULL) {
        G->vertices[from].firstarc = p;
    } else {
        q = G->vertices[from].firstarc;

        while (q->nextarc != NULL) {
            q = q->nextarc;
        }

        q->nextarc = p;
    }

    G->arcnum++;
}


/* 计算所有顶点的入度 */
void GetIndegree(ALGraph *G, int indegree[])
{
    int i;
    ArcNode *p;

    for (i = 0; i < G->vexnum; i++) {
        indegree[i] = 0;
    }

    for (i = 0; i < G->vexnum; i++) {
        p = G->vertices[i].firstarc;

        while (p != NULL) {
            indegree[p->adjvex]++;
            p = p->nextarc;
        }
    }
}


/*
 * 拓扑排序，并同时计算事件的最早发生时间 ve。
 *
 * topo[]：保存拓扑序列
 * ve[]：保存各事件的最早发生时间
 *
 * 返回值：
 * 1：拓扑排序成功，图中无环
 * 0：拓扑排序失败，图中有环
 */
int TopologicalOrder(ALGraph *G, int topo[], int ve[])
{
    int indegree[MAXV];
    int queue[MAXV];

    int front;
    int rear;
    int count;

    int i;
    int u;
    int v;

    ArcNode *p;

    GetIndegree(G, indegree);

    front = 0;
    rear = 0;
    count = 0;

    /* 所有事件的最早发生时间初始为 0 */
    for (i = 0; i < G->vexnum; i++) {
        ve[i] = 0;
    }

    /* 将所有入度为 0 的顶点入队 */
    for (i = 0; i < G->vexnum; i++) {
        if (indegree[i] == 0) {
            queue[rear++] = i;
        }
    }

    while (front < rear) {
        /* 取出一个当前入度为 0 的顶点 */
        u = queue[front++];

        /* 保存到拓扑序列 */
        topo[count++] = u;

        /*
         * 删除 u 的所有出边。
         * 实际上不修改图，只把对应顶点的入度减 1。
         */
        p = G->vertices[u].firstarc;

        while (p != NULL) {
            v = p->adjvex;

            /*
             * 更新事件 v 的最早发生时间：
             *
             * ve[v] = max(ve[v], ve[u] + weight)
             */
            if (ve[u] + p->weight > ve[v]) {
                ve[v] = ve[u] + p->weight;
            }

            indegree[v]--;

            if (indegree[v] == 0) {
                queue[rear++] = v;
            }

            p = p->nextarc;
        }
    }

    /*
     * 如果没有输出全部顶点，
     * 说明剩余顶点构成有向环。
     */
    if (count < G->vexnum) {
        return 0;
    }

    return 1;
}


/*
 * 从当前顶点开始，递归输出所有关键路径。
 */
void PrintCriticalPaths(ALGraph *G,
                        int u,
                        int sink,
                        int ve[],
                        int vl[],
                        int path[],
                        int length)
{
    int i;
    int v;
    int e;
    int l;

    ArcNode *p;

    path[length] = u;
    length++;

    /* 到达汇点，输出一条完整关键路径 */
    if (u == sink) {
        for (i = 0; i < length; i++) {
            printf("%c", G->vertices[path[i]].data);

            if (i < length - 1) {
                printf(" -> ");
            }
        }

        printf("\n");
        return;
    }

    p = G->vertices[u].firstarc;

    while (p != NULL) {
        v = p->adjvex;

        /* 活动 <u,v> 的最早开始时间 */
        e = ve[u];

        /* 活动 <u,v> 的最迟开始时间 */
        l = vl[v] - p->weight;

        /*
         * e == l 表示该活动的时间余量为 0，
         * 即它是关键活动。
         */
        if (e == l) {
            PrintCriticalPaths(
                G,
                v,
                sink,
                ve,
                vl,
                path,
                length
            );
        }

        p = p->nextarc;
    }
}


/*
 * 求 AOE 网的关键路径。
 *
 * 假设：
 * 1. 图是有向无环图；
 * 2. 图只有一个源点；
 * 3. 图只有一个汇点。
 */
int CriticalPath(ALGraph *G)
{
    int topo[MAXV];
    int ve[MAXV];
    int vl[MAXV];
    int indegree[MAXV];
    int path[MAXV];

    int source;
    int sink;
    int sourceCount;
    int sinkCount;

    int projectTime;

    int i;
    int u;
    int v;
    int e;
    int l;
    int slack;

    ArcNode *p;

    /*
     * 第一步：
     * 拓扑排序，并按拓扑序计算 ve。
     */
    if (!TopologicalOrder(G, topo, ve)) {
        printf("图中存在有向环，不能求关键路径。\n");
        return 0;
    }

    /*
     * 查找源点和汇点。
     */
    GetIndegree(G, indegree);

    source = -1;
    sink = -1;
    sourceCount = 0;
    sinkCount = 0;

    for (i = 0; i < G->vexnum; i++) {
        if (indegree[i] == 0) {
            source = i;
            sourceCount++;
        }

        if (G->vertices[i].firstarc == NULL) {
            sink = i;
            sinkCount++;
        }
    }

    if (sourceCount != 1 || sinkCount != 1) {
        printf("该图不是标准 AOE 网：需要唯一源点和唯一汇点。\n");
        printf("可以添加虚拟源点或虚拟汇点。\n");
        return 0;
    }

    /*
     * 汇点的最早发生时间就是工程最短完成时间。
     */
    projectTime = ve[sink];

    /*
     * 第二步：
     * 所有事件最迟发生时间初始化为工程完成时间。
     */
    for (i = 0; i < G->vexnum; i++) {
        vl[i] = projectTime;
    }

    /*
     * 第三步：
     * 按逆拓扑序计算 vl。
     *
     * vl[u] = min(vl[v] - weight(u,v))
     */
    for (i = G->vexnum - 1; i >= 0; i--) {
        u = topo[i];

        p = G->vertices[u].firstarc;

        while (p != NULL) {
            v = p->adjvex;

            if (vl[v] - p->weight < vl[u]) {
                vl[u] = vl[v] - p->weight;
            }

            p = p->nextarc;
        }
    }

    printf("\n工程最短完成时间：%d\n", projectTime);

    printf("\n事件时间：\n");
    printf("顶点\tve\tvl\t时间余量\n");

    for (i = 0; i < G->vexnum; i++) {
        printf("%c\t%d\t%d\t%d\n",
               G->vertices[i].data,
               ve[i],
               vl[i],
               vl[i] - ve[i]);
    }

    printf("\n各项活动：\n");
    printf("活动\t持续时间\te\tl\t时间余量\t是否关键\n");

    for (u = 0; u < G->vexnum; u++) {
        p = G->vertices[u].firstarc;

        while (p != NULL) {
            v = p->adjvex;

            /*
             * 活动 <u,v>：
             *
             * e = ve[u]
             * l = vl[v] - weight(u,v)
             */
            e = ve[u];
            l = vl[v] - p->weight;
            slack = l - e;

            printf("%c->%c\t%d\t\t%d\t%d\t%d\t\t",
                   G->vertices[u].data,
                   G->vertices[v].data,
                   p->weight,
                   e,
                   l,
                   slack);

            if (e == l) {
                printf("是\n");
            } else {
                printf("否\n");
            }

            p = p->nextarc;
        }
    }

    printf("\n关键路径：\n");

    PrintCriticalPaths(
        G,
        source,
        sink,
        ve,
        vl,
        path,
        0
    );

    return 1;
}


/* 释放邻接表结点 */
void DestroyGraph(ALGraph *G)
{
    int i;
    ArcNode *p;
    ArcNode *q;

    for (i = 0; i < G->vexnum; i++) {
        p = G->vertices[i].firstarc;

        while (p != NULL) {
            q = p;
            p = p->nextarc;
            free(q);
        }

        G->vertices[i].firstarc = NULL;
    }
}


int main(void)
{
    ALGraph G;

    int topo[MAXV];
    int ve[MAXV];
    int i;

    /*
     * 构造如下 AOE 网：
     *
     *          3
     *      A ------> B
     *      |         |
     *    4 |         | 5
     *      v         v
     *      C ------> D
     *          2
     *
     * 活动：
     * A -> B，持续 3
     * A -> C，持续 4
     * B -> D，持续 5
     * C -> D，持续 2
     */

    InitGraph(&G, 4);

    AddEdge(&G, 0, 1, 3);  /* A -> B */
    AddEdge(&G, 0, 2, 4);  /* A -> C */
    AddEdge(&G, 1, 3, 5);  /* B -> D */
    AddEdge(&G, 2, 3, 2);  /* C -> D */

    printf("拓扑序列：\n");

    if (TopologicalOrder(&G, topo, ve)) {
        for (i = 0; i < G.vexnum; i++) {
            printf("%c", G.vertices[topo[i]].data);

            if (i < G.vexnum - 1) {
                printf(" -> ");
            }
        }

        printf("\n");
    } else {
        printf("图中存在有向环，不存在拓扑序列。\n");
    }

    CriticalPath(&G);

    DestroyGraph(&G);

    return 0;
}

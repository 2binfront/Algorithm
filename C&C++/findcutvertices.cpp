#include <stdio.h>

#define MAX_V 1005
#define MAX_E 20005

/* ---------- 邻接表 ---------- */

/*
 * 无向边需要存储成两条有向边：
 *
 * u -> v
 * v -> u
 *
 * 因此 MAX_E 至少应为无向边数上限的两倍。
 */
int head[MAX_V];
int to[MAX_E];
int nextEdge[MAX_E];
int edgeCount;


/* ---------- DFS 相关数组 ---------- */

/*
 * dfn[u]：
 * 顶点 u 第一次被 DFS 访问的时间戳。
 *
 * dfn[u] == 0 表示尚未访问。
 */
int dfn[MAX_V];

/*
 * low[u]：
 * 从 u 的 DFS 子树出发，
 * 通过若干条 DFS 树边和至多一条返祖边，
 * 能够到达的最早顶点的 dfn。
 */
int low[MAX_V];

/* DFS 时间戳 */
int timeStamp;


/* ---------- 割点信息 ---------- */

/*
 * isCut[u] == 1：
 * 顶点 u 是割点。
 */
int isCut[MAX_V];

/* 割点个数 */
int cutCount;


/*
 * 初始化图。
 */
void InitGraph(int n)
{
    int i;

    edgeCount = 0;

    for (i = 1; i <= n; i++)
    {
        head[i] = -1;
        dfn[i] = 0;
        low[i] = 0;
        isCut[i] = 0;
    }

    timeStamp = 0;
    cutCount = 0;
}


/*
 * 添加一条有向边 u -> v。
 */
void AddDirectedEdge(int u, int v)
{
    to[edgeCount] = v;
    nextEdge[edgeCount] = head[u];
    head[u] = edgeCount;

    edgeCount++;
}


/*
 * 添加一条无向边 u - v。
 *
 * 连续加入的两条边互为反向边：
 *
 * 偶数编号边 e
 * 对应的反向边为 e ^ 1
 */
void AddUndirectedEdge(int u, int v)
{
    AddDirectedEdge(u, v);
    AddDirectedEdge(v, u);
}


/*
 * 从顶点 u 开始进行 DFS。
 *
 * parentEdge：
 * 父结点到 u 的那条边的编号。
 *
 * 使用边编号而不是父顶点编号，可以正确处理重边。
 */
void DFS(int u, int parentEdge)
{
    int edge;
    int v;
    int childCount;

    timeStamp++;
    dfn[u] = timeStamp;
    low[u] = timeStamp;

    /*
     * childCount 统计 u 在 DFS 树中的孩子数量。
     */
    childCount = 0;

    edge = head[u];

    while (edge != -1)
    {
        v = to[edge];

        /*
         * 忽略当前边的反向父边。
         *
         * 如果父边是 parentEdge，
         * 那么它的反向边编号是 parentEdge ^ 1。
         */
        if (parentEdge != -1 && edge == (parentEdge ^ 1))
        {
            edge = nextEdge[edge];
            continue;
        }

        /*
         * 情况一：
         * v 尚未访问。
         *
         * 此时 u - v 是 DFS 树边。
         */
        if (dfn[v] == 0)
        {
            childCount++;

            DFS(v, edge);

            /*
             * 子树搜索完成后，用 low[v] 更新 low[u]。
             */
            if (low[v] < low[u])
            {
                low[u] = low[v];
            }

            /*
             * 非根结点割点条件：
             *
             * 如果 v 的子树不能到达 u 的祖先，
             * 那么删除 u 后，v 的子树会断开。
             */
            if (parentEdge != -1 && low[v] >= dfn[u])
            {
                isCut[u] = 1;
            }
        }
        /*
         * 情况二：
         * v 已访问，并且当前边不是父边。
         *
         * 在无向 DFS 中，这条边是返祖边，
         * 用 dfn[v] 更新 low[u]。
         */
        else
        {
            if (dfn[v] < low[u])
            {
                low[u] = dfn[v];
            }
        }

        edge = nextEdge[edge];
    }

    /*
     * 根结点割点条件：
     *
     * 根结点至少有两个 DFS 孩子。
     */
    if (parentEdge == -1 && childCount >= 2)
    {
        isCut[u] = 1;
    }
}


/*
 * 求整个无向图中的所有割点。
 *
 * 即使图不是连通图，这段代码也能正确处理。
 */
void FindCutVertices(int n)
{
    int i;

    for (i = 1; i <= n; i++)
    {
        if (dfn[i] == 0)
        {
            DFS(i, -1);
        }
    }

    /*
     * 统计割点个数。
     */
    cutCount = 0;

    for (i = 1; i <= n; i++)
    {
        if (isCut[i])
        {
            cutCount++;
        }
    }
}


int main(void)
{
    int n;
    int m;
    int i;
    int u;
    int v;

    /*
     * 输入格式：
     *
     * 第一行：顶点数 n，边数 m
     * 接下来 m 行：每行一条无向边 u v
     *
     * 顶点编号为 1 到 n。
     */
    scanf("%d%d", &n, &m);

    InitGraph(n);

    for (i = 0; i < m; i++)
    {
        scanf("%d%d", &u, &v);
        AddUndirectedEdge(u, v);
    }

    FindCutVertices(n);

    printf("割点个数：%d\n", cutCount);
    printf("所有割点：");

    for (i = 1; i <= n; i++)
    {
        if (isCut[i])
        {
            printf("%d ", i);
        }
    }

    printf("\n");

    return 0;
}

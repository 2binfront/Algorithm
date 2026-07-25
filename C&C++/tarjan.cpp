#include <stdio.h>

#define MAX_V 1005
#define MAX_E 10005

/* ---------- 邻接表 ---------- */

/* head[u]：顶点 u 的第一条出边编号 */
int head[MAX_V];

/* to[i]：第 i 条边的终点 */
int to[MAX_E];

/* nextEdge[i]：与第 i 条边同起点的下一条边 */
int nextEdge[MAX_E];

/* 当前已经存储的边数 */
int edgeCount;


/* ---------- Tarjan 算法相关数组 ---------- */

/*
 * dfn[u]：
 * 顶点 u 第一次被 DFS 访问时的时间戳。
 * dfn[u] == 0 表示 u 尚未访问。
 */
int dfn[MAX_V];

/*
 * low[u]：
 * 从 u 出发，通过 DFS 树边以及至多一条返祖边，
 * 能到达的最早访问顶点的 dfn 值。
 */
int low[MAX_V];

/* DFS 时间戳 */
int timeStamp;


/* ---------- Tarjan 使用的栈 ---------- */

int stack[MAX_V];
int top;

/*
 * inStack[u] == 1：
 * 顶点 u 当前仍在 Tarjan 栈中。
 */
int inStack[MAX_V];


/* ---------- 强连通分量信息 ---------- */

/* 强连通分量个数 */
int sccCount;

/*
 * sccId[u]：
 * 顶点 u 所属的强连通分量编号。
 */
int sccId[MAX_V];

/*
 * sccSize[i]：
 * 第 i 个强连通分量包含的顶点数。
 */
int sccSize[MAX_V];


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
    }
}


/*
 * 添加一条有向边 u -> v。
 */
void AddEdge(int u, int v)
{
    to[edgeCount] = v;
    nextEdge[edgeCount] = head[u];
    head[u] = edgeCount;

    edgeCount++;
}


/*
 * 从顶点 u 开始执行 Tarjan DFS。
 */
void Tarjan(int u)
{
    int edge;
    int v;
    int x;

    /*
     * 第一次访问 u：
     * dfn[u] 和 low[u] 都初始化为当前时间戳。
     */
    timeStamp++;
    dfn[u] = timeStamp;
    low[u] = timeStamp;

    /*
     * 将 u 压入 Tarjan 栈。
     */
    stack[top] = u;
    top++;

    inStack[u] = 1;

    /*
     * 遍历 u 的所有出边 u -> v。
     */
    edge = head[u];

    while (edge != -1)
    {
        v = to[edge];

        /*
         * 情况一：
         * v 尚未被访问。
         *
         * 此时边 u -> v 是 DFS 树边，
         * 先递归访问 v。
         */
        if (dfn[v] == 0)
        {
            Tarjan(v);

            /*
             * v 的子树搜索完成后，
             * 用 low[v] 更新 low[u]。
             */
            if (low[v] < low[u])
            {
                low[u] = low[v];
            }
        }
        /*
         * 情况二：
         * v 已经被访问，并且仍然在 Tarjan 栈中。
         *
         * 这说明 u 可以回到当前 DFS 搜索路径中的某个顶点。
         */
        else if (inStack[v])
        {
            /*
             * 这里使用 dfn[v] 更新 low[u]，
             * 不能写成 low[v]。
             */
            if (dfn[v] < low[u])
            {
                low[u] = dfn[v];
            }
        }

        edge = nextEdge[edge];
    }

    /*
     * 如果 low[u] == dfn[u]，
     * 则 u 是一个强连通分量在 DFS 树中的根。
     *
     * 从栈顶不断弹出顶点，直到弹出 u。
     */
    if (low[u] == dfn[u])
    {
        sccCount++;

        do
        {
            top--;
            x = stack[top];

            inStack[x] = 0;

            sccId[x] = sccCount;
            sccSize[sccCount]++;

        } while (x != u);
    }
}


/*
 * 对整个有向图执行 Tarjan 算法。
 *
 * 有向图可能不是连通的，因此需要检查每个顶点。
 */
void FindSCC(int n)
{
    int i;

    timeStamp = 0;
    top = 0;
    sccCount = 0;

    for (i = 1; i <= n; i++)
    {
        dfn[i] = 0;
        low[i] = 0;
        inStack[i] = 0;
        sccId[i] = 0;
        sccSize[i] = 0;
    }

    for (i = 1; i <= n; i++)
    {
        if (dfn[i] == 0)
        {
            Tarjan(i);
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
    int id;

    /*
     * 输入：
     * 第一行：顶点数 n 和边数 m
     * 接下来 m 行：每行一条有向边 u -> v
     *
     * 顶点编号为 1 到 n。
     */
    scanf("%d%d", &n, &m);

    InitGraph(n);

    for (i = 0; i < m; i++)
    {
        scanf("%d%d", &u, &v);
        AddEdge(u, v);
    }

    FindSCC(n);

    printf("强连通分量个数：%d\n", sccCount);

    /*
     * 输出每个强连通分量中的顶点。
     */
    for (id = 1; id <= sccCount; id++)
    {
        printf("强连通分量 %d：", id);

        for (i = 1; i <= n; i++)
        {
            if (sccId[i] == id)
            {
                printf("%d ", i);
            }
        }

        printf("\n");
    }

    return 0;
}

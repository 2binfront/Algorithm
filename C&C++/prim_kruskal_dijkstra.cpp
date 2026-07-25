#include <iostream>
#include <algorithm>
using namespace std;

#define MAXV 100
#define MAXE 10000
#define INF 0x3f3f3f3f

typedef struct {
    int vertexNum;
    int edgeNum;
    int edge[MAXV][MAXV];
} MGraph;

typedef struct {
    int u;
    int v;
    int weight;
} Edge;

/*================ Prim ================*/

bool Prim(const MGraph &G, int start)
{
    int lowcost[MAXV];
    int parent[MAXV];
    bool inMST[MAXV];

    int i, j;
    int totalWeight = 0;

    for (i = 0; i < G.vertexNum; i++) {
        lowcost[i] = INF;
        parent[i] = -1;
        inMST[i] = false;
    }

    lowcost[start] = 0;

    for (i = 0; i < G.vertexNum; i++) {
        int u = -1;
        int minWeight = INF;

        for (j = 0; j < G.vertexNum; j++) {
            if (!inMST[j] && lowcost[j] < minWeight) {
                minWeight = lowcost[j];
                u = j;
            }
        }

        if (u == -1) {
            cout << "图不连通，不存在最小生成树" << endl;
            return false;
        }

        inMST[u] = true;
        totalWeight += lowcost[u];

        if (parent[u] != -1) {
            cout << parent[u] << " - "
                 << u << "，权值："
                 << G.edge[parent[u]][u] << endl;
        }

        for (j = 0; j < G.vertexNum; j++) {
            if (!inMST[j] &&
                G.edge[u][j] < lowcost[j]) {

                lowcost[j] = G.edge[u][j];
                parent[j] = u;
            }
        }
    }

    cout << "总权值：" << totalWeight << endl;

    return true;
}

/*================ Kruskal ================*/

int parentSet[MAXV];
int rankSet[MAXV];

void InitSet(int vertexNum)
{
    int i;

    for (i = 0; i < vertexNum; i++) {
        parentSet[i] = i;
        rankSet[i] = 0;
    }
}

int FindSet(int x)
{
    if (parentSet[x] != x) {
        parentSet[x] = FindSet(parentSet[x]);
    }

    return parentSet[x];
}

void UnionSet(int x, int y)
{
    int rootX = FindSet(x);
    int rootY = FindSet(y);

    if (rootX == rootY) {
        return;
    }

    if (rankSet[rootX] < rankSet[rootY]) {
        parentSet[rootX] = rootY;
    } else if (rankSet[rootX] > rankSet[rootY]) {
        parentSet[rootY] = rootX;
    } else {
        parentSet[rootY] = rootX;
        rankSet[rootX]++;
    }
}

bool CompareEdge(const Edge &a, const Edge &b)
{
    return a.weight < b.weight;
}

bool Kruskal(Edge edges[], int vertexNum, int edgeNum)
{
    int i;
    int selectedEdgeNum = 0;
    int totalWeight = 0;

    sort(edges, edges + edgeNum, CompareEdge);

    InitSet(vertexNum);

    for (i = 0; i < edgeNum; i++) {
        if (FindSet(edges[i].u) != FindSet(edges[i].v)) {
            cout << edges[i].u << " - "
                 << edges[i].v << "，权值："
                 << edges[i].weight << endl;

            UnionSet(edges[i].u, edges[i].v);

            totalWeight += edges[i].weight;
            selectedEdgeNum++;

            if (selectedEdgeNum == vertexNum - 1) {
                break;
            }
        }
    }

    if (selectedEdgeNum != vertexNum - 1) {
        cout << "图不连通，不存在最小生成树" << endl;
        return false;
    }

    cout << "总权值：" << totalWeight << endl;

    return true;
}

/*================ Dijkstra ================*/

void Dijkstra(const MGraph &G,
              int start,
              int dist[],
              int previous[])
{
    bool visited[MAXV];
    int i, j;

    for (i = 0; i < G.vertexNum; i++) {
        dist[i] = INF;
        previous[i] = -1;
        visited[i] = false;
    }

    dist[start] = 0;

    for (i = 0; i < G.vertexNum; i++) {
        int u = -1;
        int minDistance = INF;

        for (j = 0; j < G.vertexNum; j++) {
            if (!visited[j] && dist[j] < minDistance) {
                minDistance = dist[j];
                u = j;
            }
        }

        if (u == -1) {
            break;
        }

        visited[u] = true;

        for (j = 0; j < G.vertexNum; j++) {
            if (!visited[j] &&
                G.edge[u][j] < INF &&
                dist[u] + G.edge[u][j] < dist[j]) {

                dist[j] = dist[u] + G.edge[u][j];
                previous[j] = u;
            }
        }
    }
}

void PrintPath(int previous[], int start, int v)
{
    if (v == start) {
        cout << start;
        return;
    }

    if (previous[v] == -1) {
        cout << "不可达";
        return;
    }

    PrintPath(previous, start, previous[v]);

    cout << " -> " << v;
}

int main()
{
    MGraph G;
    Edge edges[MAXE];

    int i, j;
    int u, v, weight;

    cout << "输入顶点数和边数：" << endl;
    cin >> G.vertexNum >> G.edgeNum;

    /*
     * 初始化邻接矩阵
     */
    for (i = 0; i < G.vertexNum; i++) {
        for (j = 0; j < G.vertexNum; j++) {
            if (i == j) {
                G.edge[i][j] = 0;
            } else {
                G.edge[i][j] = INF;
            }
        }
    }

    cout << "依次输入每条边：起点 终点 权值" << endl;

    for (i = 0; i < G.edgeNum; i++) {
        cin >> u >> v >> weight;

        edges[i].u = u;
        edges[i].v = v;
        edges[i].weight = weight;

        /*
         * 无向图，对称存储
         * 若存在平行边，保留权值较小的边
         */
        if (weight < G.edge[u][v]) {
            G.edge[u][v] = weight;
            G.edge[v][u] = weight;
        }
    }

    cout << endl;
    cout << "Prim最小生成树：" << endl;
    Prim(G, 0);

    cout << endl;
    cout << "Kruskal最小生成树：" << endl;
    Kruskal(edges, G.vertexNum, G.edgeNum);

    int start;
    int dist[MAXV];
    int previous[MAXV];

    cout << endl;
    cout << "输入Dijkstra起点：" << endl;
    cin >> start;

    Dijkstra(G, start, dist, previous);

    cout << endl;
    cout << "Dijkstra最短路径：" << endl;

    for (i = 0; i < G.vertexNum; i++) {
        cout << start << " 到 " << i << "：";

        if (dist[i] == INF) {
            cout << "不可达" << endl;
        } else {
            PrintPath(previous, start, i);
            cout << "，距离：" << dist[i] << endl;
        }
    }

    return 0;
}

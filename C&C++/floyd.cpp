#include <iostream>
using namespace std;

#define MAXV 100
#define INF 0x3f3f3f3f

typedef struct {
    int vertexNum;
    int edgeNum;
    int edge[MAXV][MAXV];
} MGraph;

void Floyd(const MGraph &G,
           int dist[][MAXV],
           int nextVertex[][MAXV])
{
    int i, j, k;

    /*
     * 初始化
     */
    for (i = 0; i < G.vertexNum; i++) {
        for (j = 0; j < G.vertexNum; j++) {
            dist[i][j] = G.edge[i][j];

            if (i == j) {
                nextVertex[i][j] = i;
            } else if (G.edge[i][j] < INF) {
                /*
                 * i到j有直接边，
                 * 离开i后的下一个顶点就是j
                 */
                nextVertex[i][j] = j;
            } else {
                /*
                 * 当前不可达
                 */
                nextVertex[i][j] = -1;
            }
        }
    }

    /*
     * Floyd核心过程
     */
    for (k = 0; k < G.vertexNum; k++) {
        for (i = 0; i < G.vertexNum; i++) {
            for (j = 0; j < G.vertexNum; j++) {
                if (dist[i][k] < INF &&
                    dist[k][j] < INF &&
                    dist[i][k] + dist[k][j] < dist[i][j]) {

                    dist[i][j] =
                        dist[i][k] + dist[k][j];

                    /*
                     * i到j现在先走向i到k路径中的下一个顶点
                     */
                    nextVertex[i][j] =
                        nextVertex[i][k];
                }
            }
        }
    }
}

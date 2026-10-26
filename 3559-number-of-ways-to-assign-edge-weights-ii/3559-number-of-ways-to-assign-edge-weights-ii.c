
#include <stdlib.h>

#define MOD 1000000007
#define MAXN 100005
#define LOG 17

static int head[MAXN];
static int to[2 * MAXN];
static int nxt[2 * MAXN];
static int up[LOG][MAXN];
static int depth[MAXN];
static int parent[MAXN];
static int order[MAXN];
static int edgeCount;
static long long pow2[MAXN];

static void addEdge(int u, int v) {
    to[edgeCount] = v;
    nxt[edgeCount] = head[u];
    head[u] = edgeCount++;
}

static int lca(int u, int v) {
    if (depth[u] < depth[v]) {
        int temp = u;
        u = v;
        v = temp;
    }

    int diff = depth[u] - depth[v];

    for (int j = 0; j < LOG; j++) {
        if (diff & (1 << j))
            u = up[j][u];
    }

    if (u == v)
        return u;

    for (int j = LOG - 1; j >= 0; j--) {
        if (up[j][u] != up[j][v]) {
            u = up[j][u];
            v = up[j][v];
        }
    }

    return parent[u];
}

int* assignEdgeWeights(
    int** edges,
    int edgesSize,
    int* edgesColSize,
    int** queries,
    int queriesSize,
    int* queriesColSize,
    int* returnSize
) {
    (void)edgesColSize;
    (void)queriesColSize;

    int n = edgesSize + 1;

    for (int i = 0; i <= n; i++) {
        head[i] = -1;
        depth[i] = 0;
        parent[i] = 0;
    }

    edgeCount = 0;

    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];

        addEdge(u, v);
        addEdge(v, u);
    }

    // Iterative traversal avoids stack overflow on a chain.
    int count = 0;
    order[count++] = 1;
    parent[1] = 0;

    for (int i = 0; i < count; i++) {
        int u = order[i];

        for (int e = head[u]; e != -1; e = nxt[e]) {
            int v = to[e];

            if (v == parent[u] || v == 1)
                continue;

            parent[v] = u;
            depth[v] = depth[u] + 1;
            up[0][v] = u;
            order[count++] = v;
        }
    }

    up[0][1] = 0;

    // Build the binary lifting table.
    for (int j = 1; j < LOG; j++) {
        for (int i = 1; i <= n; i++) {
            up[j][i] = up[j - 1][up[j - 1][i]];
        }
    }

    // Precompute powers of two.
    pow2[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        pow2[i] = (pow2[i - 1] * 2) % MOD;
    }

    int* answer = malloc(queriesSize * sizeof(int));
    *returnSize = queriesSize;

    for (int i = 0; i < queriesSize; i++) {
        int u = queries[i][0];
        int v = queries[i][1];

        int ancestor = lca(u, v);
        int dist = depth[u] + depth[v] - 2 * depth[ancestor];

        answer[i] = (dist == 0) ? 0 : (int)pow2[dist - 1];
    }

    return answer;
}

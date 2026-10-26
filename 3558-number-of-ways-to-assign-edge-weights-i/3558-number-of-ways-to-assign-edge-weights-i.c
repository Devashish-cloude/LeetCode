
#include <stdlib.h>

#define MOD 1000000007

int assignEdgeWeights(int** edges, int edgesSize, int* edgesColSize) {
    (void)edgesColSize;

    int n = edgesSize + 1;
    int *head = (int*)malloc(n * sizeof(int));
    int *to = (int*)malloc(2 * edgesSize * sizeof(int));
    int *next = (int*)malloc(2 * edgesSize * sizeof(int));
    int *depth = (int*)malloc(n * sizeof(int));
    int *queue = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
        head[i] = -1;

    int idx = 0;

    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0] - 1;
        int v = edges[i][1] - 1;

        to[idx] = v;
        next[idx] = head[u];
        head[u] = idx++;

        to[idx] = u;
        next[idx] = head[v];
        head[v] = idx++;
    }

    for (int i = 0; i < n; i++)
        depth[i] = -1;

    int front = 0, back = 0;
    queue[back++] = 0;
    depth[0] = 0;

    int maxDepth = 0;

    while (front < back) {
        int u = queue[front++];

        for (int e = head[u]; e != -1; e = next[e]) {
            int v = to[e];

            if (depth[v] == -1) {
                depth[v] = depth[u] + 1;

                if (depth[v] > maxDepth)
                    maxDepth = depth[v];

                queue[back++] = v;
            }
        }
    }

    free(head);
    free(to);
    free(next);
    free(depth);
    free(queue);

    if (maxDepth == 0)
        return 0;

    long long ans = 1;
    for (int i = 1; i < maxDepth; i++)
        ans = (ans * 2) % MOD;

    return (int)ans;
}

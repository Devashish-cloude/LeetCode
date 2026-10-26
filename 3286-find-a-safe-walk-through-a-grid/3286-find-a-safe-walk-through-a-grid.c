
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

bool findSafeWalk(int** grid, int gridSize, int* gridColSize, int health) {
    int m = gridSize;
    int n = gridColSize[0];
    int total = m * n;

    int *dist = malloc(total * sizeof(int));
    int *deque = malloc(2 * total * sizeof(int));

    for (int i = 0; i < total; i++) {
        dist[i] = INT_MAX;
    }

    int front = total;
    int back = total;

    dist[0] = grid[0][0];
    deque[--front] = 0;

    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};

    while (front < back) {
        int u = deque[front++];
        int r = u / n;
        int c = u % n;

        for (int k = 0; k < 4; k++) {
            int nr = r + dr[k];
            int nc = c + dc[k];

            if (nr < 0 || nr >= m || nc < 0 || nc >= n)
                continue;

            int v = nr * n + nc;
            int cost = grid[nr][nc];

            if (dist[u] + cost < dist[v]) {
                dist[v] = dist[u] + cost;

                if (cost == 0) {
                    deque[--front] = v;
                } else {
                    deque[back++] = v;
                }
            }
        }
    }

    bool result = dist[total - 1] < health;

    free(dist);
    free(deque);

    return result;
}

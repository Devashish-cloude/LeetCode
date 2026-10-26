
#include <stdlib.h>
#include <stdbool.h>

int maximumSafenessFactor(int** grid, int gridSize, int* gridColSize) {
    int n = gridSize;
    int total = n * n;

    int *dist = malloc(total * sizeof(int));
    int *queue = malloc(total * sizeof(int));
    int *visited = malloc(total * sizeof(int));

    int head = 0, tail = 0;

    // Multi-source BFS from all thieves
    for (int i = 0; i < total; i++) {
        dist[i] = -1;
        if (grid[i / n][i % n] == 1) {
            dist[i] = 0;
            queue[tail++] = i;
        }
    }

    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};

    while (head < tail) {
        int u = queue[head++];
        int r = u / n, c = u % n;

        for (int k = 0; k < 4; k++) {
            int nr = r + dr[k], nc = c + dc[k];

            if (nr >= 0 && nr < n && nc >= 0 && nc < n) {
                int v = nr * n + nc;

                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    queue[tail++] = v;
                }
            }
        }
    }

    // Binary search for the maximum possible safeness
    int low = 0, high = 2 * n, answer = 0;

    while (low <= high) {
        int limit = low + (high - low) / 2;

        for (int i = 0; i < total; i++)
            visited[i] = 0;

        head = 0;
        tail = 0;

        if (dist[0] >= limit) {
            queue[tail++] = 0;
            visited[0] = 1;
        }

        bool found = false;

        while (head < tail) {
            int u = queue[head++];

            if (u == total - 1) {
                found = true;
                break;
            }

            int r = u / n, c = u % n;

            for (int k = 0; k < 4; k++) {
                int nr = r + dr[k], nc = c + dc[k];

                if (nr >= 0 && nr < n && nc >= 0 && nc < n) {
                    int v = nr * n + nc;

                    if (!visited[v] && dist[v] >= limit) {
                        visited[v] = 1;
                        queue[tail++] = v;
                    }
                }
            }
        }

        if (found) {
            answer = limit;
            low = limit + 1;
        } else {
            high = limit - 1;
        }
    }

    free(dist);
    free(queue);
    free(visited);

    return answer;
}

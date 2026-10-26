
#include <stdlib.h>
#include <stdbool.h>

int countIslands(int** grid, int gridSize, int* gridColSize, int k) {
    int m = gridSize;
    int n = gridColSize[0];

    int totalCells = m * n;
    int* stack = (int*)malloc(totalCells * sizeof(int));
    bool* visited = (bool*)calloc(totalCells, sizeof(bool));

    int count = 0;

    int dr[] = {1, -1, 0, 0};
    int dc[] = {0, 0, 1, -1};

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {

            int start = i * n + j;

            if (grid[i][j] > 0 && !visited[start]) {
                int top = 0;
                long long sum = 0;

                stack[top++] = start;
                visited[start] = true;

                while (top > 0) {
                    int cell = stack[--top];
                    int r = cell / n;
                    int c = cell % n;

                    sum += grid[r][c];

                    for (int d = 0; d < 4; d++) {
                        int nr = r + dr[d];
                        int nc = c + dc[d];

                        if (nr >= 0 && nr < m &&
                            nc >= 0 && nc < n &&
                            grid[nr][nc] > 0) {

                            int next = nr * n + nc;

                            if (!visited[next]) {
                                visited[next] = true;
                                stack[top++] = next;
                            }
                        }
                    }
                }

                if (sum % k == 0) {
                    count++;
                }
            }
        }
    }

    free(stack);
    free(visited);

    return count;
}

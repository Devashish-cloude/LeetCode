
#include <stdlib.h>

typedef struct {
    int id;
    int height;
} Restriction;

int compare(const void* a, const void* b) {
    Restriction* x = (Restriction*)a;
    Restriction* y = (Restriction*)b;
    return (x->id > y->id) - (x->id < y->id);
}

int maxBuilding(int n, int** restrictions, int restrictionsSize,
                int* restrictionsColSize) {
    int m = restrictionsSize + 1;
    Restriction* r = malloc((m + 1) * sizeof(Restriction));

    r[0].id = 1;
    r[0].height = 0;

    for (int i = 0; i < restrictionsSize; i++) {
        r[i + 1].id = restrictions[i][0];
        r[i + 1].height = restrictions[i][1];
    }

    qsort(r, m, sizeof(Restriction), compare);

    // Add the last building if it is not already restricted.
    if (r[m - 1].id != n) {
        r[m].id = n;
        r[m].height = n - 1;
        m++;
    }

    // Forward pass: enforce adjacent height limits.
    for (int i = 1; i < m; i++) {
        int distance = r[i].id - r[i - 1].id;
        int allowed = r[i - 1].height + distance;

        if (r[i].height > allowed) {
            r[i].height = allowed;
        }
    }

    // Backward pass: enforce limits from the right.
    for (int i = m - 2; i >= 0; i--) {
        int distance = r[i + 1].id - r[i].id;
        int allowed = r[i + 1].height + distance;

        if (r[i].height > allowed) {
            r[i].height = allowed;
        }
    }

    int answer = 0;

    // Find the maximum possible peak between restrictions.
    for (int i = 1; i < m; i++) {
        int distance = r[i].id - r[i - 1].id;
        int leftHeight = r[i - 1].height;
        int rightHeight = r[i].height;

        int peak = (leftHeight + rightHeight + distance) / 2;

        if (peak > answer) {
            answer = peak;
        }
    }

    free(r);
    return answer;
}

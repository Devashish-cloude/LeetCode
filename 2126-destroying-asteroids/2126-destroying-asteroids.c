
#include <stdlib.h>
#include <stdbool.h>

int cmp(const void *a, const void *b) {
    int x = *(const int *)a;
    int y = *(const int *)b;
    return (x > y) - (x < y);
}

bool asteroidsDestroyed(int mass, int* asteroids, int asteroidsSize) {
    qsort(asteroids, asteroidsSize, sizeof(int), cmp);

    long long currentMass = mass;

    for (int i = 0; i < asteroidsSize; i++) {
        if (currentMass < asteroids[i]) {
            return false;
        }

        currentMass += asteroids[i];
    }

    return true;
}



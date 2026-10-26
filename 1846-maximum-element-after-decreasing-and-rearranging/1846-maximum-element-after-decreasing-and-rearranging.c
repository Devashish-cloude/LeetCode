
#include <stdlib.h>

int compare(const void* a, const void* b) {
    int x = *(const int*)a;
    int y = *(const int*)b;
    return (x > y) - (x < y);
}

int maximumElementAfterDecrementingAndRearranging(int* arr, int arrSize) {
    qsort(arr, arrSize, sizeof(int), compare);

    arr[0] = 1;

    for (int i = 1; i < arrSize; i++) {
        if (arr[i] > arr[i - 1] + 1) {
            arr[i] = arr[i - 1] + 1;
        }
    }

    return arr[arrSize - 1];
}

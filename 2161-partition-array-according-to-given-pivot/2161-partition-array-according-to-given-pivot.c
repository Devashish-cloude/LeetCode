
#include <stdlib.h>

int* pivotArray(int* nums, int numsSize, int pivot, int* returnSize) {
    int* result = (int*)malloc(numsSize * sizeof(int));
    int index = 0;

    // First: elements smaller than pivot
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] < pivot) {
            result[index++] = nums[i];
        }
    }

    // Second: elements equal to pivot
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] == pivot) {
            result[index++] = nums[i];
        }
    }

    // Third: elements greater than pivot
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] > pivot) {
            result[index++] = nums[i];
        }
    }

    *returnSize = numsSize;
    return result;
}

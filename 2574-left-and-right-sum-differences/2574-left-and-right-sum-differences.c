
#include <stdlib.h>

int* leftRightDifference(int* nums, int numsSize, int* returnSize) {
    int* answer = (int*)malloc(numsSize * sizeof(int));

    int totalSum = 0;
    int leftSum = 0;

    // Calculate the sum of all elements
    for (int i = 0; i < numsSize; i++) {
        totalSum += nums[i];
    }

    for (int i = 0; i < numsSize; i++) {
        int rightSum = totalSum - leftSum - nums[i];

        answer[i] = abs(leftSum - rightSum);

        leftSum += nums[i];
    }

    *returnSize = numsSize;
    return answer;
}

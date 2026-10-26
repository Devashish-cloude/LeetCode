
long long countMajoritySubarrays(int* nums, int numsSize, int target) {
    long long count = 0;

    for (int i = 0; i < numsSize; i++) {
        int targetCount = 0;

        for (int j = i; j < numsSize; j++) {
            if (nums[j] == target) {
                targetCount++;
            }

            int length = j - i + 1;

            if (targetCount * 2 > length) {
                count++;
            }
        }
    }

    return count;
}

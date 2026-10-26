
long long countMajoritySubarrays(int* nums, int numsSize, int target) {
    int n = numsSize;
    int offset = n + 1;
    int size = 2 * n + 3;

    long long *bit = (long long *)calloc(size, sizeof(long long));
    if (bit == NULL) return 0;

    long long ans = 0;
    int prefix = 0;

    // Empty prefix has sum 0.
    for (int i = 0; i < n; i++) {
        prefix += (nums[i] == target) ? 1 : -1;

        // Count previous prefix sums strictly less than current prefix.
        int idx = prefix - 1 + offset;
        while (idx > 0) {
            ans += bit[idx];
            idx -= idx & -idx;
        }

        // Insert current prefix sum.
        idx = prefix + offset;
        while (idx < size) {
            bit[idx]++;
            idx += idx & -idx;
        }
    }

    // Include the empty prefix before the first element.
    // Recompute with the empty prefix correctly included.
    free(bit);

    bit = (long long *)calloc(size, sizeof(long long));
    if (bit == NULL) return 0;

    ans = 0;
    prefix = 0;

    int idx = offset;
    while (idx < size) {
        bit[idx]++;
        idx += idx & -idx;
    }

    for (int i = 0; i < n; i++) {
        prefix += (nums[i] == target) ? 1 : -1;

        idx = prefix - 1 + offset;
        while (idx > 0) {
            ans += bit[idx];
            idx -= idx & -idx;
        }

        idx = prefix + offset;
        while (idx < size) {
            bit[idx]++;
            idx += idx & -idx;
        }
    }

    free(bit);
    return ans;
}

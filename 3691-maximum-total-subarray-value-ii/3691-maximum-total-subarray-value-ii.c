
#include <stdlib.h>

#define MAXN 50005
#define LOG 17

typedef long long ll;

static int stMax[LOG][MAXN];
static int stMin[LOG][MAXN];
static int lg[MAXN];

typedef struct {
    ll value;
    int l, r;
} Item;

static Item heap[MAXN + 5];
static int heapSize;

static void push(Item x) {
    int i = ++heapSize;

    while (i > 1 && heap[i / 2].value < x.value) {
        heap[i] = heap[i / 2];
        i /= 2;
    }

    heap[i] = x;
}

static Item pop(void) {
    Item ans = heap[1];
    Item last = heap[heapSize--];

    int i = 1;

    while (i * 2 <= heapSize) {
        int child = i * 2;

        if (child + 1 <= heapSize &&
            heap[child + 1].value > heap[child].value) {
            child++;
        }

        if (heap[child].value <= last.value)
            break;

        heap[i] = heap[child];
        i = child;
    }

    heap[i] = last;
    return ans;
}

static int rangeValue(int l, int r) {
    int j = lg[r - l + 1];
    int len = 1 << j;

    int mx = stMax[j][l];
    int otherMax = stMax[j][r - len + 1];

    if (otherMax > mx)
        mx = otherMax;

    int mn = stMin[j][l];
    int otherMin = stMin[j][r - len + 1];

    if (otherMin < mn)
        mn = otherMin;

    return mx - mn;
}

long long maxTotalValue(int* nums, int numsSize, int k) {
    int n = numsSize;

    lg[1] = 0;
    for (int i = 2; i <= n; i++)
        lg[i] = lg[i / 2] + 1;

    for (int i = 0; i < n; i++) {
        stMax[0][i] = nums[i];
        stMin[0][i] = nums[i];
    }

    for (int j = 1; j < LOG; j++) {
        int len = 1 << j;
        int half = len >> 1;

        for (int i = 0; i + len <= n; i++) {
            int a = stMax[j - 1][i];
            int b = stMax[j - 1][i + half];
            stMax[j][i] = a > b ? a : b;

            a = stMin[j - 1][i];
            b = stMin[j - 1][i + half];
            stMin[j][i] = a < b ? a : b;
        }
    }

    heapSize = 0;

    // Initialize with the longest subarray for each left endpoint.
    for (int l = 0; l < n; l++) {
        Item x;
        x.l = l;
        x.r = n - 1;
        x.value = rangeValue(l, n - 1);
        push(x);
    }

    ll answer = 0;

    // Extract the k largest distinct subarray values.
    for (int i = 0; i < k; i++) {
        Item cur = pop();
        answer += cur.value;

        // For the same left endpoint, shorter subarrays
        // have values no greater than the current value.
        if (cur.r > cur.l) {
            Item next;
            next.l = cur.l;
            next.r = cur.r - 1;
            next.value = rangeValue(next.l, next.r);
            push(next);
        }
    }

    return answer;
}

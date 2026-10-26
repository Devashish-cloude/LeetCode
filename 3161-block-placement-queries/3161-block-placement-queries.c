
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 150005

static int coords[MAXN];
static int bit[MAXN];
static int seg[4 * MAXN];
static int N;

static int cmpInt(const void *a, const void *b) {
    int x = *(const int *)a;
    int y = *(const int *)b;
    return (x > y) - (x < y);
}

static void bitAdd(int i, int val) {
    for (i++; i <= N; i += i & -i)
        bit[i] += val;
}

static int bitSum(int i) {
    int sum = 0;
    for (i++; i > 0; i -= i & -i)
        sum += bit[i];
    return sum;
}

// Return the zero-based index of the kth active position.
static int findKth(int k) {
    int idx = 0;
    int step = 1;

    while (step * 2 <= N)
        step *= 2;

    for (; step; step >>= 1) {
        int next = idx + step;
        if (next <= N && bit[next] < k) {
            idx = next;
            k -= bit[next];
        }
    }

    return idx;
}

static void segUpdate(int node, int l, int r,
                      int idx, int val) {
    if (l == r) {
        seg[node] = val;
        return;
    }

    int mid = l + (r - l) / 2;

    if (idx <= mid)
        segUpdate(node * 2, l, mid, idx, val);
    else
        segUpdate(node * 2 + 1, mid + 1, r, idx, val);

    int a = seg[node * 2];
    int b = seg[node * 2 + 1];
    seg[node] = a > b ? a : b;
}

static int segQuery(int node, int l, int r,
                    int ql, int qr) {
    if (ql > r || qr < l || ql > qr)
        return 0;

    if (ql <= l && r <= qr)
        return seg[node];

    int mid = l + (r - l) / 2;
    int a = segQuery(node * 2, l, mid, ql, qr);
    int b = segQuery(node * 2 + 1, mid + 1, r, ql, qr);

    return a > b ? a : b;
}

static int lowerBound(int x) {
    int l = 0, r = N;

    while (l < r) {
        int mid = l + (r - l) / 2;
        if (coords[mid] < x)
            l = mid + 1;
        else
            r = mid;
    }

    return l;
}

static int upperBound(int x) {
    int l = 0, r = N;

    while (l < r) {
        int mid = l + (r - l) / 2;
        if (coords[mid] <= x)
            l = mid + 1;
        else
            r = mid;
    }

    return l;
}

bool* getResults(int** queries, int queriesSize,
                 int* queriesColSize, int* returnSize) {
    (void)queriesColSize;

    // Coordinate compression: include every query position.
    for (int i = 0; i < queriesSize; i++)
        coords[i] = queries[i][1];

    coords[queriesSize] = 0;
    qsort(coords, queriesSize + 1, sizeof(int), cmpInt);

    N = 0;
    for (int i = 0; i <= queriesSize; i++) {
        if (N == 0 || coords[i] != coords[N - 1])
            coords[N++] = coords[i];
    }

    for (int i = 0; i <= N; i++)
        bit[i] = 0;
    for (int i = 0; i < 4 * N; i++)
        seg[i] = 0;

    // Position 0 is the initial boundary.
    int zeroIdx = lowerBound(0);
    bitAdd(zeroIdx, 1);

    bool *active = calloc(N, sizeof(bool));
    active[zeroIdx] = true;

    bool *ans = malloc(queriesSize * sizeof(bool));
    int ansCount = 0;

    for (int qi = 0; qi < queriesSize; qi++) {
        int type = queries[qi][0];
        int x = queries[qi][1];

        if (type == 1) {
            int idx = lowerBound(x);

            // Find previous active obstacle.
            int before = bitSum(idx - 1);
            int prevIdx = findKth(before);

            // Find next active obstacle, if one exists.
            int total = bitSum(N - 1);
            int nextIdx = -1;

            if (before < total)
                nextIdx = findKth(before + 1);

            // Insert the new obstacle.
            active[idx] = true;
            bitAdd(idx, 1);

            // Gap ending at the new obstacle.
            segUpdate(1, 0, N - 1, idx,
                      coords[idx] - coords[prevIdx]);

            // Update the gap ending at the next obstacle.
            if (nextIdx != -1) {
                segUpdate(1, 0, N - 1, nextIdx,
                          coords[nextIdx] - coords[idx]);
            }

        } else {
            int sz = queries[qi][2];

            // Last compressed coordinate <= x.
            int last = upperBound(x) - 1;

            // Number of active obstacles at positions <= x.
            int cnt = bitSum(last);

            int prevIdx = findKth(cnt);
            int prevPos = coords[prevIdx];

            // Largest complete gap ending at an obstacle <= x.
            int best = 0;
            if (last >= 1)
                best = segQuery(1, 0, N - 1, 1, last);

            // Space between the last obstacle and x.
            int tail = x - prevPos;
            if (tail > best)
                best = tail;

            ans[ansCount++] = (best >= sz);
        }
    }

    free(active);
    *returnSize = ansCount;
    return ans;
}

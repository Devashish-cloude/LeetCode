
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int start;
    int duration;
} Ride;

int cmpRide(const void *a, const void *b) {
    const Ride *x = (const Ride *)a;
    const Ride *y = (const Ride *)b;

    return (x->start > y->start) - (x->start < y->start);
}

long long solve(int *startA, int *durationA, int n,
                int *startB, int *durationB, int m) {
    Ride *rides = malloc(m * sizeof(Ride));
    int *prefixMin = malloc(m * sizeof(int));
    int *suffixMin = malloc(m * sizeof(int));

    for (int i = 0; i < m; i++) {
        rides[i].start = startB[i];
        rides[i].duration = durationB[i];
    }

    qsort(rides, m, sizeof(Ride), cmpRide);

    // Minimum duration among rides opening up to each index.
    prefixMin[0] = rides[0].duration;
    for (int i = 1; i < m; i++) {
        prefixMin[i] = prefixMin[i - 1] < rides[i].duration
                     ? prefixMin[i - 1] : rides[i].duration;
    }

    // Minimum (start + duration) among rides from each index onward.
    suffixMin[m - 1] = rides[m - 1].start + rides[m - 1].duration;
    for (int i = m - 2; i >= 0; i--) {
        int value = rides[i].start + rides[i].duration;
        suffixMin[i] = suffixMin[i + 1] < value
                     ? suffixMin[i + 1] : value;
    }

    long long answer = LLONG_MAX;

    for (int i = 0; i < n; i++) {
        int finish = startA[i] + durationA[i];

        // First index with ride start > finish.
        int left = 0, right = m;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (rides[mid].start <= finish)
                left = mid + 1;
            else
                right = mid;
        }

        int split = left;

        // Second ride is already open: finish + minimum duration.
        if (split > 0) {
            long long candidate =
                (long long)finish + prefixMin[split - 1];

            if (candidate < answer)
                answer = candidate;
        }

        // Second ride opens after the first ride finishes.
        if (split < m) {
            long long candidate = suffixMin[split];

            if (candidate < answer)
                answer = candidate;
        }
    }

    free(rides);
    free(prefixMin);
    free(suffixMin);

    return answer;
}

int earliestFinishTime(int* landStartTime, int landStartTimeSize,
                       int* landDuration, int landDurationSize,
                       int* waterStartTime, int waterStartTimeSize,
                       int* waterDuration, int waterDurationSize) {
    (void)landDurationSize;
    (void)waterDurationSize;

    long long landFirst = solve(
        landStartTime, landDuration, landStartTimeSize,
        waterStartTime, waterDuration, waterStartTimeSize
    );

    long long waterFirst = solve(
        waterStartTime, waterDuration, waterStartTimeSize,
        landStartTime, landDuration, landStartTimeSize
    );

    return (int)(landFirst < waterFirst ? landFirst : waterFirst);
}

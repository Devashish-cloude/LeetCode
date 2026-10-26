
#include <stdio.h>
#include <string.h>

typedef long long ll;

char digits[20];
int len;

typedef struct {
    ll count;
    ll waviness;
} State;

State memo[20][11][11][2];
int visited[20][11][11][2];

State dfs(int pos, int prev2, int prev1, int tight) {
    if (pos == len) {
        State base = {1, 0};
        return base;
    }

    if (!tight && visited[pos][prev2][prev1][0])
        return memo[pos][prev2][prev1][0];

    int limit = tight ? digits[pos] - '0' : 9;
    State ans = {0, 0};

    for (int d = 0; d <= limit; d++) {
        int ntight = tight && (d == digits[pos] - '0');
        State cur;

        if (prev1 == 10 && d == 0) {
            cur = dfs(pos + 1, 10, 10, ntight);
        } else if (prev1 == 10) {
            cur = dfs(pos + 1, 10, d, ntight);
        } else if (prev2 == 10) {
            cur = dfs(pos + 1, prev1, d, ntight);
        } else {
            cur = dfs(pos + 1, prev1, d, ntight);
            if ((prev1 > prev2 && prev1 > d) ||
                (prev1 < prev2 && prev1 < d)) {
                cur.waviness += cur.count;
            }
        }

        ans.count += cur.count;
        ans.waviness += cur.waviness;
    }

    if (!tight) {
        visited[pos][prev2][prev1][0] = 1;
        memo[pos][prev2][prev1][0] = ans;
    }

    return ans;
}

ll countWaviness(ll x) {
    if (x < 0)
        return 0;

    sprintf(digits, "%lld", x);
    len = (int)strlen(digits);
    memset(visited, 0, sizeof(visited));

    return dfs(0, 10, 10, 1).waviness;
}

long long totalWaviness(long long num1, long long num2) {
    return countWaviness(num2) - countWaviness(num1 - 1);
}

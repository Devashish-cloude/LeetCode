
#include <stdlib.h>
#include <string.h>

char processStr(char* s, long long k) {
    int n = strlen(s);
    long long *len = malloc((n + 1) * sizeof(long long));
    const long long LIMIT = 1000000000000000LL;

    len[0] = 0;

    for (int i = 0; i < n; i++) {
        long long x = len[i];

        if (s[i] >= 'a' && s[i] <= 'z')
            len[i + 1] = x < LIMIT ? x + 1 : LIMIT;
        else if (s[i] == '*')
            len[i + 1] = x > 0 ? x - 1 : 0;
        else if (s[i] == '#')
            len[i + 1] = x > LIMIT / 2 ? LIMIT : x * 2;
        else
            len[i + 1] = x;
    }

    if (k >= len[n]) {
        free(len);
        return '.';
    }

    for (int i = n - 1; i >= 0; i--) {
        char c = s[i];
        long long prev = len[i];
        long long curr = len[i + 1];

        if (c == '%') {
            k = curr - 1 - k;
        } else if (c == '#') {
            if (prev > 0)
                k %= prev;
        } else if (c == '*') {
            // Deletion removed the last character.
        } else {
            if (k == curr - 1) {
                free(len);
                return c;
            }
            // This letter was appended at the end.
            // Earlier characters retain their indices.
        }
    }

    free(len);
    return '.';
}

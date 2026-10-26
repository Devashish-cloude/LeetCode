
long long numberOfSubstrings(char* s) {
    int lastA = -1, lastB = -1, lastC = -1;
    long long count = 0;

    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == 'a') {
            lastA = i;
        } else if (s[i] == 'b') {
            lastB = i;
        } else {
            lastC = i;
        }

        int minLast = lastA;
        if (lastB < minLast) minLast = lastB;
        if (lastC < minLast) minLast = lastC;

        if (minLast != -1) {
            count += minLast + 1;
        }
    }

    return count;
}


long long totalWaviness(int num1, int num2) {
    long long total = 0;

    for (int num = num1; num <= num2; num++) {
        int digits[10];
        int len = 0;
        int x = num;

        while (x > 0) {
            digits[len++] = x % 10;
            x /= 10;
        }

        // Check each middle digit
        for (int i = 1; i < len - 1; i++) {
            int left = digits[i + 1];
            int mid = digits[i];
            int right = digits[i - 1];

            if ((mid > left && mid > right) ||
                (mid < left && mid < right)) {
                total++;
            }
        }
    }

    return total;
}

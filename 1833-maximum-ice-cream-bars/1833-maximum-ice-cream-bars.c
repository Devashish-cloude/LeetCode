
int maxIceCream(int* costs, int costsSize, int coins) {
    int freq[100001] = {0};

    // Count the frequency of each cost
    for (int i = 0; i < costsSize; i++) {
        freq[costs[i]]++;
    }

    int count = 0;

    // Buy the cheapest ice cream bars first
    for (int cost = 1; cost <= 100000; cost++) {
        while (freq[cost] > 0) {
            if (coins < cost) {
                return count;
            }

            coins -= cost;
            count++;
            freq[cost]--;
        }
    }

    return count;
}

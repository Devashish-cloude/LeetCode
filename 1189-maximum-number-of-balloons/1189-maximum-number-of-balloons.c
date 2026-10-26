
#include <string.h>

int maxNumberOfBalloons(char* text) {
    int freq[26] = {0};

    for (int i = 0; text[i] != '\0'; i++) {
        freq[text[i] - 'a']++;
    }

    int b = freq['b' - 'a'];
    int a = freq['a' - 'a'];
    int l = freq['l' - 'a'] / 2;
    int o = freq['o' - 'a'] / 2;
    int n = freq['n' - 'a'];

    int result = b;

    if (a < result) result = a;
    if (l < result) result = l;
    if (o < result) result = o;
    if (n < result) result = n;

    return result;
}

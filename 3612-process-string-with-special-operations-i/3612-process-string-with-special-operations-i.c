
#include <stdlib.h>
#include <string.h>

char* processStr(char* s) {
    int n = strlen(s);
    int capacity = (1 << n) + 1;

    char* result = malloc(capacity * sizeof(char));
    int len = 0;

    for (int i = 0; i < n; i++) {
        if (s[i] >= 'a' && s[i] <= 'z') {
            result[len++] = s[i];
        }
        else if (s[i] == '*') {
            if (len > 0) {
                len--;
            }
        }
        else if (s[i] == '#') {
            int oldLen = len;

            if (oldLen > 0) {
                memcpy(result + len, result, oldLen);
                len += oldLen;
            }
        }
        else if (s[i] == '%') {
            for (int j = 0; j < len / 2; j++) {
                char temp = result[j];
                result[j] = result[len - 1 - j];
                result[len - 1 - j] = temp;
            }
        }
    }

    result[len] = '\0';
    return result;
}

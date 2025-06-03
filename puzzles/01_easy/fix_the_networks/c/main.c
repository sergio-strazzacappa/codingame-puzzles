#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

void solve(char cidr[]);
char *to_binary(char *address);

int main() {
    int m;

    scanf("%d", &m);
    fgetc(stdin);

    for (int i = 0; i < m; i++) {
        char cidr[21];

        scanf("%[^\n]", cidr);
        fgetc(stdin);

        solve(cidr);
    }

    return 0;
}

void solve(char cidr[]) {
    fprintf(stderr, "[DEBUG] Solving: %s\n", cidr);

    // xxxx.xxxx.xxxx.xxxx/yy
    // 1. split the prefix and the suffix
    // 2. convert the prefix to binary
    // 3. test if the last yy bits are 0
    // 4. if true print valid
    // 5. else print invalid and fix the suffix

    char *prefix;
    int suffix;

    prefix = strtok(cidr, "/");
    suffix = atoi(strtok(NULL, "\n"));

    char *binary = to_binary(prefix);

    fprintf(stderr, "[DEBUG] Binary: %s\n", binary);

    // check if it is valid
    int range = 32 - suffix;
    int new_suffix = 0;
    bool valid = true;

    for (int i = strlen(binary) - 1; i >= 0; i--) {
        if (31 - range >= i)
            break;
        if (binary[i] != '0') {
            new_suffix = i + 1; 
            valid = false;
            break;
        }
    }

    if (valid) {
        printf("valid %.f\n", pow(2, range));
    } else {
        // fix it
        printf("invalid %s/%d %.f\n", prefix, new_suffix, pow(2, 32 - new_suffix));
    }
}

char *to_binary(char *address) {
    static char binary[33];
    char s[33];
    int index = 0;
    strcpy(s, address);
    char *token = strtok(s, ".");

    while (token != NULL) {
        int n = atoi(token);
        int i = 7;

        while (n > 0) {
            binary[index + i] = n % 2 + '0';
            n /= 2;
            i--;
        }

        while (i >= 0) {
            binary[index + i] = 0 + '0';
            i--;
        }
        token = strtok(NULL, ".");
        index += 8;
    }
    binary[index] = '\0';

    return binary;
}

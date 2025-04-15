#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char a[1001];
char b[1001];

void solve();

int main() {
    scanf("%[^\n]", a);
    fgetc(stdin);
    scanf("%[^\n]", b);
    fgetc(stdin);

    solve();
    
    return 0;
}

void solve() {
    long dot_product = 0;

    char *context_a = NULL;
    char *token_a = strtok_r(a, " ", &context_a);
    long times_a = atoi(token_a);
    token_a = strtok_r(NULL, " ", &context_a);
    long value_a = atoi(token_a);
    int next_a = 0;

    char *context_b = NULL;
    char *token_b = strtok_r(b, " ", &context_b);
    long times_b = atoi(token_b);
    token_b = strtok_r(NULL, " ", &context_b);
    long value_b = atoi(token_b);
    int next_b = 0;

    while (1) {
        if (next_a) {
            token_a = strtok_r(NULL, " ", &context_a);

            if (token_a == NULL)
                break;

            times_a = atoi(token_a);
            token_a = strtok_r(NULL, " ", &context_a);
            value_a = atoi(token_a);
            next_a = 0;
            continue;
        }

        if (next_b) {
            token_b = strtok_r(NULL, " ", &context_b);

            if (token_b == NULL)
                break;

            times_b = atoi(token_b);
            token_b = strtok_r(NULL, " ", &context_b);
            value_b = atoi(token_b);
            next_b = 0;
            continue;
        }

        if (times_a < times_b) {
            dot_product += times_a * value_a * value_b;
            times_b -= times_a;
            next_a = 1;
        } else if (times_a > times_b) {
            dot_product += times_b * value_a * value_b;
            times_a -= times_b;
            next_b = 1;
        } else {
            dot_product += times_a * value_a * value_b;
            next_a = 1;
            next_b = 1;
        }
    }

    printf("%ld\n", dot_product);
}

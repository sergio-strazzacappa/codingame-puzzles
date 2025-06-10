#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct type {
    int count;
    int value;
} Type;

int value_to_reach;
int n;
Type *coins;

void init();
void solve();
int cmp(const void *a, const void *b);
void clean();
void debug();

int main() {
    init();
    solve();
    clean();

    return 0;
}

void init() {
    scanf("%d%d", &value_to_reach, &n);

    coins = (Type *)malloc(sizeof(Type) * n);

    for (int i = 0; i < n; i++) {
        int count;
        scanf("%d", &count);
        coins[i].count = count;
    }
    for (int i = 0; i < n; i++) {
        int value;
        scanf("%d", &value);
        coins[i].value = value;
    }
}

void solve() {
    qsort(coins, n, sizeof(coins[0]), cmp);

    int current_value = 0;
    int coin = 0;
    int index = 0;
    while (current_value < value_to_reach) {
        Type c = coins[index];
        int current_coins = ceil(((float)value_to_reach - current_value) / c.value);

        if (current_coins <= c.count) {
            current_value += current_coins * c.value;
            coin += current_coins;
        } else {
            current_value += c.count * c.value;
            coin += c.count;
        }
        index++;

        if (index > n) {
            printf("-1\n");
            return;
        }
    }
    printf("%d\n", coin);
}

int cmp(const void *a, const void *b) {
    Type p = *(Type *)a;
    Type q = *(Type *)b;

    return p.value - q.value;
}

void clean() {
    free(coins);
}

void debug() {
    for (int i = 0; i < n; i++) {
        Type c = coins[i];
        fprintf(stderr, "[DEBUG] (%d, %d)\n", c.count, c.value);
    }
}

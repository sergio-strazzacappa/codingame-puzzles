#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int n;
int *ps;

void solve();
int cmp(const void *a, const void *b);
void debug();


int main() {
    scanf("%d", &n);

    ps = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        int p;
        scanf("%d", &p);
        ps[i] = p;
    }

    debug();
    solve();
    free(ps);

    return 0;
}

void solve() {
    qsort(ps, n, sizeof(int), cmp);

    int min = INT_MAX;

    for (int i = 0; i < n - 1; i++) {
        int diff = ps[i + 1] - ps[i];

        if (diff < min)
            min = diff;
    }

    printf("%d\n", min);
}

int cmp(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

void debug() {
    fprintf(stderr, "[");
    for (int i = 0; i < n; i++) {
        fprintf(stderr, "%d", ps[i]);
        if (i != n - 1)
            fprintf(stderr, ", ");
    }
    fprintf(stderr, "]\n");
}

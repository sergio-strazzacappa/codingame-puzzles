#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int *ps;

int comparator(const void *n1, const void *n2) {
    return (*(int *)n1 - *(int *)n2);
}

void debug(const int *ps, int n) {
    fprintf(stderr, "[");
    for (int i = 0; i < n; i++) {
        fprintf(stderr, "%d", ps[i]);
        if (i != n - 1) fprintf(stderr, ", ");
    }
    fprintf(stderr, "]\n");
}

int main() {
    int n, min, dif;
    scanf("%d", &n);

    ps = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        int p;
        scanf("%d", &p);
        ps[i] = p;
    }

    qsort(ps, n, sizeof(int), comparator);
    
    min = INT_MAX;

    for (int i = 0; i < n - 1; i++) {
        dif = ps[i + 1] - ps[i];

        if (dif < min) min = dif;
    }

    printf("%d\n", min);

    free(ps);
    return 0;
}

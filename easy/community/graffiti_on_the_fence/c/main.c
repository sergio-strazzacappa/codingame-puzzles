#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Report {
    int start;
    int end;
} Report;

int l; // length of the fence
int n; // number of reports
Report *reports;

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
    scanf("%d%d", &l, &n);

    reports = (Report *)malloc(sizeof(Report) * n);

    for (int i = 0; i < n; i++) {
        Report r;

        scanf("%d%d", &r.start, &r.end);

        reports[i] = r;
    }
}

void solve() {
    qsort(reports, n, sizeof(reports[0]), cmp);

    int current = 0;
    int index = 0;
    bool all_painted = true;

    while (index < n) {
        if (current < reports[index].start) {
            printf("%d %d\n", current, reports[index].start);
            all_painted = false;
        }

        if (current < reports[index].end)
            current = reports[index].end;

        index++;
    }

    if (current < l) {
        all_painted = false;
        printf("%d %d\n", current, l);
    }

    if (all_painted)
        printf("All painted\n");
}

int cmp(const void *a, const void *b) {
    return ((Report *)a)->start - ((Report *)b)->start;
}

void clean() {
    free(reports);
}

void debug() {
    fprintf(stderr, "[DEBUG] REPORTS:\n");

    for (int i = 0; i < n; i++)
        fprintf(stderr, "[DEBUG] [%d - %d]\n", reports[i].start, reports[i].end);
}

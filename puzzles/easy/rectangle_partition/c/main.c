#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 100000

int rows;
int cols;
int count_x;
int count_y;

int *x; // list of measurements on the x-axis
int *y; // list of measurements on the y-axis

void init();
void solve();
int cmp(const void *a, const void *b);
void print_measurements(int *list, int count, char *title);
void clean();

int main() {
    init();
    solve();
    clean();

    return 0;
}

void init() {
    scanf("%d%d%d%d", &cols, &rows, &count_x, &count_y);

    x = (int *)malloc(sizeof(int) * count_x);
    y = (int *)malloc(sizeof(int) * count_y);

    for (int i = 0; i < count_x; i++)
        scanf("%d", &x[i]);
    for (int i = 0; i < count_y; i++)
        scanf("%d", &y[i]);
}

void solve() {
    int start, end;

    int x_sizes[MAX_LEN];
    int x_index = 0;

    // get all partitions in the x-axis
    for (int i = 0; i < count_x + 1; i++) {
        if (i == 0)
            start = 0;
        else
            start = x[i - 1];

        for (int j = i; j < count_x + 1; j++) {
            if (j == count_x)
                end = cols;
            else
                end = x[j];

            x_sizes[x_index++] = end - start;
        }
    }

    int y_sizes[MAX_LEN];
    int y_index = 0;

    // get all partitions in the y-axis
    for (int i = 0; i < count_y + 1; i++) {
        if (i == 0)
            start = 0;
        else
            start = y[i - 1];

        for (int j = i; j < count_y + 1; j++) {
            if (j == count_y)
                end = rows;
            else
                end = y[j];

            y_sizes[y_index++] = end - start;
        }
    }

    // sort the arrays to improve performance
    qsort(x_sizes, x_index, sizeof(int), cmp);
    qsort(y_sizes, y_index, sizeof(int), cmp);

    int squares = 0;

    // check squares
    for (int i = 0; i < x_index; i++) {
        for (int j = 0; j < y_index; j++) {
            if (y_sizes[j] > x_sizes[i])
                break;
            if (x_sizes[i] == y_sizes[j])
                squares++;
        }
    }

    printf("%d\n", squares);
}

int cmp(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

void clean() {
    free(x);
    free(y);
}

void print_measurements(int *list, int count, char *title) {
    fprintf(stderr, "[DEBUG] %s = [", title);

    for (int i = 0; i < count; i++)
        fprintf(stderr, " %d", list[i]);

    fprintf(stderr, " ]\n");
}

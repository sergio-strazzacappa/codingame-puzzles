#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct element {
    int row;
    int column;
    float value;
};

int m;
int n;
int p;
int count_a;
int count_b;
struct element *a;
struct element *b;

void solve();
float calculate(int row, int col);
bool find(int array[], int index, int element);
void format_output(char *str);
void debug();

int main() {
    scanf("%d%d%d%d%d", &m, &n, &p, &count_a, &count_b);

    a = (struct element *)malloc(sizeof(struct element) * count_a);
    b = (struct element *)malloc(sizeof(struct element) * count_b);

    for (int i = 0; i < count_a; i++) {
        int row;
        int column;
        float value;
        scanf("%d%d%f", &row, &column, &value);

        a[i].row = row;
        a[i].column = column;
        a[i].value = value;
    }

    for (int i = 0; i < count_b; i++) {
        int row;
        int column;
        float value;
        scanf("%d%d%f", &row, &column, &value);

        b[i].row = row;
        b[i].column = column;
        b[i].value = value;
    }

    solve();

    free(a);
    free(b);

    return 0;
}

void solve() {
    int rows[100];
    int rows_index = 0;

    for (int i = 0; i < count_a; i++) {
        if (find(rows, rows_index, a[i].row))
            continue;

        rows[rows_index++] = a[i].row;

        int cols[100];
        int cols_index = 0;

        for (int j = 0; j < count_b; j++) {
            if (find(cols, cols_index, b[j].column))
                continue;

            cols[cols_index++] = b[j].column;

            float r = calculate(a[i].row, b[j].column);

            if (r == 0)
                continue;

            char result[100];
            sprintf(result, "%1.20f", r);
            format_output(result);
            printf("%d %d %s\n", a[i].row, b[j].column, result);
        }
    }
}

float calculate(int row, int col) {
    fprintf(stderr, "[DEBUG] Calculate for (%d, %d)\n", row, col);

    float result = 0;
    for (int i = 0; i < count_a; i++) {
        if (a[i].row != row)
            continue;
        for (int j = 0; j < count_b; j++) {
            if (b[j].column != col)
                continue;
            if (b[j].row != a[i].column)
                continue;
            result += a[i].value * b[j].value;
            break;
        }
    }

    fprintf(stderr, "[DEBUG] Result: %f\n", result);

    return result;
}

bool find(int array[], int index, int element) {
    for (int i = 0; i < index; i++) {
        if (array[i] == element)
            return true;
    }
    return false;
}

void format_output(char *str) {
    int i = strlen(str) - 1;

    while (i > 0) {
        if (str[i] == '0') {
            str[i--] = '\0';
            continue;
        }
        if (str[i] == '.') {
            str[++i] = '0';
            str[++i] = '\0';
            break;
        }
        if (str[i] != '0' && str[i] != '.')
            break;
    }
}

void debug() {
    fprintf(stderr, "MATRIX A:\n");
    for (int i = 0; i < count_a; i++) {
        fprintf(stderr, "(%d, %d, %f)\n", a[i].row, a[i].column, a[i].value);
    }

    fprintf(stderr, "MATRIX B:\n");
    for (int i = 0; i < count_b; i++) {
        fprintf(stderr, "(%d, %d, %f)\n", b[i].row, b[i].column, b[i].value);
    }
}

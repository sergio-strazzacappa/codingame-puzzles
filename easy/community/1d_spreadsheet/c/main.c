#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>

typedef struct Cell{
    char operation[6];
    char arg_1[20];
    char arg_2[20];
    int index;
} Cell;

int n;
char operation[6];
char arg_1[7];
char arg_2[7];
Cell *left;
int left_index;
long *result;

void init();
void solve();
void clean();

int main() {
    init();
    solve();
}

void init() {
    scanf("%d", &n);

    left_index = 0;
    left = (Cell *)malloc(sizeof(Cell) * n);

    for (int i = 0; i < n; i++) {
        scanf("%s%s%s", operation, arg_1, arg_2);

        Cell c;
        strcpy(c.operation, operation);
        strcpy(c.arg_1, arg_1);
        strcpy(c.arg_2, arg_2);
        c.index = i;

        left[left_index++] = c;
    }

    result = (long *)malloc(sizeof(long) * n);

    for (int i = 0; i < n; i++)
        result[i] = LONG_MAX;
}

void solve() {
    while (left_index > 0) {
        for (int i = 0; i < left_index; i++) {
            Cell c = left[i];

            if (c.arg_1[0] == '$') {
                // remove the $ character
                for (int j = 0; j < strlen(c.arg_1) - 1; j++)
                    c.arg_1[j] = c.arg_1[j + 1];
                c.arg_1[strlen(c.arg_1) - 1] = '\0';

                sprintf(c.arg_1, "%ld", result[atol(c.arg_1)]);

                if (atol(c.arg_1) == LONG_MAX)
                    continue;
            }

            if (c.arg_2[0] == '$') {
                // remove the $ character
                for (int j = 0; j < strlen(c.arg_2) - 1; j++)
                    c.arg_2[j] = c.arg_2[j + 1];
                c.arg_2[strlen(c.arg_2) - 1] = '\0';

                sprintf(c.arg_2, "%ld", result[atol(c.arg_2)]);
                
                if (atol(c.arg_2) == LONG_MAX)
                    continue;
            }

            if (strcmp(c.operation, "VALUE") == 0)
                result[c.index] = atol(c.arg_1);
            if (strcmp(c.operation, "ADD") == 0)
                result[c.index] = atol(c.arg_1) + atol(c.arg_2);
            if (strcmp(c.operation, "SUB") == 0)
                result[c.index] = atol(c.arg_1) - atol(c.arg_2);
            if (strcmp(c.operation, "MULT") == 0)
                result[c.index] = atol(c.arg_1) * atol(c.arg_2);

            // remove the ith element
            for (int j = i; j < left_index - 1; j++)
                left[j] = left[j + 1];
            left_index--;

            break;
        }
    }

    for (int i = 0; i < n; i++)
        printf("%ld\n", result[i]);
}

void clean() {
    free(left);
    free(result);
}

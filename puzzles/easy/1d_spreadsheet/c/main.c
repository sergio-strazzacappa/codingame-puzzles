#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>

const char *OPERATIONS[4] = { "VALUE", "ADD", "SUB", "MULT" };

typedef struct Cell{
    char operation[6];
    char arg_1[7];
    char arg_2[7];
    int index;
} Cell;

int n;
char operation[6];
char arg_1[7];
char arg_2[7];

int solve(char *operation, char *arg1_1, char *arg_2, int result[]);
int value(char *arg, int result[]);
int op(char *arg_1, char *arg_2, int result[], char operator);
int has_dep(char *arg, int result[]);

int main() {
    scanf("%d", &n);
    Cell left[n];

    for (int i = 0; i < n; i++) {
        scanf("%s%s%s", operation, arg_1, arg_2);

        Cell c;
        strcpy(c.operation, operation);
        strcpy(c.arg_1, arg_1);
        strcpy(c.arg_2, arg_2);
        c.index = i;

        left[i] = c;
    }

    int result[n];

    for (int i = 0; i < n; i++) {
        result[i] = -INT_MAX;
    }

    int size = n;

    while (size > 0) {
        for (int i = 0; i < n; i++) {
            Cell c = left[i];
            if (has_dep(c.arg_1, result) && has_dep(c.arg_2, result) && c.index != -1) {
                result[c.index] = solve(c.operation, c.arg_1, c.arg_2, result);
                left[i].index = -1;
                size--;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        printf("%d\n", result[i]);
    }
}


int solve(char *operation, char *arg_1, char *arg_2, int result[]) {
    if (!strcmp(operation, OPERATIONS[0]))  return value(arg_1, result);
    if (!strcmp(operation, OPERATIONS[1]))  return op(arg_1, arg_2, result, '+');
    if (!strcmp(operation, OPERATIONS[2]))  return op(arg_1, arg_2, result, '-');
    if (!strcmp(operation, OPERATIONS[3]))  return op(arg_1, arg_2, result, '*');

    return 0;
}

int value(char *arg, int result[]) {
    if (arg[0] == '$') {
        char val[7];
        for (int i = 1; i < 7; i++) {
            val[i - 1] = arg[i];
        }
        return result[atoi(val)];
    }
    return atoi(arg);
}

int op(char *arg_1, char *arg_2, int result[], char operator) {
    int op1, op2;

    if (arg_1[0] == '$') {
        char val[7];

        for (int i = 1; i < 7; i++) {
            val[i - 1] = arg_1[i];
        }
        op1 = result[atoi(val)];
    } else {
        op1 = atoi(arg_1);
    }

    if (arg_2[0] == '$') {
        char val[7];
        for (int i = 1; i < 7; i++) {
            val[i - 1] = arg_2[i];
        }
        op2 = result[atoi(val)];
    } else {
        op2 = atoi(arg_2);
    }

    if (operator == '+') return (op1 + op2);
    if (operator == '-') return (op1 - op2);
    if (operator == '*') return (op1 * op2);

    return -1;
}

int has_dep(char *arg, int result[]) {
    if (arg[0] == '$') {
        char val[7];
        for (int i = 1; i < 7; i++) {
            val[i - 1] = arg[i];
        }
        return result[atoi(val)] != -INT_MAX;
    }
    return 1;
}

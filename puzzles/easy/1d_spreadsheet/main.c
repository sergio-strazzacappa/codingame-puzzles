#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>

char* operations[4] = { "VALUE", "ADD", "SUB", "MULT" };

typedef struct Cell{
    char operation[6];
    char arg_1[7];
    char arg_2[7];
    int index;
} Cell;

int value(char* arg, int result[]) {
    if (arg[0] == '$') {
        char val[7];
        for (int i = 1; i < 7; i++) {
            val[i - 1] = arg[i];
        }
        return result[atoi(val)];
    }
    return atoi(arg);
}

int add(char* arg_1, char* arg_2, int result[]) {
    int op1;
    int op2;

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
    return op1 + op2;
}

int sub(char* arg_1, char* arg_2, int result[]) {
    int op1;
    int op2;

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
    return op1 - op2;
}

int mult(char* arg_1, char* arg_2, int result[]) {
    int op1;
    int op2;

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
    return op1 * op2;
}

int solve(char* operation, char* arg_1, char* arg_2, int result[]) {
    if (!strcmp(operation, operations[0])) {
        //fprintf(stderr, "[Debug] Value: %s\n", arg_1);
        return value(arg_1, result);
    }
    if (!strcmp(operation, operations[1])) {
        //fprintf(stderr, "[Debug] Add: %s %s\n", arg_1, arg_2);
        return add(arg_1, arg_2, result);
    }
    if (!strcmp(operation, operations[2])) {
        //fprintf(stderr, "[Debug] Sub\n");
        return sub(arg_1, arg_2, result);
    }
    if (!strcmp(operation, operations[3])) {
        //fprintf(stderr, "[Debug] Mult\n");
        return mult(arg_1, arg_2, result);
    }
    return 0;
}

int has_dep(char* arg, int result[]) {
    //fprintf(stderr, "Has deps %s\n", arg);

    if (arg[0] == '$') {
        char val[7];
        for (int i = 1; i < 7; i++) {
            val[i - 1] = arg[i];
        }
        return result[atoi(val)] != -INT_MAX;
    }
    return 1;
}

int main() {
    int n;
    scanf("%d", &n);

    int result[n];
    Cell left[n];

    for (int i = 0; i < n; i++) {
        result[i] = -INT_MAX;
    }

    for (int i = 0; i < n; i++) {
        char operation[6];
        char arg_1[7];
        char arg_2[7];
        scanf("%s%s%s", operation, arg_1, arg_2);

        Cell c;
        strcpy(c.operation, operation);
        strcpy(c.arg_1, arg_1);
        strcpy(c.arg_2, arg_2);
        c.index = i;

        left[i] = c;
    }

    int size = n;

    while (size > 0) {
        for (int i = 0; i < n; i++) {
            Cell c = left[i];
            if (has_dep(c.arg_1, result) && has_dep(c.arg_2, result) && c.index != -1) {
                //fprintf(stderr, "Solving\n");
                result[c.index] = solve(c.operation, c.arg_1, c.arg_2, result);
                left[i].index = -1;
                size--;
            }
            //fprintf(stderr, "Result: ");
            //for (int i = 0; i < n; i++) {
            //    fprintf(stderr, "%d ", result[i]);
            //}
            //fprintf(stderr, "\n");*/
        }
    }

    for (int i = 0; i < n; i++) {
        printf("%d\n", result[i]);
    }
}
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>

#define TEST            0
#define NUMBER_FILES    13

const char *INPUT_FILE[] = {
    "input/01_simple_dependency.txt",
    "input/02_double_dependency.txt",
    "input/03_substraction.txt",
    "input/04_multiplication.txt",
    "input/05_no_dependencies.txt",
    "input/06_coefficients.txt",
    "input/07_fibonacci.txt",
    "input/08_backward_dependency.txt",
    "input/09_diamond_dependency.txt",
    "input/10_accounting_is_easy.txt",
    "input/11_accounting_is_hard_1.txt",
    "input/12_accounting_is_hard_2.txt",
    "input/13_deep_birecursion.txt",
};

const char *OUTPUT_FILE[] = {
    "output/01_simple_dependency.txt",
    "output/02_double_dependency.txt",
    "output/03_substraction.txt",
    "output/04_multiplication.txt",
    "output/05_no_dependencies.txt",
    "output/06_coefficients.txt",
    "output/07_fibonacci.txt",
    "output/08_backward_dependency.txt",
    "output/09_diamond_dependency.txt",
    "output/10_accounting_is_easy.txt",
    "output/11_accounting_is_hard_1.txt",
    "output/12_accounting_is_hard_2.txt",
    "output/13_deep_birecursion.txt",
};

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
    if (TEST) {
        for (int i = 0; i < NUMBER_FILES; i++) {
            FILE *fp; 
            char line[20];
            int index = 0;;

            if ((fp = fopen(INPUT_FILE[i], "r")) == NULL) {
                printf("[ERROR] Can't open the file %s\n", INPUT_FILE[i]);
                exit(1);
            }

            fgets(line, 20, fp); n = atoi(line);

            Cell left[n];
            int result[n];

            while (fgets(line, 20, fp)) {
                Cell c;
                strcpy(c.operation, strtok(line, " "));   
                strcpy(c.arg_1, strtok(NULL, " "));
                strcpy(c.arg_2, strtok(NULL, " \n"));
                c.index = index;
                left[index] = c;
                index++;
            }
            for (int j = 0; j < n; j++) {
                result[j] = -INT_MAX;
            }

            int size = n;

            while (size > 0) {
                for (int j = 0; j < n; j++) {
                    Cell c = left[j];
                    if (has_dep(c.arg_1, result) && has_dep(c.arg_2, result) && c.index != -1) {
                        result[c.index] = solve(c.operation, c.arg_1, c.arg_2, result);
                        left[j].index = -1;
                        size--;
                    }
                }
            }
            fclose(fp);

            if ((fp = fopen(OUTPUT_FILE[i], "r")) == NULL) {
                printf("[ERROR] Can't open the file %s\n", INPUT_FILE[i]);
                exit(1);
            }

            int j = 0;
            while (fgets(line, 20, fp)) {
                if (atoi(line) != result[j])
                    printf("FAILED\n");
                j++;
            }
            if (j == n)
                printf("PASSED\n");

            fclose(fp);
        }
    } else {
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

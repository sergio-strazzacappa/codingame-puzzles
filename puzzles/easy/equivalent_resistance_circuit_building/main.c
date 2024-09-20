#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct Resistor {
    char name[11];
    int r;
};

struct Symbol {
    char c;
    double d;
};

void print_stack(struct Symbol stack[], int n);

int main() {
    int n;
    scanf("%d", &n);

    struct Resistor resistors[n];
    struct Symbol stack[1000];
    int top = 0;

    for (int i = 0; i < n; i++) {
        char name[11];
        int r;

        scanf("%s%d", name, &r);
        fgetc(stdin);

        struct Resistor res;
        strcpy(res.name, name);
        res.r = r;

        resistors[i] = res;
    }

    for (int i = 0; i < n; i++) {
        fprintf(stderr, "[DEBUG] %s - %d\n", resistors[i].name, resistors[i].r);
    }
    fprintf(stderr, "\n");

    char circuit[121];
    scanf("%[^\n]", circuit);

    int index = 0;
    char name[11] = "";
    double result = 0;

    for (int i = 0; i < strlen(circuit); i++) {
        if (circuit[i] == '(' || circuit[i] == '[') {
            struct Symbol s;
            s.c = circuit[i];
            s.d = -1;
            stack[top] = s;
            top++;
            print_stack(stack, top);
        } else if (isalpha(circuit[i])) {
            name[index] = circuit[i];
            index++;
        } else if (circuit[i] == ' ') {
            // End of circuit
            name[index] = '\0';
            for (int j = 0; j < n; j++) {
                if (strcmp(name, resistors[j].name) == 0) {
                    struct Symbol s;
                    s.c = '-';
                    s.d = resistors[j].r;
                    stack[top] = s;
                    top++;
                    print_stack(stack, top);
                    break;
                }
            }
            index = 0;
            name[index] = '\0';
        } else if (circuit[i] == ')') {
            result = 0;
            while (stack[top - 1].c != '(') {
                result += stack[top - 1].d;
                top--;
            }
            stack[top - 1].c = '-';
            stack[top - 1].d = result;
            print_stack(stack, top);
        } else if (circuit[i] == ']') {
            result = 0;
            while (stack[top - 1].c != '[') {
                result += 1 / stack[top - 1].d;
                top--;
            }
            result = 1 / result;
            stack[top - 1].c = '-';
            stack[top - 1].d = result;
            print_stack(stack, top);
        }
    }

    printf("%0.1f\n", result);

    return 0;
}

void print_stack(struct Symbol stack[], int n) {
    fprintf(stderr, "[DEBUG] THE STACK\n");
    fprintf(stderr, "[DEBUG] ---------\n");

    for (int i = 0; i < n; i++) {
        if (stack[i].c != '-') fprintf(stderr, "[DEBUG] %c\n", stack[i].c);
        if (stack[i].d != -1) fprintf(stderr, "[DEBUG] %0.1f\n", stack[i].d);
    }
}
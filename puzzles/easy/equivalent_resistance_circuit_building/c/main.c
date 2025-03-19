#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct resistor {
    char name[11];
    int r;
} Resistor;

typedef struct symbol {
    char c;
    double d;
} Symbol;

int n;
Resistor *resistors;
char circuit[121];

void read_input();
void solve();
void print_stack(Symbol stack[], int n);

int main() {
    read_input();
    solve();
    free(resistors);

    return 0;
}

void read_input() {
    scanf("%d", &n);

    resistors = (Resistor *)malloc(sizeof(Resistor) * n);

    for (int i = 0; i < n; i++) {
        char name[11];
        int r;

        scanf("%s%d", name, &r);
        fgetc(stdin);

        Resistor res;
        strcpy(res.name, name);
        res.r = r;

        resistors[i] = res;
    }

    for (int i = 0; i < n; i++)
        fprintf(stderr, "[DEBUG] %s - %d\n", resistors[i].name, resistors[i].r);
    fprintf(stderr, "\n");

    scanf("%[^\n]", circuit);
}

void solve() {
    Symbol stack[1000];
    int top = 0;
    int index = 0;
    char name[11] = "";
    double result = 0;

    for (int i = 0; i < strlen(circuit); i++) {
        if (circuit[i] == '(' || circuit[i] == '[') {
            Symbol s;
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
                    Symbol s;
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

}

void print_stack(Symbol stack[], int n) {
    fprintf(stderr, "[DEBUG] THE STACK\n");
    fprintf(stderr, "[DEBUG] ---------\n");

    for (int i = 0; i < n; i++) {
        if (stack[i].c != '-')
            fprintf(stderr, "[DEBUG] %c\n", stack[i].c);
        if (stack[i].d != -1)
            fprintf(stderr, "[DEBUG] %0.1f\n", stack[i].d);
    }
}

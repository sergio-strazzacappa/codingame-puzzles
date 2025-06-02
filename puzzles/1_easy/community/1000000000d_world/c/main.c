#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct data {
    int n;
    int times;
} Data;

Data a[100];
Data b[100];
int a_index;
int b_index;

void init();
void parse(char str[], Data ds[], int *index);
void solve();
void debug();

int main() {
    init();
    solve();
    
    return 0;
}

void init() {
    char a_input[1001];
    char b_input[1001];

    scanf("%[^\n]", a_input);
    fgetc(stdin);
    scanf("%[^\n]", b_input);
    fgetc(stdin);

    a_index = 0;
    b_index = 0;

    parse(a_input, a, &a_index);
    parse(b_input, b, &b_index);
}

void parse(char str[], Data ds[], int *index) {
    char *token = strtok(str, " ");

    while (token != NULL) {
        Data d;

        d.times = atoi(token);
        token = strtok(NULL, " ");
        d.n = atoi(token);
        ds[(*index)++] = d;
        token = strtok(NULL, " ");
    }
}

void solve() {
    long dot_product = 0;

    for (int i = 0; i < a_index; i++) {
        for (int j = 0; j < b_index; j++) {
            if (a[i].times == 0)
                break;
            if (b[j].times == 0)
                continue;
            if (a[i].times <= b[j].times) {
                dot_product += (long)a[i].n * b[j].n * a[i].times;
                b[j].times -= a[i].times;
                a[i].times = 0;
            } else {
                dot_product += (long)a[i].n * b[j].n * b[j].times;
                a[i].times -= b[j].times;
                b[j].times = 0;
            }
        }
    }

    printf("%ld\n", dot_product);
}

void debug() {
    fprintf(stderr, "[DEBUG] Number a: \n");
    for (int i = 0; i < a_index; i++) {
        fprintf(stderr, "[DEBUG] (%d, %d)\n", a[i].n, a[i].times);
    }

    fprintf(stderr, "[DEBUG] Number b: \n");
    for (int i = 0; i < b_index; i++) {
        fprintf(stderr, "[DEBUG] (%d, %d)\n", b[i].n, b[i].times);
    }
}

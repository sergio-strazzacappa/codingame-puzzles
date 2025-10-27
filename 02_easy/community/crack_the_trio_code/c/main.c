#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NUM 120

int triad_set[MAX_NUM];
int triad_set_len;

void init();
void solve();
int is_solution(int a, int b, int c, int n);
void debug();

int main() {
    init();
    solve();

    return 0;
}

void init() {
    triad_set_len = 0;

    char line[1025];
    scanf("%[^\n]", line);

    char *token = strtok(line, ",");

    while (token != NULL) {
        triad_set[triad_set_len++] = atoi(token);
        token = strtok(NULL, ",");
    }
}

void solve() {
    int triads = 0;
    int aa, bb, cc;

    for (int a = 0; a <= triad_set[triad_set_len - 1]; a++) {
        for (int b = a; b <= triad_set[triad_set_len - 1]; b++) {
            for (int c = b; c <= triad_set[triad_set_len - 1]; c++) {
                int flag = 1;
                for (int i = 0; i < triad_set_len; i++) {
                    if (!is_solution(a, b, c, triad_set[i])) {
                        flag = 0;
                        break;
                    }
                }
                if (!flag)
                    continue;
                aa = a;
                bb = b;
                cc = c;
                triads++;
            }
        }
    }

    if (triads > 1)
        printf("many\n");
    else if (triads == 0)
        printf("none\n");
    else
        printf("%d,%d,%d\n", aa, bb, cc);
}

int is_solution(int a, int b, int c, int n) {
    return
        (a          == n) ||
        (b          == n) ||
        (c          == n) ||
        (a + a      == n) ||
        (a + b      == n) ||
        (a + c      == n) ||
        (b + b      == n) ||
        (b + c      == n) ||
        (c + c      == n) ||
        (a + a + a  == n) ||
        (a + a + b  == n) ||
        (a + a + c  == n) ||
        (a + b + b  == n) ||
        (a + b + c  == n) ||
        (a + c + c  == n) ||
        (b + b + b  == n) ||
        (b + b + c  == n) ||
        (b + c + c  == n) ||
        (c + c + c  == n);
}

void debug() {
    fprintf(stderr, "[DEBUG] [");

    for (int i = 0; i < triad_set_len; i++) {
        fprintf(stderr, " %d", triad_set[i]);

        if (i < triad_set_len - 1)
            fprintf(stderr, ",");
    }
    
    fprintf(stderr, " ]\n");
}

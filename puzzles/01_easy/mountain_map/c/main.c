#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int n;
int *mountains;

void init();
void clean();
void solve();
void spaces(int s);
bool last_mountain(int current_line, int i);

int main() {
    init();
    solve();
    clean();

    return 0;
}

void init() {
    scanf("%d", &n);

    mountains = (int *)malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++)
        scanf("%d", &mountains[i]);
}

void clean() {
    free(mountains);
}

void solve() {
    int current_line = 0;

    for (int i = 0; i < n; i++) {
        if (mountains[i] > current_line)
            current_line = mountains[i];
    }

    while (current_line) {
        for (int i = 0; i < n; i++) {
            if (current_line > mountains[i]) {
                if (!last_mountain(current_line, i))
                    spaces(mountains[i] * 2);
                continue;
            }
            spaces(current_line - 1);
            printf("/");
            spaces((mountains[i] - current_line) * 2);
            printf("\\");

            if (!last_mountain(current_line, i))
                spaces(current_line - 1);
        }
        printf("\n");
        current_line--;
    }
}

void spaces(int s) {
    for (int i = 0; i < s; i++)
        printf(" ");
}

bool last_mountain(int current_line, int i) {
    bool highest = true;
        for (int j = i + 1; j < n; j++) {
            if (mountains[j] >= current_line)
                highest = false;
        }
    return highest;
}

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define EMPTY_SYMBOL ' '

int cols;
int rows;
int n;
char *symbols;
int  *positions;

void init();
void solve();
void format_output(char solution[rows][cols]);
void clean();

int main() {
    init();
    solve(); 

    return 0;
}

void init() {
    scanf("%d%d%d", &cols, &rows, &n);

    symbols = (char *)malloc(sizeof(char) * n);
    positions = (int *)malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++) {
        char s[2];
        int p;

        scanf("%s%d", s, &p);
        symbols[i] = s[0];
        positions[i] = p;
    }
}

void solve() {
    char solution[rows][cols];

    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            solution[y][x] = EMPTY_SYMBOL;
        }
    }

    for (int i = 0; i < n; i++) {
        char s = symbols[i];
        int x = positions[i];

        for (int y = 0; y < rows; y++) {
            if (solution[y][x] != EMPTY_SYMBOL) {
                if (islower(s)) {
                    // right, left
                    if (x + 1 < cols && solution[y][x + 1] == EMPTY_SYMBOL) {
                        y--;
                        x++;
                        continue;
                    }
                    if (x - 1 >= 0 && solution[y][x - 1] == EMPTY_SYMBOL) {
                        y--;
                        x--;
                        continue;
                    }
                    solution[y - 1][x] = s;
                    break;
                }
                if (isupper(s)) {
                    // left, right
                    if (x - 1 >= 0 && solution[y][x - 1] == EMPTY_SYMBOL) {
                        y--;
                        x--;
                        continue;
                    }
                    if (x + 1 < cols && solution[y][x + 1] == EMPTY_SYMBOL) {
                        y--;
                        x++;
                        continue;
                    }
                    solution[y - 1][x] = s;
                    break;
                }
            }
            if (y == rows - 1) {
                solution[y][x] = s;
            }
        }
    }
    format_output(solution);
}

void format_output(char solution[rows][cols]) {
    for (int y = 0; y < rows; y++) {
        printf("|");

        for (int x = 0; x < cols; x++)
            printf("%c", solution[y][x]);

        printf("|\n");
    }

    printf("+");

    for (int x = 0; x < cols; x++)
        printf("-");

    printf("+\n");
}

void clean() {
    free(symbols);
    free(positions);
}

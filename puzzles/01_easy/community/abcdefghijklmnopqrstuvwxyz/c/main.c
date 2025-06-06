#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct point {
    int x;
    int y;
} Point;

const int DIRS[4][2] = {
    {1, 0},
    {0, 1},
    {-1, 0},
    {0, -1}
};

int size;
char **grid;

void init();
void solve();
bool find_solution(Point start);
void clean();
void debug();

int main() {
    init();
    solve();
    clean();

    return 0;
}

void init() {
    scanf("%d", &size);
    grid = (char **)malloc(sizeof(char*) * size);

    for (int y = 0; y < size; y++) {
        char m[size + 1];
        scanf("%s", m);

        grid[y] = (char *)malloc(sizeof(char) * size);

        for (int x = 0; x < strlen(m); x++) {
            grid[y][x] = m[x];
        }
    }
}

void solve() {
    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            if (grid[y][x] == 'a') {
                Point start = {x, y};
                find_solution(start);
            }
        }
    }
}

bool find_solution(Point start) {
    bool found = true;
    char letter = 'a';
    char **solution = (char **)malloc(sizeof(char *) * size);

    for (int y = 0; y < size; y++)
        solution[y] = (char *)malloc(sizeof(char) * size);

    for (int y = 0; y < size; y++)
        for (int x = 0; x < size; x++)
            solution[y][x] = '-';

    while (found) {
        solution[start.y][start.x] = letter;

        if (letter == 'z') {
            found = true;
            break;
        }

        letter++;
        found = false;

        for (int i = 0; i < 4; i++) {
            Point next = {start.x + DIRS[i][0], start.y + DIRS[i][1]};

            if (next.x < 0)     continue;
            if (next.x >= size) continue;
            if (next.y < 0)     continue;
            if (next.y >= size) continue;

            if (grid[next.y][next.x] == letter) {
                start.x = next.x;
                start.y = next.y;
                found = true;
                break;
            }
        }
    }

    if (found) {
        for (int y = 0; y < size; y++) {
            for (int x = 0; x < size; x++) {
                printf("%c", solution[y][x]);
            }
            printf("\n");
        }
    }

    return found;
}

void clean() {
    for (int y = 0; y < size; y++)
        free(grid[y]);
    free(grid);
}

void debug() {
    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            fprintf(stderr, "%c", grid[y][x]);
        }
        fprintf(stderr, "\n");
    }
}

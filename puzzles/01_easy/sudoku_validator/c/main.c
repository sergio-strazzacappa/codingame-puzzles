#include <stdio.h>
#include <stdbool.h>

#define ROWS 9
#define COLS 9

int grid[ROWS][COLS];
bool rows[ROWS][COLS];
bool cols[ROWS][COLS];
bool subgrids[ROWS][COLS];

void init();
void solve();
bool validate(bool matrix[ROWS][COLS]);
void print_grid();

int main() {
    init();
    solve();

    return 0;
}

void init() {
    for (int y = 0; y < ROWS; y++)
        for (int x = 0; x < COLS; x++)
            scanf("%d", &grid[y][x]);

    for (int y = 0; y < ROWS; y++) {
        for (int x = 0; x < COLS; x++) {
            rows[y][x]      = false;
            cols[y][x]      = false;
            subgrids[y][x]  = false;
        }
    }
}

void solve() {
    for (int y = 0; y < ROWS; y++) {
        for (int x = 0; x < COLS; x++) {
            rows[y][grid[y][x] - 1]                         = true;
            cols[x][grid[y][x] - 1]                         = true;
            subgrids[3 * (y / 3) + x / 3][grid[y][x] - 1]   = true;
        }
    }

    if (validate(rows) && validate(cols) && validate(subgrids))
        printf("true\n");
    else
        printf("false\n");
}

bool validate(bool matrix[ROWS][COLS]) {
    for (int y = 0; y < ROWS; y++) {
        for (int x = 0; x < COLS; x++) {
            if (!matrix[y][x])
                return false;
        }
    }
    return true;
}

void print_grid() {
    for (int y = 0; y < ROWS; y++) {
        for (int x = 0; x < COLS; x++) {
            fprintf(stderr, "%d", grid[y][x]);
        }
        fprintf(stderr, "\n");
    }
}

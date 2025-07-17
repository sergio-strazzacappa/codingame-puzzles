#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 15

int n;
char grid[MAX_SIZE][MAX_SIZE];

void init();
void solve();
bool is_solved();
void debug();

int main() {
    init();
    solve();

    return 0;
}

void init() {
    scanf("%d%*c", &n);

    for (int y = 0; y < n; y++) {
        char row[n + 1];
        scanf("%[^\n]%*c", row);

        for (int x = 0; x < n; x++)
            grid[y][x] = row[x];
    }
}

void solve() {
    while (!is_solved()) {
        for (int y = 0; y < n; y++) {
            for (int x = 0; x < n; x++) {
                if (grid[y][x] == '.') {
                    // try to set the square to 0 or 1
                    int ones = 0;
                    int zeros = 0;

                    if (x - 1 >= 0 && grid[y][x - 1] == '1') {
                        ones++;
                        if (x - 2 >= 0 && grid[y][x - 2]  == '1')
                            ones++;
                    }
                    if (x + 1 < n && grid[y][x + 1] == '1') {
                        ones++;
                        if (x + 2 < n && grid[y][x + 2] == '1')
                        ones++;
                    }

                    if (ones >= 2) { 
                        grid[y][x] = '0';
                        y = -1;
                        break;
                    }

                    if (x - 1 >= 0 && grid[y][x - 1] == '0') {
                        zeros++;
                        if (x - 2 >= 0 && grid[y][x - 2] == '0')
                        zeros++;
                    }
                    if (x + 1 < n && grid[y][x + 1] == '0') {
                        zeros++;
                        if (x + 2 < n && grid[y][x + 2] == '0')
                        zeros++;
                    }

                    if (zeros >= 2) { 
                        grid[y][x] = '1';
                        y = -1;
                        break;
                    }

                    ones = 0;
                    zeros = 0;

                    if (y - 1 >= 0 && grid[y - 1][x] == '1') {
                        ones++;
                        if (y - 2 >= 0 && grid[y - 2][x] == '1')
                        ones++;
                    }
                    if (y + 1 < n && grid[y + 1][x] == '1') {
                        ones++;
                        if (y + 2 < n && grid[y + 2][x] == '1')
                        ones++;
                    }

                    if (ones >= 2) { 
                        grid[y][x] = '0';
                        y = -1;
                        break;
                    }

                    if (y - 1 >= 0 && grid[y - 1][x] == '0') {
                        zeros++;
                        if (y - 2 >= 0 && grid[y - 2][x] == '0')
                        zeros++;
                    }
                    if (y + 1 < n && grid[y + 1][x] == '0') {
                        zeros++;
                        if (y + 2 < n && grid[y + 2][x] == '0')
                        zeros++;
                    }

                    if (zeros >= 2) { 
                        grid[y][x] = '1';
                        y = -1;
                        break;
                    }
                }
            }
        }
    }

    for (int y = 0; y < n; y++) {
        for (int x = 0; x < n; x++)
            printf("%c", grid[y][x]);
        printf("\n");
    }
}

bool is_solved() {
    for (int y = 0; y < n; y++)
        for (int x = 0; x < n; x++)
            if (grid[y][x] == '.')
                return false;
    return true;
}

void debug() {
    for (int y = 0; y < n; y++) {
        for (int x = 0; x < n; x++)
            fprintf(stderr, "%c", grid[y][x]);
        fprintf(stderr, "\n");
    } 
}

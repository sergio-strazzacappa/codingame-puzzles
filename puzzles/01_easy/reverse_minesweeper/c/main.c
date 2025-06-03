#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int moves[8][2]= {
    {1, 0},
    {1, 1},
    {0, 1},
    {-1, 1},
    {-1, 0},
    {-1, -1},
    {0, -1},
    {1, -1}
};

int height;
int width;
char **grid;
char **solution;

void init();
void solve();
void print_grid(char **g);
void clean();

int main() {
    init();
    solve();
    clean();

    return 0;
}

void init() {
    scanf("%d%d", &width, &height);
    fgetc(stdin);

    grid        = (char **)malloc(sizeof(char *) * height);
    solution    = (char **)malloc(sizeof(char *) * height);

    for (int y = 0; y < height; y++) {
        char line[101];
        scanf("%s", line);
        fgetc(stdin);

        grid[y]     = (char *)malloc(sizeof(char) * width);
        solution[y] = (char *)malloc(sizeof(char) * width);

        for (int x = 0; x < strlen(line); x++) {
            grid[y][x] = line[x];
            solution[y][x] = 0;
        }
    }
}

void solve() {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (grid[y][x] == 'x') {
                // it's a mine, add its neighbors
                for (int i = 0; i < 8; i++) {
                    if (y + moves[i][1] < 0)
                        continue;
                    if (y + moves[i][1] >= height)
                        continue;
                    if (x + moves[i][0] < 0)
                        continue;
                    if (x + moves[i][0] >= width)
                        continue;
                    if (grid[y + moves[i][1]][x + moves[i][0]] != 'x')
                        solution[y + moves[i][1]][x + moves[i][0]]++;
                }
            }
        }
    }

    print_grid(solution);
}

void print_grid(char **g) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (solution[y][x] == 0) {
                printf(".");
                continue;
            }
            printf("%d", solution[y][x]);
        }
        printf("\n");
    }
}

void clean() {
    for (int y = 0; y < height; y++) {
        free(grid[y]);
        free(solution[y]);
    }

    free(grid);
    free(solution);
}

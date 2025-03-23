#include <stdio.h>
#include <string.h>

#define W   30
#define H   30

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
char grid[H][W];
char solution[H][W];

void solve();

int main() {
    scanf("%d%d", &width, &height);
    fgetc(stdin);

    for (int y = 0; y < height; y++) {
        char line[101];
        scanf("%s", line);
        fgetc(stdin);

        for (int x = 0; x < strlen(line); x++) {
            grid[y][x] = line[x];
            solution[y][x] = 0;
        }
    }

    solve();

    return 0;
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

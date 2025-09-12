#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

const int dirs[8][2] = {
    {+1, +0},
    {+1, +1},
    {+0, +1},
    {-1, +1},
    {-1, +0},
    {-1, -1},
    {+0, -1},
    {+1, -1}
};

int rows;
int cols;
int **map;

void init();
void solve();
void find_all(char *str);
void clean();
void print_map();

int main() {
    init();
    solve();
    clean();

    return 0;
}

void init() {
    scanf("%d", &rows);
    fgetc(stdin);

    cols = 0;
    map = (int **)malloc(sizeof(int *) * rows);

    for (int y = 0; y < rows; y++) {
        char line[101] = "";
        scanf("%[^\n]", line);
        fgetc(stdin);

        // split each line into the ints values
        char *token = strtok(line, " ");
        int data[101];
        int index = 0;

        // stores a line of data
        while (token != NULL) {
            data[index++] = atoi(token);
            token = strtok(NULL, " ");
        }

        if (cols == 0)
            cols = index;

        map[y] = (int *)malloc(sizeof(int) * cols);

        // stores the line of data into the map
        for (int x = 0; x < cols; x++)
            map[y][x] = data[x];
    }
}

void solve() {
    find_all("peaks");
    find_all("valleys");
}

void find_all(char *str) {
    int n = 0;
    bool first = true;

    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            int current = map[y][x];
            bool solution = true;

            for (int i = 0; i < 8; i++) {
                int next_x = x + dirs[i][0];
                int next_y = y + dirs[i][1];

                if (next_x < 0)             continue;
                if (next_x > cols - 1)      continue;
                if (next_y < 0)             continue;
                if (next_y > rows - 1)      continue;

                bool is_peak = strcmp(str, "peaks") == 0;
                bool is_valley = strcmp(str, "valleys") == 0;
                
                if ((is_peak && current <= map[next_y][next_x]) ||
                    (is_valley && current >= map[next_y][next_x])) {
                    // the current cell is not a peak or a vally
                    solution = false;
                    break;
                }
            }
            if (solution) {
                // the current cell is either a peak or a valley
                if (!first)
                    printf(", ");
                printf("(%d, %d)", x, y);
                first = false;
                n++;
            }
        }
    }
    if (n == 0)
        printf("NONE");
    printf("\n");
}

void clean() {
    for (int y = 0; y < rows; y++)
        free(map[y]);
    free(map);
}

void print_map() {
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++)
            fprintf(stderr, "%04d ", map[y][x]);
        fprintf(stderr, "\n");
    }
}

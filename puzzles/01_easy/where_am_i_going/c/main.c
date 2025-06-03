#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

enum Direction {
    RIGHT,
    DOWN,
    LEFT,
    UP
};

const int directions[4][2] = {
    {1, 0},
    {0, 1},
    {-1, 0},
    {0, -1}
};

int rows;
int cols;
char **map;

struct me {
    int x;
    int y;
    enum Direction dir;
} me;

void init();
void solve();
bool in_map(int x, int y);
void clean();
void print_map();

int main() {
    init();
    solve();
    clean();

    return 0;
}

void init() {
    scanf("%d%d", &rows, &cols);
    fgetc(stdin);

    // initialize the map
    map = (char **)malloc(sizeof(char *) * rows);

    for (int y = 0; y < rows; y++) {
        map[y] = (char *)malloc(sizeof(char) * cols);
        scanf("%[^\n]", map[y]);
        fgetc(stdin);
    }

    // initialize my position
    me.x = -1;
    me.y = 0;
    me.dir = RIGHT;
}

void solve() {
    bool solved = false;
    int steps = 0;

    while (!solved) {
        int next_x = me.x + directions[me.dir][0];
        int next_y = me.y + directions[me.dir][1];

        if (in_map(next_x, next_y) && map[next_y][next_x] == '#') {
            me.x = next_x;
            me.y = next_y;
            steps++;
            continue;
        }

        if (!in_map(next_x, next_y) || map[next_y][next_x] == '.') {
            enum Direction next_dir;

            // turn right
            if (me.dir != UP) {
                next_dir = me.dir + 1;
                next_x = me.x + directions[next_dir][0];
                next_y = me.y + directions[next_dir][1];
            } else {
                next_dir = RIGHT;
                next_x = me.x + directions[next_dir][0];
                next_y = me.y + directions[next_dir][1];
            }
            if (in_map(next_x, next_y) && map[next_y][next_x] == '#') {
                me.dir = next_dir;
                printf("%dR", steps);
                steps = 0;
                continue;
            }
            
            // turn left
            if (me.dir != RIGHT) {
                next_dir = me.dir - 1;
                next_x = me.x + directions[next_dir][0];
                next_y = me.y + directions[next_dir][1];
            } else {
                next_dir = UP; 
                next_x = me.x + directions[next_dir][0];
                next_y = me.y + directions[next_dir][1];
            }
            if (in_map(next_x, next_y) && map[next_y][next_x] == '#') {
                me.dir = next_dir;
                printf("%dL", steps);
                steps = 0;
                continue;
            }
        }

        printf("%d\n", steps);
        solved = true;
    }
}

bool in_map(int x, int y) {
    if (x < 0)      return false;
    if (x >= cols)  return false;
    if (y < 0)      return false;
    if (y >= rows)  return false;

    return true;
}

void clean() {
    for (int y = 0; y < rows; y++)
        free(map[y]);
    free(map);
}

void print_map() {
    for (int y = 0; y < rows; y++)
        fprintf(stderr, "%s\n", map[y]);
}

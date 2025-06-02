#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct point {
    int x;
    int y;
} Point;

const int MOVES[4][2] = {
    {1, 0},
    {0, 1},
    {-1, 0},
    {0, -1}
};

int rows;
int cols;
char **map;
Point me;

void init();
void solve();
Point locate_me();
void dfs(Point current, Point v[], int *v_index, int gold, int *max);
bool visited(Point p, Point v[], int v_index);
void clean();
void debug();

int main() {
    init();
    solve();
    clean();

    return 0;
}

void init() {
    scanf("%d%d", &rows, &cols);
    fgetc(stdin);

    map = (char **)malloc(sizeof(char *) * rows);

    for (int y = 0; y < rows; y++) {
        map[y] = (char *)malloc(sizeof(char) * cols + 1);
        scanf("%[^\n]", map[y]);
        fgetc(stdin);
    }
}

void solve() {
    Point me = locate_me();

    Point v[rows * cols];
    int v_index = 0;
    int max = 0;

    dfs(me, v, &v_index, 0, &max);

    printf("%d\n", max);
}

// returns the Point where am I
Point locate_me() {
    Point me = {-1, -1};

    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            if (map[y][x] == 'X') {
                me.x = x;
                me.y = y;
                return me;
            }
        }
    }
    fprintf(stderr, "[ERROR] Me not found\n");
    return me;
}

void dfs(Point current, Point v[], int *v_index, int gold, int *max) {
    v[*v_index] = current;
    *v_index = *v_index + 1;

    for (int i = 0; i < 4; i++) {
        Point next = {current.x + MOVES[i][0], current.y + MOVES[i][1]};

        if (next.x < 0)                 continue;
        if (next.x >= cols)             continue;
        if (next.y < 0)                 continue;
        if (next.y >= rows)             continue;
        if (visited(next, v, *v_index)) continue;
        if (map[next.y][next.x] == '#') continue;

        if (isdigit(map[next.y][next.x])) {
            if (gold + map[next.y][next.x] - '0' > *max)
                *max = gold + map[next.y][next.x] - '0';

            dfs(next, v, v_index, gold + map[next.y][next.x] - '0', max);
        } else
            dfs(next, v, v_index, gold, max);
    }
    *(v_index) = *(v_index) - 1;
}

// returns true of p was visited, otherwise false
bool visited(Point p, Point v[], int v_index) {
    for (int i = 0; i < v_index; i++) {
        if (p.x == v[i].x && p.y == v[i].y)
            return true;
    }
    return false;
}

void clean() {
    for (int y = 0; y < rows; y++)
        free(map[y]);
    free(map);
}

void debug() {
    fprintf(stderr, "Map of size %d X %d\n", rows, cols);

    for (int y = 0; y < rows; y++)
        fprintf(stderr, "%s\n", map[y]);
}

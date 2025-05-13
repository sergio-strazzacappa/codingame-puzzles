#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define MAX_CANDLES 1000

typedef struct point {
    int x;
    int y;
} Point;

int size;
int light;
char **map;
Point candles[MAX_CANDLES];
int c_index;

void init();
void solve();
int distance(Point p, Point q);
void clean();
void print_map();

int main() {
    init();
    solve();
    clean();
    
    return 0;
}

void init() {
    c_index = 0;
    scanf("%d%d", &size, &light);

    map = (char **)malloc(sizeof(char *) * size);

    for (int y = 0; y < size; y++) {
        map[y] = (char *)malloc(sizeof(char) * size);
        for (int x = 0; x < size; x++) {
            char cell[4];
            scanf("%s", cell);
            map[y][x] = cell[0];

            if (cell[0] == 'C') {
                Point p = {x, y};
                candles[c_index++] = p;
            }
        }
    }
}

void solve() {
    int places = 0;

    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            Point p = {x, y};
            bool in = true;
            for (int i = 0; i < c_index; i++) {
                Point q = candles[i];
                if (distance(p, q) < light) {
                    in = false;
                    break;
                }
            }
            if (in)
                places++;
        }
    }

    printf("%d\n", places);
}

int distance(Point p, Point q) {
    if (abs(p.x - q.x) > abs(p.y - q.y))
        return abs(p.x - q.x);
    else
        return abs(p.y - q.y);
}

void clean() {
    for (int y = 0; y < size; y++)
        free(map[y]);
    free(map);
}

void print_map() {
    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++)
            fprintf(stderr, "%c", map[y][x]);
        fprintf(stderr, "\n");
    }
}

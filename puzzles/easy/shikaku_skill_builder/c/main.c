#include <stdio.h>
#include <stdlib.h>

typedef struct point {
    int x;
    int y;
} Point;

typedef struct good_rectangle {
    int r;
    int c;
    int width;
    int height;
} Good_rectangle;

int width;
int height;
int **grid;

void read_input();
void solve();
void rectangles(int n, Point p);
int check(Point start, Point n, int w, int h);
int cmp(const void *a, const void *b);
void clear();
void print_grid();

int main() {
    read_input();
    solve();
    clear();

    return 0;
}

void read_input() {
    scanf("%d%d", &width, &height);

    grid = (int **)malloc(height * sizeof(int*));

    for (int y = 0; y < height; y++) {
        grid[y] = (int *)malloc(width * sizeof(int));
        for (int x = 0; x < width; x++) {
            scanf("%d", &grid[y][x]);
        }
    }
}

void solve() {
    int n;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (grid[y][x] != 0) {
                n = grid[y][x];
                Point p = {x, y};
                rectangles(n, p); // get all the rectangles of area n
            }
        }
    }
}

// n: the area
// (x, y): position of n
// return 1 if there is at least 1 good rectangle
void rectangles(int n, Point p) {
    Good_rectangle gs[100];
    int w, h;
    int gs_index = 0;

    for (int i = 1; i <= n; i++) {
        if (n % i == 0) {
            w = i;
            h = n / i;
            for (int y = p.y - (h - 1); y < p.y + h ; y++) {
                for (int x = p.x - (w - 1); x < p.x + w; x++) {
                    Point start = {x, y};
                    int is_valid = check(start, p, w, h);

                    if (!is_valid) continue;

                    Good_rectangle g = {y, x, w, h};
                    gs[gs_index++] = g;

                    if (gs_index == 1)
                        printf("%d %d %d\n", p.y, p.x, n);
                }
            }
        }
    }
    if (gs_index > 0) {
        qsort(gs, gs_index, sizeof(Good_rectangle), cmp);

        for (int i = 0; i < gs_index; i++) {
            printf("%d %d %d %d\n", gs[i].r, gs[i].c, gs[i].width, gs[i].height);
        }
    }
} 

// return 1 if the rectangle is valid
// from the start point until width and height, including the n point
// 0 otherwise
int check(Point start, Point n, int w, int h) {
    int has_n = 0;
    int area = 0;
    for (int y = start.y; y < start.y + h; y++) {
        for (int x = start.x; x < start.x + w; x++) {
            if (y < 0)                                      return 0;
            if (y > height - 1)                             return 0;
            if (x < 0)                                      return 0;
            if (x > width - 1)                              return 0;
            if (grid[y][x] != 0 && !(x == n.x && y == n.y)) return 0;
            if (area > grid[n.y][n.x])                      return 0;
            if (x == n.x && y == n.y)                       has_n = 1;
            area++;
        }
    }
    if (area == grid[n.y][n.x] && has_n)    return 1;
    else                                    return 0;
}

int cmp(const void *a, const void *b) {
    Good_rectangle *ga = (Good_rectangle *)a; 
    Good_rectangle *gb = (Good_rectangle *)b; 

    if ((ga->r - gb->r) != 0)       return (ga->r - gb->r);
    else if (ga->c - gb->c != 0)    return (ga->c - gb->c);
    else                            return (ga->width - gb->width);
}

void print_grid() {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++)
            fprintf(stderr, "%d ", grid[y][x]);
        fprintf(stderr, "\n");
    }
}

void clear() {
    for (int y = 0; y < height; y++)
        free(grid[y]);
    free(grid);
}

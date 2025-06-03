#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct point {
    int x;
    int y;
} Point;

const int directions[4][2] = {
    {1, 0},
    {0, 1},
    {-1, 0},
    {0, -1}
};

int rows;
int cols;
char **map;

void init();
void solve();
bool bfs(int start);
bool visited(Point p, Point v[], int v_index);
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

    map = (char **)malloc(sizeof(char *) * rows);

    for (int y = 0; y < rows; y++) {
        char row[1025];
        scanf("%[^\n]", row);
        fgetc(stdin);

        map[y] = (char *)malloc(sizeof(char) * cols);

        int x = 0;
        for (int i = 0; i < strlen(row); i++) {
            if (row[i] != ' ') {
                map[y][x] = row[i];
                x++;
            }
        }
    }
}

void solve() {
    int routes = 0;
    for (int y = 0; y < rows; y++) {
        if (map[y][0] == '+')
            routes += bfs(y);
    }

    printf("%d\n", routes);
}

// start is the row number trying to seek a path
bool bfs(int start) {
    Point q[rows * cols], v[rows * cols];
    int q_index = 0;
    int v_index = 0;
    Point current = {0, start};

    q[q_index++] = current;

    while (q_index > 0) {
        // fetch the first Point
        current = q[0];
        v[v_index++] = current;

        // remove the current Point from the queue
        for (int i = 0; i < q_index - 1; i++)
            q[i] = q[i + 1]; 
        q_index--;

        // search in every direction
        for (int i = 0; i < 4; i++) {
            Point next = {
                current.x + directions[i][0],
                current.y + directions[i][1]
            };

            if (next.x < 0)                 continue;
            if (next.x >= cols)             continue;
            if (next.y < 0)                 continue;
            if (next.y >= rows)             continue;
            if (visited(next, v, v_index))  continue;

            if (map[next.y][next.x] == '+') {
                // exit found
                if (next.x == cols - 1)
                    return true;

                q[q_index++] = next;
            }
        }
    }

    return false;
}

bool visited(Point p, Point v[], int v_index) {
    for (int i = 0; i < v_index; i++)
        if (v[i].x == p.x && v[i].y == p.y)
            return true;
    return false;
}

void clean() {
    for (int y = 0; y < rows; y++)
        free(map[y]);
    free(map);
}

void print_map() {
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++)
            fprintf(stderr, "%c", map[y][x]);
        fprintf(stderr, "\n");
    }
}

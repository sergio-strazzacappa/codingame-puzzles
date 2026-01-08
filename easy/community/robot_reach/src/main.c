#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

struct Point {
    int x;
    int y;
};

const int DIRS[4][2] = {
    {+1, +0},
    {+0, +1},
    {-1, +0},
    {+0, -1}
};

int rows;
int cols;
int threshold;

void solve();
int get_value(struct Point p);
bool is_visited(struct Point visited[], int visited_size, struct Point p);

int main() {
    scanf("%d%d%d", &rows, &cols, &threshold);
    solve();

    return 0;
}

void solve() {
    struct Point robot = { 0, 0 };
    struct Point frontier[rows * cols];
    struct Point visited[rows * cols];
    int frontier_size = 0;
    int visited_size = 0;
    int reachable_cells = 1;

    frontier[frontier_size++] = robot;
    visited[visited_size++] = robot;
    while (frontier_size > 0) {
        // remove current cell from the frontier
        robot = frontier[0];

        fprintf(stderr, "[DEBUG] The robot is at (%d, %d)\n", robot.x, robot.y);

        for (int i = 0; i < frontier_size - 1; i++) {
           frontier[i] = frontier[i + 1]; 
        }
        frontier_size--;

        for (int dir = 0; dir < 4; dir++) {
            struct Point next_point = { robot.x + DIRS[dir][0], robot.y + DIRS[dir][1] };

            if (next_point.x < 0)                               continue;
            if (next_point.x > cols - 1)                        continue;
            if (next_point.y < 0)                               continue;
            if (next_point.y > rows - 1)                        continue;
            if (is_visited(visited, visited_size, next_point))  continue;

            int value = get_value(next_point);

            if (value <= threshold) {
                visited[visited_size++] = next_point;
                frontier[frontier_size++] = next_point;
                reachable_cells++;
            }
        }
    }
    printf("%d\n", reachable_cells);
}

// get the cell value of a given point. That is the sum of the digit of the x
// coordinate plus the sum of the digits of the y coordinate
int get_value(struct Point p) {
    fprintf(stderr, "[DEBUG] get_value(%d, %d)\n", p.x, p.y);

    // convert both coordinates to string
    char x[4], y[4];
    sprintf(x, "%d", p.x);
    sprintf(y, "%d", p.y);

    // compute the value
    int value = 0;
    for (int c = 0; c < strlen(x); c++) value += x[c] - '0';
    for (int c = 0; c < strlen(y); c++) value += y[c] - '0';

    fprintf(stderr, "[DEBUG] value:%d\n", value);
    return value;
}

bool is_visited(struct Point visited[], int visited_size, struct Point p) {
    for (int i = 0; i < visited_size; i++) {
        if (visited[i].x == p.x && visited[i].y == p.y)
            return true;
    }
    return false;
}

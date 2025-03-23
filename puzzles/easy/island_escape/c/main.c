#include <stdio.h>
#include <stdlib.h>

typedef struct Point {
    int x;
    int y;
} Point;

const int MOVES[4][2] = {
    {1, 0},
    {0, 1},
    {-1, 0},
    {0, -1}
};

int size;
int map[20][20];

int solve();
int is_visited(Point p, Point v[], int v_index);
void print_map();
void print_queue(Point q[], int q_index);

int main() {
    scanf("%d", &size);

    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            int elevation;
            scanf("%d", &elevation);
            map[x][y] = elevation;
        }
    }

    int solution = solve();

    if (solution)
        printf("yes\n");
    else
        printf("no\n");

    return 0;
}

int solve() {
    Point q[size * size], v[size * size], current, next;
    int q_index, v_index;
    Point me = {
        .x = size / 2,
        .y = size / 2
    };
    
    q_index = 0;
    q[q_index++] = me;

    v_index = 0;
    v[v_index++] = me;

    while (q_index > 0) {
        // fetch the first element of the queue
        current = q[0];
        for (int i = 0; i < q_index - 1; i++) {
            q[i] = q[i + 1];
        }
        q_index--;

        // check for solution
        if (map[current.x][current.y] == 0) {
            return 1;
        }

        // try to move in every direction
        for (int i = 0; i < 4; i++) {
            next.x = current.x + MOVES[i][0];
            next.y = current.y + MOVES[i][1];

            if (next.x < 0)                     continue;
            if (next.x > size)                  continue;
            if (next.y < 0)                     continue;
            if (next.y > size)                  continue;
            if (is_visited(next, v, v_index))   continue;

            if (abs(map[current.x][current.y] - map[next.x][next.y]) <= 1) {
                // move to that cell
                q[q_index++] = next;
                v[v_index++] = next;
            }
        }
    }
    return 0;
}

// return 1 if p is visited, 0 otherwise
int is_visited(Point p, Point v[], int v_index) {
    for (int i = 0; i < v_index; i++)
        if (p.x == v[i].x && p.y == v[i].y)
            return 1;
    return 0;
}

void print_map() {
    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            printf("%d", map[x][y]);
        }
        printf("\n");
    }
}

void print_queue(Point q[], int q_index) {
    printf("[START QUEUE]\n");
    for (int i = 0; i < q_index; i++) {
        printf("(%d, %d)\n", q[i].x, q[i].y);
    }
    printf("[END QUEUE]\n");
}

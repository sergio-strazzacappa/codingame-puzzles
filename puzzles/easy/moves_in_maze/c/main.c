#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 30

typedef struct point {
    int x;
    int y;
} Point;

const int moves[4][2] = {
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
void print_map();
void print_q(Point q[], int index); 
void clean();

int main() {
    init();
    solve();
    print_map();
    clean();

    return 0;
}

void init() {
    scanf("%d%d", &cols, &rows);
    fgetc(stdin);

    map = (char **)malloc(sizeof(char *) * rows);

    for (int y = 0; y < rows; y++)
        map[y] = (char *)malloc(sizeof(char) * cols);

    for (int y = 0; y < rows; y++) {
        scanf("%[^\n]", map[y]);
        fgetc(stdin);
    }
}

void solve() {
    Point *start = NULL;

    // get the starting position
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            if (map[y][x] == 'S') {
                start = (Point *)malloc(sizeof(Point));
                start->x = x;
                start->y = y;
                break;
            }
        }
        if (start != NULL)
            break;
    }

    Point q[MAX_SIZE];
    int q_index = 0;

    // queue the starting point
    q[q_index++] = *start;

    // distance to the start point is 0
    map[q[0].y][q[0].x] = '0';

    while (q_index > 0) {
        //get the first element
        Point current = q[0];

        // remove the first element from the queue
        for (int i = 1; i < q_index; i++) {
            q[i - 1] = q[i];
        }
        q_index--;

        for (int i = 0; i < 4; i++) {
            Point next = current;
            
            next.x += moves[i][0];
            next.y += moves[i][1];

            if (next.x < 0)
                next.x = cols - 1;
            if (next.x == cols)
                next.x = 0;
            if (next.y < 0)
                next.y = rows - 1;
            if (next.y == rows)
                next.y = 0;

            if (map[next.y][next.x] != '.')
                continue;

            if (map[next.y][next.x] == '.') {
                int val = map[current.y][current.x] + 1;

                if (val > '9' && val < 'A')
                    val = 'A';

                map[next.y][next.x] = val;
                q[q_index++] = next;
            }
        }
    }
}

void print_map() {
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            printf("%c", map[y][x]);
        }
        printf("\n");
    }
}

void print_q(Point q[], int index) {
    fprintf(stderr, "[ ");

    for (int i = 0; i < index; i++) {
        fprintf(stderr, "(%d, %d)", q[i].x, q[i].y);
    }

    fprintf(stderr, " ]\n");
}

void clean() {
    for (int y = 0; y < rows; y++)
        free(map[y]);
    free(map);
}

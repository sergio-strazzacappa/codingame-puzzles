#include <stdio.h>

typedef struct Point {
    int x;
    int y;
} Point;

const int NEIGHBORS[4][2] = {
    {+1, -1},
    {+1, +1},
    {-1, +1},
    {-1, -1}
};

int n;
int g;

void sim(int current_index, char grid[n][n], Point frontier[n * n],
    int frontier_len, int *most_infected, int *index, char final_grid[n][n]);
void cp_frontier(Point src[n * n], int src_len, Point dst[n * n]);
void print_grid(char grid[n][n]);
void print_frontier(Point frontier[n * n], int frontier_len);

int main() {
    scanf("%d%d", &n, &g);
    fgetc(stdin);

    char final_grid[n][n];
    int index = 0;
    int most_infected = 0;

    for (int i = 0; i < g; i++) {
        char grid[n][n];
        Point frontier[n * n];
        int frontier_len = 0;

        for (int y = 0; y < n; y++) {
            char row[n + 1];
            scanf("%[^\n]", row);
            fgetc(stdin);

            for (int x = 0; x < n; x++) {
                grid[y][x] = row[x];

                if (row[x] == 'C')
                    frontier[frontier_len++] = (Point){x, y};
            }
        }
        // simulate each grid, updating the grid with most infected people
        sim(i, grid, frontier, frontier_len,
            &most_infected, &index, final_grid);
    }

    printf("%d\n", index);
    print_grid(final_grid);

    return 0;
}

void sim(int current_index, char grid[n][n], Point frontier[n * n],
    int frontier_len, int *most_infected, int *index, char final_grid[n][n]) {

    int infected = 0;
    while (frontier_len > 0) {
        Point new_frontier[n * n];
        int new_frontier_len = 0;
        infected += frontier_len;

        for (int i = 0; i < frontier_len; i++) {
            Point C = frontier[i];

            for (int j = 0; j < 4; j++) {
                Point next = {C.x + NEIGHBORS[j][0], C.y + NEIGHBORS[j][1]};

                if (next.x < 0)                     continue;
                if (next.x >= n)                    continue;
                if (next.y < 0)                     continue;
                if (next.y >= n)                    continue;
                if (grid[next.y][next.x] == 'H')    continue;
                if (grid[next.y][next.x] == 'C')    continue;

                // infect the next cell
                new_frontier[new_frontier_len++] = next;
                grid[next.y][next.x] = 'C';
            }
        }
        // update the new frontier
        cp_frontier(new_frontier, new_frontier_len, frontier);
        frontier_len = new_frontier_len;
    }

    // check if it has more infected people than all the previous
    if (infected > *most_infected) {
        *index = current_index;
        *most_infected = infected;

        for (int y = 0; y < n; y++)
            for (int x = 0; x < n; x++)
                final_grid[y][x] = grid[y][x];
    }
}

void cp_frontier(Point src[n * n], int src_len, Point dst[n * n]) {
    for (int i = 0; i < src_len; i++)
        dst[i] = src[i];
}

void print_grid(char grid[n][n]) {
    for (int y = 0; y < n; y++) {
        for (int x = 0; x < n; x++)
            printf("%c", grid[y][x]);
        printf("\n");
    }
}

void print_frontier(Point frontier[n * n], int frontier_len) {
    fprintf(stderr, "[DEBUG] Frontier=[");

    for (int i = 0; i < frontier_len; i++)
        fprintf(stderr, "(%d, %d)", frontier[i].x, frontier[i].y);

    fprintf(stderr, "]\n");
}

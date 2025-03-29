#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct cell {
    int row;
    int col;
    char content;
    bool visited;
} Cell;

int size;
Cell *grid;

void solve();
int bfs(Cell root);
void debug();

int main() {
    scanf("%d", &size);
    fgetc(stdin);

    grid = (Cell *)malloc(sizeof(Cell) * size * size);

    for (int i = 0; i < size; i++) {
        char row[size + 1];
        scanf("%[^\n]", row);
        fgetc(stdin);

        for (int j = 0; j < size; j++) {
            Cell c = {
                .row = i, 
                .col = j, 
                .content = row[j],
                .visited = false
            };
            grid[i * size + j] = c;
        }
    }

    //debug();
    solve();
    free(grid);

    return 0;
}

void solve() {
    int max_coast = 0;
    int max_index = 1;
    int current_index = 0;

    for (int i = 0; i < size * size; i++) {
        if (grid[i].content == '#' && !grid[i].visited) {
            // start an island and the block was not visited
            int coast = bfs(grid[i]);
            current_index++;

            if (coast > max_coast) {
                max_coast = coast;
                max_index = current_index; 
            }
        }
    }
    printf("%d %d\n", max_index, max_coast);
}

int bfs(Cell root) {
    fprintf(stderr, "[DEBUG] Starting BFS\n");

    int coast_length = 0;
    Cell q[size * size];
    int head = 0;
    int tail = 0;
    q[tail] = root;
    tail++;
    grid[root.row * size + root.col].visited = true;

    while (head != tail) { // q is not empty
        Cell current = q[head];

        fprintf(stderr, "[DEBUG] head = %d tail = %d\n", head, tail);
        fprintf(stderr, "[DEBUG] current(%d %d %c)\n", current.row, current.col, current.content);
        head++;

        int next_col = current.col + 1;
        int next_row = current.row;

        if (next_col < size && !grid[next_row * size + next_col].visited) {
            grid[next_row * size + next_col].visited = true;
            if (grid[next_row * size + next_col].content == '#') {
                fprintf(stderr, "[DEBUG] find block 1\n");
                q[tail] = grid[next_row * size + next_col];
                tail++;
            } else {
                fprintf(stderr, "[DEBUG] find water 1\n");
                coast_length++;
            }
        }

        next_col = current.col;
        next_row = current.row + 1;

        if (next_row < size && !grid[next_row * size + next_col].visited) {
            grid[next_row * size + next_col].visited = true;
            if (grid[next_row * size + next_col].content == '#') {
                fprintf(stderr, "[DEBUG] find block 2\n");
                q[tail] = grid[next_row * size + next_col];
                tail++;
            } else {
                fprintf(stderr, "[DEBUG] find water 2\n");
                coast_length++;
            }
        }

        next_col = current.col - 1;
        next_row = current.row;

        if (next_col > -1 && !grid[next_row * size + next_col].visited) {
            grid[next_row * size + next_col].visited = true;
            if (grid[next_row * size + next_col].content == '#') {
                fprintf(stderr, "[DEBUG] find block 3\n");
                q[tail] = grid[next_row * size + next_col];
                tail++;
            } else {
                fprintf(stderr, "[DEBUG] find water 3\n");
                coast_length++;
            }
        }

        next_col = current.col;
        next_row = current.row - 1;

        if (next_row > -1 && !grid[next_row * size + next_col].visited) {
            grid[next_row * size + next_col].visited = true;
            if (grid[next_row * size + next_col].content == '#') {
                fprintf(stderr, "[DEBUG] find block 4\n");
                q[tail] = grid[next_row * size + next_col];
                tail++;
            } else {
                fprintf(stderr, "[DEBUG] find water 4\n");
                coast_length++;
            }
        }
    }

    for (int i = 0; i < size * size; i++) {
        if (grid[i].content == '~') {
            grid[i].visited = false;
        }
    }

    fprintf(stderr, "[DEBUG] Coast length: %d\n", coast_length);
    return coast_length;
}

void debug() {
    fprintf(stderr, "[DEBUG]\n");
    
    for (int i = 0; i < size * size; i++) {
        fprintf(stderr, "(%d %d %c) ", 
            grid[i].row, grid[i].col, grid[i].content);

        if (grid[i].col == size - 1) {
            fprintf(stderr, "\n");
        }
    }
}

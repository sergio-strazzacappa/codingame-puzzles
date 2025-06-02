#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct data {
    int rows;
    int cols;
    char **matrix;
} object, grid;

void init();
void solve();
bool check_object(int x, int y);
void insert_object(int x, int y);
void print_grid();
void clean(struct data d);
void debug(struct data d, char *title);

int main() {
    init();
    solve();
    clean(object);
    clean(grid);

    return 0;
}

void init() {
    // read the object
    scanf("%d%d", &object.rows, &object.cols);
    fgetc(stdin);

    object.matrix = (char **)malloc(sizeof(char *) * object.rows);

    for (int y = 0; y < object.rows; y++) {
        object.matrix[y] = (char *)malloc(sizeof(char) * object.cols);
        scanf("%[^\n]", object.matrix[y]);
        fgetc(stdin);
    }

    // read the grid
    scanf("%d%d", &grid.rows, &grid.cols);
    fgetc(stdin);

    grid.matrix = (char **)malloc(sizeof(char *) * grid.rows);

    for (int y = 0; y < grid.rows; y++) {
        grid.matrix[y] = (char *)malloc(sizeof(char) * grid.cols);
        scanf("%[^\n]", grid.matrix[y]);
        fgetc(stdin);
    }
}

void solve() {
    int solutions = 0;
    int solution_x = -1;
    int solution_y = -1;

    for (int y = 0; y < grid.rows; y++) {
        for (int x = 0; x < grid.cols; x++) {
            bool result = check_object(x, y);

            if (result) {
                solution_x = x;
                solution_y = y;
            }
            solutions += result;
        }
    }

    printf("%d\n", solutions);

    if (solutions == 1) {
        insert_object(solution_x, solution_y);
        print_grid();
    }
}

// returns true of the object can be inserted at position (x, y), otherwise
// returns false
bool check_object(int x, int y) {
    for (int y1 = 0; y1 < object.rows; y1++) {
        for (int x1 = 0; x1 < object.cols; x1++) {
            if (object.matrix[y1][x1] == '*') {
                int pos_x = x + x1;
                int pos_y = y + y1;

                if (pos_x >= grid.cols ||
                    pos_y >= grid.rows ||
                    grid.matrix[pos_y][pos_x] == '#')

                    return false;
            }
        }
    }
    return true;
}

// insert the object at pos (x, y)
void insert_object(int x, int y) {
    for (int y1 = 0; y1 < object.rows; y1++) {
        for (int x1 = 0; x1 < object.cols; x1++) {
            int pos_x = x + x1;
            int pos_y = y + y1;

            if (grid.matrix[pos_y][pos_x] == '.' && object.matrix[y1][x1] == '*')
                grid.matrix[pos_y][pos_x] = '*';
        }
    }
}

void print_grid() {
    for (int y = 0; y < grid.rows; y++) {
        for (int x = 0; x < grid.cols; x++) {
            printf("%c", grid.matrix[y][x]);
        }
        printf("\n");
    }
}

void clean(struct data d) {
    for (int y = 0; y < d.rows; y++)
        free(d.matrix[y]);
    free(d.matrix);
}

void debug(struct data d, char *title) {
    fprintf(stderr, "[DEBUG] %s (%d, %d)\n", title, d.rows, d.cols);

    for (int y = 0; y < d.rows; y++) {
        for (int x = 0; x < d.cols; x++) {
            fprintf(stderr, "%c", d.matrix[y][x]);
        }
        fprintf(stderr, "\n");
    }
}

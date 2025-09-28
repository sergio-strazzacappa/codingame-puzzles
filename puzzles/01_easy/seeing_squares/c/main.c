#include <stdio.h>
#include <stdlib.h>

int rows;
int cols;
char **grid;

void init();
void solve();
int is_square(int x, int y);
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

    grid = (char **)malloc(sizeof(char *) * rows);

    for (int y = 0; y < rows; y++) {
        grid[y] = (char *)malloc(sizeof(char) * cols);

        char *row = (char *)malloc(sizeof(char) * cols);
        scanf("%[^\n]", row);
        fgetc(stdin);

        for (int x = 0; x < cols; x++)
            grid[y][x] = row[x];
    }
}

void solve() {
    int squares = 0;

    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            if (grid[y][x] == '+') {
                // find all the squares of every cell
                squares += is_square(x, y);
            }
        }
    }
    printf("%d\n", squares);
}

int is_square(int x, int y) {
    int squares = 0;
    int yy = y + 1;
    int exit = 1;
    int v_len = 1;

    while (yy < rows) {
        // iterate over every possible square size
        
        exit = 1;

        // calculate the length of a side
        // compute the left side
        for (; yy < rows && exit; yy++) {
            v_len++;
            if (grid[yy][x] == '+')
                exit = 0;
            else if (grid[yy][x] == '|')
                exit = 1;
            else {
                exit = 1;
                break;
            }
        }

        if (exit)
            break;

        int h_len = v_len * 2 - 1;
        int len = h_len;
        int top     = yy - v_len;
        int bottom  = yy - 1;
        exit = 1;

        // compute the top and bottom sides
        for (int xx = x + 1; xx < cols; xx++) {
            if ((grid[top][xx] == '-' && grid[bottom][xx] == '-') ||
                (grid[top][xx] == '-' && grid[bottom][xx] == '+') ||
                (grid[top][xx] == '+' && grid[bottom][xx] == '-'))
                len--;
            else if (grid[top][xx] == '+' && grid[bottom][xx] == '+') {
                len--;
                if (len == 1) {
                    exit = 0;
                    break;
                }
            } else {
                exit = 1;
                break;
            }   
        }

        if (exit || len != 1)
            continue;

        len = v_len;
        // compute the right side
        for (int yyy = y + 1; yyy < rows; yyy++) {
            if (grid[yyy][x + h_len - 1] == '|')
                len--;
            else if (grid[yyy][x + h_len - 1] == '+') {
                len--;
                if (len == 1)
                    break;
            } else {
                exit = 1;
                break;
            }
        }

        if (exit || len > 1)
            continue;

        squares++;
    }

    return squares;
}

void clean() {
    for (int y = 0; y < rows; y++)
        free(grid[y]);
    free(grid);
}

void debug() {
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++)
            fprintf(stderr, "%c", grid[y][x]);
        fprintf(stderr, "\n");
    }
}

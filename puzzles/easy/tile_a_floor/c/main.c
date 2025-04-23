#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int rows;
int cols;
char **pattern;

void read_pattern();
void solve();
char **make_tile();
void format_output(char **tile);
void top_bottom();
void print_tile(char **tile);
void print_pattern();
void free_pattern();

int main() {
    read_pattern();
    solve();
    free_pattern();
    return 0;
}

void read_pattern() {
    scanf("%d", &rows);
    fgetc(stdin);

    // save space for each row
    pattern = (char **)malloc(sizeof(char *) * rows);

    for (int i = 0; i < rows; i++) {
        char row[8];

        scanf("%[^\n]", row);
        fgetc(stdin);

        if (i == 0)
            cols = strlen(row);

        // save space of each element
        pattern[i] = (char *)malloc(sizeof(char) * cols);

        strcpy(pattern[i], row);
    }
}

void solve() {
    char **tile = make_tile();

    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            switch (tile[y][x]) {
                case '(':
                    tile[y][cols * 2 - x - 2] = ')';
                    tile[rows * 2 - y - 2][cols * 2 - x - 2] = ')';
                    break;
                case ')':
                    tile[y][cols * 2 - x - 2] = '(';
                    tile[rows * 2 - y - 2][cols * 2 - x - 2] = '(';
                    break;
                case '{':
                    tile[y][cols * 2 - x - 2] = '}';
                    tile[rows * 2 - y - 2][cols * 2 - x - 2] = '}';
                    break;
                case '}':
                    tile[y][cols * 2 - x - 2] = '{';
                    tile[rows * 2 - y - 2][cols * 2 - x - 2] = '{';
                    break;
                case '[':
                    tile[y][cols * 2 - x - 2] = ']';
                    tile[rows * 2 - y - 2][cols * 2 - x - 2] = ']';
                    break;
                case ']':
                    tile[y][cols * 2 - x - 2] = '[';
                    tile[rows * 2 - y - 2][cols * 2 - x - 2] = '[';
                    break;
                case '<':
                    tile[y][cols * 2 - x - 2] = '>';
                    tile[rows * 2 - y - 2][cols * 2 - x - 2] = '>';
                    break;
                case '>':
                    tile[y][cols * 2 - x - 2] = '<';
                    tile[rows * 2 - y - 2][cols * 2 - x - 2] = '<';
                    break;
                case '^':
                    tile[rows * 2 - y - 2][x] = 'v';
                    tile[rows * 2 - y - 2][cols * 2 - x - 2] = 'v';
                    break;
                case 'v':
                    tile[rows * 2 - y - 2][x] = '^';
                    tile[rows * 2 - y - 2][cols * 2 - x - 2] = '^';
                    break;
                case 'A':
                    tile[rows * 2 - y - 2][x] = 'V';
                    tile[rows * 2 - y - 2][cols * 2 - x - 2] = 'V';
                    break;
                case 'V':
                    tile[rows * 2 - y - 2][x] = 'A';
                    tile[rows * 2 - y - 2][cols * 2 - x - 2] = 'A';
                    break;
                case 'w':
                    tile[rows * 2 - y - 2][x] = 'm';
                    tile[rows * 2 - y - 2][cols * 2 - x - 2] = 'm';
                    break;
                case 'm':
                    tile[rows * 2 - y - 2][x] = 'w';
                    tile[rows * 2 - y - 2][cols * 2 - x - 2] = 'w';
                    break;
                case 'W':
                    tile[rows * 2 - y - 2][x] = 'M';
                    tile[rows * 2 - y - 2][cols * 2 - x - 2] = 'M';
                    break;
                case 'M':
                    tile[rows * 2 - y - 2][x] = 'W';
                    tile[rows * 2 - y - 2][cols * 2 - x - 2] = 'W';
                    break;
                case 'u':
                    tile[rows * 2 - y - 2][x] = 'n';
                    tile[rows * 2 - y - 2][cols * 2 - x - 2] = 'n';
                    break;
                case 'n':
                    tile[rows * 2 - y - 2][x] = 'u';
                    tile[rows * 2 - y - 2][cols * 2 - x - 2] = 'u';
                    break;
                case '/':
                    tile[y][cols * 2 - x - 2] = '\\';
                    tile[rows * 2 - y - 2][x] = '\\';
                    break;
                case '\\':
                    tile[y][cols * 2 - x - 2] = '/';
                    tile[rows * 2 - y - 2][x] = '/';
                    break;
            }
        }
    }

    format_output(tile);
}

char **make_tile() {
    char **tile = (char **)malloc(sizeof(char*) * (rows * 2 - 1));

    for (int y = 0; y < rows * 2 - 1; y++)
        tile[y] = (char *)malloc(sizeof(char) * (cols * 2 - 1));

    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            tile[y][x] = pattern[y][x];

            if (x != cols - 1)
                tile[y][cols * 2 - x - 2] = pattern[y][x];

            if (y != rows - 1) {
                tile[rows * 2 - y - 2][x] = pattern[y][x];

                if (x != cols - 1) {
                    tile[rows * 2 - y - 2][cols * 2 - x - 2] = pattern[y][x];
                }
            }
        }
    }

    return tile;
}

void format_output(char **tile) {
    top_bottom();
    print_tile(tile);
    top_bottom();
}

void top_bottom() {
    printf("+");

    for (int i = 0; i < cols * 2 - 1; i++)
        printf("-");

    printf("+");

    for (int i = 0; i < cols * 2 - 1; i++)
        printf("-");

    printf("+\n");
}

void print_tile(char **tile) {
    for (int y = 0; y < rows * 2 - 1; y++) {
        printf("|%s|", tile[y]);

        printf("%s|\n", tile[y]);
    }

    top_bottom();

    for (int y = 0; y < rows * 2 - 1; y++) {
        printf("|%s|", tile[y]);
        printf("%s|\n", tile[y]);
    }
}

void print_pattern() {
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            fprintf(stderr, "%c", pattern[y][x]);
        }
        fprintf(stderr, "\n");
    }
}

void free_pattern() {
    for (int y = 0; y < rows; y++)
        free(pattern[y]);
    free(pattern);
}

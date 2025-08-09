#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

int rows;
int cols;
char **city;

void init();
void solve();
int get_int(char c);
char get_char(int i);
int distance(int x1, int y1, int x2, int y2);
void clean();
void debug();

int main() {
    init();
    solve();
    clean();

    return 0;
}

void init() {
    scanf("%d%d%*c", &rows, &cols);
    city = (char **)malloc(sizeof(char *) * rows);

    for (int y = 0; y < rows; y++) {
        char s[cols + 1];
        scanf("%[^\n]%*c", s);
        city[y] = (char *)malloc(sizeof(char) * cols);

        for (int x = 0; x < cols; x++)
            city[y][x] = s[x];
    }
}

void solve() {
    char light[rows][cols];

    for (int y = 0; y < rows; y++)
        for (int x = 0; x < cols; x++)
            light[y][x] = '0';

    for (int y1 = 0; y1 < rows; y1++) {
        for (int x1 = 0; x1 < cols; x1++) {
            if (city[y1][x1] == '.')
                continue;

            int radius = get_int(city[y1][x1]);

            for (int y2 = 0; y2 < rows; y2++) {
                for (int x2 = 0; x2 < cols; x2++) {
                    int brightness = radius - distance(x1, y1, x2, y2);

                    if (brightness > 0) {
                        int value = get_int(light[y2][x2]);
                        value += brightness;

                        if (value < 0)
                            value = 0;
                        else if (value > 35)
                            value = 35;

                        light[y2][x2] = get_char(value); 
                    }
                }
            }
        }
    }
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++)
            printf("%c", light[y][x]);
        printf("\n");
    }
}

int get_int(char c) {
    if (isdigit(c))
        return c - '0';
    return c + 10 - 'A';
}

char get_char(int i) {
    if (i < 10)
        return i + '0';
    return i - 10 + 'A';
}

int distance(int x1, int y1, int x2, int y2) {
    return round(sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)));
}

void clean() {
    for (int y = 0; y < rows; y++)
        free(city[y]);
    free(city);
}

void debug() {
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++)
            fprintf(stderr, "%c", city[y][x]);
        fprintf(stderr, "\n");
    }
}

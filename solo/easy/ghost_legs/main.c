#include <stdio.h>
#include <string.h>
#define MAX_WIDTH 100
#define MAX_HEIGHT 100

char top[MAX_WIDTH];
char bottom[MAX_HEIGHT];
char map[MAX_HEIGHT - 2][MAX_WIDTH];

int search(int start, int w, int h) {
    int current_line = start;
    int depth = 0;

    while (depth < (h - 2)) {
        if (current_line == 0) {
            if (map[depth][current_line + 1] == '-') {
                current_line += 3;
            }
        } else if (current_line == w) {
            if (map[depth][current_line - 1] == '-') {
                current_line -= 3;
            }
        } else {
            if (map[depth][current_line - 1] == '-') {
                current_line -= 3;
            } else if (map[depth][current_line + 1] == '-') {
                current_line += 3;
            }
        }
        depth++;
    }
    return current_line;
}

void solve(int w, int h) {
    for (int i = 0; i < w; i++) {
        if (top[i] != ' ') {
            printf("%c%c\n", top[i], bottom[search(i,  w, h)]);
        }
    }
}

int main() {
    int w, h;
    scanf("%d%d", &w, &h);
    fgetc(stdin);

    for (int i = 0; i < h; i++) {
        char row[1025];
        scanf("%[^\n]", row);
        fgetc(stdin);

        for (int j = 0; j < w; j++) {
            if (i == 0) {
                top[j] = row[j];
            } else if (i == h - 1) {
                bottom[j] = row[j];
            } else {
                map[i - 1][j] = row[j];
            }
        }
    }

    solve(w, h);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

typedef struct point {
    int x;
    int y;
} Point;

int width;
int height;
Point start;
int n;
char *map;

int solve();
void print_maps();

int main() {
    scanf("%d%d%d%d%d", &width, &height, &start.y, &start.x, &n);
    fgetc(stdin);

    map = (char *)malloc(n * height * width * sizeof(char));

    int offset = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < height; j++) {
            char map_row[width + 1];
            scanf("%[^\n]", map_row);
            fgetc(stdin);
            for (int k = 0; k < width; k++) {
                *(map + offset) = map_row[k];
                offset++;
            }
        }
    }

    int solution = solve();

    if (solution == -1)
        printf("TRAP\n");
    else
        printf("%d\n", solution);

    return 0;
}

int solve() {
    int shortest_path = INT_MAX;
    int index = -1;

    for (int i = 0; i < n; i++) {
        Point current = start;
        int path = 0;
        int treasure = 0;
        int trap = 0;

        while (1) {
            int cell = i * height * width + current.y * width + current.x;
            path++;

            if (treasure && path < shortest_path) {
                shortest_path = path;
                index = i;
            }
            
            if (treasure || trap)
                break;

            switch (*(map + cell)) {
                case '^': 
                    current.y--;
                    break;
                case 'v':
                    current.y++;
                    break;
                case '<':
                    current.x--;
                    break;
                case '>':
                    current.x++;
                    break;
                case 'T':
                    treasure = 1;
                    break;
                default:
                    trap = 1; 
                    break;
            }

            *(map + cell) = '.';
        }
    }
    return index;
}

void print_maps() {
    int offset = 0;
    for (int i = 0; i < n; i++) {
        printf("MAP N°%d\n", i + 1);
        for (int j = 0; j < height; j++) {
            for (int k = 0; k < width; k++) {
                printf("%c", *(map + offset));
                offset++;
            }
            printf("\n");
        }
    }
}

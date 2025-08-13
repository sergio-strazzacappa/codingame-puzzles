#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define INDEX   (z * width * length) + (y * length) + x
#define SIZE    (depth * width * length)

/*
 * representation of the map
 * [depth][width][length]
 * [z][y][x]
 */

typedef struct Point {
    int x;
    int y;
    int z;
    int brightness;
} Point;

int length;
int width;
int depth;
int n;
Point *map;

void init();
void solve();
void fmt_output();
float distance(Point p, Point q);
void clean();
void debug();

int main() {

    init();
    solve();
    fmt_output();
    clean();

    return 0;
}

void init() {
    scanf("%d%d%d%d", &length, &width, &depth, &n);
    fgetc(stdin);

    map = (Point *)malloc(sizeof(Point) * SIZE);

    // set the coordinates of every cell and its light to 0
    for (int z = 0; z < depth; z++) {
        for (int y = 0; y < width; y++) {
            for (int x = 0; x < length; x++) {
                Point p = {x, y, z, 0};
                map[INDEX] = p;
            }
        }
    }
}

void solve() {
    int x = 0;
    int y = 0;
    int z = 0;

    for (int i = 0; i < n; i++) {
        char s[21] = "";
        scanf("%[^\n]", s);
        fgetc(stdin);

        if (strcmp(s, "") == 0) {
            // next depth
            y = -1;
            z++;
        }

        for (x = 0; x < strlen(s); x++) {
            int radius = 0;

            if (s[x] == '.')
                // no light source, go to the next cell
                continue;

            // transform char to int
            if (s[x] <= '9')
                radius = s[x] - '0';
            else
                radius = s[x] - 'A' + 10;

            Point p = {
                .x          = x,
                .y          = y,
                .z          = z,
                .brightness = radius
            };

            for (int i = 0; i < SIZE; i++) {
                int brightness = p.brightness - round(distance(map[i], p));

                if (brightness < 0)
                    // if brightness is negative it is still 0
                    brightness = 0;

                map[i].brightness += brightness;

                if (map[i].brightness > 35)
                    // brightness is greater than Z it is set to Z
                    map[i].brightness = 35;
            }
        }
        y++;
    }
}

// format the output
void fmt_output() {
    for (int i = 0; i < SIZE; i++) {
        Point cell = map[i];

        // transform int to char
        if (cell.brightness <= 9)
            printf("%c", cell.brightness + '0');
        else
            printf("%c", cell.brightness - 10 + 'A');

        if (cell.x == length - 1) {
            // newline at the end of y-axis
            printf("\n");
            if (cell.y == width - 1 && cell.z != depth - 1) {
                // newline at the end of z-axis
                printf("\n");
            }
        }
    }
}

// compute the euclidean distance in 3D
float distance(Point p, Point q) {
    return sqrt(pow(p.x - q.x, 2) + pow(p.y - q.y, 2) + pow(p.z - q.z, 2));
}

void clean() {
    free(map);
}

void debug() {
    for (int i = 0; i < SIZE; i++)
        fprintf(stderr, "[DEBUG] {(%d, %d, %d), %d}\n",
            map[i].x, map[i].y, map[i].z, map[i].brightness);
}

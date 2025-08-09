#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct point {
    char id;
    int x;
    int y;
} Point;

int cols;
int rows;
int times[3];
char **picture1;
char **picture2;

void init();
void solve();
void clean();
void print_picture(char **picture);

int main() {
    init();
    solve();
    clean();

    return 0;
}

void init() {
    scanf("%d%d%d%d%d", &cols, &rows, &times[0], &times[1], &times[2]);

    picture1 = (char **)malloc(sizeof(char*) * rows);
    picture2 = (char **)malloc(sizeof(char*) * rows);

    for (int y = 0; y < rows; y++) {
        char first_picture_row[cols];
        char second_picture_row[cols];

        scanf("%s", first_picture_row);
        fgetc(stdin);
        scanf("%s", second_picture_row);

        picture1[y] = (char *)malloc(sizeof(char) * cols);
        picture2[y] = (char *)malloc(sizeof(char) * cols);

        for (int x = 0; x < cols; x++) {
            picture1[y][x] = first_picture_row[x];
            picture2[y][x] = second_picture_row[x];
        }
    }
}

void solve() {
    // each obs is an array for each letter it has (-1, -1, -1) if that asteroid
    // is not present, when it is found set the values to (x, y, letter)
    Point *obs1, *obs2, *obs3;

    obs1 = (Point *)malloc(sizeof(Point) * 26);
    obs2 = (Point *)malloc(sizeof(Point) * 26);
    obs3 = (Point *)malloc(sizeof(Point) * 26);

    for (int i = 0; i < 26; i++) {
        obs1[i] = (Point){ -1, -1, -1 };
        obs2[i] = (Point){ -1, -1, -1 };
        obs3[i] = (Point){ -1, -1, -1 };
    }
    
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            // get the starting coordinates of each asteroid
            char id1 = picture1[y][x];

            if (id1 != '.') {
                Point p = { id1, x, y };
                obs1[id1 - 65] = p;
            }

            // get the final coordinates of each asteriod
            char id2 = picture2[y][x];
            
            if (id2 != '.') {
                Point p = { id2, x, y };
                obs2[id2 - 65] = p;
            }
        }
    }

    float proportion = ((float)times[2] - times[1]) / (times[1] - times[0]);

    // calculate new coordinates
    for (int i = 0; i < 26; i++) {
        int id = obs1[i].id;
        float x, y;

        if (obs1[i].x == obs2[i].x)
            x = obs1[i].x;
        else if (obs1[i].x < obs2[i].x)
            x = obs2[i].x + (obs2[i].x - obs1[i].x) * proportion;
        else
            x = obs2[i].x - (obs1[i].x - obs2[i].x) * proportion;

        if (obs1[i].y == obs2[i].y)
            y = obs1[i].y;
        else if (obs1[i].y < obs2[i].y)
            y = obs2[i].y + (obs2[i].y - obs1[i].y) * proportion;
        else
            y = obs2[i].y - (obs1[i].y - obs2[i].y) * proportion;

        Point p = { id, floor(x), floor(y) };
        obs3[p.id - 65] = p;
    }

    int asteroid_found = 0;
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            asteroid_found = 0;
            for (int i = 0; i < 26; i++) {
                if (obs3[i].x == x && obs3[i].y == y) {
                    printf("%c", obs3[i].id);
                    asteroid_found = 1;
                    break;
                }
            }
            if (!asteroid_found)
                printf(".");
        }
        printf("\n");
    }
}

void clean() {
    for (int y = 0; y < rows; y++) {
        free(picture1[y]);
        free(picture2[y]);
    }

    free(picture1);
    free(picture2);
}

void print_picture(char **picture) {
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            fprintf(stderr, "%c", picture[y][x]);
        }
        fprintf(stderr, "\n");
    }
}

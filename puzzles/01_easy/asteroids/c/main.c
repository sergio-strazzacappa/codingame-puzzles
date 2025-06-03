#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct point {
    char id;
    int x;
    int y;
} Point;

int w;
int h;
int times[3];
char* picture1;
char* picture2;

Point *solve();
void print_picture(char* picture, int h, int w);

int main() {
    scanf("%d%d%d%d%d", &w, &h, &times[0], &times[1], &times[2]);

    picture1 = (char *)malloc((h * w) * sizeof(char));
    picture2 = (char *)malloc((h * w) * sizeof(char));

    for (int i = 0; i < h; i++) {
        char first_picture_row[w];
        char second_picture_row[w];

        scanf("%s", first_picture_row);
        fgetc(stdin);
        scanf("%s", second_picture_row);

        for (int j = 0; j < w; j++) {
            picture1[i * w + j] = first_picture_row[j];
            picture2[i * w + j] = second_picture_row[j];
        }
    }

    Point *solution = solve();

    int asteroid_found = 0;

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            asteroid_found = 0;
            for (int k = 0; k < 26; k++) {
                if (solution[k].x == j && solution[k].y == i) {
                    printf("%c", solution[k].id);
                    asteroid_found = 1;
                    break;
                }
            }
            if (!asteroid_found) {
                printf(".");
            }
        }
        printf("\n");
    }

    return 0;
}

Point *solve() {
    Point *obs1, *obs2, *obs3;

    obs1 = (Point *)malloc(sizeof(Point) * 26);
    obs2 = (Point *)malloc(sizeof(Point) * 26);
    obs3 = (Point *)malloc(sizeof(Point) * 26);

    for (int i = 0; i < 26; i++) {
        obs1[i] = (Point){ -1, -1, -1 };
        obs2[i] = (Point){ -1, -1, -1 };
        obs3[i] = (Point){ -1, -1, -1 };
    }
    
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            // get the starting coordinates of each asteroid
            char id1 = picture1[i * w + j];

            if (id1 != '.') {
                Point p = { id1, j, i };
                obs1[id1 - 65] = p;
            }

            // get the final coordinates of each asterios
            char id2 = picture2[i * w + j];
            
            if (id2 != '.') {
                Point p = { id2, j, i };
                obs2[id2 - 65] = p;
            }
        }
    }

    float proportion = ((float)times[2] - times[1]) / (times[1] - times[0]);

    // calculate new coordinates
    for (int i = 0; i < 26; i++) {
        int id = obs1[i].id;
        float x, y;

        if (obs1[i].x == obs2[i].x) {
            x = obs1[i].x;
        } else if (obs1[i].x < obs2[i].x) {
            x = obs2[i].x + (obs2[i].x - obs1[i].x) * proportion;
        } else {
            x = obs2[i].x - (obs1[i].x - obs2[i].x) * proportion;
        }

        if (obs1[i].y == obs2[i].y) {
            y = obs1[i].y;
        } else if (obs1[i].y < obs2[i].y) {
            y = obs2[i].y + (obs2[i].y - obs1[i].y) * proportion;
        } else {
            y = obs2[i].y - (obs1[i].y - obs2[i].y) * proportion;
        }

        Point p = { id, floor(x), floor(y) };
        obs3[p.id - 65] = p;
    }

    return obs3;
}

void print_picture(char* picture, int h, int w) {
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            printf("%c", picture[i * w + j]);
        }
        printf("\n");
    }
}

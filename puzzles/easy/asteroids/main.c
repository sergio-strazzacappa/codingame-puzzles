#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void debug(char* picture, int h, int w);

struct Point {
    char id;
    int x;
    int y;
};

char* picture1;
char* picture2;

int main() {
    int w, h;
    int times[3];

    scanf("%d%d%d%d%d", &w, &h, &times[0], &times[1], &times[2]);

    picture1 = malloc((h * w) * sizeof(char));
    picture2 = malloc((h * w) * sizeof(char));

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

    debug(picture1, h, w);
    debug(picture2, h, w);

    struct Point obs1[26];
    struct Point obs2[26];
    struct Point obs3[26];

    for (int i = 0; i < 26; i++) {
        struct Point p;
        obs1[i] = p;
        obs2[i] = p;
        obs3[i] = p;
    }

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            // Get the starting coordinates of each asteroid
            char id1 = picture1[i * w + j];
            if (id1 != '.') {
                struct Point p = { id1, j, i };
                obs1[id1 - 65] = p;
            }
            // Get the final coordinates of each asteroid
            char id2 = picture2[i * w + j];
            if (id2 != '.') {
                struct Point p = { id2, j, i };
                obs2[id2 - 65] = p;
            }
        }
    }

    float proportion = ((float)times[2] - times[1]) / (times[1] - times[0]);

    fprintf(stderr, "Proportion = %.2f\n", proportion);

    // Calculate new coordinates
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

        struct Point p = {id, floor(x), floor(y)};
        obs3[p.id - 65] = p;
    }

    for (int i = 0; i < 26; i++) {
        fprintf(stderr, "%c: (%d, %d)\n", obs1[i].id, obs1[i].x, obs1[i].y);
    }

    int asteroid_found = 0;

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            asteroid_found = 0;
            for (int k = 0; k < 26; k++) {
                if (obs3[k].x == j && obs3[k].y == i) {
                    printf("%c", obs3[k].id);
                    asteroid_found = 1;
                    break;
                }
            }
            if (!asteroid_found) printf(".");
        }
        printf("\n");
    } 

    free(picture1);
    free(picture2);

    return 0;
}

void debug(char* picture, int h, int w) {
    fprintf(stderr, "[DEBUG]\b");
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            fprintf(stderr, "%c", picture[i * w + j]);
        }
        fprintf(stderr, "\n");
    }
}
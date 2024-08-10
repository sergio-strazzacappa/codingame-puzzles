#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define NUMBER_VERTICES 3

typedef struct Point {
    int x;
    int y;
} point;

char* grid;

void print_grid(int hi, int wi) {
    for (int i = 0; i < hi; i++) {
        for (int j = 0; j < wi; j++) {
            fprintf(stderr, "%c", grid[(i * wi) + j]);
        }
        fprintf(stderr, "\n");
    }
}

float area(point a, point b, point c) {
    return 
        abs((a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y))) / 2.0;
}

void fill_grid(int hi, int wi, point triangle[3]) {
    point a = triangle[0];
    point b = triangle[1];
    point c = triangle[2];

    float A = area(a, b, c);

    fprintf(stderr, "Points: (%d, %d) - (%d, %d) - (%d, %d)\n", a.x, a.y, b.x, b.y, c.x, c.y);
    fprintf(stderr, "Area: %.2f\n", A);

    for (int i = 0; i < hi; i++) {
        for (int j = 0; j < wi; j++) {
            point p;
            p.x = j;
            p.y = i;

            float A1 = area(p, b, c);
            float A2 = area(p, a, c);
            float A3 = area(p, a, b);

            if (A == A1 + A2 + A3) { // the point is in the triangle
                if (grid[(i * wi) + j] == '*')  grid[(i * wi) + j] = ' ';
                else                            grid[(i * wi) + j] = '*';
            } else {
                if (grid[(i * wi) + j] != ' ') {
                    grid[(i * wi) + j] = '*';
                }
            }
        }
    }
}

void solve(char* style, int hi, int wi, point triangles[][NUMBER_VERTICES], int n) {
    grid = malloc(hi * wi * sizeof(char));

    for (int i = 0; i < hi; i++) {
        for (int j = 0; j < wi; j++) {
            grid[(i * wi) + j] = '*';
        }
    }

    for (int i = 0; i < n; i++) {
        fill_grid(hi, wi, triangles[i]);
    }

    for (int i = 0; i < hi; i++) {
        for (int j = 0; j < wi; j++) {
            printf("%c", grid[(i * wi) + j]); 
            if (strcmp(style, "expanded") == 0 && j != wi - 1) {
                printf(" ");
            }
        }
        printf("\n");
    }

    //print_grid(hi, wi);
    free(grid);
}

int main() {
    int hi, wi, how_many_triangles;
    char style[21];

    scanf("%d%d", &hi, &wi);
    fgetc(stdin);
    scanf("%[^\n]", style);
    scanf("%d", &how_many_triangles);

    point triangles[how_many_triangles][NUMBER_VERTICES];

    for (int i = 0; i < how_many_triangles; i++) {
        int x_1, y_1, x_2, y_2, x_3, y_3;
        scanf("%d%d%d%d%d%d", &x_1, &y_1, &x_2, &y_2, &x_3, &y_3);

        triangles[i][0].x = x_1;
        triangles[i][0].y = y_1;
        triangles[i][1].x = x_2;
        triangles[i][1].y = y_2;
        triangles[i][2].x = x_3;
        triangles[i][2].y = y_3;
    }

    solve(style, hi, wi, triangles, how_many_triangles);

    return 0;
}
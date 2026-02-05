#include <stdio.h>
#include <stdlib.h>

typedef struct Vector {
    int velocity;
    int elegance;
} Vector;

void solve();
unsigned int distance(Vector v1, Vector v2);
void debug(Vector horses[], int n);

int main() {
    int n;
    Vector *horses;
    scanf("%d", &n);

    horses = (Vector*)malloc(sizeof(Vector) * n);

    for (int i = 0; i < n; i++) {
        int velocity, elegance;
        scanf("%d%d", &velocity, &elegance);

        Vector v = {velocity, elegance};
        horses[i] = v;
    }

    debug(horses, n);
    solve(horses, n);

    free(horses);

    return 0;
}

void solve(Vector horses[], int n) {
    int *distances = (int *)malloc(sizeof(int) * n * n);
    int index = 0;

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            unsigned int d = distance(horses[i], horses[j]);
            distances[index++] = d;
        }
    }

    unsigned int min = distances[0];

    for (int i = 1; i < index; i++) {
        if (min == 0) {
            fprintf(stderr, "[DEBUG] min is 0, early break\n");
            break;
        }

        if (distances[i] < min) {
            min = distances[i];
        }
    }
    printf("%d\n", min);
    free(distances);
}

unsigned int distance(Vector v1, Vector v2) {
    return (abs((int)v1.velocity - v2.velocity) + abs(v1.elegance - v2.elegance));
}

void debug(Vector horses[], int n) {
    fprintf(stderr, "Number of horses:%d\n", n);
    fprintf(stderr, "[\n");

    for (int i = 0; i < n; i++) {
        fprintf(stderr, "\t(%d, %d)\n", horses[i].velocity, horses[i].elegance);
    }
    fprintf(stderr, "]\n");
}

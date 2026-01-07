#include <stdio.h>
#include <stdlib.h>

struct vector {
    int velocity;
    int elegance;
}; 

int n;
struct vector *horses;
unsigned int *distances;

void init();
unsigned int distance(struct vector v1, struct vector v2);
void solve();
void debug();

int main() {
    init();
    debug();
    solve();
    free(horses);

    return 0;
}

void init() {
    scanf("%d", &n);

    horses = (struct vector*)malloc(sizeof(struct vector) * n);

    for (int i = 0; i < n; i++) {
        int velocity, elegance;
        scanf("%d%d", &velocity, &elegance);

        struct vector v = {velocity, elegance};
        horses[i] = v;
    }
}

void solve() {
    distances = (unsigned int *)malloc(sizeof(unsigned int) * n * n);
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

unsigned int distance(struct vector v1, struct vector v2) {
    return (abs((int)v1.velocity - v2.velocity) + abs(v1.elegance - v2.elegance));
}

void debug() {
    fprintf(stderr, "Number of horses:%d\n", n);
    fprintf(stderr, "[\n");
    
    for (int i = 0; i < n; i++) {
        fprintf(stderr, "\t(%d, %d)\n", horses[i].velocity, horses[i].elegance);
    }
    fprintf(stderr, "]\n");
}

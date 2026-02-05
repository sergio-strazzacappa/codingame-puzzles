#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_HORSES 100000

typedef struct Horse {
    int velocity;
    int elegance;
} Horse;

void lcg(Horse horses[], int congruential_h, int seed);
void solve(Horse horses[], size_t size);
long distance(Horse h1, Horse h2);
int cmp(const void *a, const void *b);
void debug(Horse horses[], size_t size);

int main() {
    int natural_h;
    int congruential_h;
    int seed;

    scanf("%d%d%d", &natural_h, &congruential_h, &seed);

    Horse horses[MAX_HORSES];
    lcg(horses, congruential_h, seed);

    for (int i = 0; i < natural_h; i++) {
        Horse h;
        scanf("%d%d", &h.velocity, &h.elegance);

        horses[congruential_h + i] = h;
    }

    qsort(horses, natural_h + congruential_h, sizeof(Horse), cmp);
    solve(horses, natural_h + congruential_h);

    return 0;
}

void lcg(Horse horses[], int congruential_h, int seed) {
    for (int i = 0; i < congruential_h; i++) {
        Horse h;
        h.velocity = seed;
        seed = ((long)1103515245 * (long)seed + 12345) % (long)pow(2, 31);
        h.elegance = seed;

        horses[i] = h;

        seed = ((long)1103515245 * (long)seed + 12345) % (long)pow(2, 31);
    }
}

int cmp(const void *a, const void *b) {
    Horse *h1 = (Horse *)a;
    Horse *h2 = (Horse *)b;

    return h1->velocity - h2->velocity;
}

void solve(Horse horses[], size_t size) {
    long min_distance = LONG_MAX;
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            int dv = horses[j].velocity - horses[i].velocity;

            // since the horses are sorted by velocity, if the delta is already
            // greater than the min_distance break the inner loop. The distance
            // to remaining horses will be greater than min_distance
            if (dv >= min_distance)
                break;

            long d = distance(horses[i], horses[j]);
            if (d < min_distance) {
                min_distance = d;
            }
        }
    }

    printf("%ld\n", min_distance);
}

long distance(Horse h1, Horse h2) {
    return (long)abs(h2.velocity - h1.velocity) + (long)abs(h2.elegance - h1.elegance);
}

void debug(Horse horses[], size_t size) {
    for (int i = 0; i < size; i++) {
        Horse h = horses[i];
        fprintf(stderr, "[DEBUG] (%d, %d)\n", h.velocity, h.elegance);
    }
}

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

typedef struct sphere {
    int x;
    int y;
    int z;
    float r;
} Sphere;

int n;
Sphere *spheres;

void solve();
void expand(int index);
void print_spheres();

int main() {
    scanf("%d", &n);

    spheres = (Sphere *)malloc(sizeof(Sphere) * n);

    for (int i = 0; i < n; i++) {
        Sphere s;
        scanf("%d%d%d%f", &s.x, &s.y, &s.z, &s.r);
        spheres[i] = s;
    }

    solve();
    free(spheres);

    return 0;
}

void solve() {
    float r = 0;

    for (int i = 0; i < n; i++) {
        expand(i);
        r += pow(spheres[i].r, 3);
    }

    printf("%.0f\n", r);
}

void expand(int index) {
    Sphere current = spheres[index];
    float min_r = (float)INT_MAX;

    /*
     * From the current sphere calculate:
     * 1. The distance between the center and the center of each other sphere
     * 2. If the sum of both radius are lower then expand the radius until
     *      they overlap
     * 3. Then set the radius of the current sphere to the distance to the
     *      closest sphere
     */

    for (int i = 0; i < n; i++) {
        if (i == index)
            continue;

        Sphere s = spheres[i];

        float distance = sqrt(
            pow((current.x - s.x), 2) + 
            pow((current.y - s.y), 2) +
            pow((current.z - s.z), 2));

        float radius_sum = current.r + s.r; 
        float radius_expansion = current.r;

        if (radius_sum < distance)
            radius_expansion = distance - s.r;

        if (radius_expansion < min_r)
            min_r = radius_expansion;
    } 

    if (min_r < (float)INT_MAX)
        spheres[index].r = min_r;
}

void print_spheres() {
    fprintf(stderr, "------------------------------\n");
    for (int i = 0; i < n; i++) {
        Sphere s = spheres[i];
        fprintf(stderr, "[DEBUG] (%d, %d, %d) r:%0.2f\n", s.x, s.y, s.z, s.r);
    }
    fprintf(stderr, "------------------------------\n");
}

#include <stdio.h>
#include <math.h>

#define PI 3.14159265359

float side;
float diameter;

void solve();
int wasteful();
int frugal();

int main() {
    scanf("%f%f", &side, &diameter);
    solve();

    return 0;
}

void solve() {
    printf("%d\n", frugal() - wasteful());
}

int wasteful() {
    return pow((int)(side / diameter), 2);
}

int frugal() {
    int n = 0;
    float current_side = side;

    while (current_side >= diameter) {
        n += pow((int)(current_side / diameter), 2);
        float square_area = side * side;
        float circle_area = PI * pow((diameter / 2), 2);
        current_side = sqrt(square_area - circle_area * n);
    }

    return n;
}

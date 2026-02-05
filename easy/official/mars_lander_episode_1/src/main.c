#include <stdio.h>
#include <stdbool.h>

#define MAX_V_SPEED 39

typedef struct Spaceship {
    int x;
    int y;
    int h_speed;
    int v_speed;
    int fuel;
    int rotate;
    int power;
} Spaceship;

void solve();

int main() {
    int surface_n;
    scanf("%d", &surface_n);

    for (int i = 0; i < surface_n; i++) {
        // omit for the 1st level
        int land_x;
        int land_y;
        scanf("%d%d", &land_x, &land_y);
    }

    solve();

    return 0;
}

void solve() {
    Spaceship mars_lander;

    while (true) {
        scanf("%d%d%d%d%d%d%d",
            &mars_lander.x, &mars_lander.y, &mars_lander.h_speed,
            &mars_lander.v_speed, &mars_lander.fuel, &mars_lander.rotate,
            &mars_lander.power);

        if (mars_lander.v_speed < -(MAX_V_SPEED))
            mars_lander.power = 4;
        else
            mars_lander.power = 0;

        printf("0 %d\n", mars_lander.power);
    }
}

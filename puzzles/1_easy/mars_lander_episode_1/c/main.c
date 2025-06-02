#include <stdio.h>

#define MAX_V_SPEED 39

int surface_n;

struct mars_lander {
    int x;
    int y;
    int h_speed;
    int v_speed;
    int fuel;
    int rotate;
    int power;
} m;

void solve();

int main() {
    scanf("%d", &surface_n);

    for (int i = 0; i < surface_n; i++) {
        // omit for the 1st level
        int land_x;
        int land_y;
        scanf("%d%d", &land_x, &land_y);
    }

    while (1)
        solve();

    return 0;
}

void solve() {
    scanf("%d%d%d%d%d%d%d",
        &m.x, &m.y, &m.h_speed, &m.v_speed, &m.fuel, &m.rotate, &m.power);

        if (m.v_speed < -(MAX_V_SPEED))
            m.power = 4;
        else
            m.power = 0;

        printf("0 %d\n", m.power);
}

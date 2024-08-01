#include <stdio.h>

int main() {
    int surface_n;
    scanf("%d", &surface_n);

    for (int i = 0; i < surface_n; i++) {
        int land_x;
        int land_y;
        scanf("%d%d", &land_x, &land_y);
    }

    while (1) {
        int x;
        int y;
        int h_speed;
        int v_speed;
        int fuel;
        int rotate;
        int power;
        scanf("%d%d%d%d%d%d%d", &x, &y, &h_speed, &v_speed, &fuel, &rotate, &power);

        if (v_speed < -39) {
            power = 4;
        } else {
            power = 0;
        }
        printf("0 %d\n", power);
    }
    return 0;
}
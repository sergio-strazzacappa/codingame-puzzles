#include <stdio.h>

int main() {
    while (1) {
        int highest_peak = 0;
        int highest_index = 0;

        for (int i = 0; i < 8; i++) {
            int mountain_h;
            scanf("%d", &mountain_h);

            if (mountain_h > highest_peak) {
                highest_peak = mountain_h;
                highest_index = i;
            }
        }
        printf("%d\n", highest_index);
    }
    return 0;
}
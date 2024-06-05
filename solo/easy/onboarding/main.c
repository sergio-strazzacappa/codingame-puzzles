#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main () {
    while (1) {
        char enemy_1[257], enemy_2[257];
        int dist_1, dist_2;

        scanf("%s", enemy_1);
        scanf("%d", &dist_1);
        scanf("%s", enemy_2);
        scanf("%d", &dist_2);

        if (dist_1 < dist_2) {
            printf("%s\n", enemy_1);
        } else {
            printf("%s\n", enemy_2);
        }
    }

    return 0;
}
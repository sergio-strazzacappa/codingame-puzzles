#include <stdio.h>
#include <string.h>

char order[9];
char side[6];

int solve();

int main() {
    scanf("%[^\n]", order);
    fgetc(stdin);
    scanf("%[^\n]", side);

    int folds = solve();

    printf("%d\n", folds);

    return 0;
}

int solve() {
    int folds[] = {1, 1, 1, 1}; // R/D/L/U
    int index;

    for (int i = 0; i < strlen(order); i++) {
        switch (order[i]) {
            case 'R': 
                folds[2] += folds[0];
                folds[0] = 1;
                folds[1] *= 2;
                folds[3] *= 2;
                break;
            case 'D':
                folds[3] += folds[1];
                folds[0] *= 2;
                folds[1] = 1;
                folds[2] *= 2;
                break;
            case 'L': 
                folds[0] += folds[2];
                folds[1] *= 2;
                folds[2] = 1;
                folds[3] *= 2;
                break;
            case 'U':
                folds[1] += folds[3];
                folds[0] *= 2;
                folds[2] *= 2;
                folds[3] = 1;
                break;
            default: 
                printf("Incorrect side\n");
                break;
        }
    }

    switch (side[0]) {
        case 'R':
            index = 0;
            break;
        case 'D':
            index = 1;
            break;
        case 'L':
            index = 2;
            break;
        case 'U':
            index = 3;
            break;
        default:
            printf("Incorrect side\n");
            break;
    }

    return folds[index];
}

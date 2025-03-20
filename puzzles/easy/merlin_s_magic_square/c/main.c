#include <stdio.h>
#include <string.h>

int grid[3][3] = {
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
};

int solution[3][3] = {
    {1, 1, 1},
    {1, 0, 1},
    {1, 1, 1}
};

char pressed[101];

void solve();
int different(int *x, int *y);
void print_grid();

int main() {
    for (int y = 0; y < 3; y++) {
        char row[6];
        scanf("%[^\n]", row);
        fgetc(stdin);

        int x = 0;
        for (int j = 0; j < strlen(row); j++) {
            if (row[j] == ' ')
                continue;
            if (row[j] == '*') {
                grid[y][x] ^= 1;
            }
            x++;
        }
    }

    scanf("%[^\n]", pressed);

    solve();

    return 0;
}

void solve() {
    // simulate every button pressed by Lizzo
    for (int i = 0; i < strlen(pressed); i++) {
        char button = pressed[i];

        switch (button) {
            case '1':
                grid[0][0] ^= 1;
                grid[0][1] ^= 1;
                grid[1][0] ^= 1;
                grid[1][1] ^= 1;
                break;
            case '2':
                grid[0][0] ^= 1;
                grid[0][1] ^= 1;
                grid[0][2] ^= 1;
                break;
            case '3':
                grid[0][1] ^= 1;
                grid[0][2] ^= 1;
                grid[1][1] ^= 1;
                grid[1][2] ^= 1;
                break;
            case '4':
                grid[0][0] ^= 1;
                grid[1][0] ^= 1;
                grid[2][0] ^= 1;
                break;
            case '5':
                grid[0][1] ^= 1;
                grid[1][0] ^= 1;
                grid[1][1] ^= 1;
                grid[1][2] ^= 1;
                grid[2][1] ^= 1;
                break;
            case '6':
                grid[0][2] ^= 1;
                grid[1][2] ^= 1;
                grid[2][2] ^= 1;
                break;
            case '7':
                grid[1][0] ^= 1;
                grid[1][1] ^= 1;
                grid[2][0] ^= 1;
                grid[2][1] ^= 1;
                break;
            case '8':
                grid[2][0] ^= 1;
                grid[2][1] ^= 1;
                grid[2][2] ^= 1;
                break;
            case '9':
                grid[1][1] ^= 1;
                grid[1][2] ^= 1;
                grid[2][1] ^= 1;
                grid[2][2] ^= 1;
                break;
            default:
                fprintf(stderr, "[ERROR] Incorrect button\n");
        }
    }

    // check the flipped cells
    int x, y;
    int n = different(&x, &y);

    // print the button that reaches the solution
    if (n == 3) {
        if (x == 1 && y == 0)
            printf("2\n");
        if (x == 2 && y == 1)
            printf("6\n");
        if (x == 1 && y == 2)
            printf("8\n");
        if (x == 0 && y == 1)
            printf("4\n");
    }
    if (n == 4) {
        if (x == 0 && y == 0)
            printf("1\n");
        if (x == 2 && y == 0)
            printf("3\n");
        if (x == 0 && y == 2)
            printf("7\n");
        if (x == 2 && y == 2)
            printf("9\n");
    }
    if (n == 5)
        printf("5\n");
}

// return the number of different cells between the current state of the grid
// and the solution
// set the variables x and y with the position of a cell that determine the
// button to press to reach the solution
int different(int *x, int *y) {
    int n = 0;
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            if (grid[y][x] != solution[y][x]) {
                n++;
            }
        }
    }
    if (n == 4) {
        if (grid[0][0] != solution[0][0]) {
            *x = 0;
            *y = 0;
        }
        if (grid[2][0] != solution[2][0]) {
            *x = 0;
            *y = 2;
        }
        if (grid[0][2] != solution[0][2]) {
            *x = 2;
            *y = 0;
        }
        if (grid[2][2] != solution[2][2]) {
            *x = 2;
            *y = 2;
        }
    }

    if (n == 3) {
        if (grid[0][1] != solution[0][1]) {
            *x = 1;
            *y = 0;
        }
        if (grid[1][2] != solution[1][2]) {
            *x = 2;
            *y = 1;
        }
        if (grid[2][1] != solution[2][1]) {
            *x = 1;
            *y = 2;
        }
        if (grid[1][0] != solution[1][0]) {
            *x = 0;
            *y = 1;
        }
    }
    return n;
}

void print_grid() {
    for (int i = 0; i < 5; i++)
        fprintf(stderr, "-");
    fprintf(stderr, "\n");

    for (int y = 0; y < 3; y++) {
        fprintf(stderr, "|");
        for (int x = 0; x < 3; x++) {
            fprintf(stderr, "%d", grid[y][x]);
        }
        fprintf(stderr, "|\n");
    }

    for (int i = 0; i < 5; i++)
        fprintf(stderr, "-");
    fprintf(stderr, "\n");
}

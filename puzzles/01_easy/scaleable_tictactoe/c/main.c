#include <stdio.h>
#include <stdlib.h>

int size;
int goal;
char **grid;

void init();
void solve();
int check_goal(int x, int y, char player);
void clean();
void print_grid();

int main() {
    init();
    solve();
    clean();

    return 0;
}

void init() {
    scanf("%d%d%*c", &size, &goal);

    grid = (char **)malloc(sizeof(char *) * size);

    for (int y = 0; y < size; y++) {
        char row[size + 1];
        scanf("%[^\n]%*c", row);

        grid[y] = (char *)malloc(sizeof(char) * size);

        for (int x = 0; x < size; x++)
            grid[y][x] = row[x];
    }
}

void solve() {
    const char *MESSAGES[] = {
        "The game isn't over yet!",
        "The winner is X.",
        "The winner is O.",
        "The game ended in a draw!"
    };

    int status = 0;

    for (int y = 0; y < size && status == 0; y++) {
        for (int x = 0; x < size && status == 0; x++) {
            if (grid[y][x] == ' ')
                continue;
            status = check_goal(x, y, grid[y][x]);
        }
    }

    print_grid();
    printf("%s\n", MESSAGES[status]);
}

// check if the player starting from cell (x, y) wins the game
// returns the status:
// 0 the game continues
// 1 wins X
// 2 wins O
// 3 draw
int check_goal(int x, int y, char player) {
    int status = 3;

    const int MOVES[4][3] = {
        {+1, +0},
        {+1, +1},
        {+0, +1},
        {-1, +1}
    };

    const char MARKS[4] = {'-', '\\', '|', '/'};

    for (int i = 0; i < 4; i++) {
        int current_x = x;
        int current_y = y;
        int path_length = 0;

        while (current_x >= 0 && current_x < size &&
                current_y >= 0 && current_y < size) {
            if (grid[current_y][current_x] != player)
                break;
            if (grid[current_y][current_x] == player)
                path_length++;
            if (path_length == goal) {
                // success
                for (int path = 0; path < goal; path++) {
                    grid[y][x] = MARKS[i];
                    x += MOVES[i][0];
                    y += MOVES[i][1];
                }
                if (player == 'X')
                    status = 1;
                else if (player == 'O')
                    status = 2;
                break;
            }

            current_x += MOVES[i][0];
            current_y += MOVES[i][1];
        }
    }

    if (status == 3) {
        // check if it is a draw
        for (int y = 0; y < size; y++) {
            for (int x = 0; x < size; x++) {
                if (grid[y][x] == ' ') {
                    status = 0;
                    break;
                }
            }
            if (status == 0)
                break;
        }
    }
    return status;
}

void clean() {
    for (int y = 0; y < size; y++)
        free(grid[y]);
    free(grid);
}

void print_grid() {
    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            printf("%c", grid[y][x]);
        }
        printf("\n");
    }
}

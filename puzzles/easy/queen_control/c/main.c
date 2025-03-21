#include <stdio.h>

enum Color  {
    WHITE,
    BLACK
};

enum Color color;
char board[8][8];

void solve();
int valid_move(int x, int y, int *stop);
void print_board();

int main() {
    char c[6];
    scanf("%[^\n]", c);
    fgetc(stdin);

    if (c[0] == 'w')
        color = WHITE;
    else
        color = BLACK;

    for (int y = 0; y < 8; y++) {
        char line[9];
        scanf("%[^\n]", line);
        fgetc(stdin);

        for (int x = 0; x < 8; x++) {
            board[y][x] = line[x];
        }
    }

    solve();

    return 0;
}

void solve() {
    // get the position of the queen
    int x = -1;
    int y = -1;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board[i][j] == 'Q') {
                x = j;
                y = i;
                break;
            }
        }
        if (x != -1)
            break;
    }

    int moves = 0;

    // to the left
    for (int i = x - 1; i >= 0; i--) {
        int stop;
        moves += valid_move(i, y, &stop);
        if (stop)
            break;
    }

    // to the right
    for (int i = x + 1; i < 8; i++) {
        int stop;
        moves += valid_move(i, y, &stop);
        if (stop)
            break;
    }

    // up
    for (int i = y - 1; i >= 0; i--) {
        int stop;
        moves += valid_move(x, i, &stop);
        if (stop)
            break;
    }

    // down
    for (int i = y + 1; i < 8; i++) {
        int stop;
        moves += valid_move(x, i, &stop);
        if (stop)
            break;
    }

    // up/left
    for (int i = x - 1, j = y - 1; i >= 0 && j >= 0; i--, j--) {
        int stop;
        moves += valid_move(i, j, &stop);
        if (stop)
            break;
    }

    // up/right
    for (int i = x + 1, j = y - 1; i < 8 && j >= 0; i++, j--) {
        int stop;
        moves += valid_move(i, j, &stop);
        if (stop)
            break;
    }

    // down/left
    for (int i = x - 1, j = y + 1; i >= 0 && j < 8; i--, j++) {
        int stop;
        moves += valid_move(i, j, &stop);
        if (stop)
            break;
    }

    // down/right
    for (int i = x + 1, j = y + 1; i < 8 && j < 8; i++, j++) {
        int stop;
        moves += valid_move(i, j, &stop);
        if (stop)
            break;
    }

    printf("%d\n", moves);
}

// return 1 if the queen can move to (x, y)
// 0 otherwise
// set stop to 1 if another piece is in that cell
int valid_move(int x, int y, int *stop) {
    *stop = 0;
    if (board[y][x] == '.')
        return 1;

    enum Color cell;

    if (board[y][x] == 'w')
        cell = WHITE;
    else
        cell = BLACK;

    *stop = 1;

    if (color == cell)
        return 0;
    else
        return 1;
}


void print_board() {
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            fprintf(stderr, "%c", board[y][x]);
        }
        fprintf(stderr, "\n");
    }
}

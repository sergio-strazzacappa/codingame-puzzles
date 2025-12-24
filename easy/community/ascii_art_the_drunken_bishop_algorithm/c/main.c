#include <stdio.h>
#include <ctype.h>

#define ROWS 9
#define COLS 17

typedef struct position {
    int row;
    int column;
} Position;

char fingerprint[129];
int board[ROWS][COLS];
Position my_pos;

void init();
void solve();
void move(char hex[], int index);
void hex_to_bin(char *binary, char c);
void do_a_move(char bits[]);
void print_board();
void debug();

int main() {
    init();
    solve();

    return 0;
}

void init() {
    scanf("%[^\n]", fingerprint);

    for (int y = 0; y < ROWS; y++) {
        for (int x = 0; x < COLS; x++) {
            board[y][x] = 0;
        }
    }

    my_pos.row = 4;
    my_pos.column = 8;
}

void solve() {
    char hex[32];
    int j = 0;

    for (int i = 0; i < 48; i++) {
        if (fingerprint[i] == ':')
            continue;
        hex[j] = fingerprint[i];
        j++;
    }

    for (int i = 0; i < 32; i += 2)
        move(hex, i);

    print_board(board);
}

void move(char hex[], int index) {
    char high[5] = {'0', '0', '0', '0', '\0'};
    char low[5] = {'0', '0', '0', '0', '\0'};

    hex_to_bin(high, hex[index]);
    hex_to_bin(low, hex[index + 1]);

    char bits_1[2];
    char bits_2[2];
    char bits_3[2];
    char bits_4[2];

    bits_1[0] = low[2];
    bits_1[1] = low[3];
    bits_2[0] = low[0];
    bits_2[1] = low[1];
    bits_3[0] = high[2];
    bits_3[1] = high[3];
    bits_4[0] = high[0];
    bits_4[1] = high[1];

    do_a_move(bits_1);
    do_a_move(bits_2);
    do_a_move(bits_3);
    do_a_move(bits_4);
}

void hex_to_bin(char *binary, char c) {
    int n;

    if (isdigit(c))
        n = c - '0';
    else
        n = 10 + c - 'a';

    int i = 3;
    while (n > 0) {
        binary[i] = (n % 2) + '0';
        n /= 2;
        i--;
    }

    for (; i >= 0; i--)
        binary[i] = '0';
}

void do_a_move(char bits[]) {
    if (bits[0] == '0' && bits[1] == '0') {
        // North/West
        if (my_pos.column == 0 && my_pos.row > 0) {
            my_pos.row--;
        } else if (my_pos.row == 0 && my_pos.column > 0) {
            my_pos.column--;
        } else if (my_pos.row != 0 && my_pos.column != 0) {
            my_pos.row--;
            my_pos.column--;
        }
    }
    if (bits[0] == '0' && bits[1] == '1') {
        // North/East
        if (my_pos.column == 16 && my_pos.row > 0) {
            my_pos.row--;
        } else if (my_pos.row == 0 && my_pos.column < 16) {
            my_pos.column++;
        } else if (my_pos.row != 0 && my_pos.column != 16) {
            my_pos.row--;
            my_pos.column++;
        }
    }
    if (bits[0] == '1' && bits[1] == '0') {
        // South/West
        if (my_pos.column == 0 && my_pos.row < 8) {
            my_pos.row++;
        } else if (my_pos.row == 8 && my_pos.column > 0) {
            my_pos.column--;
        } else if (my_pos.row != 8 && my_pos.column != 0) {
            my_pos.row++;
            my_pos.column--;
        }
    }
    if (bits[0] == '1' && bits[1] == '1') {
        // South/East
        if (my_pos.column == 16 && my_pos.row < 8) {
            my_pos.row++;
        } else if (my_pos.row == 8 && my_pos.column < 16) {
            my_pos.column++;
        } else if (my_pos.row != 8 && my_pos.column != 16) {
            my_pos.row++;
            my_pos.column++;
        }
    }
    board[my_pos.row][my_pos.column]++;
}

void print_board() {
    printf("+---[CODINGAME]---+\n");

    for (int i = 0; i < ROWS; i++) {
        printf("|");

        for (int j = 0; j < COLS; j++) {
            if (i == 4 && j == 8) {
                printf("%c", 'S');
            } else if (i == my_pos.row && j == my_pos.column) {
                printf("%c", 'E');
            } else {
                switch (board[i][j] % 15) {
                    case 0:
                        printf("%c", ' ');
                        break;
                    case 1:
                        printf("%c", '.');
                        break;
                    case 2:
                        printf("%c", 'o');
                        break;
                    case 3:
                        printf("%c", '+');
                        break;
                    case 4:
                        printf("%c", '=');
                        break;
                    case 5:
                        printf("%c", '*');
                        break;
                    case 6:
                        printf("%c", 'B');
                        break;
                    case 7:
                        printf("%c", 'O');
                        break;
                    case 8:
                        printf("%c", 'X');
                        break;
                    case 9:
                        printf("%c", '@');
                        break;
                    case 10:
                        printf("%c", '%');
                        break;
                    case 11:
                        printf("%c", '&');
                        break;
                    case 12:
                        printf("%c", '#');
                        break;
                    case 13:
                        printf("%c", '/');
                        break;
                    case 14:
                        printf("%c", '^');
                        break;
                }
            }
        }
        printf("|\n");
    }
    printf("+-----------------+\n");
}

void debug() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            fprintf(stderr, "%d", board[i][j]);
        }
        fprintf(stderr, "\n");
    }
}

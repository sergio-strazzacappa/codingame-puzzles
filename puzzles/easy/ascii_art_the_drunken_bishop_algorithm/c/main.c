#include <stdio.h>

typedef struct position {
    int row;
    int column;
} Position;

char fingerprint[129];
Position my_pos;

void move(int board[9][17], char hex[], int index);
void hex_to_bin(char *binary, char c);
void do_a_move(int board[9][17], char bits[]);
void print_board(int board[9][17]);
void debug_board(int board[9][17]);

int main() {
    scanf("%[^\n]", fingerprint);

    char hex[32];
    int j = 0;

    for (int i = 0; i < 48; i++) {
        if (fingerprint[i] == ':') {
            continue;
        }
        hex[j] = fingerprint[i];
        j++;
    }

    int board[9][17];

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 17; j++) {
            board[i][j] = 0;
        }
    }

    my_pos.row = 4;
    my_pos.column = 8;

    for (int i = 0; i < 32; i+=2) {
        move(board, hex, i);
    }

    print_board(board);

    return 0;
}

void move(int board[9][17], char hex[], int index) {
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

    do_a_move(board, bits_1);
    do_a_move(board, bits_2);
    do_a_move(board, bits_3);
    do_a_move(board, bits_4);
}

void hex_to_bin(char *binary, char c) {
    switch(c) {
        case '1': {
            binary[3] = '1';
            break;
        }
        case '2': {
            binary[2] = '1';
            break;
        }
        case '3': {
            binary[2] = '1';
            binary[3] = '1';
            break;
        }
        case '4': {
            binary[1] = '1';
            break;
        }
        case '5': {
            binary[1] = '1';
            binary[3] = '1';
            break;
        }
        case '6': {
            binary[1] = '1';
            binary[2] = '1';
            break;
        }
        case '7': {
            binary[1] = '1';
            binary[2] = '1';
            binary[3] = '1';
            break;
        }
        case '8': {
            binary[0] = '1';
            break;
        }
        case '9': {
            binary[0] = '1';
            binary[3] = '1';
            break;
        }
        case 'a': {
            binary[0] = '1';
            binary[2] = '1';
            break;
        }
        case 'b': {
            binary[0] = '1';
            binary[2] = '1';
            binary[3] = '1';
            break;
        }
        case 'c': {
            binary[0] = '1';
            binary[1] = '1';
            break;
        }
        case 'd': {
            binary[0] = '1';
            binary[1] = '1';
            binary[3] = '1';
            break;
        }
        case 'e': {
            binary[0] = '1';
            binary[1] = '1';
            binary[2] = '1';
            break;
        }
        case 'f': {
            binary[0] = '1';
            binary[1] = '1';
            binary[2] = '1';
            binary[3] = '1';
            break;
        }
    }
}

void do_a_move(int board[9][17], char bits[]) {
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

void print_board(int board[9][17]) {
    printf("+---[CODINGAME]---+\n");

    for (int i = 0; i < 9; i++) {
        printf("|");

        for (int j = 0; j < 17; j++) {
            if (i == 4 && j == 8) {
                printf("%c", 'S');
            } else if (i == my_pos.row && j == my_pos.column) {
                printf("%c", 'E');
            } else {
                while(board[i][j] > 14) {
                    board[i][j] -= 15;
                }
                switch (board[i][j]) {
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

void debug_board(int board[9][17]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 17; j++) {
            fprintf(stderr, "%d", board[i][j]);
        }
        fprintf(stderr, "\n");
    }
    fprintf(stderr, "\n");
}

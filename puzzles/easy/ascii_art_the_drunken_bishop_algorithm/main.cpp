#include <iostream>
#include <string>

using namespace std;

struct Position {
    int row;
    int column;
} my_pos;

void debug_board(int board[9][17]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 17; j++) {
            cerr << board[i][j];
        }
        cerr << endl;
    }
    cerr << endl;
}

void print_board(int board[9][17]) {
    printf("+---[CODINGAME]---+\n");
    for (int i = 0; i < 9; i++) {
        cout << "|";
        for (int j = 0; j < 17; j++) {
            if (i == 4 && j == 8) {
                cout << "S";
            } else if (i == my_pos.row && j == my_pos.column) {
                cout << "E";
            } else {
                while(board[i][j] > 14) {
                    board[i][j] -= 15;
                }
                switch (board[i][j]) {
                    case 0:
                        cout << " ";
                        break;
                    case 1:
                        cout << ".";
                        break;
                    case 2:
                        cout << "o";
                        break;
                    case 3:
                        cout << "+";
                        break;
                    case 4:
                        cout << "=";
                        break;
                    case 5:
                        cout << "*";
                        break;
                    case 6:
                        cout << "B";
                        break;
                    case 7:
                        cout << "O";
                        break;
                    case 8:
                        cout << "X";
                        break;
                    case 9:
                        cout << "@";
                        break;
                    case 10:
                        cout << "%";
                        break;
                    case 11:
                        cout << "&";
                        break;
                    case 12:
                        cout << "#";
                        break;
                    case 13:
                        cout << "/";
                        break;
                    case 14:
                        cout << "^";
                        break;
                }
            }
        }
        cout << "|" << endl;
    }
    cout << "+-----------------+" << endl;;
}

string hex_to_bin(string binary, char c) {
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
    return binary;
}

void do_a_move(int board[9][17], string bits) {
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

void move(int board[9][17], string hex, int index) {
    string high = "0000";
    string low = "0000";

    high = hex_to_bin(high, hex[index]);
    low = hex_to_bin(low, hex[index + 1]);

    string bits_1 = "00";
    string bits_2 = "00";
    string bits_3 = "00";
    string bits_4 = "00";

    bits_1[0] = low[2];
    bits_1[1] = low[3];
    bits_2[0] = low[0];
    bits_2[1] = low[1];
    bits_3[0] = high[2];
    bits_3[1] = high[3];
    bits_4[0] = high[0];
    bits_4[1] = high[1];

    do_a_move(board, bits_1);
    //debug_board(board);
    do_a_move(board, bits_2);
    //debug_board(board);
    do_a_move(board, bits_3);
    //debug_board(board);
    do_a_move(board, bits_4);
    //debug_board(board);
}

int main() {
    string fingerprint;
    cin >> fingerprint;
    cin.ignore();

    string hex = "";

    for (int i = 0; i < fingerprint.size(); i++) {
        if (fingerprint[i] == ':') {
            continue;
        }
        hex += fingerprint[i];
    }

    int board[9][17];

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 17; j++) {
            board[i][j] = 0;
        }
    }

    my_pos.row = 4;
    my_pos.column = 8;

    //debug_board(board);

    for (int i = 0; i < 32; i+=2) {
        move(board, hex, i);
    }

    //debug_board(board);

    print_board(board);
}

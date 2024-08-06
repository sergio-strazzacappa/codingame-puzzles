#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define LEN 501
#define ROW 25
#define COL 19

// Init the board with {}
int init(char* board[ROW][COL]) {
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            board[i][j] = "{}";
        }
    }
    return 0;
}

// check of char c is out of range
int error(char c) {
    return !(c >= 32 && c <= 122);
}

int reset(char* action, char* diameter) {
    strcpy(action, "");
    strcpy(diameter, "");
    return 0;    
}

int print(char* board[ROW][COL]) {
    fprintf(stderr, "%s\n", "BOARD:");
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            fprintf(stderr, "%s", board[i][j]);
        }
        fprintf(stderr, "\n");
    }
    return 0;
}

int print_solution(char* board[ROW][COL]) {
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            printf("%s", board[i][j]);
        }
        printf("\n");
    }
    return 0;
}

// calculate the euclidean distance between two points
double distance(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

int solve(char* action, char x, char y, char* diameter, char* board[ROW][COL]) {
    double radius = atof(diameter) / 2;

    struct Point {
        int x;
        int y;
    } center;

    center.x = x - 'a';
    center.y = y - 'a';

    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            double d = distance(center.x, center.y, j, i);
            if (d <= radius) {
                if (strcmp(action, "PLANTMOW") == 0) {
                    if (strcmp(board[i][j], "  ") == 0) {
                        board[i][j] = "{}";
                    } else {
                        board[i][j] = "  ";
                    }
                } else if (strcmp(action, "PLANT") == 0) {
                    board[i][j] = "{}";
                } else {
                    board[i][j] = "  ";
                }
            }
        }
    }
    
    return 0;
}

int main() {
    char instructions[LEN];
    scanf("%[^\n]", instructions);

    char* board[ROW][COL];
    char action[9];
    char x;
    char y;
    char diameter[3];

    init(board);

    for (int i = 0; i < LEN; i++) {
        // check end of instruction
        if (instructions[i] == ' ' || error(instructions[i])) {
            solve(action, x, y, diameter, board);

            if (error(instructions[i])) {
                break; // end of input, exit
            }

            reset(action, diameter); // reset for the next instruction
            continue;
        }

        // check if action is PLANT or PLANTMOW
        if (instructions[i] == 'P') {
            action[0] = instructions[i];            // P
            action[1] = instructions[i + 1];        // L
            action[2] = instructions[i + 2];        // A
            action[3] = instructions[i + 3];        // N
            action[4] = instructions[i + 4];        // T
            action[5] = '\0';
            if (instructions[i + 5] == 'M') {
                action[5] = instructions[i + 5];    // M
                action[6] = instructions[i + 6];    // O
                action[7] = instructions[i + 7];    // W
                action[8] = '\0';
                i += 3;
            }
            i += 4;
            continue;
        }

        // get coordinates and diameter
        x = instructions[i];
        y = instructions[i + 1];
        diameter[0] = instructions[i + 2];
        diameter[1] = '\0';
        if (instructions[i + 3] >= 48 && instructions[i + 3] <= 57) {
            diameter[1] = instructions[i + 3];
            diameter[2] = '\0';
            i++;
        }
        i += 2;
    }

    print_solution(board); // print the board

    return 0;
}
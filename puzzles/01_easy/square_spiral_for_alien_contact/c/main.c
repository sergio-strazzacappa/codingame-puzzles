#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MIN(a, b) ((a) <= (b) ? (a) : (b))
#define MAX_SIDE 31

enum Start {
    TOP_LEFT,
    TOP_RIGHT,
    BOTTOM_RIGHT,
    BOTTOM_LEFT
};

enum Direction {
    CLOCKWISE,
    COUNTER_CLOCKWISE
};

struct Pattern {
    char first_char; 
    char second_char;
    int begin_range;
    int end_range;
};

int side;
enum Start start;
enum Direction direction;
struct Pattern pattern;

void init();
void solve();
void debug();

int main() {
    init();
    solve();

    return 0;
}

void init() {
    char instructions[101] = "";
    scanf("%[^\n]", instructions);

    char *token = strtok(instructions, " ");
    int field = 1;

    // Format: [Side Size - Start Position - Direction - Pattern]
    while (token != NULL) {
        char range[strlen(token) - 1];

        switch (field) {
            case 1:
                side = atoi(token);
                break;
            case 2:
                if (strcmp(token, "topLeft") == 0)
                    start = TOP_LEFT;
                if (strcmp(token, "topRight") == 0)
                    start = TOP_RIGHT;
                if (strcmp(token, "bottomLeft") == 0)
                    start = BOTTOM_LEFT;
                if (strcmp(token, "bottomRight") == 0)
                    start = BOTTOM_RIGHT;
                break;
            case 3:
                if (strcmp(token, "clockwise") == 0)
                    direction = CLOCKWISE;
                if (strcmp(token, "counter-clockwise") == 0)
                    direction = COUNTER_CLOCKWISE;
                break;
            case 4:
                pattern.first_char = token[0];

                for (int i = 1; i < strlen(token); i++)
                    range[i - 1] = token[i];

                range[strlen(token) - 1] = '\0';
                pattern.begin_range = atoi(range);
                break;
            case 5:
                pattern.second_char = token[0];

                for (int i = 1; i < strlen(token); i++)
                    range[i - 1] = token[i];
                
                range[strlen(token) - 1] = '\0';
                pattern.end_range = atoi(range);
                break;
            default:
                fprintf(stderr, "[ERROR] Incorrect field\n");
                break;
        }
        field++;
        token = strtok(NULL, " ");
    }
}

void solve() {
    char spiral[side][side];

    for (int y = 0; y < side; y++) {
        for (int x = 0; x < side; x++) {
            spiral[y][x] = ' ';
        }
    }

    int x = -1;
    int y = -1;

    if (start == TOP_LEFT) {
        x = 0;
        y = 0;
    } else if (start == TOP_RIGHT) {
        x = side - 1;
        y = 0;
    } else if (start == BOTTOM_RIGHT) {
        x = side - 1;
        y = side - 1;
    } else if (start == BOTTOM_LEFT) {
        x = 0;
        y = side - 1;
    }

    char current_char = pattern.first_char;
    int range = pattern.begin_range;
    int n = 0;
    int char_diff = pattern.second_char - pattern.first_char;
    int range_diff = pattern.end_range - pattern.begin_range;
    bool first = true;
    int line = side;
    int current_line = 0;
    int current_position = start;

    while (line != 0) {
        spiral[y][x] = current_char;
        n++;

        if (n == range) {
            n = 0;
            range += range_diff;
            current_char += char_diff;
        }

        current_line++;

        if (current_line == line) {
            current_line = 0;

            if (direction == CLOCKWISE)
                current_position = (current_position + 1) % 4;
            else {
                if (current_position == 0)
                    current_position = 3;
                else
                    current_position--;
            }

            if (first) {
                line--;
                first = false;
            } else if (current_position % 2 != start % 2)
                line -=2;
        }

        if (current_position == TOP_LEFT) {
            if (direction == CLOCKWISE)
                x++;
            else
                y++;
        } else if (current_position == TOP_RIGHT) {
            if (direction == CLOCKWISE)
                y++;
            else
                x--;
        } else if (current_position == BOTTOM_RIGHT) {
            if (direction == CLOCKWISE)
                x--;
            else
                y--;
        } if (current_position == BOTTOM_LEFT) {
            if (direction == CLOCKWISE)
                y--;
            else
                x++;
        }

        if (current_char > 'Z' || current_char < 'A')
            break;
    }

    // print the result
    for (int y = 0; y < MIN(side, MAX_SIDE); y++) {
        for (int x = 0; x < MIN(side, MAX_SIDE); x++) {
            printf("%c", spiral[y][x]);
        }
        printf("\n");
    }
}

void debug() {
    fprintf(stderr, "[DEBUG] Side = %d\n", side);
    fprintf(stderr, "[DEBUG] Start = %d\n", start);
    fprintf(stderr, "[DEBUG] Direction = %d\n", direction);
    fprintf(stderr, "[DEBUG] Pattern = (%c, %d) - (%c, %d)\n",
        pattern.first_char, pattern.begin_range,
        pattern.second_char, pattern.end_range);
}

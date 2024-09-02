#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void split(char input[]);
void solve(void);
void right(void);
void left(void);
void debug();

struct Opts {
    char* direction;
    int how_many_arrows;
    int height_of_arrows;
    int stroke_thickness_of_arrows;
    int spacing_between_arrows;
    int additional_indent_of_each_line;
} opts;

int main() {
    char input[101];
    scanf("%[^\n]", input);

    split(input);
    debug();
    solve();

    return 0;
}

void split(char input[]) {
    char *token = strtok(input, " ");
    int field = 1;

    while (token != NULL) {
        switch (field) {
            case 1:
                opts.direction = token;
                break;
            case 2:
                opts.how_many_arrows = atoi(token);
                break;
            case 3:
                opts.height_of_arrows = atoi(token);
                break;
            case 4:
                opts.stroke_thickness_of_arrows = atoi(token);
                break;
            case 5:
                opts.spacing_between_arrows = atoi(token);
                break;
            case 6:
                opts.additional_indent_of_each_line = atoi(token);
                break;
            default:
                fprintf(stderr, "Error splitting the input\n");
                break;
        }
        token = strtok(NULL, " ");
        field++;
    }
}

void solve() {
    if (strcmp(opts.direction, "right") == 0) {
        right();
    } else {
        left();
    }
}

void right() {
    int indent = 0;

    for (int i = 0; i < opts.height_of_arrows; i++) {
        for (int j = 0; j < indent; j++) {
            printf(" ");
        }

        if (i < opts.height_of_arrows / 2) {
            indent += opts.additional_indent_of_each_line;
        } else {
            indent -= opts.additional_indent_of_each_line;
        }

        for (int j = 0; j < opts.how_many_arrows; j++) {
            for (int k = 0; k < opts.stroke_thickness_of_arrows; k++) {
                printf(">");
            }
            if (j < opts.how_many_arrows - 1) {
                for (int k = 0; k < opts.spacing_between_arrows; k++) {
                    printf(" ");
                }
            }
        }
        printf("\n");
    }
}

void left() {
    int indent = 
        opts.height_of_arrows / 2 * opts.additional_indent_of_each_line;

    for (int i = 0; i < opts.height_of_arrows; i++) {
        for (int j = 0; j < indent; j++) {
            printf(" ");
        }

        if (i < opts.height_of_arrows / 2) {
            indent -= opts.additional_indent_of_each_line;
        } else {
            indent += opts.additional_indent_of_each_line;
        }

        for (int j = 0; j < opts.how_many_arrows; j++) {
            for (int k = 0; k < opts.stroke_thickness_of_arrows; k++) {
                printf("<");
            }
            if (j < opts.how_many_arrows - 1) {
                for (int k = 0; k < opts.spacing_between_arrows; k++) {
                    printf(" ");
                }
            }
        }
        printf("\n");
    }
}

void debug() {
    fprintf(stderr, "[DEBUG] Direction: %s\n", opts.direction);
    fprintf(stderr, "[DEBUG] How many arrows: %d\n", opts.how_many_arrows);
    fprintf(stderr, "[DEBUG] Height of arrows: %d\n", opts.height_of_arrows);
    fprintf(stderr, "[DEBUG] Stroke thickness of arrows: %d\n", opts.stroke_thickness_of_arrows);
    fprintf(stderr, "[DEBUG] Spacing between arrows: %d\n", opts.spacing_between_arrows);
    fprintf(stderr, "[DEBUG] Additional indent of each line: %d\n", opts.additional_indent_of_each_line);
}
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define SEQUENCE_MAX_SIZE 300

void solve(char sequence[]);

int main() {
    char sequence[SEQUENCE_MAX_SIZE];
    scanf("%[^\n]", sequence);

    solve(sequence);

    return 0;
}

void solve(char sequence[]) {
    float weights[26];
    int depth = 0;
    float max_weight = 0;
    bool is_open_tag = true;
    char solution;

    for (int i = 0; i < 26; i++)
        weights[i] = 0;

    depth = 1;

    for (int i = 0; i < strlen(sequence); i++) {
        char c = sequence[i];

        if (is_open_tag && isalpha(c)) {
            // found a new open tag
            depth++;
        } else if (!is_open_tag && isalpha(c)) {
            // found a close tag
            weights[c - 'a'] += 1. / depth;
            depth--;
            is_open_tag = true;
        } else {
            // the next tag is a close tag
            is_open_tag = false;
        }
    }

    // print the result
    for (int i = 0; i < 26; i++) {
        if (weights[i] > max_weight) {
            max_weight = weights[i];
            solution = i + 'a';
        }
    }

    printf("%c\n", solution);
}

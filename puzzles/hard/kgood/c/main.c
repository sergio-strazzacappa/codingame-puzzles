#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define STRING_MAX_SIZE 5001
#define LETTERS         26

char s[STRING_MAX_SIZE];
int k;

void init();
void solve();
void reset(char letters[]);
void mark(char c, char letters[]);

int main() {
    init();
    solve();

    return 0;
}

void init() {
    scanf("%s[^\n]", s);
    scanf("%d", &k);
}

void solve() {
    char letters[LETTERS];
    int start = 0;
    int longest = 0;

    while (start != strlen(s)) {
        int len = 0;
        int current_k = 0;

        reset(letters);

        for (int i = start; i < strlen(s); i++) {
            char current = s[i];

            if (letters[current - 'a']) {
                // current char is already seen
                len++;
                continue;
            }

            if (current_k == k)
                break;

            if (!letters[current - 'a']) {
                mark(current, letters);
                current_k++;
            }
            len++;
        }

        if (len > longest)
            longest = len;

        start++;
    }

    printf("%d\n", longest);
}

void reset(char letters[]) {
    for (int i = 0; i < LETTERS; i++)
        letters[i] = false;
}

void mark(char c, char letters[]) {
    letters[c - 'a'] = true;
}

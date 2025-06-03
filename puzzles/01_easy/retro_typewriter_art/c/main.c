#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

char recipe[1001];

void solve();
bool parse(char *token);
bool abbr(char c[]);

int main() {
    scanf("%[^\n]", recipe);
    solve();

    return 0;
}

void solve() {
    char *token = strtok(recipe, " ");
    bool nl = false;

    while (token != NULL) {
        nl = parse(token);
        token = strtok(NULL, " ");
    }

    if (!nl)
        printf("\n");
}

bool parse(char *token) {
    int times = 0;
    int index = 0;
    char character[3];
    int len = strlen(token);
    bool nl = false;

    for (int i = 0; i < len; i++) {
        if (isdigit(token[i]) && i < len - 1) {
            int digit = token[i] - '0';
            times *= 10;
            times += digit;
            index = 0;
            continue;
        }

        character[index++] = token[i];
    }

    character[index] = '\0';

    if (strcmp(character, "nl") == 0) {
        times = 1;
        nl = true;
    }

    for (int i = 0; i < times; i++) {
        if (abbr(character))        ;
        else printf("%s", character);
    }

    return nl;
}

bool abbr(char c[]) {
    if (strcmp(c, "sp") == 0) {
        printf(" ");
        return true;
    }
    if (strcmp(c, "bS") == 0) {
        printf("\\");
        return true;
    }
    if (strcmp(c, "sQ") == 0) {
        printf("'");
        return true;
    }
    if (strcmp(c, "nl") == 0) {
        printf("\n");
        return true;
    }

    return false;
}

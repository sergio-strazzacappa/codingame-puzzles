#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int n; // number of digits
char **numbers;

void init();
void solve();
void clean();
void debug();

int main() {
    init();
    solve();
    clean();

    return 0;
}

void init() {
    n = -1;
    numbers = (char **)malloc(sizeof(char *) * 5);

    for (int i = 0; i < 5; i++) {
        char s[4097];
        scanf("%[^\n]", s);
        fgetc(stdin);

        if (n == -1)
            n = strlen(s) / 6 + 1;

        numbers[i] = (char *)malloc(sizeof(char) * strlen(s));
        strcpy(numbers[i], s);
    }
}

void solve() {
    for (int i = 0; i < n; i++) {
        int index = 5 * i + i;

        if (numbers[0][index] == '*') {
            // 0 - 1 - 6 - 7 - 8 - 9
            if (numbers[1][index] == '0')
                printf("0");
            else if (numbers[2][index] == '*')
                printf("8");
            else if (numbers[4][index] == '*')
                if (numbers[0][index + 2] == '*')
                    printf("1");
                else
                    printf("7");
            else if (numbers[4][index + 3] == '*')
                printf("6");
            else
                printf("9");
        } else {
           // 2 - 3 - 4 - 5 
            if (numbers[1][index] == '0')
               printf("4");
            else if (numbers[2][index + 1] == '*')
                printf("2");
            else if (numbers[1][index + 2] == '*')
               printf("3");
            else
                printf("5");
        }
    }
    printf("\n");
}

void clean() {
    for (int i = 0; i < 5; i++)
        free(numbers[i]);
    free(numbers);
}

void debug() {
    for (int i = 0; i < 5; i++)
        fprintf(stderr, "%s\n", numbers[i]);
}

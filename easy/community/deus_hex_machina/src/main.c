#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NUMBER_SIZE 20000

const char HORIZONTAL_FLIP[16] = {
    '0', '1', '5', '#', '#', '2', 'a', '#', '8', 'e', '6', 'd', '#', 'b', '9', '#'
};

const char VERTICAL_FLIP[16] = {
    '0', '1', '5', '3', '#', '2', 'e', '#', '8', 'a', '9', '#', 'c', '#', '6', '#'
};

int ones = 0;
int zeros = 0;

void solve(char number[]);
char *to_bin(char number[]);

int main() {
    char number[MAX_NUMBER_SIZE + 1] = "";
    scanf("%[^\n]", number);

    solve(number);

    return 0;
}

void solve(char number[]) {
    char *bin = to_bin(number);

    bool leading_zeros = true;

    for (int i = 0; i < strlen(bin); i++) {
        // for each flip
        if (leading_zeros && bin[i] == '0') {
            zeros--;
            continue;
        }
        leading_zeros = false;
    }

    for (int i = 0; i < strlen(number); i++) {
        int pos = -1;

        if (number[i] >= '0' && number[i] <= '9')
            pos = number[i] - '0';
        else if (number[i] >= 'a' && number[i] <= 'f') {
            pos = number[i] - 'a' + 10;
        }

        if (zeros % 2 == 1) {
            // horizontal flip
            number[i] = HORIZONTAL_FLIP[pos];
        }
    }

    if (zeros % 2 == 1) {
        for (int i = 0; i < strlen(number) / 2; i++) {
            char tmp = number[i];
            number[i] = number[strlen(number) - i - 1];
            number[strlen(number) - i - 1] = tmp;
        }
    }

    for (int i = 0; i < strlen(number); i++) {
        int pos = -1;

        if (number[i] >= '0' && number[i] <= '9')
            pos = number[i] - '0';
        else if (number[i] >= 'a' && number[i] <= 'f') {
            pos = number[i] - 'a' + 10;
        }

        if (ones % 2 == 1) {
            // vertical flip
            number[i] = VERTICAL_FLIP[pos];
        }
    }

    for (int i = 0; i < strlen(number); i++) {
        if (number[i] == '#') {
            printf("Not a number\n");
            exit(1);
        }
    }

    if (strlen(number) > 1000) {
        for (int i = 0; i < 1000; i++) {
            printf("%c", number[i]);
        }
        printf("\n");

    } else {
        printf("%s\n", number);
    }
}

char *to_bin(char number[]) {
    static char bin[MAX_NUMBER_SIZE * 4 + 1];
    int i = 0;

    for (int j = 0; j < strlen(number); j++) {
        int hex = -1;
        int k = 3;

        if (number[j] >= '0' && number[j] <= '9' )
            hex = number[j] - '0';
        else
            hex = number[j] - 'a' + 10;

        while (hex > 0) {
            bin[i + k] = hex % 2 + '0';

            if (hex % 2 == 0)
                zeros++;
            else
                ones++;

            hex /= 2;
            k--;
        }

        while (k >= 0) {
            bin[i + k] = '0';
            zeros++;
            k--;
        }

        i += 4;
    }

    bin[i] = '\0';

    return bin;
}

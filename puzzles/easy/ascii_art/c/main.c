#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LINE_LEN 600
#define ROW_SIZE 1025

int width;
int height;
char text[257];
char *representation;
int size;

void dump();
char *solve();

int main() {
    scanf("%d%d", &width, &height);
    fgetc(stdin);

    scanf("%[^\n]", text);
    fgetc(stdin);

    representation = (char *)malloc(height * ROW_SIZE * sizeof(char));

    for (int i = 0; i < height; i++) {
        char row[ROW_SIZE];
        scanf("%[^\n]", row);
        fgetc(stdin);

        if (i == 0)
            size = strlen(row);

        for (int j = 0; j < size; j++)
            representation[i * size + j] = row[j];
    }
    printf("%s\n", solve());

    return 0;
}

char *solve() {
    char *solution = (char *)malloc(height * ROW_SIZE * sizeof(char));
    int index = 0;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < strlen(text); j++) {
            char c = text[j];

            // if c is lowercase, convert it to uppercase
            if (c >= 'a' && c <= 'z')
                c = toupper(c);

            int base = c - 'A';

            // if c is invalid, change base to ?
            if (c < 'A' || c > 'Z')
                base = 'Z' - 'A' + 1;

            for (int k = base * width; k < base * width + width; k++) {
                solution[index++] = representation[i * size + k];
            }
        }
        solution[index++] = '\n';
    }
    return solution;
}

void dump() {
    printf("### START DUMP ###\n");

    printf("The width is: %d\n", width);
    printf("The height is: %d\n", height);
    printf("The text is: %s\n", text);
    printf("The representation is:\n");

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < size; j++)
            printf("%c", representation[i * size + j]);

        printf("\n");
    }

    printf("### END DUMP ###\n\n");
}

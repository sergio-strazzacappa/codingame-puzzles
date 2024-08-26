#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ROW_SIZE 1025

char* representation; // stores the ascii representation of every letter
int size;

int main() {
    int length, height;
    char text[257];

    scanf("%d%d", &length, &height);
    fgetc(stdin);
    scanf("%[^\n]", text);
    fgetc(stdin);

    representation = malloc(height * ROW_SIZE * sizeof(char));

    for (int i = 0; i < height; i++) {
        char row[ROW_SIZE];
        scanf("%[^\n]", row);
        fgetc(stdin);

        if (!i) size = strlen(row);

        for (int j = 0; j < size; j++) {
            representation[i * size + j] = row[j];
        }
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < strlen(text); j++) {
            char c = text[j];

            // if c is lowercase convert it to uppercase
            if (c >= 'a' && c <= 'z') {
                c = toupper(c);
            }

            int base = c - 'A';
            // if c is invalid change the base to ?
            if (c < 'A' || c > 'Z') {
                base = 'Z' - 'A' + 1;
            }
            for (int k = base * length; k < base * length + length ; k++) {
                printf("%c", representation[i * size + k]);
            }
        }
        printf("\n");
    }

    free(representation);

    return 0;
}
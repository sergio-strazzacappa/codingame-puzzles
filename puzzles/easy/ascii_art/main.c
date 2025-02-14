#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TEST            0
#define NUMBER_FILES    6
#define LINE_LEN        600
#define ROW_SIZE        1025

const char *INPUT_FILE[] = {
    "input/01_test_only_one_letter_e.txt",
    "input/02_test_manhattan.txt",
    "input/03_test_manhattan_2.txt",
    "input/04_test_manhattan_3.txt",
    "input/05_manhattan_with_another_ascii_representation.txt",
    "input/06_test_man_hat_tan.txt"
};

const char *OUTPUT_FILE[] = {
    "output/01_test_only_one_letter_e.txt",
    "output/02_test_manhattan.txt",
    "output/03_test_manhattan_2.txt",
    "output/04_test_manhattan_3.txt",
    "output/05_manhattan_with_another_ascii_representation.txt",
    "output/06_test_man_hat_tan.txt"
};

int width;
int height;
char text[257];
char *representation;
int size;

void dump();
char *solve();

int main() {
    if (TEST) {
        for (int i = 0; i < NUMBER_FILES; i++) {
            FILE *fp;
            char line[LINE_LEN];

            if ((fp = fopen(INPUT_FILE[i], "r")) == NULL) {
                printf("[ERROR] Can't open the file %s\n", INPUT_FILE[i]);
                exit(1);
            }

            fgets(line, LINE_LEN, fp); // first line - width
            width = atoi(line);

            fgets(line, LINE_LEN, fp); // second line - height
            height = atoi(line);

            fgets(line, LINE_LEN, fp); // third line - text
            line[strlen(line) - 1] = '\0';
            strcpy(text, line);

            representation = (char *)malloc(height * ROW_SIZE * sizeof(char));

            for (int j = 0; j < height; j++) {
                fgets(line, LINE_LEN, fp);
                line[strlen(line) - 1] = '\0';

                if (j == 0)
                    size = strlen(line);

                for (int k = 0; k < size; k++) {
                    representation[j * size + k] = line[k];
                }
            }

            char *solution = solve();

            fclose(fp);

            if ((fp = fopen(OUTPUT_FILE[i], "r")) == NULL) {
                printf("[ERROR] Can't open the file %s\n", INPUT_FILE[i]);
                exit(1);
            }

            char *answer = (char *)malloc(height * ROW_SIZE * sizeof(char));

            int index = 0;
            for (int j = 0; j < height; j++) {
                fgets(line, LINE_LEN, fp);
                line[strlen(line) - 1] = '\0';

                for (int k = 0; k < strlen(line); k++) {
                    answer[index++] = line[k];
                }
                answer[index++] = '\n';
            }

            if (strcmp(solution, answer) == 0)
                printf("PASSED\n");
            else
                printf("FAILED\n");
        }

    } else {
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
    }

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

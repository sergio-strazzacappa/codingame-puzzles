#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TEST            0
#define NUMBER_FILES    9
#define EMPTY_SYMBOL    ' '
#define LINE_LEN        100

char *INPUT_FILE[] = {
    "input/01_example.txt",
    "input/02_wall_hug.txt",
    "input/03_single_pile.txt",
    "input/04_close_fit.txt",
    "input/05_fibo.txt",
    "input/06_pop_culture.txt",
    "input/07_chess_italian_opening.txt",
    "input/08_landscape.txt",
    "input/09_big_box.txt"
};

char *OUTPUT_FILE[] = {
    "output/01_example.txt",
    "output/02_wall_hug.txt",
    "output/03_single_pile.txt",
    "output/04_close_fit.txt",
    "output/05_fibo.txt",
    "output/06_pop_culture.txt",
    "output/07_chess_italian_opening.txt",
    "output/08_landscape.txt",
    "output/09_big_box.txt"
};

int width;
int height;
int n;
char *symbols;
int  *positions;

void solve(char solution[width][height]);

int main() {
    if (TEST) {
        for (int i = 0; i < NUMBER_FILES; i++) {
            FILE *fp;
            char line[LINE_LEN];

            if ((fp = fopen(INPUT_FILE[i], "r")) == NULL) {
                printf("[ERROR] Can't open the file %s\n", INPUT_FILE[i]);
                exit(1);
            }

            fgets(line, LINE_LEN, fp);          // line 1 - w and h
            width   = atoi(strtok(line, " "));
            height  = atoi(strtok(NULL, "\n"));

            fgets(line, LINE_LEN, fp);          // line 2 - n
            n       = atoi(strtok(line, "\n"));

            symbols     = (char *)malloc(sizeof(char) * n);
            positions   = (int *)malloc(sizeof(int) * n);

            int j = 0;
            while (fgets(line, LINE_LEN, fp)) { // next n lines
                symbols[j] = strtok(line, " ")[0];
                positions[j] = atoi(strtok(NULL, "\n"));
                j++;
            }

            char solution[width][height];

            for (int y = 0; y < height; y++) {
                for (int x = 0; x < width; x++) {
                    solution[x][y] = EMPTY_SYMBOL;
                }
            }

            solve(solution);
            
            printf("INPUT %d\n", i + 1);
            for (int y = 0; y < height; y++) {
                for (int x = 0; x < width; x++) {
                    printf("%c", solution[x][y]);
                }
                printf("\n");
            }

            fclose(fp);

            if ((fp = fopen(OUTPUT_FILE[i], "r")) == NULL) {
                printf("[ERROR] Can't open the file %s\n", OUTPUT_FILE[i]);
                exit(1);
            }

            int solved = 1;
            int y = 0;
            int x = 0;

            while (fgets(line, LINE_LEN, fp)) {
                x = 0;
                for (int j = 0; j < strlen(line); j++) {
                    if (line[j] == '\n')
                        break;
                    if (line[j] == '|' || line[j] == '+' || line[j] == '-')
                        continue;
                    if (solution[x][y] != line[j]) {
                        solved = 0;
                        break;
                    }
                    x++;
                }
                if (!solved)
                    break;
                y++;
            }

            if (solved)
                printf("\nPASSED\n");
            else
                printf("FAILED\n");

            fclose(fp);
        }
    } else {
        scanf("%d%d%d", &width, &height, &n);

        symbols     = (char *)malloc(sizeof(char) * n);
        positions   = (int *)malloc(sizeof(int) * n);

        for (int i = 0; i < n; i++) {
            char s[2];
            int p;

            scanf("%s%d", s, &p);
            symbols[i] = s[0];
            positions[i] = p;
        }
        
        char solution[width][height];

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                solution[x][y] = EMPTY_SYMBOL;
            }
        }

        solve(solution);

        for (int y = 0; y < height; y++) {
            printf("|");
            for (int x = 0; x < width; x++) {
                printf("%c", solution[x][y]);
            }
            printf("|\n");
        }
        printf("+");
        for (int x = 0; x < width; x++)
            printf("-");
        printf("+\n");
    }

    return 0;
}

void solve(char solution[width][height]) {
    for (int i = 0; i < n; i++) {
        char s = *(symbols + i);
        int x = *(positions + i);

        for (int y = 0; y < height; y++) {
            if (solution[x][y] != EMPTY_SYMBOL) {
                if (islower(s)) {
                    // right, left
                    if (x + 1 < width && solution[x + 1][y] == EMPTY_SYMBOL) {
                        y--;
                        x++;
                        continue;
                    }
                    if (x - 1 >= 0 && solution[x - 1][y] == EMPTY_SYMBOL) {
                        y--;
                        x--;
                        continue;
                    }
                    solution[x][y - 1] = s;
                    break;
                }
                if (isupper(s)) {
                    // left, right
                    if (x - 1 >= 0 && solution[x - 1][y] == EMPTY_SYMBOL) {
                        y--;
                        x--;
                        continue;
                    }
                    if (x + 1 < width && solution[x + 1][y] == EMPTY_SYMBOL) {
                        y--;
                        x++;
                        continue;
                    }
                    solution[x][y - 1] = s;
                    break;
                }
            }
            if (y == height - 1) {
                solution[x][y] = s;
            }
        }
    }
}

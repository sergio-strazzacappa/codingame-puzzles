#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMBER_WORDS 20

typedef struct Point {
    int x;
    int y;
} Point;

typedef struct cell {
    char character;
    Point point;
    int letter_mult;
    int word_mult;
    int compute;
} Cell;

typedef struct word {
    Cell letter[10];
    int size;
} Word;

typedef struct data {
    char *word;
    int score;
} Data;

int n;              // number of tiles in the tileset
int *tileset[2];
int width;          // width of the board
int height;         // height of the board
char *score;
char *start_board;
char *current_board;

void solve();
int compute_score(Word w);
int find(char c);
int is_bonus();
void clear();
void print_tileset();
void print_board(char *title, char *board);
int comp(const void *a, const void *b);

int main() {
    scanf("%d", &n);

    tileset[0] = (int *)malloc(sizeof(int) * n);
    tileset[1] = (int *)malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++) {
        char character[2];
        int score;
        scanf("%s%d", character, &score); 
        *(tileset[0] + i) = character[0];
        *(tileset[1] + i) = score;
    }

    scanf("%d%d", &width, &height);
    fgetc(stdin);

    score = (char *)malloc(sizeof(char) * height * width);
    for (int y = 0; y < height; y++) {
        // score system
        char row[16];
        scanf("%[^\n]", row);
        fgetc(stdin);

        for (int x = 0; x < width; x++) {
            *(score + (y * width + x)) = row[x];
        }
    }

    start_board = (char *)malloc(sizeof(char) * height * width);
    for (int y = 0; y < height; y++) {
        char row[16];
        scanf("%[^\n]", row);
        fgetc(stdin);
        
        for (int x = 0; x < width; x++) {
            *(start_board + (y * width + x)) = row[x];
        }
    }

    current_board = (char *)malloc(sizeof(char) * height * width);
    for (int y = 0; y < height; y++) {
        char row[16];
        scanf("%[^\n]", row);
        fgetc(stdin);

        for (int x = 0; x < width; x++) {
            *(current_board + (y * width + x)) = row[x];
        }
    }

    solve();
    clear();

    return 0;
}

void solve() {
    Word words[NUMBER_WORDS];
    Data solution[NUMBER_WORDS];
    int solution_index = 0;
    int number_words = 0;
    int total = 0;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // check the start of a word
            if (*(current_board + y * width + x) != '.') {
                if (y == 0 || (y > 0 && *(current_board + (y - 1) * width + x) == '.')) {
                    if (y == height - 1 || (y < height - 1 && *(current_board + (y + 1) * width + x) == '.'))
                        goto Horizontal;

                    // vertical word
                    Word word;
                    word.size = 0;
                    int index = 0;
                    int temp_y = y;

                    while (temp_y < height && *(current_board + temp_y * width + x) != '.') {
                        // still in the word
                        Cell c = {
                            .character = *(current_board + temp_y * width + x),
                            .point = {.x = x, .y = temp_y},
                            .letter_mult = 1,
                            .word_mult = 1,
                            .compute = 0
                        };

                        switch (*(score + temp_y * width + x)) {
                            case 'l':
                                c.letter_mult = 2;
                                break;
                            case 'L':
                                c.letter_mult = 3;
                                break;
                            case 'w':
                                c.word_mult = 2;
                                break;
                            case 'W':
                                c.word_mult = 3;
                                break;
                        }

                        word.letter[index++] = c;
                        word.size = index;
                        temp_y++;
                    }

                    words[number_words++] = word;
                }

Horizontal:
                if (x == 0 || (x > 0 && *(current_board + y * width + (x - 1)) == '.')) {
                    if (x == width - 1 || (x < width - 1 && *(current_board + y * width + (x + 1)) == '.'))
                        continue;

                    // horizontal word
                    Word word;
                    word.size = 0;
                    int index = 0;
                    int temp_x = x;

                    while (temp_x < width && *(current_board + y * width + temp_x) != '.') {
                        // still in the word
                        Cell c = {
                            .character = *(current_board + y * width + temp_x),
                            .point = {.x = temp_x, .y = y},
                            .letter_mult = 1,
                            .word_mult = 1,
                            .compute = 0
                        };

                        switch (*(score + y * width + temp_x)) {
                            case 'l':
                                c.letter_mult = 2;
                                break;
                            case 'L':
                                c.letter_mult = 3;
                                break;
                            case 'w':
                                c.word_mult = 2;
                                break;
                            case 'W':
                                c.word_mult = 3;
                                break;
                        }

                        word.letter[index++] = c;
                        word.size = index;
                        temp_x++;
                    }
                    words[number_words++] = word;
                }
            }
        }
    }

    int compute;
    for (int i = 0; i < number_words; i++) {
        compute = 0;
        for (int j = 0; j < words[i].size; j++) {
            int x = words[i].letter[j].point.x;
            int y =  words[i].letter[j].point.y;

            if (words[i].letter[j].character != *(start_board + y * width + x)) {
                compute = 1;
                words[i].letter[j].compute = 1;
            }
        }
        if (compute) {
            int score = compute_score(words[i]);
            char word[words[i].size + 1];

            for (int j = 0; j < words[i].size; j++) {
                word[j] = words[i].letter[j].character;
            }
            word[words[i].size] = '\0';

            Data d;

            d.word = (char *)malloc(sizeof(char) * words[i].size + 1);
            strcpy(d.word, word);
            d.score = score;
            solution[solution_index++] = d;

            total += score;
        }
    }

    qsort(solution, solution_index, sizeof(solution[0]), comp);

    for (int i = 0; i < solution_index; i++) {
        printf("%s %d\n", solution[i].word, solution[i].score);
    }

    if (is_bonus()) {
        printf("Bonus 50\n");
        total += 50;
    }

    printf("Total %d\n", total);
}

int compute_score(Word w) {
    int score = 0;
    for (int i = 0; i < w.size; i++)
        if (w.letter[i].compute)
            score += (find(w.letter[i].character) * w.letter[i].letter_mult);
        else
            score += find(w.letter[i].character);

    for (int i = 0; i < w.size; i++)
        if (w.letter[i].compute)
            score *= w.letter[i].word_mult;

    return score;
}

int find(char c) {
    for (int i = 0; i < n; i++) {
        if (c == *(tileset[0] + i))
            return *(tileset[1] + i);
    }
    return -1;
}

int is_bonus() {
    int adds = 0;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (*(start_board + y * width + x) != *(current_board + y * width + x)) {
                adds++;
            }
        }
    }

    return (adds == 7);
}

void clear() {
    free(tileset[0]);
    free(tileset[1]);
    free(score);
    free(start_board);
    free(current_board);
}

void print_tileset() {
    printf("[DEBUG] Tileset\n");
    printf("[DEBUG] ----------\n");
    for (int i = 0; i < n; i++) {
        printf("[DEBUG] %c:%d\n", *(tileset[0] + i), *(tileset[1] + i));
    }
}

void print_board(char *title, char *board) {
    printf("[DEBUG] %s\n", title);
    
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            printf("%c", *(board + (y * width + x)));
        }
        printf("\n");
    }
}

int comp(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

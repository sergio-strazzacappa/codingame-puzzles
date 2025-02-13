#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST            0
#define NUMBER_FILES    10
#define LINE_LEN        1000

typedef struct data {
    char *id;
    int start_range;
    int end_range;
    int *elements;
} Data;

const char *INPUT_FILE[] = {
    "input/01_simple.txt",
    "input/02_negative_indexing.txt",
    "input/03_nested.txt",
    "input/04_one_based.txt",
    "input/05_only_one_element.txt",
    "input/06_big_offsets_1.txt",
    "input/07_big_offsets_2.txt",
    "input/08_deep_nesting.txt",
    "input/09_complicated_1.txt",
    "input/10_complicated_2.txt"
};

const char *OUTPUT_FILE[] = {
    "output/01_simple.txt",
    "output/02_negative_indexing.txt",
    "output/03_nested.txt",
    "output/04_one_based.txt",
    "output/05_only_one_element.txt",
    "output/06_big_offsets_1.txt",
    "output/07_big_offsets_2.txt",
    "output/08_deep_nesting.txt",
    "output/09_complicated_1.txt",
    "output/10_complicated_2.txt"
};

int n;
Data *arrays;
char *target;

int solve();
int parse(char *target, char *current_id);
void print_data(Data d);

int main() {
    if (TEST) {
        for (int i = 0; i < NUMBER_FILES; i++) {
            printf("[DEBUG] INPUT FILE #%d\n", i + 1);

            FILE *fp;
            char line[LINE_LEN];

            if ((fp = fopen(INPUT_FILE[i], "r")) == NULL) {
                printf("[ERROR] Can't open the file %s\n", INPUT_FILE[i]);
                exit(1);
            }

            n = atoi(fgets(line, LINE_LEN, fp));

            arrays = (Data *)malloc(sizeof(Data) * n);

            for (int j = 0; j < n; j++) {
                Data d;
                char *token;

                fgets(line, LINE_LEN, fp);
                token = strtok(line, "[");
                
                d.id = (char *)malloc(strlen(token) + 1);
                strcpy(d.id, token);

                token = strtok(NULL, ".");
                d.start_range = atoi(token); 

                token = strtok(NULL, ".]");
                d.end_range = atoi(token);

                strtok(NULL, " ");

                d.elements = (int *)malloc(sizeof(int) * (d.end_range - d.start_range + 1));
                for (int k = d.start_range; k <= d.end_range; k++) {
                    token = strtok(NULL, " \n");
                    int offset = k - d.start_range;

                    *(d.elements + offset) = atoi(token);
                }
                *(arrays + j) = d;
            }

            fgets(line, LINE_LEN, fp);

            target = (char *)malloc(sizeof(char) * (strlen(line) + 1));
            strcpy(target, strtok(line, "\n"));

            int solution = solve();

            printf("[DEBUG] Solution: %d\n", solution);

            fclose(fp);

            if ((fp = fopen(OUTPUT_FILE[i], "r")) == NULL) {
                printf("[ERROR] Can't open the file %s\n", INPUT_FILE[i]);
                exit(1);
            }

            if (solution == atoi(fgets(line, LINE_LEN, fp)))
                printf("PASSED\n");
            else
                printf("FAILED\n");

            fclose(fp);
        }
    } else {
        scanf("%d", &n);
        fgetc(stdin);

        arrays = (Data *)malloc(sizeof(Data) * n);

        for (int i = 0; i < n; i++) {
            char assignment[1025];
            char *token;
            Data d;

            scanf("%[^\n]", assignment);
            fgetc(stdin);

            token = strtok(assignment, "[");
            d.id = (char *)malloc(strlen(token) + 1);
            strcpy(d.id, token);

            token = strtok(NULL, ".");
            d.start_range = atoi(token);

            token = strtok(NULL, ".]");
            d.end_range = atoi(token);

            strtok(NULL, " ");

            d.elements = (int *)malloc(sizeof(int) * (d.end_range - d.start_range + 1));

            for (int j = d.start_range; j <= d.end_range; j++) {
                token = strtok(NULL, " \n");
                int offset = j - d.start_range;

                *(d.elements + offset) = atoi(token);
            }
            *(arrays + i) = d;
        }
        char x[257];
        scanf("%[^\n]", x);
        
        target = (char *)malloc(sizeof(char) * (strlen(x) + 1));
        strcpy(target, strtok(x, "\n"));

        int solution = solve();

        printf("%d\n", solution);
    }

    return 0;
}

int solve() {
    return parse(target, ""); 
}

int parse(char *target, char *current_id) {
    int id = 0;
    int solution;

    for (int i = 0; i < strlen(target); i++) {
        if (target[i] == '[') {
            id = 1;
            break;
        }
        if (target[i] == ']') {
            id = 0;
            break;
        }
    }

    if (id) {
        // recursive call
        char *token = strtok(target, "[");
        current_id = (char *)malloc(sizeof(char) * strlen(token));
        strcpy(current_id, token);
        token = strtok(NULL, "\n");
        int index = parse(token, current_id);

        for (int i = 0; i < n; i++) {
            if (strcmp(current_id, arrays[i].id) == 0) {
                index = index - arrays[i].start_range;
                solution = arrays[i].elements[index];
                break;
            }
        }
    } else {
        char *token = strtok(target, "]");
        return atoi(token);

        for (int i = 0; i < n; i++) {
            if (strcmp(current_id, arrays[i].id) == 0) {
                int index = arrays[i].end_range + 1 - atoi(token);
                solution = arrays[i].elements[index];
                break;
            }
        }

    }
    return solution;
}

void print_data(Data d) {
    printf("[DEBUG] %s[%d .. %d] = [", d.id, d.start_range, d.end_range);

    for (int i = d.start_range; i <= d.end_range; i++) {
        int offset = i - d.start_range;
        printf(" %d", *(d.elements + offset));
    }
    printf(" ]\n");
}

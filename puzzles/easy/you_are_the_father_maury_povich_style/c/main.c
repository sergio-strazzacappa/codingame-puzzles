#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE  100

int num_chrom;
char mother_chrom_pairs[SIZE * 2];
char child_chrom_pairs[SIZE * 2];
int num_fathers;
char *fathers_name;
char *fathers_chrom;
int *possibles;

void parse_input();
void solve();
void clear();

int main() {
    parse_input();
    solve();

    return 0;
}

void parse_input() {
    char mother[501];
    scanf("%[^\n]", mother);
    fgetc(stdin);

    char *token;
    // skip the mother's name
    token = strtok(mother, ":");
    token = strtok(NULL, " ");

    int index = 0;
    num_chrom = 0;

    while (token != NULL) {
        num_chrom++;
        mother_chrom_pairs[index] = token[0];
        mother_chrom_pairs[index + 1] = token[1];
        index += 2;
        token = strtok(NULL, " \n");
    }

    char child[501];
    scanf("%[^\n]", child);

    // skip the child's name
    token = strtok(child, ":");
    token = strtok(NULL, " ");

    index = 0;

    while (token != NULL) {
        child_chrom_pairs[index] = token[0];
        child_chrom_pairs[index + 1] = token[1];
        index += 2;
        token = strtok(NULL, " \n");
    }

    scanf("%d", &num_fathers);
    fgetc(stdin);

    fathers_name = (char *)malloc(num_fathers * 100);
    fathers_chrom = (char *)malloc(num_fathers * sizeof(char) * num_chrom * 2);

    for (int i = 0; i < num_fathers; i++) {
        char father[501];
        scanf("%[^\n]", father);
        fgetc(stdin);

        token = strtok(father, ":");
        strcpy(fathers_name + 100 * i, father);

        token = strtok(NULL, " ");

        index = 0;

        while (token != NULL) {
            fathers_chrom[i * num_chrom * 2 + index] = token[0];
            fathers_chrom[i * num_chrom * 2 + index + 1] = token[1];
            index += 2;
            token = strtok(NULL, " \n");
        }
    }
}

void solve() {
    possibles = (int *)malloc(sizeof(int) * num_fathers);

    for (int i = 0; i < num_fathers; i++) {
        possibles[i] = 1;
    }

    for (int i = 0; i < num_chrom * 2; i += 2) {
        int j;
        int both = 0;
        if (child_chrom_pairs[i] == mother_chrom_pairs[i]) {
            j = 1;
        } else if (child_chrom_pairs[i] == mother_chrom_pairs[i + 1]){
            j = 1;
        } else {
            j = 0;
        }

        if ((child_chrom_pairs[i] == mother_chrom_pairs[i] &&
            child_chrom_pairs[i + 1] == mother_chrom_pairs[i + 1]) ||
            (child_chrom_pairs[i] == mother_chrom_pairs[i + 1] &&
            child_chrom_pairs[i + 1] == mother_chrom_pairs[i])) {
            both = 1;
        }

        for (int k = 0; k < num_fathers; k++) {
            if (!possibles[k])
                continue;
            if (fathers_chrom[k * num_chrom * 2 + i] == child_chrom_pairs[i + j])
                continue;
            if (fathers_chrom[k * num_chrom * 2 + i + 1] == child_chrom_pairs[i + j])
                continue;

            int l;
            if (j == 0)
                l = 1;
            else
                l = 0;

            if (both && fathers_chrom[k * num_chrom * 2 + i] == child_chrom_pairs[i + l])
                continue;
            if (both && fathers_chrom[k * num_chrom * 2 + i + 1] == child_chrom_pairs[i + l])
                continue;
            possibles[k] = 0;
        }
    }

    for (int i = 0; i < num_fathers; i++) {
        if (possibles[i]) {
            printf("%s, you are the father!\n", fathers_name + 100 * i);
            break;
        }
    }
}

void clear() {
    free(fathers_name);
    free(fathers_chrom);
    free(possibles);
}

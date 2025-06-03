#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct data {
    char *id;
    int start_range;
    int end_range;
    int *elements;
} Data;

int n;
Data *arrays;
char *target;

void init();
void solve();
int parse(char *target, char *current_id);
void print_data(Data d);

int main() {
    init();
    solve();

    return 0;
}

void init() {
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
}

void solve() {
    printf("%d\n", parse(target, ""));
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
    fprintf(stderr, "[DEBUG] %s[%d .. %d] = [",
        d.id, d.start_range, d.end_range);

    for (int i = d.start_range; i <= d.end_range; i++) {
        int offset = i - d.start_range;
        fprintf(stderr, " %d", *(d.elements + offset));
    }
    fprintf(stderr, " ]\n");
}

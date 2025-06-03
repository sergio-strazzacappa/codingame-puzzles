#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

int instructions;

typedef struct entry {
    char *key;
    char *value;
} Entry;

struct dictionary {
    Entry elements[100];
    int len;
} dict;

void solve(char instruction[]);
void set(char *arg);
void get(char *arg);
void exists(char *arg);
void keys();
void debug();

int main() {
    dict.len = 0;
    scanf("%d", &instructions);
    fgetc(stdin);

    for (int i = 0; i < instructions; i++) {
        char instruction[101];
        scanf("%[^\n]", instruction);
        fgetc(stdin);
        solve(instruction);
    }

    return 0;
}

void solve(char instruction[]) {
    char *token = strtok(instruction, " ");

    char *command = (char *)malloc(sizeof(char) * strlen(token));
    strcpy(command, token);

    token = strtok(NULL, "\n");
    if (strcmp(command, "SET") == 0)
        set(token);
    if (strcmp(command, "GET") == 0)
        get(token);
    if (strcmp(command, "EXISTS") == 0)
        exists(token);
    if (strcmp(command, "KEYS") == 0)
        keys();
}

void set(char *arg) {
    fprintf(stderr, "[DEBUG] SET %s\n", arg);

    bool key = true;
    char *token = strtok(arg, "= ");

    int index = -1;
    while (token != NULL) {
        if (key) {
            for (int i = 0; i < dict.len; i++) {
                if (strcmp(dict.elements[i].key, token) == 0) {
                    // update
                    index = i;
                    break;
                }
                index = -1;
            }
            if (index == -1) {
                Entry d;
                d.key = (char *)malloc(sizeof(char) * strlen(token));
                strcpy(d.key, token);
                dict.elements[dict.len++] = d;
            }
        } else {
            if (index == -1) {
                dict.elements[dict.len - 1].value =
                    (char *)malloc(sizeof(char) * strlen(token));
                strcpy(dict.elements[dict.len - 1].value, token);
            } else {
                dict.elements[index].value =
                    (char *)malloc(sizeof(char) * strlen(token));
                strcpy(dict.elements[index].value, token);
            }
        }
        key = !key;
        token = strtok(NULL, "= ");
    }
    debug();
}

void get(char *arg) {
    fprintf(stderr, "[DEBUG] GET %s\n", arg);

    char *token = strtok(arg, " ");

    while (token != NULL) {
        bool found = false;
        for (int i = 0; i < dict.len; i++) {
            if (strcmp(dict.elements[i].key, token) == 0) {
                // key found
                printf("%s", dict.elements[i].value);
                found = true;
                break;
            }
        }

        if (!found)
            printf("null");

        token = strtok(NULL, " ");

        if (token != NULL)
            printf(" ");
    }
    printf("\n");
}

void exists(char *arg) {
    fprintf(stderr, "[DEBUG] EXISTS %s\n", arg);

    char *token = strtok(arg, " ");

    while (token != NULL) {
        bool found = false;
        for (int i = 0; i < dict.len; i++) {
            if (strcmp(dict.elements[i].key, token) == 0) {
                // key found
                printf("true");
                found = true;
                break;
            }
        }
        token = strtok(NULL, " ");

        if (!found)
            printf("false");

        if (token != NULL)
            printf(" ");
    }
    printf("\n");
}

void keys() {
    fprintf(stderr, "[DEBUG] KEYS\n");

    if (dict.len == 0)
        printf("EMPTY");

    for (int i = 0; i < dict.len; i++) {
        printf("%s", dict.elements[i].key);

        if (i < dict.len - 1)
            printf(" ");
    }
    printf("\n");
}

void debug() {
    fprintf(stderr, "[DEBUG] Dictionary: { ");

    for (int i = 0; i < dict.len; i++) {
        fprintf(stderr, "%s:%s", dict.elements[i].key, dict.elements[i].value);

        if (i < dict.len - 1)
            fprintf(stderr, ", ");
    }
    fprintf(stderr, " }\n");
}

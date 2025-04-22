#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define EXT_MAX_SIZE        10
#define MIME_TYPE_MAX_SIZE  50
#define FNAME_MAX_SIZE      256
#define MAX_ELEM            10000

struct mime_data {
    char extension[EXT_MAX_SIZE + 1];
    char mime_type[MIME_TYPE_MAX_SIZE + 1];
};

int n;
int q;
struct mime_data table[MAX_ELEM];
int last_index;

void solve(char fname[]);
int search(char ext[]);
void print_table();

int main() {
    last_index = 0;

    scanf("%d%d", &n, &q);

    for (int i = 0; i < n; i++) {
        struct mime_data m;
        scanf("%s%s", m.extension, m.mime_type);
        fgetc(stdin);

        // change case to lowercase if needed
        for (int j = 0; m.extension[j] != '\0'; j++) {
            if (isupper(m.extension[j]))
                m.extension[j] += 'a' - 'A';
        }

        table[last_index++] = m;
    }

    for (int i = 0; i < q; i++) {
        char fname[FNAME_MAX_SIZE + 1];
        scanf("%s", fname);
        fgetc(stdin);;

        solve(fname);
    }

    //print_table();
    return 0;
}

void solve(char fname[]) {
    //fprintf(stderr, "[DEBUG] Solve(%s)\n", fname);

    char *ext = (char *)malloc(sizeof(char) * EXT_MAX_SIZE + 1);
    int in_ext = 0;
    int j = 0;

    for (int i = 0; i < strlen(fname); i++) {
        if (fname[i] == '.') {
            in_ext = 1;
            j = 0;
            continue;
        }
        if (in_ext) {
            ext[j++] = fname[i];
        }
    }
    ext[j] = '\0';

    if (strlen(ext) > 0) {
        // change case to lowercase if needed
        for (int k = 0; ext[k] != '\0'; k++) {
            if (isupper(ext[k]))
                ext[k] += 'a' - 'A';
        }
    }

    if (strlen(ext) == 0) {
        printf("UNKNOWN\n");
    } else {
        int index = search(ext);

        if (index == -1)
            printf("UNKNOWN\n");
        else
            printf("%s\n", table[index].mime_type);
    }

    free(ext);
}

int search(char ext[]) {
    for (int i = 0; i < last_index; i++) {
        if (strcmp(ext, table[i].extension) == 0) {
            return i;
        }
    }
    return -1;
}

void print_table() {
    fprintf(stderr, "[DEBUG] ---------------\n");
    for (int i = 0; i < last_index; i++) {
        fprintf(stderr, "[DEBUG] (%s, %s)\n",
            table[i].extension, table[i].mime_type);
    }
    fprintf(stderr, "[DEBUG] ---------------\n");
}

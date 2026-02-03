#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define EXT_MAX_SIZE        10
#define MIME_TYPE_MAX_SIZE  50
#define FNAME_MAX_SIZE      256
#define MAX_ELEM            10000

typedef struct Mime_data {
    char extension[EXT_MAX_SIZE + 1];
    char mime_type[MIME_TYPE_MAX_SIZE + 1];
} Mime_data;

int cmp(const void *a, const void *b);
void solve(Mime_data table[], size_t table_size, char fname[]);
int search(Mime_data table[], size_t table_size, char ext[]);
void print_table(Mime_data table[], size_t table_size);

int main() {
    Mime_data table[MAX_ELEM];
    size_t table_size = 0;
    int n;
    int q;
    scanf("%d%d", &n, &q);

    for (int i = 0; i < n; i++) {
        Mime_data m;
        scanf("%s%s", m.extension, m.mime_type);
        fgetc(stdin);

        // change case to lowercase if needed
        for (int j = 0; m.extension[j] != '\0'; j++) {
            if (isupper(m.extension[j]))
                m.extension[j] += 'a' - 'A';
        }

        table[table_size++] = m;
    }

    qsort(table, table_size, sizeof(Mime_data), cmp);

    for (int i = 0; i < q; i++) {
        char fname[FNAME_MAX_SIZE + 1];
        scanf("%s", fname);
        fgetc(stdin);

        solve(table, table_size, fname);
    }

    return 0;
}

int cmp(const void *a, const void *b) {
    return strcmp(((Mime_data *)a)->extension, ((Mime_data *)b)->extension);
}

void solve(Mime_data table[], size_t table_size,  char fname[]) {
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
        int index = search(table, table_size, ext);

        if (index == -1)
            printf("UNKNOWN\n");
        else
            printf("%s\n", table[index].mime_type);
    }

    free(ext);
}

int search(Mime_data table[], size_t table_size, char ext[]) {
    int low = 0;
    int mid = 0;
    int high = table_size - 1;

    while (low <= high) {
        mid = low + (high - low) / 2;
        if (strcmp(ext, table[mid].extension) > 0) {
            low = mid + 1;
        } else if (strcmp(ext, table[mid].extension) < 0) {
            high = mid - 1;
        } else {
            return mid;
        }
    }
    return -1;
}

void print_table(Mime_data table[], size_t table_size) {
    fprintf(stderr, "[DEBUG] ---------------\n");
    for (int i = 0; i < table_size; i++) {
        fprintf(stderr, "[DEBUG] (%s, %s)\n",
            table[i].extension, table[i].mime_type);
    }
    fprintf(stderr, "[DEBUG] ---------------\n");
}

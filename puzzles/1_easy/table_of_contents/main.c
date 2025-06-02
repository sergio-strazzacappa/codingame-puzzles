#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Entry {
    int level;
    char* title;
    char* page;
};

int length_of_line;

void debug_entry(struct Entry e) {
    fprintf(stderr, "Debuging Entry\n");
    fprintf(stderr, "--------------\n");
    fprintf(stderr, "Level: %d\n", e.level);
    fprintf(stderr, "Title: %s\n", e.title);
    fprintf(stderr, "Page: %s\n\n", e.page);
}

int number_of_digits(int n) {
    int digits = 0;

    while (n > 0) {
        n /= 10;
        digits++;
    }
    return digits;
}

void format_output(struct Entry e, int section_numbers[]) {
    int indent = e.level * 4;
    int current_length = 0;

    for (int i = 0; i < indent; i++) {
        printf(" ");
        current_length++;
    }

    printf("%d ", section_numbers[e.level]);
    current_length += number_of_digits(section_numbers[e.level]) + 1;
    printf("%s", e.title);
    current_length += strlen(e.title);
    int dots = length_of_line - current_length - strlen(e.page);

    for (int i = 0; i < dots; i++) {
        printf(".");
    }
    printf("%s\n", e.page);
}

void solve(char* entry, int section_numbers[], int* prev_level, int n) {
    struct Entry e = {0, "", ""};
    int size = strlen(entry);
    int j = 0;
    char* title = "";
    char* page = "";
    int title_completed = 0;

    for (int i = 0; i < size; i++) {
        if (entry[i] == '>') {
            e.level++;
            continue;
        }

        if (entry[i] != ' ' && !title_completed) {
            title = malloc(strlen(title) + 1);

            for (int k = 0; k < j; k++) {
                title[k] = e.title[k];
            }

            title[j] = entry[i];
            e.title = title;
            j++;
            continue;
        }

        if (entry[i] == ' ') {
            title_completed = 1;
            j = 0;
            page = malloc(strlen(page) + 1);
            continue;
        }

        if (title_completed) {
            page[j] = entry[i];
            e.page = page;
            j++;
        }
    }

    if (e.level < *prev_level) {
        for (int i = e.level; i < n; i++) {
            section_numbers[i + 1] = 0;
        }
    }

    section_numbers[e.level]++;
    *prev_level = e.level;
    format_output(e, section_numbers);
}

int main() {
    int n;
    scanf("%d%d", &length_of_line, &n);
    fgetc(stdin);

    int section_numbers[n];
    int prev_level = -1;

    for (int i = 0; i < n; i++) {
        section_numbers[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        char entry[51];
        scanf("%[^\n]", entry);
        fgetc(stdin);

        solve(entry, section_numbers, &prev_level, n);
    }

    return 0;
}
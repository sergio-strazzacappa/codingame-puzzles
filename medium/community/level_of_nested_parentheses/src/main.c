#include <stdio.h>
#include <string.h>
#include <stdbool.h>

struct parens {
    char symbol;
    int pos;
    int level;
};

void solve(char f[]);

int main() {
    char f[101] = "";
    scanf("%[^\n]", f);

    solve(f);

    return 0;
}

void solve(char f[]) {
    struct parens parens_list[100];
    size_t parens_size = 0;
    size_t len = strlen(f);
    int level = 0;
    int lines = 1;

    for (int i = 0; i < len; i++) {
        if (f[i] != '(' && f[i] != ')')
            continue;
        if (f[i] == '(')
            level++;

        if (level > lines - 1)
            lines++;

        struct parens p = {
            .symbol = f[i],
            .pos = i,
            .level = level
        };

        parens_list[parens_size++] = p;

        if (f[i] == ')')
            level--;
    }

    if (lines > 1)
        lines += 2;

    // Print the output
    for (int line = 0; line < lines; line++) {
        if (line == 0) {
            // First line, the original string
            printf("%s\n", f);
            continue;
        }

        // Second line, ^ below each parens
        if (line == 1) {
            for (int i = 0; i < len; i++) {
                if (f[i] == '(' || f[i] == ')')
                    putchar('^');
                else
                    putchar (' ');
            }

            putchar('\n');
            continue;
        }

        int index = 0;
        int current_level = 0;
        bool open = false;

        for (int i = 0; i < len; i++) {
            // calculate the max sublevel nested inside the current parens
            int max_sublevel = 0;
            int current_index = index;
            current_level = parens_list[index].level;
            max_sublevel = parens_list[index].level;

            if (f[i] == '(') {
                index++;
                for (int j = index; j < parens_size; j++) {
                    if (parens_list[j].level == parens_list[current_index].level && parens_list[j].symbol == ')')
                        break;
                    if (parens_list[j].level > max_sublevel)
                        max_sublevel = parens_list[j].level;
                }
            }

            if (f[i] == ')') {
                index++;
                for (int j = index - 2; j > 0; j--) {
                    if (parens_list[j].level == parens_list[current_index].level && parens_list[j].symbol == '(')
                        break;
                    if (parens_list[j].level > max_sublevel)
                        max_sublevel = parens_list[j].level;
                }
            }

            // print the line
            if (f[i] == '(' || f[i] == ')') {
                if (line <= max_sublevel - current_level + 2)
                    putchar('|');
                else if (line == max_sublevel - current_level + 3) {
                    putchar(current_level + '0');
                    if (f[i] == '(')
                        open = true;
                    else
                        open = false;
                } else if (!open)
                    putchar(' ');
                else
                    putchar('-');
            } else if (open)
                putchar('-');
             else
                putchar (' ');
        }
        putchar('\n');
    }
}

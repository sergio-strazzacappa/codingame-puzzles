#include <stdio.h>
#include <string.h>

void solve(char typed_keys[]);
void write_char(char c, char text[], int cursor_position);
void remove_char(char text[], int cursor_position);

int main() {
    char typed_keys[81];
    scanf("%[^\n]", typed_keys);
    solve(typed_keys);

    return 0;
}

void solve(char typed_keys[]) {
    char text[81] = "\0";
    int cursor_position = 0;

    for (int i = 0; i < strlen(typed_keys); i++) {
        char c = typed_keys[i];

        if (c == '<') {
            cursor_position--;

            if (cursor_position < 0)
                cursor_position = 0;

            continue;
        }
        if (c == '>') {
            cursor_position++;

            if (cursor_position > strlen(text))
                cursor_position = strlen(text);

            continue;
        }
        if (c == '-') {
            remove_char(text, cursor_position - 1);
            cursor_position--;

            if (cursor_position < 0)
                cursor_position = 0;

            continue;
        }

        // the input is a character
        write_char(c, text, cursor_position);
        cursor_position++;
    }
    printf("%s\n", text);
}

// write the char c at the cursor_position of the text
void write_char(char c, char text[], int cursor_position) {
    for (int i = strlen(text) + 1; i >= cursor_position; i--)
        text[i] = text[i - 1];
    text[cursor_position] = c;
}

// remove the char at cursor_position from the text
void remove_char(char text[], int cursor_position) {
    for (int i = cursor_position; i < strlen(text) + 1; i++)
        text[i] = text[i + 1];
}

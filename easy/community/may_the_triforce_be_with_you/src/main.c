#include <stdio.h>

void solve(int n);

int main() {
    int n;
    scanf("%d", &n);

    solve(n);

    return 0;
}

void solve(int n) {
    // draw the top triangle
    int pos = 1;
    putchar('.');
    for (int line = 0; line < n; line++) {
        int half = 2 * n - 1;

        for (int spaces = pos; spaces < half - line; spaces++)
            putchar(' ');
        for (int symbol = 0; symbol < (line * 2) + 1; symbol++)
            putchar('*');

        putchar('\n');
        pos = 0;
    }

    // draw the two triangles of the botom
    for (int line = 0; line < n; line++) {
        for (int spaces = 0; spaces < n - 1 - line; spaces++)
            putchar(' ');
        for (int symbol = 0; symbol < line * 2 + 1; symbol++)
            putchar('*');
        for (int spaces = 0; spaces < (2 * n) - (line * 2) - 1; spaces++)
            putchar(' ');
        for (int symbol = 0; symbol < line * 2 + 1; symbol++)
            putchar('*');

        putchar('\n');
    }
}

#include <stdio.h>

int height;
int width;
int number_of_shelves;

void solve();
void draw_top();
void build_shelves();

int main() {
    scanf("%d%d%d", &height, &width, &number_of_shelves);
    solve();

    return 0;
}

void solve() {
    draw_top();
    build_shelves();
}

void draw_top() {
    int mid = width / 2;

    // draw the left half of the top
    for (int i = 0; i < mid; i++) {
        printf("%c", '/');
    }

    // if the width is odd, draw the mid char
    if  (width % 2 == 1) {
        printf("%c", '^');
    }

    // draw the right half of the top
    for (int i = 0; i < mid; i++) {
        printf("%c", '\\');
    }

    printf("\n");
    height--;
}

void build_shelves() {
    int larger_shelves = height % number_of_shelves;

    for (int i = 0; i < number_of_shelves; i++) {
        int current_height = height / number_of_shelves;

        // check if this shelf should be larger
        if (number_of_shelves - i <= larger_shelves) {
            current_height++;
        }

        for (int j = 0; j < current_height; j++) {
            printf("%c", '|');

            for (int k = 0; k < width - 2; k++) {
                if (j == current_height - 1) {
                    printf("%c", '_');
                } else {
                    printf("%c", ' ');
                }
            }
            printf("%c\n", '|');
        }
    }
}

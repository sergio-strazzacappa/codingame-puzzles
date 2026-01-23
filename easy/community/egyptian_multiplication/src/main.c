#include <stdio.h>

int a;
int b;

void solve();
void swap();

int main() {
    scanf("%d%d", &a, &b);
    solve();

    return 0;
}

void solve() {
    if (a < b)
        swap();

    printf("%d * %d\n", a, b);

    int result = a * b;
    int terms[100];
    size_t terms_size = 0;

    while (b > 0) {
        if (b % 2 == 0) {
            a *= 2;
            b /= 2;
        } else {
            terms[terms_size++] = a;
            b--;
        }

        // print a step
        printf("= %d * %d", a, b);

        for (int i = 0; i < terms_size; i++) {
            printf(" + %d", terms[i]);
        }
        printf("\n");
    }

    // print the final result
    printf("= %d\n", result);
}

// swap the values of a and b, so a is always greater than b
void swap() {
    int tmp = a;
    a = b;
    b = tmp;
}

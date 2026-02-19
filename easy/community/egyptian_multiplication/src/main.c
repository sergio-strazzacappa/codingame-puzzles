#include <stdio.h>

void solve(int a, int b);
void swap(int *x, int *y);

int main() {
    int a, b;
    scanf("%d%d", &a, &b);
    solve(a, b);

    return 0;
}

void solve(int a, int b) {
    if (a < b)
        swap(&a, &b);

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

// swap the values of x and y
void swap(int *x, int *y) {
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

#include <stdio.h>

int n;

void init();
void solve();

int main() {
    init();
    solve();

    return 0;
}

void init() {
    scanf("%d", &n);
}

void solve() {
    long sum = 1;

    int elem = 1;
    int factor = n - 1;

    while (factor > 0) {
        for (int i = 0; i < 4; i++) {
            elem += factor;
            sum += elem;
        }
        factor -= 2;
    } 

    if (n % 2 == 0)
        sum -= elem;

    printf("%ld\n", sum);
}

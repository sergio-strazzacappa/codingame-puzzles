#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int plate[5]; // [a, b, cde, f, g]
int n;

void init();
void solve();
int solve_num(int *num, int n, int mod);

int main() {
    init();
    solve();

    return 0;
}

void init() {
    char x[10];
    scanf("%[^\n]%d", x, &n);

    char num[] = {x[3], x[4], x[5], '\0'};

    plate[0] = x[0] - 'A';
    plate[1] = x[1] - 'A';
    plate[2] = atoi(num);
    plate[3] = x[7] - 'A';
    plate[4] = x[8] - 'A';
}

void solve() {
    int it = solve_num(&plate[2], n, 1000);
    it = solve_num(&plate[4], it, 27);
    it = solve_num(&plate[3], it, 27);
    it = solve_num(&plate[1], it, 27);
    it = solve_num(&plate[0], it, 27);

    printf("%c%c-%03d-%c%c\n",
        plate[0] + 'A', plate[1] + 'A',
        plate[2],
        plate[3] + 'A', plate[4] + 'A');
}

int solve_num(int *num, int n, int mod) {
    int m = (*num + n) % mod;
    int it = (*num + n) / mod;
    int total_it = it;
    *num = m + it;

    while ((*num) > (mod - 1)) {
        m = *num % mod;
        it = *num / mod;
        *num = m + it;
        total_it += it;

        if (*num == 0)
            (*num)++;
    }
    return total_it;
}

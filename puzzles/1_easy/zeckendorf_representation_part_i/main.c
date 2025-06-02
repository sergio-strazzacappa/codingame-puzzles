#include <stdio.h>

void input(void);
void solve(void);
long long fib(void);

long long number;

int main() {
    input();
    solve();

    return 0;
}

void input() {
    scanf("%lld", &number);
}

void solve() {
    while (number != 0) {
        long long n = fib();
        printf("%lld", n);
        number -= n;
        
        if (number != 0) {
            printf("+");
        }
    }
}

long long fib() {
    long long first = 0;
    long long second = 1;
    long long next = 0;

    while (next < number) {
        next = first + second;

        if (next > number) {
            next -= first;
            break;
        }
        first = second;
        second = next;
    }
    return next;
}
#include <stdio.h>
#include <math.h>

int solve(int n, int k);
int left_most_digit(int n);
int number_of_digits(int n);
int bruteforce(int n, int k);

int main() {
    int solution, n, k;

    scanf("%d %d", &n, &k);

    solution = solve(n, k);
    printf("%d\n", solution);

    return 0;
}

int solve(int n, int k) {
    if (n < 10 && n < k)
        return 0;

    if (n < 10 && n >= k)
        return 1;

    int left_most = left_most_digit(n);
    int d = number_of_digits(n);
    int first = left_most * (d - 1) * pow(10, d - 2);

    n -= left_most * pow(10, d - 1);

    if (left_most < k)
        return (first + solve(n, k));
    else if (left_most > k)
        return (first + pow(10, number_of_digits(n)) + solve(n, k));
    else
        return (first + n + 1 + solve(n, k));
}

// return the left most digit of n
int left_most_digit(int n) {
    while (1) {
        n /= 10;

        if (n < 10)
            return n;
    }
    return -1;
}

// return the number of digits of n
int number_of_digits(int n) {
    int d = 0;

    while (n > 0) {
        n /= 10;
        d++;
    }

    return d;
}

// brutefoce algorithm times out in tests 6, 7, 8, and 9
int bruteforce(int n, int k) {
    int solution = 0;

    for (int i = 0; i <= n; i++) {
        int number = i;

        fprintf(stderr, "[DEBUG] Current number %d\n", number);

        while (number > 0) {
            if (k == number % 10)
                solution++;
            number /= 10;
        }
    }
    return solution;
}

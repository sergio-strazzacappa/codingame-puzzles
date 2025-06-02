#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

long n;

void solve();
bool check_factors(int a, int b);
void to_date(long number, int *day, int *month, int *year); 

int main() {
    scanf("%ld", &n);
    solve();

    return 0;
}

void solve() {
    int a, b;
    long number = n;
    int digits = 0;
    
    // number of digits of n
    while (number > 0) {
        number /= 10;
        digits++;
    }

    int current_digit = 1;
    while (current_digit < digits) {
        number = n;
        a = 0;
        b = 0;

        int i = 0;
        while (number > 0) {
            if (i < current_digit)
                a += number % 10 * pow(10, i);
            else
                b += number % 10 * pow(10, i - current_digit);

            i++;
            number /= 10;
        }

        if (check_factors(a, b)) {
            int day, month, year;
            long p = a * b;
            to_date(p, &day, &month, &year);

            if (day >= 1 && day <= 31 && month >= 1 && month <= 12 && year <= 9999) {
                printf("%04d-%02d-%02d\n", year, month, day);
                break;
            }
        }
        current_digit++;
    }
}

bool check_factors(int a, int b) {
    long product = a * b;

    int divisors[10000];
    int divisors_index = 0;

    int i = 2;

    while (i <= sqrt(product)) {
        if (product % i == 0)
            divisors[divisors_index++] = i; 
        i++;
    }

    for (int i = 0; i < divisors_index; i++) {
        for (int j = 0; j < divisors_index; j++) {
            long p = (long)divisors[i] * divisors[j];
            if (p == product && abs(divisors[i] - divisors[j]) < abs(a - b))
                return false;
        }
    }

    return true;
}

void to_date(long number, int *day, int *month, int *year) {
    *day     = 0;
    *month   = 0;
    *year    = 0;

    int i = 0;
    while (number > 0) {
        if (i < 2)      *day += number % 10 * pow(10, i);
        else if (i < 4) *month += number % 10 * pow(10, i - 2);
        else            *year += number % 10 * pow(10, i - 4);

        i++;
        number /= 10;
    }
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct Date {
    int day;
    int month;
    int year;
} begin, end;

const int DAYS_PER_MONTH[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

void init();
void solve();
bool is_leap_year(int year);
int number_of_leap_years(int year1, int year2);

int main() {
    init();
    solve();

    return 0;
}

void init() {
    char b[11];
    char e[11];

    scanf("%s", b);
    scanf("%s", e);

    char *token = strtok(b, ".");
    begin.day = atoi(token);

    token = strtok(NULL, ".");
    begin.month = atoi(token);

    token = strtok(NULL, ".");
    begin.year = atoi(token);

    token = strtok(e, ".");
    end.day = atoi(token);

    token = strtok(NULL, ".");
    end.month = atoi(token);

    token = strtok(NULL, ".");
    end.year = atoi(token);
}

void solve() {
    int year_diff, month_diff, total_days;

    // calculate the years diff and months diff
    year_diff = end.year - begin.year;

    if (begin.month > end.month) {
        year_diff--;
        month_diff = 12 - (begin.month - end.month);
    } else {
        month_diff = end.month - begin.month;
    }

    if (begin.day > end.day)
        month_diff--;

    // calculate the total days
    total_days =
        (end.year - begin.year) * 365 +
        number_of_leap_years(begin.year, end.year);

    if (begin.month > end.month) {
        total_days -= 365;

        for (int m = begin.month - 1; m < 12 + end.month - 1; m++) {
            total_days += DAYS_PER_MONTH[m % 12];

            if (m == 1 && is_leap_year(end.year))
                total_days++;
        }
    }

    for (int m = begin.month - 1; m < end.month - 1; m++) {
        total_days += DAYS_PER_MONTH[m];
    }

    if (begin.day > end.day) {
        total_days -= (DAYS_PER_MONTH[end.month - 1]);
        total_days += (DAYS_PER_MONTH[end.month - 1] - begin.day);
        total_days += end.day;
    } else {
        total_days += end.day - begin.day;
    }

    if (is_leap_year(begin.year) && begin.month > 2)
        total_days--;

    if (is_leap_year(end.year) && end.month < 3)
        total_days--;

    // print the result
    if (year_diff > 0)
        printf("%d year%s, ", year_diff, year_diff > 1 ? "s" : "");
    if (month_diff > 0)
        printf("%d month%s, ", month_diff, month_diff > 1 ? "s" : "");
    printf("total %d days\n", total_days);
}

bool is_leap_year(int year) {
    return ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
}

int number_of_leap_years(int year1, int year2) {
    return
        (year2 / 4 - (year1 - 1) / 4) -
        (year2 / 100 - (year1 - 1) / 100) +
        (year2 / 400 - (year1 - 1) / 400);
}

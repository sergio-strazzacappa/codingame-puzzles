#include <stdio.h>
#include <string.h>

typedef struct signal {
    char name[9];
    char signal[65];
} Signal;

int n;
int m;
Signal signals[4];

void parse_input();
void solve(char output_name[], char type[], char input_name_1[],
    char input_name_2[]);

int main() {
    parse_input();

    for (int i = 0; i < m; i++) {
        char output_name[9];
        char type[9];
        char input_name_1[9];
        char input_name_2[9];

        scanf("%s%s%s%s", output_name, type, input_name_1, input_name_2);

        solve(output_name, type, input_name_1, input_name_2);
    }

    return 0;
}

void parse_input() {
    scanf("%d%d", &n, &m);

    for (int i = 0; i < n; i++) {
        Signal s;
        scanf("%s%s", s.name, s.signal);
        signals[i] = s;
    }
}

void solve(char output_name[], char type[], char input_name_1[], char input_name_2[]) {
    Signal s1, s2;

    for (int i = 0; i < n; i++) {
        if (strcmp(input_name_1, signals[i].name) == 0) {
            s1 = signals[i];
        }
        if (strcmp(input_name_2, signals[i].name) == 0) {
            s2 = signals[i];
        }
    }

    char output_signal[65];
    int index = 0;

    for (int i = 0; i < strlen(s1.signal); i++) {
        int op1, op2;

        if (s1.signal[i] == '_')
            op1 = 0;
        else
            op1 = 1;
        if (s2.signal[i] == '_')
            op2 = 0;
        else
            op2 = 1;

        if (strcmp(type, "AND") == 0) {
            int res = op1 & op2;
            if (res == 0)
                output_signal[index++] = '_';
            else
                output_signal[index++] = '-';
        }

        if (strcmp(type, "OR") == 0) {
            int res = op1 | op2;
            if (res == 0)
                output_signal[index++] = '_';
            else
                output_signal[index++] = '-';
        }

        if (strcmp(type, "XOR") == 0) {
            int res = op1 ^ op2;
            if (res == 0)
                output_signal[index++] = '_';
            else
                output_signal[index++] = '-';
        }

        if (strcmp(type, "NAND") == 0) {
            int res = !(op1 & op2);
            if (res == 0)
                output_signal[index++] = '_';
            else
                output_signal[index++] = '-';

        }

        if (strcmp(type, "NOR") == 0) {
            int res = !(op1 | op2);
            if (res == 0)
                output_signal[index++] = '_';
            else
                output_signal[index++] = '-';

        }

        if (strcmp(type, "NXOR") == 0) {
            int res = !(op1 ^ op2);
            if (res == 0)
                output_signal[index++] = '_';
            else
                output_signal[index++] = '-';

        }
    }

    output_signal[index] = '\0';

    printf("%s %s\n", output_name, output_signal);
}

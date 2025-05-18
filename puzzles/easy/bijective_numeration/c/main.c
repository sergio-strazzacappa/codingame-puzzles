#include <stdio.h>
#include <string.h>
#include <math.h>

int to_decimal(char decimary[]);
char *to_decimary(int decimal);
void invert(char string[]);

int main() {
    int count;
    scanf("%d", &count);

    int decimal_sum = 0;

    for (int i = 0; i < count; i++) {
        char decimary[10];
        scanf("%s", decimary);

        decimal_sum += to_decimal(decimary);
    }

    printf("%s\n", to_decimary(decimal_sum));

    return 0;
}

// convert a decimary number to its equivalent decimal number
int to_decimal(char decimary[]) {
    int decimal = 0;

    for (int i = strlen(decimary) - 1; i >= 0; i--) {
        int value = decimary[i] - '0';

        if (decimary[i] == 'A')
            value = 10;

        decimal += value * pow(10, strlen(decimary) - i - 1);
    }
    
    return decimal;
}

// convert a decimal number to its equivalent decimary number
char *to_decimary(int decimal) {
    static char decimary[11];
    int index = 0;
    
    while (decimal > 0) {
        int dig = decimal % 10;
        decimal /= 10;

        if (dig != 0) {
            decimary[index++] = dig + '0';
        } else {
            decimary[index++] = 'A';
            decimal--;
        }
    }

    decimary[index++] = '\0';
    invert(decimary);

    return decimary;
}

// invert a string
void invert(char string[]) {
    char tmp[11];
    strcpy(tmp, string);

    for (int i = strlen(tmp) - 1; i >= 0; i--)
        string[strlen(string) - i - 1] = tmp[i];

    string[strlen(string)] = '\0';
}

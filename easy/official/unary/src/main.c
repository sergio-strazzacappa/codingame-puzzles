#include <stdio.h>
#include <string.h>

void solve(char message[]);
void to_bin(char c, char binary[]);

int main() {
    char message[101];
    scanf("%[^\n]", message);

    solve(message);

    return 0;
}

void solve(char message[]) {
    char binary_message[1000] = "";
    char binary[8];

    for (int i = 0; i < strlen(message); i++) {
        to_bin(message[i], binary);
        strcat(binary_message, binary);
    }

    char last = '-';
    char encoded_message[1000] = "";
    int i = 0;

    for (int j = 0; j < strlen(binary_message); j++) {
        char current = binary_message[j];

        if (current == last) {
            encoded_message[i++] = '0';
        } else if (last == '-') {
            if (current == '0') {
                encoded_message[i++] = '0';
                encoded_message[i++] = '0';
                encoded_message[i++] = ' ';
                encoded_message[i++] = '0';
            } else {
                encoded_message[i++] = '0';
                encoded_message[i++] = ' ';
                encoded_message[i++] = '0';
            }
        } else {
            if (current == '0') {
                encoded_message[i++] = ' ';
                encoded_message[i++] = '0';
                encoded_message[i++] = '0';
                encoded_message[i++] = ' ';
                encoded_message[i++] = '0';
            } else {
                encoded_message[i++] = ' ';
                encoded_message[i++] = '0';
                encoded_message[i++] = ' ';
                encoded_message[i++] = '0';
            }
        }
        last = current;
    }

    encoded_message[i] = '\0';
    printf("%s\n", encoded_message);
}

void to_bin(char c, char binary[]) {
    int i = 0;

    while (c > 0) {
        binary[i++] = (c % 2) + '0';
        c /= 2;
    }
    binary[i] = '\0';

    // complete up to 7 bits with zeros
    while (strlen(binary) < 7) {
        binary[i++] = '0';
        binary[i] = '\0';
    }

    // revert the string
    for (int i = 0; i < strlen(binary) / 2; i++) {
        char tmp = binary[strlen(binary) - i - 1];
        binary[strlen(binary) - i - 1] = binary[i];
        binary[i] = tmp;
    }
}

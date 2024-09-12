#include <stdio.h>
#include <string.h>

void encode(char msg[], int n, char rotor1[], char rotor2[], char rotor3[]);
void decode(char msg[], int n, char rotor1[], char rotor2[], char rotor3[]);

int main() {
    char operation[257];
    scanf("%[^\n]", operation);

    int pseudo_random_number;
    scanf("%d", &pseudo_random_number);
    fgetc(stdin);

    char rotor1[28], rotor2[28], rotor3[28];

    scanf("%[^\n]", rotor1);
    fgetc(stdin);

    scanf("%[^\n]", rotor2);
    fgetc(stdin);

    scanf("%[^\n]", rotor3);
    fgetc(stdin);

    char message[1025];
    scanf("%[^\n]", message);

    if (strcmp(operation, "ENCODE") == 0) {
        encode(message, pseudo_random_number, rotor1, rotor2, rotor3);
    } else if (strcmp(operation, "DECODE") == 0) {
        decode(message, pseudo_random_number, rotor1, rotor2, rotor3);
    } else {
        fprintf(stderr, "[ERROR] Error processing the operation\n");
    }

    return 0;
}

void encode(char msg[], int n, char rotor1[], char rotor2[], char rotor3[]) {
    fprintf(stderr, "[DEBUG] Encode\n");
    fprintf(stderr, "[DEBUG] Message is: [ %s ]\n", msg);
    fprintf(stderr, "[DEBUG] Shift: %d\n", n);
    fprintf(stderr, "[DEBUG] Rotor 1: %s\n", rotor1);
    fprintf(stderr, "[DEBUG] Rotor 2: %s\n", rotor2);
    fprintf(stderr, "[DEBUG] Rotor 3: %s\n", rotor3);

    for (int i = 0; i < strlen(msg); i++) {
        // shift
        int c = msg[i] + n;

        while (c > 'Z') {
            c = 'A' + c - 'Z' - 1; 
        }

        msg[i] = c;
        n++;

        // rotor 1
        msg[i] = rotor1[msg[i] - 'A'];

        // rotor 2
        msg[i] = rotor2[msg[i] - 'A'];

        // rotor 3
        msg[i] = rotor3[msg[i] - 'A'];
    }

    fprintf(stderr, "[DEBUG] Message is: [ %s ]\n", msg);

    printf("%s\n", msg);
}

void decode(char msg[], int n, char rotor1[], char rotor2[], char rotor3[]) {
    fprintf(stderr, "[DEBUG] Decode\n");
    fprintf(stderr, "[DEBUG] Message is: [ %s ]\n", msg);
    fprintf(stderr, "[DEBUG] Shift: %d\n", n);
    fprintf(stderr, "[DEBUG] Rotor 1: %s\n", rotor1);
    fprintf(stderr, "[DEBUG] Rotor 2: %s\n", rotor2);
    fprintf(stderr, "[DEBUG] Rotor 3: %s\n", rotor3);

    for (int i = 0; i < strlen(msg); i++) {
        // rotor 3
        for (int j = 0; j < strlen(rotor3); j++) {
            if (rotor3[j] == msg[i]) {
                msg[i] = 'A' + j;
                break;
            }
        }

        // rotor 2
        for (int j = 0; j < strlen(rotor2); j++) {
            if (rotor2[j] == msg[i]) {
                msg[i] = 'A' + j;
                break;
            }
        }

        // rotor 1
        for (int j = 0; j < strlen(rotor1); j++) {
            if (rotor1[j] == msg[i]) {
                msg[i] = 'A' + j;
                break;
            }
        }

        // shift
        int c = msg[i] - n;

        while (c < 'A') {
            c = 'Z' - ('A' - c - 1);
        }

        msg[i] = c;
        n++;
    }

    fprintf(stderr, "[DEBUG] Message is: [ %s ]\n", msg);

    printf("%s\n", msg);
}
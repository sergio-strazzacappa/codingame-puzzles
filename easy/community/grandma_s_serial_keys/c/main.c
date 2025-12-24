#include <stdio.h>
#include <string.h>

void solve(char username[]);
int get_seed(char username[]);
int get_first_segment(int seed);
int get_second_segment(int seed);
int get_third_segment(char username[]);
int get_fourth_segment(int segments[]);

int main() {
    char username[1001] = "";
    scanf("%[^\n]", username);

    solve(username);

    return 0;
}

void solve(char username[]) {
    fprintf(stderr, "[DEBUG] Call solve(%s)\n", username);

    int seed = get_seed(username);

    fprintf(stderr, "[DEBUG] Seed = %d\n", seed);

    int segments[4]; 

    segments[0] = get_first_segment(seed);
    segments[1] = get_second_segment(seed);
    segments[2] = get_third_segment(username);
    segments[3] = get_fourth_segment(segments);

    fprintf(stderr, "[DEBUG] First segment = %d\n", segments[0]);
    fprintf(stderr, "[DEBUG] Second segment = %d\n", segments[1]);
    fprintf(stderr, "[DEBUG] Third segment = %d\n", segments[2]);
    fprintf(stderr, "[DEBUG] Fourth segment = %d\n", segments[3]);

    for (int i = 0; i < 4; i++) {
        printf("%04X", segments[i]);

        if (i == 3) printf("\n");
        else        printf("-");
    }
}

/*
 * 1.   Add up all the ASCII values of each of the characters of the string
 * 2.   Get the length of the characters in the username string
 * 3.   Multiply the two values above with each other, and perform a bitwise XOR
 *      operation with the number 20480
 */
int get_seed(char username[]) {
    int len = strlen(username);
    int sum = 0;

    for (int i = 0; i < len; i++)
        sum += username[i];

    return ((sum * len) ^ 20480);
}

// Perform a bitwise AND with your SEED and the number 65535
int get_first_segment(int seed) {
    return (seed & 65535);
}

// Take your SEED and do a bitwise right shift by 16 bits
int get_second_segment(int seed) {
    return (seed >> 16);
}

/*
 * Add the first and last ASCII values of your username variable and multiply
 * the sum by the length of the username variable
 */
int get_third_segment(char username[]) {
    int len = strlen(username);
    return ((username[0] + username[len - 1]) * len);
}

/*
 * Add the numerical values of all the segments above (First, Second, and Third
 * segments added together), and take the remainder of this sum when divided by
 * 65536
 */
int get_fourth_segment(int segments[]) {
    return ((segments[0] + segments[1] + segments[2]) % 65536);
}

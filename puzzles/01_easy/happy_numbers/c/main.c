#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define SIZE 1000

const char *emotes[] = {
    ":)",
    ":("
};

void solve(char x[]);
bool find(int n, int array[], int size);
void debug(int array[], int size);

int main() {
    int n;
    scanf("%d", &n);
    fgetc(stdin);

    for (int i = 0; i < n; i++) {
        char x[129] = "";
        scanf("%[^\n]", x);
        fgetc(stdin);
        solve(x);
    }
    return 0;
}

void solve(char x[]) {
    int explored[SIZE];
    int explored_size = 0;
    int next = 0;

    for (int i = 0; i < strlen(x); i++) {
        int d = x[i] - '0';
        next += d * d; 
    }

    do {
        int current = next;
        explored[explored_size++] = current;
        next = 0;

        while (current > 0) {
            int d = current % 10;
            next += d * d;
            current /= 10;
        }

    } while (next != 1 && !find(next, explored, explored_size));

    printf("%s", x);

    if (next == 1) {
        // happy number
        printf(" %s\n", emotes[0]);
    } else {
        // unhappy number
        printf(" %s\n", emotes[1]);
    }
}

// return true if n is in the array
bool find(int n, int array[], int size) {
    for (int i = 0; i < size; i++)
        if (array[i] == n)
            return true;
    return false;
}

void debug(int array[], int size) {
    fprintf(stderr, "[DEBUG] [");
    for (int i = 0; i < size; i++)
        fprintf(stderr, " %d", array[i]); 
    fprintf(stderr, " ]\n");
}

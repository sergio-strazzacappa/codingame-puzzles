#include <stdio.h>
#include <string.h>
#include <math.h>

#define N 52

/*
 * ranks = A 2 3 4 5 6 7 8 9 T J Q K
 * suits = C D H S
 */ 

int r;
int s;
char cards[N];

void remove_cards(char a[], int n, char removed[]);
int is_suit(char c);
int is_rank(char c);
float seek_cards(char a[], int n, char sought[]);
int get_index(char c);
int total(char a[], int n);
void dump(char a[], int n);

int main() {
    scanf("%d%d", &r, &s);
    fgetc(stdin);

    for (int i = 0; i < N; i++)
        cards[i] = 1;

    char removed[16];
    for (int i = 0; i < r; i++) {
        scanf("%[^\n]", removed);
        fgetc(stdin);
        remove_cards(cards, N, removed);
    }

    char sought[16];
    float percentage = 0;
    for (int i = 0; i < s; i++) {
        scanf("%[^\n]", sought);
        fgetc(stdin);
        percentage += seek_cards(cards, N, sought);
    }

    printf("%.0f%%\n", round(percentage));

    return 0;
}

void remove_cards(char a[], int n, char removed[]) {
    char ranks[13], suits[4];
    
    int r_index = 0;
    int s_index = 0;
    for (int i = 0; i < strlen(removed); i++) {
        if (is_rank(removed[i])) {
            ranks[r_index] = removed[i];
            r_index++;
        }

        if (is_suit(removed[i])) {
            suits[s_index] = removed[i];
            s_index++;
        }
    }

    if (s_index == 0) {
        // remove every rank found
        for (int i = 0; i < r_index; i++) {
            for (int j = 0; j < 4; j++) {
                a[get_index(ranks[i]) + j * 13] = 0;
            }
        }
    } else if (r_index == 0) {
        // remove every suit found
        for (int i = 0; i < s_index; i++) {
            for (int j = 0; j < 13; j++) {
                a[get_index(suits[i]) * 13 + j] = 0;
            }
        }
    } else {
        for (int i = 0; i < r_index; i++) {
            for (int j = 0; j < s_index; j++) {
                a[get_index(suits[j]) * 13 + get_index(ranks[i])] = 0;
            }
        }
    }
}

int is_suit(char c) {
    return c == 'C' || c == 'D' || c == 'H' || c == 'S';
}

int is_rank(char c) {
    return !is_suit(c);
}

float seek_cards(char a[], int n, char sought[]) {
    char ranks[13], suits[4];
    
    int r_index = 0;
    int s_index = 0;
    float p = 0;
    for (int i = 0; i < strlen(sought); i++) {
        if (is_rank(sought[i])) {
            ranks[r_index] = sought[i];
            r_index++;
        }
        if (is_suit(sought[i])) {
            suits[s_index] = sought[i];
            s_index++;
        }
    }

    if (s_index == 0) {
        // seek every rank found
        for (int i = 0; i < r_index; i++) {
            for (int j = 0; j < 4; j++) {
                if (a[get_index(ranks[i]) + j * 13] == 1) {
                    p += (float)1 / total(a, n) * 100;
                    a[get_index(ranks[i]) + j * 13] = 2;
                }
            }
        }
    } else if (r_index == 0) {
        // seek every suit found
        for (int i = 0; i < s_index; i++) {
            for (int j = 0; j < 13; j++) {
                if (a[get_index(suits[i]) * 13 + j] == 1) {
                    p += (float)1 / total(a, n) * 100;
                    a[get_index(suits[i]) * 13 + j] = 2;
                }
            }
        }
    } else {
        for (int i = 0; i < r_index; i++) {
            for (int j = 0; j < s_index; j++) {
                if (a[get_index(suits[j]) * 13 + get_index(ranks[i])] == 1) {
                    p += (float)1 / total(a, n) * 100;
                    a[get_index(suits[j]) * 13 + get_index(ranks[i])] = 2;
                }
            }
        }
    }
    return p;
}

int get_index(char c) {
    if (c == 'A')               return 0;
    if (c >= '2' && c <= '9')   return c - '0' - 1;
    if (c == 'T')               return 9;
    if (c == 'J')               return 10;
    if (c == 'Q')               return 11;
    if (c == 'K')               return 12;

    if (c == 'C')               return 0;
    if (c == 'D')               return 1;
    if (c == 'H')               return 2;
    if (c == 'S')               return 3;

    return -1;
}

int total(char a[], int n) {
    int t = 0;

    for (int i = 0; i < n; i++) {
        if (a[i] == 1 || a[i] == 2)
            t++;
    }

    return t;
}

void dump(char a[], int n) {
    for (int i = 0; i < n; i++) {
        if (a[i] == 0)          printf("O");
        if (a[i] == 1)          printf("X");
        if (a[i] == 2)          printf("F");
        if (i < n - 1)          printf(" ");
        if ((i + 1) % 13 == 0)  printf("\n");
    }
}

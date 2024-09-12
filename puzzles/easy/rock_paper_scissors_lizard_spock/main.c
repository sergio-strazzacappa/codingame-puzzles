#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

typedef struct Player {
    int number;
    char sign;
    int* opponents;
    bool eliminated;
} player;

player *players;

void debug(int n, int rounds);
void solve(int n, int rounds);
void play(int p1, int p2, int current_round);
void output(int n, int rounds);
void clear(int n);

int main() {
    int n, rounds;
    scanf("%d", &n);

    rounds = log2(n);
    players = malloc(n * sizeof(player));

    for (int i = 0; i < n; i++) {
        int num_player;
        char sign_player[2];
        scanf("%d%s", &num_player, sign_player);

        player p = {
            .number = num_player,
            .sign = sign_player[0],
            .opponents = malloc(rounds * sizeof(int)),
            .eliminated = false
        };
        
        players[i] = p;
    }

    solve(n, rounds);
    clear(n);

    return 0;
}

void debug(int n, int rounds) {
    for (int i = 0; i < n; i++) {
        if (!players[i].eliminated) {
            fprintf(stderr, "(%d %c %s", players[i].number, players[i].sign,
            players[i].eliminated == 0? "FALSE" : "TRUE");

            for (int j = 0; j < rounds; j++) {
                fprintf(stderr, " %d", players[i].opponents[j]);
            }
            fprintf(stderr, ")\n");
        }
    }
}

void solve(int n, int rounds) {
    for (int i = 0; i < rounds; i++) {
        fprintf(stderr, "ROUND %d\n", i + 1);
        debug(n, rounds);
        int p1 = -1;
        int p2 = -1;
        for (int j = 0; j < n; j++) {
            if (!players[j].eliminated) {
                if (p1 == -1) {
                    p1 = j;
                } else {
                    p2 = j;
                    // p1 vs p2
                    play(p1, p2, i);

                    p1 = p2 = -1;
                }
            }
        }
    }
    output(n, rounds);
}

void play(int p1, int p2, int current_round) {
    char p1_sign = players[p1].sign;
    char p2_sign = players[p2].sign;
    int winner = -1;

    if ((p1_sign == p2_sign && players[p1].number < players[p2].number) ||
        (p1_sign == 'C' && p2_sign == 'P')                              ||
        (p1_sign == 'P' && p2_sign == 'R')                              ||
        (p1_sign == 'R' && p2_sign == 'L')                              ||
        (p1_sign == 'L' && p2_sign == 'S')                              ||
        (p1_sign == 'S' && p2_sign == 'C')                              ||
        (p1_sign == 'C' && p2_sign == 'L')                              ||
        (p1_sign == 'L' && p2_sign == 'P')                              ||
        (p1_sign == 'P' && p2_sign == 'S')                              ||
        (p1_sign == 'S' && p2_sign == 'R')                              ||
        (p1_sign == 'R' && p2_sign == 'C')) {
        winner = p1;
    } else {
        winner = p2;
    }

    if (p1 == winner) {
        players[p2].eliminated = true;
        players[p1].opponents[current_round] = players[p2].number;
    } else {
        players[p1].eliminated = true;
        players[p2].opponents[current_round] = players[p1].number;
    }
}

void output(int n, int rounds) {
    for (int i = 0; i < n; i++) {
        if (!players[i].eliminated) {
            printf("%d\n", players[i].number);
            for (int j = 0; j < rounds; j++) {
                printf("%d", players[i].opponents[j]);
                if (j != rounds - 1) {
                    printf(" ");
                }
            }
            break;
        }
    }
}

void clear(int n) {
    for (int i = 0; i < n; i++) {
        free(players[i].opponents);
    }
    free(players);
}
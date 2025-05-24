#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

typedef struct player {
    int number;
    char sign;
    int* opponents;
    bool eliminated;
} Player;

int n;
Player *players;

void init();
void solve();
void play(int p1, int p2, int current_round);
void output();
void debug();
void clear();

int main() {
    init();
    solve();
    clear(n);

    return 0;
}

void init() {
    scanf("%d", &n);

    players = malloc(n * sizeof(Player));

    for (int i = 0; i < n; i++) {
        Player p;
        int num_player;
        int rounds;
        char sign_player[2];

        scanf("%d%s", &num_player, sign_player);
        rounds = log2(n);

        p.number = num_player;
        p.sign = sign_player[0];
        p.opponents = malloc(rounds * sizeof(int));
        p.eliminated = false;
        
        players[i] = p;
    }
}

void solve() {
    int rounds = log2(n);

    for (int i = 0; i < rounds; i++) {
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
                    p1 = -1;
                    p2 = -1;
                }
            }
        }
    }
    output();
}

// p1 plays vs p2 in current round number
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
        (p1_sign == 'R' && p2_sign == 'C'))

        winner = p1;
    else
        winner = p2;

    if (p1 == winner) {
        players[p2].eliminated = true;
        players[p1].opponents[current_round] = players[p2].number;
    } else {
        players[p1].eliminated = true;
        players[p2].opponents[current_round] = players[p1].number;
    }
}

void output() {
    int rounds = log2(n);

    for (int i = 0; i < n; i++) {
        if (!players[i].eliminated) {
            printf("%d\n", players[i].number);

            for (int j = 0; j < rounds; j++) {
                printf("%d", players[i].opponents[j]);

                if (j != rounds - 1)
                    printf(" ");
            }
            printf("\n");
            break;
        }
    }
}

void debug() {
    int rounds = log2(n);

    for (int i = 0; i < n; i++) {
        if (!players[i].eliminated) {
            fprintf(stderr, "(%d %c %s", players[i].number, players[i].sign,
            players[i].eliminated == 0? "FALSE" : "TRUE");

            for (int j = 0; j < rounds; j++)
                fprintf(stderr, " %d", players[i].opponents[j]);
            fprintf(stderr, ")\n");
        }
    }
}

void clear() {
    for (int i = 0; i < n; i++)
        free(players[i].opponents);
    free(players);
}

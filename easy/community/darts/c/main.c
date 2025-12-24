#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

typedef struct Player {
    char name[101];
    int score;
} Player;

typedef struct Throw {
    char name[101];
    int x;
    int y;
} Throw;

int size;
int n;
Player *players;
int t;
Throw *throws;

void init();
void solve();
int search_player(char *name);
bool in_square(int x, int y);
bool in_circle(int x, int y);
bool in_diamond(int x, int y);
int cmp(const void *p, const void *q);
void clean();
void debug_players();
void debug_throws();

int main() {
    init();
    solve();
    clean();

    return 0;
}

void init() {
    scanf("%d", &size);
    scanf("%d%*c", &n);

    players = (Player *)malloc(sizeof(Player) * n);

    for (int i = 0; i < n; i++) {
        scanf("%[^\n]%*c", players[i].name);
        players[i].score = 0;
    }

    scanf("%d", &t);

    throws = (Throw *)malloc(sizeof(Throw) * t);

    for (int i = 0; i < t; i++) {
        scanf("%s%d%d", throws[i].name, &throws[i].x, &throws[i].y);
    }
}

void solve() {
    for (int i = 0; i < t; i++) {
        Throw t = throws[i];

        int index = search_player(t.name);

        if (in_diamond(t.x, t.y))
            players[index].score += 15;
        else if (in_circle(t.x, t.y))
            players[index].score += 10;
        else if (in_square(t.x, t.y))
            players[index].score += 5;
    }

    // sort the players by the scores in descending order
    qsort(players, n, sizeof(players[0]), cmp);

    // print the output
    for (int i = 0; i < n; i++)
        printf("%s %d\n", players[i].name, players[i].score);
}

// return the index of a player
int search_player(char *name) {
    for (int i = 0; i < n; i++) {
        if (strcmp(name, players[i].name) == 0)
            return i;
    }
    return -1;
}

// return true if the point (x, y) is in the square
bool in_square(int x, int y) {
    return  x >= -((float)size / 2) && x <= (float)size / 2 && 
            y >= -((float)size / 2) && y <= (float)size / 2;
}

// return true if the point (x, y) is in the circle
bool in_circle(int x, int y) {
    float radius = size / 2.;

    return sqrt(pow(x, 2) + pow(y, 2)) <= radius;
}

// return true if the point (x, y) is in the diamond
bool in_diamond(int x, int y) {
    return abs(x) + abs(y) <= (float)size / 2;
}

int cmp(const void *p, const void *q) {
    Player *p1 = (Player *)p;
    Player *p2 = (Player *)q;

    return p1->score < p2->score;
}

void clean() {
    free(players);
    free(throws);
}

void debug_players() {
    fprintf(stderr, "[DEBUG] Players:\n");
    fprintf(stderr, "[DEBUG] ------------\n");

    for (int i = 0; i < n; i++) {
        Player p = players[i];
        fprintf(stderr, "[DEBUG] (%s, %d)\n", p.name, p.score);
    }
}

void debug_throws() {
    fprintf(stderr, "[DEBUG] THROWS:\n");
    fprintf(stderr, "[DEBUG] ------------\n");

    for (int i = 0; i < t; i++) {
        Throw t = throws[i];
        fprintf(stderr, "[DEBUG] (%s, %d, %d)\n", t.name, t.x, t.y);
    }
}

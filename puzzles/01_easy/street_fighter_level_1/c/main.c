#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct champion {
    char name[5];
    int hp;
    int punch_dmg;
    int kick_dmg;
    int rage;
    int hits;
} Champion;

Champion player1;
Champion player2;

void init();
void set_champion(Champion *player);
void solve();
bool simulate(char direction[], char type[]);
void attack(Champion *player1, Champion *player2, char type[]);
bool is_dead(Champion player);
void end();
void debug(Champion player);

int main() {
    init();
    solve();

    return 0;
}

void init() {
    scanf("%s%s", player1.name, player2.name);
    set_champion(&player1);
    set_champion(&player2);
}

void set_champion(Champion *player) {
    if (strcmp(player->name, "KEN") == 0) {
        player->hp          = 25;
        player->punch_dmg   = 6;
        player->kick_dmg    = 5;
    }
    if (strcmp(player->name, "RYU") == 0) {
        player->hp          = 25;
        player->punch_dmg   = 4;
        player->kick_dmg    = 5;
    }
    if (strcmp(player->name, "TANK") == 0) {
        player->hp          = 50;
        player->punch_dmg   = 2;
        player->kick_dmg    = 2;
    }
    if (strcmp(player->name, "VLAD") == 0) {
        player->hp          = 30;
        player->punch_dmg   = 3;
        player->kick_dmg    = 3;
    }
    if (strcmp(player->name, "JADE") == 0) {
        player->hp          = 20;
        player->punch_dmg   = 2;
        player->kick_dmg    = 7;
    }
    if (strcmp(player->name, "ANNA") == 0) {
        player->hp          = 18;
        player->punch_dmg   = 9;
        player->kick_dmg    = 1;
    }
    if (strcmp(player->name, "JUN") == 0) {
        player->hp          = 60;
        player->punch_dmg   = 2;
        player->kick_dmg    = 1;
    }
    player->rage = 0;
    player->hits = 0;
}

void solve() {
    int n;
    scanf("%d", &n);

    bool dead = false;
    for (int i = 0; i < n; i++) {
        // each attack
        char direction[2];
        char type[11];
        scanf("%s%s", direction, type);

        fprintf(stderr, "[DEBUG] Round #%d %s %s\n", i + 1, direction, type);
        debug(player1);
        debug(player2);

        dead = simulate(direction, type);

        if (dead)
            break;
    }
    if (!dead)
        end();
}

// return true if this was the last simulation cause a dead player
bool simulate(char direction[], char type[]) {
    if (direction[0] == '>')
        // champion 1 attacks champion 2 
        attack(&player1, &player2, type);
    else
        // champion 2 attacks champion 1
        attack(&player2, &player1, type);

    if (is_dead(player1) || is_dead(player2)) {
        end();
        return true;
    }
    return false;
}

void attack(Champion *player1, Champion *player2, char type[]) {
    if (strcmp(type, "PUNCH") == 0) {
       player2->hp -= player1->punch_dmg;
    }
    if (strcmp(type, "KICK") == 0) {
        player2->hp -= player1->kick_dmg;
    }
    if (strcmp(type, "SPECIAL") == 0) {
        if (strcmp(player1->name, "KEN") == 0)
            player2->hp -= 3 * player1->rage;  
        if (strcmp(player1->name, "RYU") == 0)
            player2->hp -= 4 * player1->rage;  
        if (strcmp(player1->name, "TANK") == 0)
            player2->hp -= 2 * player1->rage;  
        if (strcmp(player1->name, "VLAD") == 0) {
            player2->hp -= 2 * (player1->rage + player2->rage);
            player2->rage = 0;
        }
        if (strcmp(player1->name, "JADE") == 0)
            player2->hp -= player1->hits + player1->rage;
        if (strcmp(player1->name, "ANNA") == 0)
            player2->hp -= 18 - player1->hp;
        if (strcmp(player1->name, "JUN") == 0) {
            player2->hp -= player1->rage;
            player1->hp += player1->rage;
        }
        player1->rage = 0;
    }

    player2->rage++;
    player1->hits++;
}

bool is_dead(Champion player) {
    return player.hp <= 0;
}

void end() {
    char winner[5];
    char loser[5];
    int hits;

    if (player1.hp > player2.hp) {
        strcpy(winner, player1.name);
        strcpy(loser, player2.name);
        hits = player1.hits;
    } else {
        strcpy(winner, player2.name);
        strcpy(loser, player1.name);
        hits = player2.hits;
    }

    printf("%s beats %s in %d hits\n", winner, loser, hits);
}

void debug(Champion player) {
    fprintf(stderr, "[DEBUG] %s = ", player.name);
    fprintf(stderr,
        "{ Life: %d Punch dmg: %d Kick dmg: %d Rage: %d Hits: %d}\n",
        player.hp, player.punch_dmg, player.kick_dmg, player.rage,
        player.hits);
}

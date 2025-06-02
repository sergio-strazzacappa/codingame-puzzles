#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NUM_BOWLS 7

int my_bowls[NUM_BOWLS];
int opp_bowls[NUM_BOWLS];
int num;

int solve();
void format_output();
void debug();

int main() {
    char line[101], *token;
    int index;

    scanf("%[^\n]", line);
    fgetc(stdin);

    token = strtok(line, " ");

    index = 0;
    while (token != NULL) {
        opp_bowls[index++] = atoi(token); 
        token = strtok(NULL, " ");
    }

    scanf("%[^\n]", line);
    fgetc(stdin);

    token = strtok(line, " ");

    index = 0;
    while (token != NULL) {
        my_bowls[index++] = atoi(token);
        token = strtok(NULL, " ");
    }

    scanf("%d", &num);

    int replay = solve();
    format_output(replay);

    return 0;
}

int solve() {
    int replay, grains, me;

    grains = my_bowls[num];
    me = 1;
    my_bowls[num] = 0; 

    if (num == 6) {
        me = 0;
        num = 0;
    } else {
        num++;
    }

    while (grains > 0) {
        if (me) {
            // from 0 to 6
            my_bowls[num]++;

            if (num == 6) {
                replay = 1;
                num = 0;
                me = 0;
            } else {
                replay = 0;
                num++;
            }
        } else {
            // from 0 to 5
            opp_bowls[num]++;

            if (num == 5) {
                num = 0;
                me = 1;
            } else {
                num++;
            }
            replay = 0;
        }
        grains--;
    }

    return replay;
}

void format_output(int replay) {
    for (int i = 0; i < NUM_BOWLS - 1; i++)
        printf("%d ", opp_bowls[i]);
    printf("[%d]\n", opp_bowls[NUM_BOWLS - 1]);

    for (int i = 0; i < NUM_BOWLS - 1; i++)
        printf("%d ", my_bowls[i]);
    printf("[%d]\n", my_bowls[NUM_BOWLS - 1]);

    if (replay)
        printf("REPLAY\n");
}

void debug() {
    fprintf(stderr, "Opp: [");
    for (int i = 0; i < NUM_BOWLS; i++) {
        fprintf(stderr, "%d", opp_bowls[i]);

        if (i < NUM_BOWLS - 1)
            fprintf(stderr, ", ");
    }

    fprintf(stderr, "]\n");
    fprintf(stderr, "Me: [");
    for (int i = 0; i < NUM_BOWLS; i++) {
        fprintf(stderr, "%d", my_bowls[i]);

        if (i < NUM_BOWLS - 1)
            fprintf(stderr, ", ");
    }
    fprintf(stderr, "]\n");
}

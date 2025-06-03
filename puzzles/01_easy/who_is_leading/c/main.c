#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct team {
    char *name;
    int try[80];
    int try_i;
    int conversion[80];
    int conversion_i;
    int penalty[80];
    int penalty_i;
    int dropped_goal[80];
    int dropped_goal_i;
} a, b;

void init();
void parse_input(char input[], struct team *t);
void solve();
int cmp(const void *a, const void *b);
void clean();
void debug(struct team t);

int main() {
    init();
    solve();
    clean();

    return 0;
}

void init() {
    char teams[101];
    scanf("%[^\n]", teams);
    fgetc(stdin);

    // name of team A
    char *token = strtok(teams, ",");
    a.name = (char *)malloc(sizeof(char) * strlen(token));
    strcpy(a.name, token);

    // name of team B
    token = strtok(NULL, "\n");
    b.name = (char *)malloc(sizeof(char) * strlen(token));
    strcpy(b.name, token);

    // scores of team A
    char scores_1[201];
    scanf("%[^\n]", scores_1);
    fgetc(stdin);

    a.try_i = 0;
    a.conversion_i = 0;
    a.penalty_i = 0;
    a.dropped_goal_i = 0;

    parse_input(scores_1, &a);

    // scores of team B
    char scores_2[201];
    scanf("%[^\n]", scores_2);
    fgetc(stdin);

    b.try_i = 0;
    b.conversion_i = 0;
    b.penalty_i = 0;
    b.dropped_goal_i = 0;

    parse_input(scores_2, &b);
}

void parse_input(char input[], struct team *t) {
    int array = 0;
    int j = 0;
    char val[4];

    for (int i = 0; i < strlen(input); i++) {
        if (input[i] == ',' || input[i] == ' ' || i == strlen(input) - 1) {
            if (isdigit(input[i]))
                val[j++] = input[i];

            val[j] = '\0';

            if (j != 0) {
                if (array == 0)
                    t->try[t->try_i++] = atoi(val);
                else if (array == 1)
                    t->conversion[t->conversion_i++] = atoi(val);
                else if (array == 2)
                    t->penalty[t->penalty_i++] = atoi(val);
                else
                    t->dropped_goal[t->dropped_goal_i++] = atoi(val);
            }

            j = 0;

            if (input[i] == ',')
                array++;

            continue;
        }

        val[j++] = input[i];
    }
}

void solve() {
    // order both array by timestamp
    int a_scores[a.try_i + a.conversion_i + a.penalty_i + a.dropped_goal_i][2];
    int b_scores[b.try_i + b.conversion_i + b.penalty_i + b.dropped_goal_i][2];

    int index_a = 0;
    for (int i = 0; i < a.try_i; i++) {
        a_scores[index_a][0] = a.try[i];
        a_scores[index_a][1] = 5;
        index_a++;
    }

    for (int i = 0; i < a.conversion_i; i++) {
        a_scores[index_a][0] = a.conversion[i];
        a_scores[index_a][1] = 2;
        index_a++;
    }

    for (int i = 0; i < a.penalty_i; i++) {
        a_scores[index_a][0] = a.penalty[i];
        a_scores[index_a][1] = 3;
        index_a++;
    }

    for (int i = 0; i < a.dropped_goal_i; i++) {
        a_scores[index_a][0] = a.dropped_goal[i];
        a_scores[index_a][1] = 3;
        index_a++;
    }

    qsort(a_scores, index_a, sizeof(a_scores[0]), cmp);

    int index_b = 0;
    for (int i = 0; i < b.try_i; i++) {
        b_scores[index_b][0] = b.try[i];
        b_scores[index_b][1] = 5;
        index_b++;
    }

    for (int i = 0; i < b.conversion_i; i++) {
        b_scores[index_b][0] = b.conversion[i];
        b_scores[index_b][1] = 2;
        index_b++;
    }

    for (int i = 0; i < b.penalty_i; i++) {
        b_scores[index_b][0] = b.penalty[i];
        b_scores[index_b][1] = 3;
        index_b++;
    }

    for (int i = 0; i < b.dropped_goal_i; i++) {
        b_scores[index_b][0] = b.dropped_goal[i];
        b_scores[index_b][1] = 3;
        index_b++;
    }

    qsort(b_scores, index_b, sizeof(b_scores[0]), cmp);

    int a_score = 0;
    int a_adv   = 0;
    int a_time  = 0;
    int b_score = 0;
    int b_adv   = 0;
    int b_time  = 0;

    int i = 0;
    int j = 0;

    int last = 0;
    while (i < index_a || j < index_b) {
        if (i < index_a)
            a_time = a_scores[i][0];
        else
            a_time = 81;

        while (j < index_b) {
            b_time = b_scores[j][0];

            if (b_time > a_time)
                break;

            if (b_score > a_score)
                b_adv += b_time - last;
            else if (a_score > b_score)
                a_adv += b_time - last;

            b_score += b_scores[j][1];
            j++;
            last = b_time;
        }

        if (a_score > b_score)
            a_adv += a_time - last;
        else if (b_score > a_score)
            b_adv += a_time - last;

        if (i < index_a)
            a_score += a_scores[i][1];

        i++;
        last = a_time;
    }
    last = 81;

    if (a_score > b_score)
        a_adv += last - a_time;
    else if (b_score > a_score)
        b_adv += last - a_time;

    printf("%s: %d %d\n", a.name, a_score, a_adv);
    printf("%s: %d %d\n", b.name, b_score, b_adv);
}

int cmp(const void *a, const void *b) {
    return *((int *)a) - *((int *)b);
}

void clean() {
    free(a.name);
    free(b.name);
}

void debug(struct team t) {
    fprintf(stderr, "[DEBUG] Name: %s\n", t.name);
    
    fprintf(stderr, "[DEBUG] Tries: [");
    for (int i = 0; i < t.try_i; i++) {
        fprintf(stderr, " %d", t.try[i]);
    }
    fprintf(stderr, " ]\n");

    fprintf(stderr, "[DEBUG] Conversions: [");
    for (int i = 0; i < t.conversion_i; i++) {
        fprintf(stderr, " %d", t.conversion[i]);
    }
    fprintf(stderr, " ]\n");

    fprintf(stderr, "[DEBUG] Penalties: [");
    for (int i = 0; i < t.penalty_i; i++) {
        fprintf(stderr, " %d", t.penalty[i]);
    }
    fprintf(stderr, " ]\n");

    fprintf(stderr, "[DEBUG] Dropped goals: [");
    for (int i = 0; i < t.dropped_goal_i; i++) {
        fprintf(stderr, " %d", t.dropped_goal[i]);
    }
    fprintf(stderr, " ]\n");
}

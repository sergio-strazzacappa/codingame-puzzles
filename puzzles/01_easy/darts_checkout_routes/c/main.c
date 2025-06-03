#include <stdio.h>

#define N_SINGLES   21
#define N_DOUBLES   21
#define N_TREBLES   20

typedef struct {
    int value;
    int mult;
} Dartboard;

const int SINGLES[] = {
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 25
};

const int DOUBLES[] = {
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 25
};

const int TREBLES[] = {
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20
};

enum dartboard {
    singles,
    doubles,
    trebles
};

int score;
int darts;

void solve();
void dfs(int current_score, int darts_remaining, enum dartboard db,
    enum dartboard current_db, int index, int *routes, Dartboard path[],
    int path_index);

int main() {
    scanf("%d%d", &score, &darts);
    solve();

    return 0;
}

void solve() {
    int routes = 0;
    Dartboard path[darts];

    dfs(0, darts, singles, singles, 0, &routes, path, 0);
    printf("%d\n", routes);
}

void dfs(int current_score, int darts_remaining, enum dartboard db,
    enum dartboard current_db, int index, int *routes, Dartboard path[],
    int path_index) {

    // solution found
    if (darts_remaining >= 0 && current_score == score && current_db == doubles) {
        (*routes)++;

        fprintf(stderr, "[DEBUG] Solution found ");
        fprintf(stderr, "[");
        
        for (int i = 0; i < path_index; i++) {
            fprintf(stderr, " (%d, %d)", path[i].value, path[i].mult);
        }

        fprintf(stderr, " ]\n");

        return;
    }

    if (current_score == score && current_db != doubles)    return;
    if (current_score > score)                              return;
    if (darts_remaining == 0)                               return;

    while (1) {
        if (index == N_SINGLES && (db == singles || db == doubles))  {
            db++;
            index = 0;
        }

        if (db == trebles && index == N_TREBLES) break;

        int add;
        current_db = db;

        if (db == singles)  add = SINGLES[index];
        if (db == doubles)  add = DOUBLES[index] * 2;
        if (db == trebles)  add = TREBLES[index] * 3;

        current_score += add;
        path[path_index++] = (Dartboard){add / (current_db + 1), current_db + 1};

        dfs(current_score, darts_remaining - 1, singles, current_db, 0, routes,
            path, path_index);

        path_index--;
        current_score -= add;
        index++;
    }
}

#include <stdio.h>

int score;

void solve();

int main() {
    scanf("%d", &score);

    solve();

    return 0;
}

void solve() {
    int computed_score = score;
    int tries = 0;
    int transformations = 0;
    int penalties = 0;

    while (computed_score > 0) {
        // compute the tries
        for (int i = 0; i <= tries; i++) {
            // compute the transformations
            if (i > 0) {
                computed_score -= 2;
                transformations++;
            }

            while (computed_score > 0) {
                // compute the penalties/drops

                // add a penalty
                computed_score -= 3;
                penalties++;

                if (computed_score == 0)
                    printf("%d %d %d\n", tries, transformations, penalties);
            }

            // restore the score
            computed_score += 3 * penalties;
            penalties = 0;

            if (computed_score == 0)
                printf("%d %d %d\n", tries, transformations, penalties);
        }

        // restore the score
        computed_score += 2 * transformations;
        transformations = 0;

        // add a new try
        computed_score -= 5;
        tries++;

        if (computed_score == 0)
            printf("%d %d %d\n", tries, transformations, penalties);
    }
}

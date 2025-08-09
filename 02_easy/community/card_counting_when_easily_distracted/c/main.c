#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

const char symbols[5] = {'K', 'Q', 'J', 'T', 'A'};

char stream_of_consciousness[5001];
int bust_threshold;

void init();
void solve();
bool is_valid(char *observation, int size);

int main() {
    init();
    solve();

    return 0;
}

void init() {
    scanf("%[^\n]", stream_of_consciousness);
    scanf("%d", &bust_threshold);
}

void solve() {
    char *observation = strtok(stream_of_consciousness, ".");
    int under = (bust_threshold - 1) * 4;
    int missing = 52;

    while (observation != NULL) {
        int size = strlen(observation);

        if (is_valid(observation, size)) {
            for (int i = 0; i < size; i++) {
                char card = observation[i];
                int value = 0;

                if (card >= 50 && card <= 57)
                    value = observation[i] - 48;
                else if (observation[i] == 'A')
                    value = 1;
                else
                    value = 10;

                if (value < bust_threshold)
                    under--;
                
                missing--;
            }
        }
        observation = strtok(NULL, ".");
    }

    printf("%.0f%%\n", round((float)under / missing * 100));
}

// return false if the observations has any non card, true otherwise
bool is_valid(char *observation, int size) {
    for (int i = 0; i < size; i++) {
        if (observation[i] >= 50 && observation[i] <= 57) // [2, 9]
            continue;

        for (int j = 0; j < 5; j++) { // [A, T, J, Q, K]
            if (observation[i] == symbols[j])
                break;
            if (j == 4) 
                return false;
        }
    }
    return true;
}

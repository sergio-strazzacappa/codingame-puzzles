#include <stdio.h>
#include <string.h>
#include <math.h>

char symbols[5] = {'K', 'Q', 'J', 'T', 'A'};

int is_valid(char* observation, int size) {
    int is_valid = 0;

    for (int i = 0; i < size; i++) {
        if (observation[i] >= 50 && observation[i] <= 57) continue;

        for (int j = 0; j < 5; j++) {
            if (observation[i] == symbols[j])   break;
            if (j == 4)                         return 0;
        }
    }

    return 1;
}

int main() {
    char stream_of_consciousness[5001];
    scanf("%[^\n]", stream_of_consciousness);

    int bust_threshold;
    scanf("%d", &bust_threshold);

    char* observation = strtok(stream_of_consciousness, ".");

    int under = (bust_threshold - 1) * 4;
    int missing = 52;

    while (observation != NULL) {
        int size = strlen(observation);

        if (is_valid(observation, size)) {
            for (int i = 0; i < size; i++) {
                char card = observation[i];
                int value = 0;

                if (card >= 50 && card <= 57)   value = observation[i] - 48;
                else if (observation[i] == 'A') value = 1;
                else                            value = 10;

                if (value < bust_threshold)     under--;
                missing--;
            }
        }
        observation = strtok(NULL, ".");
    }

    printf("%.0f%%\n", round((float)under / missing * 100));

    return 0;
}
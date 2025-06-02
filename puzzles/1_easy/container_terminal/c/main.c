#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SHIPS 26

void solve(char line[]);

int main() {
    int n;
    scanf("%d", &n);
    fgetc(stdin);

    for (int i = 0; i < n; i++) {
        char line[501];
        scanf("%[^\n]", line);
        fgetc(stdin);

        solve(line);
    }

    return 0;
}

void solve(char line[]) {
    char queue[MAX_SHIPS];
    int q_index = 0;

    for (int i = 0; i < strlen(line); i++) {
        char container = line[i];
        bool queued = false;

        for (int j = 0; j < q_index; j++) {
            if (queue[j] >= container) {
                // add the container to the current queue
                queue[j] = container;
                queued = true;
                break;
            }
        }

        if (!queued)
            // add another stack
            queue[q_index++] = container;
    }

    printf("%d\n", q_index);
}

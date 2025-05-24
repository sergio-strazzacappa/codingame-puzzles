#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const char *DICTS[4][26] = {
    {
        "Authority", "Bills", "Capture", "Destroy", "Englishmen", "Fractious",
        "Galloping", "High", "Invariably", "Juggling", "Knights", "Loose",
        "Managing", "Never", "Owners", "Play", "Queen", "Remarks", "Support",
        "The", "Unless", "Vindictive", "When", "Xpeditiously", "Your", "Zigzag"
    },
    {
        "Apples", "Butter", "Charlie", "Duff", "Edward", "Freddy", "George",
        "Harry", "Ink", "Johnnie", "King", "London", "Monkey", "Nuts", "Orange",
        "Pudding", "Queenie", "Robert", "Sugar", "Tommy", "Uncle", "Vinegar",
        "Willie", "Xerxes", "Yellow", "Zebra"
    },
    {
        "Amsterdam", "Baltimore", "Casablanca", "Denmark", "Edison", "Florida",
        "Gallipoli", "Havana", "Italia", "Jerusalem", "Kilogramme", "Liverpool",
        "Madagascar", "New-York", "Oslo", "Paris", "Quebec", "Roma", "Santiago",
        "Tripoli", "Uppsala", "Valencia", "Washington", "Xanthippe", "Yokohama",
        "Zurich"
    },
    {
        "Alfa", "Bravo", "Charlie", "Delta", "Echo", "Foxtrot", "Golf", "Hotel",
        "India", "Juliett", "Kilo", "Lima", "Mike", "November", "Oscar", "Papa",
        "Quebec", "Romeo", "Sierra", "Tango", "Uniform", "Victor", "Whiskey",
        "X-ray", "Yankee", "Zulu"
    }
};

char word[101];

void solve();
int search_dict();

int main() {
    scanf("%[^\n]", word);
    solve();

    return 0;
}

void solve() {
    int i = search_dict() + 1;

    if (i == 4)
        i = 0;

    char *token = strtok(word, " ");

    while (token != NULL) {
        printf("%s", DICTS[i][token[0] - 'A']);

        token = strtok(NULL, " ");

        if (token != NULL)
            printf(" ");
    }
    printf("\n");
}

// returns the first index of the array if found, otherwise -1
int search_dict() {
    char *tmp = (char *)malloc(sizeof(char) * (strlen(word) + 1));
    strcpy(tmp, word);
    char *token = strtok(tmp, " ");

    int found[4] = {
        0, 0, 0, 0
    };

    while (token != NULL) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 26; j++) {
                if (strcmp(token, DICTS[i][j]) == 0) {
                    found[i]++;
                    break;
                }
            }
        }

        token = strtok(NULL, " ");
    }

    free(tmp);

    int index = -1;
    int max = 0;

    for (int i = 0; i < 4; i++) {
        if (found[i] > max) {
            max = found[i];
            index = i;
        }
    }

    return index;
}

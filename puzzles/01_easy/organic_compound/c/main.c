#include <stdio.h>
#include <string.h>
#include <ctype.h>

const char *PREFIX[] = {
    "EMPTY",
    "meth", // 1
    "eth",  // 2
    "prop", // 3
    "but",  // 4
    "pent", // 5
    "hex",  // 6
    "hept", // 7
    "oct",  // 8
    "non",  // 9
    "dec"   // 10
};

const char *SUFFIX[] = {
    "ane",
    "ene",
    "anol",
    "anoic acid",
    "anal",
    "anone"
};

void parse(char formula[]);

int main() {
    char formula[1025] = "";
    scanf("%[^\n]", formula);
    parse(formula);

    return 0;
}

void parse(char formula[]) {
    int atoms[3] = {
        0,  // carbon
        0,  // hydrogen
        0   // oxygen
    };

    char chemical_name[30] = "OTHERS";

    char current_element = '-';
    int n = 0;

    for (int i = 0; i < strlen(formula) + 1; i++) {
        char c = '-';

        if (i < strlen(formula))
            c = formula[i];

        if (!isdigit(c) || i == strlen(formula)) {
            if (current_element == 'C') atoms[0] += n;
            if (current_element == 'H') atoms[1] += n;
            if (current_element == 'O') atoms[2] += n;
        }

        if (!isdigit(c)) {
            current_element = c;
            n = 1;

            if (i < strlen(formula) - 1 && isdigit(formula[i + 1]))
                n = 0;
        }

        if (isdigit(c)) {
            // build the number of atoms
            n = n * 10 + c - '0';        
        }
    }

    // alkane
    if (atoms[1] == atoms[0] * 2 + 2 && atoms[2] == 0) {
        strcpy(chemical_name, PREFIX[atoms[0]]);
        strcat(chemical_name, SUFFIX[0]);
    }

    // alkene
    if (atoms[1] == atoms[0] * 2 && atoms[2] == 0) {
        strcpy(chemical_name, PREFIX[atoms[0]]);
        strcat(chemical_name, SUFFIX[1]);
    }

    // alcohol - functional group
    if (atoms[1] == atoms[0] * 2 + 2) {
        int len = strlen(formula);
        if (formula[len - 2] == 'O' && formula[len - 1] == 'H' && 
            atoms[2] < 2) {
            strcpy(chemical_name, PREFIX[atoms[0]]);
            strcat(chemical_name, SUFFIX[2]);
        }
    }

    // carboxyilic acid - functionl group
    if (atoms[1] == atoms[0] * 2) {
        int len = strlen(formula);
        if (formula[len - 4] == 'C' && formula[len - 3] == 'O' &&
            formula[len - 2] == 'O' && formula[len - 1] == 'H' &&
            atoms[2] < 3) {
            strcpy(chemical_name, PREFIX[atoms[0]]);
            strcat(chemical_name, SUFFIX[3]);
        }
    }

    // aldehyde - functional group
    if (atoms[1] == atoms[0] * 2) {
        int len = strlen(formula);
        if (formula[len - 3] == 'C' && formula[len - 2] == 'H' &&
            formula[len - 1] == 'O' && atoms[2] < 2) {
            strcpy(chemical_name, PREFIX[atoms[0]]);
            strcat(chemical_name, SUFFIX[4]);
        }
    }

    // ketone - functional group
    if (strcmp(chemical_name, "OTHERS") == 0 && atoms[1] == atoms[0] * 2 &&
        strstr(formula, "CO") != NULL && atoms[2] < 2) {
        strcpy(chemical_name, PREFIX[atoms[0]]);
        strcat(chemical_name, SUFFIX[5]);
    }

    printf("%s\n", chemical_name);
}

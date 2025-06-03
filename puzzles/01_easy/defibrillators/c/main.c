#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>

#define NUMBER_LEN 150
#define STRING_LEN 257

struct {
    double lon;
    double lat;
} user;

typedef struct defib {
    char name[STRING_LEN];
    double lon;
    double lat;
} Defib;

void replace(char str1[], char str2[]);
void parse_input(char input[], Defib defs[], int index);
void solve(Defib defs[], int n);

int main() {
    char lon[NUMBER_LEN], lat[NUMBER_LEN], tmp[NUMBER_LEN];
    int n;

    scanf("%s%s%d", lon, lat, &n);
    fgetc(stdin);

    replace(lon, tmp);
    user.lon = atof(tmp);

    replace(lat, tmp);
    user.lat = atof(tmp);

    fprintf(stderr, "[DEBUG] User: (%.6f %.6f)\n", user.lon, user.lat);

    Defib *defs = (Defib *)malloc(sizeof(Defib) * n);

    for (int i = 0; i < n; i++) {
        char defib[STRING_LEN];
        scanf("%[^\n]", defib);
        fgetc(stdin);
        parse_input(defib, defs, i);
    }

    solve(defs, n);

    return 0;
}

// replaces the "," for "." in a floating point number
void replace(char str1[], char str2[]) {
    str2[0] = '\0';
    fprintf(stderr, "[DEBUG] str1: %s - str2: %s\n", str1, str2);

    int index = -1;

    for (int i = 0; i < strlen(str1); i++) {
        if (str1[i] == ',') {
            index = i;
            fprintf(stderr, "[DEBUG] Coma index: %d\n", index);
            break;
        }
    }

    if (index != -1) {
        // the "," was found
        strcpy(str2, str1);
        fprintf(stderr, "[DEBUG] str2: %s\n", str2);
        str2[index] = '\0'; // marks the ","
        strcat(str2, ".");
        fprintf(stderr, "[DEBUG] str2: %s\n", str2);
        strcat(str2, &str1[index + 1]);
        fprintf(stderr, "[DEBUG] str2: %s\n", str2);
    }
    fprintf(stderr, "[DEBUG] Exit replace\n");
}

void parse_input(char input[], Defib defs[], int index) {
    int field = 1;
    int j = 0;
    char field_name[STRING_LEN], tmp[NUMBER_LEN];
    Defib d;

    for (int i = 0; i < strlen(input); i++) {
        if (input[i] == ';') {
            if (field == 2) {
                strcpy(d.name, field_name);
                fprintf(stderr, "[DEBUG] NAME: %s\n", d.name);
            }
            if (field == 5) {
                replace(field_name, tmp);
                fprintf(stderr, "[DEBUG] LON: %s\n", tmp);
                d.lon = atof(tmp);
            }
            field++;
            j = 0;
            field_name[j] = '\0';
            continue;
        }
        field_name[j] = input[i];
        field_name[j + 1] = '\0';
        j++;
    }
    field_name[j] = '\0';
    replace(field_name, tmp);
    fprintf(stderr, "[DEBUG] LAT: %s\n", tmp);
    d.lat = atof(tmp);

    defs[index] = d;
}

void solve(Defib defs[], int n) {
    char name[STRING_LEN];
    double min_distance = DBL_MAX;

    for (int i = 0; i < n; i++) {
        fprintf(stderr, "[DEBUG] (%s %0.20f %0.20f)\n", defs[i].name, defs[i].lon, defs[i].lat);

        double d = sqrt(pow(defs[i].lon - user.lon, 2) + pow(defs[i].lat - user.lat, 2));

        fprintf(stderr, "[DEBUG] Distance: %f\n", d);

        if (d < min_distance) {
            min_distance = d;
            strcpy(name, defs[i].name);
        }
    }
    printf("%s\n", name);
}

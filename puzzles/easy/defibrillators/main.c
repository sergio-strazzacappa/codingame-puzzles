#include <stdio.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include <stdlib.h>

#define NUMBER_LEN 150
#define STRING_LEN 257

struct User {
    double lon;
    double lat;
} user;

struct Defib {
    char name[STRING_LEN];
    double lon;
    double lat;
};

void replace(char string1[NUMBER_LEN], char string2[NUMBER_LEN]);
void parse_input(char input[STRING_LEN], struct Defib defs[], int i);
void solve(struct Defib defs[], int n);

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

    struct Defib defs[n];

    for (int i = 0; i < n; i++) {
        char defib[STRING_LEN];
        scanf("%[^\n]", defib);
        fgetc(stdin);
        parse_input(defib, defs, i);
    }
    solve(defs, n);

    return 0;
}

void solve(struct Defib defs[], int n) {
    char name[STRING_LEN];
    double min_distance = DBL_MAX;

    for (int i = 0; i < n; i++) {
        fprintf(stderr, "[DEBUG] (%s %0.20f %0.20f)\n", defs[i].name, defs[i].lon, defs[i].lat);
        double x = (defs[i].lon - user.lon) * cos((user.lat + defs[i].lat)) / 2;
        double y = defs[i].lat - user.lat;
        //double d = sqrt(pow(x, 2) + pow(y, 2)) * 6371;
        double d = sqrt(pow(defs[i].lon - user.lon, 2) + pow(defs[i].lat - user.lat, 2));

        fprintf(stderr, "[DEBUG] Distance: %f\n", d);
        if (d < min_distance) {
            min_distance = d;
            strcpy(name, defs[i].name);
        }
    }
    printf("%s\n", name);
}

/**
 ** replaces the "," for "." in a floating point number
 *
 * @param string1 original number
 * @param string2 new number with the substitution 
 */
void replace(char string1[NUMBER_LEN], char string2[NUMBER_LEN]) {
    fprintf(stderr, "[DEBUG] string1: %s - string2: %s\n", string1, string2);
    int index = -1;

    for (int i = 0; i < strlen(string1); i++) {
        if (string1[i] == ',') {
            index = i;
            fprintf(stderr, "[DEBUG] Coma index: %d\n", index);
        }
    }

    if (index != -1) {
        // the "," was found
        strncpy(string2, string1, index);
        fprintf(stderr, "[DEBUG] string2: %s\n", string2);
        string2[index] = '\0';
        strncat(string2, ".", 1);
        fprintf(stderr, "[DEBUG] string2: %s\n", string2);
        strncat(string2, &string1[index + 1], 51);
        fprintf(stderr, "[DEBUG] string2: %s\n", string2);
    }
}

void parse_input(char input[STRING_LEN], struct Defib defs[], int i) {
    int field = 1;
    int j = 0;
    char field_name[STRING_LEN], tmp[NUMBER_LEN];
    struct Defib d;

    for (int i = 0; i < strlen(input); i++) {
        if (input[i] == ';') {
            if (field == 2) {
                strcpy(d.name, field_name);
                fprintf(stderr, "NAME: %s\n", d.name);
            }
            if (field == 5) {
                replace(field_name, tmp);
                fprintf(stderr, "LON: %s\n", tmp);
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
    fprintf(stderr, "LAT: %s\n", tmp);
    d.lat = atof(tmp);

    defs[i] = d;
}
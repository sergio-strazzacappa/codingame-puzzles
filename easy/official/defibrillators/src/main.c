#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>

#define NUMBER_LEN 150
#define STRING_LEN 257

typedef struct Position {
    double lon;
    double lat;
} Position;

typedef struct Defib {
    char name[STRING_LEN];
    double lon;
    double lat;
} Defib;

void parse_input(char input[], Defib defs[], int index);
void solve(Defib defs[], int n, Position user);

int main() {
    char lon[NUMBER_LEN], lat[NUMBER_LEN];
    int n;

    scanf("%s%s%d", lon, lat, &n);
    fgetc(stdin);

    // replace the "," for a "." in lon if neccesary
    for (int i = 0; i < strlen(lon); i++) {
        if (lon[i] == ',') {
            lon[i] = '.';
            break;
        }
    }

    // replace the "," for a "." in lat if neccesary
    for (int i = 0; i < strlen(lat); i++) {
        if (lat[i] == ',') {
            lat[i] = '.';
            break;
        }
    }

    Position user = {
        .lon = atof(lon),
        .lat = atof(lat)
    };

    fprintf(stderr, "[DEBUG] User: (%.6f %.6f)\n", user.lon, user.lat);

    Defib *defs = (Defib *)malloc(sizeof(Defib) * n);

    for (int i = 0; i < n; i++) {
        char defib[STRING_LEN];
        scanf("%[^\n]", defib);
        fgetc(stdin);
        parse_input(defib, defs, i);
    }

    solve(defs, n, user);

    return 0;
}

void parse_input(char input[], Defib defs[], int index) {
    int field = 1;
    int j = 0;
    char field_name[STRING_LEN];
    Defib d;

    for (int i = 0; i < strlen(input); i++) {
        if (input[i] == ';') {
            if (field == 2) { // name
                strcpy(d.name, field_name);
                fprintf(stderr, "[DEBUG] NAME: %s\n", d.name);
            }
            if (field == 5) { // longitud
                // replace the "," for a "." in the lon field if neccesary
                for (int k = 0; k < strlen(field_name); k++) {
                    if (field_name[k] == ',') {
                        field_name[k] = '.';
                        break;
                    }
                }
                fprintf(stderr, "[DEBUG] LON: %s\n", field_name);
                d.lon = atof(field_name);
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

    // replace the "," for a "." in the lat field if neccesary
    for (int i = 0; i < strlen(field_name); i++) {
        if (field_name[i] == ',') {
            field_name[i] = '.';
            break;
        }
    }
    fprintf(stderr, "[DEBUG] LAT: %s\n", field_name);
    d.lat = atof(field_name);

    defs[index] = d;
}

void solve(Defib defs[], int n, Position user) {
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

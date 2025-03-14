#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_AIRCRAFTS 100

typedef struct aircraft {
    int x;
    int y;
    int direction;
    int shot;
} Aircraft;


int width;
int height;
char **grid;
Aircraft aircrafts[MAX_AIRCRAFTS];
int size;
int me;

void read_input();
void solve();
void action();
void update_state();
void print_grid();
void print_aircrafts();

int main() {
    size = 0;
    read_input();
    solve();

    return 0;
}

void read_input() {
    scanf("%d", &height);

    grid = (char **)malloc(height * sizeof(char *));

    for (int y = 0; y < height; y++) {
        char line[41];
        scanf("%s", line);

        if (!y)
            width = strlen(line);

        grid[y] = (char *)malloc(width * sizeof(char));

        for (int x = 0; x < width; x++) {
            grid[y][x] = line[x];

            if (line[x] == '>') {
                Aircraft a = {x, y, 0, 0};
                aircrafts[size++] = a;
            }
            if (line[x] == '<') {
                Aircraft a = {x, y, 1, 0};
                aircrafts[size++] = a;
            }
            if (y == height - 1 && line[x] == '^') {
                me = x;
            }
        }
    }
}

void solve() {
    int next;

    while (1) {
        next = 0;
        action();
        update_state();

        // check for end of the game
        for (int i = 0; i < size; i++) {
            Aircraft a = aircrafts[i];
            if (!a.shot)
                next = 1;
        }

        if (!next)
            break;
    }
}

void action() {
    int shoot = 0;
    for (int i = 0; i < size; i++) {
        Aircraft a = aircrafts[i];
        if (a.shot)
            continue;
        int v_distance = height - a.y;
        int h_distance = abs(a.x - me);

        if (h_distance == v_distance) {
            shoot = 1;
            aircrafts[i].shot = 1;
            break;
        }
    }

    if (shoot) {
        printf("SHOOT\n");
    } else {
        printf("WAIT\n");
    }
}

void update_state() {
    for (int i = 0; i < size; i++) {
        if (aircrafts[i].direction == 0) {
            aircrafts[i].x++;
        } else {
            aircrafts[i].x--;
        }
    }
}

void print_grid() {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            fprintf(stderr, "%c", grid[y][x]);
        }
        fprintf(stderr, "\n");
    }
}

void print_aircrafts() {
    fprintf(stderr, "ME: %d\n", me);
    fprintf(stderr, "AIRCRAFTS:\n");
    for (int i = 0; i < size; i++) {
        Aircraft a = aircrafts[i];
        fprintf(stderr, "[ (%.2d, %.2d) %d %d ]\n", a.x, a.y, a.direction, a.shot);
    }
}

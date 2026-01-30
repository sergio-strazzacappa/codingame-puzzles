#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define WIDTH   40
#define HEIGHT  18

typedef struct Point {
    int x;
    int y;
} Point;

typedef struct Player {
    Point position;
    int strikes;
} Player;

void solve(Player *thor, Point *giants, size_t size);
int distance(Point p, Point q);
bool is_target_safe(Point thor, Point target, char map[HEIGHT][WIDTH]);
bool is_in_danger(Point thor, char map[HEIGHT][WIDTH]);
void move(Player thor, Point p, char *action, Point *next);
void move_danger(Point thor, int *min_distance, char *action, Point *next,
    int dx, int dy, char map[HEIGHT][WIDTH]); 
int range(Player thor, Point giants[], size_t size);
void print_player(Player p);
void print_giants(Point *g, size_t size);
void print_map(char map[HEIGHT][WIDTH], Player thor);

/*
 * Strategy #1
 * Wait until a giant is at a distance of 1 and then strike
 *
 * Strategy #2
 * Move towards the center of all the giants, if anyone is at a distance of 1
 * strike
 *
 * Strategy #3
 * Build a map with the risk of every cell of being reached by a giant, then
 * move in the direction with low risk (distance 2 of the closest giant) in
 * the direction to the center. Check if the next cell is of high risk, and
 * avoid it
 */

int main() {
    Player thor;

    scanf("%d%d", &thor.position.x, &thor.position.y);

    while (true) {
        size_t giants_left;
        scanf("%d%ld", &thor.strikes, &giants_left);

        Point *giants = (Point *)malloc(sizeof(Point) * giants_left);

        for (int i = 0; i < giants_left; i++) {
            scanf("%d%d", &giants[i].x, &giants[i].y);
        }

        print_player(thor);
        print_giants(giants, giants_left);

        solve(&thor, giants, giants_left);

        free(giants);
    }

    return 0;
}

void solve(Player *thor, Point *giants, size_t size) {

    /*
     * a map with the risk of moving to each cell
     * a value of 0 means a giant is on that cell
     * a value of m means that a giant is 2-steps from that cell
     */
    char map[HEIGHT][WIDTH];

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            int count = 0;
            bool giant_found = false;
            map[y][x] = '-';
            for (int i = 0; i < size; i++) {
                Point p = {x, y};
                Point q = giants[i];
                if (distance(p, q) == 0 || distance(p, q) == 1) {
                    // a giant is on the cell
                    giant_found = true;
                    map[y][x] = '0';
                    break;
                }
                if (distance(p, q) == 2) {
                    count++;
                }
            }
            if (!giant_found && count)
                map[y][x] = count + '0';
        }
    }

    print_map(map, *thor);

    // try to move the the cell with highest value towards the center
    Point center = {WIDTH / 2, HEIGHT / 2};
    int max_value = 0;
    int min_distance_to_center = INT_MAX;
    bool safe = false;
    Point target;

    while (!safe) {
        target = (Point){-1, -1};
        for (int y = 0; y < HEIGHT; y++) {
            for (int x = 0; x < WIDTH; x++) {
                char cell = map[y][x];
                if (cell != '-' && cell - '0' >= max_value) {
                    max_value = cell - '0';
                    Point p = {x, y};
                    int d = distance(p, center);

                    if (d < min_distance_to_center) {
                        min_distance_to_center = d;
                        target = p;
                    }
                }
            }
        }

        if (target.x == -1 && target.y == -1)
            break;

        safe = is_target_safe(thor->position, target, map);

        if (!safe)
            map[target.y][target.x] = '-';
    }

    fprintf(stderr, "[DEBUG] target: (%d, %d)\n", target.x, target.y);

    char action[16] = "WAIT";
    double min_strike = (double)size / (double)thor->strikes;
    Point next = {-1, -1};

    if (range(*thor, giants, size) >= min_strike) {
        strcpy(action, "STRIKE");
    } else if (target.x != -1 && target.y != -1) {
        move(*thor, target, action, &next); 
    } else if (is_in_danger(thor->position, map)) {
        fprintf(stderr, "[DEBUG] Thor is in danger, should move\n");

        int min_distance = INT_MAX;

        move_danger(thor->position, &min_distance, action, &next, -1, +0, map);
        move_danger(thor->position, &min_distance, action, &next, -1, +1, map);
        move_danger(thor->position, &min_distance, action, &next, +0, +1, map);
        move_danger(thor->position, &min_distance, action, &next, +1, +1, map);
        move_danger(thor->position, &min_distance, action, &next, +1, +0, map);
        move_danger(thor->position, &min_distance, action, &next, +1, -1, map);
        move_danger(thor->position, &min_distance, action, &next, +0, -1, map);
        move_danger(thor->position, &min_distance, action, &next, -1, -1, map);

        if (strcmp(action, "WAIT") == 0)
            strcpy(action, "STRIKE");
    }

    fprintf(stderr, "(%d, %d) %s\n", next.x, next.y, action);

    if (action[0] == '\0' || (next.x != - 1 && next.y != -1 && map[next.y][next.x] == 0))
        strcpy(action, "WAIT");
    if (strcmp(action, "WAIT") != 0 && strcmp(action, "STRIKE") != 0) {
        thor->position = next;
    }
        
    fprintf(stderr, "[DEBUG] Move to (%d, %d)\n", target.x, target.y);
    printf("%s\n", action);
}

// Chebyshev distance: max(|x2 - x1|, |y2 - y1|)
int distance(Point p, Point q) {
    int dx = abs(p.x - q.x);
    int dy = abs(p.y - q.y);

    if (dx >= dy)
        return dx;
    else
        return dy;
}

// check if thor will not die if he moves to target
bool is_target_safe(Point thor, Point target, char map[HEIGHT][WIDTH]) {
    Point next = thor;

    if (thor.y < target.y)
        next.y++;
    if (thor.y > target.y)
        next.y--;
    if (thor.x < target.x)
        next.x++;
    if (thor.x > target.x)
        next.x--;
    if (map[next.y][next.x] == '0')
        return false;
    else
        return true;
}

// check if thor is at distance of 1 to any giant
bool is_in_danger(Point thor, char map[HEIGHT][WIDTH]) {
    if (thor.y > 0 && map[thor.y - 1][thor.x] == '0')
        return true;
    if (thor.y > 0 && thor.x < WIDTH - 1 && map[thor.y - 1][thor.x + 1] == '0')
        return true;
    if (thor.x < WIDTH - 1 && map[thor.y][thor.x + 1] == '0')
        return true;
    if (thor.x < WIDTH - 1 && thor.y < HEIGHT - 1 && map[thor.y + 1][thor.x + 1] == '0')
        return true;
    if (thor.y < HEIGHT - 1 && map[thor.y + 1][thor.x] == '0')
        return true;
    if (thor.x > 0 && thor.y < HEIGHT - 1 && map[thor.y + 1][thor.x - 1] == '0')
        return true;
    if (thor.x > 0 && map[thor.y][thor.x - 1] == '0')
        return true;
    if (thor.x > 0 && thor.y > 0 && map[thor.y - 1][thor.x - 1] == '0')
        return true;

    return false;
}

// make a move in the direction of p
void move(Player thor, Point p, char *action, Point *next) {
    fprintf(stderr, "[DEBUG] Moving from (%d, %d) to (%d, %d)\n", thor.position.x, thor.position.y, p.x, p.y);
    action[0] = '\0';
    *next = thor.position;

    if (thor.position.y < p.y) {
        strcat(action, "S");
        (next->y)++;
    }
    if (thor.position.y > p.y) {
        strcat(action, "N");
        (next->y)--;
    }
    if (thor.position.x < p.x) {
        strcat(action, "E");
        (next->x)++;
    }
    if (thor.position.x > p.x) {
        strcat(action, "W");
        (next->x)--;
    }
}

// try to make move if thor is close to a giant in another direction
void move_danger(Point thor, int *min_distance, char *action, Point *next,
    int dx, int dy, char map[HEIGHT][WIDTH]) {

    Point center = {21, 8};
    thor.x += dx;
    thor.y += dy;

    if (thor.x < 0)
        return;
    if (thor.x > WIDTH - 1)
        return;
    if (thor.y < 0)
        return;
    if (thor.y > HEIGHT - 1)
        return;
    if (map[thor.y][thor.x] == '0')
        return;

    int d = distance(center, thor);

    if (d < *min_distance) {
        action[0] = '\0';

        if (dy > 0)
            strcat(action, "S");
        if (dy < 0)
            strcat(action, "N");
        if (dx > 0)
            strcat(action, "E");
        if (dx < 0)
            strcat(action, "W");

        *min_distance = d;
        *next = thor;
    }
}

// return how many giants are in range of a strike
int range(Player thor, Point giants[], size_t size) {
    int in_range = 0;

    for (int i = 0; i < size; i++) {
        if (distance(thor.position, giants[i]) <= 4)
            in_range++;
    }

    fprintf(stderr, "[DEBUG] Number of giants in range: %d\n", in_range);

    return in_range;
}

void print_player(Player p) {
    fprintf(stderr, "[DEBUG] Position: (%d, %d) - Strikes left: %d\n",
        p.position.x, p.position.y, p.strikes);
}

void print_giants(Point *g, size_t size) {
    fprintf(stderr, "[DEBUG] Giants: [ ");

    for (int i = 0; i < size; i++) {
        fprintf(stderr, "(%d, %d)", g[i].x, g[i].y);

        if (i < size - 1)
            fprintf(stderr, ", ");
        else
            fprintf(stderr, " ]\n");
    }
}

void print_map(char map[HEIGHT][WIDTH], Player thor) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (x == thor.position.x && y == thor.position.y)
                fprintf(stderr, "X");
            else
                fprintf(stderr, "%c", map[y][x]);
        }
        fprintf(stderr, "\n");
    }
}

#include <stdio.h>
#include <math.h>

#define WIDTH   200
#define HEIGHT  150 

typedef struct Point {
    int x;
    int y;
} point;

point current, goal;

void input();
double distance(point p, point q);
void solve();
double move(point q);

int main() {
    input();
    solve();
    return 0;
}

void input() {
    int x, y, u, v;
    scanf("%d%d%d%d", &x, &y, &u, &v);

    current.x   = x;
    current.y   = y;
    goal.x      = u;
    goal.y      = v;
}

double distance(point p, point q) {
    return sqrt(pow((p.x - q.x), 2) + pow((p.y - q.y), 2));
}

void solve() {
    fprintf(stderr, "Direct distance: %0.1f\n", distance(current, goal));

    point q;
    
    if (current.x < WIDTH / 2) {
        if (goal.x < current.x + WIDTH - goal.x) {
            q.x = goal.x;
        } else {
            q.x = current.x + current.x + WIDTH - goal.x;
        }
    } else {
        if (goal.x > WIDTH / 2) {
            q.x = goal.x;
        } else {
            q.x = current.x + current.x - (WIDTH + goal.x);
        }
    }

    if (current.y < HEIGHT / 2) {
        if (goal.y < current.y + HEIGHT - goal.y) {
            q.y = goal.y;
        } else {
            q.y = current.y + current.y + HEIGHT - goal.y;
        }
    } else {
        if (goal.y > HEIGHT / 2) {
            q.y = goal.y;
        } else {
            q.y = current.y + current.y - (HEIGHT + goal.y);
        }
    }
    
    printf("%0.1f\n", move(q));

    fprintf(stderr, "q = (%d, %d)\n", q.x, q.y);
}

double move(point q) {
    double time = 0;
    point p = current;

    while (p.x != q.x || p.y != q.y) {
        fprintf(stderr, "CURRENT = (%d, %d) - TIME = %0.1f\n", p.x, p.y, time);

        if (p.x < q.x && p.y < q.y) { // SE
            p.x++;
            p.y++;
            time += 0.5;
            continue;
        }
        if (p.x > q.x && p.y < q.y) { // SW
            p.x--;
            p.y++;
            time += 0.5;
            continue;
        }
        if (p.x < q.x && p.y > q.y) { // NE
            p.x++;
            p.y--;
            time += 0.5;
            continue;
        }
        if (p.x > q.x && p.y > q.y) { // NW
            p.x--;
            p.y--;
            time += 0.5;
            continue;
        }
        if (p.x == q.x && p.y < q.y) { // S
            p.y++;
            time += 0.4;
            continue;
        }
        if (p.x == q.x && p.y > q.y) { // N
            p.y--;
            time += 0.4;
            continue;
        }
        if (p.x < q.x && p.y == q.y) { // E
            p.x++;
            time += 0.3;
            continue;
        }
        if (p.x > q.x && p.y == q.y) { // W
            p.x--;
            time += 0.3;
            continue;
        }
    }

    return time;
}
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

typedef struct Point {
    char id;
    int x;
    int y;
} Point;

void solve(Point a, Point b, Point c, Point d);
bool is_rhombus(Point a, Point b, Point c, Point d);
bool is_rectangle(Point a, Point b, Point c, Point d);
bool is_parallelogram(Point a, Point b, Point c, Point d);

int main() {
    int n;
    scanf("%d\n", &n);

    for (int i = 0; i < n; i++) {
        Point a, b, c, d;
        scanf("%c %d %d ", &a.id, &a.x, &a.y);
        scanf("%c %d %d ", &b.id, &b.x, &b.y);
        scanf("%c %d %d ", &c.id, &c.x, &c.y);
        scanf("%c %d %d ", &d.id, &d.x, &d.y);

        solve(a, b, c, d);
    }

    return 0;
}

void solve(Point a, Point b, Point c, Point d) {
    if (is_rectangle(a, b, c, d) && is_rhombus(a, b, c, d)) {
        printf("%c%c%c%c is a square.\n", a.id, b.id, c.id, d.id);
        return;
    }

    if (is_rectangle(a, b, c, d)) {
        printf("%c%c%c%c is a rectangle.\n", a.id, b.id, c.id, d.id);
        return;
    }

    if (is_rhombus(a, b, c, d)) {
        printf("%c%c%c%c is a rhombus.\n", a.id, b.id, c.id, d.id);
        return;
    }

    if (is_parallelogram(a, b, c, d)) {
        printf("%c%c%c%c is a parallelogram.\n", a.id, b.id, c.id, d.id);
        return;
    }

    printf("%c%c%c%c is a quadrilateral.\n", a.id, b.id, c.id, d.id);
}

// is a parallelogram if both opposite sides are parallel to each other
bool is_parallelogram(Point a, Point b, Point c, Point d) {
    int abx = b.x - a.x;
    int aby = b.y - a.y;
    int bcx = c.x - b.x;
    int bcy = c.y - b.y;
    int cdx = d.x - c.x;
    int cdy = d.y - c.y;
    int dax = a.x - d.x;
    int day = a.y - d.y;

    // ab | cd
    if (abx * cdy - aby * cdx != 0) return false;
    // bc | da
    if (bcx * day - bcy * dax != 0) return false;

    return true;
}

// is a rhombus if the 4 side's length are equal
bool is_rhombus(Point a, Point b, Point c, Point d) {
    int ab = pow(a.x - b.x, 2) + pow(a.y - b.y, 2);
    int bc = pow(b.x - c.x ,2) + pow(b.y - c.y, 2);
    int cd = pow(c.x - d.x ,2) + pow(c.y - d.y, 2);
    int da = pow(d.x - a.x ,2) + pow(d.y - a.y, 2);

    return ab == bc && bc == cd && cd == da;
}

// is a rectangle if the 4 angles are right
bool is_rectangle(Point a, Point b, Point c, Point d) {
    int abx = b.x - a.x;
    int aby = b.y - a.y;

    int bcx = c.x - b.x;
    int bcy = c.y - b.y;

    int cdx = d.x - c.x;
    int cdy = d.y - c.y;

    int dax = a.x - d.x;
    int day = a.y - d.y;

    // AB -> BC
    if (abx * bcx + aby * bcy != 0) return false;

    // BC -> CD
    if (bcx * cdx + bcy * cdy != 0) return false;

    // CD -> DA
    if (cdx * dax + cdy * day != 0) return false;

    // If 3 angles are right, the fourth mast be right
    return true;
}

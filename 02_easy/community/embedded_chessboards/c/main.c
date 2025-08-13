#include <stdio.h>
#include <math.h>

void solve(int row, int col, int is_white);

int main() {
    int test_cases;
    scanf("%d", &test_cases);

    for (int i = 0; i < test_cases; i++) {
        int row, col, is_white;
        scanf("%d%d%d", &row, &col, &is_white);

        solve(row, col, is_white);
    }

    return 0;
}

void solve(int row, int col, int is_white) {
    int chessboards = (row - 7) * (col - 7);

    if (!is_white)
        chessboards--;

    chessboards = ceil((double)chessboards / 2);

    printf("%d\n", chessboards);
}

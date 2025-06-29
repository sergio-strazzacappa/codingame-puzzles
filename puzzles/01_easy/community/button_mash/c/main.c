#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>

int n;

void solve();

int main() {
    scanf("%d", &n);
    solve();

    return 0;
}

void solve() {
    int presses = 0;

    while (n > 1) { // go from n until 0 is reached
        // x2 if can divide by 2
        if (n % 2 == 0) {
            n /= 2;
            presses++;
            continue;
        }

        // +1 and count next divisions
        int tmp = n + 1;
        int count_plus = 0;
        while (tmp % 2 == 0) {
            tmp /= 2;
            count_plus++;
        }

        // -1 and count next divisions
        tmp = n - 1;
        int count_minus = 0;
        while (tmp % 2 == 0) {
            if (tmp == 2) {
                // shortcut
                count_minus = INT_MAX;
                break;
            }
            tmp /=  2;
            count_minus++;
        }

        if (count_plus > count_minus)
            // best +1
            n++;
        else if (count_minus > count_plus)
            // best -1
            n--;
        else {
            // equal, find closest pow of 2 to decide if +1 or -1
            int closest = 0;
            for (int i = 0; i < n; i++) {
                int next = pow(2, i);

                if (abs(next - n) < abs(closest - n))
                    closest = next;
            }

            if (closest > n)
                n++;
            else
                n--;
        }
        presses++;
    }
    presses++;

    printf("%d\n", presses);
}

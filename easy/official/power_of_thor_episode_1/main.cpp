#include <bits/stdc++.h>

using namespace std;

#define ll long long

void solve() {
    int light_x, light_y, initial_tx, initial_ty, tx, ty;

    cin >> light_x;
    cin.ignore();

    cin >> light_y;
    cin.ignore();

    cin >> initial_tx;
    cin.ignore();

    cin >> initial_ty;
    cin.ignore();

    tx = initial_tx;
    ty = initial_ty;

    while (true) {
        int remaining_turns;
        string direction = "";

        cin >> remaining_turns;
        cin.ignore();

        if (ty > light_y) {
            direction += "N";
            ty--;
        } else if (ty < light_y) {
            direction += "S";
            ty++;
        }
        if (tx > light_x) {
            direction += "W";
            tx--;
        } else if (tx < light_x) {
            direction += "E";
            tx++;
        }
        cout << direction << endl;
    }
}

int main() {
    solve();
}

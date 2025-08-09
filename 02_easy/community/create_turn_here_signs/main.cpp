#include <iostream>
#define N 5

using namespace std;

void solve(string direction, int param[]) {
    int quantity = param[0];
    int height = param[1];
    int width = param[2];
    int space = param[3];
    int indent = param[4];

    string arrow = "";

    if (direction == "right") {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < quantity; j++) {
                if (i <= height / 2 && j == 0) {
                    for (int k = 0; k < indent * i; k++) {
                        arrow += ' ';
                    }
                } else {
                    for (int k = indent * (height - i - 1); k > 0 && j == 0; k--) {
                        arrow += ' ';
                    }
                }
                for (int k = 0; k < width; k++) {
                    arrow += '>';
                }
                if (j != quantity - 1) {
                    for (int k = 0; k < space; k++) {
                        arrow += ' ';
                    }
                }
            }
            arrow += '\n';
        }
    } else {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < quantity; j++) {
                if (i <= height / 2 && j == 0) {
                    for (int k = indent * (height / 2 - i); k > 0; k--) {
                        arrow += ' ';
                    }
                } else if (j == 0) {
                    for (int k = 0; k < indent * (i - height / 2); k++) {
                        arrow += ' ';
                    }
                }
                for (int k = 0; k < width; k++) {
                    arrow += '<';
                }
                if (j != quantity - 1) {
                    for (int k = 0; k < space; k++) {
                        arrow += ' ';
                    }
                }
            }
            arrow += '\n';
        }
    }
    cout << arrow;
}

int main() {
    string direction;
    int params[N];

    cin >> direction;
    for (int i = 0; i < N; i++) {
        cin >> params[i];
    }
    solve(direction, params);
}
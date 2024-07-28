#include <iostream>
#include <string>

using namespace std;

int search(int start, string map[], int w, int h) {
    int current_line = start;
    int depth = 0;

    while (depth < (h - 2)) {
        if (current_line == 0) {
            if (map[depth][current_line + 1] == '-') {
                current_line += 3;
            }
        } else if (current_line == w) {
            if (map[depth][current_line - 1] == '-') {
                current_line -= 3;
            }
        } else {
            if (map[depth][current_line - 1] == '-') {
                current_line -= 3;
            } else if (map[depth][current_line + 1] == '-') {
                current_line += 3;
            }
        }
        depth++;
    }
    return current_line;
}

void solve(char top[], char bottom[], string map[], int w, int h) {
    for (int i = 0; i < w; i++) {
        if (top[i] != ' ') {
            cout << top[i] << bottom[search(i, map, w, h)] << endl;
        }
    }
}

int main() {
    int w, h;
    cin >> w >> h;
    cin.ignore();

    char top[w];
    char bottom[w];
    string map[h - 2];

    for (int i = 0; i < h; i++) {
        string row;
        getline(cin, row);

        for (int j = 0; j < w; j++) {
            if (i == 0) {
                top[j] = row[j];
            } else if (i == h - 1) {
                bottom[j] = row[j];
            } else {
                map[i - 1] = row;
            }
        }
    }

    solve(top, bottom, map, w, h);
}
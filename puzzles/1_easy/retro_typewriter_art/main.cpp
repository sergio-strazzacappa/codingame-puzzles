#include <iostream>
#include <vector>

using namespace std;

vector<string> chunks;

void split(string recipe) {
    string chunk = "";
    for (char c : recipe) {
        if (c != ' ') {
            chunk += c;
        } else {
            chunks.push_back(chunk);
            chunk = "";
            continue;
        }
    }
    chunks.push_back(chunk);
}

string parse(string s) {
    string image = "";
    char c = '"';

    // nl
    if (s == "nl") {
        cout << endl;
        return image;
    }

    // sp
    if (s[s.size() - 1] == 'p' && s[s.size() - 2] == 's') {
        c = ' ';
    }

    // bS
    if (s[s.size() - 1] == 'S' && s[s.size() - 2] == 'b') {
        c = '\\';
    }

    // sQ
    if (s[s.size() - 1] == 'Q' && s[s.size() - 2] == 's') {
        c = '\'';
    }

    int quantity = 0;
    int mult = 1;
    int limit = s.size() - 1;

    if (c != '"') {
        limit = s.size() - 2;
    } else {
        c = s[s.size() - 1];
    }

    for (int i = 0; i < limit; i++) {
        quantity = quantity * mult + s[i] - 48;
        mult = mult * 10;
    }

    for (int j = 0; j < quantity; j++) {
        image += c;
    }

    return image;
}

void solve(string recipe) {
    split(recipe);

    for (string s : chunks) {
        cout << parse(s);
    }
}

int main() {
    string recipe;
    getline(cin, recipe);

    solve(recipe);
}
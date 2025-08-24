#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <iomanip>
#include <math.h>

using namespace std;

map<string, int> resitances;
stack<double> open;

void solve(string circuit) {
    string name = "";

    for (int i = 0; i < circuit.size(); i++) {
        if (circuit[i] == '(' || circuit[i] == '[') {
            if (circuit[i] == '(') {
                open.push(INT32_MAX);
            }
            if (circuit[i] == '[') {
                open.push(INT32_MIN);
            }
        }
        if (circuit[i] == ' ' && name != "") { 
            open.push(resitances[name]);
            name = "";
        }
        if (isalpha(circuit[i])) {
            name += circuit[i];
        }
        if (circuit[i] == ')' || circuit[i] == ']') {
            char symbol = circuit[i];
            double sum = 0.0;
            if (symbol == ')') {
                while (open.top() != INT32_MAX) {
                    sum += open.top();
                    open.pop();
                }
            }
            if (symbol == ']') {
                while (open.top() != INT32_MIN) {
                    sum += 1 / open.top();
                    open.pop();
                }
                sum = 1 / sum;
            }
            open.pop();
            open.push(sum);
        }
    }
    printf("%.1f\n", open.top());
}

int main() {
    int n;
    cin >> n;
    cin.ignore();

    for (int i = 0; i < n; i++) {
        string name;
        int r;
        cin >> name >> r;
        cin.ignore();

        resitances.insert(pair<string, int>(name, r));
    }

    string circuit;
    getline(cin, circuit);

    solve(circuit);
}
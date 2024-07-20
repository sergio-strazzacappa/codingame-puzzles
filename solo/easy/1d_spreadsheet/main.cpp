#include <iostream>
#include <string>
#include <vector>

using namespace std;

string operations[4] = { "VALUE", "ADD", "SUB", "MULT" };

struct Cell {
    string operation;
    string arg_1;
    string arg_2;
    int index;
};

bool has_dep(string arg, int result[]) {
    if (arg[0] == '$') {
        return result[stoi(arg.substr(1))] != -INT32_MAX;
    } else {
        return true;
    }
}

int value(string arg, int result[]) {
    if (arg[0] == '$') {
        string cell = arg.substr(1);
        return result[stoi(arg.substr(1))];
    } else {
        return stoi(arg);
    }
}

int add(string arg_1, string arg_2, int result[]) {
    int op1;
    int op2;

    if (arg_1[0] == '$') {
        op1 = result[stoi(arg_1.substr(1))];
    } else {
        op1 = stoi(arg_1);
    }

    if (arg_2[0] == '$') {
        op2 = result[stoi(arg_2.substr(1))];
    } else {
        op2 = stoi(arg_2);
    }
    return op1 + op2;
}

int sub(string arg_1, string arg_2, int result[]) {
    int op1;
    int op2;

    if (arg_1[0] == '$') {
        op1 = result[stoi(arg_1.substr(1))];
    } else {
        op1 = stoi(arg_1);
    }

    if (arg_2[0] == '$') {
        op2 = result[stoi(arg_2.substr(1))];
    } else {
        op2 = stoi(arg_2);
    }

    return op1 - op2;
}

int mult(string arg_1, string arg_2, int result[]) {
    int op1;
    int op2;

    if (arg_1[0] == '$') {
        op1 = result[stoi(arg_1.substr(1))];
    } else {
        op1 = stoi(arg_1);
    }

    if (arg_2[0] == '$') {
        op2 = result[stoi(arg_2.substr(1))];
    } else {
        op2 = stoi(arg_2);
    }

    return op1 * op2;
}

int solve(string operation, string arg_1, string arg_2, int result[]) {
    if (operation == operations[0]) {
        return value(arg_1, result);
    }
    if (operation == operations[1]) {
        return add(arg_1, arg_2, result);
    }
    if (operation == operations[2]) {
        return sub(arg_1, arg_2, result);
    }
    if (operation == operations[3]) {
        return mult(arg_1, arg_2, result);
    }
    return 0;
}

int main() {
    int n;
    cin >> n;
    cin.ignore();

    int result[n];
    vector<Cell> left;

    for (int i = 0; i < n; i++) {
        result[i] = -INT32_MAX;
    }

    for (int i = 0; i < n; i++) {
        string operation;
        string arg_1;
        string arg_2;
        cin >> operation >> arg_1 >> arg_2;
        cin.ignore();

        Cell c = {operation, arg_1, arg_2, i};
        left.push_back(c);
    }

    while (!left.empty()) {
        cerr << left.size() << endl;
        for (unsigned i = 0; i < left.size(); i++) {
            Cell c = left[i];
            if (has_dep(c.arg_1, result) && has_dep(c.arg_2, result)) {
                result[c.index] = solve(c.operation, c.arg_1, c.arg_2, result);
                left.erase(left.begin() + i);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        cout << result[i] << endl;
    }
}
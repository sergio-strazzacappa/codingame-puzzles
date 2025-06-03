#include <iostream>

using namespace std;

struct Signal {
    string name;
    string signal;
};


void print_input(Signal input[], int n) {
    cerr << "### INPUT SIGNALS ###" << endl;

    for (int i = 0; i < n; i++ ) {
        cerr << "Name: " << input[i].name << " Signal: " << input[i].signal;
        cerr << endl;
    }
}

string search_signal(string name, Signal input[], int n) {
    string signal = "";

    for (int i = 0; i < n; i++) {
        if (input[i].name == name) {
            signal = input[i].signal;
            break;
        }
    }
    return signal;
}

Signal solve(string name, string type, string input_1, string input_2) {
    Signal s = {name, ""};

    string signal_1;
    string signal_2;

    if (type == "AND") {
        for (int i = 0; i < input_1.size(); i++) {
            if (input_1[i] == '-' && input_2[i] == '-') {
                s.signal += '-';
            } else {
                s.signal += '_';
            }
        }
    }

    if (type == "OR") {
        for (int i = 0; i < input_1.size(); i++) {
            if (input_1[i] == '_' && input_2[i] == '_') {
                s.signal += '_';
            } else {
                s.signal += '-';
            }
        }
    }

    if (type == "XOR") {
        for (int i = 0; i < input_1.size(); i++) {
            if ((input_1[i] == '_' && input_2[i] == '_') ||
                (input_1[i] == '-' && input_2[i] == '-')) {
                s.signal += '_';
            } else {
                s.signal += '-';
            }
        }
    }

    if (type == "NAND") {
        for (int i = 0; i < input_1.size(); i++) {
            if (input_1[i] == '-' && input_2[i] == '-') {
                s.signal += '_';
            } else {
                s.signal += '-';
            }
        }
    }

    if (type == "NOR") {
        for (int i = 0; i < input_1.size(); i++) {
            if (input_1[i] == '_' && input_2[i] == '_') {
                s.signal += '-';
            } else {
                s.signal += '_';
            }
        }
    }

    if (type == "NXOR") {
        for (int i = 0; i < input_1.size(); i++) {
            if ((input_1[i] == '_' && input_2[i] == '_') ||
                (input_1[i] == '-' && input_2[i] == '-')) {
                s.signal += '-';
            } else {
                s.signal += '_';
            }
        }
    }

    return s;
}

int main() {
    int n, m;
    cin >> n >> m;
    cin.ignore();

    Signal input[n];
    Signal result[m];

    for (int i = 0; i < n; i++) {
        string input_name;
        string input_signal;
        cin >> input_name >> input_signal;
        cin.ignore();

        Signal s = {input_name, input_signal};
        input[i] = s;
    }

    //print_input(input, n);

    for (int i = 0; i < m; i++) {
        string output_name;
        string type;
        string input_name_1;
        string input_name_2;
        cin >> output_name >> type >> input_name_1 >> input_name_2;
        cin.ignore();

        string signal_1 = search_signal(input_name_1, input, n);
        string signal_2 = search_signal(input_name_2, input, n);

        result[i] = solve(output_name, type, signal_1, signal_2);
    }

    for (int i = 0; i < m; i++) {
        cout << result[i].name << " " << result[i].signal << endl;
    }
}
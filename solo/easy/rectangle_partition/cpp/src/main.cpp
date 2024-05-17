#include <iostream>
#include <ctime>
#include <map>
#include "include/main.h"
#include "include/input.h"
#include "include/output.h"

const int FILES_QUANTITY = 10;

int main() {
    // Input files for testing
    vector<string> input_files = 
        {
            "input/test1.txt",
            "input/test2.txt",
            "input/test3.txt",
            "input/test4.txt",
            "input/test5.txt",
            "input/test6.txt",
            "input/test7.txt",
            "input/test8.txt",
            "input/test9.txt",
            "input/test10.txt"
        };

    // Output files for testing
    vector<string> output_files =
        {
            "output/test1.txt",
            "output/test2.txt",
            "output/test3.txt",
            "output/test4.txt",
            "output/test5.txt",
            "output/test6.txt",
            "output/test7.txt",
            "output/test8.txt",
            "output/test9.txt",
            "output/test10.txt"
        };

    for (int i = 0; i < FILES_QUANTITY; i++) {
        cout << "Ejecutando: " << input_files[i] << '\n';

        solve(input_files[i], output_files[i]);
    }

    cout << "\n\nProgram finished succesfully\n";

    return 0;
}

void solve(string input_file, string output_file) {
    // Read data from input
    Input input(input_file);
    input.read_data();

    int solution = logic(
        input.get_width(),
        input.get_height(), 
        input.get_mesurements_x(),
        input.get_mesurements_y()
    );

    Output output(output_file);
    output.read_data();

    check_answer(solution, output.get_answer(), input_file);
}

int logic(int width, int height, vector<int> x, vector<int> y) {
    // Insert the last index of the width
    x.insert(x.begin(), 0);
    x.push_back(width);

    // Insert the last index of the height
    y.insert(y.begin(), 0);
    y.push_back(height);

    int t0, t1;

    t0 = clock();
    int solution = create_subrectangles(x, y);
    t1 = clock();

    long double time = (double(t1 - t0) / CLOCKS_PER_SEC);
    cout << "Execution Time: " << time << '\n';

    return solution;
}

int create_subrectangles(vector<int> x, vector<int> y) {
    map<int, int> meditions;
    int squares = 0;

    // Setting the width
    for (int i = 0; i < x.size(); i++) {
        for (int j = i + 1; j < x.size(); j++) {
            int w = x[j] - x[i]; // Width of a medition
            int quantity = meditions.count(w);
            if (quantity == 0) {
                meditions.insert(pair<int, int>(w, 1));
            } else {
                meditions[w]++;
            }
        }
    }

    // Setting the height
    for (int i = 0; i < y.size(); i++) {
        for (int j = i + 1; j < y.size(); j++) {
            int h = y[j] - y[i]; // Height of a medition
            int quantity = meditions.count(h);
            if (quantity != 0) {
                squares += meditions[h];
            }
        }
    }

    cout << "Answer: " << squares << '\n';
    return squares;
}

void print_map(map<int, int> m) {
    map<int, int>::iterator it;

    for (it = m.begin(); it != m.end(); ++it) {
        cout << it->first << '\t' << it->second << '\n';
    }
    cout << '\n';
}

void check_answer(int solution, int answer, string input_file) {
    if (solution == answer) {
        cout << input_file << ": correct answer\n";
    } else {
        cout << input_file << ": incorrect answer\n";
        exit(1);
    }
}
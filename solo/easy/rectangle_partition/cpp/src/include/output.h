#ifndef OUTPUT_H
#define OUTPUT_H

#include <string>

using namespace std;

class Output {
    string file;
    int answer;

    public:
        // Constructor
        Output(string file);

        // Getters
        string get_file();
        int get_answer();

        // Setters
        void set_file(string file);
        void set_answer(int answer);

        // Public methods
        void read_data();
        void debug();
};

#endif
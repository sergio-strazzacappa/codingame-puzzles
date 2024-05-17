#include <iostream>
#include <fstream>
#include "include/output.h"

// Constructors
Output::Output(string file) {
    this->file = file;
    this->answer = 0;
}

// Getters
string Output::get_file() {
    return this->file;
}

int Output::get_answer() {
    return this->answer;
}

// Setters
void Output::set_file(string file) {
    this->file = file;
}

void Output::set_answer(int answer) {
    this->answer = answer;
}

// Public methods
void Output::read_data() {
    ifstream file(this->file);

    if (!file.is_open()) {
        cerr << "Error trying to open the file\n";
    }
    
    file >> this->answer;
}

void Output::debug() {
    cout 
        << "DEBUG OUTPUT: \n"
        << "File: " << this->file << '\n'
        << "Answer: " << this->answer << '\n';
}
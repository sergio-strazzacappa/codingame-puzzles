#include <iostream>
#include <fstream>
#include "include/input.h"

using namespace std;

// Private methods
void Input::print_mesurements_x() {
    cout << "Mesurements x: \n[ ";

    for (int i = 0; i < this->count_x; i++) {
        cout << this->mesurements_x[i] << ' ';
    }
    cout << " ]\n";
}

void Input::print_mesurements_y() {
    cout << "Mesurements y: \n[ ";

    for (int i = 0; i < this->count_y; i++) {
        cout << this->mesurements_y[i] << ' ';
    }
    cout << " ]\n";
}

// Constructors
Input::Input() {
    this->file = "";
    this->width = 0;
    this->height = 0;
    this->count_x = 0;
    this->count_y = 0;
    this->mesurements_x = {};
    this->mesurements_y = {};
}

Input::Input(string file) {
    this->file = file;
    this->width = 0;
    this->height = 0;
    this->count_x = 0;
    this->count_y = 0;
    this->mesurements_x = {};
    this->mesurements_y = {};
}

Input::Input(int width, int height, int count_x, int count_y) {
    this->width = width;
    this->height = height;
    this->count_x = count_x;
    this->count_y = count_y;
}

// Getters
string Input::get_file() {
    return this->file;
}

int Input::get_width() {
    return this->width;
}

int Input::get_height() {
    return this->height;
}

int Input::get_count_x() {
    return this->count_x;
}

int Input::get_count_y() {
    return this->count_y;
}

vector<int> Input::get_mesurements_x() {
    return this->mesurements_x;
}

vector<int> Input::get_mesurements_y() {
    return this->mesurements_y;
}

// Setters
void Input::set_file(string file) {
    this->file = file;
}

void Input::set_width(int width) {
    this->width = width;
}

void Input::set_height(int height) {
    this->height = height;
}

void Input::set_count_x(int count_x) {
    this->count_x = count_x;
}

void Input::set_count_y(int count_y) {
    this->count_y = count_y;
}

void Input::set_mesurements_x(vector<int> mesurements_x) {
    this->mesurements_x = mesurements_x;
}

void Input::set_mesurements_y(vector<int> mesurements_y) {
    this->mesurements_y = mesurements_y;
}

// Public methods
void Input::read_data() {
    ifstream file(this->file);

    if (!file.is_open()) {
        cerr << "Error trying to open the file\n";
    }

    file >> this->width;
    file >> this->height;
    file >> this->count_x;
    file >> this->count_y;

    for (int i = 0; i < this->count_x; i++) {
        int x;
        file >> x;
        this->mesurements_x.push_back(x);
    }

    for (int i = 0; i < this->count_y; i++) {
        int y;
        file >> y;
        this->mesurements_y.push_back(y);
    }
}

void Input::debug() {
    cout 
        << "DEBUG INPUT: \n"
        << "Width: " << this->width << '\n'
        << "Height: " << this->height << '\n'
        << "Count x: " << this->count_x << '\n'
        << "Count y: " << this->count_y << '\n';

        this->print_mesurements_x();
        this->print_mesurements_y();

    cout << '\n';
}
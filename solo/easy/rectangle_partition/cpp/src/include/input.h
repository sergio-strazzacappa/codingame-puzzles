#ifndef INPUT_H
#define INPUT_H

#include <vector>
#include <string>

using namespace std;

class Input {
    // Atributes
    string file;
    int width;
    int height;
    int count_x;
    int count_y;
    vector<int> mesurements_x;
    vector<int> mesurements_y;

    // Private methods
    void print_mesurements_x();
    void print_mesurements_y();

    public:
        // Constructors
        Input();
        Input(string file);
        Input(int width, int height, int count_x, int count_y);

        // Getters
        string get_file();
        int get_width();
        int get_height();
        int get_count_x();
        int get_count_y();
        vector<int> get_mesurements_x();
        vector<int> get_mesurements_y();

        // Setters
        void set_file(string file);
        void set_width(int width);
        void set_height(int height);
        void set_count_x(int count_x);
        void set_count_y(int count_y);
        void set_mesurements_x(vector<int> mesurements_x);
        void set_mesurements_y(vector<int> mesurements_y);

        // Public methods
        void read_data();
        void debug();
};

#endif
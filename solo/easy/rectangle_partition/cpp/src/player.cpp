// Complete code for codingame

#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

class Input {
    int width;
    int height;
    int count_x;
    int count_y;
    vector<int> mesurements_x;
    vector<int> mesurements_y;

    void print_mesurements_x() {
        cout << "Mesurements x: \n[ ";

        for (int i = 0; i < this->count_x; i++) {
            cout << this->mesurements_x[i] << ' ';
        }
        cout << " ]\n";
    }

    void print_mesurements_y() {
        cout << "Mesurements y: \n[ ";

        for (int i = 0; i < this->count_y; i++) {
            cout << this->mesurements_y[i] << ' ';
        }
        cout << " ]\n";
    }

    public:
    Input() {
        this->width = 0;
        this->height = 0;
        this->count_x = 0;
        this->count_y = 0;
        this->mesurements_x = {};
        this->mesurements_y = {};
    }

    Input(string file) {
        this->width = 0;
        this->height = 0;
        this->count_x = 0;
        this->count_y = 0;
        this->mesurements_x = {};
        this->mesurements_y = {};
    }

    Input(int width, int height, int count_x, int count_y) {
        this->width = width;
        this->height = height;
        this->count_x = count_x;
        this->count_y = count_y;
    }

    int get_width() {
        return this->width;
    }

    int get_height() {
        return this->height;
    }

    int get_count_x() {
        return this->count_x;
    }

    int get_count_y() {
        return this->count_y;
    }

    vector<int> get_mesurements_x() {
        return this->mesurements_x;
    }

    vector<int> get_mesurements_y() {
        return this->mesurements_y;
    }

    void set_width(int width) {
        this->width = width;
    }

    void set_height(int height) {
        this->height = height;
    }

    void set_count_x(int count_x) {
        this->count_x = count_x;
    }

    void set_count_y(int count_y) {
        this->count_y = count_y;
    }

    void set_mesurements_x(vector<int> mesurements_x) {
        this->mesurements_x = mesurements_x;
    }

    void set_mesurements_y(vector<int> mesurements_y) {
        this->mesurements_y = mesurements_y;
    }

    void read_data() {
        cin >> this->width >> this->height >> this->count_x >> this->count_y;
        cin.ignore();

        for (int i = 0; i < this->count_x; i++) {
            int x;
            cin >> x;
            cin.ignore();
            this->mesurements_x.push_back(x);
        }

        for (int i = 0; i < this->count_y; i++) {
            int y;
            cin >> y;
            cin.ignore();
            this->mesurements_y.push_back(y);
        }
    }

    void debug() {
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
};

void print_map(map<int, int> m) {
    map<int, int>::iterator it;

    for (it = m.begin(); it != m.end(); ++it) {
        cout << it->first << '\t' << it->second << '\n';
    }
    cout << '\n';
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
    return squares;
}

int logic(int width, int height, vector<int> x, vector<int> y) {
    // Insert the last index of the width
    x.insert(x.begin(), 0);
    x.push_back(width);

    // Insert the last index of the height
    y.insert(y.begin(), 0);
    y.push_back(height);

    return create_subrectangles(x, y);
}

int main() {
    // Read data from input
    Input input;
    input.read_data();

    int solution = logic(
        input.get_width(),
        input.get_height(), 
        input.get_mesurements_x(),
        input.get_mesurements_y()
    );

    cout << solution << '\n';
    
    return 0;
}
#include <iostream>
#include <vector>
#include <queue>
#include <string.h>

using namespace std;

struct Node {
    int row;
    int column;
    int distance;
    bool operator==(Node n) {
        return row == n.row && column == n.column;
    }
};

class Maze {
    private:
        int rows;
        int columns;
        char** map;

    public:
        Maze() {
            rows = 0;
            columns = 0;
        }

        void set_rows(int r) {
            rows = r;
        }

        void set_columns(int c) {
            columns = c;
        }

        int get_rows() {
            return rows;
        }

        int get_columns() {
            return columns;
        }

        void init_map() {
            map = new char*[rows];

            for (int i = 0; i < rows; i++) {
                map[i] = new char[columns];
                memset(map[i], '-', columns * sizeof(char));
            }
        }

        void add_cell(int r, int c, char content) {
            map[r][c] = content;
        }

        bool is_empty(int row, int column) {
            return map[row][column] == '.';
        }

        void print_general_info() {
            cerr << "### MAZE ###" << endl;
            cerr << "Rows: " << rows << endl;
            cerr << "Columns: " << columns << endl;
        }

        void print_map() {
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < columns; j++) {
                    cerr << map[i][j];
                }
                cerr << endl;
            }
        }

        void generate_map() {
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < columns; j++) {
                    cout << map[i][j];
                }
                cout << endl;
            }
        }
};

Maze maze;
Maze result;

Node init() {
    Node root;
    root.distance = 0;

    int w, h;
    cin >> w >> h;
    cin.ignore();

    maze.set_rows(h);
    maze.set_columns(w);
    maze.init_map();

    result.set_rows(h);
    result.set_columns(w);
    result.init_map();

    for (int i = 0; i < maze.get_rows(); i++) {
        string row;
        getline(cin, row);

        for (int j = 0; j < maze.get_columns(); j++) {
            maze.add_cell(i, j, row[j]);
            result.add_cell(i, j, row[j]);

            if (row[j] == 'S') {
                root.row = i;
                root.column = j;
            }
        }
    }

    return root;
}

template<typename T>
bool find_element(vector<T> v, T elem) {
    for (T e : v) {
        if (e == elem) {
            return true;
        }
    }
    return false;
}

char get_char(int n) {
    switch (n) {
        case 0: return '0'; break;
        case 1: return '1'; break;
        case 2: return '2'; break;
        case 3: return '3'; break;
        case 4: return '4'; break;
        case 5: return '5'; break;
        case 6: return '6'; break;
        case 7: return '7'; break;
        case 8: return '8'; break;
        case 9: return '9'; break;
        case 10: return 'A'; break;
        case 11: return 'B'; break;
        case 12: return 'C'; break;
        case 13: return 'D'; break;
        case 14: return 'E'; break;
        case 15: return 'F'; break;
        case 16: return 'G'; break;
        case 17: return 'H'; break;
        case 18: return 'I'; break;
        case 19: return 'J'; break;
        case 20: return 'K'; break;
        case 21: return 'L'; break;
        case 22: return 'M'; break;
        case 23: return 'N'; break;
        case 24: return 'O'; break;
        case 25: return 'P'; break;
        case 26: return 'Q'; break;
        case 27: return 'R'; break;
        case 28: return 'S'; break;
        case 29: return 'T'; break;
        case 30: return 'U'; break;
        case 31: return 'V'; break;
        case 32: return 'W'; break;
        case 33: return 'X'; break;
        case 34: return 'Y'; break;
        case 35: return 'Z'; break;
    }
}

void BFS(Node root) {
    vector<Node> explored;
    queue<Node> frontier;

    result.add_cell(root.row, root.column, get_char(root.distance));

    explored.push_back(root);
    frontier.push(root);

    while (!frontier.empty()) {
        Node current = frontier.front();
        frontier.pop();

        int new_column, new_row;

        new_column = current.column + 1;

        if (new_column == maze.get_columns()) {
            new_column = 0;
        }

        if (maze.is_empty(current.row, new_column)) {
            Node n {
                current.row,
                new_column,
                current.distance
            };

            if (!find_element(explored, n)) {
                n.distance = n.distance + 1;
                result.add_cell(current.row, new_column, get_char(n.distance));
                explored.push_back(n);
                frontier.push(n);
            }
        }

        new_row = current.row + 1;

        if (new_row == maze.get_rows()) {
            new_row = 0;
        }

        if (maze.is_empty(new_row, current.column)) {
            Node n {
                new_row,
                current.column,
                current.distance
            };

            if (!find_element(explored, n)) {
                n.distance = n.distance + 1;
                result.add_cell(new_row, current.column, get_char(n.distance));
                explored.push_back(n);
                frontier.push(n);
            }
        }

        new_column = current.column - 1;

        if (current.column - 1 == -1) {
            new_column = maze.get_columns() - 1;
        }

        if (maze.is_empty(current.row, new_column)) {
            Node n {
                current.row,
                new_column,
                current.distance
            };

            if (!find_element(explored, n)) {
                n.distance = current.distance + 1;
                result.add_cell(current.row, new_column, get_char(n.distance));
                explored.push_back(n);
                frontier.push(n);
            }
        }

        new_row = current.row - 1;

        if (new_row == -1) {
            new_row = maze.get_rows() - 1;
        }

        if (maze.is_empty(new_row, current.column)) {
            Node n {
                new_row,
                current.column,
                current.distance
            };

            if (!find_element(explored, n)) {
                n.distance = current.distance + 1;
                result.add_cell(new_row, current.column, get_char(n.distance));
                explored.push_back(n);
                frontier.push(n);
            }
        }
    }
}

int main() {
    Node root = init();

    maze.print_general_info();
    maze.print_map();
    cerr << endl << endl;

    BFS(root);
    result.generate_map();
}
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <cctype>
#include <algorithm>

using namespace std;

struct Node {
    int id; // id = (row * 100) + column
    char elem;
    int row;
    int column;
};

void print_grid(char* grid, int size) {
    cerr << "THE GRID" << endl << endl;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cerr << *((grid + i * size) + j);
        }
        cerr << endl;
    }
}

void DFS(Node node, map<int, bool> visited, char* grid, int size, string word,
    int index, vector<Node> &solution, int direction, bool &solution_found) {
    
    char next = word[index];

    if (!solution_found && node.elem == next) {
        visited[node.id] = true;

        bool correct_dir = direction == 1 || direction == -1;

        if (node.column <= size - 1 && correct_dir && !solution_found) {
            //cerr << "1 - ELEM: " << node.elem << " NEXT: " << next << " INDEX: " << index << " (" << node.row << ", " << node.column << ")" << endl;
            
            // 1 right
            solution.push_back(node);
            int row = node.row;
            int column = node.column + 1;

            int id = row * 100 + column;

            if (!visited[id]) {
                char elem = *((grid + row * size) + column);

                Node new_node = {id, elem, row, column};

                DFS(new_node, visited, grid, size, word,
                    index + 1, solution, 1, solution_found);

                if (solution.size() == word.size()) {
                    solution_found = true;
                } else {
                    index = 0;
                    solution.clear();
                }
            }
        }

        correct_dir = direction == 2 || direction == -1;

        if (node.row <= size - 1 && node.column <= size - 1 && correct_dir && !solution_found) {
            //cerr << "2 - ELEM: " << node.elem << " NEXT: " << next << " INDEX: " << index << " (" << node.row << ", " << node.column << ")" << endl;

            // 2 right/down
            solution.push_back(node);
            int row = node.row + 1;
            int column = node.column + 1;

            int id = row * 100 + column;

            if (!visited[id]) {
                char elem = *((grid + row * size) + column);

                Node new_node = {id, elem, row, column};

                DFS(new_node, visited, grid, size, word,
                    index + 1, solution, 2, solution_found);
                
                if (solution.size() == word.size()) {
                    solution_found = true;
                } else {
                    index = 0;
                    solution.clear();
                }
            }
        }
        
        correct_dir = direction == 3 || direction == -1;

        if (node.row <= size - 1 && correct_dir && !solution_found) {
            //cerr << "3 - ELEM: " << node.elem << " NEXT: " << next << " INDEX: " << index << " (" << node.row << ", " << node.column << ")" << endl;

            // 3 down
            solution.push_back(node);
            int row = node.row + 1;
            int column = node.column;

            int id = row * 100 + column;

            if (!visited[id]) {
                char elem = *((grid + row * size) + column);

                Node new_node = {id, elem, row, column};

                DFS(new_node, visited, grid, size, word,
                    index + 1, solution, 3, solution_found);

                if (solution.size() == word.size()) {
                    solution_found = true;
                } else {
                    index = 0;
                    solution.clear();
                }
            }
        }

        correct_dir = direction == 4 || direction == -1;

        if (node.row <= size - 1 && node.column >= 0 && correct_dir && !solution_found) {
            //cerr << "4 - ELEM: " << node.elem << " NEXT: " << next << " INDEX: " << index << " (" << node.row << ", " << node.column << ")" << endl;

            // 4 left/down
            solution.push_back(node);
            int row = node.row + 1;
            int column = node.column - 1;

            int id = row * 100 + column;

            if (!visited[id]) {
                char elem = *((grid + row * size) + column);

                Node new_node = {id, elem, row, column};

                DFS(new_node, visited, grid, size, word,
                    index + 1, solution, 4, solution_found);

                if (solution.size() == word.size()) {
                    solution_found = true;
                } else {
                    index = 0;
                    solution.clear();
                }
            }
        }

        correct_dir = direction == 5 || direction == -1;

        if (node.column >= 0 && correct_dir && !solution_found) {
            //cerr << "5 - ELEM: " << node.elem << " NEXT: " << next << " INDEX: " << index << " (" << node.row << ", " << node.column << ")" << endl;

            // 5 left
            solution.push_back(node);
            int row = node.row;
            int column = node.column - 1;

            int id = row * 100 + column;

            if (!visited[id]) {
                char elem = *((grid + row * size) + column);

                Node new_node = {id, elem, row, column};

                DFS(new_node, visited, grid, size, word,
                    index + 1, solution, 5, solution_found);

                if (solution.size() == word.size()) {
                    solution_found = true;
                } else {
                    index = 0;
                    solution.clear();
                }
            }
        }

        correct_dir = direction == 6 || direction == -1;

        //cerr << "Debug: " << node.row << " " << node.column << " " << correct_dir << " " << solution_found << endl;
        if (node.row >= 0 && node.column >= 0 && correct_dir && !solution_found) {
            //cerr << "6 - ELEM: " << node.elem << " NEXT: " << next << " INDEX: " << index << " (" << node.row << ", " << node.column << ")" << endl;

            // 6 left/up
            solution.push_back(node);
            int row = node.row - 1;
            int column = node.column - 1;

            int id = row * 100 + column;

            if (!visited[id]) {
                char elem = *((grid + row * size) + column);

                Node new_node = {id, elem, row, column};

                DFS(new_node, visited, grid, size, word,
                    index + 1, solution, 6, solution_found);

                if (solution.size() == word.size()) {
                    solution_found = true;
                } else {
                    index = 0;
                    solution.clear();
                }
            }
        }

        correct_dir = direction == 7 || direction == -1;

        if (node.row >= 0 && correct_dir && !solution_found) {
            //cerr << "7 - ELEM: " << node.elem << " NEXT: " << next << " INDEX: " << index << " (" << node.row << ", " << node.column << ")" << endl;

            // 7 up
            solution.push_back(node);
            int row = node.row - 1;
            int column = node.column;

            int id = row * 100 + column;

            if (!visited[id]) {
                char elem = *((grid + row * size) + column);

                Node new_node = {id, elem, row, column};

                DFS(new_node, visited, grid, size, word,
                    index + 1, solution, 7, solution_found);

                if (solution.size() >= word.size()) {
                    solution_found = true;
                } else {
                    index = 0;
                    solution.clear();
                }
            }
        }

        correct_dir = direction == 8 || direction == -1;

        if (node.row >= 0 && node.column <= size - 1 && correct_dir && !solution_found) {
            //cerr << "8 - ELEM: " << node.elem << " NEXT: " << next << " INDEX: " << index << " (" << node.row << ", " << node.column << ")" << endl;

            // 8 right/up
            solution.push_back(node);
            int row = node.row - 1;
            int column = node.column + 1;

            int id = row * 100 + column;

            if (!visited[id]) {
                char elem = *((grid + row * size) + column);

                Node new_node = {id, elem, row, column};

                DFS(new_node, visited, grid, size, word,
                    index + 1, solution, 8, solution_found);

                if (solution.size() == word.size()) {
                    solution_found = true;
                } else {
                    index = 0;
                    solution.clear();
                }
            }
        }
    }
}

void solve(char* grid, int size, string word, char* solution_grid) {
    vector<Node> solution;
    bool solution_found = false;

    for (int i = 0; i < size && !solution_found; i++) {
        for (int j = 0; j < size && !solution_found; j++) {
            int id = i * 100 + j;
            Node root {id, *((grid + i * size) + j), i, j};
            map<int, bool> visited;

            solution.clear();

            DFS(root, visited, grid, size, word, 0,
                solution, -1, solution_found);
        }
    }

    //cerr << "Solution: " << endl;
    for (auto s : solution) {
    //    cerr << s.elem << " " << s.row << " " << s.column << endl;
    }

    for (Node n : solution) {
        solution_grid[n.row * size + n.column] = n.elem;
    }
}

int main() {
    int size;
    cin >> size;
    cin.ignore();

    char grid[size][size];

    for (int i = 0; i < size; i++) {
        string row;
        cin >> row;
        cin.ignore();

        for (int j = 0; j < size; j++) {
            grid[i][j] = toupper(row[j]);
        }
    }

    //print_grid((char*)grid, size);

    string clues;
    getline(cin, clues);
    transform(clues.begin(), clues.end(), clues.begin(), ::toupper);

    char solution_grid[size][size];

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            solution_grid[i][j] = ' ';
        }
    }

    string word = "";
    for (char c : clues) {
        if (c != ' ') {
            word += c;
        } else {
            //cerr << "SOLVING: " << word << endl;
            solve((char*)grid, size, word, (char*)solution_grid);
            word = "";
        }
    }
    //cerr << "SOLVING: " << word << endl;
    solve((char*)grid, size, word, (char*)solution_grid);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << solution_grid[i][j];
        }
        cout << endl;
    }
}
#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;

struct Node {
    int id; // id = (row * 100) + column
    char elem;
    int row;
    int column;
};

void print_grid(char* grid, int n) {
    cerr << "THE GRID" << endl << endl;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cerr << *((grid + i * n) + j);
        }
        cerr << endl;
    }
}

void print_solution(vector<Node> solution, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            char elem = '-';
            for (Node node : solution) {
                if (node.row == i && node.column == j) {
                    elem = node.elem;
                    break;
                }
            }
            cout << elem;
        }
        cout << endl;
    }
}

void DFS(
    Node node, map<int, bool> visited, char* grid, int n, char next,
    vector<Node> &solution) {

    if (node.elem == next) {
        solution.push_back(node);
        visited[node.id] = true;

        if (node.column < n - 1) {
            // right
            int row = node.row;
            int column = node.column + 1;

            int id = row * 100 + column;

            if (!visited[id]) {
                char elem = *((grid + row * n) + column);

                Node new_node = {id, elem, row, column};
                DFS(new_node, visited, grid, n, next + 1, solution);
            }
        }

        if (node.row < n - 1) {
            // down
            int row = node.row + 1;
            int column = node.column;

            int id = row * 100 + column;

            if (!visited[id]) {
                char elem = *((grid + row * n) + column);

                Node new_node = {id, elem, row, column};
                DFS(new_node, visited, grid, n, next + 1, solution);
            }
        }

        if (node.column > 0) {
            // left
            int row = node.row;
            int column = node.column - 1;

            int id = row * 100 + column;

            if (!visited[id]) {
                char elem = *((grid + row * n) + column);

                Node new_node = {id, elem, row, column};
                DFS(new_node, visited, grid, n, next + 1, solution);
            }
        }

        if (node.row > 0) {
            // up
            int row = node.row - 1;
            int column = node.column;

            int id = row * 100 + column;

            if (!visited[id]) {
                char elem = *((grid + row * n) + column);

                Node new_node = {id, elem, row, column};
                DFS(new_node, visited, grid, n, next + 1, solution);
            }
        }
    }
}

int main() {
    int n;
    cin >> n;
    cin.ignore();

    char grid[n][n];

    for (int i = 0; i < n; i++) {
        string m;
        cin >> m;
        cin.ignore();

        for (int j = 0; j < n; j++) {
            grid[i][j] = m[j];
        }
    }

    vector<Node> solution;

    for (int i = 0; i < n && solution.size() != 26; i++) {
        for (int j = 0; j < n && solution.size() != 26; j++) {
            int id = i * 100 + j;
            Node root {id, grid[i][j], i, j};
            map<int, bool> visited;
            solution.clear();

            DFS(root, visited, (char*)grid, n, 'a', solution);
        }
    }
    
    print_solution(solution, n);
}
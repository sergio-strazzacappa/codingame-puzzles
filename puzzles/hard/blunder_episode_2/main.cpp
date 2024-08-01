#include <iostream>
#include <vector>

using namespace std;

struct Room {
    int id;
    int money;
    int room_1;
    int room_2;
    int max_distance;

    void print() {
        cerr << "Id: " << id;
        cerr << " | Money: " << money;
        cerr << " | Exit: [ " << room_1;
        cerr << ", " << room_2;
        cerr << " ] | Max distance: " << max_distance;
        cerr << endl;
    }
};

vector<Room> maze;

void print_maze() {
    cerr << "Maze: " << endl;
    for (Room r : maze) {
        r.print();
    }
}

Room* search(int id) {
    for (int i = 0; i < maze.size(); i++) {
        if (maze[i].id == id) {
            return &maze[i];
        }
    }
    return NULL;
}

void dijkstra() {
    int max = 0;

    while (!maze.empty()) {
        Room* current_node = &maze[0];

        if (current_node->max_distance > max) {
            max = current_node->max_distance;
        }

        Room* next_room = NULL;

        for (int i = 0; i < 2; i++) {  
            next_room = search(current_node->room_1);

            if (next_room != NULL) {
                int distance = 
                    current_node->max_distance + next_room->money;

                if (distance > next_room->max_distance) {
                    next_room->max_distance = distance;
                }
            }

            next_room = search(current_node->room_2);

            if (next_room != NULL) {
                int distance =
                    current_node->max_distance + next_room->money;

                if (distance > next_room->max_distance) {
                    next_room->max_distance = distance;
                }
            }
        }
        maze.erase(maze.begin());
    }
    cout << max << endl;
}

int main() {
    int n;
    cin >> n;
    cin.ignore();

    for (int i = 0; i < n; i++) {
        int id, money, r_1 = -1, r_2 = -1;
        string room_1, room_2;

        cin >> id >> money >> room_1 >> room_2;
        cin.ignore();

        if (room_1[0] != 'E') {
            r_1 = stoi(room_1);
        }
        if (room_2[0] != 'E') {
            r_2 = stoi(room_2);
        }

        struct Room r {id, money, r_1, r_2};
        maze.push_back(r);

        if (id == 0) {
            maze[i].max_distance = money;
        }
    }
    dijkstra();
}
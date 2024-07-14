#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#define TARGET "Kevin Bacon"

using namespace std;

struct Movie {
    string name;
    vector<string> actors;
};

struct Node {
    string actor;
    int bacon_number;
};

vector<Movie> movies;

void split(string s) {
    string field = "";
    Movie m;
    m.name = "";

    for (char c : s) {
        if (c == ':' || c == ',') {
            if (m.name == "") {
                m.name = field;
            } else {
                field.erase(0, 1);
                m.actors.push_back(field);
            }
            field = "";
            continue;
        }
        field += c;
    }
    field.erase(0, 1);
    m.actors.push_back(field);
    movies.push_back(m);
}

int BFS(Node root) {
    vector<string> explored;
    queue<Node> frontier;

    explored.push_back(root.actor);
    frontier.push(root);

    while (!frontier.empty()) {
        Node actual_actor = frontier.front(); 
        frontier.pop();

        if (actual_actor.actor == TARGET) {
            return actual_actor.bacon_number;
        }

        for (Movie m : movies) {
            if (find(m.actors.begin(), m.actors.end(), actual_actor.actor) != 
                m.actors.end()) {
                for (string a : m.actors) {
                    if (actual_actor.actor != a) {
                        Node n = {
                            a,
                            actual_actor.bacon_number
                        };
                        if (find(explored.begin(), explored.end(), a) ==
                            explored.end()) {
                            n.bacon_number++;
                            explored.push_back(a);
                            frontier.push(n);
                        }
                    }
                }
            }
        }
    }
    return 0;
}

int main() {
    string actor_name;
    getline(cin, actor_name);
    int n;
    cin >> n;
    cin.ignore();

    for (int i = 0; i < n; i++) {
        string movie_cast;
        getline(cin, movie_cast);
        split(movie_cast);
    }

    Node root {
        actor_name,
        0
    };

    cout << BFS(root) << endl;
}
#include <bits/stdc++.h>

using namespace std;

#define ll long long

class Point {
    int x;
    int y;

    public:
        Point() {
            this->x = 0;
            this->y = 0;
        }

        Point(int x, int y) {
            this->x = x;
            this->y = y;
        }

        int getX() {
            return this->x;
        }

        int getY() {
            return this->y;
        }

        void setX(int x) {
            this->x = x;
        }

        void setY(int y) {
            this->y = y;
        }

        string toString() {
            return "(" + to_string(this->x) + ", " + to_string(this->y) + ")";
        }
};

class Snail {
    int id;
    int speed;
    Point point;

    public:
        Snail() {
            this->id = 0;
            this->speed = 0;
            this->point = Point();
        }

        Snail(int id, int speed, Point point) {
            this->id = id;
            this->speed = speed;
            this->point = point;
        }

        int getId() {
            return this->id;
        }

        int getSpeed() {
            return this->speed;
        }

        Point getPoint() {
            return this->point;
        }

        void setId(int id) {
            this->id = id;
        }

        void setSpeed(int speed) {
            this->speed = speed;
        }

        void setPoint(Point point) {
            this->point = point;
        }

        string toString() {
            string output = "";

            output += "ID: " + to_string(this->id);
            output += " Speed: " + to_string(this->speed);
            output += " Position: " + this->point.toString();

            return output;
        }
};

void solve(Snail snails[], int numberSnails, vector<Point> goals) {
    int bestId = 0;
    double minTurns = INT32_MAX;

    for (int i = 0; i < numberSnails; i++) {
        int closest = INT32_MAX;
        double turns = 0;

        for (auto j = goals.begin(); j != goals.end(); j++) {
            int distance = 
                abs(snails[i].getPoint().getX() - j.base()->getX()) + 
                abs(snails[i].getPoint().getY() - j.base()->getY());
            if (distance < closest) {
                closest = distance;
            }
        }
        turns = (float)closest / snails[i].getSpeed();

        if (turns < minTurns) {
            minTurns = turns;
            bestId = snails[i].getId();
        }
    }
    cout << bestId << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int numberSnails;
    vector<Point> goals;

    cin >> numberSnails;
    cin.ignore();

    Snail snails[numberSnails];

    for (int i = 0; i < numberSnails; i++) {
        int speed;
        cin >> speed;
        cin.ignore();

        snails[i].setId(i + 1);
        snails[i].setSpeed(speed);
    }

    // map size
    int mapHeight;
    int mapWidth;

    cin >> mapHeight; 
    cin.ignore();

    cin >> mapWidth;
    cin.ignore();

    for (int y = 0; y < mapHeight; y++) {
        string row;

        getline(cin, row);

        for (int x = 0; x < row.size(); x++) {
            if (row[x] == '#') {
                goals.push_back(Point(x, y));
            } else if (row[x] != '*') {
                int id = row[x] - '0';
                bool exito = false;
                for (int i = 0; i < numberSnails && !exito; i++) {
                    if (id == snails[i].getId()) {
                        snails[i].setPoint(Point(x, y));
                        exito = true;
                    }
                }
            }
        }
    }
    solve(snails, numberSnails, goals);
}
#include <bits/stdc++.h>
using namespace std;

struct Point {
    int row, col;
    bool operator==(const Point& p) const { return row == p.row && col == p.col; }
    bool operator<(const Point& p) const { return tie(row, col) < tie(p.row, p.col); }
};

bool in_map(const Point& p, const vector<string>& map) {
    return p.row >= 0 && p.row < map.size() && p.col >= 0 && p.col < map[0].size();
}

bool move_obstacles(const Point& start, const Point& dir, vector<string>& map) {
    Point current = start;
    while (map[current.row][current.col] == 'O') {
        current.row += dir.row;
        current.col += dir.col;
    }
    if (map[current.row][current.col] == '.') {
        swap(map[start.row][start.col], map[current.row][current.col]);
        return true;
    }
    return false;
}

int main() {
    ifstream file("../input.txt");
    vector<string> map;
    Point start;
    string line, moves;


    while (getline(file, line) && !line.empty()) {
        map.push_back(line);
        int pos = line.find('@');
        if (pos != string::npos) {
            start = {int(map.size()) - 1, int(pos)};
        }
    }

    // Načítanie pohybov
    while (getline(file, line)) {
        moves += line;
    }

    Point current = start;
    array<Point, 4> directions = {{{-1, 0}, {0, 1}, {1, 0}, {0, -1}}}; // ^, >, v, <
    unordered_map<char, int> move_map = {{'^', 0}, {'>', 1}, {'v', 2}, {'<', 3}};


    for (char move : moves) {
        int dir_idx = move_map[move];
        Point new_point = {current.row + directions[dir_idx].row, current.col + directions[dir_idx].col};

        if (!in_map(new_point, map) || map[new_point.row][new_point.col] == '#') {
            continue;
        }

        if (map[new_point.row][new_point.col] == 'O' &&
            move_obstacles(new_point, directions[dir_idx], map)) {
            swap(map[current.row][current.col], map[new_point.row][new_point.col]);
            current = new_point;
        } else if (map[new_point.row][new_point.col] == '.') {
            swap(map[current.row][current.col], map[new_point.row][new_point.col]);
            current = new_point;
        }
    }

    int total = 0;
    for (int row = 0; row < map.size(); ++row) {
        for (int col = 0; col < map[row].size(); ++col) {
            if (map[row][col] == 'O') {
                total += 100 * row + col;
            }
        }
    }

    cout << total << '\n';
    return 0;
}

#include <bits/stdc++.h>
using namespace std;

struct Point {
    int row, col;
};

bool in_map(const Point& p, const vector<string>& map) {
    return p.row >= 0 && p.row < map.size() && p.col >= 0 && p.col < map[0].size();
}

bool attempt_move_obstacles(const Point& current, const Point& possible_move, vector<string>& map) {
    char cell = map[current.row][current.col];
    if (cell == '.' || cell == '#') return cell == '.';

    if (cell == '[' || cell == ']') {
        bool move_possible = attempt_move_obstacles(Point(current.row + possible_move.row, current.col + possible_move.col), possible_move, map);
        if (possible_move.row != 0) {
            move_possible &= attempt_move_obstacles(Point(current.row + possible_move.row, current.col + (cell == '[' ? 1 : -1)), possible_move, map);
        }
        return move_possible;
    }
    return false;
}

void move_obstacles(const Point& current, const Point& possible_move, vector<string>& map) {
    char cell = map[current.row][current.col];
    if (cell == '.') return;

    move_obstacles(Point(current.row + possible_move.row, current.col + possible_move.col), possible_move, map);
    swap(map[current.row][current.col], map[current.row + possible_move.row][current.col + possible_move.col]);

    if (possible_move.row != 0 && map[current.row][current.col + (cell == '[' ? 1 : -1)] == (cell == '[' ? ']' : '[')) {
        move_obstacles(Point(current.row, current.col + (cell == '[' ? 1 : -1)), possible_move, map);
    }
}

int main() {
    ifstream file("../input.txt");
    string line;
    vector<string> map;
    Point start;
    while (getline(file, line) && !line.empty()) {
        string updated_line;
        for (char ele : line) {
            if (ele == '#') updated_line += "##";
            else if (ele == '.') updated_line += "..";
            else if (ele == '@') updated_line += "@.";
            else if (ele == 'O') updated_line += "[]";
        }
        map.push_back(updated_line);
        for (int idx = 0; idx < updated_line.size(); ++idx) {
            if (updated_line[idx] == '@') {
                start.row = map.size() - 1;
                start.col = idx;
            }
        }
    }

    string moves;
    while (getline(file, line)) {
        moves += line;
    }

    array<Point, 4> directions{{Point(-1, 0), Point(0, 1), Point(1, 0), Point(0, -1)}};
    Point current = start;
    for (char move : moves) {
        int move_idx = (move == '^') ? 0 : (move == '>') ? 1 : (move == 'v') ? 2 : 3;
        Point new_point{current.row + directions[move_idx].row, current.col + directions[move_idx].col};

        if (!in_map(new_point, map) || map[new_point.row][new_point.col] == '#') continue;

        if (map[new_point.row][new_point.col] == '.' || map[new_point.row][new_point.col] == '@') {
            swap(map[new_point.row][new_point.col], map[current.row][current.col]);
            current = new_point;
        }

        if (map[new_point.row][new_point.col] == '[' || map[new_point.row][new_point.col] == ']') {
            if (attempt_move_obstacles(new_point, directions[move_idx], map)) {
                move_obstacles(new_point, directions[move_idx], map);
                swap(map[current.row][current.col], map[new_point.row][new_point.col]);
                current = new_point;
            }
        }
    }

    int total = 0;
    for (int row_idx = 0; row_idx < map.size(); ++row_idx) {
        for (int col_idx = 0; col_idx < map[row_idx].size(); ++col_idx) {
            if (map[row_idx][col_idx] == '[') {
                total += (100 * row_idx + col_idx);
            }
        }
    }

    cout << total << '\n';
    return 0;
}

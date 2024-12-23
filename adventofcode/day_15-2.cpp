#include <bits/stdc++.h>
using namespace std;
struct Point {
    int row;
    int col;
    bool operator == (const Point& p) const {
        return row == p.row && col == p.col;
    }

    bool operator < (const Point& p) const {
        return row < p.row || (row == p.row &&  col < p.col);
    }
};

struct Hasher {
    size_t operator () (const Point& p) const {
        return p.row;
    }
};

bool in_map(const Point& p, const vector<string>& map ) {
    return p.row >= 0 && p.row < map.size() && p.col >= 0 && p.col < map[0].size();
}

bool attempt_move_obstacles(const Point& current, const Point& possible_move, vector<string>& map) {
    if(map[current.row][current.col] == '.') return true;
    if(map[current.row][current.col] == '#') return false;
    if(map[current.row][current.col] == '[') {
        const bool possible_1 = attempt_move_obstacles(Point(current.row + possible_move.row, current.col + possible_move.col), possible_move, map);
        bool possible_2 = true;
        if (possible_move.row != 0) possible_2 = attempt_move_obstacles(Point(current.row + possible_move.row, current.col + 1), possible_move, map);
        return possible_1 && possible_2;
    }
    if(map[current.row][current.col] == ']') {
        const bool possible_1 = attempt_move_obstacles(Point(current.row + possible_move.row, current.col + possible_move.col), possible_move, map);
        bool possible_2 = true;
        if (possible_move.row != 0) possible_2 = attempt_move_obstacles(Point(current.row + possible_move.row, current.col - 1), possible_move, map);
        return possible_1 && possible_2;
    }
    return false;
}

void move_obstacles(const Point& current, const Point& possible_move, vector<string>& map) {
    if(map[current.row][current.col] == '.') return;
    if (map[current.row][current.col] == '[') {
        move_obstacles(Point(current.row + possible_move.row, current.col + possible_move.col), possible_move, map);
        swap(map[current.row][current.col], map[current.row+possible_move.row][current.col+possible_move.col]);
        if (possible_move.row != 0 && map[current.row][current.col+1] == ']') move_obstacles(Point(current.row, current.col + 1), possible_move, map);
    }
    else if (map[current.row][current.col] == ']') {
        move_obstacles(Point(current.row + possible_move.row, current.col + possible_move.col), possible_move, map);
        swap(map[current.row][current.col], map[current.row+possible_move.row][current.col+possible_move.col]);
        if (possible_move.row != 0 && map[current.row][current.col-1] == '[') move_obstacles(Point(current.row, current.col - 1), possible_move, map);
    }
}

int main() {
    string input = "../input.txt";

    ifstream file(input);
    string line;
    vector<string> mapa;
    Point start;
    while(getline(file, line) && !line.empty()) {
        string updated_line = "";
        for (const auto ele : line) {
            if (ele == '#') updated_line += "##";
            else if (ele == '.') updated_line += "..";
            else if (ele == '@') updated_line += "@.";
            else if (ele == 'O') updated_line += "[]";
        }
        mapa.push_back(updated_line);
        for (const auto [idx,ele] : std::views::enumerate(updated_line)) {
            if (ele == '@') {
                start.row = mapa.size()-1;
                start.col = idx;
            }
        }
    }
    string moves;
    while(getline(file, line)) {
        moves += line;
    }

    Point current = start;
    array<Point, 4> possible_moves {{
        Point(-1,0),
        Point(0,1),
        Point(1,0),
        Point(0,-1)
    }};
    for (const auto move : moves) {

        int move_idx = 0;
        if (move == '^') {
            move_idx = 0;
        } else if (move == '>') {
            move_idx = 1;
        } else if (move == 'v') {
            move_idx = 2;
        } else if (move == '<') {
            move_idx = 3;
        }
        Point new_point;
        new_point.row = current.row + possible_moves[move_idx].row;
        new_point.col = current.col + possible_moves[move_idx].col;
        if (!in_map(new_point, mapa)) {
            continue;
        }
        if (mapa[new_point.row][new_point.col] == '#') {
            continue;
        }
        if (mapa[new_point.row][new_point.col] == '.') {
            swap(mapa[new_point.row][new_point.col], mapa[current.row][current.col]);
            current = new_point;
        }
        if (mapa[new_point.row][new_point.col] == '[' || mapa[new_point.row][new_point.col] == ']') {
            if (attempt_move_obstacles(new_point, possible_moves[move_idx], mapa)) {
                move_obstacles(new_point, possible_moves[move_idx], mapa);
                swap(mapa[current.row][current.col], mapa[new_point.row][new_point.col]);
                current = new_point;
            }
        }
    }
    int total = 0;
    for (const auto& [row_idx, row] : views::enumerate(mapa)) {
        for (const auto& [col_idx, ele] : views::enumerate(row)) {
            if (ele == '[') {
                total += (100 * row_idx + col_idx);
            }
        }
    }
    cout << total << '\n';
    return 0;
}
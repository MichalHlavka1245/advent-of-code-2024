#include <bits/stdc++.h>
using namespace std;
struct Point {
    int row;
    int col;
    bool operator == (const Point& p) const {
        return row == p.row && col == p.col;
    }
};


constexpr array motions {  //pohyby
    Point( 0,-1),
    Point(-1, 0),
    Point( 0, 1),
    Point( 1, 0)
};

int check_corner(const Point& p, const vector<string>& mapa) {
    int nc = 0;
    const auto c = mapa[p.row][p.col];


    // Outside corners
    if (mapa[p.row+1][p.col] != c && mapa[p.row][p.col+1] != c) nc++; // p in the top left position
    if (mapa[p.row+1][p.col] != c && mapa[p.row][p.col-1] != c) nc++; // p in the top right position
    if (mapa[p.row-1][p.col] != c && mapa[p.row][p.col+1] != c) nc++; // p in the bottom left position
    if (mapa[p.row-1][p.col] != c && mapa[p.row][p.col-1] != c) nc++; // p is the bottom right position

    // Inside corners
    if (mapa[p.row+1][p.col] == c && mapa[p.row][p.col+1] == c && mapa[p.row+1][p.col+1] != c) nc++; // p in the top left position
    if (mapa[p.row+1][p.col] == c && mapa[p.row][p.col-1] == c && mapa[p.row+1][p.col-1] != c) nc++; // p in the top right position
    if (mapa[p.row-1][p.col] == c && mapa[p.row][p.col+1] == c && mapa[p.row-1][p.col+1] != c) nc++; // p in the bottom left position
    if (mapa[p.row-1][p.col] == c && mapa[p.row][p.col-1] == c && mapa[p.row-1][p.col-1] != c) nc++; // p is the bottom right position

    return nc;
}

long long calculate_cost(
    const int row_idx,
    const int col_idx,
    const vector<string>& map,
    vector<vector<bool>>& visited) {
    const auto c = map[row_idx][col_idx];  // c označuje rastliny
    const auto start = Point(row_idx, col_idx);
    long long cost = 0;
    queue<Point> q;
    q.push(start);
    long long area = 0;
    long long perimeter= 0;
    while(!q.empty()) {
        auto p = q.front();
        q.pop();
        if (visited[p.row][p.col]) continue;
        visited[p.row][p.col] = true;
        area++;
        perimeter += check_corner(p, map);
        for (const auto& motion : motions) {
            const auto next = Point(p.row + motion.row, p.col + motion.col);
            if (map[next.row][next.col] != c) {
                continue;
            }
            if (map[next.row][next.col] == c && !visited[next.row][next.col]) {
                q.push(next);
            }
        }
    }

    return area * perimeter;
}

int main() {
    string input = "../input.txt";


    ifstream file(input);
    string line;
    vector<string> mapa;
    mapa.emplace_back();

    // Add a buffer
    while(getline(file, line)) {
        line = '#' + line + '#';
        mapa.push_back(line);
    }
    mapa[0] = string(mapa[1].size(), '#');
    mapa.emplace_back(mapa[0]);

    vector<std::vector<bool>> visited (mapa.size(), vector<bool>(mapa[0].size(), false));
    long long total_cost = 0;
    for (const auto& [row_idx, row] : views::enumerate(mapa)) {
        for (const auto& [col_idx, ele] : views::enumerate(row)) {
            if (visited[row_idx][col_idx]) continue;
            const auto c = mapa[row_idx][col_idx];
            if (c == '#') continue;
            total_cost += calculate_cost(row_idx, col_idx, mapa, visited);
        }
    }
    cout << total_cost << '\n';
    return 0;
}
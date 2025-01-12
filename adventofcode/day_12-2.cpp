#include <bits/stdc++.h>
using namespace std;

int check_corner(int row, int col, const vector<string>& mapa) {
    int pocet_rohov = 0;    char c = mapa[row][col];


    vector<pair<int, int>> corners{{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    for (const auto& [dr, dc] : corners) {
        bool is_outer = mapa[row + dr][col] != c && mapa[row][col + dc] != c;
        bool is_inner = mapa[row + dr][col] == c && mapa[row][col + dc] == c && mapa[row + dr][col + dc] != c;
        if (is_outer || is_inner) ++pocet_rohov;
    }

    return pocet_rohov;
}

long long calculate_cost(int row_idx, int col_idx, const vector<string>& map, vector<vector<bool>>& visited) {
    char c = map[row_idx][col_idx];
    queue<pair<int, int>> q;
    q.push({row_idx, col_idx});

    long long area = 0, obvod = 0;
    vector<pair<int, int>> dirs{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();

        if (visited[r][c]) continue;
        visited[r][c] = true;

        ++area;
        obvod += check_corner(r, c, map);

        for (const auto& [dr, dc] : dirs) {
            int nr = r + dr, pocet_rohov = c + dc;
            if (map[nr][pocet_rohov] == map[r][c] && !visited[nr][pocet_rohov]) {
                q.push({nr, pocet_rohov});
            }
        }
    }

    return area * obvod;
}

int main() {
    ifstream file("../input.txt");
    vector<string> mapa;

    string line;
    while (getline(file, line)) {
        mapa.emplace_back('#' + line + '#');
    }

    int width = mapa[0].size();
    mapa.insert(mapa.begin(), string(width, '#'));
    mapa.emplace_back(string(width, '#'));

    vector<vector<bool>> visited(mapa.size(), vector<bool>(width, false));
    long long total_cost = 0;

    for (size_t row_idx = 0; row_idx < mapa.size(); ++row_idx) {
        for (size_t col_idx = 0; col_idx < mapa[row_idx].size(); ++col_idx) {
            if (mapa[row_idx][col_idx] != '#') {
                total_cost += calculate_cost(row_idx, col_idx, mapa, visited);
            }
        }
    }

    cout << total_cost << '\n';
    return 0;
}

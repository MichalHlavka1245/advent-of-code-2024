#include <bits/stdc++.h>
using namespace std;

using Point = pair<int, int>;
vector<pair<int, int>> dirs{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

long long calculate_cost(int row_idx, int col_idx, const vector<string>& mapa, vector<vector<bool>>& visited) {
    const char c = mapa[row_idx][col_idx];  // Rastliny
    if (c == '#') return 0;
    const Point start(row_idx, col_idx);
    long long cost = 0;
    queue<Point> q;
    q.push(start);
    long long area = 0; //počet rastlin v jednej oblasti
    long long obvod = 0;

    while (!q.empty()) {
        auto p = q.front();
        q.pop();
        if (visited[p.first][p.second]) continue;
        visited[p.first][p.second] = true;
        area++;

        for (const auto& dir : dirs) {
            const Point next(p.first + dir.first, p.second + dir.second);
            if (mapa[next.first][next.second] != c) {
                obvod++;
                continue;
            }
            if (!visited[next.first][next.second]) {
                q.push(next);
            }
        }
    }

    return area * obvod;
}

int main() {
    ifstream file("../input.txt");
    string line;
    vector<string> mapa;

    while (getline(file, line)) {
        line = "#" + line + "#";
        mapa.push_back(line);
    }

    
    string border(mapa[0].size(), '#');
    mapa.insert(mapa.begin(), border);
    mapa.push_back(border);

    vector<vector<bool>> visited(mapa.size(), vector<bool>(mapa[0].size(), false));
    long long total_cost = 0;

    for (int row_idx = 0; row_idx < mapa.size(); ++row_idx) {
        for (int col_idx = 0; col_idx < mapa[row_idx].size(); ++col_idx) {
            if (visited[row_idx][col_idx]) continue;
            const auto c = mapa[row_idx][col_idx];
            if (c != '#') total_cost += calculate_cost(row_idx, col_idx, mapa, visited);
        }
    }

    cout << total_cost << '\n';
    return 0;
}



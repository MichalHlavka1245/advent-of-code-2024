#include <bits/stdc++.h>
using namespace std;

int main() {
    char a[50][50];
    int height = 50;
    int width = 50;
    vector<pair<int, int>> where[256];


    string line;
    int row = 0;
    while (getline(cin, line)) {

        if (line.empty()) {
            break;
        }
        strcpy(a[row], line.c_str());

        for (int col = 0; col < width; col++) {
            height = row + 1;
            if (a[row][col] != '.') {
                where[(int)a[row][col]].emplace_back(row, col);
            }
        }
        row++;
    }

    vector<vector<bool>> yes(height, vector<bool>(width));
    int answer = 0;

    for (int z = 0; z < 256; z++) {
        const vector<pair<int, int>>& v = where[z];
        for (int i = 0; i < (int)v.size(); i++) {
            for (int j = 0; j < (int)v.size(); j++) {
                if (i == j) {
                    continue;
                }
                int r = v[i].first;
                int c = v[i].second;
                int r2 = v[j].first;
                int c2 = v[j].second;
                int row = r2 + (r2 - r);
                int col = c2 + (c2 - c);

                if (0 <= row && row < height && 0 <= col && col < width) {
                    if (!yes[row][col]) {
                        yes[row][col] = true;
                        answer++;
                    }
                }
            }
        }
    }

    cout << answer<<endl;
    return 0;
}
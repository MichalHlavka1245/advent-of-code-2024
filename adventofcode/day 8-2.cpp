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
    vector<vector<bool>> yes(height, vector<bool>(width, false));
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
                int dx = r2 - r;
                int dy = c2 - c;
                int g = __gcd(dx, dy);
                dx /= g;
                dy /= g;

                for (int rep = 0; rep < 2; rep++) {
                    for (int m = 0; true; m++) {
                        int row = r + dx * m;
                        int col = c + dy * m;

                        if (0 <= row && row < height && 0 <= col && col < width) {
                            if (!yes[row][col]) {
                                yes[row][col] = true;
                                answer++;
                            }
                        } else {
                            break;
                        }
                    }
                    dx = -dx;
                    dy = -dy;
                }
            }
        }
    }
    cout << answer << endl;
    return 0;
}
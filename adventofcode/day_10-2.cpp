#include <bits/stdc++.h>
using namespace std;

char a[52][52];//grid
vector<pair<int, int>> dirs{{-1,0},{1,0},{0,-1},{0,1}};
int targets = 0;
int height, width;
bool vis[52][52];

bool inside(int row, int col) {
    return 0 <= row && row < height && 0 <= col && col < width;
}

void dfs(int row, int col) {
    vis[row][col] = true;
    if (a[row][col] == '9') {
        targets++;
    }

    for (pair<int,int> dir : dirs) {
        int r2 = row + dir.first;
        int c2 = col + dir.second;
        if (inside(r2, c2) && a[r2][c2] == a[row][col] + 1 ) {
            dfs(r2, c2);
        }
    }
}

int main() {
    string line;
    height = 0;


    while (getline(cin, line)) {
        if (line.empty()) {
            break;
        }
        strcpy(a[height], line.c_str());
        width = line.length();
        height++;
    }
    memset(vis, 0, sizeof(vis));
    targets = 0;

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            if (a[row][col] == '0') {
                dfs(row, col);
                for (int i = 0; i < height; i++) {
                    for (int j = 0; j < width; j++) {
                        vis[i][j] = false;
                    }
                }
            }
        }
    }

    cout << targets << endl;
    return 0;
}
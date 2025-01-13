#include <bits/stdc++.h>
using namespace std;

tuple<bool, int, int> check_linear_combination(const int ax, const int ay, const int bx, const int by, const int cx, const int cy) {
    if ((ax * by) == (bx * ay)) exit(0);;
    const int A = (cx * by - cy * bx) / (ax * by - ay * bx);
    const int B = (cx * ay - cy * ax) / (bx * ay - by * ax);

    if (A * ax + B * bx != cx) return {false, -1, -1};
    if (A * ay + B * by != cy) return {false, -1, -1};
    if (A < 0 || B < 0 || A > 100 || B > 100) return {false, -1, -1};
    return {true, A, B};
}

int main() {
    string input = "../input.txt";
    ifstream file(input);
    string line;
    long long answer = 0;

    const regex vzor(R"([A-Za-z ]+: X[+=]([0-9]+), Y[+=]([0-9]+))");
    smatch match;
    int total_cost = 0;
    while(true) {
        getline(file, line);
        regex_search(line, match, vzor);
        const int ax = stoi(match[1]);
        const int ay = stoi(match[2]);
        getline(file, line);
        regex_search(line, match, vzor);
        const int bx = stoi(match[1]);
        const int by = stoi(match[2]);
        getline(file, line);
        regex_search(line, match, vzor);
        const int px = stoi(match[1]);
        const int py = stoi(match[2]);
        const auto [possible, A, B] = check_linear_combination(ax, ay, bx, by, px, py);

        if (possible) total_cost += (A * 3 + B);
        if(!getline(file, line)) break;
    }
    cout << total_cost << '\n';
    return 0;
}

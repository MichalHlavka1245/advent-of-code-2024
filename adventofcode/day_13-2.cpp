#include <bits/stdc++.h>
using namespace std;

tuple<bool, long long, long long> check_linear_combination(const long long ax, const long long ay, const long long bx, const long long by, const long long cx, const long long cy) {
    if ((ax * by) == (bx * ay)) exit(0);
    const long long A = (cx * by - cy * bx) / (ax * by - ay * bx);
    const long long B = (cx * ay - cy * ax) / (bx * ay - by * ax);

    if (A * ax + B * bx != cx) return {false, -1, -1};
    if (A * ay + B * by != cy) return {false, -1, -1};
    if (A < 0 || B < 0) return {false, -1, -1};
    return {true, A, B};
}

int main() {
    string input = "../input.txt";

    ifstream file(input);
    string line;
    long long answer = 0;

    const regex vzor(R"([A-Za-z ]+: X[+=]([0-9]+), Y[+=]([0-9]+))");
    smatch match;
    long long total_cost = 0;
    while(true) {
        getline(file, line);
        regex_search(line, match, vzor);
        const long long ax = stoi(match[1]);
        const long long ay = stoi(match[2]);
        getline(file, line);
        regex_search(line, match, vzor);
        const long long bx = stoi(match[1]);
        const long long by = stoi(match[2]);
        getline(file, line);
        regex_search(line, match, vzor);
        const long long px = stoi(match[1]) + 10000000000000;
        const long long py = stoi(match[2]) + 10000000000000;
        const auto [possible, A, B] = check_linear_combination(ax, ay, bx, by, px, py);
        
        if (possible) total_cost += (A * 3 + B);
        if(!getline(file, line)) break;
    }
    cout << total_cost << '\n';
    return 0;
}

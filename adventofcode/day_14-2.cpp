#include <bits/stdc++.h>
using namespace std;
struct Robot {
    int p_col;
    int p_row;
    int v_col;
    int v_row;
};

int main() {
    string input = "../input.txt";
    ifstream file(input);
    string line;
    const int time = 100;
    const int room_col = 101;
    const int room_row = 103;

    const regex vzor(R"(p=(-?[0-9]+),(-?[0-9]+) v=(-?[0-9]+),(-?[0-9]+))");
    smatch zhoda;
    int total_cost = 0;
    array<int, 4> count = {{0,0,0,0}};


    vector<Robot> robots;
    while(getline(file, line)) {
        robots.emplace_back();
        regex_search(line, zhoda, vzor);
        robots.back().p_col = stoi(zhoda[1]) % room_col;
        robots.back().p_row = stoi(zhoda[2]) % room_row;
        robots.back().v_col = stoi(zhoda[3]) % room_col;
        robots.back().v_row = stoi(zhoda[4]) % room_row;
    }
    long long sekundy = 1;
    int safety_factor = numeric_limits<int>::max();
    while(true) {
        array<array<int, room_col>, room_row> room;
        for (auto& row : room) {
            for (auto& ele : row) {
                ele = 0;
            }
        }
        array<int, 4> count = {{0,0,0,0}};
        for (auto& robot : robots) {
            robot.p_col += robot.v_col + room_col;
            robot.p_col %= room_col;
            robot.p_row += robot.v_row + room_row;
            robot.p_row %= room_row;
            room[robot.p_row][robot.p_col] = '#';
            if (robot.p_row < room_row / 2 && robot.p_col < room_col / 2) count[0]++;
            else if (robot.p_row < room_row / 2 && robot.p_col > room_col / 2) count[1]++;
            else if (robot.p_row > room_row / 2 && robot.p_col < room_col / 2) count[2]++;
            else if (robot.p_row > room_row / 2 && robot.p_col > room_col / 2) count[3]++;
        }
        int new_safety_factor = 1;
        for (const auto ele : count) {
            new_safety_factor *= ele;
        }
        if (new_safety_factor < safety_factor) {
            safety_factor = new_safety_factor;
            for (const auto row : room) {
                for (const auto ele : row) {
                    cout << char(ele == 0 ? '.' : ele + '0');
                }
                cout << '\n';
            }
            cout << sekundy<< '\n';
        }
        sekundy++;
    }
    return 0;
}

#include <bits/stdc++.h>
using namespace std;
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
    array<int, 4> count = {{0,0,0,0}};  // pocet robotov v kvadrnatoch
    array<array<int, room_col>, room_row> room;
    for (auto& row : room) {
        for (auto& prvok : row) {
            prvok = 0;
        }
    }
    while(getline(file, line)) {
        regex_search(line, zhoda, vzor);
        const int p_col = stoi(zhoda[1]);
        const int p_row = stoi(zhoda[2]);
        const int v_col = stoi(zhoda[3]);
        const int v_row = stoi(zhoda[4]);
        int final_col = (p_col + v_col * time);
        while(final_col < 0) {
            final_col += (room_col * time);
        }
        final_col %= room_col;
        int final_row = p_row + v_row * time;
        while(final_row < 0) {
            final_row += (room_row * time);
        }
        final_row %= room_row;
        if (final_row < room_row / 2 && final_col < room_col / 2) count[0]++;
        else if (final_row < room_row / 2 && final_col > room_col / 2) count[1]++;
        else if (final_row > room_row / 2 && final_col < room_col / 2) count[2]++;
        else if (final_row > room_row / 2 && final_col > room_col / 2) count[3]++;
        room[final_row][final_col]++;
    }

    int safety_factor = 1;
    for (const auto prvok : count) {
        safety_factor *= prvok;
    }


    cout << safety_factor<< '\n';
    return 0;
}

#include <bits/stdc++.h>
using namespace std;

struct Robot {
    int p_col, p_row, v_col, v_row;
};

int main() {
    const int time = 100, room_col = 101, room_row = 103;
    const regex pattern(R"(p=(-?[0-9]+),(-?[0-9]+) v=(-?[0-9]+),(-?[0-9]+))");
    vector<Robot> robots;

  
    ifstream file("../input.txt");
    for (string line; getline(file, line); ) {
        smatch match;
        if (regex_search(line, match, pattern)) {
            robots.push_back({
                stoi(match[1]) % room_col,
                stoi(match[2]) % room_row,
                stoi(match[3]) % room_col,
                stoi(match[4]) % room_row
            });
        }
    }

    long long seconds_elapsed = 1;
    int safety_factor = numeric_limits<int>::max();
    int iterations_without_improvement = 0;
    const int max_iterations_without_improvement = 10000;  

    while (true) {
        array<int, 4> count = {0, 0, 0, 0};

        
        for (auto& robot : robots) {
            robot.p_col = (robot.p_col + robot.v_col + room_col) % room_col;
            robot.p_row = (robot.p_row + robot.v_row + room_row) % room_row;

            int quadrant = (robot.p_row >= room_row / 2) * 2 + (robot.p_col >= room_col / 2);
            count[quadrant]++;
        }
        int new_safety_factor = accumulate(count.begin(), count.end(), 1, multiplies<int>());
        if (new_safety_factor < safety_factor) {
            safety_factor = new_safety_factor;
            cout << "Time: " << seconds_elapsed << '\n';
            iterations_without_improvement = 0;
        } else {
            iterations_without_improvement++;
        }

      
        if (iterations_without_improvement >= max_iterations_without_improvement) {
            break;
        }
        seconds_elapsed++;
    }

    return 0;
}

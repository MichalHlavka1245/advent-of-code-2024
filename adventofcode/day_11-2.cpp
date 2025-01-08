#include <bits/stdc++.h>
using namespace std;
struct pair_hash {
    size_t operator () (const pair<long long, long long> &p) const {
        auto h1 = hash<long long>{}(p.first);
        auto h2 = hash<long long>{}(p.second);
        return h1 ^ h2;
    }
};
unordered_map<pair<int, long long>, long long, pair_hash> memo;
long long calculateStones(int steps, long long stone) {
    auto key = make_pair(steps, stone);
    auto it = memo.find(key);
    if (it != memo.end()) return it->second;
    if (steps == 0) return 1;
long long result;
    if (stone == 0) {
        result = calculateStones(steps - 1, 1);
        memo[key] = result;
        return result;
    }
    string stoneString = to_string(stone);
    if (stoneString.size() % 2 == 0) {
        int mid = stoneString.size() / 2;
        long long leftStone = stoll(stoneString.substr(0, mid));
        long long rightStone = stoll(stoneString.substr(mid));
        result = calculateStones(steps - 1, leftStone) +
                    calculateStones(steps - 1, rightStone);
        memo[key] = result;
        return result;
    }
    result = calculateStones(steps - 1, stone * 2024);
    memo[key] = result;
    return result;
}

int main()
{
    string input="../input.txt";
ifstream fin(input);
vector<long long> stones;
    long long temp;
while(fin >> temp) stones.push_back(temp);
long long total_stones = 0;
    total_stones = 0;
for(auto& stone: stones){
total_stones += calculateStones(75, stone);
}
cout << total_stones << endl;
}

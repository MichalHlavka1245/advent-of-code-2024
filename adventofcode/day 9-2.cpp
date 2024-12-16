#include <bits/stdc++.h>
using namespace std;
struct Block {
    Block(const int start_idx, const int size, const int value) : start_idx(start_idx), size(size), value(value) {}
    int start_idx;
    int size;
    int value;

    tuple<Block, Block> split(const int size_in, const int value_in) const {
        return {Block(start_idx, size_in, value_in), Block(start_idx + size_in, size - size_in, -1)};
    }
};
int main() {
    string input = "../input.txt";
    ifstream file(input);
    string line;
    getline(file, line);
    vector<Block> blocks;
    int pocet_suborov = 0;
    int pos = 0;
    int volny = false;
    for (const auto c : line) {
        const int c_num = c - '0';
        if (volny) {
            blocks.emplace_back(pos, c_num, -1);
            volny = false;
        } else {
            blocks.emplace_back(pos, c_num, pocet_suborov);
            volny = true;
            pocet_suborov++;
        }
        pos += c_num ;
    }
    int index = blocks.size() - 1;
    while (index > 0) {
        if (blocks[index].value == -1) {
            index--;
            continue;
        }
        for (int idx_2 = 0; idx_2 < index; idx_2++) {
            if (blocks[idx_2].value == -1 && blocks[idx_2].size >= blocks[index].size) {
                const auto [b1, b2] = blocks[idx_2].split(blocks[index].size, blocks[index].value);
                blocks[idx_2] = b1;
                blocks[index].value = -1;
                blocks.insert(begin(blocks) + idx_2 + 1, b2);
                break;
            }
        }
        index--;
    }
    unsigned long long answer = 0;
    index = 0;
    for (const auto& b : blocks) {
        if (b.value != - 1) {
            for (int i = 0; i < b.size; i++, index++) {
                answer += index * b.value;
            }
        } else {
            index += b.size;
        }
    }

    cout <<"answer=" <<answer << '\n';
    return 0;
}
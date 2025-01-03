#include <bits/stdc++.h>
using namespace std;
int main() {
    string input = "../input.txt";
    ifstream file(input);
    string line;
    long long vysledok = 0;
    unordered_map<int, vector<int>> pravidla;
    vector<vector<int>> aktualizacie;
    while(getline(file, line)) {
        if (line.empty()) break;
        const auto idx = line.find('|');
        pravidla[stoi(line.substr(0, idx))].push_back(stoi(line.substr(idx + 1, line.size())));
    }
    while(getline(file, line)) {
        size_t current = 0;
        size_t comma_idx = line.find(',');
        aktualizacie.emplace_back();
        auto& update = aktualizacie.back();
        while(comma_idx != string::npos) {
            update.push_back(stoi(line.substr(current, comma_idx - current)));
            current = comma_idx + 1;
            comma_idx = line.find(',', current);
        }
        update.push_back(stoi(line.substr(current, line.size() - current)));
    }
    for (auto& update : aktualizacie) {
        bool follows_rules = true;
        for (int i = 0; i < update.size() && follows_rules; i++) {
            for (int j = i+1; j < update.size() && follows_rules; j++) {
                if (ranges::contains(pravidla[update[j]], update[i])) {
                    follows_rules = false;
                }
            }
        }
        if (!follows_rules) {
            ranges::sort(update,[&pravidla](const auto& n1, const auto& n2)
                                {return ranges::contains(pravidla[n2], n1); });
            vysledok += update[update.size() / 2];
        }
    }

    cout << vysledok << '\n';
    return 0;
}

#include<bits/stdc++.h>
using namespace std;
constexpr int n_level = 75;

struct Node {
    long long engraving;
    Node* left;
    Node* right;
};
queue<pair<Node*, int>> q;
void blink_n(vector<unique_ptr<Node>>& nodes, unordered_map<long long, Node*>& seen) {
    while(!q.empty()) {
        auto [node, level] = q.front();
        q.pop();

        if (level >= 75) continue;
        int n_digits = 0;
        {
            auto engraving = node->engraving;
            while(engraving > 0) {
                n_digits++;
                engraving /= 10;
            }
        }
        if (node->engraving == 0) {
            auto new_node = make_unique<Node>();
            new_node->engraving = 1;
            if (!seen.contains(new_node->engraving)) {
                nodes.push_back(move(new_node));
                node->left = nodes.back().get();
                seen[nodes.back().get()->engraving] = nodes.back().get();
                q.push({nodes.back().get(), level+1});
            } else {
                node->left = seen[new_node->engraving];
            }
        } else if (n_digits % 2 == 0) {
            {
                auto new_node = make_unique<Node>();
                new_node->engraving = node->engraving / static_cast<long long>(pow(10, n_digits / 2));
                if (!seen.contains(new_node->engraving)) {
                    nodes.push_back(std::move(new_node));
                    node->left = nodes.back().get();
                    seen[nodes.back().get()->engraving] = nodes.back().get();
                    q.push({nodes.back().get(), level+1});
                } else {
                    node->left = seen[new_node->engraving];
                }
            }
            {
                auto new_node = make_unique<Node>();
                new_node->engraving = node->engraving % static_cast<long long>(pow(10, n_digits / 2));
                if (!seen.contains(new_node->engraving)) {
                    nodes.push_back(std::move(new_node));
                    node->right = nodes.back().get();
                    seen[nodes.back().get()->engraving] = nodes.back().get();
                    q.push({nodes.back().get(), level+1});
                } else {
                    node->right = seen[new_node->engraving];
                }
            }
        } else {
            auto new_node = make_unique<Node>();
            new_node->engraving = node->engraving * 2024;
            if (!seen.contains(new_node->engraving)) {
                nodes.push_back(std::move(new_node));
                node->left = nodes.back().get();
                seen[nodes.back().get()->engraving] = nodes.back().get();
                q.push({nodes.back().get(), level+1});
            } else {
                node->left = seen[new_node->engraving];
            }
        }

    }
}

unordered_map<long long, unordered_map<long long, long long>> memory;
long long count (Node * node, const int level){
    // if (level == n_level ) cout << node->engraving << ' ';
    if (level == n_level) return 1;
    if (memory.contains(node->engraving) && memory[node->engraving].contains(level)) return memory[node->engraving][level];
    if (node->left == nullptr && node->right == nullptr) return 1;
    long long n = 0;
    if (node->left != nullptr) n += count(node->left, level+1);
    if (node->right != nullptr) n += count(node->right, level+1);
    memory[node->engraving][level] = n;
    return n;
}

int main() {
    string input = "../input.txt";

    ifstream file(input);
    string line;
    while(getline(file, line)){
        vector<unique_ptr<Node>> nodes;
        long long current = 0;
        long long idx = line.find(' ');
        while(idx != string::npos) {
            nodes.emplace_back();
            nodes.back() = std::make_unique<Node>();
            nodes.back()->engraving = stoi(line.substr(current, idx - current));
            current = idx + 1;
            idx = line.find(' ', current);
        }
        nodes.emplace_back();
        nodes.back() = make_unique<Node>();
        nodes.back()->engraving = stoi(line.substr(current, line.size() - current));
        const int n = nodes.size();
        long long answer = 0;
        for (int i = 0; i < n; i++){
            vector<unique_ptr<Node>> nodes_temp;
            nodes_temp.push_back(move(nodes[i]));
            unordered_map<long long, Node*> seen;
            q = {};
            q.push(make_pair<Node*, int>(nodes_temp.back().get(), 0));
            seen[nodes_temp.back().get()->engraving] = nodes_temp.back().get();
            blink_n(nodes_temp, seen);
            answer += count(nodes_temp[0].get(), 0);
        }

        cout << fixed << answer << '\n';
    }
    return 0;
}
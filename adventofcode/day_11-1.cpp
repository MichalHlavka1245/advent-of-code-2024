#include <bits/stdc++.h>
using namespace std;
int main() {
    vector<long long> v;
    string line;
    getline(cin, line);

    stringstream ss(line);
    int temp;

    while (ss >> temp) {
        v.push_back(temp);
    }
    for (int rep = 0; rep < 25; rep++) {
        vector<long long> newV;
        for (long long x : v) {
            if (x == 0) {
                newV.push_back(1);
            }
            else if (to_string(x).length() % 2 == 0) {
                string s = to_string(x);
                int k = s.length();
                newV.push_back(stoll(s.substr(0, k/2)));
                newV.push_back(stoll(s.substr(k/2, k/2)));
            }
            else {
                newV.push_back(x * 2024);
            }
        }
        v = newV;
    }
    cout << v.size() << endl;
    return 0;
}
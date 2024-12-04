#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
int main() {
    vector<int> zoznam(1000), zoznam1(1000);

    for(int i = 0; i < 1000; i++) {
        cin >> zoznam[i] >> zoznam1[i];
    }
    sort(zoznam.begin(), zoznam.end());
    sort(zoznam1.begin(), zoznam1.end());
    long long sucet = 0;
    for(int i = 0; i < 1000; i++) {
        int rozdiely = abs(zoznam[i] - zoznam1[i]);
        sucet += rozdiely;
        cout << zoznam[i] << " " << zoznam1[i] << " (rozdiel: " << rozdiely << ")" << endl;
    }
    cout << "Celkovy sucet rozdielov: " << sucet << endl;

    return 0;
}
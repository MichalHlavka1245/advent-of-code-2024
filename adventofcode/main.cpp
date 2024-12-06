#include <iostream>
#include <vector>
#include <sstream>
#include <string>
using namespace std;

bool scitanie(const vector<int>& riadok) {
    for (size_t i = 0; i < riadok.size() - 1; i++) {
        int rozdiel = riadok[i+1] - riadok[i];
        if (rozdiel != 1 && rozdiel != 2 && rozdiel != 3) {
            return false;
        }
    }
    return true;
}
bool odcitanie(const vector<int>& riadok) {
    for (size_t i = 0; i < riadok.size() - 1; i++) {
        int rozdiel = riadok[i] - riadok[i+1];
        if (rozdiel != 1 && rozdiel != 2 && rozdiel != 3) {
            return false;
        }
    }
    return true;
}
int main() {
    int pocet_bezpecne = 0;
    string riadok_text;

    for (int i = 0; i < 1000; i++) {

        if (!getline(cin, riadok_text)) break;

        istringstream iss(riadok_text);

        vector<int> riadok;
        int cislo;


        while (iss >> cislo) {
            riadok.push_back(cislo);
        }
        cout << "Pocet cisel v riadku " << i+1 << ": " << riadok.size() << endl;
        if (riadok.size() < 2) continue;
        if (riadok[0] < riadok[1]) {
            if (scitanie(riadok)) {
                pocet_bezpecne++;
            }
        }

        if (riadok[0] > riadok[1]) {
            if (odcitanie(riadok)) {
                pocet_bezpecne++;
            }
        }
    }

    cout << "Celkovy pocet bezpecnych riadkov: " << pocet_bezpecne << endl;
    return 0;
}
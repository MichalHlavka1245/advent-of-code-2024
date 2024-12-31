#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
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

bool je_mozne_spravit_bezpecny(vector<int> riadok, int& pozicia_vymazaneho_cisla) {

    for (int i = 0; i < riadok.size(); i++) {
        vector<int> test_riadok = riadok;
        test_riadok.erase(test_riadok.begin() + i);
        
    if (test_riadok.size() < 2) continue;
        if (test_riadok[0] < test_riadok[1]) {
            if (scitanie(test_riadok)) {
                pozicia_vymazaneho_cisla = i;
                return true;
            }
        }
    if (test_riadok[0] > test_riadok[1]) {
            if (odcitanie(test_riadok)) {
                pozicia_vymazaneho_cisla = i;
                return true;
            }
        }
    }
    return false;
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
//cout << "Pocet cisel v riadku " << i+1 << ": " << riadok.size() << endl;

if (riadok.size() < 2) continue;
int pozicia_vymazaneho_cisla = -1;
bool povodny_bezpecny = false;
        
        if (riadok[0] < riadok[1]) {
            if (scitanie(riadok)) {
                pocet_bezpecne++;
                povodny_bezpecny = true;
            }
        }

        if (riadok[0] > riadok[1]) {
            if (odcitanie(riadok)) {
                pocet_bezpecne++;
                povodny_bezpecny = true;
            }
        }

if (!povodny_bezpecny) {
            if (je_mozne_spravit_bezpecny(riadok, pozicia_vymazaneho_cisla)) {
            pocet_bezpecne++;
cout << "Riadok sa stal bezpecny po odstraneni cisla na pozicii "<< pozicia_vymazaneho_cisla << endl;
            }
        }
    }

    cout << "Celkovy pocet bezpecnych riadkov: " << pocet_bezpecne << endl;
    return 0;
}

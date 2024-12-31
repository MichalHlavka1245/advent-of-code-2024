#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <string>
using namespace std;

int main(){
    string text, total="";
    ifstream inputFile("../data.txt");

    if (!inputFile) {
        cerr << "Error opening file data.txt" << endl;
        return 1;
    }

    while(getline(inputFile, text)) total += text;

    regex vzor(R"(mul\((\d{1,3}),(\d{1,3})\))"), vzorSwitch(R"(do\(\)|don't\(\))");
    smatch match;
    unsigned long long result = 0;
    bool isOn = true;

    vector<size_t> state; //pozicia  kde sa nachadza do a don´t
    sregex_iterator iterSwitch(total.begin(), total.end(), vzorSwitch), endSwitch;

    while(iterSwitch != endSwitch){
        smatch match = *iterSwitch;
        if(match.str() == "don't()" && state.size() % 2 == 0) state.push_back(match.position());
        else if(match.str() == "do()" && state.size() % 2 == 1) state.push_back(match.position());
        ++iterSwitch;
    }

    sregex_iterator iter(total.begin(), total.end(), vzor), end;

    while (iter != end) {
        smatch match = *iter;
        bool isOn = true;
        size_t pos = match.position();

        for(int i = 1; i < state.size(); i++){
            if(pos>state[i-1]&&pos<state[i]){
                (i%2==1?isOn=0:isOn=1);
                break;
            }
        }

        if(!state.empty()&&pos>state[state.size()-1]&&state.size()%2==1) isOn = false;

        if(isOn){
            int first = stoi(match[1]);
            int second = stoi(match[2]);

            result += first * second;
            cout<<result<<endl;
        }
        ++iter;
    }
    cout << result << "\n";
    return 0;
}

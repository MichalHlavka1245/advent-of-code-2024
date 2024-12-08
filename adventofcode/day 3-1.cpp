#include <iostream>
#include <regex>
#include <string>
using namespace std;
int main(){
    string text; regex vzor(R"(mul\((\d{1,3}),(\d{1,3})\))"); smatch match; long long result = 0;
    while(getline(cin, text)){
        sregex_iterator iter(text.begin(), text.end(), vzor), end;
        while (iter != end) {
            smatch match = *iter;
            int first = stoi(match[1]);
            int second = stoi(match[2]);
            result += first * second;
            cout<<result<<endl;
            ++iter;
        }
    }
    cout << result << endl;
    return 0;
}
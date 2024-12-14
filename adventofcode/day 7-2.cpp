#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;
void rec(int i, long long sum, long long target, const vector<int>& v, bool& ok) {
    if(i==(int) v.size()){
        if(sum==target){
            ok=true;
        }
        return;
    }
    rec(i+1,sum+v[i],target,v,ok);
    rec(i+1,sum*v[i],target,v,ok);
    rec(i+1,stoll(to_string(sum)+to_string(v[i])),target,v,ok);

}

int main() {
    string line;
    long long total_answer = 0;

    while (getline(cin, line)) {

        istringstream iss(line);
        long long result;
        char colon; // načiatnie :

        if (!(iss >> result >> colon)) {
            break;
        }

        vector<int> v;
        int x;
        while (iss >> x) {
            v.push_back(x);
        }

        cout << result << endl;
        bool ok = false;
        rec(1, v[0], result, v, ok);

        if (ok) {
            total_answer += result;
        }
    }

    cout << "total_answer=" << total_answer << endl;
    return 0;
}
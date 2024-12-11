#include <bits/stdc++.h>
#include <iostream>
using namespace std;
int main(){
string s;
    long long answer=0;
map<int,vector<int>> edges;
    while (getline(cin, s)){
        if (s.empty() or !isdigit(s[0])){
            continue;
        }
        int length =(int) s.length();
        vector<int>v;
        bool was_pipe =false;
        cout<< s<<endl;
        for (int i = 0; i < length; i++){
            if(isdigit(s[i])){
                int x=0;
                while(isdigit(s[i])){
                    x=x*10+(s[i]-'0');
                    i++;
                }
                v.push_back(x);
                cout<<"i="<<i<<" s[i]="<<int(s[i])<<endl;
                if(s[i]== '|'){
                    was_pipe = true;
                }
                assert(s[i]==',' || s[i]=='|' ||s[i]=='\n' || s[i]==0);
                cout<<"x="<< x << " ";
            }
        }
        if(was_pipe){
            edges[v[0]].push_back(v[1]);
        }
        else{
            set<int> earlier;
            bool ok=true;
            for(int i=0;i< (int) v.size();i++){
                int x = v[i];
                for(int y:edges[x]){
                    if(earlier.count(y)){
                        ok=false;
                    }
                }
                earlier.insert(x);
            }
            if(ok){
                answer+=v[v.size()/2];
                cout<<answer<<endl;
            }
        }
    }
    cout << "answer ="<<answer << endl;
    return 0;
}

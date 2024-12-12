#include <iostream>
#include <bits/stdc++.h>
using namespace std;
vector< pair<int,int>> dirs = {{-1,0},{0,1},{1,0},{0,-1} };

int main(){
    const int heigth =130;
    vector<string> a(heigth); // a je pre grid a nechce sa furt pisat grid
    for(int i =0;i<heigth;i++){
        cin>>a[i];
    }
    int width = a[0].length();

    pair<int,int> start_me {-1,-1};
    for(int row =0;row<heigth;row++){
        for(int col =0;col<width;col++){
            if(a[row][col]=='^'){
                start_me={row,col};
                a[row][col]='.';
            }
        }
    }
    auto solveCycle= [&] (){
     pair<int,int> me=start_me;
        int dir =0;

        set<vector<int>> visited;
        int turns = 0;
        while(true){
            turns++;
            if(!visited.insert(vector<int>{me.first,me.second,dir}).second){
                return true;
            }
            int r2=me.first+dirs[dir].first;
            int c2=me.second+dirs[dir].second;
            if(!(0<=r2 && r2<heigth && 0<=c2 && c2<width)){
                return false; // som mimo
            }
            if(a[r2][c2]=='.'){
                me={r2,c2};
            }
            else{
                dir=(dir+1)%4;
            }
        }
    };
    int answer =0;
    for(int row =0;row<width;row++){
        for(int col =0;col<width;col++){
            if(a[row][col]=='.' and start_me !=make_pair(row,col) ){
                cout<<row<<" "<<col<<endl;
                a[row][col]='#';
                if(solveCycle()){
                    answer++;
                    cout<<"answer ="<<answer<<endl;
                }
                a[row][col]='.';
            }
        }

    }

    cout<<answer<<endl;
    return 0;
}
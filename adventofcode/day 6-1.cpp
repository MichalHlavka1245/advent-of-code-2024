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

pair<int,int> me {-1,1};
    int dir=0;
    for(int row =0;row<width;row++){
        for(int col =0;col<width;col++){
            if(a[row][col]=='^'){
                me={row,col};
                a[row][col]='.';
            }
        }
    }
    set<pair<int,int>> vistited;
    while(true){
        vistited.insert(me);
    int r2=me.first+dirs[dir].first;
    int c2=me.second+dirs[dir].second;
    if(!(0<=r2 and r2<=heigth && 0<=c2 and c2<=width)){
        break; // som mimo
    }
        if(a[r2][c2]=='.'){
            me={r2,c2};
        }
        else{
            dir=(dir+1)%4;
        }
    }
cout<<vistited.size()<<endl;
    return 0;
}

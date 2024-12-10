#include <iostream>
#include <vector>
#include <string>
using namespace std;
const vector<pair<int,int>> directions = {{-1,-1},{-1,1},{1,1},{1,-1}};
int main()
{
    int  H = 140;  // H is for heigth
    vector <string> a(H);
    for(string& row : a)
    {
        cin>>row;
    }
    int W =  (int) a[0].length();    // W is for width
    long long answer = 0;
    for(int row = 1; row < H-1; row++){
        for(int col = 1; col < W-1; col++){
            if(a[row][col] == 'A'){
                string s;
                for(pair<int,int> direction : directions){
                    s+=a[row+direction.first][col+direction.second];
                }
                if(s== "MMSS" or s == "MSSM" or s=="SSMM" or s=="SMMS"){
                    answer++;
                    }
                }
            }
        }
cout<<answer<<endl;
    return 0;
}
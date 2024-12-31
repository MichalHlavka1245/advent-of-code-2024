#include <iostream>
#include <vector>
#include <string>
using namespace std;
int main()
{
    int  H = 140;  // H is for heigth
    long long answer = 0;
    vector <string> a(H);
    for(string& row : a)
    {
        cin>>row;
    }
    int W =  (int) a[0].length();    // W is for width
    auto inside = [&](int row, int col){
        return 0 <= row && row < H && 0 <= col && col < W;
    };
    const string vzor = "XMAS";
    for(int row = 0; row < H; row++){
        for(int col = 0; col < W; col++)
        {
            if(a[row] [col] == 'X')
            {
                for (int drow = -1; drow <= 1; drow++){
                    for (int dcol = -1; dcol <= 1; dcol++)
                    {
                        if(drow == 0 && dcol == 0){
                            continue;
                        }
                        bool all_ok = true;
                        for(int i=0 ;i<4 ;i++){
                            int r2=row+drow* i;
                            int c2 = col+dcol* i;
                            if(inside(r2,c2) and a[r2][c2] == vzor[i]){
                                continue;
                            }
                            else{
                                all_ok = false;
                                break;
                            }
                        }
                        answer +=all_ok;
                    }

                }
            }
        }

    }
    cout<<answer<<endl;
    return 0;
}

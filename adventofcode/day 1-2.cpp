#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
int main()
{
    vector<int> zoznam(1000),zoznam1(1000);
    int spolu=0;
    for (int c = 0; c < 1000; c++)
    {
        cin>>zoznam[c]>>zoznam1[c];

    }
    for (int i = 0; i < 1000; i++)
    {
        int aktualne_cislo=zoznam[i];



        for (int j = 0; j < 1000; j++)
        {
            int pocet=0;
            if(aktualne_cislo==zoznam1[j])
            {
                pocet++;
                if(pocet==0) spolu+=0;
                else
                {
                    spolu+=aktualne_cislo*pocet;
                    cout<<spolu<<endl;
                }
            }


        }
    }
    cout<<spolu<<endl;
    return 0;
}

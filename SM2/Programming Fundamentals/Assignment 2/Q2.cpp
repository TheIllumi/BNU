// Q2:
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
using namespace std;

int main()
{
    int Rollp1, Rollp2, P1Counter = 0, P2Counter = 0;
    string p1, p2, Exit;
    cout<<"Enter name for player-1: ";
    cin>>p1;
    cout<<"Enter name for player-2: ";
    cin>>p2;
    cout<<endl;

    srand(time(0));

    while (P1Counter < 100 && P2Counter < 100)
    {
        Rollp1 = rand() % 6 + 1;
        Rollp2 = rand() % 6 + 1;
        cout<< setw(25) <<"Dice rolled for player-1: "<<Rollp1;
        cout<< setw(40) <<"Dice rolled for player-2: "<<Rollp2<<endl;
        if (P1Counter + Rollp1 <= 100)
        {
            P1Counter = P1Counter + Rollp1;
        }
        if (P2Counter + Rollp2 <= 100)
        {
            P2Counter = P2Counter + Rollp2;
        }
        cout<< setw(25) <<"Cumulative score for player-1: "<<P1Counter;
        cout<< setw(40) <<"Cumulative score for player-2: "<<P2Counter<<endl;
        cout<< setw(25) <<"Press 'N' if you wish to exit the game: ";
        cin>>Exit;
        if (Exit == "N" || Exit == "n")
        {
            break;
        }
        cout<<endl;
        if (P1Counter >= 100 && P1Counter>P2Counter)
        {
            int FixedScore = P1Counter / 10 * 10;
            cout<<"Player Name: "<<p1<<endl;
            cout<<"Total Score: "<<FixedScore<<endl;
            cout<<"You Win!...Congratulations"<<endl;
            cout<<endl;
            cout<<"Player Name: "<<p2<<endl;
            cout<<"Total Score: "<<P2Counter<<endl;
            cout<<"Better luck! Next time"<<endl;
        }
        if (P2Counter >= 100 && P2Counter>P1Counter)
        {
            int FixedScore = P2Counter / 10 * 10;
            cout<<"Player Name: "<<p2<<endl;
            cout<<"Total Score: "<<FixedScore<<endl;
            cout<<"You Win!...Congratulations"<<endl;
            cout<<endl;
            cout<<"Player Name: "<<p1<<endl;
            cout<<"Total Score: "<<P1Counter<<endl;
            cout<<"Better luck! Next time"<<endl;
        }
    }
    return 0;
}

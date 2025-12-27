#include<iostream>
#include<iomanip>
#include<cstdlib>
#include<ctime>
using namespace std;
int main()
{
    string name1,name2;
    int sum1=0;
    int sum2=0;
    int dice1,dice2, r_num;
    cout<<"enter name of player 1: ";
    cin>>name1;
    cout<<"enter name of player 2: ";
    cin>>name2;
    srand(time(0));

    while(sum1<100 && sum2<100) {
        r_num = rand() % 6 + 1;
        dice1 = r_num;
        cout << "dice roll for "<<name1<<": " << dice1 << endl;
        if (sum1 + dice1 <=100)
        {
            sum1 = sum1 + dice1;
        }
        r_num = rand() % 6 + 1;
        dice2 = r_num;
        cout << "dice roll for "<<name2<<": " << dice2 << endl;
        cout<<endl;
        if (sum2 + dice2 <= 100)
        {
            sum2 = sum2 + dice2;
        }

        string Exit;
        cout<<"Press N if you wish to exit: ";
        cin>>Exit;
        if (Exit == "N")
        {
            break;
        }
    }
    if(sum1>sum2)
    {
        cout<<name1<<" you win!....Congratulations. Sum= "<<sum1<<endl;
        cout<<name2<<" better luck! Next time. Sum= "<<sum2<<endl;
    }
    if(sum2>sum1)
    {
        cout<<name2<<" you win!....Congratulations. Sum= "<<sum2<<endl;
        cout<<name1<<" better luck! Next time. Sum= "<<sum1<<endl;
    }


    return 0;
}
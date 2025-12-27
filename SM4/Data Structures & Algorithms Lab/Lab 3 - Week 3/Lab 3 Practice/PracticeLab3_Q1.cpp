#include <iostream>
#include <string>
using namespace std;

class GameEntry
{
private:
    string name;
    int score;

public:
    GameEntry(const string &n = "", int s = 0);
    string GameEntry::getName() const { return name; }
    int GameEntry::getScore() const { return score; }
    void print() const;
};

GameEntry::GameEntry(const string &n, int s) : name(n), score(s) {}

void GameEntry::print() const
{
    cout << name << " - " << score << endl;
}

class Scores
{
private:
    int maxEntries;
    int numEntries;
    GameEntry *entries;

public:
    Scores(int maxEnt = 10);
    void add(const GameEntry &e);
    GameEntry remove(int i);
    int getNumEntries() const { return numEntries; }
    void print() const;
    ~Scores();
};

Scores::Scores(int maxEnt) : maxEntries(maxEnt), numEntries(0), entries(new GameEntry[maxEntries]) {}

Scores::~Scores()
{
    delete[] entries;
    entries = nullptr;
}

void Scores::add(const GameEntry &e)
{
    int newScore = e.getScore();

    if (numEntries == maxEntries)
    {
        if (newScore <= entries[maxEntries - 1].getScore())
        {
            return;
        }
    }
    else
    {
        numEntries++;
    }

    int i = numEntries - 2;

    while (i >= 0 && newScore > entries[i].getScore())
    {
        entries[i + 1] = entries[i];
        i--;
    }
    entries[i + 1] = e;
}

GameEntry Scores::remove(int i)
{
    if (i < 0 || i >= numEntries)
    {
        cout << "Invalid Index";
        return GameEntry();
    }

    GameEntry e = entries[i];

    for (int j = i + 1; j < numEntries; j++)
    {
        entries[j - 1] = entries[j];
    }
    numEntries--;
    return e;
}

void Scores::print() const
{
    for (int i = 0; i < numEntries; i++)
    {
        entries[i].print();
    }
}

int main()
{
    Scores leaderboard(10);
    GameEntry g1("Huda", 100);
    GameEntry g2("Ayesha", 50);

    leaderboard.add(g1);
    leaderboard.add(g2);
    leaderboard.print();

    cout << "Enter 'a' to add and 'd' to delete: ";
    char choice;
    cin >> choice;

    if (choice == 'a')
    {
        cout << "Enter player name: ";
        string name;
        cin >> name;

        cout << "Enter player score: ";
        int score;
        cin >> score;

        GameEntry g3(name, score);
        leaderboard.add(g3);
        leaderboard.print();
    }
    else if (choice == 'd')
    {
        cout << "Enter index to remove: ";
        int index;
        cin >> index;

        if (index < 0 || index >= leaderboard.getNumEntries())
        {
            cout << "Invalid index!" << endl;
        }
        else
        {
            leaderboard.remove(index);
            leaderboard.print();
        }
    }

    return 0;
}
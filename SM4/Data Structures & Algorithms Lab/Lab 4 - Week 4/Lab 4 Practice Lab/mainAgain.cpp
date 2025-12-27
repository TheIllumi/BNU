#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <unordered_set>
using namespace std;

// Function to calculate score based on word length
int calculateScore(const string &word)
{
    if (word.length() == 3)
        return 1;
    if (word.length() == 4)
        return 2;
    if (word.length() == 5)
        return 3;
    if (word.length() == 6)
        return 4;
    if (word.length() >= 7)
        return 5;
    return 0;
}

// Function to check if a word is valid (exists in dictionary and uses only baseword letters)
bool isValidWord(const string &word, const string &baseword, const unordered_set<string> &dictionary)
{
    if (dictionary.find(word) == dictionary.end())
        return false;
    string temp = baseword;
    for (char c : word)
    {
        size_t pos = temp.find(c);
        if (pos == string::npos)
            return false;
        temp.erase(pos, 1);
    }
    return true;
}

int main()
{
    // OPENING FILE AND READING WORDS
    ifstream inputFile("engmix.txt");
    if (!inputFile)
    {
        cout << "Error opening file!" << endl;
        return 1;
    }

    vector<string> allwords;
    vector<string> selectedwords;
    string line;
    unordered_set<string> wordSet;

    while (getline(inputFile, line))
    {
        allwords.push_back(line);
        wordSet.insert(line);
        if (line.length() >= 7)
            selectedwords.push_back(line);
    }
    inputFile.close();

    srand(time(0));
    string baseword = selectedwords[rand() % selectedwords.size()];
    cout << "The baseword: " << baseword << endl;

    vector<pair<string, int>> players; // Stores player names and scores
    char playAgain;

    do
    {
        string playerName;
        cout << "Enter your name: ";
        cin >> playerName;

        unordered_set<string> usedWords; // To track duplicate words
        int score = 0;
        string userWord;

        cout << "Start forming words using baseword. Enter 0 to quit.\n";

        while (true)
        {
            cout << "Enter word: ";
            cin >> userWord;

            if (userWord == "0")
                break;

            if (usedWords.find(userWord) != usedWords.end())
            {
                cout << "Word already used! Try another.\n";
                continue;
            }

            if (isValidWord(userWord, baseword, wordSet))
            {
                int wordScore = calculateScore(userWord);
                score += wordScore;
                usedWords.insert(userWord);
                cout << "Accepted! You earned " << wordScore << " points.\n";
            }
            else
            {
                cout << "Invalid word! Try again.\n";
            }
        }

        cout << playerName << ", your total score: " << score << "\n";
        players.push_back({playerName, score});

        cout << "Another player? (y/n): ";
        cin >> playAgain;
    } while (playAgain == 'y' || playAgain == 'Y');

    cout << "\nGame Over! Top Scores:\n";
    for (const auto &p : players)
    {
        cout << p.first << " - " << p.second << " points\n";
    }

    return 0;
}
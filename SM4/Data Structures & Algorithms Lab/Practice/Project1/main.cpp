#include <iostream>
#include <string>
#include <cstring>
using namespace std;

bool isPalindrome(string words, int len);

int main()
{
    /*
    // Q1
    string word;
    cout << "Enter a word to check if it is a palindrome: ";
    cin >> word;
    cout << endl;

    int length = word.length();
    
    if (isPalindrome(word, length) == true) {
        cout << word << " is a palindrome." << endl;
    }
    else {
        cout << word << " is a not palindrome." << endl;
    }

    // Q2
    cout << "The reverse of " << word << " is: ";
    for (int i = length; i >= 0; i--)
    {
        cout << word[i];
    }

    cout << endl;

    // Q3
    string word1;
    string word2;
    cout << "Enter the first string: ";
    cin >> word1;
    cout << "\nEnter the second string: ";
    cin >> word2;

    int lengthOne = word1.length();
    int lengthTwo = word2.length();

    int count = lengthTwo;

    cout << "\nChecking if the second string appears in the first string..." << endl;
    for (int i = 0; i < word2.length(); i++)
    {
        for (int j = 0; j < word1.length(); j++) {
            //check if word 2 appears in word 1
            if (word2[i] == word1[j])
            {
                cout << "The character of the second string (" << word2[i] << ") is found in index (" << j << ") of the first string" << endl;
                count--;
            }
        }
    }
    if (count == 0) {
        cout << "True" << endl;
    }
    else {
        cout << "False" << endl;
    }
    
    
    */

    // Q4
    string stringArray[6];
    cout << "Enter words in the string." << endl;
    for (int i = 0; i < 6; i++)
    {
        cin >> stringArray[i];
    }
    cout << endl;
    /*for (int i = 0; i < 6; i++)
    {
        cout << stringArray[i] << endl;
    }*/

    bool found = true;

    for (int i = 0; i < 6; i++)
    {
        while (!found) {
            for (int j = 0; j < stringArray[i].length(); j++)
            {
                if (stringArray[j]) {
                    found = true;
                }
            }
        }


        // return only those strings that contain a number
        for (int j = 0; j < stringArray[i].length(); j++) {
            cout << stringArray[j] << endl;
        }
    }

    return 0;
}

// Q1
bool isPalindrome(string words, int len)
{
    //int length = words.length();
    for (int i = 0; i < len / 2; i++)
    {
        if (words[i] != words[len - i - 1])
            return false;
    }
    return true;
}

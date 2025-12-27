#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class MyString{
private:
    vector<char> str;
public:
    // Default constructor
    MyString() {}

    // Parametrized constructor
    MyString(const string& s) {
        str.assign(s.begin(), s.end());
    }

    // Destructor
    ~MyString(){
        str.clear();
    }

    // Setter
    void SetString() {
        string input;
        cout << "Enter a string: ";
        getline(cin, input);
        if (input.empty()) {
            cout << "Input cannot be empty. Please try again." << endl;
            return;
        }
        str.assign(input.begin(), input.end());
    }

    // Find the length of the string
    int FindLength() const {
        return str.size();
    }

    // Concatenate two strings
    MyString Concatenate(const MyString &other) const {
        MyString result;
        result.str = str;
        result.str.push_back(' ');
        result.str.insert(result.str.end(), other.str.begin(), other.str.end());
        return result;
    }

    // Make a sub-string
    MyString SubString(int start, int length) {
        MyString result;

        if (start >= 0 && start < str.size() && length > 0) {
            result.str.insert(result.str.end(), str.begin() + start, str.begin() + start + length);
        } else {
            cout << "Invalid start index or length." << endl;
        }

        return result;
    }

    // Search a word in a string
    bool SearchWord(const string& word) const {
        return std::search(str.begin(), str.end(), word.begin(), word.end()) != str.end();
    }

    // Reverse the string
    void ReverseString() {
        int n = str.size();
        for (int i = 0; i < n / 2; ++i) {
            swap(str[i], str[n - i - 1]);
        }
    }
    // Display
    void Display() const {
        for(char c : str) {
            cout << c;
        }
        cout << endl;
    }
};

int main() {
    MyString myStr;
    MyString myStr1;

    myStr.SetString();
    myStr1.SetString();
    cout << "You entered: ";
    myStr.Display();
    cout << "You entered: ";
    myStr1.Display();

    MyString myStr2 = myStr.Concatenate(myStr1);
    cout << "Concatenate the two strings: ";
    myStr2.Display();

    cout << "Reverse the concatenated string: ";
    myStr2.ReverseString();
    myStr2.Display();
    cout << endl;

    cout << "Length of first string: " << myStr.FindLength() << endl;
    cout << "Length of second string: " << myStr1.FindLength() << endl;
    cout << "Length of the concatenated string: " << myStr2.FindLength() << endl;
    cout << endl;

    cout << "Reversed concatenated string reverted back to original: ";
    myStr2.ReverseString();
    myStr2.Display();
    cout << endl;

    string wordToSearch;
    cout << "Enter a word to search for in the first string: ";
    cin >> wordToSearch;

    if (myStr2.SearchWord(wordToSearch)) {
        cout << "The word \"" << wordToSearch << "\" was found in the concatenated string." << endl;
    } else {
        cout << "The word \"" << wordToSearch << "\" was not found in the concatenated string." << endl;
    }

    int start, length;
    cout << "Enter the start index for substring: ";
    cin >> start;
    cout << "Enter the length of the substring: ";
    cin >> length;

    MyString subStr = myStr.SubString(start, length);
    cout << "Substring of the first string: ";
    subStr.Display();

    return 0;
}

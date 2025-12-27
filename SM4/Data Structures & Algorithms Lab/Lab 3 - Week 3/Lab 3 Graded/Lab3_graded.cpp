#include <iostream>
#include <string>
#include <cstring>
using namespace std;

class AlphabetArrayList
{
public:
    AlphabetArrayList(int = 10);
    void getListValuesFromUser();
    bool insert(int);
    void display();

    int countVowels();
    int findLastIndex(char);
    void swapElements(int, int);
    void mergeFirstN(const AlphabetArrayList &, int);
    void sortedMerge(const AlphabetArrayList &, const AlphabetArrayList &);

    int vowelCount = 0;
    int size;
    int capacity;
    char *arraylist;
};

AlphabetArrayList::AlphabetArrayList(int list_capacity)
{
    size = 0;
    capacity = list_capacity;
    arraylist = new char[capacity];

    for (int i = 0; i < capacity; i++)
        arraylist[i] = '_'; // to show empty elements while printing
}

bool AlphabetArrayList::insert(int new_element)
{
    if (size != capacity)
    {
        arraylist[size] = new_element;
        size++;
        return true;
    }
    else
        return false;
}

void AlphabetArrayList::display()
{
    // display is designed to show entire array including empty elements
    for (int i = 0; i < capacity; i++)
        cout << arraylist[i] << " ";
    cout << "\n";
}

void AlphabetArrayList::getListValuesFromUser()
{
    cout << "Enter up to " << capacity << " characters to populate your list. Enter 0 to stop entering.\n";
    char element;
    for (int i = 0; i < 10; i++)
    {
        cout << "Enter " << i + 1 << ": ";
        cin >> element;
        if (element != '0')
            insert(element);
        else
            break;
    }
    cout << "Confirmation of list values entered: ";
    display();
}

int AlphabetArrayList::countVowels()
{
    for (int i = 0; i < 10; i++)
    {
        if (arraylist[i] == 'a' || arraylist[i] == 'E')
        {
            // cout << "Vowel 'a' found at Index " << i << endl;
            vowelCount++;
        }
        else if (arraylist[i] == 'e' || arraylist[i] == 'E')
        {
            // cout << "Vowel 'E' found at Index " << i << endl;
            vowelCount++;
        }
        else if (arraylist[i] == 'i' || arraylist[i] == 'I')
        {
            // cout << "Vowel 'I' found at Index " << i << endl;
            vowelCount++;
        }
        else if (arraylist[i] == 'o' || arraylist[i] == 'O')
        {
            // cout << "Vowel 'O' found at Index " << i << endl;
            vowelCount++;
        }
        else if (arraylist[i] == 'u' || arraylist[i] == 'U')
        {
            // cout << "Vowel 'U' found at Index " << i << endl;
            vowelCount++;
        }
        else
        {
            // cout << "No Vowel Found" << endl;
        }
    }

    return vowelCount;
}

int AlphabetArrayList::findLastIndex(char input)
{
    for (int i = 9; i >= 0; i--)
    {
        if (arraylist[i] == input)
        {
            return i;
        }
    }
    return -1;
}

void AlphabetArrayList::swapElements(int index1, int index2)
{
    char temp = arraylist[index1];
    arraylist[index1] = arraylist[index2];
    arraylist[index2] = temp;
}

void AlphabetArrayList::mergeFirstN(const AlphabetArrayList &incoming_list, int N)
{
    for (int i = 0; i < N; i++)
    {
        arraylist[size] = incoming_list.arraylist[i];
        size++;
    }
    cout << "Merged list: ";
    display();
}

// BONUS MARKS
void AlphabetArrayList::sortedMerge(const AlphabetArrayList &incoming_list1, const AlphabetArrayList &incoming_list2)
{
}

int main()
{
    AlphabetArrayList list1, list2;

    cout << "Getting list1: \n";
    list1.getListValuesFromUser();
    cout << "\nGetting list2: \n";
    list2.getListValuesFromUser();

    cout << "list 1 has " << list1.countVowels() << " vowels" << endl;
    cout << "list 2 has " << list2.countVowels() << " vowels" << endl;

    char letter_index;
    cout << "\nEnter a letter, and we will find it's latest occurrence in the array: ";
    cin >> letter_index;

    if (list1.findLastIndex(letter_index) < 0)
        cout << letter_index << " does not exist in list1";
    else
        cout << letter_index << " occurs at " << list1.findLastIndex(letter_index) << " index in list1\n";

    if (list2.findLastIndex(letter_index) < 0)
        cout << letter_index << " does not exist in list2";
    else
        cout << letter_index << " occurs at " << list2.findLastIndex(letter_index) << " index in list2\n";

    cout << "\n";

    int index1, index2;
    cout << "Enter 1st index for swapping: ";
    cin >> index1;

    cout << "Enter 2nd index for swapping: ";
    cin >> index2;

    cout << "\nList 1 before swapping:";
    list1.display();
    list1.swapElements(index1, index2);
    cout << "\nList 1 after swapping:";
    list1.display();

    cout << "\nList 2 before swapping:";
    list2.display();
    list2.swapElements(index1, index2);
    cout << "\nList 2 after swapping:";
    list2.display();

    int N;
    cout << "How many values of list2 need to be merged in list1? Enter value: ";
    cin >> N;
    cout << "\nAfter merging " << N << " values from list2 into list1 : \n";
    list1.mergeFirstN(list2, N);
    cout << "\nList1 after merge: ";
    list1.display();
    cout << "List2 after merge (unchanged): ";
    list2.display();

    // BONUS

    AlphabetArrayList list3, list4;
    cout << "\nGetting list3: \n";
    list3.getListValuesFromUser();
    cout << "\nGetting list4: \n";
    list4.getListValuesFromUser();

    // YOUR WORKING REQUIRED HERE ON LIST3 and LIST4

    cout << "Merging sorted lists:" << endl;
    AlphabetArrayList list5(list3.size + list4.size);
    list5.sortedMerge(list3, list4);
    list5.display();
}

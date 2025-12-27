#include <iostream>
#include <string>
using namespace std;

class dayType {
private:
    string currentDay; // Store the current day
    string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"}; // Array of days

    // Helper method to find the index of the current day
    int getDayIndex() const {
        for (int i = 0; i < 7; ++i) {
            if (days[i] == currentDay) {
                return i;
            }
        }
        return -1; // Return -1 if the day is invalid (shouldn't happen with proper validation)
    }

public:
    // Constructor: Initialize the day to a default value
    dayType(string day = "Sun") {
        setDay(day);
    }

    // Set the current day
    void setDay(const string& day) {
        for (int i = 0; i < 7; ++i) {
            if (days[i] == day) {
                currentDay = day;
                return;
            }
        }
        cout << "Invalid day entered. Defaulting to Sunday.\n";
        currentDay = "Sun"; // Default to Sunday if input is invalid
    }

    // Get the current day
    string getDay() const {
        return currentDay;
    }

    // Print the current day
    void printDay() const {
        cout << "Current day: " << currentDay << endl;
    }

    // Return the next day
    string nextDay() const {
        int index = getDayIndex();
        return days[(index + 1) % 7];
    }

    // Return the previous day
    string previousDay() const {
        int index = getDayIndex();
        return days[(index + 6) % 7]; // Add 6 instead of subtracting 1 to avoid negative index
    }

    // Add a number of days to the current day and return the resulting day
    string addDays(int n) const {
        int index = getDayIndex();
        return days[(index + n) % 7];
    }
};

int main() {
    dayType myDay("Tue"); // Create an object with the initial day as Tuesday

    myDay.printDay();

    cout << "Next day: " << myDay.nextDay() << endl;
    cout << "Previous day: " << myDay.previousDay() << endl;

    cout << "Day after 4 days: " << myDay.addDays(4) << endl;
    cout << "Day after 13 days: " << myDay.addDays(13) << endl;

    myDay.setDay("Fri");
    myDay.printDay();

    return 0;
}
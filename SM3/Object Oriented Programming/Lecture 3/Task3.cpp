#include <iostream>
using namespace std;
class ClockType {
public:
    // Constructor: This is where we initialize member variables
    ClockType(int hours, int minutes, int seconds) {
        hr = hours;     // Initializing hr
        min = minutes;  // Initializing min
        sec = seconds;  // Initializing sec
    }

    // Function to display the time
    void printTime() const {
        cout << hr << ":" << min << ":" << sec << endl;
    }

private:
    int hr;  // Member variable for hours
    int min; // Member variable for minutes
    int sec; // Member variable for seconds
};

int main() {
    // Creating an object (instance) of clockType
    ClockType myClock(10, 30, 45); // Setting the time to 10:30:45
    myClock.printTime(); // Display the time
    return 0;
}

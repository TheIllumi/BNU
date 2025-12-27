#include <iostream>
using namespace std;
// Function to input scores from 5 judges with validation
void inputScores(int scores[], int numOfJudges) {
    for (int i = 0; i < numOfJudges; i++) {
        do {
            cout << "Enter score from judge " << i + 1 << " (0 to 10): ";
            cin >> scores[i];
            if (scores[i] < 0 || scores[i] > 10) {
                cout << "Invalid score! Please enter a value between 0 and 10." << endl;
            }
        } while (scores[i] < 0 || scores[i] > 10);  // Keep asking until the input is valid
    }
}
// Function to remove the lowest score from the array
void removeLowestScore(int scores[], int numOfJudges) {
    // Find the minimum score and set it to 0 to "drop" it
    int minIndex = 0;
    for (int i = 1; i < numOfJudges; i++) {
        if (scores[i] < scores[minIndex]) {
            minIndex = i;
        }
    }
    scores[minIndex] = 0; // Drop the lowest score
}

// Function to calculate the final score
double calculateFinalScore(int scores[], int numOfJudges) {
    int sum = 0;
    for (int i = 0; i < numOfJudges; i++) {
        sum += scores[i];
    }
    return sum / 4.0;  // Calculate average of 4 remaining scores
}
int main() {
    const int numOfJudges = 5;
    int scores[numOfJudges];
    inputScores(scores, numOfJudges);
    removeLowestScore(scores, numOfJudges);
    double finalScore = calculateFinalScore(scores, numOfJudges);
    cout << "The final score is: " << finalScore << endl;
    return 0;
}

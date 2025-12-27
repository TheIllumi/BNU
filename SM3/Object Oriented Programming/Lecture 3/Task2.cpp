#include <iostream>
using namespace std;
class Performer {
private:
    int scores[5];   // Array to store scores from 5 judges
    double finalScore;
public:
    // Method to input scores from 5 judges with validation
    void inputScores() {
        for (int i = 0; i < 5; i++) {
            int score;
            do {
                cout << "Enter score from judge " << i + 1 << " (0-10): ";
                cin >> score;
                if (score < 0 || score > 10) {
                    cout << "Invalid score! Please enter a score between 0 and 10." << endl;
                }
            } while (score < 0 || score > 10);  // Repeat until a valid score is entered

            scores[i] = score; // Store the valid score
        }
    }
    // Method to remove the lowest score
    void removeLowestScore() {
        int minIndex = 0;
        for (int i = 1; i < 5; i++) {
            if (scores[i] < scores[minIndex]) {
                minIndex = i;
            }
        }
        scores[minIndex] = 0;  // Drop the lowest score
    }

    // Method to calculate the final score
    void calculateFinalScore() {
        int sum = 0;
        for (int i = 0; i < 5; i++) {
            sum += scores[i];  // Sum all scores except the dropped (0) score
        }
        finalScore = sum / 4.0;  // Calculate average of 4 remaining scores
    }

    // Method to display the final score
    void displayFinalScore() {
        cout << "The final score is: " << finalScore << endl;
    }
};
int main() {
    Performer performer;
    performer.inputScores();
    performer.removeLowestScore();
    performer.calculateFinalScore();
    performer.displayFinalScore();
    return 0;
}

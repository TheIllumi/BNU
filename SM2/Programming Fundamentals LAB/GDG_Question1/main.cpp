#include <iostream>
using namespace std;

int main() {
    int n;

    cout << "Enter the number of elements: ";
    cin >> n;

    int nums[n];
    cout << "Enter " << n << " elements:\n";

    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
    }

    int uniqueNumber = -1;

    for (int i = 0; i < n; ++i) {
        int count = 0;

        for (int j = 0; j < n; ++j) {
            if (nums[i] == nums[j]) {
                count++;
            }
        }

        if (count == 1) {
            uniqueNumber = nums[i];
            break;
        }
    }

    cout << "The unique element is: " << uniqueNumber << endl;

    return 0;
}

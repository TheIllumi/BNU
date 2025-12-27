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

    int result = 0;
    for (int i = 0; i < n; ++i) {
        result ^= nums[i];
    }

    cout << "The unique element is: " << result << endl;

    return 0;
}

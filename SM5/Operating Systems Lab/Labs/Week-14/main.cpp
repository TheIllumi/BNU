#include <iostream>
using namespace std;

int main() {
    int memorySize, segments;

    cout << "Enter total available memory (KB): ";
    cin >> memorySize;

    cout << "Enter number of segments: ";
    cin >> segments;

    int size[50];
    int base[50], limit[50];

    int freeMemoryStart = 0;
    bool fault = false;

    // Read segment sizes
    for (int i = 0; i < segments; i++) {
        cout << "Enter memory required for segment " << i + 1 << " (KB): ";
        cin >> size[i];
    }

    cout << "\nMemory Allocation Details:\n";

    // Allocation logic
    for (int i = 0; i < segments; i++) {

        if (freeMemoryStart + size[i] <= memorySize) {
            base[i] = freeMemoryStart;
            limit[i] = freeMemoryStart + size[i] - 1;

            cout << "Segment " << i + 1
                << " allocated from " << base[i]
                << " KB to " << limit[i] << " KB\n";

            freeMemoryStart += size[i];
        }
        else {
            cout << "Segment " << i + 1
                << " allocation failed -> SEGMENT FAULT\n";
            fault = true;
            break;
        }
    }

    cout << "\nRemaining Free Memory: "
        << memorySize - freeMemoryStart << " KB\n";

    if (!fault)
        cout << "Segmentation completed successfully.\n";
    else
        cout << "Process terminated due to Segment Fault.\n";

    return 0;
}

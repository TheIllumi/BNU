#include <iostream>
using namespace std;

int main() {
    int n, quantum;
    cout << "Enter number of processes: ";
    cin >> n;

    int arrival[20], burst[20], remaining[20];
    int waiting[20], turnaround[20];
    string name[20];

    // Input processes
    for (int i = 0; i < n; i++) {
        cout << "Enter Process Name: ";
        cin >> name[i];
        cout << "Arrival Time: ";
        cin >> arrival[i];
        cout << "Burst Time: ";
        cin >> burst[i];
        remaining[i] = burst[i];  // initially remaining time = burst
    }

    cout << "Enter Time Quantum: ";
    cin >> quantum;

    int time = 0;      // current time
    int completed = 0; // how many processes finished

    cout << "\nGantt Chart:\n";

    // Round Robin Loop
    while (completed < n) {
        bool doneSomething = false;

        for (int i = 0; i < n; i++) {
            // Run only if process has arrived and has remaining time
            if (arrival[i] <= time && remaining[i] > 0) {

                doneSomething = true;

                cout << "| " << name[i] << " ";

                if (remaining[i] > quantum) {
                    time += quantum;
                    remaining[i] -= quantum;
                }
                else {
                    time += remaining[i];
                    remaining[i] = 0;

                    // process finished → calculate WT & TAT later
                    turnaround[i] = time - arrival[i];
                    waiting[i] = turnaround[i] - burst[i];

                    completed++;
                }
            }
        }

        // If no process arrived yet → move time forward
        if (!doneSomething)
            time++;
    }

    cout << "|\n";

    // Display table
    cout << "\nProcess\tArrival\tBurst\tWaiting\tTurnaround\n";
    float totalWT = 0, totalTAT = 0;

    for (int i = 0; i < n; i++) {
        cout << name[i] << "\t" << arrival[i] << "\t"
            << burst[i] << "\t" << waiting[i] << "\t"
            << turnaround[i] << "\n";

        totalWT += waiting[i];
        totalTAT += turnaround[i];
    }

    cout << "\nAverage Waiting Time = " << totalWT / n;
    cout << "\nAverage Turnaround Time = " << totalTAT / n;

    return 0;
}

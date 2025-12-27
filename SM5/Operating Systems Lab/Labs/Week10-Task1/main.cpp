#include <iostream>
#include <string>
using namespace std;

struct Process {
    string pid;
    int at;   // Arrival Time
    int bt;   // Burst Time
    int ct;   // Completion Time
    int tat;  // Turnaround Time
    int wt;   // Waiting Time
    bool done;
};

int main() {
    int n;
    cout << "Enter number of processes in the ready queue : ";
    cin >> n;

    Process p[20];   // assuming max 20 processes
    string gantt[20]; // for Gantt chart order

    cout << "Process  Arrival Time  Burst Time\n";
    for (int i = 0; i < n; i++) {
        cin >> p[i].pid >> p[i].at >> p[i].bt;
        p[i].ct = p[i].tat = p[i].wt = 0;
        p[i].done = false;
    }

    int time = 0, completed = 0, ganttIndex = 0;

    // Find earliest arrival to start from
    int earliest_at = p[0].at;
    for (int i = 1; i < n; i++) {
        if (p[i].at < earliest_at)
            earliest_at = p[i].at;
    }
    time = earliest_at;

    while (completed < n) {
        int idx = -1;
        int min_bt = 99999;

        // Find the shortest available process
        for (int i = 0; i < n; i++) {
            if (!p[i].done && p[i].at <= time) {
                if (p[i].bt < min_bt) {
                    min_bt = p[i].bt;
                    idx = i;
                }
            }
        }

        // If no process has arrived yet
        if (idx == -1) {
            time++;
            continue;
        }

        // Execute this process
        time += p[idx].bt;
        p[idx].ct = time;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;
        p[idx].done = true;
        gantt[ganttIndex++] = p[idx].pid;
        completed++;
    }

    // Calculate and display
    double avg_wt = 0, avg_tat = 0;

    cout << "\nProcess  Arrival Time  Burst Time  Waiting Time  Turnaround Time\n";
    for (int i = 0; i < n; i++) {
        cout << p[i].pid << "\t" << p[i].at << "\t\t"
            << p[i].bt << "\t\t" << p[i].wt << "\t\t" << p[i].tat << "\n";
        avg_wt += p[i].wt;
        avg_tat += p[i].tat;
    }

    cout << "\nAVG waiting time = " << avg_wt / n << " sec\n";
    cout << "AVG Turnaround time = " << avg_tat / n << " sec\n";

    // Print Gantt chart
    cout << "\nGantt chart:\n| ";
    for (int i = 0; i < ganttIndex; i++) {
        cout << gantt[i] << " | ";
    }
    cout << "\n";

    return 0;
}
// ==================== MyDailyStack ====================
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <sstream>
#include <vector>
#include <climits>
using namespace std;

// ------------------ Action Class ------------------
class Action {
private:
    string type;
    string timeStamp;
public:
    void setData(const string& t, const string& ts) {
        type = t;
        timeStamp = ts;
    }

    void print() const {
        cout << type << "," << timeStamp;
    }

    string toString() const {
        return type + "," + timeStamp;
    }

    const string& getType() const {
        return type;
    }
};

// ------------------ Node for Linked List ------------------
struct Node {
    Action action;
    Node* next;
};

// ------------------ Stack Class ------------------
class Stack {
private:
    Node* top;
    int count;
public:
    Stack() {
        top = nullptr;
        count = 0;
    }

    void push(Action action) {
        Node* newNode = new Node;
        newNode->action = action;
        newNode->next = top;
        top = newNode;
        count++;
    }

    Action pop() {
        if (isEmpty()) {
            cout << "Stack underflow" << endl;
            exit(1);
        }
        Node* temp = top;
        Action a = temp->action;
        top = top->next;
        delete temp;
        count--;
        return a;
    }

    Action peek() {
        if (isEmpty()) {
            cout << "Stack is empty" << endl;
            exit(1);
        }
        return top->action;
    }

    bool isEmpty() {
        return top == nullptr;
    }

    void clear() {
        while (!isEmpty()) {
            pop();
        }
    }

    int size() {
        return count;
    }

    void print(const char* name) {
        cout << name << " (top -> bottom): [";
        Node* temp = top;
        while (temp) {
            temp->action.print();
            if (temp->next) cout << ", ";
            temp = temp->next;
        }
        cout << "]" << endl;
    }

    void getLastNActions(Action* actions, int n) const {
        Node* temp = top;
        int index = 0;
        while (temp != nullptr && index < n) {
            actions[n - 1 - index] = temp->action; // this line prints in reverse
            temp = temp->next;
            index++;
        }
    }

    ~Stack() {
        clear();
    }
};

// ------------------ Helpers ------------------
void splitLine(char* line, char* type, char* timeStamp) {
    int i = 0, j = 0;
    while (line[i] != ',' && line[i] != '\0') {
        type[j++] = line[i++];
    }
    type[j] = '\0';
    i++;
    while (line[i] == ' ') i++;
    j = 0;
    while (line[i] != '\0' && line[i] != '\n') {
        timeStamp[j++] = line[i++];
    }
    timeStamp[j] = '\0';
}

void readActionsFromFile(Action actions[][12], int days) {
    ifstream file("full_actions.txt");
    if (!file) {
        cout << "Error opening file." << endl;
        exit(1);
    }
    char line[50], type[30], timeStamp[15];
    for (int day = 0; day < days; day++) {
        for (int hour = 0; hour < 12; hour++) {
            if (file.getline(line, 50)) {
                splitLine(line, type, timeStamp);
                actions[day][hour].setData(type, timeStamp);
            }
            else {
                actions[day][hour].setData("Default", "9:00AM");
            }
        }
    }
    file.close();
}

void extractLast7Days(Stack& undoStack, Action last7Days[7][12]) {
    Action allActions[84];
    undoStack.getLastNActions(allActions, 84);
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 12; j++) {
            last7Days[i][j] = allActions[i * 12 + j];
        }
    }
}

string generateSignaturePattern(Action actions[12]) {
    stringstream pattern;
    for (int i = 0; i < 12; i++) {
        pattern << actions[i].toString();
        if (i < 11) pattern << "->";
    }
    return pattern.str();
}

int calculateSimilarityScore(const string& currentWeek, const string& pastWeek) {
    int score = 0;
    for (size_t i = 0; i < currentWeek.size(); i++) {
        if (i < pastWeek.size()) {
            if (currentWeek[i] == pastWeek[i]) score += 2;
            else if (pastWeek.find(currentWeek[i]) != string::npos) score += 1;
            else score -= 1;
        }
        else {
            score -= 1;
        }
    }
    return score;
}

string predictNextAction(Action last7Days[7][12], const vector<string>& pastPatterns) {
    string currentWeekPattern = generateSignaturePattern(last7Days[6]);
    int maxScore = INT_MIN;
    int mostSimilarWeekIndex = -1;
    for (size_t i = 0; i < pastPatterns.size(); i++) {
        int score = calculateSimilarityScore(currentWeekPattern, pastPatterns[i]);
        if (score > maxScore) {
            maxScore = score;
            mostSimilarWeekIndex = i;
        }
    }
    if (mostSimilarWeekIndex != -1) {
        return last7Days[mostSimilarWeekIndex][0].getType();
    }
    return "Unknown";
}

// ------------------ Undo/Redo Logic ------------------
void performAction(Stack& undoStack, Stack& redoStack, Action a) {
    undoStack.push(a);
    redoStack.clear();
    cout << "Performed: "; a.print(); cout << endl;
}

void undo(Stack& undoStack, Stack& redoStack) {
    if (undoStack.isEmpty()) {
        cout << "Nothing to undo." << endl;
        return;
    }
    Action a = undoStack.pop();
    redoStack.push(a);
    cout << "Undo: "; a.print(); cout << endl;
}

void redo(Stack& undoStack, Stack& redoStack) {
    if (redoStack.isEmpty()) {
        cout << "Nothing to redo." << endl;
        return;
    }
    Action a = redoStack.pop();
    undoStack.push(a);
    cout << "Redo: "; a.print(); cout << endl;
}

void simulateRandomOperations(Stack& undoStack, Stack& redoStack, Action actions[][12], int days) {
    srand(time(0));
    const int totalOperations = 50;
    int performedDays = 0;
    for (int i = 0; i < totalOperations; i++) {
        int operation = rand() % 3;
        if (operation == 0 && performedDays < days) {
            cout << "\n=== Performing day " << performedDays + 1 << " actions ===" << endl;
            for (int hour = 0; hour < 12; hour++) {
                performAction(undoStack, redoStack, actions[performedDays][hour]);
            }
            performedDays++;
        }
        else if (operation == 1) {
            cout << "\n=== Undo operation ===" << endl;
            undo(undoStack, redoStack);
        }
        else {
            cout << "\n=== Redo operation ===" << endl;
            redo(undoStack, redoStack);
        }
        undoStack.print("Undo Stack");
        redoStack.print("Redo Stack");
        cout << "------------------------" << endl;
    }
}

void testCase1(Stack& undoStack, Stack& redoStack) {
    undoStack.clear();
    redoStack.clear();

	cout << "\n=== Test Case 1 ===" << endl;
    Action a;
    a.setData("Study", "9AM");
    performAction(undoStack, redoStack, a);
    a.setData("Play", "10AM");
    performAction(undoStack, redoStack, a);
    a.setData("Procrastinate", "11AM");
    performAction(undoStack, redoStack, a);

    undo(undoStack, redoStack);
    undo(undoStack, redoStack);

    redo(undoStack, redoStack);
    redo(undoStack, redoStack);

    undoStack.print("Undo Stack");
    redoStack.print("Redo Stack");
}

void testCase2(Stack& undoStack, Stack& redoStack) {
    undoStack.clear();
    redoStack.clear();

    cout << "\n=== Test Case 2 ===" << endl;
    Action a;
    a.setData("Study", "9AM");
    performAction(undoStack, redoStack, a);
    a.setData("Play", "10AM");
    performAction(undoStack, redoStack, a);

    undo(undoStack, redoStack);

    a.setData("Procrastinate", "11AM");
    performAction(undoStack, redoStack, a);

    undoStack.print("Undo Stack");
    redoStack.print("Redo Stack");
}

void testCase3(Stack& undoStack, Stack& redoStack) {
    undoStack.clear();
    redoStack.clear();

	cout << "\n=== Test Case 3 ===" << endl;
    Action a;
    a.setData("Study", "9AM");
    performAction(undoStack, redoStack, a);
    a.setData("Play", "10AM");
    performAction(undoStack, redoStack, a);
    a.setData("Procrastinate", "11AM");
    performAction(undoStack, redoStack, a);

    undo(undoStack, redoStack);
    undo(undoStack, redoStack);
    undo(undoStack, redoStack);

    a.setData("New Action", "12PM");
    performAction(undoStack, redoStack, a);

    undoStack.print("Undo Stack");
    redoStack.print("Redo Stack");
}

void testCase4(Stack& undoStack, Stack& redoStack) {
    undoStack.clear();
    redoStack.clear();

	cout << "\n=== Test Case 4 ===" << endl;
    undo(undoStack, redoStack);

    undoStack.print("Undo Stack");
    redoStack.print("Redo Stack");
}

void testCase5(Stack& undoStack, Stack& redoStack) {
    undoStack.clear();
    redoStack.clear();

	cout << "\n=== Test Case 5 ===" << endl;
    redo(undoStack, redoStack);

    undoStack.print("Undo Stack");
    redoStack.print("Redo Stack");
}

void testCase6(Stack& undoStack, Stack& redoStack) {
    undoStack.clear();
    redoStack.clear();

	cout << "\n=== Test Case 6 ===" << endl;
    Action a;
    a.setData("Study", "9AM");
    performAction(undoStack, redoStack, a);
    a.setData("Play", "10AM");
    performAction(undoStack, redoStack, a);
    a.setData("Procrastinate", "11AM");
    performAction(undoStack, redoStack, a);
    a.setData("Study", "12PM");
    performAction(undoStack, redoStack, a);

    undo(undoStack, redoStack);
    undo(undoStack, redoStack);

    redo(undoStack, redoStack);

    undoStack.print("Undo Stack");
    redoStack.print("Redo Stack");
}

void testCase7(Stack& undoStack, Stack& redoStack) {
    undoStack.clear();
    redoStack.clear();

	cout << "\n=== Test Case 7 ===" << endl;
    Action a;
    a.setData("Study", "9AM");
    performAction(undoStack, redoStack, a);
    a.setData("Play", "10AM");
    performAction(undoStack, redoStack, a);
    a.setData("Procrastinate", "11AM");
    performAction(undoStack, redoStack, a);

    undo(undoStack, redoStack);
    undo(undoStack, redoStack);
    undo(undoStack, redoStack);

    undoStack.print("Undo Stack");
    redoStack.print("Redo Stack");
}

void testCase8(Stack& undoStack, Stack& redoStack) {
    undoStack.clear();
    redoStack.clear();

	cout << "\n=== Test Case 8 ===" << endl;
    Action a;
    a.setData("Study", "9AM");
    performAction(undoStack, redoStack, a);
    a.setData("Play", "10AM");
    performAction(undoStack, redoStack, a);
    a.setData("Procrastinate", "11AM");
    performAction(undoStack, redoStack, a);

    undo(undoStack, redoStack);
    undo(undoStack, redoStack);
    undo(undoStack, redoStack);

    redo(undoStack, redoStack);
    redo(undoStack, redoStack);
    redo(undoStack, redoStack);

    undoStack.print("Undo Stack");
    redoStack.print("Redo Stack");
}

void testCase9(Stack& undoStack, Stack& redoStack) {
    undoStack.clear();
    redoStack.clear();

	cout << "\n=== Test Case 9 ===" << endl;
    Action a;
    a.setData("Study", "9AM");
    performAction(undoStack, redoStack, a);
    a.setData("Play", "10AM");
    performAction(undoStack, redoStack, a);
    a.setData("Procrastinate", "11AM");
    performAction(undoStack, redoStack, a);

    undo(undoStack, redoStack);
    undo(undoStack, redoStack);
    undo(undoStack, redoStack);

    a.setData("New Action", "12PM");
    performAction(undoStack, redoStack, a);

    undoStack.print("Undo Stack");
    redoStack.print("Redo Stack");
}

void testCase10(Stack& undoStack, Stack& redoStack) {
    undoStack.clear();
    redoStack.clear();

	cout << "\n=== Test Case 10 ===" << endl;
    Action a;
    for (int i = 1; i <= 50; i++) {
        a.setData("Action" + to_string(i), to_string(i) + "AM");
        performAction(undoStack, redoStack, a);
    }

    for (int i = 0; i < 25; i++) {
        undo(undoStack, redoStack);
    }

    for (int i = 0; i < 25; i++) {
        redo(undoStack, redoStack);
    }

    for (int i = 0; i < 10; i++) {
        undo(undoStack, redoStack);
    }

    undoStack.print("Undo Stack");
    redoStack.print("Redo Stack");
}

int main() {
    const int days = 90;
    const int actionsPerDay = 12;
    Action allActions[days][actionsPerDay];
    readActionsFromFile(allActions, days);
    Stack undoStack, redoStack;
    simulateRandomOperations(undoStack, redoStack, allActions, days);

    Action last7Days[7][12];
    extractLast7Days(undoStack, last7Days);

    vector<string> pastPatterns;
    for (int i = 0; i <= days - 7; i += 7) {
        pastPatterns.push_back(generateSignaturePattern(allActions[i]));
    }

    cout << "\n=== Simulation Complete ===" << endl;
    cout << "Total days performed: " << undoStack.size() / 12 << endl;
    cout << "Final Undo Stack size: " << undoStack.size() << endl;
    cout << "Final Redo Stack size: " << redoStack.size() << endl;

    string prediction = predictNextAction(last7Days, pastPatterns);
    cout << "\nPredicted action for tomorrow (9AM-10AM): " << prediction << endl;

    testCase1(undoStack, redoStack);
    testCase2(undoStack, redoStack);
    testCase3(undoStack, redoStack);
    testCase4(undoStack, redoStack);
    testCase5(undoStack, redoStack);
    testCase6(undoStack, redoStack);
    testCase7(undoStack, redoStack);
    testCase8(undoStack, redoStack);
    testCase9(undoStack, redoStack);
    testCase10(undoStack, redoStack);
    return 0;
}
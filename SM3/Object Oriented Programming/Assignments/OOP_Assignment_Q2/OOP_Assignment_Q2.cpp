#include <iostream>
#include <string>
using namespace std;

class Student {
private:
    int id;
    string name;
    float math, science, urdu, english;
    float totalMarks;
    float percentage;

    void process() {
        totalMarks = math + science + urdu + english;
        percentage = (totalMarks / 400) * 100;
    }

public:
    Student() {
        id = 0;
        name = "";
        math = science = urdu = english = 0;
        totalMarks = 0;
        percentage = 0;
    }

    Student(int id, string name, float math, float science, float urdu, float english) {
        setId(id);
        setName(name);
        setMath(math);
        setScience(science);
        setUrdu(urdu);
        setEnglish(english);
        process();
    }

    // SETTERS ----------
    void setId(int newId) {
        if (newId >= 0) {
            id = newId;
        } else {
            id = 0;
        }
    }

    void setName(string newName) {
        name = newName;
    }

    void setMath(float newMath) {
        if (newMath >= 0 && newMath <= 100) {
            math = newMath;
        } else {
            math = 0;
        }
    }

    void setScience(float newScience) {
        if (newScience >= 0 && newScience <= 100) {
            science = newScience;
        } else {
            science = 0;
        }
    }

    void setUrdu(float newUrdu) {
        if (newUrdu >= 0 && newUrdu <= 100) {
            urdu = newUrdu;
        } else {
            urdu = 0;
        }
    }

    void setEnglish(float newEnglish) {
        if (newEnglish >= 0 && newEnglish <= 100) {
            english = newEnglish;
        } else {
            english = 0;
        }
    }

    // GETTERS ---------
    float getMath() {
        return math;
    }

    float getScience() {
        return science;
    }

    string getName() {
        return name;
    }

    int getId() {
        return id;
    }

    void display() {
        process();
        cout << "----------------------------------------" << endl;
        cout << "Student[ Id : " << id
             << ", Name = " << name
             << ", Math = " << math
             << ", Science = " << science
             << ", Urdu = " << urdu
             << ", English = " << english
             << ", Total Marks = " << totalMarks
             << ", Percentage = " << percentage
             << "% ]" << endl;
        cout << "----------------------------------------" << endl;
    }
};

int main() {
    const int numStudents = 3;
    Student students[numStudents];



    for (int i = 0; i < numStudents; ++i) {
        int id;
        string name;
        float math, science, urdu, english;

        cout << "Enter details for student " << i + 1 << ":\n";
        cout << "ID: ";
        cin >> id;
        while (id < 0)
        {
            cout << "ID must be non-negative. Please enter a valid ID.\n";
            cout << "ID: ";
            cin >> id;
        }

        cout << "Name: ";
        cin >> name;

        cout << "Math Marks: ";
        cin >> math;
        while (math < 0 || math > 100) {
            cout << "Math marks must be between 0 and 100. Please enter valid marks:\n";
            cout << "Math Marks: ";
            cin >> math;
        }

        cout << "Science Marks: ";
        cin >> science;
        while (science < 0 || science > 100) {
            cout << "Science marks must be between 0 and 100. Please enter valid marks:\n";
            cout << "Science Marks: ";
            cin >> science;
        }

        cout << "Urdu Marks: ";
        cin >> urdu;
        while (urdu < 0 || urdu > 100) {
            cout << "Urdu marks must be between 0 and 100. Please enter valid marks:\n";
            cout << "Urdu Marks: ";
            cin >> urdu;
        }

        cout << "English Marks: ";
        cin >> english;
        while (english < 0 || english > 100) {
            cout << "English marks must be between 0 and 100. Please enter valid marks:\n";
            cout << "English Marks: ";
            cin >> english;
        }

        students[i] = Student(id, name, math, science, urdu, english);
    }

    cout << "\nAll students' details:\n";
    for (int i = 0; i < numStudents; ++i) {
        students[i].display();
    }

    return 0;
}

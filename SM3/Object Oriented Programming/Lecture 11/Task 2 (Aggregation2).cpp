#include <iostream>
using namespace std;

class Teacher {
public:
    string name;

    Teacher(string name) {
        this->name = name;
    }

    void teach() {
        cout << name << " is teaching." << endl;
    }
};

class School {
public:
    Teacher* teacher;  // Pointer to a Teacher object

    void assignTeacher(Teacher* t) {
        teacher = t;  // Assign the teacher pointer to the given teacher
    }

    void showTeacher() {
        if (teacher != nullptr) {
            cout << "The teacher at this school is: " << teacher->name << endl;
        }
    }
};

int main() {
    Teacher t1("Mr. Smith");
    School school;

    school.assignTeacher(&t1);  // Assign teacher to the school
    school.showTeacher();  // Show teacher in the school
    t1.teach();  // Call teach method

    return 0;
}

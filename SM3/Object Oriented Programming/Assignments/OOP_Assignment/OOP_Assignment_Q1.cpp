#include <iostream>
#include <string>
using namespace std;

class Student {
private:
    int id;
    string name;
    float math, science, urdu, english;

public:
    Student(int id, string name, float math, float science, float urdu, float english) {
        setId(id);
        setName(name);
        setMath(math);
        setScience(science);
        setUrdu(urdu);
        setEnglish(english);
    }

    // SETTERS ----------
    void setId(int id) {
        if (id < 0) {
            this->id = 0;
        } else {
            this->id = id;
        }
    }

    void setName(string name) {
        this->name = name;
    }

    void setMath(float math) {
        if (math >= 0 && math <= 100) {
            this->math = math;
        } else {
            this->math = 0;
        }
    }

    void setScience(float science) {
        if (science >= 0 && science <= 100) {
            this->science = science;
        } else {
            this->science = 0;
        }
    }

    void setUrdu(float urdu) {
        if (urdu >= 0 && urdu <= 100) {
            this->urdu = urdu;
        } else {
            this->urdu = 0;
        }
    }

    void setEnglish(float english) {
        if (english >= 0 && english <= 100) {
            this->english = english;
        } else {
            this->english = 0;
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
        cout << "Student[ Id : " << id
             << " , Name = " << name
             << " , Math = " << math
             << " , Science = " << science
             << " , Urdu = " << urdu
             << " , English = " << english
             << " ]" << endl;
    }
};

int main() {
    Student student(47, "Happy", 50, 25, 99, 97);

    student.display();

    cout << "Student's Name: " << student.getName() << endl;

    return 0;
}

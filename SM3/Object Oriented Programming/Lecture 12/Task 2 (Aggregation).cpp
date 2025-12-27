#include <iostream>
#include <vector>
using namespace std;

class Point {
private:
    int xvalue;
    int yvalue;

public:
    Point(int x, int y) {
        xvalue = x;
        yvalue = y;
    }

    void print() const {
        cout << "(" << xvalue << ", " << yvalue << ")";
    }

    
    int getX() { return xvalue; }
    int getY() { return yvalue; }
};

class Line {
private:
    string color;
    string style;
    vector<Point*> points; 

public:
    Line(string color, string style) {
        this->color = color;
        this->style = style;
    }

    void addPoint(Point* point) {
        points.push_back(point);
    }

    void removePoint(Point* point) {
        for (auto it = points.begin(); it != points.end(); ++it) {
            if (*it == point) {
                points.erase(it);
                break;
            }
        }
    }

    void printPoints() const {
        cout << "Line color: " << color << ", style: " << style << endl;
        cout << "Points on the line: ";
        for (const auto& point : points) {
            point->print();
            cout << " ";
        }
        cout << endl;
    }
};

int main() {
    
    Point p1(2, 3);
    Point p2(4, 5);
    Point p3(6, 7);

    Line line("Red", "Dashed");
    
    line.addPoint(&p1);
    line.addPoint(&p2);
    line.addPoint(&p3);

   
    line.printPoints();

   
    line.removePoint(&p2);
    cout << "\nAfter removing a point:\n";
    line.printPoints();

    return 0;
}

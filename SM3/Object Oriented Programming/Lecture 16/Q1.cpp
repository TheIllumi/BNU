#include <iostream>
using namespace std;

class Car {
public:
    int speed;
    void showSpeed() { 
        cout << "Car speed: " << speed << " km/h" << endl; }
};

class SportsCar : public Car {
private:
    int speed;
public:
    void setSpeed(int s) 
    { 
        speed = s; 
        
    }
    void showSpeed() { 
        cout << "SportsCar speed: " << speed << " km/h" << endl; 
        
    }
};

int main() {
    Car car;
    car.speed = 100;
    car.showSpeed();

    SportsCar sportsCar;
    sportsCar.setSpeed(200);
    sportsCar.showSpeed();

    return 0;
}

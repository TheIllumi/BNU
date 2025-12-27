#include <iostream>
using namespace std;

class Vehicle {
protected:
    int fuelLevel; 
};


class Car : public Vehicle {
public:
    void setFuelLevel(int fuel) {
        fuelLevel = fuel; 
    }

    void displayFuelLevel() {
        cout << "Car fuel level: " << fuelLevel << " liters" << endl;
    }
};

int main() {
    Vehicle vehicle;
    Car car;

    car.setFuelLevel(30);   
    car.displayFuelLevel(); 

    // vehicle.fuelLevel = 50; // Error: Cannot access protected member from outside

    return 0;
}

#include <iostream>
using namespace std;

// objects being created by each factory, each object is a type of vehicle (inheritance/polymorphism)
class Vehicle {
    public:
        virtual string getType() = 0;
        virtual ~Vehicle() {};
};

class Car : public Vehicle {
    public:
        string getType() {
            return "Car";
        }
};

class Bike : public Vehicle {
    public:
        string getType() {
            return "Bike";
        }
};

class Truck : public Vehicle {
    public:
        string getType() {
            return "Truck";
        }
};



// multiple factories responsible for creating the respective object
// inherit from the main vehicle factory to use polymorphism
class VehicleFactory { // factory interface
    public:
        virtual Vehicle* createVehicle() = 0; // factory method
};

class CarFactory : public VehicleFactory {
    public:
        Vehicle* createVehicle() {
            return new Car();
        }
};

class BikeFactory : public VehicleFactory {
    public:
        Vehicle* createVehicle() {
            return new Bike();
        }
};

class TruckFactory : public VehicleFactory {
    public:
        Vehicle* createVehicle() {
            return new Truck();
        }
};
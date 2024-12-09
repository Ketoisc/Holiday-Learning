#include <string>
#include <iostream>
using namespace std;

// Ensures a class only has one instance, and provides a global, single point of access to it
// can think of it as a utility class/library
// principles: single instance, global access, lazy/eager initialization, thread safety, private constructor

class singleton {
    private:
        static singleton* instance;
        int data;

        singleton(int data) { // private constructor. prevents direct instantiation, and it only happens once when getInstance() is called
            this->data = data;
        }

    public:
        static singleton* getInstance(int data) { // only way to access the instance in other functions is through getInstance
            if (instance == NULL) {
                instance = new singleton(data);
            }
            return instance; // returns the same, static local instance variable
        }

};

singleton* singleton::instance = nullptr;

int main() {
    singleton* singleton1 = singleton::getInstance(5);

}
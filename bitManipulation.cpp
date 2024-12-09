#include <iostream>
using namespace std;

// c++ int is 32 bits
// therefore 32 digits in binary

int main() {
    int x = 6; //  6 = 00000110
    int y = 12; //12 = 00001100
    int z = 0; 

    z = x & y; // checks if each respective bit matches in value
    cout << "AND = " << z << endl; // = 4, turns into 00000100

    z = x | y; // checks if any bit is 1 (can be both)
    cout << "OR = " << z << endl; // = 14, turns into 00001110

    z = x ^ y; // exclusive or. checks if only one of the two bits is 1, bits must be different
    cout << "XOR = " << z << endl; // = 10, turns into 00001010

    z = x << 1; // left shift by 1,
    cout << "SHIFT LEFT = " << z << endl; // = 12, doubled, is 00001100

    z = x >> 1; // right shift by 1, 
    cout << "SHIFT RIGHT = " << z << endl; // = 3, halved, is 00000011
    return 0;
}
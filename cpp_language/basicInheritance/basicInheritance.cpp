/* Basic Inheritance
Derived classes call the super class's constructor

private, protected, public:
    Private members are accessible only to the base class
    Protected members are accessible to the base class and any deriving class
    Public members are accessible by everything.
*/

#include <helpers.hpp>
#include <iostream>
using std::cout;
using std::endl;

class Base {
public:
    Base() : publicShit(0), privateShit(1), protectedShit(2)
    {
        cout << "Base constructor called" << endl;
    }

    int publicShit;

protected:
    int protectedShit;

private:
    int privateShit;
};

class Derived : public Base {
public:
    Derived()
    {
        cout << "Derived constructor called" << endl;
    }

    void get_public() { cout << publicShit << endl; }
    void get_protected() { cout << protectedShit << endl; }

    // Derived classes cannot access the private members of the super class
#if ERROR
    void get_private() { cout << privateShit << endl; }
#endif
};





int main() {
    Base b;
    Derived d;
}
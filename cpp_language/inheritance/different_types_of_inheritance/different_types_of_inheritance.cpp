/*
NB: For all below, this is from the viewpoint of the outside accessors of the derived class.
    Internally, all access looks like it would with public inheritance
Public Inheritance:
    The classic, keeps acces the same as the parent's.
    This is the most common type, and models an "is-a" relationship with the superclass.

Protected Inheritance:
    Turns public members protected, rest is unchanged from parent.
    Models an "is-implemented-in-terms-of" relationship. Since the superclass's members aren't exposed publicly, this is for utility only in implementation, not usage.

Private Inheritance:
    Turns all members private.
    Same modeling concept as protected inheritance.


*/
#include <helpers.hpp>
#include <iostream>
using std::cout;
using std::endl;



class A {
public:
    void ambiguous() { cout << "A's ambiguous()" << endl;}
    int stuff = 1337;
};

class B {
public:
    void ambiguous() { cout << "B's ambiguous()" << endl;}
};

class C {
public:
    void ambiguous() { cout << "C's ambiguous()" << endl;}
};

class Privately_Inherited : private A
{
public:
    // We can still access stuff, even though we are privately inheriting
    Privately_Inherited() { cout << stuff << endl; }
};





int main()
{
    Privately_Inherited P_1;

    // Won't compile because we are privately inheriting
#if ERROR
    cout << P_1.stuff << endl;
#endif 

    // Protectedly_Inherited P_2;
}

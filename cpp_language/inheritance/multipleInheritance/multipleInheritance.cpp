/* Multiple inheritance
Each base Class's constructor is called

There can be inherited members that have the same name, however 
you have to specify which base class that you're referring to by using
the scope operator.

Behold, the power of C++
    d.A::ambiguous();
    d.B::ambiguous();
*/
#include <iostream>
using namespace std;

class A {
public:
    void ambiguous() { cout << "A's ambiguous()" << endl;}
};

class B {
public:
    void ambiguous() { cout << "B's ambiguous()" << endl;}
};

class Derived : public A, public B {
public:
    void report() {
        A::ambiguous();
        B::ambiguous();
    }
};

int main() {
    Derived d;

    d.report();

    // Absolute Zozzle
    d.A::ambiguous();
    d.B::ambiguous();
}
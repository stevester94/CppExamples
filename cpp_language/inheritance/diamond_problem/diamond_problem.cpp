/*
Alright so the diamond problem is where there's a base class, two deriving
    classes, and then a bottom-most deriving class that derives from those other two.

Because inheritance is all fucky, that bottom-most class would get two copies of everything from the base class.

NB: This is not fixing the case where the two middle classes actually have conflicting definitions for something!
    This is just fixing the self inflicted problem of how inheritance works.

We solve this by using virtual inheritance. How that exactly works, I have no fucking idea. But it works

Note you need to inherit publicly as in: virtual public <super>
*/
#include <helpers.hpp>
#include <iostream>
using std::cout;
using std::endl;

class A {
public:
    virtual void ambiguous() { cout << "A's ambiguous()" << endl;}
};

class B : virtual public A {
public:
};

class C : virtual public A{
public:
};

class D : public B, public C {
public:
};


int main()
{
    D d;
    d.ambiguous();
    
    C c;
    c.ambiguous();
}
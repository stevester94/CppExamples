/*
If you specify any constructors, the others will not be generated unles you force them with
    T() = default;

You can forcibly disable implicitly generated methods with
    T() = delete;

Destructors of base classes should always be virtual
    Otherwise the derived classes destructor will not be called.
*/
#include <helpers.hpp>
#include <iostream>
using std::cout;
using std::endl;

class A
{
public:
    // Specifying a constructor like this halts the compiler from implictly defining A() <as seen in B()>
    A(int data) : x(data) {}

    // We can force its creation like this, or we could have just written it ourselves
    A() = default;

    // A(const A& old) { cout << "Copy c'tor" << endl; }

    int x = 10;

    ~A() { cout << "A d'tor called" << endl; }
};

class B
{
public:
    // Note here how we wanted to delete the copy constructor, so we actually HAVE to explicitly imply the default c'tor
    B() = default;
    B(const B& old) = delete;

    int x;

    ~B() { cout << "B d'tor called" << endl; }
};

class C
{
public:
    C() = default;
    virtual ~C() { cout << "C d'tor called" << endl; }
};

class D : public C
{
public:
    ~D() { cout << "D d'tor called" << endl; }
};

int main()
{
    {
        A a1(1337);
        A a2;

        A a3(a1);
        B b;
    }

    ANNOUNCE_SECTION("Destructors need to be virtual");
    // B's destructor is never called!
    A* actually_b = (A*)new B;
    delete actually_b;

    ANNOUNCE_SECTION("Using a virtual destructor works");
    C* actually_D = (C*)new D;
    delete actually_D;
}
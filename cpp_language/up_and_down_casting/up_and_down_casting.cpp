/* Advanced polymorphism
Upcasting:
    Casting a derived-class reference or pointer to a super-class
    Will always work

Downcasting:
    Casting a super-class to a derived-class
    Won't always work, and is dangerous to do so manually, so use dynamic_cast

Sidecasting:
    Casting one derived class to another derived class
    Obviously dangerous, and I can't even think of an example when it would work

*/
#include <helpers.hpp>
#include <iostream>
using namespace std;

class Base {
public:
    virtual void report() { cout << "I think I am Base" << endl; }
};

class Left : public Base {
public:
    void report() { cout << "I am Left" << endl; }
    const int data[1000] = {0};
};

class Right : public Base {
public:
    void report() { cout << "I am Right" << endl; }
    const int data[1000] = {1337};
};

int main() {
    Left l;
    Right r;
    Base b;


    ANNOUNCE_SECTION("Upcast is always ok");
    Base* actually_l = (Base*)&l;
    actually_l->report();

    /*
    This downcast is not valid, but there are no errors whatsoever
    */
    ANNOUNCE_SECTION("Downcast is dangerous");
    Right* actuallyB = (Right*)&b;
    cout << actuallyB->data[999] << endl; // If this was a right, we'd be printing 1337

    /*
    Check if the downcast is valid. The compiler can even do some static analysis
    */
    ANNOUNCE_SECTION("Use dynamic_cast for downcasting safely");
    Right* actuallyB2 = dynamic_cast<Right*>(&b);
    if(actuallyB2 == nullptr)
        cout << "Our dynamic cast failed" << endl;
    else
        cout << "This would segfault" << actuallyB2->data[999] << endl;
}
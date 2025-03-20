/*

L stands for "Locator Value". This identifies a non-temporary object or member. This is basically anything that has a definite position in memory

R value: These typically do not have a definite location. They cannot be assigned to
- Literals like 5, and 'a', are R values

And of course it gets worse in C++11...

Prvalues: These are "Pure" R values. These are the above definition of R values

Xrvalues: These are "expiring" object, basically at the end of its lifecycle. This allows for move semantics

*/
#include <helpers.hpp>
#include <iostream>
using std::cout;
using std::endl;


#include <iostream>
#include <vector>

class MovableClass {
public:
    MovableClass() { std::cout << "Default constructor\n"; }
    MovableClass(const MovableClass&) { std::cout << "Copy constructor\n"; }
    MovableClass(MovableClass&&) { std::cout << "Move constructor\n"; }
    ~MovableClass() { std::cout << "Destructor\n"; }
};


MovableClass createMovable() {
    MovableClass temp;
    return temp; // temp is an xvalue when it's returned by value
}

int main() {
/*
This fails because we don't have the right constructor
*/
#if ERROR
    MovableClass M;
    M = MovableClass();
#endif

    // This is still default constructor
    {
        MovableClass M = MovableClass();
    }
    

    // This is a copy constructor
    {
        MovableClass M1;
        MovableClass M2 = M1;
    }
    
    // This is a move constructor!
    {
        MovableClass M1;
        MovableClass M2 = std::move(M1);
    }

    return 0;
}
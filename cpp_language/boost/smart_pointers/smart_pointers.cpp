#include <boost/shared_ptr.hpp>
#include <iostream>


/*
This module demonstrates how subclassing and superclassing works with both boost pointers and
vanilla pointers.
The main take-away is that boost pointers work in the same way as vanilla pointers:
- implicit upcasting, IE from a base class to a superclass is always OK 
    - virtual methods will always be honored, this is the point of polymorphism
- implicit downcasting never works
- Explicit downcasting works
    - if using static_cast, it will always "work", thought the results are unpredicable
    - if using dynamic_cast, a check is performed under the hood, if the cast is not possible
          then a null pointer is returned
*/

class A 
{
public:
    virtual void report() { std::cout << "Class A reporting" << std::endl; }

    virtual ~A()
    {
        std::cout << "A destructing" << std::endl;
    }
};

class B : public A
{
public:
    virtual void report() { std::cout << "Class B reporting" << std::endl; }

    ~B()
    {
        std::cout << "B destructing" << std::endl;
    }
};


void this_function_wants_a_boost_ptr(boost::shared_ptr<A> A_ptr)
{
    A_ptr->report();
}

// This is always valid!
void implicit_up_cast(A* a)
{
    a->report();
}

// Implicit down casts do not work
void implicit_down_cast(B* b)
{
    b->report();
}


void explicit_static_down_cast(A* a)
{
    std::cout << "attempting static_down_cast to B" << std::endl;

    B* b_ptr = static_cast<B*>(a);

    b_ptr->report();
}

void explicit_dynamic_down_cast(A* a)
{
    std::cout << "attempting dynamic_down_cast" << std::endl;

    B* b = dynamic_cast<B*>(a);

    if(b == NULL)
    {
        std::cout << "dynamic_cast failed" << std::endl;
        return;
    }
    else
    {
        b->report();
    }
}
    
    
// This is also valid, isn't boost great...
void implicit_boost_upcast(boost::shared_ptr<A> A_ptr)
{
    A_ptr->report();
}


void explicit_boost_down_cast(boost::shared_ptr<A> A_ptr)
{
    std::cout << "Attempting dynamic down_cast of boost pointer to B" << std::endl;
    boost::shared_ptr<B> b_ptr = boost::dynamic_pointer_cast<B>(A_ptr);

    if(b_ptr == NULL)
    {
        std::cout << "dynamic down cast failed" << std::endl;
        return;
    }   
    else
    {
        b_ptr->report();
    }
}


int main()
{
    A a;
    B b;
    A* actually_b = (A*)&b;

    implicit_up_cast(&a);
    implicit_up_cast(&b);
    //implicit_down_cast(actually_b); // This is not valid!

    boost::shared_ptr<A> shared_A_actually_B(new B());
    boost::shared_ptr<A> shared_A(new A()); 

    implicit_boost_upcast(shared_A_actually_B); // upcasts implicitly
    
    // Can't just pass this in, have to be specific with a boost 
    //this_function_wants_a_boost_ptr(a);

    explicit_static_down_cast(actually_b);  // Works fine
    explicit_static_down_cast(&a); // This one is interesting, it works, but only by chance since static_cast doesn't perform checks of the type...
    explicit_dynamic_down_cast(actually_b); // Works fine
    explicit_dynamic_down_cast(&a); // This one will say it failed

    explicit_boost_down_cast(shared_A_actually_B); // Works fine
    explicit_boost_down_cast(shared_A); // This will fail, the dynamic cast return =='s a NULL
     


    return 0;
}

/* Multiple inheritance
Each base Class's constructor is called

There can be inherited members that have the same name, however 
you have to specify which base class that you're referring to by using
the scope operator
*/
#include <iostream>
using namespace std;

class A {
public:
	A() {
		cout << "A's constructor called" << endl;
		ambiguous = 1337;
		notAmbiguousA = 'A';
	}

	int ambiguous;
	char notAmbiguousA;
};

class B {
public:
	B() {
		cout << "B's constructor called" << endl;
		ambiguous = 420;
		notAmbiguousB = 'B';
	}

	int ambiguous;
	char notAmbiguousB;
};

class Derived : public A, public B {
public:
	void report() {
		// Here we have to specify which base class we're refering to
		// since they have the same name.
		cout << A::ambiguous << " " << B::ambiguous << endl;

		// Here we don't because it's not ambiguous
		cout << notAmbiguousA << " " << notAmbiguousB << endl;
	}
};

int main() {
	Derived d;

	d.report();
}
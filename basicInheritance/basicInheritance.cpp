/* Basic Inheritance
private, protected, public:
	Private members are accessible only to the base class
	Protected members are accessible to the base class and any deriving class
	Public members are accessible by everything.

	These rules need to be considered when trying to access through other functions
		kind of like in a different scope
*/
#include <iostream>

using namespace std;

class Base {
public:
	Base() {
		privateShit = 1;
		protectedShit = 420;
	}

protected:
	int protectedShit;

private:
	int privateShit; //Cannot be accessed by a deriving class
};

class Derived : public Base {
public:
	Derived() {
		int publicShit = 1337;
	}

	// You can't do this

	// void printPrivateShit() {
	// 	cout << privateShit << endl;
	// }

	// You can do this
	void printProtectedShit() {
		cout << protectedShit << endl;
	}
};





int main() {
	Base b;
	Derived d;

	//Can't do either of these:
	// cout << d.protectedShit;
	// cout << d.privateShit;

	// Can do this because the access is ocurring within the class
	d.printProtectedShit();
}